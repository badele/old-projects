/***************************************************************************
                          kdresultview.h  -  description
                             -------------------
    begin                : Sat Mar 17 2001
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

#ifndef KDRESULTVIEW_H
#define KDRESULTVIEW_H

#include <qwidget.h>
#include <qmultilineedit.h>

/**
  *@author Bruno Adele
  */

class KDResultView : public QMultiLineEdit  {
   Q_OBJECT
public: 
	KDResultView(QWidget *parent=0, const char *name=0);
	~KDResultView();
};

#endif
