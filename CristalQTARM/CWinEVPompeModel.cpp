#include "CWinEVPompeModel.h"
#include "CSupervision.h"
#include "CWinEVPompeView.h"
#include "CStreamModel.h"
#include "CCmdJBusRunnable.h"

#include "header_qt.h"


// En fonction de l'ordre d'ajout des requetes : A rendre dynamique, sinon ce sera inmaintenable (voir aussi WinMeasureCardModel)
#define POMPE_ON "POMPE_ON_"
#define POMPE_OFF "POMPE_OFF_"
#define EV_ON "EV_ON_"
#define EV_OFF "EV_OFF_"
#define CONFIG_VITESSE_POMPE "CONFIG_VITESSE_POMPE"
#define CONFIG_POMPE "CONFIG_POMPE"
#define ALL_POMPES_OFF_1 "ALL_POMPES_OFF_1"
#define ALL_POMPES_OFF_2 "ALL_POMPES_OFF_2"

CWinEVPompeModel::CWinEVPompeModel(CSupervision* argpSupervision): m_cycleStep(NULL)//, CWinEVPompeView* argpView)
{
	qDebug() << "### Instance CWinEVPompeModel" << endl;
	m_pSupervision = argpSupervision;
	//m_pView = argpView;

    m_threadPool = new QThreadPool(this);
    m_mutex = new QMutex();

	TCHAR szText[260];
	bCopyFile(szGetFullPathName(_T("InterfaceMesure.ini"),szText),SZ_FIC_TEMP,FALSE);

#ifndef TEST
	dwGetPrivateProfileString(_T("Config_pump"), _T("Config_Pump"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
	QString sConfigPump = QString::fromUtf16 ((const ushort *)szText);
	QStringList sListConfigPump = sConfigPump.split("|");
	QString sConfigTemp = "";
	int nNumPumpPhysique = 0;
	int nNumPumpVirtuel = 0;
	TCHAR szRQ[5000];
	TCHAR szRP[5000];
	m_pSupervision->addKeyOnMapRQTComJBUSMesure(CONFIG_VITESSE_POMPE);
	_stprintf(szRQ,_T("10|16|0x0220|10|20|300|300|300|300|300|300|300|300|300|300"));
	_stprintf(szRP,_T("10|16|0x0220|10"));
	for(int i=0; i<10; ++i)	m_listVitessePompe.append("30");
	m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
	m_pSupervision->addKeyOnMapRQTComJBUSMesure(CONFIG_POMPE);
	_stprintf(szRQ,_T("10|16|0x0240|10|20|12|12|12|12|12|12|12|12|12|12"));
	_stprintf(szRP,_T("10|16|0x0240|10"));
	for(int i=0; i<10; ++i)	m_listConfPompe.append("12");
	for(int i=0; i<10; ++i)	m_listNbTourPompe.append("1000");

	m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
	/*m_pSupervision->addKeyOnMapRQTComJBUSMesure(ALL_POMPES_OFF_1);
	_stprintf(szRQ,_T("10|15|0x112|8|1|1"));
	_stprintf(szRP,_T("10|15|0x112|8"));
	m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
	m_pSupervision->addKeyOnMapRQTComJBUSMesure(ALL_POMPES_OFF_2);
	_stprintf(szRQ,_T("10|15|0x113|8|1|1"));
	_stprintf(szRP,_T("10|15|0x113|8"));
	m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());*/
					
	foreach(sConfigTemp, sListConfigPump)
	{
		++nNumPumpPhysique;
		if(sConfigTemp == "1")
		{
			m_pSupervision->addKeyOnMapRQTComJBUSMesure(POMPE_ON + QString::number(nNumPumpVirtuel));
			m_pSupervision->addKeyOnMapRQTComJBUSMesure(POMPE_OFF + QString::number(nNumPumpVirtuel++));
			qDebug() << "### Instance CWinEVPompeModel | nNumPumpPhysique:"<< nNumPumpPhysique << endl;
			switch(nNumPumpPhysique)
			{	
				case 1:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_0"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE1_ON
					_stprintf(szRQ,_T("10|5|0x1100|1|0"));
					_stprintf(szRP,_T("10|5|0x1100|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE1_OFF
					_stprintf(szRQ,_T("10|5|0x1120|1|0"));
					_stprintf(szRP,_T("10|5|0x1120|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 2:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_1"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE2_ON
					_stprintf(szRQ,_T("10|5|0x1101|1|0"));
					_stprintf(szRP,_T("10|5|0x1101|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE2_OFF
					_stprintf(szRQ,_T("10|5|0x1121|1|0"));
					_stprintf(szRP,_T("10|5|0x1121|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 3:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_2"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE3_ON
					_stprintf(szRQ,_T("10|5|0x1102|1|0"));
					_stprintf(szRP,_T("10|5|0x1102|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE3_OFF
					_stprintf(szRQ,_T("10|5|0x1122|1|0"));
					_stprintf(szRP,_T("10|5|0x1122|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 4:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_3"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE4_ON
					_stprintf(szRQ,_T("10|5|0x1103|1|0"));
					_stprintf(szRP,_T("10|5|0x1103|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE4_OFF
					_stprintf(szRQ,_T("10|5|0x1123|1|0"));
					_stprintf(szRP,_T("10|5|0x1123|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 5:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_4"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE5_ON
					_stprintf(szRQ,_T("10|5|0x1104|1|0"));
					_stprintf(szRP,_T("10|5|0x1104|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1124|1|0"));
					_stprintf(szRP,_T("10|5|0x1124|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 6:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_5"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE6_ON
					_stprintf(szRQ,_T("10|5|0x1105|1|0"));
					_stprintf(szRP,_T("10|5|0x1105|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1125|1|0"));
					_stprintf(szRP,_T("10|5|0x1125|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 7:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_6"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE7_ON
					_stprintf(szRQ,_T("10|5|0x1106|1|0"));
					_stprintf(szRP,_T("10|5|0x1106|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE7_OFF
					_stprintf(szRQ,_T("10|5|0x1126|1|0"));
					_stprintf(szRP,_T("10|5|0x1126|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 8:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_7"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE8_ON
					_stprintf(szRQ,_T("10|5|0x1107|1|0"));
					_stprintf(szRP,_T("10|5|0x1107|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1127|1|0"));
					_stprintf(szRP,_T("10|5|0x1127|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 9:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_8"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE7_ON
					_stprintf(szRQ,_T("10|5|0x1110|1|0"));
					_stprintf(szRP,_T("10|5|0x1110|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1130|1|0"));
					_stprintf(szRP,_T("10|5|0x1130|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 10:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_9"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE8_ON
					_stprintf(szRQ,_T("10|5|0x1111|1|0"));
					_stprintf(szRP,_T("10|5|0x1111|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1131|1|0"));
					_stprintf(szRP,_T("10|5|0x1131|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
			}
		}
	}

	dwGetPrivateProfileString(_T("Config_sv"), _T("Config_SV"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
	QString sConfigEV = QString::fromUtf16 ((const ushort *)szText);
	QStringList sListConfigEV = sConfigEV.split("|");
	int nNumEVPhysique = 0;
	int nNumEVVirtuel = 0;
	qDebug() << "#### sListConfigEV : " << sListConfigEV;
	foreach(sConfigTemp, sListConfigEV)
	{
		qDebug() << "#### sConfigTemp : " << sConfigTemp;
		
		++nNumEVPhysique;
		if(sConfigTemp == "1")
		{
			m_pSupervision->addKeyOnMapRQTComJBUSMesure(EV_ON + QString::number(nNumEVVirtuel));
			m_pSupervision->addKeyOnMapRQTComJBUSMesure(EV_OFF + QString::number(nNumEVVirtuel++));
			
			switch(nNumEVPhysique)
			{
				case 1:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_0"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1000|1|0"));
					_stprintf(szRP,_T("10|5|0x1000|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1000|0|0"));
					_stprintf(szRP,_T("10|5|0x1000|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 2:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_1"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1001|1|0"));
					_stprintf(szRP,_T("10|5|0x1001|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1001|0|0"));
					_stprintf(szRP,_T("10|5|0x1001|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 3:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_2"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1002|1|0"));
					_stprintf(szRP,_T("10|5|0x1002|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1002|0|0"));
					_stprintf(szRP,_T("10|5|0x1002|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 4:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_3"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1003|1|0"));
					_stprintf(szRP,_T("10|5|0x1003|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1003|0|0"));
					_stprintf(szRP,_T("10|5|0x1003|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 5:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_4"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1004|1|0"));
					_stprintf(szRP,_T("10|5|0x1004|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1004|0|0"));
					_stprintf(szRP,_T("10|5|0x1004|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 6:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_5"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1005|1|0"));
					_stprintf(szRP,_T("10|5|0x1005|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1005|0|0"));
					_stprintf(szRP,_T("10|5|0x1005|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 7:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_6"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1006|1|0"));
					_stprintf(szRP,_T("10|5|0x1006|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1006|0|0"));
					_stprintf(szRP,_T("10|5|0x1006|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 8:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_7"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), SZ_FIC_TEMP);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1007|1|0"));
					_stprintf(szRP,_T("10|5|0x1007|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1007|0|0"));
					_stprintf(szRP,_T("10|5|0x1007|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
			}
		}
	}
#else
	HANDLE hf  ;
	long filelen = openFile(SZ_FIC_TEMP, hf);

	dwGetPrivateProfileString(_T("Config_pump"), _T("Config_Pump"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
	QString sConfigPump = QString::fromUtf16 ((const ushort *)szText);
	QStringList sListConfigPump = sConfigPump.split("|");
	QString sConfigTemp = "";
	int nNumPumpPhysique = 0;
	int nNumPumpVirtuel = 0;
	TCHAR szRQ[5000];
	TCHAR szRP[5000];
	m_pSupervision->addKeyOnMapRQTComJBUSMesure(CONFIG_VITESSE_POMPE);
	_stprintf(szRQ,_T("10|16|0x0220|10|20|300|300|300|300|300|300|300|300|300|300"));
	_stprintf(szRP,_T("10|16|0x0220|10"));
	for(int i=0; i<10; ++i)	m_listVitessePompe.append("30");
	m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
	m_pSupervision->addKeyOnMapRQTComJBUSMesure(CONFIG_POMPE);
	_stprintf(szRQ,_T("10|16|0x0240|10|20|12|12|12|12|12|12|12|12|12|12"));
	_stprintf(szRP,_T("10|16|0x0240|10"));
	for(int i=0; i<10; ++i)	m_listConfPompe.append("12");
	for(int i=0; i<10; ++i)	m_listNbTourPompe.append("1000");

	m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
	/*m_pSupervision->addKeyOnMapRQTComJBUSMesure(ALL_POMPES_OFF_1);
	_stprintf(szRQ,_T("10|15|0x112|8|1|1"));
	_stprintf(szRP,_T("10|15|0x112|8"));
	m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
	m_pSupervision->addKeyOnMapRQTComJBUSMesure(ALL_POMPES_OFF_2);
	_stprintf(szRQ,_T("10|15|0x113|8|1|1"));
	_stprintf(szRP,_T("10|15|0x113|8"));
	m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());*/
					
	foreach(sConfigTemp, sListConfigPump)
	{
		++nNumPumpPhysique;
		if(sConfigTemp == "1")
		{
			m_pSupervision->addKeyOnMapRQTComJBUSMesure(POMPE_ON + QString::number(nNumPumpVirtuel));
			m_pSupervision->addKeyOnMapRQTComJBUSMesure(POMPE_OFF + QString::number(nNumPumpVirtuel++));
			qDebug() << "### Instance CWinEVPompeModel | nNumPumpPhysique:"<< nNumPumpPhysique << endl;
			switch(nNumPumpPhysique)
			{	
				case 1:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_0"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE1_ON
					_stprintf(szRQ,_T("10|5|0x1100|1|0"));
					_stprintf(szRP,_T("10|5|0x1100|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE1_OFF
					_stprintf(szRQ,_T("10|5|0x1120|1|0"));
					_stprintf(szRP,_T("10|5|0x1120|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 2:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_1"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE2_ON
					_stprintf(szRQ,_T("10|5|0x1101|1|0"));
					_stprintf(szRP,_T("10|5|0x1101|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE2_OFF
					_stprintf(szRQ,_T("10|5|0x1121|1|0"));
					_stprintf(szRP,_T("10|5|0x1121|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 3:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_2"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE3_ON
					_stprintf(szRQ,_T("10|5|0x1102|1|0"));
					_stprintf(szRP,_T("10|5|0x1102|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE3_OFF
					_stprintf(szRQ,_T("10|5|0x1122|1|0"));
					_stprintf(szRP,_T("10|5|0x1122|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 4:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_3"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE4_ON
					_stprintf(szRQ,_T("10|5|0x1103|1|0"));
					_stprintf(szRP,_T("10|5|0x1103|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE4_OFF
					_stprintf(szRQ,_T("10|5|0x1123|1|0"));
					_stprintf(szRP,_T("10|5|0x1123|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 5:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_4"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE5_ON
					_stprintf(szRQ,_T("10|5|0x1104|1|0"));
					_stprintf(szRP,_T("10|5|0x1104|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1124|1|0"));
					_stprintf(szRP,_T("10|5|0x1124|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 6:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_5"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE6_ON
					_stprintf(szRQ,_T("10|5|0x1105|1|0"));
					_stprintf(szRP,_T("10|5|0x1105|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1125|1|0"));
					_stprintf(szRP,_T("10|5|0x1125|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 7:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_6"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE7_ON
					_stprintf(szRQ,_T("10|5|0x1106|1|0"));
					_stprintf(szRP,_T("10|5|0x1106|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE7_OFF
					_stprintf(szRQ,_T("10|5|0x1126|1|0"));
					_stprintf(szRP,_T("10|5|0x1126|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 8:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_7"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE8_ON
					_stprintf(szRQ,_T("10|5|0x1107|1|0"));
					_stprintf(szRP,_T("10|5|0x1107|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1127|1|0"));
					_stprintf(szRP,_T("10|5|0x1127|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 9:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_8"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE7_ON
					_stprintf(szRQ,_T("10|5|0x1110|1|0"));
					_stprintf(szRP,_T("10|5|0x1110|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1130|1|0"));
					_stprintf(szRP,_T("10|5|0x1130|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
				case 10:
					dwGetPrivateProfileString(_T("Config_pump"), _T("Pump_Label_9"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vPumpLabels.append(QString::fromUtf16 ((const ushort *)szText).split("|").first());
					//POMPE8_ON
					_stprintf(szRQ,_T("10|5|0x1111|1|0"));
					_stprintf(szRP,_T("10|5|0x1111|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//POMPE5_OFF
					_stprintf(szRQ,_T("10|5|0x1131|1|0"));
					_stprintf(szRP,_T("10|5|0x1131|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					break;
			}
		}
	}

	dwGetPrivateProfileString(_T("Config_sv"), _T("Config_SV"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
	QString sConfigEV = QString::fromUtf16 ((const ushort *)szText);
	QStringList sListConfigEV = sConfigEV.split("|");
	int nNumEVPhysique = 0;
	int nNumEVVirtuel = 0;
	qDebug() << "#### sListConfigEV : " << sListConfigEV;
	foreach(sConfigTemp, sListConfigEV)
	{
		qDebug() << "#### sConfigTemp : " << sConfigTemp;
		
		++nNumEVPhysique;
		if(sConfigTemp == "1")
		{
			m_pSupervision->addKeyOnMapRQTComJBUSMesure(EV_ON + QString::number(nNumEVVirtuel));
			m_pSupervision->addKeyOnMapRQTComJBUSMesure(EV_OFF + QString::number(nNumEVVirtuel++));
			
			switch(nNumEVPhysique)
			{
				case 1:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_0"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1000|1|0"));
					_stprintf(szRP,_T("10|5|0x1000|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1000|0|0"));
					_stprintf(szRP,_T("10|5|0x1000|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 2:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_1"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1001|1|0"));
					_stprintf(szRP,_T("10|5|0x1001|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1001|0|0"));
					_stprintf(szRP,_T("10|5|0x1001|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 3:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_2"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1002|1|0"));
					_stprintf(szRP,_T("10|5|0x1002|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1002|0|0"));
					_stprintf(szRP,_T("10|5|0x1002|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 4:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_3"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1003|1|0"));
					_stprintf(szRP,_T("10|5|0x1003|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1003|0|0"));
					_stprintf(szRP,_T("10|5|0x1003|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 5:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_4"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1004|1|0"));
					_stprintf(szRP,_T("10|5|0x1004|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1004|0|0"));
					_stprintf(szRP,_T("10|5|0x1004|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 6:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_5"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1005|1|0"));
					_stprintf(szRP,_T("10|5|0x1005|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1005|0|0"));
					_stprintf(szRP,_T("10|5|0x1005|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 7:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_6"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1006|1|0"));
					_stprintf(szRP,_T("10|5|0x1006|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1006|0|0"));
					_stprintf(szRP,_T("10|5|0x1006|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
				case 8:
					dwGetPrivateProfileString(_T("Config_sv"), _T("SV_Label_7"),_T("0"),szText, sizeof(szText)/sizeof(TCHAR), hf, filelen);
					m_vEVLabels.append(QString::fromUtf16 ((const ushort *)szText));
					//EV1_ON
					_stprintf(szRQ,_T("10|5|0x1007|1|0"));
					_stprintf(szRP,_T("10|5|0x1007|1|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					//EV1_OFF
					_stprintf(szRQ,_T("10|5|0x1007|0|0"));
					_stprintf(szRP,_T("10|5|0x1007|0|0"));
					m_pSupervision->getCarteMesure()->bAddExchangeJbus(szRQ,szRP,m_pSupervision->getAnalyseur());
					qDebug() << "####  Instance Mesure | m_vEVLabels:" << m_vEVLabels<< endl;
					break;
			}
		}
	}
#endif
	
}
//M�thode appel� par les thread de m_threadPool
void CWinEVPompeModel::sendCmdJBus(const int& arg_numRQT, CElemList* arg_elemList, CEnumInterface& arg_interface)
{
    QMutexLocker locker(m_mutex);
   // qDebug() << "CWinEVPompeModel::sendCmdJBus : " << arg_numRQT;
    m_cycleStep.bExecuteNumExchange(arg_numRQT, arg_elemList, TRUE, TRUE, arg_interface);
}

void CWinEVPompeModel::cmdEv(const int& nNumEv, const bool& bRelaisActif)
{
    int numRQT = 0;
    if(bRelaisActif)
        numRQT = m_pSupervision->getNumRQTComJBUSMesure(EV_ON + QString::number(nNumEv));
    else
        numRQT = m_pSupervision->getNumRQTComJBUSMesure(EV_OFF + QString::number(nNumEv));

    m_threadPool->start(new CCmdJBusRunnable( this
                                            , numRQT
                                            , m_pSupervision->getCarteMesure()->getListExchange()
                                            , m_pSupervision->getAnalyseur()->m_ExternalInterface));

}
void CWinEVPompeModel::cmdPompe(const int& nNumPompe, const bool& bRelaisActif)
{
    int numRQT = 0;
    if(bRelaisActif)
        numRQT = m_pSupervision->getNumRQTComJBUSMesure(POMPE_ON + QString::number(nNumPompe));
    else
        numRQT = m_pSupervision->getNumRQTComJBUSMesure(POMPE_OFF + QString::number(nNumPompe));

    m_threadPool->start(new CCmdJBusRunnable( this
                                            , numRQT
                                            , m_pSupervision->getCarteMesure()->getListExchange()
                                            , m_pSupervision->getAnalyseur()->m_ExternalInterface));
	
}
void CWinEVPompeModel::cmdConfigPompes()
{
    m_threadPool->start(new CCmdJBusRunnable( this
                                            , m_pSupervision->getNumRQTComJBUSMesure(CONFIG_POMPE)
                                            , m_pSupervision->getCarteMesure()->getListExchange()
                                            , m_pSupervision->getAnalyseur()->m_ExternalInterface));
    m_threadPool->start(new CCmdJBusRunnable( this
                                            , m_pSupervision->getNumRQTComJBUSMesure(CONFIG_VITESSE_POMPE)
                                            , m_pSupervision->getCarteMesure()->getListExchange()
                                            , m_pSupervision->getAnalyseur()->m_ExternalInterface));
	

}
void CWinEVPompeModel::cmdPompesOff()
{
}

void CWinEVPompeModel::setVitessePompe(int arg_numPompe, const QString arg_vit){
	m_listVitessePompe[arg_numPompe] = arg_vit ;
	QString sRq = "10|16|0x0220|10|20";
	QString sValue;
	foreach(sValue, m_listVitessePompe) sRq += "|" + sValue +"0";
	//	_stprintf(szRQ,_T("10|16|0x0220|10|20|300|300|300|300|300|300|300|300|300|300"));
	TCHAR szRQ[MAX_PATH];
	TCHAR szRP[MAX_PATH];

	lstrcpy(szRQ, (TCHAR*)sRq.utf16());
	szRQ[sRq.size()] = _T('\0');
	_stprintf(szRP,_T("10|16|0x0220|10"));

	qDebug() << "setVitessePompe " << QString::fromUtf16((const ushort *)szRQ);
	m_pSupervision->getCarteMesure()->bSetExchangeJbus(szRQ, szRP
			, m_pSupervision->getAnalyseur()
			, m_pSupervision->getNumRQTComJBUSMesure(CONFIG_VITESSE_POMPE));

	m_threadPool->start(new CCmdJBusRunnable( this
                                            , m_pSupervision->getNumRQTComJBUSMesure(CONFIG_VITESSE_POMPE)
                                            , m_pSupervision->getCarteMesure()->getListExchange()
                                            , m_pSupervision->getAnalyseur()->m_ExternalInterface));

}
void CWinEVPompeModel::setSensRotation(int arg_numPompe, bool arg_sensTrigo){
	/*Char sens de rotation
				XX00-> horaire en tour
				XX01-> antihoraire en tour
				XX10-> nombre de pas Horaire
				XX11-> nombre de pas antihoraire 
				X1XX-> Alimentation du moteur au repos
				X0XX-> pas d�alimentation au repos
				1XXX-> Retour position Homing 
				0XXX-> Pas de gestion de la position Homing 
	*/
	int confPompe = m_listConfPompe[arg_numPompe].toInt();
	qDebug() << "setSensRotation avant "<< confPompe;
	if(arg_sensTrigo)
		confPompe = confPompe | 0x01;
	else
		confPompe = confPompe & 0xFE;
	qDebug() << "setSensRotation apres "<< confPompe << " " << arg_sensTrigo;

	m_listConfPompe[arg_numPompe] = QString::number(confPompe);
	initConfPompe();
}
void CWinEVPompeModel::setModeRotation(int arg_numPompe, bool arg_modeTour){
	int confPompe = m_listConfPompe[arg_numPompe].toInt();
	qDebug() << "setModeRotation avant "<< confPompe;
	if(arg_modeTour)
		//confPompe = confPompe & 0xF7;
		confPompe = (confPompe & 0xF7) | 0x02;
	else
		confPompe = confPompe & 0xF5;
	qDebug() << "setModeRotation apres "<< confPompe << " " << arg_modeTour;

	m_listConfPompe[arg_numPompe] = QString::number(confPompe);
	initConfPompe();
}
void CWinEVPompeModel::initConfPompe(){ 
	//m_listConfPompe[arg_numPompe] = arg_conf;
	QString sRq = "10|16|0x0240|10|20";
	QString sValue;
	foreach(sValue, m_listConfPompe) sRq += "|" + sValue;
	//_stprintf(szRQ,_T("10|16|0x0240|10|20|12|12|12|12|12|12|12|12|12|12"));
	TCHAR szRQ[MAX_PATH];
	TCHAR szRP[MAX_PATH];

	lstrcpy(szRQ, (TCHAR*)sRq.utf16());
	szRQ[sRq.size()] = _T('\0');
	_stprintf(szRP,_T("10|16|0x0240|10"));

	qDebug() << "setConfPompe " << QString::fromUtf16((const ushort *)szRQ);
	m_pSupervision->getCarteMesure()->bSetExchangeJbus(szRQ, szRP
			, m_pSupervision->getAnalyseur()
			, m_pSupervision->getNumRQTComJBUSMesure(CONFIG_POMPE));

	m_threadPool->start(new CCmdJBusRunnable( this
                                            , m_pSupervision->getNumRQTComJBUSMesure(CONFIG_POMPE)
                                            , m_pSupervision->getCarteMesure()->getListExchange()
                                            , m_pSupervision->getAnalyseur()->m_ExternalInterface));
	
}
void CWinEVPompeModel::setNbTourPompe(int arg_numPompe, const QString arg_nbtour){ 
	m_listNbTourPompe[arg_numPompe] = arg_nbtour;
	QString sAddrPompe = "0x02"+ QString::number(arg_numPompe*2, 16).rightJustified(2,'0');
	QString sRq = "10|16|"+ sAddrPompe+"|1|2|" + QString::number(arg_nbtour.toInt());
	QString sRp = "10|16|"+ sAddrPompe+"|1";
	
	TCHAR szRQ[MAX_PATH];
	TCHAR szRP[MAX_PATH];

	lstrcpy(szRQ, (TCHAR*)sRq.utf16());
	szRQ[sRq.size()] = _T('\0');
	lstrcpy(szRP, (TCHAR*)sRp.utf16());
	szRP[sRp.size()] = _T('\0');
	

	qDebug() << "setNbTourPompe ON" << QString::fromUtf16((const ushort *)szRQ);
	m_pSupervision->getCarteMesure()->bSetExchangeJbus(szRQ, szRP
			, m_pSupervision->getAnalyseur()
			, m_pSupervision->getNumRQTComJBUSMesure(POMPE_ON + QString::number(arg_numPompe)));

	//Arret -> 0 tour de pompe, m�me Rp que ON
	/*sRq = "10|16|"+ sAddrPompe+"|1|2|0" ;
	lstrcpy(szRQ, (TCHAR*)sRq.utf16());
	szRQ[sRq.size()] = _T('\0');
	qDebug() << "setNbTourPompe OFF" << QString::fromUtf16((const ushort *)szRQ);
	m_pSupervision->getCarteMesure()->bSetExchangeJbus(szRQ, szRP
			, m_pSupervision->getAnalyseur()
			, m_pSupervision->getNumRQTComJBUSMesure(POMPE_OFF + QString::number(arg_numPompe)));*/
}
