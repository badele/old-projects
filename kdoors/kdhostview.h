/***************************************************************************
                          kdhostview.h  -  description
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

#ifndef KDHOSTVIEW_H
#define KDHOSTVIEW_H

#include <kurl.h>

#include <klistview.h>
#include "kdhostitem.h"
#include "kdoors.h"
#include <qdom.h>

/**
  *@author Bruno Adele
  */

class KDHostItem;

class KDHostView : public KListView  {
public: 
	KDHostView(QWidget *parent=0, const char *name=0);
	~KDHostView();

  /** Efface un hote et son element XML corespondant */
	void DeleteHost(KDHostItem* AHostItem);
  /** Ajout un hote son element XML corespondant */
	void AddHost(QString AStatus,QString AIp,QString AAddress);
  /** Ouvre un fichier d'hotes */
  bool openDocument(const KURL& url, const char *format=0);
  /** Sauvegarde un fichier d'hotes */
  bool saveDocument(const KURL& url, const char *format=0);
  /** Demande si l'on desire sauvegarder le document modifier, par lors de la fermeture de l'applicatin */
  bool saveModified();	
  /** Retourne vrai si le document à été modifié */
	bool isModified(){ return m_modified; };
  /** Permet de modifier le status de l'état du document */
  void setModified(bool value=true){ m_modified=value; };
  /** Contient l'URL du document */
  KURL& URL() { return m_url;}



private:
  /** Contient l'etat sur le document */
	bool m_modified;
  /** Contient l'URL*/
  KURL m_url;
  /** Contient le document XML */
	QDomDocument doc;
  /** Contient la liste des hotes sous forme XML*/
	QDomElement hosts_list;
};

#endif
