/***************************************************************************
                          kdfrmparamplugins.h  -  description
                             -------------------
    begin                : Sat Feb 10 2001
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

#ifndef KDFRMPARAMPLUGINS_H
#define KDFRMPARAMPLUGINS_H

#include <frmparamplugins.h>
#include <kplugins.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qdom.h>
/**
  *@author Bruno Adele
  */

class KDfrmParamPlugins : public frmparamplugins  {
	
	Q_OBJECT

private:
	QDomElement m_element;
	void CreateControls();
	int m_posy;
protected slots:
		virtual void accept();
		void CreateParam(QString& AParam)	;
	
public:
  KDfrmParamPlugins( QDomElement& Aelement);
	~KDfrmParamPlugins();
	
	QDomElement& element() { return m_element;}
};

#endif
