#ifndef CDIALOG_VAL_ETALON
#define CDIALOG_VAL_ETALON

#include <QDialog>
#include <QString>
class CDialogPaveNum;
class QTabWidget;
class QPushButton;
class QLabel;
class CDialogValEtalon: public QDialog
{
		Q_OBJECT

public:
	static CDialogValEtalon* getInstance();
	void setTittle(const QString& sTitre);
	void setLine(const QString& sLblTittle, const QString& sValue);
	void setLine(int nbMesure, const QString& sLblTittle, const QString& sValue);
	void setLine2(const QString& sLblTittle, const QString& sValue);
	void setLine3(const QString& sLblTittle, const QString& sValue);
	void setLine4(const QString& sLblTittle, const QString& sValue);
	void init();
	QString getReturnValue(); 
	QString getReturnValue(int); 
	QString getReturnValue2(); 
	QString getReturnValue3(); 
	QString getReturnValue4(); 

public slots:
	void btValuePressed();
	void valueChanged();
    void btValuePressed2();
	void valueChanged2();
	void btValuePressed3();
	void valueChanged3();
	void btValuePressed4();
	void valueChanged4();
private:
	CDialogValEtalon(void);
	void setConnexion();
private:

	static CDialogValEtalon* singleton;
	CDialogPaveNum* m_pPaveNum;
	QString m_sDialogTittle;
	QString m_sTittle;
	QString m_sValue;
	QTabWidget* m_tabWidget;
	QPushButton* m_btValue;
	QPushButton* m_btValue2;
	QPushButton* m_btValue3;
	QPushButton* m_btValue4;
	QLabel* m_lblValue;
	QLabel* m_lblValue2;
	QLabel* m_lblValue3;
	QLabel* m_lblValue4;
	//QVBoxLayout* m_layoutMenu;
	QPushButton* m_btBack;
	QPushButton* m_btApply;
};

#endif
