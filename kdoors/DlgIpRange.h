/****************************************************************************
** Form interface generated from reading ui file './DlgIpRange.ui'
**
** Created: Sat Dec 30 20:52:52 2000
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMIPRANGE_H
#define FRMIPRANGE_H


#include <qvariant.h>
#include <qdialog.h>
#include <qstring.h>

class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class KLineEdit;
class QCheckBox;
class QLineEdit;
class QPushButton;

class frmIpRange : public QDialog
{ 
    Q_OBJECT

public:
    frmIpRange( QWidget* parent = 0, const char* name = 0, bool modal = false, WFlags fl = 0 );
    ~frmIpRange();

    KLineEdit* edtEndIp1;
    KLineEdit* edtEndIp2;
    KLineEdit* edtEndIp3;
    KLineEdit* edtEndIp4;
    QCheckBox* ckbxIpRange;
    QPushButton* btnOk;
    QPushButton* btnCancel;
    KLineEdit* edtStartIp3;
    KLineEdit* edtStartIp4;
    KLineEdit* edtStartIp2;
    KLineEdit* edtStartIp1;

		QString getStringIp(const QString& AIp1,const QString& AIp2,const QString& AIp3,const QString& AIp4);
		QString getStringIp(int AIp1,int AIp2,int AIp3,int AIp4);
		QString startip();
		QString endip();

protected slots:
		virtual void accept();

public slots:
    virtual void slot_edttab1(const QString& AString);
    virtual void slot_edttab2(const QString& AString);
    virtual void slot_edttab3(const QString& AString);
    virtual void slot_ckbxclick();

};

#endif // FRMIPRANGE_H
