/****************************************************************************
** Form interface generated from reading ui file './DlgIpRange.ui'
**
** Created: Sat Dec 30 20:52:52 2000
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef KDFRMLISTPLUGINS_H
#define KDFRMLISTPLUGINS_H


#include <qvariant.h>
#include <qdialog.h>
#include <qstring.h>
#include <qmultilineedit.h>
#include <qlistbox.h>
#include <qdom.h>

#include "kdpluginslistbox.h"
#include "kplugins.h"

class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class KLineEdit;
class QCheckBox;
class QLineEdit;
class QPushButton;

class KDfrmListPlugins : public QDialog
{ 
    Q_OBJECT

private:
//	bool plugins_running;
	int process_count;
public:
    KDfrmListPlugins( QWidget* parent = 0, const char* name = 0, bool modal = false, WFlags fl = 0 );
    ~KDfrmListPlugins();

		QMultiLineEdit* multilineEdit;
		KDPluginsListBox* PluginsListBox;
    QPushButton* btnOk;
    QPushButton* btnCancel;
		void CheckPlugins();
		bool IsSelected();
		QDomElement& GetSelectedElement();


protected slots:
		void slotselectionChanged(QListBoxItem* AItem);
		virtual void accept();
		void slotCheckGetInfo(KProcess* AProcess,const QDomElement& element);

public slots:

};

#endif // KDFRMLISTPLUGINS_H
