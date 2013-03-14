/***************************************************************************
                          kresolvename.h  -  description
                             -------------------
    begin                : Sun Jan 7 2001
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

#ifndef KRESOLVENAME_H
#define KRESOLVENAME_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kprocess.h>


#include <qobject.h>
#include <qstring.h>
#include <qlistview.h>
#include <kdhostview.h>

/**
  *@author Bruno Adele
  */

//TODO Utiliser les thread (ne fonctionne pas actulement, parcour du combatant)


/** Classe permetant de resoudre un domaine */
class KResolveName : public QObject  {

  Q_OBJECT
	
public:
  /** Constructeur */
	KResolveName(KDHostItem *AItem);
	/** Destructeur */
	~KResolveName();
	/** Demarre la resolution du domaine */
	virtual void run();
private:
	/** Contient l'item à resoudre, si la resolution c'est bien passé,
      l'item sera mis à jours */
	KDHostItem*	Item;
};


/** Classe permetant d'executer des pings */
class KDPing : public KProcess  {

  Q_OBJECT

private:
	KDHostItem*	Item;

public slots:
  /** retour des resultat des pings */
	void slotStdout(KProcess* AProcess,char* ABuffer,int ALength);
	
public:
  /** Constructeur */
	KDPing(KDHostItem *AItem);
	/** Destructeur */
	~KDPing();
};




#endif
