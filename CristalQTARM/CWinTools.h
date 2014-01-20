#ifndef CWIN_TOOLS
#define CWIN_TOOLS

#include "header.h"
#include "header_qt.h"

class CSupervision;
class CWinMenuTests;

class CWinTools: public QDialog
{
	Q_OBJECT

public:
	CWinTools(CSupervision* argoSupervision, QWidget *parent = 0, Qt::WFlags flags = 0);
	~CWinTools();
	
public slots:


private :
	
	void setConnections();



private:

	//Pr�sentation
	QGroupBox *mainGroupBox;
	QVBoxLayout *mainLayout;
	//
	QPushButton *btTest;
	QPushButton *btMaintenance;
	QPushButton *btConfig;
	QPushButton *btDateHeure;
	QPushButton *btSave;
	QPushButton *btHelp;
	QPushButton *btInfo;
	QPushButton *btSequenceur;
	QPushButton *btLog;
	QPushButton *btCodes;
	QPushButton *btClose;


	//Obj m�tier
	CSupervision* m_pSupervision;
	

	//Autre fen�tres
	CWinMenuTests* m_oWinMenuTests;
};

#endif // CWINDOW_TOOLS