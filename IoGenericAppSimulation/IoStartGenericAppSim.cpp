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
	#include <direct.h>


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
#define IDns__setsimulationstatus 48

int m_wsflags[49];



struct simdata 
{
public :
	CIoGenericSteerSimulation  *simptr;
	int isimid;
	int status;
	void *userid; //for secure service user would provide ssl key public key?
	pthread_t tid;
	char *dir;
	int ipid;
};


//array of simulations created by SAAS requests
int numsims=0;
struct simdata *simdataarray=NULL;
int m_numsubprocs=1;
int m_allocsubprocs=0; //this is set by bthe get objnum routine
                       //which allocates a subprocessor id to each simulation
                       //it is incremented each time an allocation is made
                       //all processors MUST make ONE call to getobjnum at the
                       //start of the routine

//array of simulations created by multiple threads
int newsimind;
struct simdata *simsubprocs=NULL;

static CIoInitialiser m_Init;
CIoGenericSteerSimulation *TestSimulation=NULL;
int getsimdata();
static void *startapp(void *simulation);
static void *runsimulation(void *simulationid);
static void *runanddeletesimulation(void *simulationid);
static void *executesimulation(void *simulation);	
static void *process_request(void *soap);
//void *process_request(void *soap);	

int m_maxsims=10;

int m_isimfinished=0;
char m_serverclient[300] = "localhost:8080";
char m_hostname[300] = "localhost";
int m_port=8080;
int port=m_port;
char script[300];
char appscript[300];
struct soap m_soapclient;
int finish=0;
char m_workingdir[600]=".";
#ifndef MAXNUMSIMS
		#define MAXNUMSIMS 5
#endif

#ifndef MAXNUMTHREADS
		#define MAXNUMTHREADS 2
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

//appname appscript jobname appxsl jobid numprocs machinefile
//int InitIOME(char *simname, char *simxslfile, char *simfilename, char *statefilename, char *configfilename, int port, int istandalone);

int InitIOME(char *sappscript, char *script, char *simname, char *simxslfile, int port, int numtasks, int numsubprocs, int numprocs, int procid);



	bool fileexists(string strFilename) {
		bool blnReturn=false;
	 
	int intStat; 
		#ifndef IO_MSVC
	struct stat stFileInfo; 

	// Attempt to get the file attributes 
	intStat = stat(strFilename.c_str(),&stFileInfo); 

#else
	struct _stat stFileInfo; 

	// Attempt to get the file attributes 
	intStat = _stat(strFilename.c_str(),&stFileInfo); 

	  #endif 
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

int main(int argc, char* argv[])
{
	
	int m1, m2,m3,m4,m5,m6,m7,m8;
	m1=m2=m3=m4=m5=m6=m7=m8=0;
	int itype=-1;
	int status=1;


	//static CIoInitialiser m_Init;
	#ifdef CWDEBUG
		Debug( dc::notice.on());
		Debug( libcw_do.on());
		Debug(dc::malloc.on());
	#endif
	m_Init.Initialise();




	//pthread_create(&simtid, NULL, (void*(*)(void*))startscilab, (void*)TestSimulation);

    //Set input filename as first arg
	//if NULL use defaults
	char *method=NULL;
	//CIoSimulation *TestSimulation;
	CIoModel *pMod;
	CIoParam *pPar;
	
    if(argc>0)
    {
     	//appname appscript jobname appxsl port numtasks numsubprocs numprocs procid
     		if(argc>9)
				InitIOME(argv[1],argv[2],argv[3],argv[4],atoi(argv[5]),atoi(argv[6]),atoi(argv[7]),atoi(argv[8]),atoi(argv[9]));                
     		if(argc>8)
				InitIOME(argv[1],argv[2],argv[3],argv[4],atoi(argv[5]),atoi(argv[6]),atoi(argv[7]),atoi(argv[8]),0);                
     		if(argc>7)
				InitIOME(argv[1],argv[2],argv[3],argv[4],atoi(argv[5]),atoi(argv[6]),atoi(argv[7]),1,0);                
     		if(argc>6)
				InitIOME(argv[1],argv[2],argv[3],argv[4],atoi(argv[5]),atoi(argv[6]),1,1,0);
			else if(argc>5)
				InitIOME(argv[1],argv[2],argv[3],argv[4],atoi(argv[5]),1,1,1,0);
			else if(argc>4)
				InitIOME(argv[1],argv[2],argv[3],argv[4],8080,1,1,1,0);
			else if(argc>3)
				InitIOME(argv[1],argv[2],argv[3],"null",8080,1,1,1,0); 
			else if(argc>2)
				InitIOME(argv[1],argv[2],argv[3],"null",8080,1,1,1,0);
	}
    
 	m_Init.Terminate();
    
	return 0;
}

//int InitIOME(char *simname, char *simxslfile, char *simfilename, char *statefilename="gsstatefile", char *configfilename="gsconfigfile", int port=8080,int istandalone=1)
int InitIOME(char *sappscript, char *sscript, char *simname, char *simxslfile, int iport , int numtasks=1,int numsubprocs=1, int numprocs=1, int procid=0)
{
	int status=0;
	pthread_t simtid;
	//pthread_t *scitid;
	string sserver;

	struct soap *tsoap;
    pthread_t tid;
	int i,j;
	int m, s; /* master and slave sockets */
    //int port=8080;
	struct soap soap;
	port=iport;
	sprintf(m_serverclient,"%s:%d","localhost",port);
	int finished=0;
    strcpy(script,sscript);
	strcpy(appscript, sappscript);

	//enable all of the services (default setting)
    for(i=0;i<49;i++)
		m_wsflags[i]=1;
	char *siogscfgfile="ioapp.config";
	string siogsfil=siogscfgfile;
	int val;

	if(fileexists(siogsfil))
	{
		ifstream infile;	
		infile.open (siogsfil.c_str(), ifstream::in);
	
			for(i=0;i<49;i++)
			{
				infile >> m_wsflags[i];
				while((!infile.eof()) && (infile.get()!='\n'));
			}
		

		infile.close();
	}
	CIoGenericSteerSimulation *LocalSimulation=NULL;

			if(	 TestSimulation = (CIoGenericSteerSimulation *)new CIoGenericSteerSimulation )
			{


  		//pPar=(TestSimulation->GetSimulant()->GetParams());
		//pPar=(TestSimulation->GetSimulant()->GetProperty(IO_AGENTMODEL_SCAFFUNC_STRARRAY));
	    //std::cout<<"sim created" << *pPar << std::endl;	
	    //std::cout<< "end sim created" << std::endl;
			
	    //pPar=(TestSimulation->GetSimulant()->GetParams());
	    //std::cout << *pPar << std::endl;
		//		printf("here 1  doing dx %s \n");
	   // if(argc>2 && (strcmp("2dx",argv[2])==0))
	    //{
	    //	std::cout<<"here 2  doing dx %s "<<argv[2]<<"\n";

	    //	((CIoTestAgentSimulation *)TestSimulation)->Transform2dx();
	    //}
	    //else
		//{


		soap_init(&soap);
		const int soapbindfailed = 1;
		int i=0;
		while(i<50)
		{
			try
			{
				m = soap_bind(&soap, NULL, port, 100);
				if (m < 0)
					throw soapbindfailed;
				else
					i=50;
			}
			catch(int j)
			{
				fprintf(stderr, "Socket connection failed: master socket = %d port %d\n", m, port);

				if(j==soapbindfailed)
				{
	
					soap_print_fault(&soap, stderr);
						i++;
						port++;
						if(i==50)
							 exit(-1);
				}
			}
		}
		char svar[50];
		//sprintf(svar,"IOME_WSPORT=%d",port);
		//char svar[50];
		char simportfile[500];
		//sprintf(svar,"IOME_WSPORT=%d",port);
        sprintf(svar,"%d",port);
		if(numprocs>0)
			sprintf(simportfile,"%s%d_port.txt",simname,procid);
		else
			sprintf(simportfile,"%s_port.txt",simname);

        fstream filestr;
		filestr.open(simportfile, fstream::out );
        filestr<<svar; 
		filestr.close();

		int ret;
		#ifndef IO_MSVC
			ret = putenv(svar);
		#else
			ret = _putenv(svar);
		#endif



		//if num procs>0
		int ifinished=0;
		if(numprocs>0)
		{
			//read machine file get server names and add server nodes to simulation
			string smachinefile=simname;
			smachinefile+=".machines";

			
			//check for existence of portfiles
			//wait for all of portfiles to be written
			///get the procid from the machines file
			//using getprocid function
			//scilab matlab have aGetProcID function which can be used
			while(ifinished==0)
			{
				int icount=0;
				for(i=0;i<numprocs;i++)
				{
					char *stempimportfile;
					stempimportfile=(char *)calloc(strlen(simname)+14,sizeof(char));
					sprintf(stempimportfile,"%s%d_port.txt",simname,i);
					string spfile=stempimportfile;
					if(fileexists(spfile))
						icount++;
					free(stempimportfile);
				}
				//if(fileexists(smachinefile))
				//		icount++;
				if(icount>=(numprocs))
					ifinished=1;
			}

			numsims+=m_numsubprocs;
			m_numsubprocs=numsubprocs;
			//set port for node with id
			TestSimulation->m_iprocid=0;
			TestSimulation->m_ijobid=0;
			TestSimulation->m_inumprocs=1;
			TestSimulation->m_isubproc=0;
			if(numprocs>1)
			{
				fstream machfile;
				int inumsubprocs=1;
				machfile.open (smachinefile.c_str(), fstream::in );
				for(i=0;i<numprocs;i++)
				{
					int iport;
					char *stempimportfile;
					stempimportfile=(char *)calloc(strlen(simname)+14,sizeof(char));
					sprintf(stempimportfile,"%s%d_port.txt",i,simname);
					fstream filestr;
					filestr.open (stempimportfile, fstream::in );
					filestr>>iport;
					machfile>>sserver>>inumsubprocs;
					TestSimulation->AddNode(iport,sserver,inumsubprocs);
					for(j=0;j<inumsubprocs;j++)
						TestSimulation->AddJob(i,j);
					
					filestr.close();
					free(stempimportfile);
				}
				machfile.close();

			}
			else
			{
				sserver="localhost";
				TestSimulation->AddNode(port,sserver,numsubprocs);
				for(j=0;j<numsubprocs;j++)
						TestSimulation->AddJob(0,j);

			}
			//all nodes set
		}


		simdataarray=(struct simdata *)calloc(numsubprocs+MAXNUMSIMS, sizeof(struct simdata ));
		for(int j=0; j<(numsubprocs+MAXNUMSIMS); j++)
		{
			simdataarray[j].simptr=NULL;
			simdataarray[j].isimid=-1;
			simdataarray[j].status=-1;
			simdataarray[j].userid=NULL;
		}
		//simsubprocs=(struct simdata *)calloc(numsubprocs, sizeof(struct simdata ));
		//for(int j=0; j<numsubprocs; j++)
		//{
		//	simsubprocs[j].simptr=NULL;
		//	simsubprocs[j].isimid=-1;
		//	simsubprocs[j].status=-1;
		//	simsubprocs[j].userid=NULL;
		//}


		newsimind=0;
		for(j=0;j<numsubprocs;j++)
		{
			if(	 LocalSimulation = (CIoGenericSteerSimulation *)new CIoGenericSteerSimulation )
			{
				if(newsimind>=numsubprocs)
					newsimind=0;
				LocalSimulation->copyjobs(TestSimulation->m_pjobs);
				LocalSimulation->copynodes(TestSimulation->m_pnodes);
				LocalSimulation->SetSimName(simname);
				LocalSimulation->m_ijobid=TestSimulation->GetJobid(procid,j);
				LocalSimulation->m_inumprocs=numprocs;
				LocalSimulation->m_isubproc=j;
				LocalSimulation->SetStateFileName("statefile.xml");
				LocalSimulation->SetConfigFileName("configfile.xml");		

				if(simxslfile)
					if((strlen(simxslfile)>0)  && (strcmp(simxslfile,"NULL") !=0) && (strcmp(simxslfile,"null") !=0))
						LocalSimulation->SetSimXSLFileName(simxslfile);
				
				simdataarray[j].simptr=LocalSimulation;
				simdataarray[j].isimid=j;
				simdataarray[j].status=0;
				

				pthread_create(&(simdataarray[j].tid), NULL, (void*(*)(void*))startapp, (void*)LocalSimulation);
				newsimind++;				
			}
		}
		newsimind=0;
		while(finish==0)
		{

		 
		 		s = soap_accept(&soap);
		    	// copy soap environment and spawn thread
		      	tsoap = soap_copy(&soap);
		      	pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)tsoap);
		    fprintf(stderr, "Socket connection successful: master socket = %d port %d\n", m, port);
							
		    //pthread_create(&simtid, NULL, (void*(*)(void*))executesimulation, (void*)TestSimulation);

		    //while(m_isimfinished!=1)
		    //{ 
				//	    	s = soap_accept(&soap);
		    	// copy soap environment and spawn thread
		      	//tsoap = soap_copy(&soap);
		      	//pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)tsoap);
		    	    
		      /*fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);*/
		      if (s < 0)
		      { soap_print_fault(&soap, stderr);
		        exit(-1);
		      } 
		      //soap_serve(&soap);
			  //soap_end(&soap);

		}
		soap_done(&soap);
				 pthread_cancel(tid);
				printf("INIT IOME has finished\n");
						for(j=0;j<numsubprocs;j++)
							pthread_cancel(simdataarray[j].tid);
		
		      //soap_destroy(&soap);
		 //  }
		//}
			//TestSimulation->RunSimulation();
		delete TestSimulation;

	}

	return status;

}




int ns__add(struct soap *soap, double a, double b, double *result)
{ *result = a + b;
   printf("hello\n");
  return SOAP_OK;
} 


void *startapp(void *simulation)
{ 
	pthread_detach(pthread_self());
    char startapp[500]="";
	char *path=(char *)calloc(1+strlen(getenv("IOME_HOME")),sizeof(char));
    strcpy(path,getenv("IOME_HOME"));
	char fullpath[500]="";
    

    //system( "WScilex.exe" );

	//Run the model
	int pid,status,procstatus=0;
        


	//unix/linux/cygwin process call
	#ifndef IO_MSVC
        sprintf(fullpath,"%s//bin//%s",path,appscript);
	    if(fileexists(appscript))
                sprintf(startapp,"%s %s",appscript,script);
		else if(fileexists(fullpath))
                sprintf(startapp,"%s//bin//%s %s",path,appscript,script);
		else
				sprintf(startapp,"genericapp.sh %s",script);
		system(startapp);
		//fork();
		//execl(startapp,startapp,script,NULL);
		
		/*if((pid=fork())<0)
		         procstatus=-1;*/
		         
		//if( (procstatus==0))
		//{
		/*	if((pid==0) )
			{
			       //the file to be executed
			       //and the parameters passed to the command
			       execvp((const char *)startscilab.c_str(),args);	
			}*/
			
			//while(wait(&status) != pid)
			           ;/*do nothing*/
		//}
	//windows process call
	#else
		//_flushall();
        sprintf(fullpath,"%s\bin\%s",path,appscript);
	    if(fileexists(appscript))
                sprintf(startapp,"genericapp.bat %s",script);
	    else if(fileexists(fullpath))
                sprintf(startapp,"%s\bin\%s %s",path,appscript,script);
		else
                sprintf(startapp,"genericapp.bat %s",script);

		//sprintf(startapp,"genericapp.bat %s",script);
    	system( startapp);
		//system( startscilab.c_str() );
		//pid=_spawnv(_P_NOWAIT, path, args);
		//if(pid != -1)
		//	_cwait(&status, pid, _WAIT_CHILD);
		
	#endif	


	free(path);

	m_isimfinished=1;
  	return NULL;
}

void *runsimulation(void *simulationid)
{ 
	pthread_detach(pthread_self());
	int simid=*(int *)( simulationid);
	struct simdata currentsim=simdataarray[simid];
	CIoGenericSteerSimulation  *simulation;
	string jobdir=simdataarray[simid].dir;
	if((currentsim.simptr !=NULL) && (currentsim.isimid==simid))
	{
				   	
		try
		{
			#ifndef IO_MSVC
			   	  chdir(jobdir.c_str());
			   	  //printf("job dir %s \n",jobdir.c_str());
			#else
			   	  _chdir(jobdir.c_str());
			#endif	
		
		simulation=currentsim.simptr;
		currentsim.status=1;
		simulation->RunSimulation();
		simdataarray[simid].ipid=simulation->m_ipid;
		currentsim.status=2;
		//((CIoSimulation *)simulation)->RunSimulation();
		
		  #ifndef IO_MSVC
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir(m_workingdir);
			#else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir(m_workingdir);
			#endif	
		}
		catch(int j)
		{
			printf("run simulation thread caught exception\n");
		}
	}
	
  	return NULL;
}


void *runanddeletesimulation(void *simulationid)
{ 
	pthread_detach(pthread_self());
	int simid=*(int *)( simulationid);
	struct simdata currentsim=simdataarray[simid];
	CIoGenericSteerSimulation  *simulation;
	string jobdir=simdataarray[simid].dir;
	if((currentsim.simptr !=NULL) && (currentsim.isimid==simid))
	{
				   	
		try
		{
			#ifndef IO_MSVC
			   	  chdir(jobdir.c_str());
			   	  //printf("job dir %s \n",jobdir.c_str());
			#else
			   	  ;//_chdir(jobdir.c_str());
			#endif	
		
		simulation=currentsim.simptr;
		currentsim.status=1;
		simulation->RunSimulation();
		simdataarray[simid].ipid=simulation->m_ipid;
		currentsim.status=2;
		//((CIoSimulation *)simulation)->RunSimulation();
		
		  #ifndef IO_MSVC
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir(m_workingdir);
			#else
			   	  //_mkdir(jobdir.c_str());
			   	  ;//_chdir("..");
			#endif
			
				simdataarray[simid].isimid=-1;
				simdataarray[simid].simptr=NULL;
				simdataarray[simid].status=-1;
				simdataarray[simid].userid=NULL;
				//simdataarray[isimid].tid=0;



		numsims--;
			

		#ifndef IO_MSVC
			   	  
			   	  string sdelcommand="/bin/rm -rf ";
			   	  
			   	  printf("deleting %s %s\n",sdelcommand.c_str(),jobdir.c_str());
			   	  sdelcommand.append(jobdir);
			   	  system(sdelcommand.c_str());
				  //chdir("..");
				  //rmdir(sjobdir.c_str());
				  printf("deleting %s %s\n",sdelcommand.c_str(),jobdir.c_str());
				  
			#else
			   	  remove("*");
			   	  _chdir(m_workingdir);
			   	  _rmdir(sjobdir.c_str());
			#endif

		if(/*(standalone!=1 ) && */(simulation != NULL))
			delete simulation;	

			
				
		}
		catch(int j)
		{
			printf("run and delete simulation thread caught exception\n");
		}
	}
	
  	return NULL;
}

void *executesimulation(void *simulation)
{ 
	pthread_detach(pthread_self());
	((CIoSimulation *)simulation)->RunSimulation();
	m_isimfinished=1;
  	return NULL;
}


void *process_request(void *soap)
{ pthread_detach(pthread_self());
  // serve request (or multiple requests with keep-alive enabled)
  soap_serve((struct soap*)soap);
  // cleanup class instances
  soap_destroy((struct soap*)soap);
  // cleanup
  soap_end((struct soap*)soap);
  // detach thread's copy of soap environment
  soap_done((struct soap*)soap);
  // free soap environment
  free(soap);
  return NULL;
}

int ns__getstep(struct soap *soap, int id, int *step)
{

	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    if(m_wsflags[IDns__getstep]==1)
	{
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);

				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
					*step=LocalSimulation->m_iCurrentStep;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				soap_call_ns__getstep(&m_soapclient, sserverclient, "",id, step);
				
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get simulation step\n");
	
		
	}

	//free(sstr);
	}
	
	return SOAP_OK;

}

int ns__setstep(struct soap *soap, int id, int newstep, int *step)
{

		int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    if(m_wsflags[IDns__setstep]==1)
	{
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);

				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					LocalSimulation->SetCurrentStep(newstep);
					*step=newstep;
				}

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				soap_call_ns__setstep(&m_soapclient, sserverclient, "",id,newstep, step);
				
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to set simulation step\n");
	
		
	}

	//free(sstr);
	}
	
	return SOAP_OK;

}


int ns__getnsteps(struct soap *soap, int id, int *nsstep)
{
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];

    if(m_wsflags[IDns__getnsteps]==1)
	{
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);

				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					*nsstep=LocalSimulation->GetNumSteps();
					
				}

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				soap_call_ns__getnsteps(&m_soapclient, sserverclient, "",id,nsstep);
				
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get num simulation steps\n");
	
		
	}
	}
	//free(sstr);

	
	return SOAP_OK;


}

int ns__setnsteps(struct soap *soap, int id, int newnsteps, int *nsteps)
{
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];

    if(m_wsflags[IDns__setnsteps]==1)
	{
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);

				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					LocalSimulation->SetNumSteps(newnsteps);
					*nsteps=newnsteps;
				}

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				soap_call_ns__setnsteps(&m_soapclient, sserverclient, "",id,newnsteps, nsteps);
				
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to set num simulation steps\n");
	
		
	}
	}
	//free(sstr);

	
	return SOAP_OK;
}


/*int ns__getsimulationstate(struct soap *soap, int id, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulationstate(soap,id,istate);

	return SOAP_OK;
}

int ns__setsimulationstate(struct soap *soap, int id, int inewstate, int *istate)
{

	//CIoParam *pPar;
	//CIoAgentModel *pmod;


	if(TestSimulation != NULL)
	{
		((CIoWFSimulation *)TestSimulation)->setsimulationstate(soap,id,inewstate,istate);
		
//								pPar=(TestSimulation->GetSimulant()->GetProperty(IO_AGENTMODEL_FLOATPROPS_VEC));
//	    std::cout<<" set sim parsim created" << *pPar << std::endl;	
//	    pmod=(CIoAgentModel *)(TestSimulation->m_pSimulant);
//	    std::cout<<" before  "<<*(pmod->GetProperty(4))<<std::endl;
//	    pmod->EvaluateScaFieldFuncs();
//	    std::cout<<" after  "<<*(pmod->GetProperty(4))<<std::endl;
	}

	return SOAP_OK;
}


int ns__getsimulantstate(struct soap *soap, int id, char *simmap, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulantstate(soap,id,simmap,istate);

	return SOAP_OK;
}

int ns__setsimulantstate(struct soap *soap, int id, char *simmap, int inewstate, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsimulantstate(soap,id,simmap,inewstate,istate);

	return SOAP_OK;
}


int ns__getsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulantinportstate(soap,id,simmap,portid,istate);

	return SOAP_OK;
}

int ns__setsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsimulantinportstate(soap,id,simmap,portid,inewstate,istate);

	return SOAP_OK;
}


int ns__getsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulantoutportstate(soap,id,simmap,portid,istate);

	return SOAP_OK;
}

int ns__setsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsimulantoutportstate(soap,id,simmap,portid,inewstate,istate);

	return SOAP_OK;
}



int ns__setsimulationprocid(struct soap *soap, char  *hostname, int *isimulationprocid)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsimulationprocid(soap,hostname,isimulationprocid);

	return SOAP_OK;
}

int ns__getsimulationhostname(struct soap *soap, int isimulationid, char **shostname)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulationhostname(soap,isimulationid,shostname);

	return SOAP_OK;
}

int ns__getfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char **sfile)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getfile(soap,id,localfilename,localpath,remotefilename,remotefilepath,sfile);

	return SOAP_OK;
}

int ns__putfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char *sdata,char **sfile)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->putfile(soap,id,localfilename,localpath,remotefilename,remotefilepath,sdata,sfile);

	return SOAP_OK;
}

int ns__setcheckpoint(struct soap *soap,int id, int inewstate, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setcheckpoint(soap,id,inewstate,istate);

	return SOAP_OK;
}




int ns__getcheckpoint(struct soap *soap,int id, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getcheckpoint(soap,id,istate);

	return SOAP_OK;
}



	
int ns__setsteerlog(struct soap *soap,int id, int inewsteerlog, int *isteerlog)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsteerlog(soap,id,inewsteerlog,isteerlog);

	return SOAP_OK;
}

int ns__getsteerlog(struct soap *soap,int id, int *isteerlog)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);

	return SOAP_OK;
}

int ns__getprocid(struct soap *soap, int id, int *procid)
{
	if(TestSimulation != NULL)
		*procid=TestSimulation->m_irank;

	return SOAP_OK;
}

int ns__getnumprocs(struct soap *soap, int id, int *numprocs)
{
	if(TestSimulation != NULL)
		*numprocs=TestSimulation->m_nprocs;
	return SOAP_OK;
}*/

int ns__runsimulationstep(struct soap *soap, int id,int istepnum, int *status)
{	
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
    if(m_wsflags[IDns__runsimulationstep]==1)
	{
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					LocalSimulation->RunSimulationStep(istepnum);
					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				soap_call_ns__runsimulationstep(&m_soapclient, sserverclient, "",id,istepnum,status);
				
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to run simulation step\n");
	
		
	}
	}
	//free(sstr);

	
	return SOAP_OK;



}



//Generic simulation operations only
int ns__newsimulation(struct soap *soap,int id,char *simname, char *xslname, int *status)
{
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];

    if(m_wsflags[IDns__newsimulation]==1)
	{
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+m_maxsims)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);

				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
				delete LocalSimulation;
				LocalSimulation = new CIoGenericSteerSimulation;
				
				LocalSimulation->SetSimName(simname);
                simdataarray[isubprocid].simptr=LocalSimulation;
				
				LocalSimulation->copyjobs(TestSimulation->m_pjobs);
				LocalSimulation->copynodes(TestSimulation->m_pnodes);
				
				LocalSimulation->m_ijobid=id;
				LocalSimulation->m_inumprocs=TestSimulation->m_inumprocs;
				LocalSimulation->m_isubproc=isubprocid;
				LocalSimulation->m_iprocid=jpid;
				LocalSimulation->SetStateFileName("statefile.xml");
				LocalSimulation->SetConfigFileName("configfile.xml");		

				if(xslname)
					if((strlen(xslname)>0)  && (strcmp(xslname,"NULL") !=0) && (strcmp(xslname,"null") !=0))
						LocalSimulation->SetSimXSLFileName(xslname);
				}

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				soap_call_ns__newsimulation(&m_soapclient, sserverclient, "", id,simname, xslname,status );
			}

	        
			//TestSimulation->SetStateFileName(statefilename);
			//TestSimulation->SetConfigFileName(configfilename); 
		}
	}
	catch(int j)
	{
		printf("Server failed to initialise new simulation\n");
		*status=-1;
		
	}
	}
	return SOAP_OK;
}




int ns__createsimulation(struct soap *soap,int id,char *filename, int *status)
{

	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

    if(m_wsflags[IDns__createsimulation]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+m_maxsims)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					if((filename == NULL) || strlen(filename)==0 )
					{
						*status=LocalSimulation->CreateSimulation(filename);
					}
					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				soap_call_ns__createsimulation(&m_soapclient, sserverclient, "",id,filename,status);
				
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to create simulation step\n");
	
		
	}
	}
	//free(sstr);

	
	return SOAP_OK;


}

int ns__runsimulation(struct soap *soap,int id,char *simfilecontent, char **result)
{
	string filename="simfile.xml";
	char sjd[200];
	sprintf(sjd,"%d",(int)time(NULL));
	string jobdir=sjd;
	int status=0;
    if(m_wsflags[IDns__runsimulation]==1)
	{
	try
	{
		if((numsims < m_numsubprocs+m_maxsims) )
		{
	

	
				int simid;
			if((simid=getsimdata())<0)
			{
				
				return SOAP_OK;
			}
	
		CIoGenericSteerSimulation *LocalTestSimulation;
	    
		
			if((simfilecontent != NULL) || strlen(simfilecontent)>0 )
			{
	
	
		
				char command[500];
		   		#ifndef IO_MSVC
		   			chdir(m_workingdir);		   		
			   		mkdir(jobdir.c_str(),0755);
					sprintf(command,"cp -p iogenericsim.sh %s/iogenericsim.sh",jobdir.c_str());
					system(command);
			   		chdir(jobdir.c_str());
			   		system("chmod a+x iogenericsim.sh");
				#else
		   			_chdir(m_workingdir);		   						
			   		_mkdir(jobdir.c_str());
					sprintf(command,"copy iogenericsim.bat %s\\iogenericsim.bat",jobdir.c_str());
					printf("command is: %s\n",command);
					system(command);
			   		_chdir(jobdir.c_str());
				#endif	

		       LocalTestSimulation = new CIoGenericSteerSimulation;
				
				
				
				//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
			//filecontent
			//*status=TestSimulation->CreateSimulation(filename);
				//write the content to the simfile
				
	            fstream filestr;
				filestr.open (filename.c_str(), fstream::out );
	            filestr<<simfilecontent; 
				filestr.close();
	
				status=LocalTestSimulation->CreateSimulation((char *)filename.c_str());
	
				//write data to output string
	
			
	        /*if(standalone==1)
			{
				if(TestSimulation != NULL)
					delete TestSimulation;
	
				TestSimulation=LocalTestSimulation;
	
			}*/
			//int simid=m_numsubprocs+numsims++;
			//int simid=m_numsubprocs+numsims;
			
			numsims++;

			char svar[50];
			sprintf(svar,"%d %d %s",m_port, simid, m_hostname);
			//fstream filestr;
			filestr.open ("ioserverinfo.txt", fstream::out );
			filestr<<svar; 
			filestr.close();



			LocalTestSimulation->copyjobs(TestSimulation->m_pjobs);
			LocalTestSimulation->copynodes(TestSimulation->m_pnodes);
			
			LocalTestSimulation->m_ijobid=simid;
			LocalTestSimulation->m_inumprocs=TestSimulation->m_inumprocs;
			LocalTestSimulation->m_isubproc=TestSimulation->m_isubproc;
			LocalTestSimulation->m_iprocid=0;
			LocalTestSimulation->SetStateFileName("statefile.xml");
			LocalTestSimulation->SetConfigFileName("configfile.xml");		
	
	
	
			simdataarray[simid].isimid=simid;
			simdataarray[simid].simptr=LocalTestSimulation;
			simdataarray[simid].status=1;
			simdataarray[simid].userid=0;
			//pthread_create(&simdataarray[simid].tid, NULL, (void*(*)(void*))runsimulation, (void*)isimid);
			simdataarray[simid].dir=(char *)calloc(strlen(jobdir.c_str()),sizeof(char));
			strcpy(simdataarray[simid].dir,jobdir.c_str());
	
	
	
	
			LocalTestSimulation->RunSimulation();
			simdataarray[simid].status=2;
			//on exception introduce here
			//else
			//	simdataarray[simid].status=-2;
	
			if((LocalTestSimulation->WriteSimulation((char *)filename.c_str())==0))
				simdataarray[simid].status=3;
			else
				simdataarray[simid].status=-3;
	
	
			string sresult="";
			string sline="";
			FILE *inf;
			if((inf=fopen(filename.c_str(),"r")) != NULL )
			{
			char c;
			do
			{
				c=fgetc(inf);
				sline=c;
				if(c != EOF)
				 sresult.append(sline);
			}
			while(c != EOF);
			}
			fclose(inf);
	
	
	
			//string sresult="";
			//ifstream infile;
			//ostringstream oss (ostringstream::out);
			//infile.open (filename.c_str(), ifstream::in);
			//while (infile.good())
			//	oss << (char) infile.get();
			//sresult=oss.str();
			//infile.close();
	
			//read the output simulation results to the result string			
			*result=(char *)soap_malloc(soap,(1+strlen(sresult.c_str()))*sizeof(char));
			strcpy(*result,sresult.c_str());
	
			simdataarray[simid].isimid=-1;
			simdataarray[simid].simptr=NULL;
			simdataarray[simid].status=-1;
			simdataarray[simid].userid=NULL;
			free(simdataarray[simid].dir);
			numsims--;
	
			if(/*(standalone!=1 ) && */(LocalTestSimulation != NULL))
				delete LocalTestSimulation;
				
			#ifndef IO_MSVC
			   	  string sdelcommand="/bin/rm -rf ";
			   	  sdelcommand.append(jobdir);
			   	  chdir(m_workingdir);		   					   	  
			   	  system(sdelcommand.c_str());
			#else
			   	  remove("*");
			   	  _chdir(m_workingdir);		   		
			   	  _rmdir(jobdir.c_str());
			#endif
			
	
			}
	
		}
	}
	catch(int j)
	{
		printf("Server failed to run simulation\n");
		
	}
}
	return SOAP_OK;



}

int ns__submitsimulation(struct soap *soap,char *simfilecontent, int *isimid)
{
	string filename="simfile.xml";
	
	char sjd[200];
	sprintf(sjd,"%d",(int)time(NULL));
	string jobdir=sjd;
	
	int *iisimid;
	int status=0;

    if(m_wsflags[IDns__submitsimulation]==1)
	{
	try
	{
	if((numsims < m_numsubprocs+m_maxsims) )
	{



		int simid;
		if((simid=getsimdata())<0)
		{
			*isimid=-1;
			return SOAP_OK;
		}
		*isimid=simid;
	CIoGenericSteerSimulation *LocalTestSimulation;
    
	
		if((simfilecontent != NULL) || strlen(simfilecontent)>0 )
		{
			char command[500];
		   	#ifndef IO_MSVC
		   	      chdir(m_workingdir);
			   	  mkdir(jobdir.c_str(),0755);
				  sprintf(command,"cp -p iogenericsim.sh %s/iogenericsim.sh",jobdir.c_str());
				  system(command);
			   	  chdir(jobdir.c_str());
			   	  system("chmod a+x iogenericsim.sh");
			#else
			   	  _chdir(m_workingdir);			
			   	  _mkdir(jobdir.c_str());
				  sprintf(command,"copy iogenericsim.bat %s\\iogenericsim.bat",jobdir.c_str());
				  printf("command is: %s\n",command);
				  system(command);
			   	  _chdir(jobdir.c_str());
			#endif



	       LocalTestSimulation = new CIoGenericSteerSimulation;
			
			//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		//filecontent
		//*status=TestSimulation->CreateSimulation(filename);
			//write the content to the simfile
            fstream filestr;
			filestr.open (filename.c_str(), fstream::out );
            filestr<<simfilecontent; 
			filestr.close();
            //printf("simfilecontent: %s\n",simfilecontent);
			status=LocalTestSimulation->CreateSimulation((char *)filename.c_str());

			//write data to output string

		
        /*if(standalone==1)
		{
			if(TestSimulation != NULL)
				delete TestSimulation;

			TestSimulation=LocalTestSimulation;

		}*/

		//int simid=m_numsubprocs+numsims++;
		//int simid=m_numsubprocs+numsims;
		numsims++;


	    char svar[50];
		sprintf(svar,"%d %d %s",m_port, simid, m_hostname);
		//fstream filestr;
		filestr.open ("ioserverinfo.txt", fstream::out );
		filestr<<svar; 
		filestr.close();

		LocalTestSimulation->copyjobs(TestSimulation->m_pjobs);
		LocalTestSimulation->copynodes(TestSimulation->m_pnodes);
		
		LocalTestSimulation->m_ijobid=simid;
		LocalTestSimulation->m_inumprocs=TestSimulation->m_inumprocs;
		LocalTestSimulation->m_isubproc=TestSimulation->m_isubproc;
		LocalTestSimulation->m_iprocid=0;
		LocalTestSimulation->SetStateFileName("statefile.xml");
		LocalTestSimulation->SetConfigFileName("configfile.xml");		

		simdataarray[simid].isimid=simid;
		simdataarray[simid].simptr=LocalTestSimulation;
		simdataarray[simid].status=1;
		simdataarray[simid].userid=0;

		simdataarray[simid].dir=(char *)calloc(strlen(jobdir.c_str()),sizeof(char));
		strcpy(simdataarray[simid].dir,jobdir.c_str());

		isimid=&(simdataarray[simid].isimid);

		pthread_create(&simdataarray[simid].tid, NULL, (void*(*)(void*))runanddeletesimulation, (void*)isimid);

		printf("Job submitted id=%d status=1  dir=%s  threadid=%d numjobs=%d \n",simid,simdataarray[simid].dir,simdataarray[simid].tid,numsims);

			   	#ifndef IO_MSVC
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir(m_workingdir);
			   	#else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir(m_workingdir);
			   	#endif	

		}

	}
	}
	catch(int j)
	{
		printf("Server failed to submit simulation\n");
		
	}	
	}
	return SOAP_OK;
}

int ns__requestsimulation(struct soap *soap,char *simfilecontent, int *isimid)
{
	char sjd[200];
	sprintf(sjd,"%d",(int)time(NULL));
	string jobdir=sjd;

	string filename="simfile.xml";
	int iisimid;
	int status=0;

	//printf("file content\n");
	//printf("%s\n",simfilecontent);
    if(m_wsflags[IDns__requestsimulation]==1)
	{
	try
	{
	if((numsims < m_numsubprocs+m_maxsims) )
	{

	CIoGenericSteerSimulation *LocalTestSimulation;
    
	    
		if((simfilecontent != NULL) || strlen(simfilecontent)>0 )
		{
			int simid;
			if((simid=getsimdata())<0)
			{
				*isimid=-1;
				return SOAP_OK;
			}



		char command[500];
		   	#ifndef IO_MSVC
			   	  chdir(m_workingdir);		   				   	
			   	  mkdir(jobdir.c_str(),0755);
				  sprintf(command,"cp -p iogenericsim.sh %s/iogenericsim.sh",jobdir.c_str());
				  system(command);
			   	  chdir(jobdir.c_str());
			   	  system("chmod a+x iogenericsim.sh");			   	  
			#else
			   	  _chdir(m_workingdir);		   					
			   	  _mkdir(jobdir.c_str());
				  sprintf(command,"copy iogenericsim.bat %s\\iogenericsim.bat",jobdir.c_str());
				  printf("command is: %s\n",command);
				  system(command);
			   	  _chdir(jobdir.c_str());
			#endif



	       LocalTestSimulation = new CIoGenericSteerSimulation;
			
			//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		//filecontent
		//*status=TestSimulation->CreateSimulation(filename);
			//write the content to the simfile
		if(strcmp(simfilecontent,"null")!=0)
		   if((simfilecontent != NULL) || strlen(simfilecontent)>0 )
		{
            fstream filestr;
			filestr.open (filename.c_str(), fstream::out );
            filestr<<simfilecontent; 
			filestr.close();

			status=LocalTestSimulation->CreateSimulation((char *)filename.c_str());
		}
			//write data to output string

		
        /*if(standalone==1)
		{
			if(TestSimulation != NULL)
				delete TestSimulation;

			TestSimulation=LocalTestSimulation;

		}*/


					
		numsims++;

	    char svar[50];
		sprintf(svar,"%d %d %s",m_port, simid, m_hostname );
		fstream filestr;
		filestr.open ("ioserverinfo.txt", fstream::out );
		filestr<<svar; 
		filestr.close();


		LocalTestSimulation->copyjobs(TestSimulation->m_pjobs);
		LocalTestSimulation->copynodes(TestSimulation->m_pnodes);
		
		LocalTestSimulation->m_ijobid=simid;
		LocalTestSimulation->m_inumprocs=TestSimulation->m_inumprocs;
		LocalTestSimulation->m_isubproc=TestSimulation->m_isubproc;
		LocalTestSimulation->m_iprocid=0;
		LocalTestSimulation->SetStateFileName("statefile.xml");
		LocalTestSimulation->SetConfigFileName("configfile.xml");		

		simdataarray[simid].isimid=simid;
		simdataarray[simid].simptr=LocalTestSimulation;
		simdataarray[simid].status=1;
		simdataarray[simid].userid=0;

		//isimid=&(simdataarray[simid].isimid);
		*isimid=simid;
		//pthread_create(&simdataarray[simid].tid, NULL, (void*(*)(void*))runsimulation, (void*)isimid);

		simdataarray[simid].dir=(char *)calloc(strlen(jobdir.c_str()),sizeof(char));
		strcpy(simdataarray[simid].dir,jobdir.c_str());
		printf("Job requested id=%d status=1  dir=%s  numjobs=%d \n",simid,simdataarray[simid].dir,numsims);
		   	#ifndef IO_MSVC
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir(m_workingdir);		   		
			   	#else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir(m_workingdir);		   		
			#endif
		}

	}
	}
	catch(int j)
	{
		printf("Server failed to request simulation\n");
		
	}	
	}
	return SOAP_OK;
}


int ns__runrequestedsimulation(struct soap *soap,int isimid, int *istatus)
{
	string filename="simfile.xml";
	string jobdir;
	int id=isimid;
	int *iisimid;
	int status=0;
    if(m_wsflags[IDns__runrequestedsimulation]==1)
	{
    try
    {
	if((numsims <= m_maxsims) && (isimid <= numsims))
	{

		CIoGenericSteerSimulation *LocalTestSimulation;
	    LocalTestSimulation=(CIoGenericSteerSimulation *)(simdataarray[isimid].simptr);	
		status=simdataarray[isimid].status;

		if((LocalTestSimulation->WriteSimulation((char *)filename.c_str())==0))
			simdataarray[isimid].status=3;
		else
			simdataarray[isimid].status=-3;

		simdataarray[isimid].isimid=isimid;
		simdataarray[isimid].simptr=LocalTestSimulation;
		simdataarray[isimid].status=1;
		simdataarray[isimid].userid=0;
		jobdir=simdataarray[isimid].dir;
        *istatus=1;
        
        #ifndef IO_MSVC
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir(m_workingdir);		   					   	  
			   	  chdir(jobdir.c_str());
	    #else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir(m_workingdir);		   					   	  
			   	  _chdir(jobdir.c_str());
		#endif
        
        *iisimid=isimid;
        
		//isimid=&(simdataarray[isimid].isimid);
		pthread_create(&simdataarray[isimid].tid, NULL, (void*(*)(void*))runsimulation, (void*)isimid);
		printf("Job runrequested id=%d status=1  dir=%s  threadid=%d numjobs=%d \n",isimid,simdataarray[isimid].dir,simdataarray[isimid].tid,numsims);

        #ifndef IO_MSVC
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir(m_workingdir);		   		
	    #else
			   	  //_mkdir(jobdir.c_str());
			   	  chdir(m_workingdir);		   		
		#endif			

	}

	

		

    }
	catch(int j)
	{
		printf("Server failed to runrequested simulation results\n");
		
	}
	}
	return SOAP_OK;



}

int ns__setsimulationstatus(struct soap *soap,int newstatus, int isimid, int *status)
{
	string filename="simfile.xml";
	int iisimid;

    if(m_wsflags[IDns__setsimulationstatus]==1)
	{
	try
	{
	if((isimid <= numsims) )
	{
		//if((standalone==1) && (numsims>0))
		if(isimid>numsims)
			return SOAP_OK;
		simdataarray[isimid].status=newstatus;
		*status=simdataarray[isimid].status;
	}
	}
	catch(int j)
	{
		printf("Server failed to set simulation status\n");
		
	}	
	}
	return SOAP_OK;
}



int ns__simulationstatus(struct soap *soap,int isimid, int *status)
{
	string filename="simfile.xml";
	int iisimid;

    if(m_wsflags[IDns__simulationstatus]==1)
	{
	try
	{
	if((isimid <= numsims) )
	{
		//if((standalone==1) && (numsims>0))
		if(isimid>numsims)
			return SOAP_OK;  		
		*status=simdataarray[isimid].status;
	}
	}
	catch(int j)
	{
		printf("Server failed to get simulation status\n");
		
	}	
	}
	return SOAP_OK;
}

int ns__getsimulationresults(struct soap *soap,int isimid, char **result)
{
	string filename="simfile.xml";
	string sjobdir;
	int status=0;
    if(m_wsflags[IDns__getsimulationresults]==1)
	{
    try
    {
	if((numsims <= m_maxsims) && (isimid <= numsims))
	{

		if((standalone==1) && (numsims>MAXNUMTHREADS))
			return SOAP_OK;

		sjobdir=simdataarray[isimid].dir;
		   	#ifndef IO_MSVC
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir(sjobdir.c_str());
			   	#else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir(sjobdir.c_str());
			#endif	

		CIoGenericSteerSimulation *LocalTestSimulation;
	    LocalTestSimulation=(CIoGenericSteerSimulation *)(simdataarray[isimid].simptr);	
		status=simdataarray[isimid].status;


		if((LocalTestSimulation->WriteSimulation((char *)filename.c_str())==0))
			simdataarray[isimid].status=3;
		else
			simdataarray[isimid].status=-3;

			//string sresult="";
			//ifstream infile;
			//ostringstream oss (ostringstream::out);
			//infile.open (filename.c_str(), ifstream::in);
			//while (infile.good())
			//	oss << (char) infile.get();
			//sresult=oss.str();
			//infile.close();

			string sresult="";
			string sline="";
			FILE *inf;
			if((inf=fopen(filename.c_str(),"r")) != NULL )
			{
			char c;
			do
			{
				c=fgetc(inf);
				sline=c;
				if(c != EOF)
				 sresult.append(sline);
			}
			while(c != EOF);
			}
			fclose(inf);



			//read the output simulation results to the result string			
			*result=(char *)soap_malloc(soap,(1+strlen(sresult.c_str()))*sizeof(char));
			strcpy(*result,sresult.c_str());

			
			if(status==2)//only remove the simulation if it has finished i.e. status is 2
			{
				pthread_cancel(simdataarray[isimid].tid);
				simdataarray[isimid].isimid=-1;
				simdataarray[isimid].simptr=NULL;
				simdataarray[isimid].status=-1;
				simdataarray[isimid].userid=NULL;
				//simdataarray[isimid].tid=0;
				numsims--;
				if(/*(standalone!=1 ) &&*/ (LocalTestSimulation != NULL))
					delete LocalTestSimulation;
			}
			
			#ifndef IO_MSVC
			   	  chdir(m_workingdir);		   		
			#else
			   	  _chdir(m_workingdir);		   		
			#endif	
	}

	

		

    }
	catch(int j)
	{
		printf("Server failed to get simulation results\n");
		
	}
	}
	return SOAP_OK;



}

int ns__deletesimulation(struct soap *soap,int isimid, int *status)
{
string filename="simfile.xml";
string sjobdir;
    if(m_wsflags[IDns__deletesimulation]==1)
	{
try
{
	if((numsims <= m_maxsims) && (isimid <= numsims))
	{

		//if((standalone==1) && (numsims>MAXNUMTHREADS))
		//	return SOAP_OK;
		sjobdir=simdataarray[isimid].dir;
	
		   	#ifndef IO_MSVC
		   		//chdir(m_workingdir);		   				   	
			   	  //mkdir(jobdir.c_str(),0755);
			   	  //chdir(sjobdir.c_str());
			 ;
			   	#else
			   	
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir(sjobdir.c_str());
			#endif		
		CIoGenericSteerSimulation *LocalTestSimulation;
	    LocalTestSimulation=(CIoGenericSteerSimulation *)(simdataarray[isimid].simptr);	
		*status=simdataarray[isimid].status;

//		pthread_cancel(simdataarray[isimid].tid);
		simdataarray[isimid].isimid=-1;
		simdataarray[isimid].simptr=NULL;
		simdataarray[isimid].status=-1;
		simdataarray[isimid].userid=NULL;
		//simdataarray[isimid].tid=0;



		numsims--;
		if(/*(standalone!=1 ) && */(LocalTestSimulation != NULL))
			delete LocalTestSimulation;
			
		#ifndef IO_MSVC
			   	  chdir(m_workingdir);		   		
			   	  
			   	  string sdelcommand="/bin/rm -rf ";
			   	  
			   	  printf("deleting %s %s\n",sdelcommand.c_str(),sjobdir.c_str());
			   	  sdelcommand.append(sjobdir);
			   	  system(sdelcommand.c_str());
				  //chdir("..");
				  //rmdir(sjobdir.c_str());
				  printf("deleting %s %s\n",sdelcommand.c_str(),sjobdir.c_str());
				  
			#else
			   	  remove("*");
			   	  _chdir("..");
			   	  _rmdir(sjobdir.c_str());
			#endif

		   //pthread_cancel(simdataarray[isimid].tid);

	}
}
catch(int j)
{
	printf("Server failed to delete simulation\n");
	
}
	}
	return SOAP_OK;



}

int ns__writesimulation(struct soap *soap,int id,char *filename, char **filecontent)
{
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

    if(m_wsflags[IDns__writesimulation]==1)
	{
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
						status=LocalSimulation->WriteSimulation(filename);
					//write simulation to the string filecontent
						string sresult="";
						string sline="";
						FILE *inf;
						if((inf=fopen(filename,"r")) != NULL )
						{
						char c;
						do
						{
							c=fgetc(inf);
							sline=c;
							if(c != EOF)
							 sresult.append(sline);
						}
						while(c != EOF);
						}
						fclose(inf);
						

						//read the output simulation results to the result string			
						*filecontent=(char *)soap_malloc(soap,(strlen(sresult.c_str()))*sizeof(char));
						strcpy(*filecontent,sresult.c_str());
						//printf("%s\n",*filecontent);

						//ofstream outfile;
						//ostringstream oss (ostringstream::out);
						//outfile.open ("testns.xml", ofstream::out);
						//outfile << *filecontent;
							
						//outfile.close();
					
				}
				else
					status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				char *sresult=(char *)calloc(10000, sizeof(char));

				soap_call_ns__writesimulation(&m_soapclient, sserverclient, "",id,filename,&sresult);

										

				//read the output simulation results to the result string			
				*filecontent=(char *)soap_malloc(soap,(1+strlen(sresult))*sizeof(char));
				strcpy(*filecontent,sresult);
				//printf("%s\n",*filecontent);
				free(sresult);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to write simulation\n");
	
		
	}
	}
	//free(sstr);

	
	return SOAP_OK;
}

int ns__writelocalsimulation(struct soap *soap,int id,char *filename, char **filecontent)
{
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	string sresult="";
	string sline="";

    if(m_wsflags[IDns__writelocalsimulation]==1)
	{
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    
				if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
						status=LocalSimulation->WriteSimulation(filename);
					//write simulation to the string filecontent
						FILE *inf;
						if((inf=fopen(filename,"r")) != NULL )
						{
						char c;
						do
						{
							c=fgetc(inf);
							sline=c;
							if(c != EOF)
							 sresult.append(sline);
						}
						while(c != EOF);
						}
						fclose(inf);

						//read the output simulation results to the result string			
						*filecontent=(char *)soap_malloc(soap,(1+strlen(sresult.c_str()))*sizeof(char));
						strcpy(*filecontent,sresult.c_str());
						remove(filename);
						//printf("%s\n",*filecontent);
					
				}
				else
					status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				char *sresult=(char *)calloc(10000, sizeof(char));

				soap_call_ns__writesimulation(&m_soapclient, sserverclient, "",id,filename,&sresult);

										

				//read the output simulation results to the result string			
				*filecontent=(char *)soap_malloc(soap,(1+strlen(sresult))*sizeof(char));
				strcpy(*filecontent,sresult);
				//printf("%s\n",*filecontent);
				free(sresult);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to write local simulation\n");
	
		
	}
	}
	//free(sstr);

	
	return SOAP_OK;
}

int ns__readsimulation(struct soap *soap,int id,char *filename, int *status)
{
	char slast[]=".rub";
	char clast[]=".xml";
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;

	if(m_wsflags[IDns__readsimulation]==1)
	{
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					int scl=strlen(filename);
					if(scl>4)
					for(i=0; i<4; i++)
						slast[i]=filename[scl-4+i];
					if(strcmp(clast,slast)==0)    
						*status=LocalSimulation->ReadSimulation(filename);
					else
					{
						//filename is the actual content to be read into the simulation
						char simfilename[200];
						sprintf(simfilename,"simfile%d.xml",id);
						
						ofstream outfile;
						outfile.open (simfilename, ofstream::out);
						outfile<<filename;
						outfile.close();			
						
						*status=LocalSimulation->ReadSimulation(simfilename);
					}

					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
	
				soap_call_ns__readsimulation(&m_soapclient, sserverclient, "",id,filename,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to read simulation\n");
	
		
	}
	}
	//free(sstr);

	
	return SOAP_OK;

}

int ns__readlocalsimulation(struct soap *soap,int id,char *filename, int *status)
{
	char slast[]=".rub";
	char clast[]=".xml";
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;

	if(m_wsflags[IDns__readlocalsimulation]==1)
	{
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					//int scl=strlen(filename);
					//if(scl>4)
					//for(i=0; i<4; i++)
					//	slast[i]=filename[scl-4+i];
					//if(strcmp(clast,slast)==0)    
					//	*status=LocalSimulation->ReadSimulation(filename);
					//else
					//{
						//filename is the actual content to be read into the simulation
						char simfilename[200];
						sprintf(simfilename,"simfile%d.xml",id);
						
						ofstream outfile;
						outfile.open (simfilename, ofstream::out);
						outfile<<filename;
						outfile.close();			
						
						*status=LocalSimulation->ReadSimulation(simfilename);
					//}

					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
	
				soap_call_ns__readlocalsimulation(&m_soapclient, sserverclient, "",id,filename,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to read local simulation\n");
	
		
	}
	}
	//free(sstr);

	
	return SOAP_OK;

}



/*int ns__writestate(struct soap *soap,int id,char *filename, char **filecontent)
{
	try
	{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		TestSimulation->WriteState(filename);
		//write the content of the file
		//to the string **filecontent
	}
	}
	catch(int j)
	{
		printf("Server failed to write state\n");
		
	}

	return SOAP_OK;
}


int ns__writeconfig(struct soap *soap,int id,char *filename, char **filecontent)
{
	try
	{
	if(TestSimulation != NULL)
		TestSimulation->WriteConfig(filename);
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
	}
	catch(int j)
	{
		printf("Server failed to write config\n");
		
	}
	return SOAP_OK;
}*/


int ns__exitiome(struct soap *soap,int id, int *status)
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;

	if(m_wsflags[IDns__exitiome]==1)
	{
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					delete LocalSimulation;
					LocalSimulation=NULL;					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
	
				soap_call_ns__exitiome(&m_soapclient, sserverclient, "",id,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to exit IOME\n");
	
		
	}

	//free(sstr);
    finish=1;
	}
	
	return SOAP_OK;

}



int ns__addparamdouble(struct soap *soap,int id,char *name, double value, int iflag, int *status )
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;

	if(m_wsflags[IDns__addparamdouble]==1)
	{
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					*status=LocalSimulation->AddParamDouble(value,sname,iflag);					
				}
				else
					*status=1;

			}
			else
			{
				port=TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__addparamdouble(&m_soapclient, sserverclient, "",id,name,value,iflag,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to add double param\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;

}


int ns__addparamint(struct soap *soap, int id,char *name, int value, int iflag, int *status )
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__addparamint]==1)
	{


	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					*status=LocalSimulation->AddParamInt(value,sname,iflag);					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__addparamint(&m_soapclient, sserverclient, "",id,name,value,iflag,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to add int param\n");
	
		
	}

	//free(sstr);
    //finish=1;
	}
	
	return SOAP_OK;
}


int ns__addparamvec(struct soap *soap, int id,char *name, struct fdata value, int n, int iflag, int *status )
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__addparamvec]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
							string sname=name;
							for(int i=0; i<n; i++)
								printf("val %d %f\n",i, value.__ptr[i]);
							*status=LocalSimulation->AddParamVec(value.__ptr,n,sname,iflag);					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__addparamvec(&m_soapclient, sserverclient, "",id,name,value,n,iflag,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to add vec param\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;

}


int ns__addparammat(struct soap *soap, int id,char *name, struct fdata value, int nr, int nc,  int iflag, int *status )
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';


	if(m_wsflags[IDns__addparammat]==1)
	{
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
							string sname=name;
							int n=nr*nc;
							//for(int i=0; i<n; i++)
							//	printf("val %d %f\n",i, value.__ptr[i]);
							*status=LocalSimulation->AddParamMat(value.__ptr,nr,nc,sname,iflag);					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__addparammat(&m_soapclient, sserverclient, "",id,name,value,nr,nc,iflag,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to add mat param\n");
	
		
	}

	//free(sstr);
    //finish=1;

	}
	return SOAP_OK;

}


int ns__addparamstring(struct soap *soap, int id,char *name, char *value, int iflag, int *status )
{

	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	string sname=name;
	string svalue=value;


	if(m_wsflags[IDns__addparamstring]==1)
	{
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					*status=LocalSimulation->AddParamString(svalue,sname,iflag);					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__addparamstring(&m_soapclient, sserverclient, "",id,name,value,iflag,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to add string param\n");
	
		
	}
	}

	//free(sstr);
    //finish=1;

	
	return SOAP_OK;

}


int ns__addparammmat3d(struct soap *soap, int id,char *name, struct fdata value, int n, int p, int q, int nr, int nc,int iflag, int *status )
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__addparammmat3d]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;
				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					*status=LocalSimulation->AddParammmat3d(value.__ptr,n,p,q,nr,nc,sname,iflag);
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__addparammmat3d(&m_soapclient, sserverclient, "",id,name,value,n,p,q,nr,nc,iflag,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to add mat param\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;
	
	return SOAP_OK;

}



int ns__addmetadata(struct soap *soap,int id,char *name, char *property, int *status)
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__addmetadata]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					string scontent=property;		
					LocalSimulation->AddMetadata(sname,scontent);
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__addmetadata(&m_soapclient, sserverclient, "",id,name,property,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to add metadata\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;

}

int ns__deletemetadata(struct soap *soap,int id,char *name, int *status)
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__deletemetadata]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;	
					LocalSimulation->DeleteMetadata(sname);
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__deletemetadata(&m_soapclient, sserverclient, "",id,name,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to delete metadata\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;

}

int ns__getparamdouble(struct soap *soap,int id,char *name, double *value )
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    //*status=0;
	string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	if(m_wsflags[IDns__getparamdouble]==1)
	{
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
							string sname=name;
							LocalSimulation->GetParamDouble(value,sname);
				}

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__getparamdouble(&m_soapclient, sserverclient, "",id,name,value);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get double\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;
}


int ns__getparamint(struct soap *soap, int id,char *name, int *value )
{

	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__getparamint]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
							string sname=name;
							LocalSimulation->GetParamInt(value,sname);
				}
				else
					status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__getparamint(&m_soapclient, sserverclient, "",id,name,value);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get int\n");
	
		
	}

	//free(sstr);
    //finish=1;
	}
	
	return SOAP_OK;



}


int ns__getparamvec(struct soap *soap, int id,char *name, int n, struct fdata **value )
{

	double *fval=(double *)calloc(n,sizeof(double));
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__getparamvec]==1)
	{
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
						string sname=name;
						LocalSimulation->GetParamVec(fval,n,sname);
						//value=(struct fdata *)malloc(sizeof(struct fdata));
						//value->__ptr=(double *)calloc(n,sizeof(double));
						(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
						(*value)->__ptr=(double *)soap_malloc(soap,n*sizeof(double));

				        
						for(int i=0; i<n; i++)
						{
							(*value)->__ptr[i]=fval[i];
							printf("%f \n",fval[i]);
						}
						(*value)->__size=n;
					}
					else
						status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				struct fdata *vval;

				vval=(struct fdata *)malloc(sizeof(struct fdata));
				(*vval).__ptr=(double *)malloc(n*sizeof(double));
				double *dfval=(*vval).__ptr;

				soap_call_ns__getparamvec(&m_soapclient, sserverclient, "",id,name,n,&vval);

				(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
				(*value)->__ptr=(double *)soap_malloc(soap,n*sizeof(double));

		        
				for(int i=0; i<n; i++)
				{
					(*value)->__ptr[i]=(*vval).__ptr[i];
					printf("%f \n",(*vval).__ptr[i]);
				}
				(*value)->__size=n;
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get int\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;

}


int ns__getparammat(struct soap *soap, int id,char *name, int nr, int nc, struct fdata **value )
{

	double *fval=(double *)calloc(nr*nc,sizeof(double));
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__getparammat]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					double *fval=(double *)calloc(nr*nc,sizeof(double));
					//value=(struct fdata *)malloc(sizeof(struct fdata));
					//value->__ptr=(double *)calloc(nr*nc,sizeof(double));
					//double *fval=(double *)soap_malloc(soap,nr*nc*sizeof(double));
					(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
					(*value)->__ptr=(double *)soap_malloc(soap,nr*nc*sizeof(double));

					string sname=name;
					LocalSimulation->GetParamMat(fval,nr,nc,sname);
					(*value)->__size=nr*nc;
					for(int i=0; i<nr*nc; i++)
					{
						(*value)->__ptr[i]=fval[i];
						//printf("%d %f \n",i,fval[i]);
					}					
				}
					else
						status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				double *darray=(double *)calloc(nr*nc,sizeof(double));
				struct fdata *mval;

				mval=(struct fdata *)malloc(sizeof(struct fdata));
				(*mval).__ptr=(double *)malloc(nr*nc*sizeof(double));
				double *dfval=(*mval).__ptr;	
				soap_call_ns__getparammat(&m_soapclient, m_serverclient, "", id,name,nr,nc,&mval);

					(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
					(*value)->__ptr=(double *)soap_malloc(soap,nr*nc*sizeof(double));

			        
					for(int i=0; i<nr*nc; i++)
					{
						(*value)->__ptr[i]=(*mval).__ptr[i];
						//printf("%f \n",(*mval).__ptr[i]);
					}
					(*value)->__size=nr*nc;


			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get mat\n");
	
		
	}

	//free(sstr);
    //finish=1;
	}
	
	return SOAP_OK;


}


int ns__getparamstring(struct soap *soap, int id,char *name, char **value )
{

	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__getparamstring]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					string svalue;
					LocalSimulation->GetParamString(&svalue,sname);
					//*value=(char *)calloc(1+strlen(sname.c_str()),sizeof(char));
					*value=(char *)soap_malloc(soap,(1+strlen(svalue.c_str()))*sizeof(char));
					strcpy(*value,svalue.c_str());
				}
				else
					status=1;

			}
			else
			{
				string sval="";
				char *msval=(char *)sval.c_str();

				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				//soap_call_ns__getparamint(&m_soapclient, sserverclient, "",id,name,value);

				soap_call_ns__getparamstring(&m_soapclient, sserverclient, "", id,name,&msval);
				*value=(char *)soap_malloc(soap,(1+strlen(msval))*sizeof(char));
				strcpy(*value,msval);

			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get string\n");
	
		
	}

	//free(sstr);
    //finish=1;
	}
	
	return SOAP_OK;



}


int ns__getparammmat3d(struct soap *soap, int id,char *name, int n, int p, int q, int nr, int nc, struct fdata **value  )
{
	double *fval=(double *)calloc(n*p*q*nr*nc,sizeof(double));
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__getparammmat3d]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					//double *fval=(double *)calloc(n*p*q*nr*nc,sizeof(double));
					(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
					(*value)->__ptr=(double *)soap_malloc(soap,n*p*q*nr*nc*sizeof(double));


					//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
					string sname=name;
					//TestSimulation->GetParammmat3d(*mmat3d,n,p,q,nr,nc,sname);
					LocalSimulation->GetParammmat3d(fval,n,p,q,nr,nc,sname);

					(*value)->__size=n*p*q*nr*nc;
					for(int i=0; i<n*p*q*nr*nc; i++)
					{
						(*value)->__ptr[i]=fval[i];
						//printf("%d %f \n",i,fval[i]);
					}
				
				}
					else
						status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);

				double *darray=(double *)calloc(n*p*q*nr*nc,sizeof(double));
				struct fdata *fval;
				int na=n*p*q*nr*nc;

				fval=(struct fdata *)malloc(sizeof(struct fdata));
				(*fval).__ptr=(double *)malloc(n*p*q*nr*nc*sizeof(double));
				double *dfval=(*fval).__ptr;

				soap_call_ns__getparammmat3d(&m_soapclient, sserverclient, "", id,name,n,p,q,nr,nc,value);
				(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
				(*value)->__ptr=(double *)soap_malloc(soap,na*sizeof(double));

			        
				for(int i=0; i<na; i++)
				{
					(*value)->__ptr[i]=dfval[i];
					printf("%f \n",dfval[i]);
				}
				(*value)->__size=na;

				free(darray);

			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get mat\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;


}



int ns__getmetadata(struct soap *soap, int id, char *name, char **property)
{

	if(m_wsflags[IDns__getmetadata]==1)
	{
	if(TestSimulation != NULL)
	{
		string sval;
		sval=TestSimulation->GetMetadata(name);
		//*property=(char *)calloc(1+strlen(sval.c_str()),sizeof(char));
		*property=(char *)soap_malloc(soap,(1+strlen(sval.c_str()))*sizeof(char));
		strcpy(*property,(const char *)(sval.c_str()));
	}


	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sval;
					sval=LocalSimulation->GetMetadata(name);
					//*property=(char *)calloc(1+strlen(sval.c_str()),sizeof(char));
					*property=(char *)soap_malloc(soap,(1+strlen(sval.c_str()))*sizeof(char));
					strcpy(*property,(const char *)(sval.c_str()));
				}
				else
					status=1;

			}
			else
			{
				string sval="";
				char *msval=(char *)sval.c_str();

				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				//soap_call_ns__getparamint(&m_soapclient, sserverclient, "",id,name,value);

				soap_call_ns__getmetadata(&m_soapclient, sserverclient, "", id,name,&msval);
				*property=(char *)soap_malloc(soap,(1+strlen(msval))*sizeof(char));
				strcpy(*property,msval);

			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get metadata\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;

}

int ns__listmetadata(struct soap *soap, int id, char **list)
{

	if(m_wsflags[IDns__listmetadata]==1)
	{
	//if(TestSimulation != NULL)
	//{
					//char *slist=(char *)calloc(2000,sizeof(char));
					//slist[0]='\0';

					//TestSimulation->GetMetadataList((char *)slist);
					//printf("%s\n",slist.c_str());

					//*list=(char *)soap_malloc(soap,(1+strlen(slist))*sizeof(char));
					//strcpy(*list,(const char *)(slist));
					
					//free(slist);				
	//}


	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					char *slist=(char *)calloc(2000,sizeof(char));
					slist[0]='\0';

					LocalSimulation->ListMetadata((char *)slist);
					//printf("%s\n",slist.c_str());

					*list=(char *)soap_malloc(soap,(1+strlen(slist))*sizeof(char));
					strcpy(*list,(const char *)(slist));
					
					free(slist);				
				}
				else
					status=1;

			}
			else
			{
				string sval="";
				char *msval=(char *)sval.c_str();

				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				//soap_call_ns__getparamint(&m_soapclient, sserverclient, "",id,name,value);

				soap_call_ns__listmetadata(&m_soapclient, sserverclient, "", id,&msval);
				*list=(char *)soap_malloc(soap,(1+strlen(msval))*sizeof(char));
				strcpy(*list,msval);

			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get metadata list\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;

}

int ns__setparamdouble(struct soap *soap, int id,char *name, double value, int *status )
{

	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__setparamdouble]==1)
	{


	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					*status=LocalSimulation->SetParamDouble(value,sname);					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__setparamdouble(&m_soapclient, sserverclient, "",id,name,value,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to set double param\n");
	
		
	}

	//free(sstr);
    //finish=1;
	}
	
	return SOAP_OK;





}


int ns__setparamint(struct soap *soap, int id,char *name, int value, int *status  )
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__setparamint]==1)
	{


	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					*status=LocalSimulation->SetParamInt(value,sname);					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__setparamint(&m_soapclient, sserverclient, "",id,name,value,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to set int param\n");
	
		
	}

	//free(sstr);
    //finish=1;

	}

	return SOAP_OK;


}


int ns__setparamvec(struct soap *soap, int id,char *name, struct fdata value, int n, int *status  )
{

	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;

	if(m_wsflags[IDns__setparamvec]==1)
	{


	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					*status=LocalSimulation->SetParamVec(value.__ptr,n,sname,7);					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__setparamvec(&m_soapclient, sserverclient, "",id,name,value,n,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to set vec param\n");
	
		
	}

	//free(sstr);
    //finish=1;
	}
	
	return SOAP_OK;


}


int ns__setparammat(struct soap *soap, int id,char *name, struct fdata value, int nr, int nc, int *status  )
{

	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	if(m_wsflags[IDns__setparammat]==1)
	{


	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					*status=LocalSimulation->SetParamMat(value.__ptr,nr,nc,sname,7);					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__setparammat(&m_soapclient, sserverclient, "",id,name,value,nr,nc,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to set mat param\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;
}


int ns__setparamstring(struct soap *soap, int id,char *name, char *value, int *status  )
{

	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__setparamstring]==1)
	{


	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					string svalue=value;
					*status=LocalSimulation->SetParamString(svalue,sname);					
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__setparamstring(&m_soapclient, sserverclient, "",id,name,value,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to set string param\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;



}


int ns__setparammmat3d(struct soap *soap, int id,char *name, struct fdata value,  int n, int p, int q, int nr, int nc, int *status  )
{

	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';

	if(m_wsflags[IDns__setparammmat3d]==1)
	{

	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					*status=LocalSimulation->SetParammmat3d(value.__ptr,n,p,q,nr,nc,sname);
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__setparammmat3d(&m_soapclient, sserverclient, "",id,name,value,n,p,q,nr,nc,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to set mmat3d param\n");
	
		
	}

	//free(sstr);
    //finish=1;
	}
	
	return SOAP_OK;
}



int ns__setmetadata(struct soap *soap,int id, char *name, char *property, int *status)
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;

	if(m_wsflags[IDns__setmetadata]==1)
	{

	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					string sname=name;
					string sproperty=property;
					LocalSimulation->SetMetadata(sname,sproperty);				
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__setmetadata(&m_soapclient, sserverclient, "",id,name,property,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to set metadata param\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;


}

int ns__deleteparam(struct soap *soap,char *name, int id, int *status )
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    *status=0;

	if(m_wsflags[IDns__deleteparam]==1)
	{

	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					*status=LocalSimulation->DeleteParam(name);				
				}
				else
					*status=1;

			}
			else
			{
				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				soap_call_ns__deleteparam(&m_soapclient, sserverclient, "",name,id,status);
			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to delete param\n");
	
		
	}

	//free(sstr);
    //finish=1;
	}
	
	return SOAP_OK;


}


int ns__listparam(struct soap *soap,char *type, int id, char  **list )
{
	/*char *slist=(char *)calloc(2000,sizeof(char));
	slist[0]='\0';
	if(TestSimulation != NULL)
	{
		TestSimulation->ListParam(type,(char *)slist);
		//printf("%s\n",slist.c_str());

		*list=(char *)soap_malloc(soap,(1+strlen(slist))*sizeof(char));
		strcpy(*list,(const char *)(slist));
	}
	free(slist);*/



	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;

	if(m_wsflags[IDns__listparam]==1)
	{

	//string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					char *slist=(char *)calloc(2000,sizeof(char));
					slist[0]='\0';

					LocalSimulation->ListParam(type,(char *)slist);
					//printf("%s\n",slist.c_str());

					*list=(char *)soap_malloc(soap,(1+strlen(slist))*sizeof(char));
					strcpy(*list,(const char *)(slist));
					
					free(slist);
				}
				else
					status=1;

			}
			else
			{
				string sval="";
				char *msval=(char *)sval.c_str();

				TestSimulation->GetJobPort(id);
				sserver=TestSimulation->GetJobServer(id);
				sprintf(sserverclient,"%s:%d",sserver.c_str(),port);
				//soap_call_ns__getparamint(&m_soapclient, sserverclient, "",id,name,value);

				soap_call_ns__listparam(&m_soapclient, sserverclient, "", type,id,&msval);
				*list=(char *)soap_malloc(soap,(1+strlen(msval))*sizeof(char));
				strcpy(*list,msval);

			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to get param list\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;


}









int ns__getnumobj(struct soap *soap,int id, int *numobj)
{
	int idvalue;
	int myid;
	string sserver;
	char sserverclient[400];
	int port;

	if(m_wsflags[IDns__getnumobj]==1)
	{
	if(TestSimulation != NULL)
	{

			
			*numobj=TestSimulation->GetNumJobs();
			printf("%d\n",*numobj);

	}
	}
	return SOAP_OK;
}

int ns__getobjnum(struct soap *soap,int id, int *objnum)
{
	int idvalue;
	int myid;
	string sserver;
	char sserverclient[400];
	int port;
	if(m_wsflags[IDns__getobjnum]==1)
	{
	if(TestSimulation != NULL)
	{
		if(m_allocsubprocs<m_numsubprocs)
		{
			*objnum=TestSimulation->GetJobid(TestSimulation->m_iprocid,m_allocsubprocs);
			m_allocsubprocs++;
		}
		else
			*objnum=-1;

		printf("%d\n",*objnum);
	}
		
	}
	
	return SOAP_OK;
}


int ns__testgroupbarrier(struct soap *soap,int id, int *state)
{

	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;

	if(m_wsflags[IDns__testgroupbarrier]==1)
	{
	//string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
					*state=LocalSimulation->m_ibarrier;
				}
				else
					status=1;

			}
			else
			{
			soap_call_ns__testgroupbarrier(&m_soapclient, sserverclient, "", id,state );

			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to test barrier\n");
	
		
	}

	//free(sstr);
    //finish=1;

	}
	return SOAP_OK;


}

int ns__setgroupbarrier(struct soap *soap,int id, int state, int *newstate)
{
	int i;
	int jpid=0;
	int isubprocid=0;
	int port;
	string sserver;
	char sserverclient[400];
    int status=0;
	if(state>1) state=1;
	if(state<0) state=0;


	if(m_wsflags[IDns__setgroupbarrier]==1)
	{
	//string sname=name;
	//char *sstr=(char *)calloc(2000,sizeof(char));
	//sstr[0]='\0';
	CIoGenericSteerSimulation *LocalSimulation;
	try
	{
		if(TestSimulation != NULL)
		{
			
			jpid=TestSimulation->GetJobProcid(id);
		    if(jpid==TestSimulation->m_iprocid)
			{
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
				{
					isubprocid=id;

				}
				else
				  isubprocid=TestSimulation->GetJobSubprocid(id);
				
				if((LocalSimulation=(simdataarray[isubprocid].simptr))!=NULL)
				{
								if((state==1) && (TestSimulation->m_ibarrier==1))
									 *newstate=1;
								else
									LocalSimulation->m_ibarrier=*newstate=state;
				}
				else
					status=1;

			}
			else
			{
			soap_call_ns__setgroupbarrier(&m_soapclient, sserverclient, "", id,state, newstate );

			}

			//*value=(char *)soap_malloc(soap,(1+strlen(sstr))*sizeof(char));
		    //strcpy(*value,sstr);
 
		}
	}
	catch(int j)
	{
		printf("Server failed to test barrier\n");
	
		
	}
	}
	//free(sstr);
    //finish=1;

	
	return SOAP_OK;


}


int getsimdata()
{
   int index=1;
   int i=0;
   struct simdata *sdata;
   
   if(simdataarray != NULL)
   {
   	for(i=1; i<m_maxsims; i++)
   	{
   		sdata= &simdataarray[i];
   		if(sdata !=NULL)
   		   if((sdata->isimid)==-1)
   		        return i;
   	}
   	
   	
   }
   return  index;	
	
}
