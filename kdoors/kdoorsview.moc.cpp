/****************************************************************************
** KDoorsView meta object code from reading C++ file 'kdoorsview.h'
**
** Created: Sun Feb 25 18:48:29 2001
**      by: The Qt MOC ($Id: kdoorsview.moc.cpp,v 1.1.1.1 2001/05/03 20:37:42 b_adele Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "kdoorsview.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *KDoorsView::className() const
{
    return "KDoorsView";
}

QMetaObject *KDoorsView::metaObj = 0;

void KDoorsView::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(KDHostView::className(), "KDHostView") != 0 )
	badSuperclassWarning("KDoorsView","KDHostView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString KDoorsView::tr(const char* s)
{
    return qApp->translate( "KDoorsView", s, 0 );
}

QString KDoorsView::tr(const char* s, const char * c)
{
    return qApp->translate( "KDoorsView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* KDoorsView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) KDHostView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"KDoorsView", "KDHostView",
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
