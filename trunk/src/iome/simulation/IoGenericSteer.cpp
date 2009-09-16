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


#include <iome/simulation/IoGenericSteer.h>

void *executeserver(void *msoap)
{ 
	int s;
	pthread_detach(pthread_self());
	struct soap *tsoap = soap_copy((soap *)msoap);
	//((soap *)msoap)->RunSimulation();
	
	for ( ; ; )
    { 
      if (s < 0)
      { soap_print_fault(tsoap, stderr);
        exit(-1);
      } 
      soap_serve(tsoap);
      //soap_destroy(&soap);
      soap_end(tsoap);
   }
	
	
  	return NULL;
}


int InitIOME(char *simname, char *statefilename, char *configfilename)
{
	int status=0;
    m_Init.Initialise();
    
    m_steer=new CIoGenericSteerSimulation();
    m_steer->SetStateFileName(statefilename);
	m_steer->SetConfigFileName(configfilename);
	m_steer->SetSimName(simname);		
    
	return status;
}


int CreateSimulation()
{
	int status=0;

	if(m_steer)
	{
		m_steer->CreateDefaultParams();
		m_steer->CreatePropNames();
		m_steer->CreatePropFlags();	
	}

	return status;	
}

int ExitIOME()
{
	int status=0;

    if(m_steer)
    	delete m_steer;
    m_steer=NULL;
    pthread_cancel(m_servertid);
	return status;
}

int StartServer(int port)
{
	int status=0;
	struct soap m_soap;

    soap_init(&m_soap);
		    
  	int m = soap_bind(&m_soap, NULL, port, 100);
    if (m < 0)
    { soap_print_fault(&m_soap, stderr);
      exit(-1);
    }
    fprintf(stderr, "Socket connection successful: master socket = %d\n", m);


	
	pthread_create(&m_servertid, NULL, (void*(*)(void*))executeserver, (void*)(&m_soap));



	return status;
}

int ConfigureParams()
{
	int status=0;


	return status;
}

int CreateDefaultParams()
{
	int status=0;


	return status;
}

int GetParamDouble(double *value, string sparamname)
{
	int status=0;
    if(m_steer)
    	status=m_steer->GetParamDouble(value, sparamname);
	return status;
}

int SetParamDouble(double value, string sparamname, int iflag)
{
	int status=0;
    if(m_steer)
    	status=m_steer->SetParamDouble(value, sparamname,iflag);
	return status;
}


int GetParamVec(double *value, int n, string sparamname)
{
	int status=0;
    if(m_steer)
    	status=m_steer->GetParamVec(value, n, sparamname);
	return status;

}

int SetParamVec(double *value, int n, string sparamname, int iflag)
{
	int status=0;
    if(m_steer)
    	status=m_steer->SetParamVec(value, n, sparamname,iflag);
	return status;
}

int GetParamMat(double *value, int nr, int nc, string sparamname)
{
	int status=0;
    if(m_steer)
    	status=m_steer->GetParamMat(value, nr, nc,sparamname);
	return status;

}

int SetParamMat(double *value, int nr, int nc, string sparamname, int iflag)
{
	int status=0;
    if(m_steer)
    	status=m_steer->SetParamMat(value, nr, nc, sparamname,iflag);
	return status;
}



int GetParammmat3d(double *value, int n, int p, int q, int nr, int nc, string sparamname)
{
	int status=0;
    if(m_steer)
    	status=m_steer->GetParammmat3d(value, n, p,q,nr,nc, sparamname);
	return status;
}

int SetParammmat3d(double *value, int n, int p, int q, int nr, int nc, string sparamname, int iflag)
{
	int status=0;
    if(m_steer)
    	status=m_steer->SetParammmat3d(value, n, p,q,nr,nc, sparamname,iflag);
	return status;
}

int UpdateParams()
{
	int status=0;


	return status;
}

int AddParamDouble(double value, string sparamname, int iflag)
{
	int status=0;
    if(m_steer)
    	m_steer->AddParamDouble(value, sparamname, iflag);

	return status;
}

int AddParamInt(int value, string sparamname, int iflag)
{
	int status=0;
    if(m_steer)
    	m_steer->AddParamInt(value, sparamname, iflag);

	return status;
}


int AddParamVec(double *value, int n, string sparamname,int iflag)
{
	int status=0;
    if(m_steer)
    	m_steer->AddParamVec(value,n, sparamname, iflag);

	return status;

}


int AddParamMat(double *value, int nr, int nc, string sparamname,int iflag)
{
	int status=0;
    if(m_steer)
    	m_steer->AddParamMat(value,nr,nc, sparamname, iflag);

	return status;
}



int AddParammmat3d(double *value, int n, int p, int q, int nr, int nc, string sparamname, int iflag)
{
	int status=0;
    if(m_steer)
    	m_steer->AddParammmat3d(value,n,p,q,nr,nc, sparamname, iflag);

	return status;
}


int ReadSimulation(char *sSimFilename)
{
	int status=0;
    if(m_steer)
      m_steer->ReadSimulation(sSimFilename);

	return status;		
}


int ReadConfig(char *sConfigFilename)
{
	int status=0;
    if(m_steer)
      m_steer->ReadConfig(sConfigFilename);

	return status;			
}


int WriteSimulation(char *sSimFilename, char *sXSLFilename)
{
	int status=0;
    if(m_steer)
      m_steer->WriteSimulation(sSimFilename,sXSLFilename);

	return status;
}


int WriteState(char *sStateFilename, int format, char *sXSLFilename)
{
	int status=0;
    if(m_steer)
      m_steer->WriteState(sStateFilename,format,sXSLFilename);


	return status;
}



int WriteConfig(char *sConfigFilename, int format, char *sXSLFilename)
{
	int status=0;
    if(m_steer)
      m_steer->WriteConfig(sConfigFilename,format,sXSLFilename);


	return status;
}



int ns__setsimulationparam(struct soap *soap, int paramid, char *parammap, char *newvalue, char **value)
{
	//if(m_steer != NULL)
	//	m_steer->ws__setsimulationparam(shost, iport, paramid, parammap, newparam)
	if(m_steer != NULL)
	{
		((CIoWFSimulation *)m_steer)->setsimulationparam(soap,paramid, parammap, newvalue,value);
	    
		
	}
	
	
	return SOAP_OK;
}

int ns__getsimulationparam(struct soap *soap, int paramid, char *parammap, char **value)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getsimulationparam(soap,paramid, parammap, value);
	
	return SOAP_OK;
}


int ns__setsimulantparam(struct soap *soap, int paramid, char *parammap, int simulantid, char *simmap, char *newvalue, char **value)
{


		
		

	return SOAP_OK;
}

int ns__getsimulantparam(struct soap *soap, int paramid, char *parammap, int simulantid, char *simmap, char **value)
{

	return SOAP_OK;
}


int ns__getstep(struct soap *soap, int id, int *step)
{
	//if(m_steer != NULL)
	//	m_steer->ws__setsimulationparam(shost, iport, paramid, parammap, newparam)
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getstep(soap,id, step);

	return SOAP_OK;
}

int ns__setstep(struct soap *soap, int id, int newstep, int *step)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->setstep(soap,id,newstep,step);

	return SOAP_OK;
}


int ns__getnsteps(struct soap *soap, int id, int *nsstep)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getnsteps(soap,id,nsstep);

	return SOAP_OK;
}

int ns__setnsteps(struct soap *soap, int id, int newnsteps, int *nsteps)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->setnsteps(soap,id,newnsteps,nsteps);

	return SOAP_OK;
}


int ns_getsimulationstate(struct soap *soap, int id, int *istate)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getsimulationstate(soap,id,istate);

	return SOAP_OK;
}

int ns_setsimulationstate(struct soap *soap, int id, int inewstate, int *istate)
{

	//CIoParam *pPar;
	//CIoAgentModel *pmod;


	if(m_steer != NULL)
	{
		((CIoWFSimulation *)m_steer)->setsimulationstate(soap,id,inewstate,istate);
		
//								pPar=(m_steer->GetSimulant()->GetProperty(IO_AGENTMODEL_FLOATPROPS_VEC));
//	    std::cout<<" set sim parsim created" << *pPar << std::endl;	
//	    pmod=(CIoAgentModel *)(m_steer->m_pSimulant);
//	    std::cout<<" before  "<<*(pmod->GetProperty(4))<<std::endl;
//	    pmod->EvaluateScaFieldFuncs();
//	    std::cout<<" after  "<<*(pmod->GetProperty(4))<<std::endl;
	}

	return SOAP_OK;
}


int ns_getsimulantstate(struct soap *soap, int id, char *simmap, int *istate)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getsimulantstate(soap,id,simmap,istate);

	return SOAP_OK;
}

int ns_setsimulantstate(struct soap *soap, int id, char *simmap, int inewstate, int *istate)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->setsimulantstate(soap,id,simmap,inewstate,istate);

	return SOAP_OK;
}


int ns_getsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getsimulantinportstate(soap,id,simmap,portid,istate);

	return SOAP_OK;
}

int ns_setsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->setsimulantinportstate(soap,id,simmap,portid,inewstate,istate);

	return SOAP_OK;
}


int ns_getsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getsimulantoutportstate(soap,id,simmap,portid,istate);

	return SOAP_OK;
}

int ns_setsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->setsimulantoutportstate(soap,id,simmap,portid,inewstate,istate);

	return SOAP_OK;
}



int ns_setsimulationprocid(struct soap *soap, char  *hostname, int *isimulationprocid)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->setsimulationprocid(soap,hostname,isimulationprocid);

	return SOAP_OK;
}

int ns_getsimulationhostname(struct soap *soap, int isimulationid, char **shostname)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getsimulationhostname(soap,isimulationid,shostname);

	return SOAP_OK;
}

int ns_getfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char **sfile)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getfile(soap,id,localfilename,localpath,remotefilename,remotefilepath,sfile);

	return SOAP_OK;
}

int ns_putfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char *sdata,char **sfile)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->putfile(soap,id,localfilename,localpath,remotefilename,remotefilepath,sdata,sfile);

	return SOAP_OK;
}

int ns_setcheckpoint(struct soap *soap,int id, int inewstate, int *istate)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->setcheckpoint(soap,id,inewstate,istate);

	return SOAP_OK;
}




int ns_getcheckpoint(struct soap *soap,int id, int *istate)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getcheckpoint(soap,id,istate);

	return SOAP_OK;
}



	
int ns_setsteerlog(struct soap *soap,int id, int inewsteerlog, int *isteerlog)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->setsteerlog(soap,id,inewsteerlog,isteerlog);

	return SOAP_OK;
}

int ns_getsteerlog(struct soap *soap,int id, int *isteerlog)
{
	if(m_steer != NULL)
		((CIoWFSimulation *)m_steer)->getsteerlog(soap,id,isteerlog);

	return SOAP_OK;
}

