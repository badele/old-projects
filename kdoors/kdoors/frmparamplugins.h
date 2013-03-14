/****************************************************************************
** Form interface generated from reading ui file './frmparamplugins.ui'
**
** Created: Mon May 7 20:29:39 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FRMPARAMPLUGINS_H
#define FRMPARAMPLUGINS_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QLabel;
class QLineEdit;
class QPushButton;

class frmparamplugins : public QDialog
{ 
    Q_OBJECT

public:
    frmparamplugins( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~frmparamplugins();

    QLabel* lblTitre;
    QLineEdit* edtTitre;
    QPushButton* btnOk;

};

#endif // FRMPARAMPLUGINS_H
