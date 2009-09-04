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

//int initiome_(char *simname, char *simxslfile, char *simfilename, char *statefilename, char *configfilename, int port, int istandalone);
int exitiome_(int port, char *sserver);
int newsimulation_( int id, char *simname, int port, char *sserver );


int runsimulationstep_( int id, int istepnum, int port, char *sserver);


int newsimulation_( int id, char *simname, int port, char *sserver );
int createsimulation_( int id, char *simfile, char *simname, int port, char *sserver );
int runsimulation_( int id, char *simfilecontent, int port, char *sserver );

int requestsimulation_(char *simfilecontent, int *isimid, int port, char *sserver);
int runrequestedsimulation_(int isimid, char **status, int port, char *sserver);

int submitsimulation_(char *simfilecontent, int *isimid, int port, char *sserver);
int simulationstatus_(int isimid, char **status, int port, char *sserver);
int getsimulationresults_(int isimid, char **result, int port, char *sserver);
int deletesimulation_(int isimid, int *status, int port, char *sserver);


int readsimulation_( int id, char *simfile, int port, char *sserver );
int writesimulation_( int id, char *simfile,  int port, char *sserver);
int readlocalsimulation_( int id, char *simfile, int port, char *sserver );
int writelocalsimulation_( int id, char *simfile,  int port, char *sserver);

int addintparam_( int id, char *sname,int iv,int iflag,  int port, char *sserver );
int adddoubleparam_( int id, char *sname,double fv,int iflag,  int port, char *sserver);
int addstringparam_( int id, char *sname,char *sv,int iflag,  int port, char *sserver);
int addmatparam_( int id, char *sname,double *vv,int nr, int nc,int iflag,   int port, char *sserver);
int addvecparam_( int id, char *sname,double *vv,int n,int iflag,   int port, char *sserver);
int addmmat3dparam_( int id,char *sname,double *vv ,int ni, int nj, int nk, int nr, int nc,int iflag,   int port, char *sserver);

int addmetadata_( int id,char *sname, char *sproperty,  int port, char *sserver);
int setmetadata_( int id,char *sname, char *sproperty,  int port, char *sserver);
int getmetadata_( int id,char *sname, char *sproperty,  int port, char *sserver);
int deletemetadata_( int id,char *sname,  int port, char *sserver);
int listmetadata_(int id, char  **list ,  int port, char *sserver);



int setintparam_( int id,char *sname,int iv,  int port, char *sserver );
int setdoubleparam_( int id,char *sname,double fv,  int port, char *sserver);
int setstringparam_( int id,char *sname,char *sv,  int port, char *sserver);
int setmatparam_( int id,char *sname,double *vv,int nr, int nc,   int port, char *sserver);
int setvecparam_( int id,char *sname,double *vv,int n,   int port, char *sserver);
int setmmat3dparam_( int id,char *sname,double *vv ,int ni, int nj, int nk, int nr, int nc,   int port, char *sserver);

int getintparam_( int id,char *sname,int *iv,  int port, char *sserver );
int getdoubleparam_( int id,char *sname,double *fv,  int port, char *sserver);
int getstringparam_( int id,char *sname,char **sv,  int port, char *sserver);
int getmatparam_( int id,char *sname,double **vv,int nr, int nc,   int port, char *sserver);
int getvecparam_( int id,char *sname,double **vv,int n,   int port, char *sserver);
int getmmat3dparam_( int id,char *sname,double **vv ,int ni, int nj, int nk, int nr, int nc,   int port, char *sserver);

int deleteparam_( int id,char *name, int *status,  int port, char *sserver );


int listparam_(char *type, int id, char  **list ,  int port, char *sserver);



int getnumobj_(int *numobj, int id,  int port, char *sserver);
int getobjnum_(int *objnum, int id);


int testgroupbarrier_(int id, int *state,  int port, char *sserver);
int setgroupbarrier_(int id, int *state,  int port, char *sserver);



