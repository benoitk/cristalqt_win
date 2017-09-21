#include "stdafx.h"
#include "header.h"
#include "header_qt.h"

/////////////////////////////////////////////////////////////////////////////
// CCarteIO
////////////////////////////////////////////////////////////////
/*@!************************************************************************
* NOM:                      CCarteIO:CCarteIO
* ROLE:                     Constructeur de la classe CCarteIO
* ALGORITHME:
*    Point d'entree
*    Initialisation des membres de la classe
*    Point de sortie
***********************************************************************@!)*/

CCarteIO::CCarteIO():CSerialPort(), m_parentCarteIO(NULL), m_ElemCycleStep(&m_parentCarteIO)
{
	m_parentCarteIO.SetLabel(_T("Carte IO"));
	m_bNumInterface = NUM_INTERFACE_CARTE_IO_MIN;
	m_bCanRead = FALSE;
	m_bCanWrite = TRUE;
	m_dwDelay = 3000;
	m_ExternalInterface.SetExternalInterface(NULL,this,NULL,NULL);
	m_nNumPort = 2;
}


/*@!************************************************************************
* NOM:                      CCarteIO::~CCarteIO
* ROLE:                     Destructeur de la classe client
* ALGORITHME:
***********************************************************************@!)*/
CCarteIO::~CCarteIO()
{
}


/******************************************************************************
 * @func :	ReadConfig
 * 
 * Rôle  :	Initialisation de donnees membres
 * @parm :	LPCSTR | szIni | fichier de configuration
 *****************************************************************************/
BOOL CCarteIO::bReadConfig(LPCTSTR pszFileName,CListStream *pListStream)
{
	BOOL bReturn;

	bReturn = CSerialPort::bReadConfig(pszFileName);
#ifndef TEST
	m_dwDelay = iGetPrivateProfileInt(_T("Config"), _T("m_dwDelay"), m_dwDelay, pszFileName);
	if (bReturn)
	{
		bReturn = m_ElemCycleStep.bReadConfig(_T("0"),pszFileName,pListStream);
	}
#else
	HANDLE hf  ;
	long filelen = openFile(pszFileName, hf);

	m_dwDelay = iGetPrivateProfileInt(_T("Config"), _T("m_dwDelay"), m_dwDelay, hf, filelen);
	_tprintf(_T(" CSerialPort::iGetPrivateProfileInt( %d \n "), m_dwDelay);
	_tprintf(_T(" CSerialPort::iGetPrivateProfileInt( %d \n "), hf);

	if (bReturn)
	{
		bReturn = m_ElemCycleStep.bReadConfig(_T("0"),hf, filelen,pListStream);
		_tprintf(_T(" m_ElemCycleStep %d \n "), bReturn);
	}
	closeFile(hf);
#endif
	if (!bReturn) 
	{
		_tprintf(_T(" Ierror "));
		TRACE_DEBUG(eDebug,eConfig,_T(__FILE__),_T(__FUNCTION__),__LINE__,_T("BOOL CCarteIO::bReadConfig"));
		TRACE_DEBUG_IHM(eError,eConfig,eErrorCarteIOReadConfig);
	}

	return bReturn;
}


/******************************************************************************
 * @func :	bWriteConfig
 * 
 * Rôle  :	enregistre la configuration dans un fichier
 * @parm :	LPCSTR | szIni | fichier de configuration
 *****************************************************************************/
BOOL CCarteIO::bWriteConfig(LPCTSTR pszFileName)
{
	BOOL bReturn;

	bReturn = CSerialPort::bWriteConfig(pszFileName);
	if (bReturn) bReturn = bWritePrivateProfileInt(_T("Config"),_T("m_dwDelay"),m_dwDelay,pszFileName);
	if (bReturn) bReturn = m_ElemCycleStep.bWriteConfig(_T("0"),pszFileName);

	if (!bReturn) 
	{
		TRACE_DEBUG(eDebug,eConfig,_T(__FILE__),_T(__FUNCTION__),__LINE__,_T("BOOL CCarteIO::bWriteConfig"));
		TRACE_DEBUG_IHM(eError,eConfig,eErrorCarteIOWriteConfig);
	}

	return TRUE;
}


//DWORD CCarteIO::RunThread()
void CCarteIO::run()
{
	
	//TRACE_LOG_MSG(_T("! pCarteIO->start(); ok !"));
	m_bInRunThread = TRUE;
	/*while(1){Sleep(1000);}*/
	m_bRun = bOpen();
    qDebug() << "Interface : " << this->m_bNumInterface << " Thread : " << QThread::currentThreadId  ();

	
	while (m_bRun)
	{
		if (m_ElemCycleStep.bExecuteBegin(m_bCanRead,m_bCanWrite,m_ExternalInterface))
		{
			m_bError = FALSE;
		}
		else
		{
			TRACE_DEBUG(eDebug,eComJBusMaster,_T(__FILE__),_T(__FUNCTION__),__LINE__,_T("BOOL CCarteIO::RunThread"));
			TRACE_DEBUG_IHM(eError,eComJBusMaster,eErrorCarteIOExecute);
			m_bError = TRUE;
		}
		Sleep(m_dwDelay);
		if (m_ElemCycleStep.bExecuteEnd(m_bCanRead,m_bCanWrite,m_ExternalInterface))
		{
		}
		else
		{
			TRACE_DEBUG(eDebug,eComJBusMaster,_T(__FILE__),_T(__FUNCTION__),__LINE__,_T("BOOL CCarteIO::RunThread"));
			TRACE_DEBUG_IHM(eError,eComJBusMaster,eErrorCarteIOExecute);
		}
		Sleep(m_dwDelay);
		while (m_bPause && m_bRun) Sleep(m_dwDelay);
	}
	Close();

//	return 0;
}


void CCarteIO::Stop()
{
	CSerialPort::Stop();
}

