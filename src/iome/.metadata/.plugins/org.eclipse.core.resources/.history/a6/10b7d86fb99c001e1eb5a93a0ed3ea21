#ifndef IO_WFSIMULATION_SIMULATION_H
#define IO_WFSIMULATION_SIMULATION_H
/*
IOME LICENSE
IOME Version 1.1.1

IOME Development  Tools
Copyright (C) 2001-2004, Michael Kenneth Griffiths, All Rights Reserved.

--------------------------------------------------------------------------------
IOME public license.

The contents of this file are subject to the IOME Public License Version 1.3
(the "License"); you may not use this file except in compliance with the
License. You may obtain a copy of the License at
http://81.174.178.112/iome/licensing/iomelicense.html
Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the License.

The Initial Developer of the Original Code is Michael Kenneth Griffiths.
Copyright (C) 2000-2004 Michael Kenneth Griffiths. All Rights Reserved.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
mikeg@photon0.freeserve.co.uk
--------------------------------------------------------------------------------
*/
// IoSimulation.h: interface for the CIoXMLSimulation class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_IOSIMULATION_H__0C90F4FD_B515_497F_807F_EC47DE354F3C__INCLUDED_)
//#define AFX_IOSIMULATION_H__0C90F4FD_B515_497F_807F_EC47DE354F3C__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
#ifndef IO_MSVC
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/wait.h>
#else
	#include <windows.h>  //not sure if this is required??
	#include <process.h>
#endif
#include <iostream>
#include <fstream>
#include "soapH.h"
//#include "IoSteerWS.nsmap" //gave linker errors may need to include in header for final application
#include <pthread.h>

#include "IoSimulator.h"
#include "IoXMLSimulation.h"
#include "CIoWFModel.h"
#include "IoProc.h"

struct simparstruct
{
	CIoSimulation *psimulation;
	CIoSimulant *psimulant;	
};



typedef CIoProc * PROCPTR;
typedef deque<PROCPTR> dqprocptr;


class CIoWFSimulation :
	public CIoXMLSimulation
{
public:
	CIoWFSimulation(void);
	~CIoWFSimulation(void);
	char *m_sbuffer; //string buffer for messaging

	//The distributed simulation runs on a master server and has a number of slaves
	//to start the simulation we start n copies of the simulation on each host
	//each simulation has the same copy of the simulation file and any required config files
	
	//each slave process makes a web service request 
	//GetProcID("hostname")

	//procid hostname simulantid simulantmap
	
	int m_isteercheckpoint; //0=off 1=on
	int m_isteerlog;  //0=off 1=on 2=full
	CIoConfigDOMBuilder *m_pDOMSteerState;
	
	#ifndef IO_XERCESCVERSION
	    xercesc_2_7::DOMDocument *m_pSteerStateDOM;
	#else  	
		IO_XERCESCVERSION::DOMDocument *m_pSteerStateDOM;
	#endif
	//Used to store state information
	//used when undertaking analysis and when transforming stet output information
	SIMULANT_LIST m_lSteerStateList;
	SIMULANT_LIST::iterator m_lSteerStateIterator;
	SIMULANT_LIST::size_type m_steerstatesize;
	

	deque<PROCPTR> m_pProcs;

     //All the simulations get state information they require from 
    //the master simulation
	char *m_sMasterServerHost;
	char *m_sMyHostname;

	string m_sHostname;
	int m_iMasterServerPort;

	//procid and nprocs below nolonger used replaced with that defined in IOSimulation
	int m_iProcid;
    int m_inprocs;
    int m_istate; //steering mode states pause=0 run=1
                  //distributed modeready=0 failed=-1 waiting=2 gettingready=3 running=4
    int m_iDistrSaveMode; //masterproconly=0, masterproconly, master updated at end of each step=1, simulant configs savesd on all procs proc saves only simulant that it runs=2, as for 2 but master proc is also updated with the parameters       
	struct soap m_soap;


	void SetHostname(string shostname){m_sHostname=shostname;}
	void SetHostname(char *shostname){m_sHostname=shostname;}
	
	string GetHostname(){return m_sHostname;}

	#ifdef USEMPI
		int BroadcastHostname(int ifromid=0);
	#endif
	//void CreatePropNames();
	//void CreatePropArrayNames();
	//void CreatePropFlags();
	//void CreatePropArrayFlags();

	//CIoModel *newModel(char *sModelClass);
	//CIoSimulator *newSimulator(char *sSimulatorClass);
	//CIoSimulant *WriteConfigSimulatorIterator(CIoSimulant *pSimulant, char *sConfigFilename, char *format=NULL, char *sXSLFilename=NULL);
	//CIoSimulant *ReadConfigSimulatorIterator(CIoSimulant *pSimulant, char *sConfigFilename, char *format=NULL);

	/*!
	Following read simulation is required since the SAX simulation parser may
	not call a default model configuration creator. This makes sure
	that the configuration gets created with the correct parameter set
	*/
	//int ReadSimulation(char *sSimFilename);
	//int CheckParamFormat(CIoParam *pSimData);
    //void CreateDefaultParams();

	//Life simulation reads an unconventional array
	//we have to define our own type of config file
	//int ReadConfig(char *sConfigFilename, int format=0);
	//virtual int WriteConfig(char *sConfigFilename, int format=0, char *sXSLFilename=NULL, int iStepNum=-1);


	dqprocptr &GetProcs(){return m_pProcs;}
	void AddProc(int id, int isimulantid, char *simulantmap=NULL){if((id>=0) && (isimulantid>=0))m_pProcs.push_back(new CIoProc(id, isimulantid, simulantmap));}
    CIoProc *GetProc(int index){return(((index>=0) && (index<m_pProcs.size()))?m_pProcs[index]:NULL);}
    int GetProcID(int index){return ((GetProc(index) != NULL)?GetProc(index)->GetID():-1);}
    void SetProcID(int index,  int id){if((GetProc(index) != NULL))GetProc(index)->SetID(id);}
    int GetProcSimulantID(int index){return ((GetProc(index) != NULL)?GetProc(index)->GetSimulantID():-1);}
    void SetProcSimulantID(int index, int isimid){if((GetProc(index) != NULL))GetProc(index)->SetSimulantID(isimid);}
    char *GetProcSimulantMap(int index){return ((GetProc(index) != NULL)?GetProc(index)->GetSimulantMap():NULL);}    
    void SetProcSimulantMap(int index, char *ssimulantmap){if((GetProc(index) != NULL))GetProc(index)->SetSimulantMap(ssimulantmap);}
    char *GetProcHostname(int index){return ((GetProc(index) != NULL)?GetProc(index)->GetHostname():NULL);}    
    void SetProcHostname(int index, char *shostname){if((GetProc(index) != NULL))GetProc(index)->SetHostname(shostname);}
	int GetSimulantProcID(CIoSimulant *psim);
    
    int RunTask(CIoSimulant *psimulant);
    int jserver(int nparams, char *function , char **sparams);
    int jfileput(char *method, char *remotehost, char *username, char *encpassword, char *localfile, char *remotefile);
    int jfileget(char *method, char *remotehost, char *username, char *encpassword, char *remotefile, char *localfile);
    int jjobrun(char *method, char *jobmanager, char *remotehost, char *username, char *encpassword, char *command, char *parameters);
    
    int steercheckpoint();
    int steerupdatesteerlog();

    void InitialiseDistributedProcs();
    void UpdateMasterSimulantParams(CIoSimulant *psimulant);	

	void MoveDataFrom(CIoSimulator *psimulator,CIoSimulant *psimulant);
	void MoveData(CIoSimulator *psimulator, CIoSimulant *psimulant,CIoSimulant *tosimulant,CIoSimulantPort *fromport,CIoSimulantPort *toport,CIoSimulantLink *fromlink,CIoSimulantLink *tolink);

	//functions used by server requests this is called by the web server response
	//function responding to the client call ws__setsimulationprocid
	void setsimulationprocid(char *shostname);
	void ws__setsimulationparam(char *ssever, int iwsport, int paramid, char *parammap, CIoParam *newparam);
	CIoParam *ws__getsimulationparam(char *ssever, int iwsport, int paramid, char *parammap);

	void ws__setsimulantparam(char *ssever, int iwsport, int paramid, char *parammap, int simulantid, char *simmap,  CIoParam *newparam);
	CIoParam *ws__getsimulantparam(char *ssever, int iwsport, int paramid, char *parammap, int simulantid, char *simmap);

	int ws__getstep(char *ssever, int iwsport, int id);
	void ws__setstep(char *ssever, int iwsport, int id, int newstep);

	int ws__getnsteps(char *ssever, int iwsport, int id);
	void ws__setnsteps(char *ssever, int iwsport, int id, int newnsteps);


	int ws__setsimulationprocid(char *ssever, int iwsport, char *shostname, int iprocid);
	char *ws__getsimulationhostname(char *ssever, int iwsport, int id);


	int ws__getsimulationstate(char *ssever, int iwsport, int id);
	int ws__setsimulationstate(char *ssever, int iwsport, int id, int inewstate);

	int ws__getsimulantstate(char *ssever, int iwsport, int id, char *simmap);
	int ws__setsimulantstate(char *ssever, int iwsport, int id, char *simmap, int inewstate);

	int ws__getsimulantinportstate(char *ssever, int iwsport, int id, char *simmap, int portid);
	int ws__setsimulantinportstate(char *ssever, int iwsport, int id, char *simmap, int portid, int inewstate);

	int ws__getsimulantoutportstate(char *ssever, int iwsport, int id, char *simmap, int portid);
	int ws__setsimulantoutportstate(char *ssever, int iwsport, int id, char *simmap, int portid, int inewstate);

	int ws__getfile(char *ssever, int iwsport, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char **sfile);
	int ws__putfile(char *ssever, int iwsport, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char *sdata, char **sfile);

	int ws__setcheckpoint(char *ssever, int iwsport,int id, int inewstate, int *istate);
	int ws__getcheckpoint(char *ssever, int iwsport,int id, int *istate);
	
	int ws__setsteerlog(char *ssever, int iwsport,int id, int inewsteerlog, int *isteerlog);
	int ws__getsteerlog(char *ssever, int iwsport,int id, int *isteerlog);


	void setsimulationparam(struct soap *soap,int paramid, char *parammap, char *newvalue, char **value);
	void getsimulationparam(struct soap *soap,int paramid, char *parammap, char **value);

	void setsimulantparam(struct soap *soap,int paramid, char *parammap, int simulantid, char *simmap, char *newvalue, char **value);
	void getsimulantparam(struct soap *soap,int paramid, char *parammap, int simulantid, char *simmap, char **value);
	
	void getstep(struct soap *soap,int id, int *step);
	void setstep(struct soap *soap,int id, int newstep, int *step);
	
	void getnsteps(struct soap *soap,int id, int *nsstep);
	void setnsteps(struct soap *soap,int id, int newnsteps, int *nsteps);
	
	void getsimulationstate(struct soap *soap,int id, int *istate);
	void setsimulationstate(struct soap *soap,int id, int inewstate, int *istate);
	
	void getsimulantstate(struct soap *soap,int id, char *simmap, int *istate);
	void setsimulantstate(struct soap *soap,int id, char *simmap, int inewstate, int *istate);
	
	void getsimulantinportstate(struct soap *soap,int id, char *simmap, int portid, int *istate);
	void setsimulantinportstate(struct soap *soap,int id, char *simmap, int portid, int inewstate, int *istate);
	
	void getsimulantoutportstate(struct soap *soap,int id, char *simmap, int portid, int *istate);
	void setsimulantoutportstate(struct soap *soap,int id, char *simmap, int portid, int inewstate, int *istate);
	
	
	void setsimulationprocid(struct soap *soap,char  *hostname, int *isimulationprocid);
	void getsimulationhostname(struct soap *soap,int isimulationid, char **shostname);

	int getfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char **sfile);
	int putfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char *sdata,char **sfile);

	int setcheckpoint(struct soap *soap,int id, int inewstate, int *istate);
	int getcheckpoint(struct soap *soap,int id, int *istate);
	
	int setsteerlog(struct soap *soap,int id, int inewsteerlog, int *isteerlog);
	int getsteerlog(struct soap *soap,int id, int *isteerlog);


	//gets and sets port states for the master processor which contains
	//all the state info
	int GetSimulantOutPortState(CIoSimulant *psim, int iport);
	int GetSimulantInPortState(CIoSimulant *psim, int iport);
	int SetSimulantOutPortState(CIoSimulant *psim, int iport, int istate);
	int SetSimulantInPortState(CIoSimulant *psim, int iport, int istate);

	CIoSimulant *GetSimulant(int isimid, char *simmap);
	int GetSimulantID(CIoSimulant *psimulant);
	void GetSimulantMap(CIoSimulant *psimulant, char *simmap);

};


#endif
