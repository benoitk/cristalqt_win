#include "CDialogValEtalon.h"
#include "CDialogPaveNum.h"

#include "header_qt.h"
CDialogValEtalon* CDialogValEtalon::singleton = 0;
CDialogValEtalon::CDialogValEtalon(void): QDialog()
{
	//menu de droite //toujours 4 items dans les menus en incluant les spacers
	m_btApply = new QPushButton();
	m_btApply->setObjectName("btApply");
	m_btBack = new QPushButton();
	m_btBack->setObjectName("btCancel");

	QVBoxLayout* layoutMenu = new QVBoxLayout();
	layoutMenu->addStretch();
	layoutMenu->addWidget(m_btApply);
	layoutMenu->addWidget(m_btBack);
	m_sTittle = "init";
	m_sValue = "init";
	m_sDialogTittle = "init";
	
	m_tabWidget = new QTabWidget();

	QWidget* widgetDialog = new QWidget();
	m_tabWidget->addTab(widgetDialog, "toto");

	m_btValue = new QPushButton();
	m_lblValue = new QLabel("**********");
    m_btValue2 = new QPushButton();
	m_lblValue2 = new QLabel("**********");
	m_btValue3 = new QPushButton();
	m_lblValue3 = new QLabel("**********");
	m_btValue4 = new QPushButton();
	m_lblValue4 = new QLabel("**********");
	m_btValue->setObjectName("btLineEdit");
	m_btValue2->setObjectName("btLineEdit");
	m_btValue3->setObjectName("btLineEdit");
	m_btValue4->setObjectName("btLineEdit");
	QFormLayout* formLayout = new QFormLayout();
	formLayout->addRow(m_lblValue, m_btValue);
	formLayout->addRow(m_lblValue2, m_btValue2);
	formLayout->addRow(m_lblValue3, m_btValue3);
	formLayout->addRow(m_lblValue4, m_btValue4);
	

	//assemblage du menu et du layoutGauche
	QHBoxLayout* layoutMain = new QHBoxLayout();
	layoutMain->addLayout(formLayout);
	layoutMain->addLayout(layoutMenu);
	widgetDialog->setLayout(layoutMain);
	
	
	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(m_tabWidget);

	setLayout(layout);
	this->setObjectName("dialogModal");
	this->setWindowFlags(Qt::FramelessWindowHint);

	setConnexion();
}

void CDialogValEtalon::setTittle(const QString& sTittle)
{
	 m_tabWidget->setTabText(0, sTittle);
}
void CDialogValEtalon::setLine(const QString& sLblTittle, const QString& sValue)
{
	m_lblValue->setText(sLblTittle);
	m_btValue->setText(sValue);
    m_btValue2->setVisible(false);
    m_lblValue2->setVisible(false);
	m_btValue3->setVisible(false);
    m_lblValue3->setVisible(false);
	m_btValue4->setVisible(false);
    m_lblValue4->setVisible(false);
	this->updateGeometry();
}
void CDialogValEtalon::setLine(int nbMesure, const QString& sLblTittle, const QString& sValue)
{
	switch(nbMesure){
case 0:
	setLine(sLblTittle, sValue);
	break;
case 1:
	setLine2(sLblTittle, sValue);
	break;
case 2:
	setLine3(sLblTittle, sValue);
	break;
case 3:
	setLine4(sLblTittle, sValue);
	break;
	}
}
void CDialogValEtalon::setLine2(const QString& sLblTittle, const QString& sValue)
{

	m_lblValue2->setText(sLblTittle);
	m_btValue2->setText(sValue);
    m_lblValue2->setVisible(true);
    m_btValue2->setVisible(true);
	m_btValue3->setVisible(false);
    m_lblValue3->setVisible(false);
	m_btValue4->setVisible(false);
    m_lblValue4->setVisible(false);
	this->updateGeometry();
}
void CDialogValEtalon::setLine3(const QString& sLblTittle, const QString& sValue)
{

	m_lblValue3->setText(sLblTittle);
	m_btValue3->setText(sValue);
    m_lblValue3->setVisible(true);
    m_btValue3->setVisible(true);
	m_btValue3->setVisible(true);
    m_lblValue3->setVisible(true);
	m_btValue4->setVisible(false);
    m_lblValue4->setVisible(false);
	this->updateGeometry();
}
void CDialogValEtalon::setLine4(const QString& sLblTittle, const QString& sValue)
{

	m_lblValue4->setText(sLblTittle);
	m_btValue4->setText(sValue);
    m_lblValue4->setVisible(true);
    m_btValue4->setVisible(true);
	m_btValue3->setVisible(true);
    m_lblValue3->setVisible(true);
	m_btValue4->setVisible(true);
    m_lblValue4->setVisible(true);
	this->updateGeometry();
}
	
QString CDialogValEtalon::getReturnValue()
{
	return m_btValue->text();
}
QString CDialogValEtalon::getReturnValue(int numValue)
{
	QPushButton* bt;
	switch(numValue){
		case 0:
			bt = m_btValue;
			break;
		case 1:
			bt = m_btValue2;
			break;
		case 2:
			bt = m_btValue3;
			break;
		case 3:
			bt = m_btValue4;
			break;
	}
	return bt->text();
}

QString CDialogValEtalon::getReturnValue2()
{
	return m_btValue2->text();
}
QString CDialogValEtalon::getReturnValue3()
{
	return m_btValue3->text();
}
QString CDialogValEtalon::getReturnValue4()
{
	return m_btValue4->text();
}

void CDialogValEtalon::init()
{

}

CDialogValEtalon* CDialogValEtalon::getInstance()
{
	if(!singleton)
		singleton = new CDialogValEtalon();
	disconnect(singleton, 0, 0, 0); //Déconnect tout les objet qui se sont connecté à ses signaux
	return singleton;
}
//SLOT
void CDialogValEtalon::btValuePressed()
{
	m_pPaveNum = CDialogPaveNum::getInstance();
	connect(m_pPaveNum, SIGNAL(accepted()), this, SLOT(valueChanged()));
	//connect(m_pPaveNum, SIGNAL(rejected()), this, SLOT(valueUnChanged()));
	m_pPaveNum->setValueName(m_lblValue->text());
	m_pPaveNum->setValue(m_btValue->text());
	m_pPaveNum->exec();
}
//SLOT
void CDialogValEtalon::valueChanged()
{
	m_btValue->setText(m_pPaveNum->getValue());
	this->updateGeometry();
}
void CDialogValEtalon::btValuePressed2()
{
	m_pPaveNum = CDialogPaveNum::getInstance();
	connect(m_pPaveNum, SIGNAL(accepted()), this, SLOT(valueChanged2()));
	//connect(m_pPaveNum, SIGNAL(rejected()), this, SLOT(valueUnChanged()));
	m_pPaveNum->setValueName(m_lblValue2->text());
	m_pPaveNum->setValue(m_btValue2->text());
	m_pPaveNum->exec();
}
//SLOT
void CDialogValEtalon::valueChanged2()
{
	m_btValue2->setText(m_pPaveNum->getValue());
	this->updateGeometry();
}
void CDialogValEtalon::btValuePressed3()
{
	m_pPaveNum = CDialogPaveNum::getInstance();
	connect(m_pPaveNum, SIGNAL(accepted()), this, SLOT(valueChanged3()));
	//connect(m_pPaveNum, SIGNAL(rejected()), this, SLOT(valueUnChanged()));
	m_pPaveNum->setValueName(m_lblValue3->text());
	m_pPaveNum->setValue(m_btValue3->text());
	m_pPaveNum->exec();
}
//SLOT
void CDialogValEtalon::valueChanged3()
{
	m_btValue3->setText(m_pPaveNum->getValue());
	this->updateGeometry();
}
void CDialogValEtalon::btValuePressed4()
{
	m_pPaveNum = CDialogPaveNum::getInstance();
	connect(m_pPaveNum, SIGNAL(accepted()), this, SLOT(valueChanged4()));
	//connect(m_pPaveNum, SIGNAL(rejected()), this, SLOT(valueUnChanged()));
	m_pPaveNum->setValueName(m_lblValue4->text());
	m_pPaveNum->setValue(m_btValue4->text());
	m_pPaveNum->exec();
}
//SLOT
void CDialogValEtalon::valueChanged4()
{
	m_btValue4->setText(m_pPaveNum->getValue());
	this->updateGeometry();
}
void CDialogValEtalon::setConnexion()
{
	connect(m_btBack, SIGNAL(clicked()), this, SLOT(reject()));
	connect(m_btApply, SIGNAL(clicked()), this, SLOT(accept()));
	connect(m_btValue, SIGNAL(clicked()), this, SLOT(btValuePressed()));
	connect(m_btValue2, SIGNAL(clicked()), this, SLOT(btValuePressed2()));
	connect(m_btValue3, SIGNAL(clicked()), this, SLOT(btValuePressed3()));
	connect(m_btValue4, SIGNAL(clicked()), this, SLOT(btValuePressed4()));
}