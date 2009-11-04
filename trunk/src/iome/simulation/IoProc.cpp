#include <iome/simulation/IoProc.h>

CIoProc::CIoProc(int id, int isimulantid, char *simulantmap)
{
	SetID(id);
	m_shostname=NULL;
	SetSimulantMap(simulantmap);
	SetSimulantID(isimulantid);
}

CIoProc::~CIoProc()
{

}


void CIoProc::SetHostname(char *shostname)
{
	if(m_shostname)
	{
		delete [] m_shostname;
		m_shostname = NULL;
	}


	if(shostname)
	{
		m_shostname = (char *) new char [1+strlen(shostname)];
		strcpy(m_shostname, shostname);
	}	
	
}

void CIoProc::SetSimulantMap(char *ssimulantmap)
{
	if(m_ssimulantmap)
	{
		delete [] m_ssimulantmap;
		m_ssimulantmap = NULL;
	}


	if(ssimulantmap)
	{
		m_ssimulantmap = (char *) new char [1+strlen(ssimulantmap)];
		strcpy(m_ssimulantmap, ssimulantmap);
	}	
		
}

