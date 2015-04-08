#include "CDialogInfo.h"
#include "Network.h"
#include "header_qt.h"

#define NUM_VERSION_QT "4.0.7 build 56"


CDialogInfo* CDialogInfo::singleton = 0;
CDialogInfo::CDialogInfo()
{
	m_btBack = new QPushButton();
	m_btBack->setObjectName("btCancel");
	
	QTabWidget* tabWidget = new QTabWidget();

	QWidget* widgetDialog = new QWidget();
	tabWidget->addTab(widgetDialog, tr("INFORMATION"));
	
	QVBoxLayout* layoutMenu = new QVBoxLayout();
	layoutMenu->addStretch();
	layoutMenu->addWidget(m_btBack);
   
    QString sTypeAnalyseur;
#ifdef SONDE
    sTypeAnalyseur = "SONDE";
#elif defined(KMNO4)    
    sTypeAnalyseur = "KMNO4";
#elif defined(TITRI)    
    sTypeAnalyseur = "TITRI";
#elif defined(SILICE)    
    sTypeAnalyseur = "SILICE";
#elif defined(COULEUR)    
    sTypeAnalyseur = "COULEUR";
#elif defined(COLO)
    sTypeAnalyseur = "COLO";
#endif

#if defined(CALIBRATIONS_INDEPENDANTE)
    sTypeAnalyseur = "\nCALIBRATION INDEPENDANTE DES VOIES\n" + sTypeAnalyseur;
#endif
#if defined(MULTI_STREAM)    
    sTypeAnalyseur = "MULTI STREAM " + sTypeAnalyseur;
#endif

#if defined(MULTI_MEASURE)
    sTypeAnalyseur = "MULTI MEASURE " + sTypeAnalyseur; 
#endif 

#if defined(PH)
    sTypeAnalyseur = "PH " + sTypeAnalyseur;
#endif 

#if defined(CHROME)
    sTypeAnalyseur = "CHROME " + sTypeAnalyseur;
#endif 

#ifdef MULTI_EV
	sTypeAnalyseur = "\nMulti EV " + sTypeAnalyseur;
#endif

#ifdef SULFITE
	sTypeAnalyseur = "SULFITE " + sTypeAnalyseur;
#endif
#ifdef CERIUM
	sTypeAnalyseur = "CERIUM " + sTypeAnalyseur;
#endif
#if defined(MAGNESIUM)
    sTypeAnalyseur = "MAGNESIUM " + sTypeAnalyseur;
#endif 
#if defined(CALCIUM_MAGNESIUM)
    sTypeAnalyseur = "Ca+Mg " + sTypeAnalyseur;
#endif 

#if defined(SELECTEUR)    
    sTypeAnalyseur = sTypeAnalyseur +tr(" avec SELECTEUR");
#endif

#if defined(R_D)
	sTypeAnalyseur = sTypeAnalyseur + "\nVERSION R&D";
#endif

	//QString lblConfig = QString::fromUtf16(( const ushort *)m_pSupervision->getAnalyseur()->m_CmdLoadNumConfig.szGetLabel());
	
    //assemblage du menu et du layoutGauche
	QHBoxLayout* layoutMain = new QHBoxLayout();
	layoutMain->addWidget(new QLabel(tr("Version de l'IHM :") 
									+ "\n" + NUM_VERSION_QT 
									+ "\n" + sTypeAnalyseur 
									+ "\n" + tr("Version de la supervision : ")
									+ "\n" + QString::number(NUM_VERSION_5)));
									//+ "\n" + lblConfig));
	layoutMain->addLayout(layoutMenu);
	widgetDialog->setLayout(layoutMain);
	
	
	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(tabWidget);

	setLayout(layout);

	this->setObjectName("dialogModal");
	this->setWindowFlags(Qt::FramelessWindowHint);

	setConnexion();
}

void CDialogInfo::setConnexion()
{
	connect(m_btBack, SIGNAL(clicked()), this, SLOT(reject()));
}

CDialogInfo* CDialogInfo::getInstance()
{
	if(!singleton)
			singleton = new CDialogInfo();

	return singleton;
}