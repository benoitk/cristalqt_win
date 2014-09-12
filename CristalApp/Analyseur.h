#pragma once
#include "Network.h"
class CAnalyseur : public CListStream
{
	Q_OBJECT
public:
	int getIndexSeq()const{return m_indexSeqence;};
	int getTimeElapse()const{return m_iTimeElapse;};
	CAnalyseur();
	virtual ~CAnalyseur();


protected:
    //virtual DWORD RunThread();
   
public slots:
	void run();

private :
	int m_indexSeqence;
	int m_iTimeElapse;
};

			 




