#ifndef CIOSIMULANTPORT_H_
#define CIOSIMULANTPORT_H_

#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>
#include "IoSimulant.h"

class CIoSimulantPort
{
public:
	CIoSimulantPort(CIoSimulantPort *port=NULL);
	virtual ~CIoSimulantPort();
	
	int m_paramid;
	string m_sparammap;

	int m_ientitysetid;
	int m_ientityid;
	
	int m_isimulantid;
	string m_ssimulantmap;

	CIoSimulant *m_simulant;
	
	void SetParamID(int ipid){m_paramid=(ipid>=0?ipid:m_paramid);}
	void SetEntitySetID(int iesid){m_ientitysetid=(iesid>=0?iesid:m_ientitysetid);}

	void SetParammap(string parammap);
	int GetParamID(){return m_paramid;}
	string GetParammap(){return m_sparammap;}
	
	void SetSimulantID(int isid){m_isimulantid=(isid>=0?isid:m_isimulantid);}
	void SetSimulantmap(string ssimulantmap);
	int GetSimulantID(){return m_isimulantid;}
	string GetSimulantmap(){return m_ssimulantmap;}
	
	int GetEntitySetID(){return m_ientitysetid;}
	
};

#endif /*CIOWFSIMULANTPORT_H_*/
