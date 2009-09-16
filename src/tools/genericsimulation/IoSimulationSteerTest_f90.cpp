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
#else
	#include "..\IoSimulation\IoInitialiser.h"
	#include "..\IoSimulation\soapH.h"
	#include "..\IoSimulation\IoGenericSteerSimulation.h"
	#include "..\IoSimulation\IoSteerWS.nsmap"
#endif

//#include "stdafx.h"
//#include "IoTestDEVSimulation.h"
//#include "IoTestAgentSimulation.h"

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

static CIoInitialiser m_Init;
CIoGenericSteerSimulation *TestSimulation;
static void *executesimulation(void *simulation);	
int m_isimfinished=0;
char m_serverclient[300] = "localhost:8080";
struct soap m_soapclient;

int AddParam(int itype, int argc, char **argv);
int GetParam( int itype, int argc, char **argv);
int SetParam(int itype, int argc, char **argv);

int SetMetadata( int argc, char **argv);
int AddMetadata( int argc, char **argv);
int GetMetadata( int argc, char **argv);


int InitIOME(char *simname, char *simfilename, char *statefilename, char *configfilename, int port);
int ExitIOME(int argc, char **argv);

int CreateSimulation( int argc, char **argv);
int ReadSimulation( int argc, char **argv);
int WriteSimulation( int argc, char **argv);

int ReadConfig( int argc, char **argv);
int WriteConfig( int argc, char **argv);

int ReadState( int argc, char **argv);
int WriteState( int argc, char **argv);

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
    //Set input filename as first arg
	//if NULL use defaults
	char *method=NULL;
	//CIoSimulation *TestSimulation;
	CIoModel *pMod;
	CIoParam *pPar;
	
    if(argc>0)
    {
    	method=argv[1];
    	
    	
    	if(strcmp("initiome",method)==0)
    	{
    		
    		if(argc>5)
				InitIOME(argv[2],argv[3],argv[4],argv[5],atoi(argv[6]));
			else if(argc>4)
				InitIOME(argv[2],argv[3],argv[4],argv[5],8080);
			else if(argc>3)
				InitIOME(argv[2],argv[3],"statefile.xml","configfile.xml",8080);
			else if(argc>2)
				InitIOME(argv[2],"simfile.xml","statefile.xml","configfile.xml",8080);


    	}
		else if(strcmp("setmetadata",method)==0)
    		status=SetMetadata(argc,argv);
    	else if(strcmp("createsimulation",method)==0)
				status=CreateSimulation(argc,argv);
    	else if(strcmp("writesimulation",method)==0)
				status=WriteSimulation(argc,argv);
    	else if(strcmp("readsimulation",method)==0)
				status=ReadSimulation(argc,argv);
    	else if(strcmp("writeconfig",method)==0)
				status=WriteConfig(argc,argv);
    	else if(strcmp("readconfig",method)==0)
				status=ReadConfig(argc,argv);
    	else if(strcmp("writestate",method)==0)
				status=WriteState(argc,argv);
    	else if(strcmp("readstate",method)==0)
					status=ReadState(argc,argv);
    	else if(strcmp("exitiome",method)==0)
					status=ExitIOME(argc,argv);
		else if(strcmp("addmetadata",method)==0)
    		status=AddMetadata(argc,argv);
    	else if(strcmp("getmetadata",method)==0)
    		status=GetMetadata(argc,argv);
    	if(strcmp("addparam",method)==0)
    	{
    		
			if(argc>1)
			{
				 if(strcmp("double",argv[2])==0)
    				itype=0;
				 if(strcmp("int",argv[2])==0)
					itype=1;
				 if(strcmp("vec",argv[2])==0)
					itype=2;				
				 if(strcmp("mat",argv[2])==0)
					itype=3;				
				 if(strcmp("string",argv[2])==0)
					itype=4;				
				 if(strcmp("mmat3d",argv[2])==0)
					itype=5;				

				 if(itype>=0)
					 status=AddParam(itype,argc, argv);
			}
    		
    	}
    	else if(strcmp("getparam",method)==0)
    	{
 				 if(strcmp("double",argv[2])==0)
    				itype=0;
				 if(strcmp("int",argv[2])==0)
					itype=1;
				 if(strcmp("vec",argv[2])==0)
					itype=2;				
				 if(strcmp("mat",argv[2])==0)
					itype=3;				
				 if(strcmp("string",argv[2])==0)
					itype=4;				
				 if(strcmp("mmat3d",argv[2])==0)
					itype=5;				

				 if(itype>=0)
					 status=GetParam(itype,argc, argv);   		
    		
    	}
    	else if(strcmp("setparam",method)==0)
    	{
    						 if(strcmp("double",argv[2])==0)
    				itype=0;
				 if(strcmp("int",argv[2])==0)
					itype=1;
				 if(strcmp("vec",argv[2])==0)
					itype=2;				
				 if(strcmp("mat",argv[2])==0)
					itype=3;				
				 if(strcmp("string",argv[2])==0)
					itype=4;				
				 if(strcmp("mmat3d",argv[2])==0)
					itype=5;				

				 if(itype>=0)
					 status=SetParam(itype,argc, argv);
    		
    	}


    }
    
    	
    	
    	
    
   	#ifdef CWDEBUG
			m1=mem_size();
	#endif	   	
    
		  	#ifdef CWDEBUG
				m7=mem_size();
			#endif	
			
			m_Init.Terminate();
    //Run Simulation
    //std::cout << "m1=" << m1<<" m2=" <<m2 << " m3="<<m3<<" m4=" << m4 <<std::endl;
   //std::cout << "m5=" << m5<<" m6=" <<m6 << " m7="<<m7<<" m8=" << m8 <<std::endl;
    
	return 0;
}

int InitIOME(char *simname, char *simfilename, char *statefilename, char *configfilename, int port)
{
	int status=0;
	pthread_t simtid;
	int m, s; /* master and slave sockets */
    //int port=8080;
	struct soap soap;
	int finish=0;
	sprintf(m_serverclient,"%s:%d","localhost",port);

	if(TestSimulation = (CIoGenericSteerSimulation *)new CIoGenericSteerSimulation)
	{	
		TestSimulation->SetSimName(simname);
		TestSimulation->SetStateFileName(statefilename);
		TestSimulation->SetConfigFileName(configfilename);		
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
		    
		    
		  	m = soap_bind(&soap, NULL, port, 100);
		    if (m < 0)
		    { soap_print_fault(&soap, stderr);
		      exit(-1);
		    }
		while(finish==0)
		{

		    fprintf(stderr, "Socket connection successful: master socket = %d\n", m);
							
		    //pthread_create(&simtid, NULL, (void*(*)(void*))executesimulation, (void*)TestSimulation);

		    //while(m_isimfinished!=1)
		    //{ 
					    	s = soap_accept(&soap);
		    	// copy soap environment and spawn thread
		      	//tsoap = soap_copy(&soap);
		      	//pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)tsoap);
		    	    
		      /*fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);*/
		      if (s < 0)
		      { soap_print_fault(&soap, stderr);
		        exit(-1);
		      } 
		      soap_serve(&soap);
			  soap_end(&soap);

		}
		      //soap_destroy(&soap);
		 //  }
		//}
			//TestSimulation->RunSimulation();
		//delete TestSimulation;
				
	}

	return status;

}


int ExitIOME(int argc, char **argv)
{
	int status=0;
	int id=0;
	int port;
			if(argc>2)
				port=atoi(argv[2]);
			else
				port=8080;

			if(argc>3)
				sprintf(m_serverclient,"%s:%d",argv[3],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

	soap_call_ns_exitiome(&m_soapclient, m_serverclient, "",id, &status);

	return status;
}


int ns__add(struct soap *soap, double a, double b, double *result)
{ *result = a + b;
   printf("hello\n");
  return SOAP_OK;
} 


void *executesimulation(void *simulation)
{ 
	pthread_detach(pthread_self());
	((CIoSimulation *)simulation)->RunSimulation();
	m_isimfinished=1;
  	return NULL;
}



int ns__setsimulationparam(struct soap *soap, int paramid, char *parammap, char *newvalue, char **value)
{
	//if(TestSimulation != NULL)
	//	TestSimulation->ws__setsimulationparam(shost, iport, paramid, parammap, newparam)
	if(TestSimulation != NULL)
	{
		((CIoWFSimulation *)TestSimulation)->setsimulationparam(soap,paramid, parammap, newvalue,value);
	    
		
	}
	
	
	return SOAP_OK;
}

int ns__getsimulationparam(struct soap *soap, int paramid, char *parammap, char **value)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulationparam(soap,paramid, parammap, value);
	
	return SOAP_OK;
}


int ns__setsimulantparam(struct soap *soap, int paramid, char *parammap, int simulantid, char *simmap, char *newvalue, char **value)
{

	CIoParam *pPar;
	//CIoAgentModel *pmod;


	if(TestSimulation != NULL)
	{
		((CIoWFSimulation *)TestSimulation)->setsimulantparam(soap,paramid, parammap, simulantid,simmap,newvalue,value);
		//printf("value set simul param %s %s\n",newvalue, *value);
		//				pPar=(TestSimulation->GetSimulant()->GetProperty(IO_AGENTMODEL_FLOATPROPS_VEC));
	    std::cout<<" set sim parsim created" << *pPar << std::endl;	
	    //pmod=(CIoAgentModel *)(TestSimulation->m_pSimulant);
	    //std::cout<<" before  "<<*(pmod->GetProperty(4))<<std::endl;
	    //pmod->EvaluateScaFieldFuncs();
	    //std::cout<<" after  "<<*(pmod->GetProperty(4))<<std::endl;
	    //pmod->SetAllProps();
	    //pmod->EvaluateScaFieldFuncs();
	    //std::cout<<" after  set all props "<<*(pmod->GetProperty(4))<<std::endl;
	   // std::cout << pmod->m_vars[0] << " " << pmod->m_vars[1] << " " << pmod->m_vars[2] << " " << pmod->m_vars[3] << " " << pmod->m_vars[4] << " "
	    //<< pmod->m_vars[5] << " " << pmod->m_vars[6] << " " << pmod->m_vars[7] << " " << pmod->m_vars[8] << " "
	   // << pmod->m_vars[9] << " " << pmod->m_vars[10] << " "
	   // << std::endl;
	    
	    //pmod->SetAllProps();
		//std::cout<< "all set" << std::endl;
		//	    std::cout << pmod->m_vars[0] << " " << pmod->m_vars[1] << " " << pmod->m_vars[2] << " " << pmod->m_vars[3] << " " << pmod->m_vars[4] << " "
	    //<< pmod->m_vars[5] << " " << pmod->m_vars[6] << " " << pmod->m_vars[7] << " " << pmod->m_vars[8] << " "
	    //<< pmod->m_vars[9] << " " << pmod->m_vars[10] << " "
	    //<< std::endl;
		
	}
		
		

	return SOAP_OK;
}

int ns__getsimulantparam(struct soap *soap, int paramid, char *parammap, int simulantid, char *simmap, char **value)
{
	if(TestSimulation != NULL)
	{
		((CIoWFSimulation *)TestSimulation)->getsimulantparam(soap, paramid, parammap, simulantid,simmap,value);
		
	}

	return SOAP_OK;
}


int ns__getstep(struct soap *soap, int id, int *step)
{
	//if(TestSimulation != NULL)
	//	TestSimulation->ws__setsimulationparam(shost, iport, paramid, parammap, newparam)
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getstep(soap,id, step);

	return SOAP_OK;
}

int ns__setstep(struct soap *soap, int id, int newstep, int *step)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setstep(soap,id,newstep,step);

	return SOAP_OK;
}


int ns__getnsteps(struct soap *soap, int id, int *nsstep)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getnsteps(soap,id,nsstep);

	return SOAP_OK;
}

int ns__setnsteps(struct soap *soap, int id, int newnsteps, int *nsteps)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setnsteps(soap,id,newnsteps,nsteps);

	return SOAP_OK;
}


int ns_getsimulationstate(struct soap *soap, int id, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulationstate(soap,id,istate);

	return SOAP_OK;
}

int ns_setsimulationstate(struct soap *soap, int id, int inewstate, int *istate)
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


int ns_getsimulantstate(struct soap *soap, int id, char *simmap, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulantstate(soap,id,simmap,istate);

	return SOAP_OK;
}

int ns_setsimulantstate(struct soap *soap, int id, char *simmap, int inewstate, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsimulantstate(soap,id,simmap,inewstate,istate);

	return SOAP_OK;
}


int ns_getsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulantinportstate(soap,id,simmap,portid,istate);

	return SOAP_OK;
}

int ns_setsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsimulantinportstate(soap,id,simmap,portid,inewstate,istate);

	return SOAP_OK;
}


int ns_getsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulantoutportstate(soap,id,simmap,portid,istate);

	return SOAP_OK;
}

int ns_setsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsimulantoutportstate(soap,id,simmap,portid,inewstate,istate);

	return SOAP_OK;
}



int ns_setsimulationprocid(struct soap *soap, char  *hostname, int *isimulationprocid)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsimulationprocid(soap,hostname,isimulationprocid);

	return SOAP_OK;
}

int ns_getsimulationhostname(struct soap *soap, int isimulationid, char **shostname)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsimulationhostname(soap,isimulationid,shostname);

	return SOAP_OK;
}

int ns_getfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char **sfile)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getfile(soap,id,localfilename,localpath,remotefilename,remotefilepath,sfile);

	return SOAP_OK;
}

int ns_putfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char *sdata,char **sfile)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->putfile(soap,id,localfilename,localpath,remotefilename,remotefilepath,sdata,sfile);

	return SOAP_OK;
}

int ns_setcheckpoint(struct soap *soap,int id, int inewstate, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setcheckpoint(soap,id,inewstate,istate);

	return SOAP_OK;
}




int ns_getcheckpoint(struct soap *soap,int id, int *istate)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getcheckpoint(soap,id,istate);

	return SOAP_OK;
}



	
int ns_setsteerlog(struct soap *soap,int id, int inewsteerlog, int *isteerlog)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->setsteerlog(soap,id,inewsteerlog,isteerlog);

	return SOAP_OK;
}

int ns_getsteerlog(struct soap *soap,int id, int *isteerlog)
{
	if(TestSimulation != NULL)
		((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);

	return SOAP_OK;
}

//Generic simulation operations only

int ns_createsimulation(struct soap *soap,char *filename, int *status)
{
	if(TestSimulation != NULL)
	{
		if((filename == NULL) || strlen(filename)==0 )
		{
			//create file with the name (make up a filename)
			//write the data filecontent to the file
			//this file will be used to generate the simulation
			*status=TestSimulation->CreateSimulation();
		}
		//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		//filecontent
		//*status=TestSimulation->CreateSimulation(filename);
		*status=TestSimulation->CreateSimulation(filename);
	}

	return SOAP_OK;
}

int ns_writesimulation(struct soap *soap,char *filename, char **filecontent)
{
	int status=0;
	if(TestSimulation != NULL)
	{
		status=TestSimulation->WriteSimulation(filename);
		//write simulation to the string filecontent

	}
	return SOAP_OK;
}


int ns_readsimulation(struct soap *soap,char *filename, int *status)
{
	if(TestSimulation != NULL)
		*status=TestSimulation->ReadSimulation(filename);
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);

	return SOAP_OK;
}


int ns_writestate(struct soap *soap,char *filename, char **filecontent)
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		TestSimulation->WriteState(filename);
		//write the content of the file
		//to the string **filecontent
	}

	return SOAP_OK;
}


int ns_writeconfig(struct soap *soap,char *filename, char **filecontent)
{
	if(TestSimulation != NULL)
		TestSimulation->WriteConfig(filename);
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);

	return SOAP_OK;
}


int ns_exitiome(struct soap *soap,int id, int *status)
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		delete TestSimulation;
		TestSimulation=NULL;
	}
	//m_Init.Terminate();

	return SOAP_OK;
}



int ns_addparamdouble(struct soap *soap,char *name, double value, int iflag, int *status )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		*status=TestSimulation->AddParamDouble(value,sname,iflag);
	}
	return SOAP_OK;
}


int ns_addparamint(struct soap *soap, char *name, int value, int iflag, int *status )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		*status=TestSimulation->AddParamInt(value,sname,iflag);
	}

	return SOAP_OK;
}


int ns_addparamvec(struct soap *soap, char *name, struct fdata value, int n, int iflag, int *status )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		for(int i=0; i<n; i++)
			printf("val %d %f\n",i, value.__ptr[i]);
		*status=TestSimulation->AddParamVec(value.__ptr,n,sname,iflag);
	}

	return SOAP_OK;
}


int ns_addparammat(struct soap *soap, char *name, struct fdata value, int nr, int nc,  int iflag, int *status )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		*status=TestSimulation->AddParamMat(value.__ptr,nr,nc,sname,iflag);
	}
	return SOAP_OK;
}


int ns_addparamstring(struct soap *soap, char *name, char *value, int iflag, int *status )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		string svalue=value;
		*status=TestSimulation->AddParamString(svalue,sname,iflag);
	}
	return SOAP_OK;
}


int ns_addparammmat3d(struct soap *soap, char *name, struct fdata value, int n, int p, int q, int nr, int nc,int iflag, int *status )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		
		*status=TestSimulation->AddParammmat3d(value.__ptr,n,p,q,nr,nc,sname,iflag);
	}
	return SOAP_OK;
}



int ns_addmetadata(struct soap *soap,char *name, char *property, int *status)
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		string scontent=property;
		
		TestSimulation->AddMetadata(sname,scontent);
	}
	return SOAP_OK;
}



int ns_getparamdouble(struct soap *soap,char *name, double *value )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		TestSimulation->GetParamDouble(value,sname);
	}
	return SOAP_OK;
}


int ns_getparamint(struct soap *soap, char *name, int *value )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		TestSimulation->GetParamInt(value,sname);
	}
	return SOAP_OK;
}


int ns_getparamvec(struct soap *soap, char *name, int n, struct fdata **value )
{
	double *fval=(double *)calloc(n,sizeof(double));
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
        
		string sname=name;
		TestSimulation->GetParamVec(fval,n,sname);
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
	return SOAP_OK;
}


int ns_getparammat(struct soap *soap, char *name, int nr, int nc, struct fdata **value )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		double *fval=(double *)calloc(nr*nc,sizeof(double));
		//value=(struct fdata *)malloc(sizeof(struct fdata));
		//value->__ptr=(double *)calloc(nr*nc,sizeof(double));
		//double *fval=(double *)soap_malloc(soap,nr*nc*sizeof(double));
		(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
		(*value)->__ptr=(double *)soap_malloc(soap,nr*nc*sizeof(double));

		string sname=name;
		TestSimulation->GetParamMat(fval,nr,nc,sname);
		(*value)->__size=nr*nc;
		for(int i=0; i<nr*nc; i++)
		{
			(*value)->__ptr[i]=fval[i];
			//printf("%d %f \n",i,fval[i]);
		}

		//free(fval);

	}
	return SOAP_OK;
}


int ns_getparamstring(struct soap *soap, char *name, char **value )
{
	if(TestSimulation != NULL)
	{
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		string svalue;
		TestSimulation->GetParamString(&svalue,sname);
		//*value=(char *)calloc(1+strlen(sname.c_str()),sizeof(char));
		*value=(char *)soap_malloc(soap,(1+strlen(sname.c_str()))*sizeof(char));

		strcpy(*value,svalue.c_str());
	}
	return SOAP_OK;
}


int ns_getparammmat3d(struct soap *soap, char *name, int n, int p, int q, int nr, int nc, struct fdata **value  )
{
	if(TestSimulation != NULL)
	{
		double *fval=(double *)calloc(n*p*q*nr*nc,sizeof(double));
		(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
		(*value)->__ptr=(double *)soap_malloc(soap,n*p*q*nr*nc*sizeof(double));


		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);
		string sname=name;
		//TestSimulation->GetParammmat3d(*mmat3d,n,p,q,nr,nc,sname);
		TestSimulation->GetParammmat3d(fval,n,p,q,nr,nc,sname);

		(*value)->__size=n*p*q*nr*nc;
		for(int i=0; i<n*p*q*nr*nc; i++)
		{
			(*value)->__ptr[i]=fval[i];
			//printf("%d %f \n",i,fval[i]);
		}
	}
	return SOAP_OK;
}



int ns_getmetadata(struct soap *soap, int id, char *name, char **property)
{
	if(TestSimulation != NULL)
	{
		string sval;
		sval=TestSimulation->GetMetadata(name);
		//*property=(char *)calloc(1+strlen(sval.c_str()),sizeof(char));
		*property=(char *)soap_malloc(soap,(1+strlen(sval.c_str()))*sizeof(char));
		strcpy(*property,(const char *)(sval.c_str()));
	}
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);

	return SOAP_OK;
}


int ns_setparamdouble(struct soap *soap, char *name, double value, int *status )
{
	if(TestSimulation != NULL)
	{
		string sname=name;
		*status=TestSimulation->SetParamDouble(value,sname);
		//strcpy(*property,(const char *)(sval.c_str()));
	}
		//;//((CIoWFSimulation *)TestSimulation)->getsteerlog(soap,id,isteerlog);

	return SOAP_OK;
}


int ns_setparamint(struct soap *soap, char *name, int value, int *status  )
{
	if(TestSimulation != NULL)
	{
		string sname=name;
		*status=TestSimulation->SetParamInt(value,sname);
	}
	return SOAP_OK;
}


int ns_setparamvec(struct soap *soap, char *name, struct fdata value, int n, int *status  )
{
	if(TestSimulation != NULL)
	{
		string sname=name;
		*status=TestSimulation->SetParamVec(value.__ptr,n,sname,7);
	}
	return SOAP_OK;
}


int ns_setparammat(struct soap *soap, char *name, struct fdata value, int nr, int nc, int *status  )
{
	if(TestSimulation != NULL)
	{
		string sname=name;
		*status=TestSimulation->SetParamMat(value.__ptr,nr,nc,sname);
	}
	return SOAP_OK;
}


int ns_setparamstring(struct soap *soap, char *name, char *value, int *status  )
{
	if(TestSimulation != NULL)
	{
		string sname=name;
		string svalue=value;
		*status=TestSimulation->SetParamString(svalue,sname);
	}
	return SOAP_OK;
}


int ns_setparammmat3d(struct soap *soap, char *name, struct fdata value,  int n, int p, int q, int nr, int nc, int *status  )
{
	if(TestSimulation != NULL)
	{
		string sname=name;
		*status=TestSimulation->SetParammmat3d(value.__ptr,n,p,q,nr,nc,sname);
	}
	return SOAP_OK;
}



int ns_setmetadata(struct soap *soap,int id, char *name, char *property, int *status)
{
	if(TestSimulation != NULL)
	{
		string sname=name;
		string sproperty=property;
		TestSimulation->SetMetadata(sname,sproperty);
	}
	return SOAP_OK;
}


//client calls
int AddParam(int itype, int argc, char **argv)
{
	int status=0;
	int isize;
	double *darray;
	int port;
	char *name;
	int iflag;
	name=argv[3];

	switch(itype)
	{

	case 0:

		if(argc>=4)
		{
			double dvalue=(double)atof(argv[4]);
			iflag=atoi(argv[5]);
			if(argc>6)
				port=atoi(argv[6]);
			else
				port=8080;

			if(argc>6)
				sprintf(m_serverclient,"%s:%d",argv[7],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns_addparamdouble(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
		}
		else
			status=1;
		
		break;
	case 1:
		int dint;
		//soap_call_ns_addparamint(&m_soapclient, m_serverclient, "", name, (int *)data );
		if(argc>=4)
		{
			int dvalue=atoi(argv[4]);
			iflag=atoi(argv[5]);
			if(argc>6)
				port=atoi(argv[6]);
			else
				port=8080;

			if(argc>7)
				sprintf(m_serverclient,"%s:%d",argv[7],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns_addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
		}
		else
			status=1;		

		break;
	case 2:
		isize=1;
		darray=(double *)calloc(isize,sizeof(double));
		//soap_call_ns_addparamvec(&m_soapclient, m_serverclient, "", name, size,(double **)data );
		if(argc>=5)
		{
			
			int size=atoi(argv[5]);
			int iflag=atoi(argv[6]);
			float fv;
			int ind=0;

			//the array of floats is string consisting of a comma separated list
			//with no white space
			char *pch;
			pch = strtok (argv[4],",");
			double *data=(double *)calloc(size,sizeof(double));
			do
			{
				//printf ("%s\n",pch);
				//;
				fv=atof(pch);
				data[ind]=fv;
				if(ind<size)
					ind++;
				
			}
			while ((pch = strtok (NULL, ",")) != NULL);
			//double fd=(double)atof(argv[4]);
			


			//double *data=&fd;

			if(argc>7)
				port=atoi(argv[7]);
			else
				port=8080;

			if(argc>8)
				sprintf(m_serverclient,"%s:%d",argv[8],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			//soap_call_ns_addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			struct fdata thedata;
			thedata.__ptr=data;
			thedata.__size=size;
			soap_call_ns_addparamvec(&m_soapclient, m_serverclient, "", name, thedata,size,iflag,&status );
		}
		else
			status=1;
		free(darray);

		break;
	case 3:
		isize=1;
	if(argc>=4)
		{
			
			int nr=atoi(argv[5]);
			int nc=atoi(argv[6]);

			int iflag=atoi(argv[7]);
			int size=nr*nc;
			float fv;
			int ind=0;

			//the array of floats is string consisting of a comma separated list
			//with no white space
			char *pch;
			pch = strtok (argv[4],",");
			double *data=(double *)calloc(size,sizeof(double));
			do
			{
				//printf ("%s\n",pch);
				//;
				fv=atof(pch);
				data[ind]=fv;
				if(ind<size)
					ind++;
				
			}
			while ((pch = strtok (NULL, ",")) != NULL);
			//double fd=(double)atof(argv[4]);
			


			//double *data=&fd;

			if(argc>8)
				port=atoi(argv[8]);
			else
				port=8080;

			if(argc>9)
				sprintf(m_serverclient,"%s:%d",argv[9],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			struct fdata thedata;
			thedata.__ptr=data;
			thedata.__size=nr*nc;

			//soap_call_ns_addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, thedata,nr,nc,iflag,&status );
		}
		else
			status=1;

		//	soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, data,nr,nc,iflag,(int *)status );		
		//soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );			
		//free(darray);

		break;
	case 4:
			if(argc>=4)
		{
			char*dvalue=(char *)(argv[4]);
			iflag=atoi(argv[5]);
			if(argc>6)
				port=atoi(argv[6]);
			else
				port=8080;

			if(argc>7)
				sprintf(m_serverclient,"%s:%d",argv[7],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns_addparamstring(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
		}
		else
			status=1;

		break;
	case 5:
		if(argc>=4)
		{
			
			int n=atoi(argv[5]);
			int p=atoi(argv[6]);
			int q=atoi(argv[7]);
			
			int nr=atoi(argv[8]);
			int nc=atoi(argv[9]);

			int iflag=atoi(argv[10]);
			int size=nr*nc*n*p*q;
			float fv;
			int ind=0;

			//the array of floats is string consisting of a comma separated list
			//with no white space
			char *pch;
			pch = strtok (argv[4],",");
			double *data=(double *)calloc(size,sizeof(double));
			do
			{
				//printf ("%s\n",pch);
				//pch = strtok (NULL, ",");
				fv=atof(pch);
				data[ind]=fv;
				if(ind<size)
					ind++;
				
			}
			while ((pch = strtok (NULL, ",")) != NULL);

			//double fd=(double)atof(argv[4]);
			


			//double *data=&fd;

			if(argc>11)
				port=atoi(argv[11]);
			else
				port=8080;

			if(argc>12)
				sprintf(m_serverclient,"%s:%d",argv[12],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			struct fdata thedata;
			thedata.__ptr=data;
			thedata.__size=n*p*q*nr*nc;


			//soap_call_ns_addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns_addparammmat3d(&m_soapclient, m_serverclient, "", name, thedata,n,p,q,nr,nc,iflag,&status );
		}
		else
			status=1;

		//	soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, data,nr,nc,iflag,(int *)status );		
		//soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );			
		//free(darray);


		//soap_call_ns_addparammmat3d(&m_soapclient, m_serverclient, "", name,size, &dmmat3d );
		//free(darray);

		break;

	}


	return status;
}


int AddMetadata( int argc, char **argv)
{
	int status=0;
	int port=atoi(argv[3]);
	char *content;
	char *name;

	if(argc>2)
	{
			content=argv[3];
			name=argv[2];
			sprintf(m_serverclient,"%s:%d","localhost",port);
			if(argc>4)
				port=atoi(argv[4]);
			else
				port=8080;

			if(argc>5)
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

			soap_call_ns_addmetadata(&m_soapclient, m_serverclient, "", name, content, &status);
	}

	return status;
}


int GetParam( int itype, int argc, char **argv)
{
	int status=0;
	int isize;
	double *darray;
	int port;
	char *name;
	name=argv[3];
char *dvalue=(char *)calloc(500,sizeof(char));
strcpy(dvalue,"junkjunkjunk");
	switch(itype)
	{
	case 0:
		{
			double dvalue=0;
			if(argc>4)
				port=atoi(argv[4]);
			else
				port=8080;

			if(argc>5)
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			soap_call_ns_getparamdouble(&m_soapclient, m_serverclient, "", name, &dvalue );
			//print the value
			printf("%f",dvalue);
		}
		break;
	case 1:
		{
		//int dint;
			int dvalue=0;
			if(argc>4)
				port=atoi(argv[4]);
			else
				port=8080;

			if(argc>5)
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			soap_call_ns_getparamint(&m_soapclient, m_serverclient, "", name, &dvalue );
			//print the value
			printf("%d",dvalue);
		}

		break;
	case 2:
		{
		isize=1;
		//soap_call_ns_addparamvec(&m_soapclient, m_serverclient, "", name, size,(double **)data );
					int dvalue=0;

			if(argc>3)
			{
				isize=atoi(argv[4]);
				darray=(double *)calloc(isize,sizeof(double));

				if(argc>5)
						port=atoi(argv[5]);
					else
						port=8080;

					if(argc>6)
						sprintf(m_serverclient,"%s:%d",argv[6],port);
					else
						sprintf(m_serverclient,"%s:%d","localhost",port);
					struct fdata *fval;
					fval=(struct fdata *)malloc(sizeof(struct fdata));
					(*fval).__ptr=(double *)malloc(isize*sizeof(double));
					//fval.__size=isize;
					soap_call_ns_getparamvec(&m_soapclient, m_serverclient, "", name,isize, &fval );
					//print the value
					for(int i=0; i<isize;i++)
							printf("%f ",fval->__ptr[i]);
					printf("\n");
				free(darray);
			}
		}

		break;
	case 3:
		{
		isize=1;
		double *darray=(double *)calloc(isize,sizeof(double));
			if(argc>3)
			{
				int nr=atoi(argv[4]);
				int nc=atoi(argv[5]);
				isize=nr*nc;
				darray=(double *)calloc(isize,sizeof(double));

				if(argc>6)
						port=atoi(argv[6]);
					else
						port=8080;

					if(argc>7)
						sprintf(m_serverclient,"%s:%d",argv[7],port);
					else
						sprintf(m_serverclient,"%s:%d","localhost",port);
					

					struct fdata *fval;
					fval=(struct fdata *)malloc(sizeof(struct fdata));
					(*fval).__ptr=(double *)malloc(isize*sizeof(double));

					//soap_call_ns_getparamvec(&m_soapclient, m_serverclient, "", name,isize, &darray );
					soap_call_ns_getparammat(&m_soapclient, m_serverclient, "", name, nr,nc,&fval );
					//print the value
					int i,j;
					int itot=0;
					for(i=0; i<nr;i++)
					{
						for(j=0; j<nc;j++)
						{
							printf("%f ",fval->__ptr[itot]);
							if(itot>isize)
								break;
							else
								itot++;
						}
						
					}
					printf("\n");
				free(darray);
			}
		
		//soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );
			
		//free(darray);
		}

		break;
	case 4:
		isize=1;
		//darray=(double *)calloc(isize,sizeof(double));

		//soap_call_ns_addparamstring(&m_soapclient, m_serverclient, "", name,(char **)data );
		//free(darray);
				{
		//int dint;
			//char *dvalue;
			
			//char dvalue[500];
			//char **strptr=&dvalue;
			if(argc>4)
				port=atoi(argv[4]);
			else
				port=8080;

			if(argc>5)
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			soap_call_ns_getparamstring(&m_soapclient, m_serverclient, "", name, &dvalue );
			//print the value
			printf("%s",dvalue);
		}
		break;
	case 5:
		{
		isize=1;
		double *darray=(double *)calloc(isize,sizeof(double));
			if(argc>7)
			{
				int nr=atoi(argv[4]);
				int nc=atoi(argv[5]);
				int n=atoi(argv[6]);
				int p=atoi(argv[7]);
				int q=atoi(argv[8]);
				isize=n*p*q*nr*nc;
				darray=(double *)calloc(isize,sizeof(double));

				if(argc>9)
						port=atoi(argv[9]);
					else
						port=8080;

					if(argc>10)
						sprintf(m_serverclient,"%s:%d",argv[10],port);
					else
						sprintf(m_serverclient,"%s:%d","localhost",port);
							//soap_call_ns_addparammmat3d(&m_soapclient, m_serverclient, "", name,size, &dmmat3d );
					struct fdata *fval;
					fval=(struct fdata *)malloc(sizeof(struct fdata));
					(*fval).__ptr=(double *)malloc(n*p*q*nr*nc*sizeof(double));

					//soap_call_ns_getparamvec(&m_soapclient, m_serverclient, "", name,isize, &darray );
					soap_call_ns_getparammmat3d(&m_soapclient, m_serverclient, "", name, n,p,q,nr,nc,&fval );
					//print the value
					int i1,i2,i3;
					int i,j;
					int itot=0;
					for(i1=0; i1<n;i1++)
					{
						for(i2=0; i2<p;i2++)
						{
							for(i3=0; i3<q;i3++)
							{
								for(i=0; i<nr;i++)
								{
									for(j=0; j<nc;j++)
									{
										//printf("%d ",darray[itot]);
										printf("%d ",fval->__ptr[itot]);
										if(itot>isize)
											break;
										else
											itot++;
									}
									
								}
					printf("\n");
					}
					}
					}
				free(darray);
			}
		
		//soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );
			
		//free(darray);
		}






		break;

	}


	return status;
}


int GetMetadata( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char content[400];
	char *scont;
	char *name;
	int id=0;
    scont=content;
	if(argc>1)
	{
			//content=argv[3];
			name=argv[2];
			//sprintf(m_serverclient,"%s:%d","localhost",port);
			if(argc>3)
				port=atoi(argv[3]);
			else
				port=8080;

			if(argc>4)
				sprintf(m_serverclient,"%s:%d",argv[4],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

			soap_call_ns_getmetadata(&m_soapclient, m_serverclient, "", id, name, &scont);
			printf("%s",scont);
	}

	return status;
}


int SetParam(int itype, int argc, char **argv)
{
	int status=0;
	int isize;
	double *darray;
	int port;
	char *name;
	name=argv[3];

	switch(itype)
	{

	case 0:

		if(argc>4)
		{
			double dvalue=atof(argv[4]);
			if(argc>5)
				port=atoi(argv[5]);
			else
				port=8080;

			if(argc>6)
				sprintf(m_serverclient,"%s:%d",argv[6],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns_setparamdouble(&m_soapclient, m_serverclient, "", name, dvalue, &status );
		}
		else
			status=1;
		
		break;
	case 1:
		int dint;
		//soap_call_ns_addparamint(&m_soapclient, m_serverclient, "", name, (int *)data );
		if(argc>4)
		{
			int dvalue=atoi(argv[4]);
			if(argc>5)
				port=atoi(argv[5]);
			else
				port=8080;

			if(argc>6)
				sprintf(m_serverclient,"%s:%d",argv[6],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns_setparamint(&m_soapclient, m_serverclient, "", name, dvalue, &status );
		}
		else
			status=1;		

		break;
	case 2:
		isize=1;
		darray=(double *)calloc(isize,sizeof(double));
		//soap_call_ns_addparamvec(&m_soapclient, m_serverclient, "", name, size,(double **)data );
		if(argc>=4)
		{
			
			int size=atoi(argv[5]);
			//int iflag=atoi(argv[6]);
			float fv;
			int ind=0;

			//the array of floats is string consisting of a comma separated list
			//with no white space
			char *pch;
			pch = strtok (argv[4],",");
			double *data=(double *)calloc(size,sizeof(double));
			do
			{
				//printf ("%s\n",pch);
				//;
				fv=atof(pch);
				data[ind]=fv;
				if(ind<size)
					ind++;
				
			}
			while ((pch = strtok (NULL, ",")) != NULL);
			//double fd=(double)atof(argv[4]);
			


			//double *data=&fd;

			if(argc>6)
				port=atoi(argv[6]);
			else
				port=8080;

			if(argc>7)
				sprintf(m_serverclient,"%s:%d",argv[7],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			struct fdata sdata;
			sdata.__ptr=data;
			sdata.__size=size;
			//soap_call_ns_addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns_setparamvec(&m_soapclient, m_serverclient, "", name, sdata,size,&status );
		}
		else
			status=1;
		free(darray);

		break;
	case 3:
		isize=1;
	if(argc>4)
		{
			
			int nr=atoi(argv[5]);
			int nc=atoi(argv[6]);

			//int iflag=atoi(argv[7]);
			int size=nr*nc;
			float fv;
			int ind=0;

			//the array of floats is string consisting of a comma separated list
			//with no white space
			char *pch;
			pch = strtok (argv[4],",");
			double *data=(double *)calloc(size,sizeof(double));
			do
			{
				//printf ("%s\n",pch);
				
				fv=atof(pch);
				data[ind]=fv;
				if(ind<size)
					ind++;
				
			}
			while ((pch = strtok (NULL, ",")) != NULL);
			//double fd=(double)atof(argv[4]);
			


			//double *data=&fd;

			if(argc>7)
				port=atoi(argv[7]);
			else
				port=8080;

			if(argc>8)
				sprintf(m_serverclient,"%s:%d",argv[8],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			struct fdata sdata;
			sdata.__ptr=data;
			sdata.__size=nr*nc;

			//soap_call_ns_addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns_setparammat(&m_soapclient, m_serverclient, "", name, sdata,nr,nc,&status );
		}
		else
			status=1;

		//	soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, data,nr,nc,iflag,(int *)status );		
		//soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );			
		//free(darray);

		break;
	case 4:
			if(argc>4)
		{
			char*dvalue=(char *)(argv[4]);
			if(argc>5)
				port=atoi(argv[5]);
			else
				port=8080;

			if(argc>6)
				sprintf(m_serverclient,"%s:%d",argv[6],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns_setparamstring(&m_soapclient, m_serverclient, "", name, dvalue, &status );
		}
		else
			status=1;

		break;
	case 5:
		if(argc>=4)
		{
			
			int n=atoi(argv[5]);
			int p=atoi(argv[6]);
			int q=atoi(argv[7]);
			
			int nr=atoi(argv[8]);
			int nc=atoi(argv[9]);

			//int iflag=atoi(argv[10]);
			int size=nr*nc*n*p*q;
			float fv;
			int ind=0;

			//the array of floats is string consisting of a comma separated list
			//with no white space
			char *pch;
			pch = strtok (argv[4],",");
			double *data=(double *)calloc(size,sizeof(double));
			do
			{
				//printf ("%s\n",pch);
				//;
				fv=atof(pch);
				data[ind]=fv;
				if(ind<size)
					ind++;
				
			}
			while ((pch = strtok (NULL, ",")) != NULL);
			//double fd=(double)atof(argv[4]);
			


			//double *data=&fd;

			if(argc>10)
				port=atoi(argv[10]);
			else
				port=8080;

			if(argc>11)
				sprintf(m_serverclient,"%s:%d",argv[11],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			struct fdata sdata;
			sdata.__ptr=data;
			sdata.__size=n*p*q*nr*nc;

			//soap_call_ns_addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns_setparammmat3d(&m_soapclient, m_serverclient, "", name, sdata,n,p,q,nr,nc,&status );
		}
		else
			status=1;

		//	soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, data,nr,nc,iflag,(int *)status );		
		//soap_call_ns_addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );			
		//free(darray);


		//soap_call_ns_addparammmat3d(&m_soapclient, m_serverclient, "", name,size, &dmmat3d );
		//free(darray);

		break;
	}


	return status;
}

int SetMetadata( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *content;
	char *name;
	int id=0;

	if(argc>2)
	{
			content=argv[3];
			name=argv[2];
			sprintf(m_serverclient,"%s:%d","localhost",port);
			if(argc>4)
				port=atoi(argv[4]);
			else
				port=8080;

			if(argc>5)
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

			soap_call_ns_setmetadata(&m_soapclient, m_serverclient, "", id, name, content, &status);
			printf("%s",content);
	}

	return status;

}

int CreateSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername="";
	char *filename="";
	char *content="";
	char *sservername="";

	if(argc>1 && (argv[2]!=NULL))
					filename=argv[2];
	else 
		filename="";

	if(argc>2 && (argv[3]!=NULL))
					content=argv[3];
	else 
		content="";

	if(argc>3 && (argv[4]!=NULL))
	{
		sservername=argv[4];
		if(argc>4 && (argv[5]!=NULL))
           port=atoi(argv[5]);
	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns_createsimulation(&m_soapclient, m_serverclient, "", filename, &status);

	//call create simulation

	return status;
}

int ReadSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername=argv[5];
	char *filename=argv[3];
	char *content=argv[4];
	char *sservername=NULL;
	char *scontent;
	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>3 && (argv[4]!=NULL))
	{
		sservername=argv[4];
		if(argc>4 && (argv[5]!=NULL))
           port=atoi(argv[5]);
	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns_readsimulation(&m_soapclient, m_serverclient, "", filename, &status);

	//call create simulation

	return status;
}

int WriteSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername=argv[5];
	char *filename=argv[2];
	char *sservername=NULL;
	char *scontent;

	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>2 && (argv[3]!=NULL))
	{
		sservername=argv[3];
		if(argc>3 && (argv[4]!=NULL))
           port=atoi(argv[4]);
	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns_writesimulation(&m_soapclient, m_serverclient, "",  filename, &scontent);

	//if strlen(scontent)>0 
	//write content to file

	//call create simulation

	return status;
}

int ReadState( int argc, char **argv)
{
	int status=0;
	int port=atoi(argv[3]);
    sprintf(m_serverclient,"%s:%d","localhost",port);

	return status;
}

int WriteState( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername=argv[5];
	char *filename=argv[3];
	char *sservername=NULL;
	char *scontent;

	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>3 && (argv[4]!=NULL))
	{
		sservername=argv[4];
		if(argc>4 && (argv[5]!=NULL))
           port=atoi(argv[5]);
	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns_writestate(&m_soapclient, m_serverclient, "",  filename, &scontent);

	//if strlen(scontent)>0 
	//write content to file

	//call create simulation

	return status;
}

int ReadConfig( int argc, char **argv)
{
	int status=0;
	int port=atoi(argv[3]);
    sprintf(m_serverclient,"%s:%d","localhost",port);

	return status;
}

int WriteConfig( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername=argv[5];
	char *filename=argv[3];
	char *sservername=NULL;
	char *scontent;

	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>3 && (argv[4]!=NULL))
	{
		sservername=argv[4];
		if(argc>4 && (argv[5]!=NULL))
           port=atoi(argv[5]);
	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns_writeconfig(&m_soapclient, m_serverclient, "",  filename, &scontent);

	//if strlen(scontent)>0 
	//write content to file

	//call create simulation

	return status;
}












