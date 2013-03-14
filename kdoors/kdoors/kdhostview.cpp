/***************************************************************************
                          kdhostview.cpp  -  description
                             -------------------
    begin                : Tue Jan 16 2001
    copyright            : (C) 2001 by Bruno Adele
    email                : b_adele@netcourrier.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <qfile.h>
#include <qtextstream.h>

// include file for KDE
#include <kio/job.h>
#include <kio/netaccess.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kapp.h>


#include "kdhostview.h"

KDHostView::KDHostView(QWidget *parent, const char *name) : KListView(parent,name)
{
  doc = QDomDocument("FileHosts");
	// ajout de la liste des hotes
	hosts_list = doc.createElement( "Hosts_List" );
  doc.appendChild( hosts_list );	 	


  setBackgroundMode(PaletteBase);

	addColumn("Etat");
	addColumn("Adresse Ip");
	addColumn("Nom de Domaine");
	addColumn("Action");
//	setColumnAlignment(1,Qt::AlignRight);
	setShowSortIndicator( true );
  setAllColumnsShowFocus( true );
//	setSorting(1);
	setModified(false);
}

KDHostView::~KDHostView(){
}


void KDHostView::AddHost(QString AStatus,QString AIp,QString AAddress)
{

	QDomElement element = doc.createElement("Host");
  hosts_list.appendChild( element );
	new KDHostItem( this, element,AStatus,AIp,AAddress);
}



void KDHostView::DeleteHost(KDHostItem* AHostItem)
{

	hosts_list.removeChild(AHostItem->element());
	delete AHostItem;
}


bool KDHostView::openDocument(const KURL& url, const char *format /*=0*/)
{
  QString tmpfile;

  KIO::NetAccess::download( url, tmpfile );
  /////////////////////////////////////////////////
  // TODO: Add your document opening code here
  /////////////////////////////////////////////////
	QFile f(tmpfile);
	
/*	QString line;
  if ( f.open(IO_ReadOnly) ) {    // file opened successfully
      QTextStream t( &f );        // use a text stream
			QString s1,s2,s3;
      while ( !t.eof() ) {        // until end of file...
					line = t.readLine();
					if (line.find(QRegExp("^ *#"))==-1) {
						QStringList list(QStringList::split(",",line,true));
						QStringList::Iterator it(list.begin());
						s1 = (*it).latin1(); it++;
						s2 = (*it).latin1(); it++;
						s3 = (*it).latin1();
					  new QListViewItem( this, s3,s1,s2);
					}
      }
      f.close();
  }*/

	QDomDocument docHosts("FileHost");
	if ( !f.open( IO_ReadOnly ) )
      return false;
  if ( !docHosts.setContent( &f ) ) {
      f.close();
      return false;
  }
  f.close();


  QDomElement host_element = docHosts.documentElement();

  QDomNode node = docHosts.namedItem("Hosts_List").firstChild();
	
	
//	if (!node.isNull()) {
//  	node.firstChild();
    while( !node.isNull() ) {
        QDomElement e = node.toElement(); // try to convert the node to an element.
        if( !e.isNull() ) { // the node was really an element.
      //      cout << e.tagName() << endl;
  				  new QListViewItem( this, e.attribute("Status"),e.attribute("Ip"),e.attribute("Address"));

        }
        node = node.nextSibling();
    }
//  }


/*  if ( f.open(IO_ReadOnly) ) {    // file opened successfully
      QTextStream t( &f );        // use a text stream
			QString s1,s2,s3;
      while ( !t.eof() ) {        // until end of file...
					line = t.readLine();
					if (line.find(QRegExp("^ *#"))==-1) {
						QStringList list(QStringList::split(",",line,true));
						QStringList::Iterator it(list.begin());
						s1 = (*it).latin1(); it++;
						s2 = (*it).latin1(); it++;
						s3 = (*it).latin1();
					  new QListViewItem( this, s3,s1,s2);
					}
      }
      f.close();
  }*/



  KIO::NetAccess::removeTempFile( tmpfile );

  m_modified=false;
//  m_modified=true;
  return true;
}


bool KDHostView::saveModified()
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
             win->slotSaveHosts();
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


bool KDHostView::saveDocument(const KURL& url, const char *format /*=0*/)
{


//  QDomDocument docHosts("FileHosts");
 	
	QFile f(url.path());
  if ( f.open(IO_WriteOnly) ) {    // file opened successfully
    QTextStream t( &f );        // use a text stream
	
		// ajout des commentaires
/*		QDomComment comment;
	  comment = docHosts.createComment("Fichier creer par KDoor");	 	
	  docHosts.appendChild( comment );	 	
	  comment = docHosts.createComment("(c) Bruno Adele");	 	
	  docHosts.appendChild( comment );	 	
	  comment = docHosts.createComment("Logiciel sous licence GPL");	 	
	  docHosts.appendChild( comment );
		
		// ajout de la liste des hotes
		QDomElement hosts_list = docHosts.createElement( "Hosts_List" );
	 	QListViewItemIterator it( this );
 		for ( ; it.current(); ++it ) {
			QDomElement host_element = docHosts.createElement( "Host" );
		  host_element.setAttribute( "Status", it.current()->text(0) );
		  host_element.setAttribute( "Ip", it.current()->text(1) );
		  host_element.setAttribute( "Address", it.current()->text(2) );
			QDomElement el;

			el = dynamic_cast<KDHostItem*>(it.current())->element();
		  hosts_list.appendChild( el );	 //host_element	
			kapp->processEvents();
		}
	  docHosts.appendChild( hosts_list );	 	*/
		doc.save(t,3);
    f.close();
  }





	m_modified=false;
  return true;
}



