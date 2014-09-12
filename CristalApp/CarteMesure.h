#pragma once
#include "network.h"
////////////////////////////////////////////////////////////////////////////
// CSerialPort window
class CCarteMesure : public CSerialPort
{
#ifdef TEST
	Q_OBJECT
#endif
public:
	CCarteMesure();
	virtual ~CCarteMesure();
	BOOL bReadConfig(LPCTSTR pszFileName,CListStream *pListStream);
	BOOL bWriteConfig(LPCTSTR pszFileName);

protected:
    //virtual DWORD RunThread();
#ifdef TEST

public slots:
	void run();
#else
	virtual void run();
#endif
};

/////////////////////////////////////////////////////////////////////////////
