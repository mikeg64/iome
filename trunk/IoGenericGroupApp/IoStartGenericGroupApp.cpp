	// IoSimulationTest.cpp : Defines the entry point for the console application.
//

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


#ifdef CWDEBUG
	#include <libcwd/sys.h>
//	#include <libcwd/debug.h>
	#include "debug.h"
#endif

#define IDns__getstep 0
#define IDns__setstep 1
#define IDns__getnsteps 2
#define IDns__setnsteps 3

#define IDns__runsimulationstep 4
#define IDns__runsimulation 5

#define IDns__requestsimulation 6
#define IDns__runrequestedsimulation 7
#define IDns__submitsimulation 8
#define IDns__simulationstatus 9
#define IDns__getsimulationresults 10
#define IDns__deletesimulation 11
#define IDns__newsimulation 12
#define IDns__createsimulation 13
#define IDns__writesimulation 14
#define IDns__readsimulation 15
#define IDns__exitiome 16
#define IDns__addparamdouble 17
#define IDns__addparamint 18
#define IDns__addparamvec 19
#define IDns__addparammat 20
#define IDns__addparamstring 21
#define IDns__addparammmat3d 22
#define IDns__addmetadata 23
#define IDns__getparamdouble 24
#define IDns__getparamint 25
#define IDns__getparamvec 26
#define IDns__getparammat 27
#define IDns__getparamstring 28
#define IDns__getparammmat3d 29
#define IDns__getmetadata 30
#define IDns__setparamdouble 31
#define IDns__setparamint 32
#define IDns__setparamvec 33
#define IDns__setparammat 34
#define IDns__setparamstring 35
#define IDns__setparammmat3d 36
#define IDns__setmetadata 37
#define IDns__deleteparam 38
#define IDns__listparam 39
#define IDns__getnumobj 40
#define IDns__getobjnum 41
#define IDns__testgroupbarrier 42
#define IDns__setgroupbarrier 43
#define IDns__writelocalsimulation 44
#define IDns__readlocalsimulation 45
#define IDns__listmetadata 46
#define IDns__deletemetadata 47


int m_wsflags[47];






#ifndef IO_MSVC
	#include "../IoSimulation/IoInitialiser.h"
	#include "../IoSimulation/soapH.h"
	#include "../IoSimulation/IoGenericSteerSimulation.h"
	#include "../IoSimulation/IoSteerWS.nsmap"
	#include <unistd.h>
	#include <sys/stat.h> 
	#include <sys/types.h>
	#include <sys/wait.h>
#else
	#include "..\IoSimulation\IoInitialiser.h"
	#include "..\IoSimulation\soapH.h"
	#include "..\IoSimulation\IoGenericSteerSimulation.h"
	#include "..\IoSimulation\IoSteerWS.nsmap"
        #include <process.h>

	#include <sys/stat.h>
	#include <sys/types.h>
#endif

//#include "stdafx.h"
//#include "IoTestDEVSimulation.h"
//#include "IoTestAgentSimulation.h"

#include <pthread.h>	// use Pthreads
#include <cstdlib>
//#include "soapH.h"
//#include "IoSteerWS.nsmap"
#include <iostream>

using std::cout;
using std::endl;
//#include "IoTestGenSimulation.h"
//#include <afxwin.h>         // MFC core and standard components
//*/
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
#ifdef CWDEBUG
	using namespace libcwd;
#endif

struct appparams
{
public :
	CIoGenericSteerSimulation  *simptr;
	string myapp;
	string myappscript;
	string jobname;
	string myxsl;
	int jobid;
	int numtasks;
	int numprocs;
	int numsubprocs;
	int procid;
	string machinefile;
};


int numsims=0;
struct simdata *simdataarray=NULL;
static CIoInitialiser m_Init;
CIoGenericSteerSimulation *TestSimulation;

static void *startapp(void *appparams);

//void *process_request(void *soap);	
int m_isimfinished=0;
char m_serverclient[300] = "localhost:8080";
struct soap m_soapclient;
char script[200]="";
int finish=0;

#ifndef MAXNUMSIMS
		#define MAXNUMSIMS 5
#endif

int standalone=1;  //A standalone simulation is one where 
                   //  the simulation runs on the same machine as the 
                   //   iome server and the iome server is used by the simulation to get and set its parameters
                   //in the case where standalone is 0 
                   // the runsimulation request will run in its own thread and with ist own 
                   //instance of IoGenericSimulation
                   //this thread will submit this job to a remote node
                   //e.g. with sungrid engine using qsub -sync y jobscript.sh
                   //the job running on the remote node will fire up its own instance of the iome server
                   //the job picks up the portadress of its local server from a jobfile.port file 
                   // the job picks up it s parameters from its local copy of the iome server
                   // the job runs
                   // job finshes and iome server shuts down on remote node
                   //  the main iome server on the submitter  returns results to the user
                   // the runsimulation thread terminates 
                   //multithreaded server allowing multipklke users to make job requests
#ifndef IO_MSVC
	bool fileexists(string strFilename) { 
	struct stat stFileInfo; 
	bool blnReturn; 
	int intStat; 

	// Attempt to get the file attributes 
	intStat = stat(strFilename.c_str(),&stFileInfo); 
	if(intStat == 0) { 
		// We were able to get the file attributes 
		// so the file obviously exists. 
		blnReturn = true; 
	} else { 
		// We were not able to get the file attributes. 
		// This may mean that we don't have permission to 
		// access the folder which contains this file. If you 
		// need to do that level of checking, lookup the 
		// return values of stat which will give you 
		// more details on why stat failed. 
		blnReturn = false; 
	} 
	   
	return(blnReturn); 
	}
#endif

int main(int argc, char* argv[])
{
	
	int m1, m2,m3,m4,m5,m6,m7,m8;
	m1=m2=m3=m4=m5=m6=m7=m8=0;
	int itype=-1;
	int status=1;

	pthread_t *apptid;

	int i;

	//static CIoInitialiser m_Init;
	#ifdef CWDEBUG
		Debug( dc::notice.on());
		Debug( libcw_do.on());
		Debug(dc::malloc.on());
	#endif
	m_Init.Initialise();
     if(argc>0)
		sprintf(script,"%s",argv[1]);
	//pthread_create(&simtid, NULL, (void*(*)(void*))startscilab, (void*)TestSimulation);

    //Set input filename as first arg
	//if NULL use defaults
	char *method=NULL;
	char sgenmachinefile[300];
	char *sjobname;
	//CIoSimulation *TestSimulation;
	CIoModel *pMod;
	CIoParam *pPar;
	struct appparams appp;
	int port;
	string server;
	int numsubprocs=1;
    if(argc>5)
    {
     	
	if(TestSimulation = (CIoGenericSteerSimulation *)new CIoGenericSteerSimulation)
	{ 
		appp.simptr=TestSimulation;
		appp.myapp=argv[1];
		appp.myappscript=argv[2];
		appp.jobname=argv[3];
		appp.myxsl=argv[4];
		appp.numprocs=1;
		appp.numtasks=atoi(argv[5]);
		appp.numsubprocs=1;
		appp.procid=0;
		appp.machinefile=appp.jobname+".machines";
        apptid=(pthread_t *)calloc(appp.numtasks,sizeof(pthread_t));
		string jobname=argv[3];
		char *sjobid;

		//generate the machinefile add the server addresses to the simulation
		//each line of the machine file will contain port and machine name and number of sub processes
		#ifndef IO_MSVC
            //readmachinefile.sh bash script
			sprintf(sgenmachinefile,"readmachinefile.sh %s",appp.machinefile.c_str());
  			system(sgenmachinefile);
		#else
			ofstream outfile;	
			outfile.open (appp.machinefile.c_str(), ofstream::out);
			//for(i=0;i<appp.numtasks;i++)
	        outfile << "8080 localhost "<< appp.numtasks << endl;

			outfile.close();
						
		#endif

		//read the generated machinefile and file the table of server names and ports 
		ifstream infile;	
		infile.open (appp.machinefile.c_str(), ifstream::in);
		port=8080;

		//for(i=0;i<appp.numtasks;i++)
		//{
		int proccount=0;
		while(!infile.eof())
		{
	        proccount++;
			infile >> port >> server >> numsubprocs;
			TestSimulation->AddNode(port,server, numsubprocs);
		}
		appp.numprocs=proccount;
		appp.numsubprocs=numsubprocs;
		//}

		infile.close();

		for(i=0;i<proccount;i++)
		{
			sjobname=(char *)calloc(strlen(argv[3]),sizeof(char));
			appp.procid=i;
			appp.numsubprocs=TestSimulation->GetNumSubProcs(i);
			sprintf(sjobname,"%s",argv[3]);
			appp.jobname=sjobname;
			//fire off separate threads to start job
			// rsh server myapp myappscript jobname my.xsl numtasks numsubprocs numprocs procid
			pthread_create(&apptid[i], NULL, (void*(*)(void*))startapp, (void*)(&appp));
			free(sjobid);	
		}
    
    	
	}
    	
    
 			
			m_Init.Terminate();
    
	return 0;
	}
}

void *startapp(void *appp)
{ 
	pthread_detach(pthread_self());
   char startapp[2000]="";
   struct appparams *papp=(struct appparams *)appp;

   if((papp !=NULL) && ((papp->simptr) !=NULL))
   {
		string sserver=papp->simptr->GetNodeServer(papp->procid);
		#ifndef IO_MSVC
            //rsh server 'appname appscript jobname appxsl numtasks numsubprocs numprocs procid'
			sprintf(startapp,"rsh %s '%s %s %s %s %d %d %s'",sserver.c_str(),(papp->myapp).c_str(),(papp->myappscript).c_str(),(papp->jobname).c_str(),(papp->myxsl).c_str(),papp->numtasks,papp->numsubprocs,papp->numprocs,papp->procid);
			system(startapp);
		#else
		//_flushall();

		//sprintf(startscilab,"Scilex.exe %s",script);
    		//system( startapp);
		;
		#endif	
   }

  	return NULL;
}


int ns__add(struct soap *soap, double a, double b, double *result)
{     	

  return SOAP_OK;
} 








int ns__setsimulationparam(struct soap *soap, int id, int paramid, char *parammap, char *newvalue, char **value)
{
	
		return SOAP_OK;
}

int ns__getsimulationparam(struct soap *soap, int id, int paramid, char *parammap, char **value)
{
		
	return SOAP_OK;
}


int ns__setsimulantparam(struct soap *soap, int id, int paramid, char *parammap, int simulantid, char *simmap, char *newvalue, char **value)
{

	
	return SOAP_OK;
}

int ns__getsimulantparam(struct soap *soap, int id, int paramid, char *parammap, int simulantid, char *simmap, char **value)
{

	return SOAP_OK;
}


int ns__getstep(struct soap *soap, int id, int *step)
{

	return SOAP_OK;
}

int ns__setstep(struct soap *soap, int id, int newstep, int *step)
{

	return SOAP_OK;
}


int ns__getnsteps(struct soap *soap, int id, int *nsstep)
{

	return SOAP_OK;
}

int ns__setnsteps(struct soap *soap, int id, int newnsteps, int *nsteps)
{

	return SOAP_OK;
}


/*int ns__getsimulationstate(struct soap *soap, int id, int *istate)
{

	return SOAP_OK;
}

int ns__setsimulationstate(struct soap *soap, int id, int inewstate, int *istate)
{


	return SOAP_OK;
}


int ns__getsimulantstate(struct soap *soap, int id, char *simmap, int *istate)
{

	return SOAP_OK;
}

int ns__setsimulantstate(struct soap *soap, int id, char *simmap, int inewstate, int *istate)
{

	return SOAP_OK;
}


int ns__getsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{

	return SOAP_OK;
}

int ns__setsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{

	return SOAP_OK;
}


int ns__getsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{

	return SOAP_OK;
}

int ns__setsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{

	return SOAP_OK;
}



int ns__setsimulationprocid(struct soap *soap, char  *hostname, int *isimulationprocid)
{

	return SOAP_OK;
}

int ns__getsimulationhostname(struct soap *soap, int isimulationid, char **shostname)
{

	return SOAP_OK;
}

int ns__getfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char **sfile)
{

	return SOAP_OK;
}

int ns__putfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char *sdata,char **sfile)
{

	return SOAP_OK;
}

int ns__setcheckpoint(struct soap *soap,int id, int inewstate, int *istate)
{

	return SOAP_OK;
}




int ns__getcheckpoint(struct soap *soap,int id, int *istate)
{

	return SOAP_OK;
}



	
int ns__setsteerlog(struct soap *soap,int id, int inewsteerlog, int *isteerlog)
{

	return SOAP_OK;
}

int ns__getsteerlog(struct soap *soap,int id, int *isteerlog)
{

	return SOAP_OK;
}*/

/*int ns__getnumprocs(struct soap *soap, int id, int *numprocs)
{

	return SOAP_OK;

}

int ns__getprocid(struct soap *soap, int id, int *procid)
{

	return SOAP_OK;

}*/

//Generic simulation operations only
int ns__newsimulation(struct soap *soap,int id, char *simname, char *xslname, int *status)
{
	return SOAP_OK;
}

int ns__createsimulation(struct soap *soap,int id, char *filename, int *status)
{
	return SOAP_OK;
}

int ns__runsimulationstep(struct soap *soap, int id, int istepnum, int *status)
{
	return SOAP_OK;

}


int ns__runsimulation(struct soap *soap, int id, char *simfilecontent, char **result)
{
	return SOAP_OK;

}

int ns__requestsimulation(struct soap *soap,char *simfilecontent, int *isimid)
{
	return SOAP_OK;
}

int ns__runrequestedsimulation(struct soap *soap,int isimid, int *istatus)
{
	return SOAP_OK;
}

int ns__submitsimulation(struct soap *soap,char *simfilecontent, int *isimid)
{
	return SOAP_OK;
}

int ns__setsimulationstatus(struct soap *soap,int newstatus,int isimid, int *status)
{
	return SOAP_OK;
}

int ns__simulationstatus(struct soap *soap,int isimid, int *status)
{
	return SOAP_OK;
}

int ns__getsimulationresults(struct soap *soap,int isimid, char **result)
{
	return SOAP_OK;
}

int ns__deletesimulation(struct soap *soap,int isimid, int *status)
{

	return SOAP_OK;
}



int ns__writesimulation(struct soap *soap,int id, char *filename, char **filecontent)
{
	return SOAP_OK;
}

int ns__writelocalsimulation(struct soap *soap,int id,char *filename, char **filecontent)
{
	return SOAP_OK;
}

int ns__readsimulation(struct soap *soap,int id, char *filename, int *status)
{
	return SOAP_OK;
}

int ns__readlocalsimulation(struct soap *soap,int id,char *filename, int *status)
{
	return SOAP_OK;

}




int ns__listmetadata(struct soap *soap, int id, char **list)
{


	
	return SOAP_OK;

}


int ns__deletemetadata(struct soap *soap,int id,char *name, int *status)
{


	
	return SOAP_OK;

}
/*int ns__writestate(struct soap *soap,int id, char *filename, char **filecontent)
{

	return SOAP_OK;
}


int ns__writeconfig(struct soap *soap,int id, char *filename, char **filecontent)
{
	return SOAP_OK;
}*/


int ns__exitiome(struct soap *soap,int id, int *status)
{
	return SOAP_OK;
}



int ns__addparamdouble(struct soap *soap,int id, char *name, double value, int iflag, int *status )
{
	
	return SOAP_OK;
}


int ns__addparamint(struct soap *soap, int id, char *name, int value, int iflag, int *status )
{

	return SOAP_OK;
}


int ns__addparamvec(struct soap *soap, int id, char *name, struct fdata value, int n, int iflag, int *status )
{

	return SOAP_OK;
}


int ns__addparammat(struct soap *soap, int id, char *name, struct fdata value, int nr, int nc,  int iflag, int *status )
{

	return SOAP_OK;
}


int ns__addparamstring(struct soap *soap, int id, char *name, char *value, int iflag, int *status )
{

	return SOAP_OK;
}


int ns__addparammmat3d(struct soap *soap, int id, char *name, struct fdata value, int n, int p, int q, int nr, int nc,int iflag, int *status )
{


	return SOAP_OK;
}



int ns__addmetadata(struct soap *soap,int id, char *name, char *property, int *status)
{
	

	
	
	
	return SOAP_OK;
}

int deletemetadata_(int id, char *sname,  int port, char *sserver)
{	
	int status=0;
	
	char *name=sname;
	//int id=0;

	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);

	soap_call_ns__deletemetadata(&m_soapclient, m_serverclient, "", id, name, &status);
	
	

	return status;
}

int listmetadata_(int id, char  **list ,  int port, char *sserver)
{
	int status=0;
	//int id=0;

	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);

	string sval="";
	char *msval=(char *)sval.c_str();

	soap_call_ns__listmetadata(&m_soapclient, m_serverclient, "", id,&msval);
	
	strcpy(*list,msval);

	return status;
}


int ns__getparamdouble(struct soap *soap,int id, char *name, double *value )
{


	return SOAP_OK;
}


int ns__getparamint(struct soap *soap, int id, char *name, int *value )
{

	return SOAP_OK;
}


int ns__getparamvec(struct soap *soap, int id, char *name, int n, struct fdata **value )
{
	
	return SOAP_OK;
}


int ns__getparammat(struct soap *soap, int id, char *name, int nr, int nc, struct fdata **value )
{
	return SOAP_OK;
}


int ns__getparamstring(struct soap *soap, int id, char *name, char **value )
{
	return SOAP_OK;
}


int ns__getparammmat3d(struct soap *soap, int id, char *name, int n, int p, int q, int nr, int nc, struct fdata **value  )
{
	return SOAP_OK;
}



int ns__getmetadata(struct soap *soap, int id, char *name, char **property)
{
	return SOAP_OK;
}


int ns__setparamdouble(struct soap *soap, int id, char *name, double value, int *status )
{


	return SOAP_OK;
}


int ns__setparamint(struct soap *soap, int id, char *name, int value, int *status  )
{

	return SOAP_OK;
}


int ns__setparamvec(struct soap *soap, int id, char *name, struct fdata value, int n, int *status  )
{


	return SOAP_OK;
}


int ns__setparammat(struct soap *soap, int id, char *name, struct fdata value, int nr, int nc, int *status  )
{

	return SOAP_OK;
}


int ns__setparamstring(struct soap *soap, int id, char *name, char *value, int *status  )
{


	return SOAP_OK;
}


int ns__setparammmat3d(struct soap *soap, int id, char *name, struct fdata value,  int n, int p, int q, int nr, int nc, int *status  )
{

	return SOAP_OK;
}



int ns__setmetadata(struct soap *soap,int id, char *name, char *property, int *status)
{

	return SOAP_OK;
}


int ns__deleteparam(struct soap *soap,char *name, int id, int *status )
{
	return SOAP_OK;
}


int ns__listparam(struct soap *soap,char *type, int id, char  **list )
{


	return SOAP_OK;
}







int ns__getnumobj(struct soap *soap,int id, int *numobj)
{
	
	return SOAP_OK;
}

int ns__getobjnum(struct soap *soap,int id, int *objnum)
{
	
	return SOAP_OK;
}


int ns__setgroupbarrier(struct soap *soap,int id, int state, int *newstate)
{
	return SOAP_OK;
}

int ns__testgroupbarrier(struct soap *soap,int id, int *state)
{
	return SOAP_OK;
}


