#include "CWinSchedulerView.h"
#include "CWinSchedulerControler.h"
#include "CWinSchedulerModel.h"

#include "header_qt.h"



CWinSchedulerView::CWinSchedulerView(CWinSchedulerControler* argpControler, QWidget *parent,Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	m_pControler = argpControler;
}
void CWinSchedulerView::setModel(CWinSchedulerModel* argpModel)
{
    m_pModel = argpModel; 
    init();
}

void CWinSchedulerView::init()
{
	qDebug() << "QTabWidget* tabWidget = new QTabWidget();" ;
	m_tabWidget = new QTabWidget();

	//*** onglet Options
    {
	    QWidget* widgetPeriodique = new QWidget();

        m_btRemoteCtrl= new QPushButton();
	    m_btRemoteCtrl->setObjectName("btLineEdit");
	    connect(m_btRemoteCtrl, SIGNAL(clicked()), m_pControler, SLOT(btRemoteCtrlPressed()));
        m_lblRemoteCtrl = new QLabel(tr("Mode de contrôle\n0 : Local\n1 : Maintenance\n2 : JBus \n3 : Externe"));
	    m_lblRemoteCtrl->setObjectName("lblMeasure");

        m_btConsigneGain= new QPushButton();
	    m_btConsigneGain->setObjectName("btLineEdit");
	    connect(m_btConsigneGain, SIGNAL(clicked()), m_pControler, SLOT(btConsigneGainPressed()));
        m_lblConsigneGain = new QLabel(tr("Consigne de gain"));
	    m_lblConsigneGain->setObjectName("lblMeasure");

        m_btConsigneTemperature= new QPushButton();
	    m_btConsigneTemperature->setObjectName("btLineEdit");
	    connect(m_btConsigneTemperature, SIGNAL(clicked()), m_pControler, SLOT(btConsigneTemperaturePressed()));
        m_lblConsigneTemperature = new QLabel(tr("Consigne de température"));
	    m_lblConsigneTemperature->setObjectName("lblMeasure");

        m_btRegalgePression= new QPushButton();
	    m_btRegalgePression->setObjectName("btLineEdit");
	    connect(m_btRegalgePression, SIGNAL(clicked()), m_pControler, SLOT(btReglagePressionPressed()));
        m_lblRegalgePression = new QLabel(tr("Réglage pression"));
	    m_lblRegalgePression->setObjectName("lblMeasure");

        m_btTempsVoieAttente= new QPushButton();
	    m_btTempsVoieAttente->setObjectName("btLineEdit");
	    connect(m_btTempsVoieAttente, SIGNAL(clicked()), m_pControler, SLOT(btTempsVoieAttentePressed()));
        m_lblTempsVoieAttente = new QLabel(tr("Réglage temps d'attente"));
	    m_lblTempsVoieAttente->setObjectName("lblMeasure");

        m_btNumEscalveJBUS= new QPushButton();
	    m_btNumEscalveJBUS->setObjectName("btLineEdit");
	    connect(m_btNumEscalveJBUS, SIGNAL(clicked()), m_pControler, SLOT(btNumEscalveJBUSPressed()));
        m_lblNumEscalveJBUS = new QLabel(tr("Esclave JBus N°"));
	    m_lblNumEscalveJBUS->setObjectName("lblMeasure");
	    QFormLayout* layoutGauche= new QFormLayout();

	    layoutGauche->addRow(m_lblConsigneTemperature, m_btConsigneTemperature);
	    layoutGauche->addRow(m_lblRegalgePression, m_btRegalgePression);
	    layoutGauche->addRow(m_lblConsigneGain, m_btConsigneGain);
	    layoutGauche->addRow(m_lblNumEscalveJBUS, m_btNumEscalveJBUS);
	    layoutGauche->addRow(m_lblRemoteCtrl, m_btRemoteCtrl);
	    //layoutGauche->addRow(m_lblTempsVoieAttente, m_btTempsVoieAttente); //ATTENTION CHANGER LES SET ET LES GET EN FONTION DU SEQUENCEUR !

	    //layoutGauche->addLayout(layoutNav);

	    //menu de gauche //toujours 4 items dans les menus en incluant les spacers
	    m_btBack = new QPushButton();
	    m_btBack->setObjectName("btBack");
	    connect(m_btBack, SIGNAL(clicked()), m_pControler, SLOT(btBackPressed()));

	    QVBoxLayout* layoutMenu = new QVBoxLayout();
	    layoutMenu->addStretch();
	    layoutMenu->addWidget(m_btBack);

	    //assemblage du menu et du layoutGauche
	    QHBoxLayout* layoutMain = new QHBoxLayout();
	    layoutMain->addLayout(layoutGauche);
	    layoutMain->addStretch();
	    layoutMain->addLayout(layoutMenu);
	    widgetPeriodique->setLayout(layoutMain);
	    //:Nom de l'onglet à garer en maj pour toutes les trad
	    m_tabWidget->addTab(widgetPeriodique, tr("OPTIONS"));
    }

	//Onglet configuration cycles auto
	{
		QWidget* widgetPeriodique = new QWidget();
		
		QFormLayout* layoutGauche= new QFormLayout();

		TCHAR szText[260];
#ifndef TEST
		bCopyFile(szGetFullPathName(_T("ConfigAnalyseur.ini"),szText),SZ_FIC_TEMP,FALSE);
		//Zero
		m_btNbCyleAvantZero = new QPushButton();
	    m_btNbCyleAvantZero->setObjectName("btLineEdit");
			
		dwGetPrivateProfileString(_T("Config"), _T("ZeroCyclePresent"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
		QString sLigneIni = QString::fromUtf16 ((const ushort *)szText);
		QStringList sListLigneIni = sLigneIni.split("|");
		if (sListLigneIni.count() > 1 && sListLigneIni.at(2).toInt())
		{
			dwGetPrivateProfileString(_T("Config"), _T("ZeroCycleLabel"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
			sLigneIni = QString::fromUtf16 ((const ushort *)szText);
			sListLigneIni = sLigneIni.split("|");

			connect(m_btNbCyleAvantZero, SIGNAL(clicked()), m_pControler, SLOT(btNbCyleAvantZeroPressed()));
			m_lblNbCyleAvantZero = new QLabel(tr("Nombre de cycle \navant ") + sListLigneIni.at(2)
#ifdef SONDE
				+ QString("\n")+QString("(if 0, no slope ctrl)"));
#else
				);
#endif

			m_lblNbCyleAvantZero->setObjectName("lblMeasure");
			layoutGauche->addRow(m_lblNbCyleAvantZero, m_btNbCyleAvantZero);
		}
	
		//Calibration
		m_btNbCyleAvantCalib = new QPushButton();
	    m_btNbCyleAvantCalib->setObjectName("btLineEdit");

		dwGetPrivateProfileString(_T("Config"), _T("CalibrageCyclePresent"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
		sLigneIni = QString::fromUtf16 ((const ushort *)szText);
		sListLigneIni = sLigneIni.split("|");
		if (sListLigneIni.count() > 1 && sListLigneIni.at(2).toInt())
		{
			dwGetPrivateProfileString(_T("Config"), _T("CalibrageCycleLabel"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
			sLigneIni = QString::fromUtf16 ((const ushort *)szText);
			sListLigneIni = sLigneIni.split("|");

			connect(m_btNbCyleAvantCalib, SIGNAL(clicked()), m_pControler, SLOT(btNbCyleAvantCalibPressed()));
			m_lblNbCyleAvantCalib = new QLabel(tr("Nombre de cycle \navant ")+ sListLigneIni.at(2));
			m_lblNbCyleAvantCalib->setObjectName("lblMeasure");
			layoutGauche->addRow(m_lblNbCyleAvantCalib, m_btNbCyleAvantCalib);
		}
		
	    //Calibration en ligne
		m_btNbCyleAvantCalibInLine = new QPushButton();
	    m_btNbCyleAvantCalibInLine->setObjectName("btLineEdit");

		dwGetPrivateProfileString(_T("Config"), _T("CalibrageInLineCyclePresent"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
		sLigneIni = QString::fromUtf16 ((const ushort *)szText);
		sListLigneIni = sLigneIni.split("|");
		if (sListLigneIni.count() > 1 && sListLigneIni.at(2).toInt())
		{
			dwGetPrivateProfileString(_T("Config"), _T("CalibrageInLineCycleLabel"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
			sLigneIni = QString::fromUtf16 ((const ushort *)szText);
			sListLigneIni = sLigneIni.split("|");

			connect(m_btNbCyleAvantCalibInLine, SIGNAL(clicked()), m_pControler, SLOT(btNbCyleAvantCalibInLinePressed()));
			m_lblNbCyleAvantCalibInLine = new QLabel(tr("Nombre de cycle \navant ")+ sListLigneIni.at(2));
			m_lblNbCyleAvantCalibInLine->setObjectName("lblMeasure");
			layoutGauche->addRow(m_lblNbCyleAvantCalibInLine, m_btNbCyleAvantCalibInLine);
		}
		
	    
		//Mesure manuel (cleanup)
		m_btNbCyleAvantCleanup = new QPushButton();
	    m_btNbCyleAvantCleanup->setObjectName("btLineEdit");

		dwGetPrivateProfileString(_T("Config"), _T("CleanupCyclePresent"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
		sLigneIni = QString::fromUtf16 ((const ushort *)szText);
		sListLigneIni = sLigneIni.split("|");
		if (sListLigneIni.count() > 1 && sListLigneIni.at(2).toInt())
		{
			dwGetPrivateProfileString(_T("Config"), _T("CleanupCycleLabel"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
			sLigneIni = QString::fromUtf16 ((const ushort *)szText);
			sListLigneIni = sLigneIni.split("|");

			connect(m_btNbCyleAvantCleanup, SIGNAL(clicked()), m_pControler, SLOT(btNbCyleAvantCleanupPressed()));
			m_lblNbCyleAvantCleanup = new QLabel(tr("Nombre de cycle \navant ")+ sListLigneIni.at(2));
			m_lblNbCyleAvantCleanup->setObjectName("lblMeasure");
			layoutGauche->addRow(m_lblNbCyleAvantCleanup, m_btNbCyleAvantCleanup);
		}
		
	    
#else
		bCopyFile(szGetFullPathName(_T("ConfigAnalyseur.ini"),szText),SZ_FIC_TEMP,FALSE);
		HANDLE hf  ;
		long filelen = openFile(SZ_FIC_TEMP, hf);
		//Zero
		dwGetPrivateProfileString(_T("Config"), _T("ZeroCyclePresent"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
		QString sLigneIni = QString::fromUtf16 ((const ushort *)szText);
		QStringList sListLigneIni = sLigneIni.split("|");
		if (sListLigneIni.count() > 1 && sListLigneIni.at(2).toInt())
		{
			dwGetPrivateProfileString(_T("Config"), _T("ZeroCycleLabel"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
			sLigneIni = QString::fromUtf16 ((const ushort *)szText);
			sListLigneIni = sLigneIni.split("|");
		}
		m_btNbCyleAvantZero = new QPushButton();
	    m_btNbCyleAvantZero->setObjectName("btLineEdit");
	    connect(m_btNbCyleAvantZero, SIGNAL(clicked()), m_pControler, SLOT(btNbCyleAvantZeroPressed()));
		m_lblNbCyleAvantZero = new QLabel(tr("Nombre de cycle \navant ") + sListLigneIni.at(2) +tr("\n(Si 0, pas de cyle de blanc)"));

		//Calibration
		dwGetPrivateProfileString(_T("Config"), _T("CalibrageCyclePresent"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
		sLigneIni = QString::fromUtf16 ((const ushort *)szText);
		sListLigneIni = sLigneIni.split("|");
		if (sListLigneIni.count() > 1 && sListLigneIni.at(2).toInt())
		{
			dwGetPrivateProfileString(_T("Config"), _T("CalibrageCycleLabel"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
			sLigneIni = QString::fromUtf16 ((const ushort *)szText);
			sListLigneIni = sLigneIni.split("|");
		}
		m_btNbCyleAvantCalib = new QPushButton();
	    m_btNbCyleAvantCalib->setObjectName("btLineEdit");
	    connect(m_btNbCyleAvantCalib, SIGNAL(clicked()), m_pControler, SLOT(btNbCyleAvantCalibPressed()));
		m_lblNbCyleAvantCalib = new QLabel(tr("Nombre de cycle \navant ")+ sListLigneIni.at(2));
		
		//Calibration en ligne
		dwGetPrivateProfileString(_T("Config"), _T("CalibrageInLineCyclePresent"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
		sLigneIni = QString::fromUtf16 ((const ushort *)szText);
		sListLigneIni = sLigneIni.split("|");
		if (sListLigneIni.count() > 1 && sListLigneIni.at(2).toInt())
		{
			dwGetPrivateProfileString(_T("Config"), _T("CalibrageInLineCycleLabel"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
			sLigneIni = QString::fromUtf16 ((const ushort *)szText);
			sListLigneIni = sLigneIni.split("|");
		}
		m_btNbCyleAvantCalibInLine = new QPushButton();
	    m_btNbCyleAvantCalibInLine->setObjectName("btLineEdit");
	    connect(m_btNbCyleAvantCalibInLine, SIGNAL(clicked()), m_pControler, SLOT(btNbCyleAvantCalibInLinePressed()));
		m_lblNbCyleAvantCalibInLine = new QLabel(tr("Nombre de cycle \navant ")+ sListLigneIni.at(2));
		
		//Mesure manuel (cleanup)
		dwGetPrivateProfileString(_T("Config"), _T("CleanupCyclePresent"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
		sLigneIni = QString::fromUtf16 ((const ushort *)szText);
		sListLigneIni = sLigneIni.split("|");
		if (sListLigneIni.count() > 1 && sListLigneIni.at(2).toInt())
		{
			dwGetPrivateProfileString(_T("Config"), _T("CleanupCycleLabel"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
			sLigneIni = QString::fromUtf16 ((const ushort *)szText);
			sListLigneIni = sLigneIni.split("|");
		}
		m_btNbCyleAvantCleanup = new QPushButton();
	    m_btNbCyleAvantCleanup->setObjectName("btLineEdit");
	    connect(m_btNbCyleAvantCleanup, SIGNAL(clicked()), m_pControler, SLOT(btNbCyleAvantCleanupPressed()));
		m_lblNbCyleAvantCleanup = new QLabel(tr("Nombre de cycle \navant ")+ sListLigneIni.at(2));
#endif
	    
		m_btValeurEtalon= new QPushButton();
	    m_btValeurEtalon->setObjectName("btLineEdit");
	    connect(m_btValeurEtalon, SIGNAL(clicked()), m_pControler, SLOT(btValeurEtalonPressed()));
        m_lblValeurEtalon = new QLabel(tr("Valeur étalon"));
	    m_lblValeurEtalon->setObjectName("lblMeasure");
		layoutGauche->addRow(m_lblValeurEtalon, m_btValeurEtalon);
	    

        //menu de gauche //toujours 4 items dans les menus en incluant les spacers
	    m_btBack = new QPushButton();
	    m_btBack->setObjectName("btBack");
	    connect(m_btBack, SIGNAL(clicked()), m_pControler, SLOT(btBackPressed()));

	    QVBoxLayout* layoutMenu = new QVBoxLayout();
	    layoutMenu->addStretch();
	    layoutMenu->addWidget(m_btBack);

	    //assemblage du menu et du layoutGauche
	    QHBoxLayout* layoutMain = new QHBoxLayout();
	    layoutMain->addLayout(layoutGauche);
	    layoutMain->addStretch();
	    layoutMain->addLayout(layoutMenu);
	    widgetPeriodique->setLayout(layoutMain);
	    //:Nom de l'onglet à garer en maj pour toutes les trad
#if !defined(CALCIUM_MAGNESIUM) && defined(RES_640_480) 
	    m_tabWidget->addTab(widgetPeriodique, tr("CYCLES AUTO"));
#endif
	}
	//*** onglet Sequenceur
    {
        QWidget* widgetSequenceur = new QWidget();
        
        QFormLayout*  layoutRows = new QFormLayout();
        int nbSequence = m_pModel->getNbSequence();
        for(int i=0; i<MAX_SEQUENCE ; ++i)
        {
            QLabel* lblNumSeq;
            CPushButton* btNumVoie;
            CPushButton* btTempsSeq;
            CPushButton* btDelete = new CPushButton(i);
            if(i<nbSequence)
            {
                lblNumSeq = new QLabel(QString::number(i+1) + " :");
                if(m_pModel->getSequence(i).iStream > NBR_STREAM_MAX)
                {
                    btNumVoie = new CPushButton(i, tr("Pause"));
                    btTempsSeq = new CPushButton(i, QString::number(m_pModel->getSequence(i).iDuree) 
                                    + ((m_pModel->getSequence(i).iDuree>1)?tr(" Minutes"):tr(" Minute")));
                }
                else
                {    
                    btNumVoie = new CPushButton(i, tr("Voie ") + QString::number(m_pModel->getSequence(i).iStream+1));
                    btTempsSeq = new CPushButton(i, QString::number(m_pModel->getSequence(i).iDuree) 
                                    + ((m_pModel->getSequence(i).iDuree>1)?tr(" Cycles"):tr(" Cycle")));
                }
            }
            else
            {
                lblNumSeq = new QLabel(QString::number(i+1) + " :");
                btNumVoie = new CPushButton(i, tr("Ajouter"));
                btTempsSeq = new CPushButton(i);
                btTempsSeq->setVisible(false);
                btDelete->setVisible(false);
            }
            
            lblNumSeq->setObjectName("lblMeasure");
            btNumVoie->setObjectName("btLineEdit");
	        connect(btNumVoie, SIGNAL(clicked(int)), m_pControler, SLOT(btNumVoiePressed(int)));
            btTempsSeq->setObjectName("btLineEdit");
	        connect(btTempsSeq, SIGNAL(clicked(int)), m_pControler, SLOT(btTempsSeqPressed(int)));
            btDelete->setObjectName("btDeleteSeq");
	        connect(btDelete, SIGNAL(clicked(int)), m_pControler, SLOT(btDeletePressed(int)));

            SequenceRow seqRow = {btNumVoie, btTempsSeq, btDelete};
            m_listSequenceRow.append(seqRow);

       
            QHBoxLayout* layoutRow = new QHBoxLayout();
            layoutRow->addWidget(btNumVoie);
            layoutRow->addWidget(btTempsSeq);
            layoutRow->addSpacing(5);
            if(i != 0)
                layoutRow->addWidget(btDelete);
            layoutRow->addStretch();

            layoutRows->addRow(lblNumSeq, layoutRow);
        }
       // layoutRows->addStretch();

        QPushButton* btBack = new QPushButton();
	    btBack->setObjectName("btBack");
	    connect(btBack, SIGNAL(clicked()), m_pControler, SLOT(btBackPressed()));

       /* QPushButton* btAddSeq = new QPushButton();
	    btAddSeq->setObjectName("btAddSeq");*/

	    QVBoxLayout* layoutMenu = new QVBoxLayout();
	    layoutMenu->addStretch();
	    //layoutMenu->addWidget(btAddSeq);
	    layoutMenu->addWidget(btBack);

        QHBoxLayout* layout = new QHBoxLayout();
        layout->addLayout(layoutRows);
	    layout->addStretch();
        layout->addLayout(layoutMenu);

        widgetSequenceur->setLayout(layout);
	    m_tabWidget->addTab(widgetSequenceur , tr("SEQUENCEUR"));
    }
	//*** onglet Config de seuil
  
    {
        QWidget* widgetSequenceur = new QWidget();
        
        QVBoxLayout* layoutRows = new QVBoxLayout();
		int indexBt = 0;
        for(int i=0; i< m_pModel->getNbStream() ; ++i)
        {
            for(int j=0; j<m_pModel->getNbMeasure(); ++j)
            {
                QLabel* lblConfigSeuil = new QLabel(  tr("Voie ") + QString::number(i+1) 
                                                    + tr(" mesure ") + QString::number(j+1));
                lblConfigSeuil->setObjectName("lblMeasure");
                
                CPushButton* btConfigSeuil= new CPushButton(indexBt++, m_pModel->getLblConfigSeuil(i, j));
                btConfigSeuil->setObjectName("btLineEdit");
                m_listBtConfigSeuil.append(btConfigSeuil);
                connect(btConfigSeuil, SIGNAL(clicked(int)), m_pControler, SLOT(btConfigSeuilPressed(int)));
                           
                QHBoxLayout* layoutRow = new QHBoxLayout();
                layoutRow->addWidget(lblConfigSeuil);
                layoutRow->addWidget(btConfigSeuil);
                layoutRow->addStretch();

                layoutRows->addLayout(layoutRow);
            }
        }
        layoutRows->addStretch();
        QPushButton* btBack = new QPushButton();
	    btBack->setObjectName("btBack");
	    connect(btBack, SIGNAL(clicked()), m_pControler, SLOT(btBackPressed()));

        
        QVBoxLayout* layoutMenu = new QVBoxLayout();
	    layoutMenu->addStretch();
	    layoutMenu->addWidget(btBack);

        QHBoxLayout* layout = new QHBoxLayout();
        layout->addLayout(layoutRows);
	    layout->addStretch();
        layout->addLayout(layoutMenu);

        widgetSequenceur->setLayout(layout);
	    m_tabWidget->addTab(widgetSequenceur , tr("SEUILS"));

    }

	//*** onglet Config Heure
  
    {
	
		QWidget* widgetSequenceur = new QWidget();

		QPushButton* btBack = new QPushButton();
	    btBack->setObjectName("btBack");
	    connect(btBack, SIGNAL(clicked()), m_pControler, SLOT(btBackPressed()));
		/*QPushButton* btApply = new QPushButton();
	    btApply->setObjectName("btApply");
	    connect(btApply, SIGNAL(clicked()), m_pControler, SLOT(btApplyDateTimePressed()));*/

		QDateTime* dateTime = new QDateTime(QDate::currentDate(), QTime::currentTime());
		
		m_btYear = new QPushButton(m_pModel->getYear());
		m_btYear->setObjectName("btLineEdit");
		m_btMonth = new QPushButton(m_pModel->getMonth());
		m_btMonth->setObjectName("btLineEdit");
		m_btDay = new QPushButton(m_pModel->getDay());
		m_btDay->setObjectName("btLineEdit");
		m_btHour = new QPushButton(m_pModel->getHour());
		m_btHour->setObjectName("btLineEdit");
		m_btMinute = new QPushButton(m_pModel->getMinute());
		m_btMinute->setObjectName("btLineEdit");
		
		QPushButton* btYearP = new QPushButton();
		btYearP->setObjectName("btPlusDateTime");
	    connect(btYearP, SIGNAL(clicked()), m_pControler, SLOT(btYearPPressed()));
		QPushButton* btMonthP = new QPushButton();
		btMonthP->setObjectName("btPlusDateTime");
	    connect(btMonthP, SIGNAL(clicked()), m_pControler, SLOT(btMonthPPressed()));
		QPushButton* btDayP = new QPushButton();
		btDayP->setObjectName("btPlusDateTime");
	    connect(btDayP, SIGNAL(clicked()), m_pControler, SLOT(btDayPPressed()));
		QPushButton* btHourP = new QPushButton();
		btHourP->setObjectName("btPlusDateTime");
	    connect(btHourP, SIGNAL(clicked()), m_pControler, SLOT(btHourPPressed()));
		QPushButton* btMinuteP = new QPushButton();
		btMinuteP->setObjectName("btPlusDateTime");
	    connect(btMinuteP, SIGNAL(clicked()), m_pControler, SLOT(btMinutePPressed()));
		
		QPushButton* btYearM = new QPushButton();
		btYearM->setObjectName("btMoinsDateTime");
	    connect(btYearM, SIGNAL(clicked()), m_pControler, SLOT(btYearMPressed()));
		QPushButton* btMonthM = new QPushButton();
		btMonthM->setObjectName("btMoinsDateTime");
	    connect(btMonthM, SIGNAL(clicked()), m_pControler, SLOT(btMonthMPressed()));
		QPushButton* btDayM = new QPushButton();
		btDayM->setObjectName("btMoinsDateTime");
	    connect(btDayM, SIGNAL(clicked()), m_pControler, SLOT(btDayMPressed()));
		QPushButton* btHourM = new QPushButton();
		btHourM->setObjectName("btMoinsDateTime");
	    connect(btHourM, SIGNAL(clicked()), m_pControler, SLOT(btHourMPressed()));
		QPushButton* btMinuteM = new QPushButton();
		btMinuteM->setObjectName("btMoinsDateTime");
	    connect(btMinuteM, SIGNAL(clicked()), m_pControler, SLOT(btMinuteMPressed()));
				
		QHBoxLayout* hboxLayoutYear = new QHBoxLayout();
		hboxLayoutYear->addWidget(btYearM);
		hboxLayoutYear->addWidget(m_btYear);
		hboxLayoutYear->addWidget(btYearP);
		QHBoxLayout* hboxLayoutMonth = new QHBoxLayout();
		hboxLayoutMonth->addWidget(btMonthM);
		hboxLayoutMonth->addWidget(m_btMonth);
		hboxLayoutMonth->addWidget(btMonthP);
		QHBoxLayout* hboxLayoutDay = new QHBoxLayout();
		hboxLayoutDay->addWidget(btDayM);
		hboxLayoutDay->addWidget(m_btDay);
		hboxLayoutDay->addWidget(btDayP);

		QVBoxLayout* vboxLayoutDate = new QVBoxLayout();
		vboxLayoutDate->addWidget(new QLabel(tr("Jour :")));
		vboxLayoutDate->addLayout(hboxLayoutDay);
		vboxLayoutDate->addWidget(new QLabel(tr("Mois :")));
		vboxLayoutDate->addLayout(hboxLayoutMonth);
		vboxLayoutDate->addWidget(new QLabel(tr("Année :")));
		vboxLayoutDate->addLayout(hboxLayoutYear);
		vboxLayoutDate->addStretch();

		QHBoxLayout* hboxLayoutHour = new QHBoxLayout();
		hboxLayoutHour->addWidget(btHourM);
		hboxLayoutHour->addWidget(m_btHour);
		hboxLayoutHour->addWidget(btHourP);
		QHBoxLayout* hboxLayoutMinute = new QHBoxLayout();
		hboxLayoutMinute->addWidget(btMinuteM);
		hboxLayoutMinute->addWidget(m_btMinute);
		hboxLayoutMinute->addWidget(btMinuteP);
		
		QVBoxLayout* vboxLayoutTime = new QVBoxLayout();
		vboxLayoutTime->addWidget(new QLabel(tr("Heure :")));
		vboxLayoutTime->addLayout(hboxLayoutHour);
		vboxLayoutTime->addWidget(new QLabel(tr("Minute :")));
		vboxLayoutTime->addLayout(hboxLayoutMinute);
		vboxLayoutTime->addStretch();
		
		QVBoxLayout* layoutMenu = new QVBoxLayout();
	    layoutMenu->addStretch();
	    layoutMenu->addWidget(btBack);

		QHBoxLayout* hboxLayout = new QHBoxLayout();
		hboxLayout->addLayout(vboxLayoutDate);
		hboxLayout->addStretch();
		hboxLayout->addLayout(vboxLayoutTime);
		hboxLayout->addLayout(layoutMenu);

		widgetSequenceur->setLayout(hboxLayout);
	    m_tabWidget->addTab(widgetSequenceur , tr("DATE/HEURE"));

    }

    QHBoxLayout* layoutGlobal = new QHBoxLayout(); 
    layoutGlobal->setContentsMargins ( 0, 0, 0, 0 );
    layoutGlobal->addWidget(m_tabWidget);
	this->setLayout(layoutGlobal);

	qDebug() << "FIN QTabWidget* tabWidget = new QTabWidget();" ;

}



void CWinSchedulerView::setNbCyleAvantZeroValue(const QString& arg_sValue)
{
	m_btNbCyleAvantZero->setText(arg_sValue);
	m_pModel->setNbCycleAvantZero(arg_sValue);
}

void CWinSchedulerView::setNbCyleAvantCalibValue(const QString& arg_sValue)
{
	m_btNbCyleAvantCalib->setText(arg_sValue);
	m_pModel->setNbCycleAvantCalib(arg_sValue);
}

void CWinSchedulerView::setNbCyleAvantCleanupValue(const QString& arg_sValue)
{
	m_btNbCyleAvantCleanup->setText(arg_sValue);
	m_pModel->setNbCycleAvantCleanup(arg_sValue);
}
void CWinSchedulerView::setNbCyleAvantCalibInLineValue(const QString& arg_sValue)
{
	m_btNbCyleAvantCalibInLine->setText(arg_sValue);
	m_pModel->setNbCycleAvantCalibInLine(arg_sValue);
}
void CWinSchedulerView::setRemoteCtrlValue(const QString& arg_sValue)
{
	m_btRemoteCtrl->setText(arg_sValue);
	m_pModel->setRemoteControl(arg_sValue);
}
void CWinSchedulerView::setValeurEtalonValue(const QString& arg_sValue)
{
	m_btValeurEtalon->setText(arg_sValue);
	m_pModel->setValeurEtalon(arg_sValue);
}
void CWinSchedulerView::setConsigneGainValue(const QString& arg_sValue)
{
	m_btConsigneGain->setText(arg_sValue);
	m_pModel->setConsigneGain(arg_sValue);
}
void CWinSchedulerView::setConsigneTemperatureValue(const QString& arg_sValue)
{
	m_btConsigneTemperature->setText(arg_sValue);
	m_pModel->setConsigneTemperature(arg_sValue);
}
void CWinSchedulerView::setReglagePressionValue(const QString& arg_sValue)
{
	m_btRegalgePression->setText(arg_sValue);
	m_pModel->setReglagePression(arg_sValue);
}
void CWinSchedulerView::setTempsVoieAttenteValue(const QString& arg_sValue)
{
	m_btTempsVoieAttente->setText(arg_sValue);
	m_pModel->setTempsVoieAttente(arg_sValue);
}
void CWinSchedulerView::setNumEscalveJBUSValue(const QString& arg_sValue)
{
    m_btNumEscalveJBUS->setText(arg_sValue);
    m_pModel->setNumEscalveJBUS(arg_sValue);
}
void CWinSchedulerView::setConfigSeuil(int arg_numBt, int arg_value)
{
    m_pModel->setConfigSeuil(arg_numBt, arg_value);
    m_listBtConfigSeuil.at(arg_numBt)->setText(m_pModel->getLblConfigSeuil(arg_numBt));
	qDebug() << arg_numBt << "###### " << arg_value << " " << m_pModel->getLblConfigSeuil(arg_numBt);
}
void CWinSchedulerView::loadPage()
{
    int nbSequence = 0;
	m_btYear->setText(m_pModel->getYear());
	m_btMonth->setText(m_pModel->getMonth());
	m_btDay->setText(m_pModel->getDay());

	m_btHour->setText(m_pModel->getHour());
	m_btMinute->setText(m_pModel->getMinute());


    switch(m_tabWidget->currentIndex())
    {
    case 0: //Options
	    m_btNbCyleAvantZero->setText(m_pModel->getNbCycleAvantZero());
	    m_btNbCyleAvantCleanup->setText(m_pModel->getNbCycleAvantCleanup());
		m_btValeurEtalon->setText(m_pModel->getValeurEtalon());
	    m_btRemoteCtrl->setText(m_pModel->getRemoteControl());
	    m_btConsigneGain->setText(m_pModel->getConsigneGain());
	    m_btConsigneTemperature->setText(m_pModel->getConsigneTemperature());
 	    m_btRegalgePression->setText(m_pModel->getReglagePression());
	    m_btTempsVoieAttente->setText(m_pModel->getTempsVoieAttente());
	    m_btNumEscalveJBUS->setText(m_pModel->getNumEscalveJBUS());
		m_btNbCyleAvantCalib->setText(m_pModel->getNbCycleAvantCalib());
		m_btNbCyleAvantCalibInLine->setText(m_pModel->getNbCycleAvantCalibInLine());
        break;
	case 1: //Cycle auto
		m_btNbCyleAvantCalib->setText(m_pModel->getNbCycleAvantCalib());
		m_btNbCyleAvantCalibInLine->setText(m_pModel->getNbCycleAvantCalibInLine());
		m_btValeurEtalon->setText(m_pModel->getValeurEtalon());
    case 2: //Sequenceur
        nbSequence = m_pModel->getNbSequence();
        for(int i=0; i<MAX_SEQUENCE ; ++i)
        {
            if(i<nbSequence)
            {

                if(m_pModel->getSequence(i).iStream > NBR_STREAM_MAX)
                {
                    m_listSequenceRow.at(i).btNumVoie->setText(tr("Pause"));
                    m_listSequenceRow.at(i).btTempsSeq->setText(QString::number(m_pModel->getSequence(i).iDuree) 
                                    + ((m_pModel->getSequence(i).iDuree>1)?tr(" Minutes"):tr(" Minute")));
                   
                }
                else
                {    
                    m_listSequenceRow.at(i).btNumVoie->setText(tr("Voie ") + QString::number(m_pModel->getSequence(i).iStream+1));
                    m_listSequenceRow.at(i).btTempsSeq->setText(QString::number(m_pModel->getSequence(i).iDuree) 
                                    + ((m_pModel->getSequence(i).iDuree>1)?tr(" Cycles"):tr(" Cycle")));
                }
                m_listSequenceRow.at(i).btTempsSeq->setVisible(true);
				if(i!=0) //ne pas afficher le bouton pour la première ligne
					m_listSequenceRow.at(i).btDelete->setVisible(true);
            }
            else
            {
                m_listSequenceRow.at(i).btNumVoie->setText(tr("Ajouter"));
                m_listSequenceRow.at(i).btTempsSeq->setVisible(false);
                if(i!=0)//ne pas afficher le bouton pour la première ligne
					m_listSequenceRow.at(i).btDelete->setVisible(false);
       
            }
        }
        break;
    default: break;
    }
}
