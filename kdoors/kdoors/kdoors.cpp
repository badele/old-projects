// include files for QT
#include <qdir.h>
#include <qpainter.h>
#include <qcheckbox.h>


// include files for KDE
#include <kiconloader.h>
#include <kfiledialog.h>
#include <kmenubar.h>
#include <klocale.h>
#include <kconfig.h>
#include <kstdaction.h>
#include <kdialogbase.h>
#include <klineedit.h>

// application specific includes
#include "kdoors.h"
#include "DlgIpRange.h"
#include "kdfrmlistplugins.h"
#include "kdfrmparamplugins.h"
#include "kresolvename.h"
#include "kdhostitem.h"


#define ID_STATUS_MSG 1

 KDoorsApp::KDoorsApp(QWidget* , const char* name):KDockMainWindow(0, name)
{
  config=kapp->config();

  ///////////////////////////////////////////////////////////////////
  // call inits to invoke all other construction parts
  initStatusBar();
  initActions();
  initDocument();
  initView();
	initMenuBar();
	
  readOptions();

  ///////////////////////////////////////////////////////////////////
  // disable actions at startup
  fileSaveHosts->setEnabled(false);
  fileSaveAsHosts->setEnabled(false);
  editCut->setEnabled(false);
  editCopy->setEnabled(false);
  editPaste->setEnabled(false);


}

KDoorsApp::~KDoorsApp()
{

}

void KDoorsApp::initActions()
{

	// hosts
	
  fileOpenHosts		 	= new KAction(i18n("Ajout un fichier"), 0, 0, this, SLOT(slotOpenHosts()), actionCollection(),"open_hosts");
  fileClearHosts		= new KAction(i18n("Effacer les hotes"), 0, 0, this, SLOT(slotClearHosts()), actionCollection(),"clear_hosts");
  fileSaveHosts			= new KAction(i18n("Sauver"), 0, 0, this, SLOT(slotSaveHosts()), actionCollection(),"save_hosts");
  fileSaveAsHosts 	= new KAction(i18n("Sauver sous"), 0, 0, this, SLOT(slotSaveAsHosts()), actionCollection(),"saveas_hosts");
  scanHosts 				= new KAction(i18n("Scanner"), 0, 0, this, SLOT(slotScanHosts()), actionCollection(),"scan_hosts");


	// plugins
  fileOpenPlugins 	= new KAction(i18n("Ouvrir"), 0, 0, this, SLOT(slotOpenPlugins()), actionCollection(),"open_plugins");
  fileSavePlugins		= new KAction(i18n("Sauver"), 0, 0, this, SLOT(slotSavePlugins()), actionCollection(),"save_plugins");
  fileSaveAsPlugins = new KAction(i18n("Sauver sous"), 0, 0, this, SLOT(slotSaveAsPlugins()), actionCollection(),"saveas_plugins");
  addPlugins				= new KAction(i18n("Ajouter plugins"), 0, 0, this, SLOT(slotAddPlugins()), actionCollection(),"add_plugins");



  fileNew = KStdAction::openNew(this, SLOT(slotFileNew()), actionCollection());
//  fileOpen = KStdAction::open(this, SLOT(slotFileOpen()), actionCollection());
  fileOpenRecent = KStdAction::openRecent(this, SLOT(slotFileOpenRecent(const KURL&)), actionCollection());
//  fileSaveAs = KStdAction::saveAs(this, SLOT(slotFileSaveAs()), actionCollection());
  fileClose = KStdAction::close(this, SLOT(slotFileClose()), actionCollection());
  fileQuit = KStdAction::quit(this, SLOT(slotFileQuit()), actionCollection());
  editCut = KStdAction::cut(this, SLOT(slotEditCut()), actionCollection());
  editCopy = KStdAction::copy(this, SLOT(slotEditCopy()), actionCollection());
  editPaste = KStdAction::paste(this, SLOT(slotEditPaste()), actionCollection());
  viewToolBar = KStdAction::showToolbar(this, SLOT(slotViewToolBar()), actionCollection());
  viewStatusBar = KStdAction::showStatusbar(this, SLOT(slotViewStatusBar()), actionCollection());

  fileSaveHosts->setStatusText(i18n("Sauve le fichier hosts"));

  fileNew->setStatusText(i18n("Creates a new document"));
  fileOpenRecent->setStatusText(i18n("Opens a recently used file"));
//  fileSaveAs->setStatusText(i18n("Saves the actual document as..."));
  fileClose->setStatusText(i18n("Closes the actual document"));
  fileQuit->setStatusText(i18n("Quits the application"));
  editCut->setStatusText(i18n("Cuts the selected section and puts it to the clipboard"));
  editCopy->setStatusText(i18n("Copies the selected section to the clipboard"));
  editPaste->setStatusText(i18n("Pastes the clipboard contents to actual position"));
  viewToolBar->setStatusText(i18n("Enables/disables the toolbar"));
  viewStatusBar->setStatusText(i18n("Enables/disables the statusbar"));



  // use the absolute path to your kdoorsui.rc file for testing purpose in createGUI();
  createGUI();

}


void KDoorsApp::initStatusBar()
{
  ///////////////////////////////////////////////////////////////////
  // STATUSBAR
  // TODO: add your own items you need for displaying current application status.
  statusBar()->insertItem(i18n("Ready."), ID_STATUS_MSG);
	// initialise la bare de progression
	ProgressBar = new KProgress(statusBar());
	ProgressBar->setTextEnabled(true);
	ProgressBar->setGeometry(statusBar()->width()-(statusBar()->width()/3)
						,3,statusBar()->width()/3,statusBar()->height()-3);
}

void KDoorsApp::initMenuBar()
{
    QPopupMenu *fonction = new QPopupMenu();

		///////////////////////////
		/////////////////
		// !!!! faire des actions !!!!
		///////////////////////////
		/////////////////

		// test
    fonction->insertItem( "Ajouter un serveur", this, SLOT( slotaddIpRange() ), CTRL + Key_I );
    fonction->insertItem( "Résoudre les nom", this, SLOT( slotResolveName() ), CTRL + Key_R );
    fonction->insertSeparator();
    fonction->insertItem( "Suprimmer les domaines vide", this, SLOT( slotClearNoDomain() ), CTRL + Key_S );
    fonction->insertItem( "Suprimmer les hotes non dispo", this, SLOT( slotClearNoUp() ));
    fonction->insertItem( "Pinger la machine", this, SLOT( slotPing() ), CTRL + Key_P );

    menuBar()->insertItem( "&Fonction", fonction,1,1 );


		// host
/*    QPopupMenu *hosts = new QPopupMenu();
    hosts->insertSeparator();
    hosts->insertItem( "Ouvir hosts", this, SLOT( slotaddIpRange() ), CTRL + Key_I );
    hosts->insertItem( "Sauvegarder", this, SLOT( slotResolveName() ), CTRL + Key_R );
    hosts->insertItem( "Sauvegarder sous", this, SLOT( slotClearNoDomain() ), CTRL + Key_S );
    hosts->insertItem( "Test", this, SLOT( slotTest() ), CTRL + Key_T );
    menuBar()->insertItem( "&Hosts", hosts,1,1 );*/


		// plugins
/*    QPopupMenu *plugins = new QPopupMenu();
    hosts->insertItem( "Ouvir plugins", this, SLOT( slotaddIpRange() ), CTRL + Key_I );
    plugins->insertSeparator();
    plugins->insertItem( "Sauvegarder", this, SLOT( slotResolveName() ), CTRL + Key_R );
    plugins->insertItem( "Sauvegarder sous", this, SLOT( slotClearNoDomain() ), CTRL + Key_S );
    plugins->insertItem( "Ajout Plugins", this, SLOT( slotTest() ), CTRL + Key_T );
    menuBar()->insertItem( "&Plugins", plugins,1,1 );*/

}




void KDoorsApp::initDocument()
{
//  doc = new KDoorsDoc(this);
//  doc->newDocument();
}

void KDoorsApp::initView()
{ 
  ////////////////////////////////////////////////////////////////////
  // create the main widget here that is managed by KTMainWindow's view-region and
  // connect the widget to your document to display document contents.


//
  dockhostlist = createDockWidget( "Liste Hotes",SmallIcon("kdevelop") );
  setView(dockhostlist);
  setMainDockWidget( dockhostlist );
  dockhostlist->setEnableDocking( KDockWidget::DockNone);   // We cannot remove this window

  dockresultat=createDockWidget( "resultat-view", SmallIcon("resultat"), 0L, i18n("resulta"));
  dockplugins=createDockWidget( "plugins-view", SmallIcon("plugins"), 0L, i18n("plugins"));

/*  tab_resultat = new CTabCtl(outputdock, "resultat","resultat");
  dockresultat->setWidget(tab_resultat);*/

/*  doc->addView(view);
  setCentralWidget(view);	
  setCaption(viewhost->URL().fileName(),false);*/


  // Set the default window placement
  dockresultat->manualDock(dockhostlist, KDockWidget::DockBottom, 80/*size relation in %*/);
  dockplugins->manualDock(dockhostlist, KDockWidget::DockRight, 80/*size relation in %*/);

  viewhost = new KDHostView(this);
  dockhostlist->setWidget(viewhost);

  viewresult= new KDResultView(this);
  dockresultat->setWidget(viewresult);

  viewplugins = new KDPluginsListBox(this);
  dockplugins->setWidget(viewplugins);

	dockhostlist->setEnableDocking( KDockWidget::DockCorner);
  dockplugins->setEnableDocking( KDockWidget::DockCorner);
  dockhostlist->setDockSite( KDockWidget::DockCorner);
  dockplugins->setDockSite( KDockWidget::DockCorner);
}

void KDoorsApp::openDocumentFile(const KURL& url)
{
  slotStatusMsg(i18n("Opening file..."));

  viewhost->openDocument( url);
  fileOpenRecent->addURL( url );
  slotStatusMsg(i18n("Ready."));
}


/*KDoorsDoc *KDoorsApp::getDocument() const
{
  return doc;
}*/

void KDoorsApp::saveOptions()
{	
  config->setGroup("General Options");
  config->writeEntry("Geometry", size());
  config->writeEntry("Show Toolbar", viewToolBar->isChecked());
  config->writeEntry("Show Statusbar",viewStatusBar->isChecked());
  config->writeEntry("ToolBarPos", (int) toolBar("mainToolBar")->barPos());
  fileOpenRecent->saveEntries(config,"Recent Files");
}


void KDoorsApp::readOptions()
{
	
  config->setGroup("General Options");

  // bar status settings
  bool bViewToolbar = config->readBoolEntry("Show Toolbar", true);
  viewToolBar->setChecked(bViewToolbar);
  slotViewToolBar();

  bool bViewStatusbar = config->readBoolEntry("Show Statusbar", true);
  viewStatusBar->setChecked(bViewStatusbar);
  slotViewStatusBar();


  // bar position settings
  KToolBar::BarPosition toolBarPos;
  toolBarPos=(KToolBar::BarPosition) config->readNumEntry("ToolBarPos", KToolBar::Top);
  toolBar("mainToolBar")->setBarPos(toolBarPos);
	
  // initialize the recent file list
  fileOpenRecent->loadEntries(config,"Recent Files");

  QSize size=config->readSizeEntry("Geometry");
  if(!size.isEmpty())
  {
    resize(size);
  }
}

void KDoorsApp::saveProperties(KConfig *_cfg)
{
  if(viewhost->URL().fileName()!=i18n("Untitled") && !viewhost->isModified())
  {
    // saving to tempfile not necessary

  }
  else
  {
    KURL url=viewhost->URL();	
    _cfg->writeEntry("filename", url.url());
    _cfg->writeEntry("modified",viewhost->isModified());
    QString tempname = kapp->tempSaveName(url.url());
    QString tempurl= KURL::encode_string(tempname);
    KURL _url(tempurl);
    viewhost->saveDocument(_url);
  }
}


void KDoorsApp::readProperties(KConfig* _cfg)
{
  QString filename = _cfg->readEntry("filename", "");
  KURL url(filename);
  bool modified = _cfg->readBoolEntry("modified", false);
  if(modified)
  {
    bool canRecover;
    QString tempname = kapp->checkRecoverFile(filename, canRecover);
    KURL _url(tempname);
  	
    if(canRecover)
    {
      viewhost->openDocument(_url);
      viewhost->setModified();
      setCaption(_url.fileName(),true);
      QFile::remove(tempname);
    }
  }
  else
  {
    if(!filename.isEmpty())
    {
      viewhost->openDocument(url);
      setCaption(url.fileName(),false);
    }
  }
}		

bool KDoorsApp::queryClose()
{
  return viewhost->saveModified();
}

bool KDoorsApp::queryExit()
{
  saveOptions();
  return true;
}

void KDoorsApp::resizeEvent(QResizeEvent* Event)
{
	QStatusBar* b = statusBar();
	ProgressBar->setGeometry(b->width()-(b->width()/3),3,b->width()/3,b->height()-3);
}
/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////


void KDoorsApp::slotOpenHosts()
{
  slotStatusMsg(i18n("Opening file..."));
	
  if(!viewhost->saveModified())
  {
     // here saving wasn't successful

  }
  else
  {	
    KURL url=KFileDialog::getOpenURL(QString::null,
        i18n("*|All files"), this, i18n("Open File..."));
    if(!url.isEmpty())
    {
			// memorise si il y'avaient deja des hotes
			int count = viewhost->childCount();
			// ouvre le document
      viewhost->openDocument(url);
      setCaption(url.fileName(), false);
      fileOpenRecent->addURL( url );
      // flag
			if (count != viewhost->childCount()) {
				viewhost->setModified(true);
			  fileSaveHosts->setEnabled(true);
			}
		  fileSaveAsHosts->setEnabled(true);
    }
  }
  slotStatusMsg(i18n("Ready."));
}


void KDoorsApp::slotClearHosts()
{
	if (viewhost->childCount()>0) {
		viewhost->clear();
		viewhost->setModified(true);
	}
}



void KDoorsApp::slotOpenPlugins()
{
  slotStatusMsg(i18n("Opening file..."));
	
  if(!viewplugins->saveModified())
  {
     // here saving wasn't successful

  }
  else
  {	
    KURL url=KFileDialog::getOpenURL(QString::null,
        i18n("*|All files"), this, i18n("Open File..."));
    if(!url.isEmpty())
    {
			// memorise si il y'avaient deja des plugins
			int count = viewplugins->count();
			// ouvre le document
      viewplugins->openDocument(url);
      setCaption(url.fileName(), false);
      fileOpenRecent->addURL( url );
      // flag
			if (count>0)
				viewplugins->setModified(true);
		  fileSaveAsHosts->setEnabled(true);
    }
  }
  slotStatusMsg(i18n("Ready."));
}




void KDoorsApp::slotFileNew()
{
  slotStatusMsg(i18n("Creating new document..."));


  if(!viewhost->saveModified())
  {
     // here saving wasn't successful

  }
  else
  {	
//    doc->newDocument();		
    setCaption(viewhost->URL().fileName(), false);
  }

  slotStatusMsg(i18n("Ready."));
}



void KDoorsApp::slotFileOpenRecent(const KURL& url)
{
  slotStatusMsg(i18n("Opening file..."));
	
  if(!viewhost->saveModified())
  {
     // here saving wasn't successful
  }
  else
  {
    viewhost->openDocument(url);
    setCaption(url.fileName(), false);
  }

  slotStatusMsg(i18n("Ready."));
}

void KDoorsApp::slotSaveHosts()
{
  slotStatusMsg(i18n("Saving file..."));
	
	if( !viewhost->URL().isEmpty()) {
	  viewhost->saveDocument(viewhost->URL());
	  fileSaveHosts->setEnabled(false);
	  slotStatusMsg(i18n("Ready."));
	} else {
   	slotSaveAsHosts();
	}


}

void KDoorsApp::slotSavePlugins()
{
  slotStatusMsg(i18n("Saving file..."));
	
	if( !viewplugins->URL().isEmpty()) {
	  viewplugins->saveDocument(viewplugins->URL());
	  fileSavePlugins->setEnabled(false);
	  slotStatusMsg(i18n("Ready."));
	} else {
	  slotSaveAsPlugins();
	}
}

void KDoorsApp::slotSaveAsPlugins()
{
  slotStatusMsg(i18n("Saving file with a new filename..."));

  KURL url=KFileDialog::getSaveURL(QDir::currentDirPath(),
        i18n("*|All files"), this, i18n("Save as..."));
  if(!url.isEmpty())
  {
    viewplugins->saveDocument(url);
    fileOpenRecent->addURL(url);
    setCaption(url.fileName(),viewplugins->isModified());
	  fileSavePlugins->setEnabled(false);
	  fileSaveAsPlugins->setEnabled(false);
  }
  slotStatusMsg(i18n("Ready."));
}


void KDoorsApp::slotSaveAsHosts()
{
  slotStatusMsg(i18n("Saving file with a new filename..."));

  KURL url=KFileDialog::getSaveURL(QDir::currentDirPath(),
        i18n("*|All files"), this, i18n("Save as..."));
  if(!url.isEmpty())
  {
    viewhost->saveDocument(url);
    fileOpenRecent->addURL(url);
    setCaption(url.fileName(),viewhost->isModified());
	  fileSaveHosts->setEnabled(false);
	  fileSaveAsHosts->setEnabled(false);
  }
  slotStatusMsg(i18n("Ready."));
}


void KDoorsApp::slotEndExecute(KProcess* AProcess,const QDomElement& element)
{
	//ajout l'item
// 	KDPluginsListBoxItem* item = new KDPluginsListBoxItem(element);
//	PluginsListBox->insertItem(item);
//	delete AProcess;
//		plugins_running = false;
	KDHostItem* host;
	QString text;
	QString toto;


	host = ((KPlugins*)AProcess)->host();
	viewresult->insertLine("resultat : "+host->text(1)+" "+element.attribute("Resultat"));
	text = host->element().nodeValue();
	toto = element.nodeValue();
	host->element().setAttribute("Resultat",element.attribute("Resultat"));

	host->element().appendChild(element);
	process_count--;
	delete AProcess;

}

void KDoorsApp::slotScanHosts()
{
	QDomElement element;
  KPlugins*		plugins;
  slotStatusMsg(i18n("Scan"));

 	QListViewItemIterator it( viewhost );
//	KResolveName* resolvename;

	int count = viewhost->childCount();
	ProgressBar->setValue(1);
	ProgressBar->setRange(1,count);
	process_count = 0;
 	while (it.current()) {
		slotStatusMsg("Résolution de : "+it.current()->text(1));
		kapp->processEvents();
		for (int index=0;index<viewplugins->count();index++) {
		  element = viewplugins->GetElement(index);	 	
			process_count++;
			plugins = new KPlugins();
			// sera supprimer par l'evenement suivant	receivedStdout	
			connect (plugins,SIGNAL(ReturnInfo (KProcess*,const QDomElement&)),SLOT(slotEndExecute (KProcess*,const QDomElement&)));
			plugins->ExecutePlugins((KDHostItem*)it.current(),element);
			while (process_count>4) {
				kapp->processEvents();
			}
		}
		ProgressBar->advance(1);
		it++;
	}
	slotStatusMsg("terminer");
}


void KDoorsApp::slotFileClose()
{
  slotStatusMsg(i18n("Closing file..."));
	
  close();

  slotStatusMsg(i18n("Ready."));
}


void KDoorsApp::slotFileQuit()
{
  slotStatusMsg(i18n("Exiting..."));
  saveOptions();
  // close the first window, the list makes the next one the first again.
  // This ensures that queryClose() is called on each window to ask for closing
  KMainWindow* w;
  if(memberList)
  {
    for(w=memberList->first(); w!=0; w=memberList->first())
    {
      // only close the window if the closeEvent is accepted. If the user presses Cancel on the saveModified() dialog,
      // the window and the application stay open.
      if(!w->close())
	break;
    }
  }	
  slotStatusMsg(i18n("Ready."));
}

void KDoorsApp::slotEditCut()
{
  slotStatusMsg(i18n("Cutting selection..."));

  slotStatusMsg(i18n("Ready."));
}

void KDoorsApp::slotEditCopy()
{
  slotStatusMsg(i18n("Copying selection to clipboard..."));

  slotStatusMsg(i18n("Ready."));
}

void KDoorsApp::slotEditPaste()
{
  slotStatusMsg(i18n("Inserting clipboard contents..."));

  slotStatusMsg(i18n("Ready."));
}

void KDoorsApp::slotViewToolBar()
{
  slotStatusMsg(i18n("Toggling toolbar..."));
  ///////////////////////////////////////////////////////////////////
  // turn Toolbar on or off
  if(!viewToolBar->isChecked())
  {
    toolBar("mainToolBar")->hide();
  }
  else
  {
    toolBar("mainToolBar")->show();
  }		

  slotStatusMsg(i18n("Ready."));
}

void KDoorsApp::slotViewStatusBar()
{
  slotStatusMsg(i18n("Toggle the statusbar..."));
  ///////////////////////////////////////////////////////////////////
  //turn Statusbar on or off
  if(!viewStatusBar->isChecked())
  {
    statusBar()->hide();
  }
  else
  {
    statusBar()->show();
  }

  slotStatusMsg(i18n("Ready."));
}


void KDoorsApp::slotStatusMsg(const QString &text)
{
  ///////////////////////////////////////////////////////////////////
  // change status message permanently
  statusBar()->clear();
  statusBar()->changeItem(text, ID_STATUS_MSG);
}


void KDoorsApp::slotResolveName()
{
 	QListViewItemIterator it( viewhost );
	KResolveName* resolvename;

	int count = viewhost->childCount();
	ProgressBar->setValue(1);
	ProgressBar->setRange(1,count);
 	while (it.current()) {
		slotStatusMsg("Résolution de : "+it.current()->text(1));
    resolvename = new KResolveName(dynamic_cast<KDHostItem*>(it.current()));
		resolvename->run();
		kapp->processEvents();
		ProgressBar->advance(1);
		it++;
	}
	if (count != viewhost->childCount())
		viewhost->setModified(true);
	slotStatusMsg("terminer");
}

void KDoorsApp::slotPing()
{
 	QListViewItemIterator it( viewhost );
	KDPing *ping;
	
	countping =0;
	ProgressBar->setValue(1);
	ProgressBar->setRange(1,viewhost->childCount());
 	while (it.current()) {
		slotStatusMsg("Ping de : "+it.current()->text(1));
    ping = new KDPing(dynamic_cast<KDHostItem*>(it.current()));
	  connect( ping, SIGNAL(processExited(KProcess*)),this,SLOT(slotPingExit(KProcess*) ) );
		countping++;
		if (!ping->start(KProcess::NotifyOnExit,KProcess::Stdout)) {
			it.current()->setText(3,"error");
		}
		while (countping>20) {
			kapp->processEvents();
		}
		it++;
	}
}

void KDoorsApp::slotAddPlugins()
{
	
	int accept;
  KDfrmListPlugins* 	frmlistplugins =  new KDfrmListPlugins();
  KDfrmParamPlugins*	frmparamplugins;
	QDomElement element;

	accept = frmlistplugins->exec();
	if ( accept == QDialog::Accepted && frmlistplugins->IsSelected()) {
	    element = frmlistplugins->GetSelectedElement();
			if (!element.attribute("Options").isEmpty()) {

		 		// parametrage du plugins	
//				frmparamplugins->setsPlugins(memsPlugins);
				frmparamplugins = new KDfrmParamPlugins(element);
				accept = frmparamplugins->exec();
				if ( accept == QDialog::Accepted) {
				 	KDPluginsListBoxItem* item = new KDPluginsListBoxItem(frmparamplugins->element());
					viewplugins->insertItem(item);

	 			}
				delete frmparamplugins;
			}
		}
	delete frmlistplugins;
}


void KDoorsApp::slotPingExit(KProcess* AProcess)
{
	delete AProcess;	
	countping--;
	ProgressBar->advance(1);
 	if (countping==0) {
		slotStatusMsg("terminer");
	}
}


void KDoorsApp::slotClearNoDomain()
{
 	QListViewItemIterator it( viewhost );
  QString string;

 	while (it.current()) {
		string = it.current()->text(2);
		
		if (string.isEmpty()) {
			viewhost->DeleteHost((KDHostItem*)it.current());
		  fileSaveHosts->setEnabled(true);
		  fileSaveAsHosts->setEnabled(true);
		} else {
			it++;
		}
	}
	slotStatusMsg("terminer");
}

void KDoorsApp::slotClearNoUp()
{
 	QListViewItemIterator it( viewhost );
  QString string;

 	while (it.current()) {
		string = it.current()->text(0);
		
		if (!string.isEmpty() && string=="Down") {
			viewhost->DeleteHost((KDHostItem*)it.current());
		  fileSaveHosts->setEnabled(true);
		  fileSaveAsHosts->setEnabled(true);
		} else {
			it++;
		}
	}
	slotStatusMsg("terminer");
}



void KDoorsApp::slotaddIpRange()
{
  slotStatusMsg(i18n("Before Add..."));
  frmIpRange frmiprange;
	int accept = frmiprange.exec();
	if ( accept == QDialog::Accepted) {
		if (frmiprange.ckbxIpRange->isChecked()) {
		  int ip1,ip2,ip3,ip4;
			int startip1,startip2,startip3,startip4;
			int endip1,endip2,endip3,endip4;
			// initalise les startip
			startip1 = frmiprange.edtStartIp1->text().toInt();
			startip2 = frmiprange.edtStartIp2->text().toInt();
			startip3 = frmiprange.edtStartIp3->text().toInt();
			startip4 = frmiprange.edtStartIp4->text().toInt();
			// initalise les endip
			endip1 = frmiprange.edtEndIp1->text().toInt();
			endip2 = frmiprange.edtEndIp2->text().toInt();
			endip3 = frmiprange.edtEndIp3->text().toInt();
			endip4 = frmiprange.edtEndIp4->text().toInt();

			//ajoute les ranges dans la vues
			for (ip1=startip1;ip1<=endip1;ip1++) {
				for (ip2=startip2;ip2<=endip2;ip2++) {
	  			for (ip3=startip3;ip3<=endip3;ip3++) {
		  			for (ip4=startip4;ip4<=endip4;ip4++) {
							//new KDHostItem( viewhost, QString(""),frmiprange.getStringIp(ip1,ip2,ip3,ip4),QString(""));
							viewhost->AddHost(QString(""),frmiprange.getStringIp(ip1,ip2,ip3,ip4),QString(""));
						}
					}
				}
			}
		} else {
			QString ip;
//			new KDHostItem( viewhost, QString(""),frmiprange.startip(),QString(""));
							viewhost->AddHost(QString(""),frmiprange.startip(),QString(""));

		}
	  fileSaveHosts->setEnabled(true);
	  fileSaveAsHosts->setEnabled(true);
	}
}

