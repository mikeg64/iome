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
	#include <iome/simulation/IoInitialiser.h>
	#include <iome/simulation/soapH.h>
	#include <iome/simulation/IoGenericSteerSimulation.h>
	#include <iome/simulation/IoSteerWS.nsmap>
    #include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>

#else
	#include <iome/simulation/IoInitialiser.h>
	#include <iome/simulation/soapH.h>
	#include <iome/simulation/IoGenericSteerSimulation.h>
	#include <iome/simulation/IoSteerWS.nsmap>

	#include <direct.h>
	
	#include <sys/stat.h>
	#include <sys/types.h>
#endif

//#include "stdafx.h"
//#include "IoTestDEVSimulation.h"
//#include "IoTestAgentSimulation.h"
#include <time.h>
#include <pthread.h>	// use Pthreads
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

static CIoInitialiser m_Init;
CIoGenericSteerSimulation *TestSimulation;
static void *runsimulation(void *simulationid);
static void *runscript(void *simulation);
static void *executesimulation(void *simulation);	




int m_isimfinished=0;
char m_serverclient[300] = "localhost:8080";
char m_hostname[300] = "localhost";
int m_port=8080;
int port=m_port;
struct soap m_soapclient;

struct simdata 
{
public :
	CIoGenericSteerSimulation  *simptr;
	int isimid;
	int status;
	void *userid; //for secure service user would provide ssl key public key?
	char *sscript;
	char *dir;
	pthread_t tid;
	int ipid;
};




//array of simulations created by SAAS requests
int numsims=0;
struct simdata *simdataarray=NULL;
int m_maxsims=10;


int m_numsubprocs=0;
int m_allocsubprocs=0; //this is set by bthe get objnum routine
                       //which allocates a subprocessor id to each simulation
                       //it is incremented each time an allocation is made
                       //all processors MUST make ONE call to getobjnum at the
                       //start of the routine
//array of simulations created by multiple threads
int newsimind;
struct simdata *simsubprocs=NULL;

int getsimdata();

int finish=0;

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
 
                 
                   

int AddParam(int itype, int argc, char **argv);
int GetParam( int itype, int argc, char **argv);
int SetParam(int itype, int argc, char **argv);

int SetMetadata( int argc, char **argv);
int AddMetadata( int argc, char **argv);
int GetMetadata( int argc, char **argv);



int ExitIOME(int argc, char **argv);


int NewSimulation( int argc, char **argv);
int CreateSimulation( int argc, char **argv);
int RunSimulation( int argc, char **argv);
int RequestSimulation( int argc, char **argv);
int RunRequestedSimulation( int argc, char **argv);
int SubmitSimulation( int argc, char **argv);
int SimulationStatus( int argc, char **argv);
int SetSimulationStatus( int argc, char **argv);
int DeleteSimulation( int argc, char **argv);
int GetSimulationResults( int argc, char **argv);
int RunSimulationStep( int argc, char **argv);
int ReadSimulation( int argc, char **argv);
int WriteSimulation( int argc, char **argv);
int ReadLocalSimulation( int argc, char **argv);
int WriteLocalSimulation( int argc, char **argv);
int GroupBarrier( int argc, char **argv);
/*int ReadConfig( int argc, char **argv);
int WriteConfig( int argc, char **argv);*/

/*int ReadState( int argc, char **argv);
int WriteState( int argc, char **argv);*/
int GetNumProcs( int argc, char **argv);
int GetProcID( int argc, char **argv);
/*char *vname 
int n

int nr,nc

int ni,nj,nk,nr,nc
int flag
int port 
char *server*/
