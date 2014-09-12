#pragma once
#ifdef TEST
#include <QObject>
#include "network.h"
#endif
////////////////////////////////////////////////////////////////////////////
// CSerialPort window
class CCarteIO : public CSerialPort
{
#ifdef TEST
	Q_OBJECT
#endif
public:
	CCarteIO();
	
	
	BOOL bReadConfig(LPCTSTR pszFileName,CListStream *pListStream);
	BOOL bWriteConfig(LPCTSTR pszFileName);
#ifndef TEST
	virtual ~CCarteIO();
	virtual void Stop();
	virtual void run();
#else
	~CCarteIO();
public slots:
    
	void run();
	void Stop();
#endif
protected:
    //virtual DWORD RunThread();

public:
	CElemCycleStep m_ElemCycleStep;
protected:
	DWORD m_dwDelay;
};

/////////////////////////////////////////////////////////////////////////////
