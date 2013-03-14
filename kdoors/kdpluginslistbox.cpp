/*
 *   kmail: KDE mail client
 *   This file: Copyright (C) 2000 Espen Sand, espen@kde.org
 *
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <qtextstream.h>


// include file for KDE
#include <kio/job.h>
#include <kio/netaccess.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kapp.h>

#include <kcolordlg.h>
#include <kcolordrag.h>



#include "kdpluginslistbox.h"

KDPluginsListBox::KDPluginsListBox( QWidget *parent, const char *name, WFlags f )
  :KListBox( parent, name, f ), mCurrentOnDragEnter(-1)
{
  connect( this, SIGNAL(selected(int)), this, SLOT(newColor(int)) );
  setAcceptDrops( true);
}



QDomElement& KDPluginsListBox::GetElement(int AIndex)
{
	KDPluginsListBoxItem* item;

	item = dynamic_cast<KDPluginsListBoxItem*>(this->item(AIndex));
	return item->element();
}


bool KDPluginsListBox::openDocument(const KURL& url, const char *format /*=0*/)
{
  QString tmpfile;

  KIO::NetAccess::download( url, tmpfile );
  /////////////////////////////////////////////////
  // TODO: Add your document opening code here
  /////////////////////////////////////////////////
	QFile f(tmpfile);
	
	QDomDocument docHosts("FilePlugins");
	if ( !f.open( IO_ReadOnly ) )
      return false;
  if ( !docHosts.setContent( &f ) ) {
      f.close();
      return false;
  }
  f.close();


  QDomElement host_element = docHosts.documentElement();

  QDomNode node = docHosts.namedItem("Plugins_List").firstChild();
	
	
    while( !node.isNull() ) {
        QDomElement element = node.toElement();
        if( !element.isNull() ) {
					 	KDPluginsListBoxItem* item = new KDPluginsListBoxItem(element);
						this->insertItem(item);
        }
        node = node.nextSibling();
    }

  KIO::NetAccess::removeTempFile( tmpfile );

  m_modified=false;
//  m_modified=true;
  return true;
}


bool KDPluginsListBox::saveDocument(const KURL& url, const char *format /*=0*/)
{
  QDomDocument docHosts("FilePlugins");
 	
	QFile f(url.path());
  if ( !f.open(IO_WriteOnly) )
  	return false;
	
  QTextStream t( &f );        // use a text stream
	
	// ajout des commentaires
	QDomComment comment;
  comment = docHosts.createComment("Fichier creer par KDoor");	 	
  docHosts.appendChild( comment );
  comment = docHosts.createComment("(c) Bruno Adele");	 	
  docHosts.appendChild( comment );	 	
  comment = docHosts.createComment("Logiciel sous licence GPL");	 	
  docHosts.appendChild( comment );

	// ajout de la liste des plugins
	QDomElement plugins_list = docHosts.createElement( "Plugins_List" );

	for (int index=0;index<this->count();index++) {
	  plugins_list.appendChild( this->GetElement(index));	 	
		kapp->processEvents();
	}
  docHosts.appendChild( plugins_list );	
	docHosts.save(t,3);
  f.close();

  return true;
}

bool KDPluginsListBox::saveModified()
{
  bool completed=true;

  if(m_modified)
  {
    KDoorsApp *win=(KDoorsApp *) parent();
    int want_save = KMessageBox::warningYesNoCancel(win, i18n("Warning"),
                                         i18n("The current file has been modified.\n"
                                              "Do you want to save it?"));
    switch(want_save)
    {
      case 1:
           if (m_url.fileName() == i18n("Untitled"))
           {
             win->slotSavePlugins();
           }
           else
           {
             saveDocument(m_url);
       	   };

       	   //deleteContents();
           completed=true;
           break;

      case 2:
           setModified(false);
           //deleteContents();
           completed=true;
           break;	

      case 3:
           completed=false;
           break;

      default:
           completed=false;
           break;
    }
  }

  return completed;
}


void KDPluginsListBox::setEnabled( bool state )
{
  if( state == isEnabled() )
  {
    return;
  }

  QListBox::setEnabled( state );
  for( uint i=0; i<count(); i++ )
  {
    updateItem( i );
  }
}



void KDPluginsListBox::dragEnterEvent( QDragEnterEvent *e )
{
  if( KColorDrag::canDecode(e) && isEnabled() )
  {
    mCurrentOnDragEnter = currentItem();
    e->accept( true );
  }
  else
  {
    mCurrentOnDragEnter = -1;
    e->accept( false );
  }
}


void KDPluginsListBox::dragLeaveEvent( QDragLeaveEvent * )
{
  if( mCurrentOnDragEnter != -1 )
  {
    setCurrentItem( mCurrentOnDragEnter );
    mCurrentOnDragEnter = -1;
  }
}


void KDPluginsListBox::dragMoveEvent( QDragMoveEvent *e )
{
  if( KColorDrag::canDecode(e) && isEnabled() )
  {
    KDPluginsListBoxItem *item = (KDPluginsListBoxItem*)itemAt( e->pos() );
    if( item != 0 )
    {
      setCurrentItem ( item );
    }
  }
}


void KDPluginsListBox::dropEvent( QDropEvent *e )
{
  QColor color;
  if( KColorDrag::decode( e, color ) ) 
  {
    int index = currentItem();
    if( index != -1 )
    {
      triggerUpdate( false ); // Redraw item
    }
    mCurrentOnDragEnter = -1;
  }
}



KDPluginsListBoxItem::KDPluginsListBoxItem( const QDomElement& a_element)
  : QListBoxItem()
{
	m_element = a_element;
}

KDPluginsListBoxItem::~KDPluginsListBoxItem()
{
}


QString KDPluginsListBoxItem::text() const
{
	return m_element.attribute("Title");
}


void KDPluginsListBoxItem::paint( QPainter *p )
{
  QFontMetrics fm = p->fontMetrics();

  p->drawText( 1, fm.ascent() + fm.leading()/2, text() );
}


int KDPluginsListBoxItem::height(const QListBox *lb ) const
{
  return( lb->fontMetrics().lineSpacing()+1 );
}


int KDPluginsListBoxItem::width(const QListBox *lb ) const
{
  return( 30 + lb->fontMetrics().width( text() ) + 6 );
}
