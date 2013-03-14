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

#ifndef _PLUGINS_LISTBOX_H_
#define _PLUGINS_LISTBOX_H_

// include QT
#include <qdom.h>
#include <qfile.h>

#include <klistbox.h>
#include <kplugins.h>
#include <kurl.h>
#include "kdoors.h"

class KDPluginsListBox : public KListBox
{
  Q_OBJECT

  public:
    KDPluginsListBox( QWidget *parent=0, const char * name=0, WFlags f=0 );
		/* retourne un element XML d'un plugins */
		QDomElement& GetElement(int AIndex);
	  /** ouvre la liste des plugins */
	  bool openDocument(const KURL& url, const char *format=0);
	  /** Sauvegarde les plugins */
	  bool saveModified();	
	  /** Teste si le document à été modifié */
		bool isModified(){ return m_modified; };


  public slots:
    virtual void setEnabled( bool state );
	  /** Sauvegarde les plugins */
    bool saveDocument(const KURL& url, const char *format=0);
		KURL& URL() { return m_url;}
  	/** sets the modified flag for the document after a modifying action on the view connected to the document.*/
	  void setModified(bool value=true){ m_modified=value; };

  protected:
    void dragEnterEvent( QDragEnterEvent *e );
    void dragLeaveEvent( QDragLeaveEvent *e );
    void dragMoveEvent( QDragMoveEvent *e );
    void dropEvent( QDropEvent *e );

  private slots:

  private:
    int mCurrentOnDragEnter;
		bool m_modified;
	  KURL m_url;


};


class KDPluginsListBoxItem : public QListBoxItem
{
  public:

		/* retourne un element XML d'un plugins */
		QDomElement& element() { return m_element;}
		
    KDPluginsListBoxItem( const QDomElement& a_element);
    ~KDPluginsListBoxItem();

    virtual QString text() const;

  protected:
		QDomElement m_element;
    virtual void paint( QPainter * );
    virtual int height( const QListBox * ) const;
    virtual int width( const QListBox * ) const;

  private:
};

#endif // _PLUGINS_LISTBOX_H_

