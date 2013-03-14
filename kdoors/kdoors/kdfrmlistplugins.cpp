
#include "kdfrmlistplugins.h"
// include des fichiers QT
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qcheckbox.h>
#include <qdir.h>
// include des fichiers KDE
#include <klineedit.h>
#include <klocale.h>
#include <kapp.h>
// include des fichiers diverses
#include <stdio.h>



KDfrmListPlugins::KDfrmListPlugins( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, true, fl )
{
    if ( !name )
			setName( "KDfrmListPlugins" );

		resize( 280, 480 );
    setCaption( i18n( "Liste des plugins" ) );


		PluginsListBox = new KDPluginsListBox(this);
    PluginsListBox->setGeometry( QRect( 5, 5, 270, 250 ) );
 	  connect( PluginsListBox, SIGNAL(selectionChanged(QListBoxItem*)),this,SLOT(slotselectionChanged(QListBoxItem*) ) );


    multilineEdit = new QMultiLineEdit(this);
    multilineEdit->setGeometry( QRect( 5, 260, 270, 160 ) );

    btnOk = new QPushButton( this, "btnOk" );
    btnOk->setGeometry( QRect( 158, 425, 50, 32 ) );
    btnOk->setText( i18n( "Ok" ) );

    btnCancel = new QPushButton( this, "btnCancel" );
    btnCancel->setGeometry( QRect( 10, 425, 90, 32 ) );
    btnCancel->setText( i18n( "Annuler" ) );

    // signals and slots connections
		connect( btnOk, SIGNAL( clicked()), SLOT( accept() ) );
		connect( btnCancel, SIGNAL( clicked()), SLOT( reject() ) );
		
		//charge la liste des plugins
		CheckPlugins();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
KDfrmListPlugins::~KDfrmListPlugins()
{
    // no need to delete child widgets, Qt does it all for us
}

void KDfrmListPlugins::accept()
{
	QDialog::accept();	
}

void KDfrmListPlugins::slotselectionChanged(QListBoxItem* AItem)
{

	KDPluginsListBoxItem* item;
	
	item = dynamic_cast<KDPluginsListBoxItem*>(AItem);
	QDomElement element = item->element();

  QDomNode node = element.namedItem("Options").firstChild();
	
	// efface le memo
	multilineEdit->clear();
	// ajoute les infos du plugins selectionner
	multilineEdit->insertLine("Faire une systeme de tag : ");
	multilineEdit->insertLine("Plugins : "+item->element().attribute("Title"));
	multilineEdit->insertLine("Version : "+item->element().attribute("Version"));
	multilineEdit->insertLine("Info : "+item->element().attribute("Info"));
	multilineEdit->insertLine("Type : "+item->element().attribute("Type"));
	multilineEdit->insertLine("Author : "+item->element().attribute("Author"));
	multilineEdit->insertLine("Email : "+item->element().attribute("Email"));
	multilineEdit->insertLine("Web : "+item->element().attribute("Web"));
	multilineEdit->insertLine("Solution : "+item->element().attribute("Solution"));
//	multilineEdit->insertLine("Options : "+item->element().attribute("Options"));
}



void KDfrmListPlugins::slotCheckGetInfo(KProcess* AProcess,const QDomElement& element)
{
	//ajout l'item
 	KDPluginsListBoxItem* item = new KDPluginsListBoxItem(element);
	PluginsListBox->insertItem(item);
//	delete AProcess;
//		plugins_running = false;
	process_count--;
	delete AProcess;

}


void KDfrmListPlugins::CheckPlugins()
{
	KPlugins* plugins;


  QDir d("/home/b_adele/kdoors/scripts/");
  d.setFilter( QDir::Files | QDir::Hidden | QDir::NoSymLinks );

  const QFileInfoList *list = d.entryInfoList();
  QFileInfoListIterator it( *list );      // create list iterator
  QFileInfo *fi;                          // pointer for traversing
	process_count = 0;
  while ( (fi=it.current()) ) {           // for each file...
//		plugins_running = true;
		process_count++;
		plugins = new KPlugins();
		// sera supprimer par l'evenement suivant	receivedStdout	
		connect (plugins,SIGNAL(ReturnInfo (KProcess*,const QDomElement&)),SLOT(slotCheckGetInfo (KProcess*,const QDomElement&)));
//		plugins->GetInfo(fi->dirPath()+"/"+fi->fileName());
		plugins->GetInfo(fi->fileName());
		while (process_count>4) {
			kapp->processEvents();
		}
//		delete plugins;
    ++it;                               // goto next list element
  }
}


bool KDfrmListPlugins::IsSelected()
{
	return PluginsListBox->currentItem()!=-1;	
}


QDomElement& KDfrmListPlugins::GetSelectedElement()
{
//	KDPluginsListBoxItem* item;
	int										index;

	index = PluginsListBox->currentItem();
//	item = dynamic_cast<KDPluginsListBoxItem*>(PluginsListBox->item(index));
	return PluginsListBox->GetElement(index);
}
