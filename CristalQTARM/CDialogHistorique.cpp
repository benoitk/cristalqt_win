#include "CDialogHistorique.h"
#include "CSupervision.h"
#include "CUserSession.h"
#include "CHistoSortedView.h"

#include "header_qt.h"
#include "stream.h"

CDialogHistorique* CDialogHistorique::singleton = 0;
CDialogHistorique* CDialogHistorique::getInstance()
{
	if(!singleton)
			singleton = new CDialogHistorique();
	return singleton;
}

CDialogHistorique::CDialogHistorique()
{
	m_listModel = new QStringListModel();
	m_listView = new CHistoSortedView(this);
    m_listView->setModel(m_listModel);

	/*m_btApply = new QPushButton();
	m_btApply->setObjectName("btApply");
	connect(m_btApply, SIGNAL(clicked()), this, SLOT(acquiter()));*/
	m_btBack = new QPushButton();
	m_btBack->setObjectName("btBack");
	connect(m_btBack, SIGNAL(clicked()), this, SLOT(close()));   
	m_btNext = new QPushButton();
	m_btNext->setObjectName("btNextBig");
	connect(m_btNext, SIGNAL(clicked()), m_listView, SLOT(slotNextPage()));
    m_btPrev = new QPushButton();
	m_btPrev->setObjectName("btPrevBig");
	connect(m_btPrev, SIGNAL(clicked()), m_listView, SLOT(slotPrevPage()));

	QTabWidget* tabWidget = new QTabWidget();

	QWidget* widgetDialog = new QWidget();
	tabWidget->addTab(widgetDialog, tr("HISTORIQUE"));
	
	QVBoxLayout* layoutMenu = new QVBoxLayout();
	layoutMenu->addStretch();
	layoutMenu->addWidget(m_btPrev);
	layoutMenu->addWidget(m_btNext);
	//layoutMenu->addWidget(m_btApply);
	layoutMenu->addWidget(m_btBack);

    

	//assemblage du menu et du layoutGauche
	QHBoxLayout* layoutMain = new QHBoxLayout();
	layoutMain->addWidget(m_listView);
	layoutMain->addLayout(layoutMenu);
	widgetDialog->setLayout(layoutMain);
	

	QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins ( 0, 0, 0, 0 );
	layout->addWidget(tabWidget);

	setLayout(layout);
}

void CDialogHistorique::setEnabledBtNext(const bool& arg_state)
{
    m_btNext->setEnabled(arg_state);
}

void CDialogHistorique::setEnabledBtPrev(const bool& arg_state)
{
    m_btPrev->setEnabled(arg_state);

}
void CDialogHistorique::addMesure(int arg_iStream, CStream* arg_pStream)
{
	//QString::fromWCharArray(arg_pszUnite);
	QStringList listString = m_listModel->stringList();

	SYSTEMTIME  stTime;
	GetLocalTime(&stTime);
	
	for(int k=0; (k < arg_pStream->iGetNbrMesure()) && (k < NBR_MESURE_MAX); k++)
	{
		QString lblMesure = QString::fromUtf16(( const ushort *)arg_pStream->pGetAt(k)->m_Val.szGetLabel()
											 , arg_pStream->pGetAt(k)->m_Val.lGetLabelLength());
		QString lblUnite = QString::fromUtf16(( const ushort *)arg_pStream->pGetAt(k)->m_Val.m_szUnit.szGetLabel()
											 , arg_pStream->pGetAt(k)->m_Val.m_szUnit.lGetLabelLength());
		QString sRow;
		QTextStream(&sRow)
			<< QString::number(stTime.wDay).rightJustified(2, '0') << "/" 
			<< QString::number(stTime.wMonth).rightJustified(2, '0')<< "/" 
			<< QString::number(stTime.wYear).rightJustified(2, '0') << " "
			<< QString::number(stTime.wHour).rightJustified(2, '0') << ":" 
			<< QString::number(stTime.wMinute).rightJustified(2, '0') << ":" 
			<< QString::number(stTime.wSecond).rightJustified(2, '0') << " " 
			<< tr("VOIE : ") << arg_iStream+1 << " "
			<< tr("MESURE : ") << lblMesure << " "
			//<<  arg_pStream->pGetAt(k)->m_Val.fGetVal() << " "
			<< rand() % 100 << " "
			<<  lblUnite ;
		listString.prepend(sRow);

		//pas plus de 1000 ligne dans l'histo
		if(listString.count() > 1000) listString.removeLast(); 
	
	}
	m_listModel->setStringList(listString);
    m_listView->slotChangePage();
}


