#pragma once
#include "network.h"

////////////////////////////////////////////////////////////////////////////
// CSerialPort window
#define NBR_CMD_WRITE_JBUS_SLAVE_MAX		300
#define NBR_CMD_READ_JBUS_SLAVE_MAX			300

#define BASE_ADDR_WRITE						0x8600
#define BASE_ADDR_READ						0x8610

class CCarteJbusSlave : public CSerialPort
{
#ifdef TEST
	Q_OBJECT
#endif
public:
	CCarteJbusSlave();
	virtual ~CCarteJbusSlave();
	virtual BOOL bRead(BYTE* lpData,long lSizeDataMax,long *plNbrLu,BOOL bByPass);
	BOOL bReadConfig(LPCTSTR pszFileName,CListStream *pListStream);
	BOOL bWriteConfig(LPCTSTR pszFileName);

public:
	CElemList m_ListDataCanRead;
	CElemList m_ListDataCanWrite;

protected:
	virtual long lDispatchTrame(BYTE* lpData,long lSizeTotal);
#ifdef TEST

public slots:
	void run();
#else
	virtual void run();
#endif
};

/////////////////////////////////////////////////////////////////////////////
