/***************************************************************************
                          kplugins.cpp  -  description
                             -------------------
    begin                : Tue Jan 30 2001
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

#include "kplugins.h"

/*KDsPlugins::KDsPlugins(KDsPlugins* Source)
{
	this->Assign(Source);
}*/

void KDsPlugins::Assign(KDsPlugins* Source)
{
	this->Author 		= Source->Author;
	this->Email 		= Source->Email;
	this->Plugins 	= Source->Plugins;
	this->Version 	= Source->Version;
	this->Type			= Source->Type;
	this->Info 			= Source->Info;
	this->Web 			= Source->Web;
	this->Options		= Source->Options;
	this->Solution	= Source->Solution;
}


/*QString KDsPlugins::ReturnInfo(const QString& AllInfo,const QString& AKey)
{
	QString title;
	
	int start,end;

 	start = AllInfo.find("<"+AKey+":>");
 	start = AllInfo.find(">",start)+1;
 	end = AllInfo.find(QRegExp("\n"),start);

 	title = AllInfo.mid(start,end-start);
 	title = title.stripWhiteSpace();
 	
 	return title;
}



void KDsPlugins::LoadInfo(const QString& AString)
{
	Author 	= ReturnInfo(AString,"Author");
	Email 	= ReturnInfo(AString,"Email");
	Plugins = ReturnInfo(AString,"Title");
	Version = ReturnInfo(AString,"Version");
	Type		= ReturnInfo(AString,"Type");
	Info 		= ReturnInfo(AString,"Info");
	Web 		= ReturnInfo(AString,"Web");
	Options	= ReturnInfo(AString,"Options");
	Solution= ReturnInfo(AString,"Solution");
}*/

KPlugins::KPlugins() : KProcess()
{

}

KPlugins::~KPlugins()
{

}


// recupere les infos sur le plugins
void KPlugins::GetInfo(const QString& AFile)
{
	m_file = AFile;
	*this << "/home/b_adele/kdoors/scripts/"+AFile;
	*this << "getinfo";
	connect (this,SIGNAL(receivedStdout (KProcess*, char*,int)),SLOT(slotCheckBlockGetInfo (KProcess*, char*,int)));
  connect( this, SIGNAL(processExited(KProcess*)),this,SLOT(slotGetInfoExit(KProcess*) ) );
	start(KProcess::NotifyOnExit,KProcess::Stdout);
}

// recupere les infos sur le plugins
void KPlugins::ExecutePlugins(KDHostItem* viewitem,const QDomElement &AElement)
{

	QString option;
	int end;

	m_hostitem = viewitem;
	m_file = AElement.attribute("File");	
	m_title = AElement.attribute("Title");	

	*this << "/home/b_adele/kdoors/scripts/"+m_file;
	
	// passage des parametres
	QStringList listoption = QStringList::split(",",AElement.attribute("Options"));

	// lits les options
	if (!listoption.isEmpty()) {
		QStringList::Iterator it(listoption.begin());
		// adresse IP
		 *this << m_hostitem->text(1);

		// options
   	for (; it != listoption.end(); ++it) {
	   	option = (*it);
			end = option.find("=");
			option = option.mid(end+1,65535).stripWhiteSpace();
      *this << option;
		}
  }

	connect (this,SIGNAL(receivedStdout (KProcess*, char*,int)),SLOT(slotCheckBlockGetInfo (KProcess*, char*,int)));
  connect( this, SIGNAL(processExited(KProcess*)),this,SLOT(slotExecuteExit(KProcess*) ) );
	start(KProcess::NotifyOnExit,KProcess::Stdout);
}


// recupere les infos sur le plugins
/*void KPlugins::RunPlugins(QString ip,QDomElement param_element,QDomElement result_element)
{
	*this << "/home/b_adele/kdoors/scripts/"+param_element.attribute("File");
	*this << ip;
	connect (this,SIGNAL(receivedStdout (KProcess*, char*,int)),SLOT(slotCheckBlockGetInfo (KProcess*, char*,int)));
  connect( this, SIGNAL(processExited(KProcess*)),this,SLOT(slotGetInfoExit(KProcess*) ) );

	start(KProcess::NotifyOnExit,KProcess::Stdout);
} */


// slot d'un retour de block de stdout
void KPlugins::slotCheckBlockGetInfo(KProcess* AProcess, char* ABuffer,int ALength)
{

	QString string;
	string = QString(ABuffer);
	string.truncate(ALength);

	m_alloutput+=string;


}


// indique un terminaison de la fonction GetInfo
void KPlugins::slotGetInfoExit(KProcess* AProcess)
{
	// recupere les infos sous le format xml DOM1

 	QDomDocument doc("doc_plugins");
 	doc.setContent(m_alloutput);
 	QDomElement element = doc.documentElement();
	element.setAttribute("File",m_file);
	emit ReturnInfo(this,element);
}


// indique un terminaison de la fonction GetInfo
void KPlugins::slotExecuteExit(KProcess* AProcess)
{
	// recupere les infos sous le format xml DOM1

 	QDomDocument doc("doc_plugins");
 	doc.setContent(m_alloutput);
 	QDomElement element = doc.documentElement();
//	element.setAttribute("File",m_file);
	element.setAttribute("Title",m_title);
	emit ReturnInfo(this,element);
}


