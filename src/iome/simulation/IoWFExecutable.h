#ifndef IOWFEXECUTABLE_H_
#define IOWFEXECUTABLE_H_

//#include "CIoWFSimulantPort.h"
#ifndef IO_MSVC
	#include <iome/utils/IoParams.h>
#else
	#include <iome/utils/IoParams.h>
#endif





class IoWFExecutable
{
public:
	IoWFExecutable(char *shost="localhost");
	virtual ~IoWFExecutable();
	
	//host info
	char *m_shost;
	char *m_sjobmanager;
	char *m_scommand;
	char *m_smethod;
	char *m_sparameters;
	int m_ihostport;
	
	//accesspoint info
	char *m_susername;
	char *m_sencrypted_password;
	
	char *GetMethod(){return m_smethod;}
	char *GetCommand(){return m_scommand;}
	char *GetParameters(){return m_sparameters;}
	
	void SetMethod(char *smethod);
    void SetCommand(char *scommand);
    void SetParameters(char *sparameters);
    char *GetHost(){return m_shost;}
    char *GetJobmanager(){return m_sjobmanager;}
    int GetHostport(){return m_ihostport;}
    
    char *GetUsername(){return m_susername;}
    char *GetEncryptedpassword(){return m_sencrypted_password;}

    void SetHost(char *shost);
    void SetJobmanager(char *sjobmanager);
    void SetHostport(int iid){m_ihostport=(iid>=0?iid:m_ihostport);}
    
    void SetUsername(char *susername);
    void SetEncryptedpassword(char *sencpasswd);





	/*CIoWFSimulantPort *GetInPort(int id);
	CIoWFSimulantPort *GetOutPort(int id);

	void AddInPort(int portid, char *type);
	void AddOutPort(int portid, char *type);


	char *GetInPortPortType(int id);
	int GetInPortPort(int id);
	int GetInPortParamID(int id);
	char *GetInPortURL(int id);
	char *GetInPortUsername(int id);
	char *GetInPortEncPassword(int id);
	
	char *GetOutPortPortType(int id);
	int GetOutPortPort(int id);
	int GetOutPortParamID(int id);
	char *GetOutPortURL(int id);
	char *GetOutPortUsername(int id);
	char *GetOutPortEncPassword(int id);
	
	void SetInPortPortType(int id, char *sporttype);
	void SetInPortPort(int id, int iport);
	void SetInPortParamID(int id, int iparamid);
	void SetInPortURL(int id, char *surl);
	void SetInPortUsername(int id, char *susername);
	void SetInPortEncPassword(int id, char *spassword);	

	
	void SetOutPortPortType(int id, char *sporttype);
	void SetOutPortPort(int id, int iport);
	void SetOutPortParamID(int id, int iparamid);
	void SetOutPortURL(int id, char *surl);
	void SetOutPortUsername(int id, char *susername);
	void SetOutPortEncPassword(int id, char *spassword);*/	
	
};

#endif /*IOWFEXECUTABLE_H_*/
