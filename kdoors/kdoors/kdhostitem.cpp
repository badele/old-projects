/***************************************************************************
                          kdhostitem.cpp  -  description
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

// include pour le reseaux
#include <arpa/inet.h>
#include <netinet/in.h>

// include pour KDE
#include <qstring.h>

#include "kdhostitem.h"

QString fields[3] = {"Status","Ip","Address"};


KDHostItem::KDHostItem(KDHostView* AView,QDomElement& element,QString AStatus,QString AIp,QString AIpName)
: QListViewItem(AView,AStatus,AIp,AIpName)
{
	// Initalise les colonnes
	m_element = element;
	setText(0,AStatus);
	setText(1,AIp);
	setText(2,AIpName);
}


KDHostItem::~KDHostItem()
{

}

QString KDHostItem::key(int AColumn,bool ascending) const
{

	unsigned long ipaddr;
	QString tmpstring;

	// on teste si on doit trier normalement
	if (AColumn!=1) return this->text(AColumn);


	// on trie seulement les addresses en convertisant l'addresse IP sous forme numerique
	ipaddr = inet_addr(this->text(1));
	ipaddr = ntohl(ipaddr);
	tmpstring.sprintf("%.12u",ipaddr);						
	return tmpstring;
}

void KDHostItem::setText(int column, const QString &text)
{
	// lors que le contenu d'une colone change modifie le contenu XML
	QListViewItem::setText(column,text);
	if (m_element.attribute(fields[column])!=text) {
		m_element.setAttribute(fields[column],text);
	}
}


/*void KDHostItem::paintCell(QPainter* p, const QColorGroup& cg, int column, int width, int align)
{
QListViewItem::paintCell(p, cg, column, width, align);
	if(DRAWGRID)
	{
	p->setPen( cg.midlight() );
	p->moveTo(0, height()-1);
	p->lineTo(width-1, height()-1);
	p->lineTo(width-1, 0);
  }
} */

