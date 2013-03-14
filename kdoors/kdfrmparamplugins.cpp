/***************************************************************************
                          kdfrmparamplugins.cpp  -  description
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

#include <qstringlist.h>
#include <qlabel.h>
#include <qapplication.h>
#include <qwidgetlist.h>
#include <qobjectlist.h>

#include "kdfrmparamplugins.h"

KDfrmParamPlugins::KDfrmParamPlugins(QDomElement& Aelement)
    : frmparamplugins( 0, 0, true, 0 )
{
	m_element = Aelement;
	connect( btnOk, SIGNAL( clicked()),this, SLOT( accept() ) );


	m_posy = 40;
	CreateControls();			
}

KDfrmParamPlugins::~KDfrmParamPlugins()
{
}




void KDfrmParamPlugins::CreateParam(QString& AParam)
{

	QString			param;
	QString			value;
	int					start;
	QLineEdit* 	edit;
	QLabel*			label;

	// parametre
	start = AParam.find("=");
	param = AParam.mid(0,start);
 	param = param.stripWhiteSpace();

	value = AParam.mid(start+1);
 	value = value.stripWhiteSpace();

  edit = new QLineEdit( this,param);
  edit->setGeometry( QRect( 80, m_posy, 110, 22 ) );
	edit->setText(value);

	label = new QLabel( this, param);
  label->setGeometry( QRect( 10, m_posy, 61, 22 ) );
	label->setText(param.replace(QRegExp("_"), " "));

	m_posy+= 30;
}

void KDfrmParamPlugins::CreateControls()
{
	QStringList listoption = QStringList::split(",",m_element.attribute("Options"));
	QString option;

  // affiche le titre
	edtTitre->setText(m_element.attribute("Title"));

	// lits les options
	if (!listoption.isEmpty()) {
		QStringList::Iterator it(listoption.begin());
   	for (; it != listoption.end(); ++it) {
	   	option = (*it);
			CreateParam(option);
		}
  }

  btnOk->setGeometry( QRect( 150, m_posy, 40, 32 ) );
	resize( 197, m_posy+40 );

}

void KDfrmParamPlugins::accept()
{
		// le titre
    m_element.setAttribute("Title",edtTitre->text());


		QObjectList * objlist = topLevelWidget()->queryList( "QLineEdit" );
    QObjectListIt it( *objlist );             // iterate over the buttons
    QLineEdit * edt;
    while ( (edt=(QLineEdit*)it.current()) != 0 ) { // for each found object...
				if (edt->name()!="edtTitre") {
	        m_element.setAttribute(edt->name(),edt->text());
				}
        ++it;
    }
    delete objlist;

	QDialog::accept();	
}
