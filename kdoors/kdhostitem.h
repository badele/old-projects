/***************************************************************************
                          kdhostitem.h  -  description
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

#ifndef KDHOSTITEM_H
#define KDHOSTITEM_H

// include pour KDE
#include <qlistview.h>
#include <qdom.h>

#include "kdhostview.h"
/**
  *@author Bruno Adele
  */

class KDHostView;

class KDHostItem : public QListViewItem
{
	private:
	QDomElement m_element;

  public:
    /** Constructeur */
		KDHostItem(KDHostView* AView,QDomElement& element,QString AStatus,QString AIp,QString AIpName);
    /** Destructeur */
    ~KDHostItem();
    /** Permet de trier la liste des hotes */
		virtual QString key(int AColumn,bool ascending) const;
    /** Permet de recuperer l'element XML affecté à l'hote */
		QDomElement& element() { return m_element; }
    /** Permet de metre à jours l'element XML, lors d'une modification d'une colonne */
		virtual void setText(int column, const QString &text);

protected:
    /** Surchage la fonction qui redessine les celulles
		virtual void paintCell(QPainter* p, const QColorGroup& cg, int column, int width, int align);*/

};


#endif
