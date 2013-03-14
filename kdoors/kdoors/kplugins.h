/***************************************************************************
                          kplugins.h  -  description
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

#ifndef KPLUGINS_H
#define KPLUGINS_H

#include <kprocess.h>
#include <qdom.h>

#include <qstring.h>

#include "kdhostitem.h"

/**
  *@author Bruno Adele
  */


class KDsPlugins : public QObject  {
  Q_OBJECT

private:
//	QString ReturnInfo(const QString& AllInfo,const QString& AKey);
public slots:
public:
	
//	KDsPlugins (KDsPlugins* Source);
//	void LoadInfo(const QString& AString);
	void Assign(KDsPlugins* Source);
	
	QString 	Author;
	QString 	Email;
	QString		Web;	
	QString		Plugins;
	QString		Version;
	QString		Type;
	QString		Info;
	QString		Solution;
	QString		Options;
};


class KDHostItem;

class KPlugins : public KProcess  {
  Q_OBJECT

private:
	QString 		m_alloutput;
	QString 		m_file;
	QString			m_title;
	KDHostItem*	m_hostitem;


protected slots:
	void slotCheckBlockGetInfo(KProcess* AProcess,char* ABuffer,int ALength);
	void slotGetInfoExit(KProcess* AProcess);
	void slotExecuteExit(KProcess* AProcess);

	
signals:
		void ReturnInfo(KProcess* AProcess,const QDomElement& element);
	
public:
	KPlugins();
	~KPlugins();
	void GetInfo(const QString& AFile);
	void ExecutePlugins(KDHostItem* viewitem,const QDomElement &AElement);
	KDHostItem* host() { return m_hostitem; }
	
};

#endif
