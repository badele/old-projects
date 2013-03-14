#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './DlgIpRange.ui'
**
** Created: Sat Dec 30 20:52:53 2000
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "DlgIpRange.h"

#include <klineedit.h>
#include <klocale.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a frmIpRange which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
frmIpRange::frmIpRange( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, true, fl )
{
    if ( !name )
			setName( "frmIpRange" );

		resize( 211, 126 );
    setCaption( i18n( "IpRange" ) );

    edtEndIp1 = new KLineEdit( this, "edtEndIp1" );
    edtEndIp1->setGeometry( QRect( 10, 60, 40, 22 ) );

    edtEndIp2 = new KLineEdit( this, "edtEndIp1_2" );
    edtEndIp2->setGeometry( QRect( 60, 60, 40, 22 ) );

    edtEndIp3 = new KLineEdit( this, "edtEndIp1_3" );
    edtEndIp3->setGeometry( QRect( 110, 60, 40, 22 ) );

    edtEndIp4 = new KLineEdit( this, "edtEndIp1_4" );
    edtEndIp4->setGeometry( QRect( 160, 60, 40, 22 ) );
    edtEndIp4->setText( "255" );

    ckbxIpRange = new QCheckBox( this, "ckbxIpRange" );
    ckbxIpRange->setGeometry( QRect( 10, 37, 130, 20 ) ); 
    ckbxIpRange->setText( i18n( "Ajouter un range" ) );

    btnOk = new QPushButton( this, "btnOk" );
    btnOk->setGeometry( QRect( 158, 90, 50, 32 ) ); 
    btnOk->setText( i18n( "Ok" ) );

    btnCancel = new QPushButton( this, "btnCancel" );
    btnCancel->setGeometry( QRect( 10, 90, 90, 32 ) );
    btnCancel->setText( i18n( "Annuler" ) );

    edtStartIp3 = new KLineEdit( this, "edtStartIp3" );
    edtStartIp3->setGeometry( QRect( 110, 10, 40, 22 ) ); 

    edtStartIp4 = new KLineEdit( this, "edtStartIp4" );
    edtStartIp4->setGeometry( QRect( 160, 10, 40, 22 ) ); 

    edtStartIp2 = new KLineEdit( this, "edtStartIp2" );
    edtStartIp2->setGeometry( QRect( 60, 10, 40, 22 ) ); 

    edtStartIp1 = new KLineEdit( this, "edtStartIp1" );
    edtStartIp1->setGeometry( QRect( 10, 10, 40, 22 ) ); 

    // signals and slots connections
		connect( btnOk, SIGNAL( clicked()), SLOT( accept() ) );
		connect( btnCancel, SIGNAL( clicked()), SLOT( reject() ) );
		// edit
    connect( edtStartIp1, SIGNAL( textChanged(const QString&) ), this, SLOT( slot_edttab1(const QString&) ) );
    connect( edtStartIp2, SIGNAL( textChanged(const QString&) ), this, SLOT( slot_edttab2(const QString&) ) );
    connect( edtStartIp3, SIGNAL( textChanged(const QString&) ), this, SLOT( slot_edttab3(const QString&) ) );
		//check
		connect( ckbxIpRange, SIGNAL( clicked()), this, SLOT( slot_ckbxclick() ) );

    // tab order
    setTabOrder( edtStartIp1, edtStartIp2 );
    setTabOrder( edtStartIp2, edtStartIp3 );
    setTabOrder( edtStartIp3, edtStartIp4 );
    setTabOrder( edtStartIp4, ckbxIpRange );
    setTabOrder( ckbxIpRange, edtEndIp1 );
    setTabOrder( edtEndIp1, edtEndIp2 );
    setTabOrder( edtEndIp2, edtEndIp3 );
    setTabOrder( edtEndIp3, edtEndIp4 );
    setTabOrder( edtEndIp4, btnCancel );
    setTabOrder( btnCancel, btnOk );

		// desactive les composants
		slot_ckbxclick();
}

/*  
 *  Destroys the object and frees any allocated resources
 */
frmIpRange::~frmIpRange()
{
    // no need to delete child widgets, Qt does it all for us
}

void frmIpRange::slot_edttab1(const QString& AString)
{
		QString str = AString;

		if (str.find(".")>0) {
			edtStartIp2->setFocus();
		}
		str.replace(QRegExp("[^0-9]"), "");
		edtStartIp1->setText(str);
		edtEndIp1->setText(str);
}

void frmIpRange::slot_edttab2(const QString& AString)
{
		QString str = AString;

		if (str.find(".")>0) {
			edtStartIp3->setFocus();
		}
		str.replace(QRegExp("[^0-9]"), "");
		edtStartIp2->setText(str);
		edtEndIp2->setText(str);
}

void frmIpRange::slot_edttab3(const QString& AString)
{
		QString str = AString;

		if (str.find(".")>0) {
			edtStartIp4->setFocus();
		}
		str.replace(QRegExp("[^0-9]"), "");
		edtStartIp3->setText(str);
		edtEndIp3->setText(str);
}

void frmIpRange::slot_ckbxclick()
{
		bool state = ckbxIpRange->isChecked();
    edtEndIp1->setEnabled( state );
    edtEndIp2->setEnabled( state );
    edtEndIp3->setEnabled( state );
    edtEndIp4->setEnabled( state );
}

QString frmIpRange::getStringIp(const QString& AIp1,const QString& AIp2,const QString& AIp3,const QString& AIp4)
{
	QString string;


	string = AIp1+".";
	string+= AIp2+".";
	string+= AIp3+".";
	string+= AIp4;

	return string;
}

QString frmIpRange::getStringIp(int AIp1,int AIp2,int AIp3,int AIp4)
{
	QString ip1,ip2,ip3,ip4;
	return getStringIp(ip1.setNum(AIp1),ip2.setNum(AIp2),ip3.setNum(AIp3),ip4.setNum(AIp4));
	/*QString string,string1,string2,string3,string4;

	string1.sprintf("%.3d",AIp1);
	string2.sprintf("%.3d",AIp2);
	string3.sprintf("%.3d",AIp3);
	string4.sprintf("%.3d",AIp4);

	string = string1+".";
	string+= string2+".";
	string+= string3+".";
	string+= string4;

	return string;*/

}


QString frmIpRange::startip()
{
	return getStringIp(edtStartIp1->text(),edtStartIp2->text(),edtStartIp3->text(),edtStartIp4->text());
}

QString frmIpRange::endip()
{
	return getStringIp(edtEndIp1->text(),edtEndIp2->text(),edtEndIp3->text(),edtEndIp4->text());
}


void frmIpRange::accept()
{
	QDialog::accept();	
}