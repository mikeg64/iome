#include "IoWFExecutable.h"

IoWFExecutable::IoWFExecutable(char *shost)
{
	m_shost=NULL;
	m_sjobmanager=NULL;
	m_ihostport=22;
	
	//accesspoint info
	m_susername=NULL;
	m_sencrypted_password=NULL;
	SetHost(shost);
}

IoWFExecutable::~IoWFExecutable()
{

}


void IoWFExecutable::SetMethod(char *smethod)
{
	if(m_smethod)
	{
		delete [] m_smethod;
		m_smethod = NULL;
	}


	if(smethod)
	{
		m_smethod = (char *) new char [1+strlen(smethod)];
		strcpy(m_smethod, smethod);
	}		
	
}


void IoWFExecutable::SetCommand(char *scommand)
{
	if(m_scommand)
	{
		delete [] m_scommand;
		m_scommand = NULL;
	}


	if(scommand)
	{
		m_scommand = (char *) new char [1+strlen(scommand)];
		strcpy(m_scommand, scommand);
	}	
	
}


void IoWFExecutable::SetParameters(char *sparameters)
{
	if(m_sparameters)
	{
		delete [] m_sparameters;
		m_sparameters = NULL;
	}


	if(sparameters)
	{
		m_sparameters = (char *) new char [1+strlen(sparameters)];
		strcpy(m_sparameters, sparameters);
	}	
	
}




void IoWFExecutable::SetHost(char *shost)
{
	if(m_shost)
	{
		delete [] m_shost;
		m_shost = NULL;
	}


	if(shost)
	{
		m_shost = (char *) new char [1+strlen(shost)];
		strcpy(m_shost, shost);
	}	
	
}

void IoWFExecutable::SetJobmanager(char *sjobmanager)
{
	if(m_sjobmanager)
	{
		delete [] m_sjobmanager;
		m_sjobmanager = NULL;
	}


	if(sjobmanager)
	{
		m_sjobmanager = (char *) new char [1+strlen(sjobmanager)];
		strcpy(m_sjobmanager, sjobmanager);
	}	
		
	
}

    
void IoWFExecutable::SetUsername(char *susername)
{
	if(m_susername)
	{
		delete [] m_susername;
		m_susername = NULL;
	}


	if(susername)
	{
		m_susername = (char *) new char [1+strlen(susername)];
		strcpy(m_susername, susername);
	}		
	
}

void IoWFExecutable::SetEncryptedpassword(char *sencpasswd)
{
	if(m_sencrypted_password)
	{
		delete [] m_sencrypted_password;
		m_sencrypted_password = NULL;
	}


	if(sencpasswd)
	{
		m_sencrypted_password = (char *) new char [1+strlen(sencpasswd)];
		strcpy(m_sencrypted_password, sencpasswd);
	}		
	
}

/*CIoWFSimulantPort *IoWFExecutable::GetInPort(int id)
{
	CIoWFSimulantPort *port=NULL;
	if((id>=0) && id<(m_pInputPorts.size()))
		port=m_pInputPorts[id];
	return port;	
}

CIoWFSimulantPort *IoWFExecutable::GetOutPort(int id)
{
	CIoWFSimulantPort *port=NULL;
	if((id>=0) && id<(m_pOutputPorts.size()))
		port=m_pOutputPorts[id];
    return port;	
}

void IoWFExecutable::AddInPort(int portid, char *type)
{
	if(type && (portid >=0))
		m_pInputPorts.push_back(new CIoWFSimulantPort(portid, type));	
}

void IoWFExecutable::AddOutPort(int portid, char *type)
{
	if(type && (portid >=0))
		m_pOutputPorts.push_back(new CIoWFSimulantPort(portid, type));
}
*/
