#ifndef IOPROC_H_
#define IOPROC_H_

#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>

class CIoProc
{
public:
	CIoProc(int id, int isimulantid, char *simulantmap=NULL);
	virtual ~CIoProc();
	
	int m_id;
	char *m_shostname;
	int m_isimulantid;
	char *m_ssimulantmap;
	
	int GetID(){return m_id;}
	char *GetHostname(){return m_shostname;}
	int GetSimulantID(){return m_isimulantid;}
	char *GetSimulantMap(){return m_ssimulantmap;}
	
	void SetID(int id){(id>=0?m_id=id:m_id=0);}
	void SetHostname(char *shostname);
	void SetSimulantID(int isid){(isid>=0?m_isimulantid=isid:m_isimulantid=0);}
	void SetSimulantMap(char *ssimulantmap);
};

#endif /*IOPROC_H_*/
