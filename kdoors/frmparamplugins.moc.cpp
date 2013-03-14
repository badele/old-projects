/****************************************************************************
** frmparamplugins meta object code from reading C++ file 'frmparamplugins.h'
**
** Created: Sat Feb 10 21:25:50 2001
**      by: The Qt MOC ($Id: frmparamplugins.moc.cpp,v 1.1.1.1 2001/05/03 20:37:48 b_adele Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_frmparamplugins
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "frmparamplugins.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *frmparamplugins::className() const
{
    return "frmparamplugins";
}

QMetaObject *frmparamplugins::metaObj = 0;

void frmparamplugins::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
	badSuperclassWarning("frmparamplugins","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString frmparamplugins::tr(const char* s)
{
    return qApp->translate( "frmparamplugins", s, 0 );
}

QString frmparamplugins::tr(const char* s, const char * c)
{
    return qApp->translate( "frmparamplugins", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* frmparamplugins::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"frmparamplugins", "QDialog",
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}
