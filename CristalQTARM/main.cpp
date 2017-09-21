#include <QtGui/QApplication>
#include <QFile>
 //#include <QDebug>
//#include <QFontDatabase>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "CWinMainControler.h"
#include "stdafx.h"
#include "header.h"
#include "wincrypt.h"
#include <windows.h>
#include <stdio.h>
#include <winioctl.h > 


//#include "CThreadIHM.h"
//typedef BOOL (__stdcall *GetSystemMemoryDivisionProc)(LPDWORD,LPDWORD,LPDWORD);
//typedef DWORD (__stdcall *SetSystemMemoryDivisionProc)(DWORD);


DWORD __stdcall ThreadEntryPoint(LPVOID lpParam)
{
	while (1)
	{
		Sleep(1000);
		_tprintf(_T("tick\n"));
	}
	return 0;
}

int main(int argc, char *argv[])
{
//	_tprintf(_T("MAIN %d"), privateHeap);
	

#ifndef TEST
	TCHAR szText[MAX_PATH];
	//TCHAR szMessage[260];
	//HANDLE hCristalAppOnce = NULL;
	BOOL bReturn;
	CAnalyseur* pAnalyseur = new CAnalyseur();
	
	CSocketIHM* pSocketIHM = new CSocketIHM();
	CCarteIO* pCarteIO = new CCarteIO();
    CCarteMesure* pCarteMesure = new CCarteMesure();
	CCarteJbusSlave* pCarteJbusSlave = new CCarteJbusSlave();
	//CThreadIHM* pThreadIhm = new CThreadIHM(argc, argv, pAnalyseur, pCarteIO, pCarteMesure, pSocketIHM);
	
	//Initialise la taille de la m�moire
	//int nStoragePages = 128; // x4 donne la taille en Ko affect� au stockage.

	//HINSTANCE hCoreDll = LoadLibrary(_T("coredll.dll"));
	//SetSystemMemoryDivisionProc procSet = (SetSystemMemoryDivisionProc)GetProcAddress(
	//														hCoreDll, _T("SetSystemMemoryDivision"));

	//DWORD dwResult = procSet(nStoragePages);

	////Process result code

	//FreeLibrary(hCoreDll);

	// protection lancement multiple
	/*hCristalAppOnce = OpenEvent(EVENT_ALL_ACCESS,FALSE,_T("CRISTAL_APP_ONCE"));
	if (hCristalAppOnce)cd 
	{
		CloseHandle(hCristalAppOnce);
		return -1;
	}
	else hCristalAppOnce = CreateEvent(NULL,TRUE,FALSE,_T("CRISTAL_APP_ONCE"));*/

	//DWORD size = 10*2*1024*1024; // (or more) (2*1024*1024)=2Mo

	//void *p = VirtualAlloc(0, size, MEM_RESERVE, PAGE_NOACCESS);
	//p = VirtualAlloc(p, size, MEM_COMMIT, PAGE_READWRITE);

	_tprintf(_T(" CHARGEMENT CONFIGURATION...\n\n"));

	pAnalyseur->m_ExternalInterface.SetExternalInterface(pSocketIHM,pCarteIO,pCarteMesure,pCarteJbusSlave);
	pSocketIHM->m_ExternalInterface.SetExternalInterface(pSocketIHM,pCarteIO,pCarteMesure,pCarteJbusSlave);
	pSocketIHM->SetAccess(TRUE,TRUE);
	
	// chargement config
	bReturn = bCopyFile(szGetFullPathName(_T("MsgErrorIHM.ini"),szText),SZ_FIC_TEMP,FALSE);
	if (bReturn) ReadConfigMsgError(SZ_FIC_TEMP);
	if (bReturn) bReturn = bCopyFile(szGetFullPathName(_T("config.ini"),szText),SZ_FIC_TEMP,FALSE);
 	if (bReturn) bReturn = pAnalyseur->bReadConfig(SZ_FIC_TEMP);
	/*if (bReturn) TRACE_LOG_MSG(_T("lecture config.ini DONE !"));	
	else TRACE_LOG_MSG(_T("pinage !"));	*/
	
	if (bReturn) bReturn = pAnalyseur->bReadCycle(SZ_FIC_TEMP);
	//TRACE_LOG_MSG(_T("lecture fichiers cycles DONE !"));	
	

	//if (bReturn) bReturn = bCopyFile(szGetFullPathName(_T("InterfaceIHM.ini"),szText),SZ_FIC_TEMP,FALSE);
	//if (bReturn) bReturn = pSocketIHM->bReadConfig(SZ_FIC_TEMP,pAnalyseur);

	/*if (bReturn) bReturn = bCopyFile(szGetFullPathName(_T("InterfaceIO.ini"),szText),SZ_FIC_TEMP,FALSE);
	if (bReturn) bReturn = pCarteIO->bReadConfig(SZ_FIC_TEMP,pAnalyseur);
	if (bReturn) bReturn = bCopyFile(szGetFullPathName(_T("InterfaceMesure.ini"),szText),SZ_FIC_TEMP,FALSE);
	if (bReturn) bReturn = pCarteMesure->bReadConfig(SZ_FIC_TEMP,pAnalyseur);
	if (bReturn) bReturn = bCopyFile(szGetFullPathName(_T("InterfaceJbusSlave.ini"),szText),SZ_FIC_TEMP,FALSE);
	if (bReturn) bReturn = pCarteJbusSlave->bReadConfig(SZ_FIC_TEMP,pAnalyseur);*/
	if (bReturn) bReturn = pCarteIO->bReadConfig(szGetFullPathName(_T("InterfaceIO.ini"),szText),pAnalyseur);
	//TRACE_LOG_MSG(_T("lecture InterfaceIO.ini DONE !"));	
	

	if (bReturn) bReturn = pCarteMesure->bReadConfig(szGetFullPathName(_T("InterfaceMesure.ini"),szText),pAnalyseur);
	//TRACE_LOG_MSG(_T("lecture InterfaceMesure.ini DONE !"));	
	

	if (bReturn) bReturn = pCarteJbusSlave->bReadConfig(szGetFullPathName(_T("InterfaceJbusSlave.ini"),szText),pAnalyseur);
	//TRACE_LOG_MSG(_T("lecture InterfaceJbusSlave.ini DONE !"));	
		
	/*TRACE_LOG_MSG(_T("! DONE !"));
	while(1){Sleep(1000);}*/
	_tprintf(_T("****************************************\n"));
	_tprintf(_T("* BILAN DES TESTS CONFIG ANALYSEUR: %s *\n"),bReturn ? _T("OK") : _T("KO"));
	_tprintf(_T("****************************************\n\n"));

	TRACE_LOG_MSG(_T("APPLICATION STARTED"));
	
	TCHAR ch;
	if (bReturn)
	{
		/*DWORD m_dwThreadID = 0;
		while ( ::CreateThread(NULL, 0,ThreadEntryPoint, NULL, 0, &m_dwThreadID) == NULL)
		{
			
			_tprintf(_T("CreateThread failed: 0x%08x\n"),GetLastError());
			Sleep(1000);
		}
		_tprintf(_T("CreateThread success\n"));
		while (1)
		{
			Sleep(1000);
			_tprintf(_T("main tick\n"));
		}*/
		QApplication a(argc, argv);
		//while (!pSocketIHM->bGetInRunThread()) Sleep(1000);
		//TRACE_LOG_MSG(_T("SocketIHM STARTED"));*/
        pCarteIO->setStackSize(64000);
		pCarteIO->start();
		while (!pCarteIO->bGetInRunThread()) Sleep(1000);
		TRACE_LOG_MSG(_T("CarteIO STARTED"));
           
        pCarteMesure->setStackSize(64000);
        pCarteMesure->start();
		while (!pCarteMesure->bGetInRunThread()) Sleep(1000);
		TRACE_LOG_MSG(_T("CarteMesure STARTED"));
     
        pCarteJbusSlave->setStackSize(64000);
		pCarteJbusSlave->start();
		while (!pCarteJbusSlave->bGetInRunThread()) Sleep(1000);
		TRACE_LOG_MSG(_T("CarteJbusSlave STARTED"));

        pAnalyseur->setStackSize(64000);
  		pAnalyseur->start();
		TRACE_LOG_MSG(_T("Analyseur STARTED"));
		
		/*pThreadIhm->setStackSize(64000);
		pThreadIhm->start();
		while (!pThreadIhm->bGetInRunThread()) Sleep(1000);
		TRACE_LOG_MSG(_T("pThreadIhm STARTED"));
		while(pThreadIhm->isRunning()) Sleep(5000);*/
		
		_tprintf(_T("* Appuyer sur la touche <ENTER> pour quitter l'application: %s *\n"),bReturn ? _T("OK") : _T("KO"));
		
		
		
		QTranslator qtTranslator;
		if(qtTranslator.load("cristalqtarm_en.qm"))
				qDebug() << "Fichier anglais charg�" ;
        else if(qtTranslator.load("cristalqtarm_ru.qm"))
				qDebug() << "Fichier anglais charg�" ;
		a.installTranslator(&qtTranslator);

		//chargement stylesheet
#ifdef RES_640_480
		QFile file(":/CristalQTARM/qss/cristalX86.qss");
#else
		QFile file(":/CristalQTARM/qss/cristal.qss");
#endif
		file.open(QFile::ReadOnly);
		a.setStyleSheet(QLatin1String(file.readAll()));
		
		CWinMainControler* pControler= new CWinMainControler(pAnalyseur, pCarteIO,pCarteMesure, pSocketIHM);
		pControler->execControler();
		
		a.exec();
	}
#else
	
	_tprintf(_T("AV no yoo RIEN %d"), privateHeap);
	
	QApplication *a = new QApplication(argc, argv);
	QTranslator qtTranslator;
	if(qtTranslator.load("cristalqtarm_en.qm"))
			qDebug() << "Fichier anglais charg�" ;
    else if(qtTranslator.load("cristalqtarm_ru.qm"))
			qDebug() << "Fichier anglais charg�" ;
	a->installTranslator(&qtTranslator);

		//chargement stylesheet
#ifdef RES_640_480
		QFile file(":/CristalQTARM/qss/cristalX86.qss");
#else
		QFile file(":/CristalQTARM/qss/cristal.qss");
#endif
		file.open(QFile::ReadOnly);
		a->setStyleSheet(QLatin1String(file.readAll()));

	TCHAR szText[MAX_PATH];
	//TCHAR szMessage[260];
	//HANDLE hCristalAppOnce = NULL;
	BOOL bReturn = TRUE;
	CAnalyseur* pAnalyseur = new CAnalyseur();
	QThread* thread_a = new QThread;
	pAnalyseur->moveToThread(thread_a);
	QObject::connect(thread_a, SIGNAL(started()), pAnalyseur, SLOT(run()));
	
	CSocketIHM* pSocketIHM = new CSocketIHM();
	
	CCarteIO* pCarteIO = new CCarteIO();
	QThread* thread_io = new QThread;
	pCarteIO->moveToThread(thread_io);
    QObject::connect(thread_io, SIGNAL(started()), pCarteIO, SLOT(run()));

	CCarteMesure* pCarteMesure = new CCarteMesure();
	QThread* thread_Mesure = new QThread;
	pCarteMesure->moveToThread(thread_Mesure);
	QObject::connect(thread_Mesure, SIGNAL(started()), pCarteMesure, SLOT(run()));

	CCarteJbusSlave* pCarteJbusSlave = new CCarteJbusSlave();
	QThread* thread_Jbus = new QThread;
	pCarteJbusSlave->moveToThread(thread_Jbus);
	QObject::connect(thread_Jbus, SIGNAL(started()), pCarteJbusSlave, SLOT(run()));

	CWinMainControler* pControler = new CWinMainControler(pAnalyseur, pCarteIO,pCarteMesure, pSocketIHM);
	QThread* thread_test = new QThread;
	pControler->moveToThread(thread_test);
	QObject::connect(thread_test, SIGNAL(started()), pControler, SLOT(load()));
	
	
	_tprintf(_T(" CHARGEMENT CONFIGURATION...\n\n"));

	pAnalyseur->m_ExternalInterface.SetExternalInterface(pSocketIHM,pCarteIO,pCarteMesure,pCarteJbusSlave);
	pSocketIHM->m_ExternalInterface.SetExternalInterface(pSocketIHM,pCarteIO,pCarteMesure,pCarteJbusSlave);
	pSocketIHM->SetAccess(TRUE,TRUE);
	
	// chargement config
	if (bReturn) ReadConfigMsgError(szGetFullPathName(_T("MsgErrorIHM.ini"),szText));
	
 	/*if (bReturn) bReturn = pAnalyseur->bReadConfig(szGetFullPathName(_T("config.ini"),szText));
	TRACE_LOG_MSG(_T("lecture config.ini DONE !"));	
	
	if (bReturn) bReturn = pAnalyseur->bReadCycle(szGetFullPathName(_T("config.ini"),szText));
	TRACE_LOG_MSG(_T("lecture fichiers cycles DONE !"));	*/
	
	thread_io->start();
	while (!pCarteIO->bGetInRunThread()){ Sleep(1000);}
	TRACE_LOG_MSG(_T("CarteIO STARTED"));     
	
    thread_Mesure->start();
	while (!pCarteMesure->bGetInRunThread()) Sleep(1000);
	TRACE_LOG_MSG(_T("CarteMesure STARTED"));
	
	thread_Jbus->start();
	while (!pCarteJbusSlave->bGetInRunThread()) Sleep(1000);
	TRACE_LOG_MSG(_T("CarteJbusSlave STARTED"));

	thread_test->start();

	thread_a->start();
	TRACE_LOG_MSG(_T("Analyseur STARTED"));
		
	for(int i=0; i<25; ++i){Sleep(1000);}

	if (bReturn) bReturn = pCarteIO->bReadConfig(szGetFullPathName(_T("InterfaceIO.ini"),szText),pAnalyseur);
	TRACE_LOG_MSG(_T("lecture InterfaceIO.ini DONE !"));	

	if (bReturn) bReturn = pCarteMesure->bReadConfig(szGetFullPathName(_T("InterfaceMesure.ini"),szText),pAnalyseur);
	TRACE_LOG_MSG(_T("lecture InterfaceMesure.ini DONE !"));	
	

	if (bReturn) bReturn = pCarteJbusSlave->bReadConfig(szGetFullPathName(_T("InterfaceJbusSlave.ini"),szText),pAnalyseur);
	TRACE_LOG_MSG(_T("lecture InterfaceJbusSlave.ini DONE !"));	
	
	_tprintf(_T("* Appuyer sur la touche <ENTER> pour quitter l'application: %s *\n"),bReturn ? _T("OK") : _T("KO"));
		
	
		
		/*CWinMainControler* pControler= new CWinMainControler(pAnalyseur, pCarteIO,pCarteMesure, pSocketIHM);
		pControler->execControler();*/
		
		while(1){Sleep(1000);}
		a->exec();
#endif
			
		_tprintf(_T("* Arr�t des process ..."));
		pAnalyseur->Stop();
        delete pAnalyseur;
		_tprintf(_T("."));
		pCarteMesure->Stop();
        delete pCarteMesure;
		_tprintf(_T("."));
		pCarteIO->Stop();
        delete pCarteIO;
		_tprintf(_T("."));
		pCarteJbusSlave->Stop();
        delete pCarteJbusSlave;
		_tprintf(_T("."));
		pSocketIHM->Stop();
        delete pSocketIHM;
		_tprintf(_T("."));
		

	
	return 0;
}
