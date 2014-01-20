#ifndef CDIALOG_HISTO
#define CDIALOG_HISTO

#include "header.h"
#include <QDialog>

class CSupervision;
class QPushButton;
class CHistoSortedView;
class QStringListModel;

class CDialogHistorique: public QDialog
{
	Q_OBJECT
public:
	static CDialogHistorique* getInstance();
	
    void setEnabledBtNext(const bool& arg_state);
    void setEnabledBtPrev(const bool& arg_state);

	void addMesure(int arg_iStream, CStream* arg_pStream);

public slots:
	
//	void acquiter();

private:
	CDialogHistorique();
	static CDialogHistorique* singleton;
	
	QPushButton* m_btBack;
	/*QPushButton* m_btApply;*/
	QPushButton* m_btNext;
	QPushButton* m_btPrev;
	
	QStringListModel *m_listModel;
    CHistoSortedView* m_listView;
};
#endif //CDIALOG_HISTO
