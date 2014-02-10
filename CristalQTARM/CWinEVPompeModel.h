#ifndef CWIN_EV_POMPE_MODEL
#define CWIN_EV_POMPE_MODEL

#include "CCardJBusModel.h"
#include <QObject>
#include <QVector>

class CWinEVPompeView;
class CSupervision;
class CStreamModel;

class QThreadPool;
class QString;
class QRunnbale;
class QMutex;

class CWinEVPompeModel: public QObject, CCardJBusModel
{
	Q_OBJECT
public:
    CWinEVPompeModel(CSupervision* argpSupervision);//, CWinEVPompeView* argpView);
   
    void cmdEv(const int& nNumEv, const bool& bRelaisActif);
    void cmdPompe(const int& nNumPompe, const bool& bRelaisActif);
    void cmdConfigPompes();
    void cmdPompesOff();
    QString getPumpLabel(const int& nNumPump)const{return m_vPumpLabels.at(nNumPump);};
    QString getEVLabel(const int& nNumEV)const{return m_vEVLabels.at(nNumEV);};
    QVector<QString> getVectorPumpLabels()const{return m_vPumpLabels;};
    QVector<QString> getVectorEVLabels()const{return m_vEVLabels;};

    void sendCmdJBus(const int& arg_numRQT, CElemList* arg_elemList, CEnumInterface& arg_interface);
	
	QString getVitessePompe(int arg_numPompe)const{return m_listVitessePompe.at(arg_numPompe);};
	QString getConfPompe(int arg_numPompe)const{return m_listConfPompe.at(arg_numPompe);};
	QString getNbTourPompe(int arg_numPompe)const{return m_listNbTourPompe.at(arg_numPompe);};

	void setVitessePompe(int arg_numPompe, const QString arg_vit);
	void initConfPompe();
	void setSensRotation(int arg_numPompe, bool arg_sensTrigo);
	void setModeRotation(int arg_numPompe, bool arg_modeTour);
	void setNbTourPompe(int arg_numPompe, const QString arg_nbtour);

private:
	//Coté supervision connexion aux données
    CSupervision* m_pSupervision;
    CWinEVPompeView* m_pView;
    CElemCycleStep m_cycleStep;
    
    QVector<QString> m_vPumpLabels;
    QVector<QString> m_vEVLabels;

	QList<QString> m_listVitessePompe;
	QList<QString> m_listConfPompe;
	QList<QString> m_listNbTourPompe;

    QThreadPool* m_threadPool;
    QMutex* m_mutex;
};

#endif