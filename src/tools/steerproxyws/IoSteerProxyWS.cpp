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
#include "IoSteerProxyWS.h"

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
	//CIoModel *pMod;
	//CIoParam *pPar;
	pthread_t simtid;
	int m, s; /* master and slave sockets */
    //int port=8080;
	struct soap soap;
	struct soap *tsoap;
    pthread_t tid;	
    
    
	
 	

	int port=atoi(argv[1]);

	if(argv[2] != NULL)
		sprintf(m_server,"%s:%d",argv[2],port);
	else
		sprintf(m_server,"%s:%d","localhost",port);

			soap_init(&soap);
		const int soapbindfailed = 1;
		int i=0;
	    soap.send_timeout = 60; // 60 seconds
      	soap.recv_timeout = 60; // 60 seconds
		
		soap.max_keep_alive = 100; // max keep-alive sequence 
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
		char simportfile[500];
		//sprintf(svar,"IOME_WSPORT=%d",port);
        sprintf(svar,"%d",port);
		sprintf(simportfile,"steerproxyws_port.txt");
           fstream filestr;
			filestr.open (simportfile, fstream::out );
            filestr<<svar; 
			filestr.close();
		printf("INIT IOME has started listening on port %d\n",port);


	
		while(finish==0)
		{
		       	s = soap_accept(&soap);
		    	// copy soap environment and spawn thread
		      	tsoap = soap_copy(&soap);
		      	pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)tsoap);
		   
		   
		    fprintf(stderr, "Socket connection successful: master socket = %d port %d\n", m, port);
		      if (s < 0)
		      { soap_print_fault(&soap, stderr);
		        exit(-1);
		      } 
		      soap_serve(&soap);
			  soap_end(&soap);


		}
		 pthread_cancel(tid);

		printf("INIT IOME has finished\n");

		
		//soap_destroy(&soap);
		 //  }
		//}
			//TestSimulation->RunSimulation();
		//delete TestSimulation;
				
	
    	
    	
    	
    
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




int ns__add(struct soap *soap, double a, double b, double *result)
{     	
 soap_call_ns__add(&m_soap, m_server, "", a,b, result);

  return SOAP_OK;
} 






/*int ns__getsimulationstate(struct soap *soap, int id, int *istate)
{
	soap_call_ns__getsimulationstate(&m_soap, m_server, "", id,istate);

	return SOAP_OK;
}

int ns__setsimulationstate(struct soap *soap, int id, int inewstate, int *istate)
{
	soap_call_ns__setsimulationstate(&m_soap, m_server, "", id,inewstate, istate);


	return SOAP_OK;
}


int ns__getsimulantstate(struct soap *soap, int id, char *simmap, int *istate)
{
	soap_call_ns__getsimulantstate(&m_soap, m_server, "", id,simmap, istate);

	return SOAP_OK;
}

int ns__setsimulantstate(struct soap *soap, int id, char *simmap, int inewstate, int *istate)
{
	soap_call_ns__setsimulantstate(&m_soap, m_server, "", id,simmap,inewstate, istate);

	return SOAP_OK;
}


int ns__getsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{
	soap_call_ns__getsimulantinportstate(&m_soap, m_server, "", id,simmap,portid, istate);

	return SOAP_OK;
}

int ns__setsimulantinportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{
	soap_call_ns__setsimulantinportstate(&m_soap, m_server, "", id,simmap,portid, inewstate,istate);

	return SOAP_OK;
}


int ns__getsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int *istate)
{
	soap_call_ns__getsimulantoutportstate(&m_soap, m_server, "", id,simmap,portid, istate);

	return SOAP_OK;
}

int ns__setsimulantoutportstate(struct soap *soap, int id, char *simmap, int portid, int inewstate, int *istate)
{
	soap_call_ns__setsimulantoutportstate(&m_soap, m_server, "", id,simmap,portid, inewstate,istate);

	return SOAP_OK;
}



int ns__setsimulationprocid(struct soap *soap, char  *hostname, int *isimulationprocid)
{
	soap_call_ns__setsimulationprocid(&m_soap, m_server, "", hostname, isimulationprocid);

	return SOAP_OK;
}

int ns__getsimulationhostname(struct soap *soap, int isimulationid, char **shostname)
{
	soap_call_ns__getsimulationhostname(&m_soap, m_server, "", isimulationid, shostname);

	return SOAP_OK;
}

int ns__getfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char **sfile)
{
	soap_call_ns__getfile(&m_soap, m_server, "", id, localfilename,localpath,remotefilename,remotefilepath,sfile);

	return SOAP_OK;
}

int ns__putfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char *sdata,char **sfile)
{
	soap_call_ns__putfile(&m_soap, m_server, "", id, localfilename,localpath,remotefilename,remotefilepath,sdata,sfile);

	return SOAP_OK;
}

int ns__setcheckpoint(struct soap *soap,int id, int inewstate, int *istate)
{
	soap_call_ns__setcheckpoint(&m_soap, m_server, "", id, inewstate,istate);

	return SOAP_OK;
}




int ns__getcheckpoint(struct soap *soap,int id, int *istate)
{
	soap_call_ns__getcheckpoint(&m_soap, m_server, "", id,istate);

	return SOAP_OK;
}



	
int ns__setsteerlog(struct soap *soap,int id, int inewsteerlog, int *isteerlog)
{
	soap_call_ns__setsteerlog(&m_soap, m_server, "", id,inewsteerlog,isteerlog);

	return SOAP_OK;
}

int ns__getsteerlog(struct soap *soap,int id, int *isteerlog)
{
	soap_call_ns__getsteerlog(&m_soap, m_server, "", id,isteerlog);

	return SOAP_OK;
}*/


//Generic simulation operations only
int ns__newsimulation(struct soap *soap,int id,char *simname, char *xslname, int *status)
{
	try
	{
		soap_call_ns__newsimulation(&m_soap, m_server, "", id,simname,xslname,status);
	}
	catch(int j)
	{
       *status=-1;

	}
	return SOAP_OK;
}

int ns__createsimulation(struct soap *soap,int id,char *filename, int *status)
{
	try
	{
	soap_call_ns__createsimulation(&m_soap, m_server, "", id,filename,status);
	}
	catch(int j)
	{
		*status=-1;
	}

	return SOAP_OK;
}



int ns__runsimulation(struct soap *soap, int id,char *simfilecontent, char **result)
{
	string sresult="";
	char *myres=(char *)sresult.c_str();
	try
	{
		soap_call_ns__runsimulation(&m_soap, m_server, "", id,simfilecontent,&myres);
		*result=(char *)soap_malloc(soap,(1+strlen(myres))*sizeof(char));
		strcpy(*result,myres);
	}
	catch(int j)
	{
        j=-1;
	}



	return SOAP_OK;

}

int ns__requestsimulation(struct soap *soap,char *simfilecontent, int *isimid)
{
	string filename="simfile.xml";
	int status=0;
	try
	{
	soap_call_ns__requestsimulation(&m_soap, m_server, "", simfilecontent,isimid);
	//pthread_create(&simdataarray[simid].tid, NULL, (void*(*)(void*))run_simulation, (void*)isimid);
	}
    catch(int j)
	{
      *isimid=-1;
	}

	return SOAP_OK;
}

int ns__runrequestedsimulation(struct soap *soap,int isimid, int *status)
{
	string filename="simfile.xml";
	int istatus=0;
	try
	{
	soap_call_ns__runrequestedsimulation(&m_soap, m_server, "", isimid,status);
	}
	catch(int j)
	{
		*status=-1;
	}
	return SOAP_OK;
}


int ns__submitsimulation(struct soap *soap,char *simfilecontent, int *isimid)
{
	string filename="simfile.xml";
	int status=0;
	try
	{
	soap_call_ns__submitsimulation(&m_soap, m_server, "", simfilecontent,isimid);
	//pthread_create(&simdataarray[simid].tid, NULL, (void*(*)(void*))run_simulation, (void*)isimid);
	}
    catch(int j)
	{
      *isimid=-1;
	}

	return SOAP_OK;
}

int ns__setsimulationstatus(struct soap *soap, int newstatus, int isimid, int *status)
{
	string filename="simfile.xml";
	int istatus=0;
	try
	{
	soap_call_ns__setsimulationstatus(&m_soap, m_server, "", newstatus, isimid,status);
	}
	catch(int j)
	{
		*status=-1;
	}
	return SOAP_OK;
}

int ns__simulationstatus(struct soap *soap,int isimid, int *status)
{
	string filename="simfile.xml";
	int istatus=0;
	try
	{
	soap_call_ns__simulationstatus(&m_soap, m_server, "", isimid,status);
	}
	catch(int j)
	{
		*status=-1;
	}
	return SOAP_OK;
}

int ns__getsimulationresults(struct soap *soap,int isimid, char **result)
{
	string filename="simfile.xml";
	int istatus=0;
	string sresult="";
	char *mresult=(char *)sresult.c_str();

	try
	{
	//pthread_cancel(simdataarray[isimid].tid);
	soap_call_ns__getsimulationresults(&m_soap, m_server, "", isimid,&mresult);
	*result=(char *)soap_malloc(soap,(1+strlen(mresult))*sizeof(char));
	strcpy(*result,mresult);
	}
	catch(int j)
	{
      j=-1;
	}


	return SOAP_OK;
}

int ns__deletesimulation(struct soap *soap,int isimid, int *status)
{
	string filename="simfile.xml";
	int istatus=0;
	try
	{
	soap_call_ns__deletesimulation(&m_soap, m_server, "", isimid,status);
	}
    catch(int j)
	{
		*status=-1;
	}

	return SOAP_OK;
}



int ns__writesimulation(struct soap *soap,int id,char *filename, char **filecontent)
{
	char *mresult;
	try
	{
	soap_call_ns__writesimulation(&m_soap, m_server, "", id,filename,&mresult);
	*filecontent=(char *)soap_malloc(soap,(1+strlen(mresult))*sizeof(char));
	strcpy(*filecontent,mresult);
	}
	catch(int j)
	{

		j=-1;
	}

	return SOAP_OK;
}


int ns__readsimulation(struct soap *soap,int id,char *filename, int *status)
{
	try
	{
	soap_call_ns__readsimulation(&m_soap, m_server, "", id,filename,status);
	}
	catch(int j)
	{
		*status=-1;
	}

	return SOAP_OK;
}

int ns__writelocalsimulation(struct soap *soap,int id,char *filename, char **filecontent)
{
	char *mresult;
	try
	{
	soap_call_ns__writelocalsimulation(&m_soap, m_server, "", id,filename,&mresult);
	*filecontent=(char *)soap_malloc(soap,(1+strlen(mresult))*sizeof(char));
	strcpy(*filecontent,mresult);
	}
	catch(int j)
	{

		j=-1;
	}

	return SOAP_OK;
}

int ns__readlocalsimulation(struct soap *soap,int id,char *filename, int *status)
{
	try
	{
	soap_call_ns__readlocalsimulation(&m_soap, m_server, "", id,filename,status);
	}
	catch(int j)
	{
		*status=-1;
	}

	return SOAP_OK;
}




int ns__listmetadata(struct soap *soap, int id, char **list)
{
	string sval="";
	char *msval=(char *)sval.c_str();

	try
	{
			soap_call_ns__listmetadata(&m_soap, m_server, "", id,&msval);

	*list=(char *)soap_malloc(&m_soap,(1+strlen(msval))*sizeof(char));
	strcpy(*list,msval);
	}
	catch(int j)
	{
		j=-1;
	}

	return SOAP_OK;

}


int ns__deletemetadata(struct soap *soap,int id,char *name, int *status)
{
	try
	{
	soap_call_ns__deletemetadata(&m_soap, m_server, "", id,name,status);
	}
	catch(int j)
	{
		*status=-1;
	}

	return SOAP_OK;

}

int ns__exitiome(struct soap *soap,int id, int *status)
{
	try
	{
		soap_call_ns__exitiome(&m_soap, m_server, "", id,status);

	}
	catch(int j)
	{
		*status=-1;
	}
	finish=1;
	return SOAP_OK;
}



int ns__addparamdouble(struct soap *soap,int id,char *name, double value, int iflag, int *status )
{
	soap_call_ns__addparamdouble(&m_soap, m_server, "", id,name,value,iflag,status);
	
	return SOAP_OK;
}


int ns__addparamint(struct soap *soap, int id,char *name, int value, int iflag, int *status )
{
	soap_call_ns__addparamint(&m_soap, m_server, "", id,name,value,iflag,status);

	return SOAP_OK;
}


int ns__addparamvec(struct soap *soap, int id,char *name, struct fdata value, int n, int iflag, int *status )
{
	soap_call_ns__addparamvec(&m_soap, m_server, "", id,name,value,n,iflag,status);

	return SOAP_OK;
}


int ns__addparammat(struct soap *soap, int id,char *name, struct fdata value, int nr, int nc,  int iflag, int *status )
{
	soap_call_ns__addparammat(&m_soap, m_server, "", id,name,value,nr,nc,iflag,status);

	return SOAP_OK;
}


int ns__addparamstring(struct soap *soap, int id,char *name, char *value, int iflag, int *status )
{
	soap_call_ns__addparamstring(&m_soap, m_server, "", id,name,value,iflag,status);

	return SOAP_OK;
}


int ns__addparammmat3d(struct soap *soap, int id,char *name, struct fdata value, int n, int p, int q, int nr, int nc,int iflag, int *status )
{

	soap_call_ns__addparammmat3d(&m_soap, m_server, "", id,name,value,n,p,q,nr,nc,iflag,status);

	return SOAP_OK;
}



int ns__addmetadata(struct soap *soap,int id, char *name, char *property, int *status)
{
	

	
	soap_call_ns__addmetadata(&m_soap, m_server, "", id,name, property, status);
	
	
	return SOAP_OK;
}



int ns__getparamdouble(struct soap *soap,int id,char *name, double *value )
{

	soap_call_ns__getparamdouble(&m_soap, m_server, "", id,name,value);

	return SOAP_OK;
}


int ns__getparamint(struct soap *soap, int id,char *name, int *value )
{
	soap_call_ns__getparamint(&m_soap, m_server, "", id,name,value);

	return SOAP_OK;
}


int ns__getparamvec(struct soap *soap, int id,char *name, int n, struct fdata **value )
{
	
	//double *fval=(double *)calloc(n,sizeof(double));

	struct fdata *fval;

	try
	{
	fval=(struct fdata *)malloc(sizeof(struct fdata));
	(*fval).__ptr=(double *)malloc(n*sizeof(double));
	double *dfval=(*fval).__ptr;



	soap_call_ns__getparamvec(&m_soap, m_server, "", id,name,n,&fval);

		(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
		(*value)->__ptr=(double *)soap_malloc(soap,n*sizeof(double));

        
		for(int i=0; i<n; i++)
		{
			(*value)->__ptr[i]=(*fval).__ptr[i];
			printf("%f \n",(*fval).__ptr[i]);
		}
			(*value)->__size=n;

	}
	catch(int j)
	{
		j=-1;
	}

	return SOAP_OK;
}


int ns__getparammat(struct soap *soap, int id,char *name, int nr, int nc, struct fdata **value )
{
	double *darray=(double *)calloc(nr*nc,sizeof(double));
	struct fdata *fval;

	try
	{
	fval=(struct fdata *)malloc(sizeof(struct fdata));
	(*fval).__ptr=(double *)malloc(nr*nc*sizeof(double));
	double *dfval=(*fval).__ptr;	
	soap_call_ns__getparammat(&m_soap, m_server, "", id,name,nr,nc,&fval);

		(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
		(*value)->__ptr=(double *)soap_malloc(soap,nr*nc*sizeof(double));

        
		for(int i=0; i<nr*nc; i++)
		{
			(*value)->__ptr[i]=(*fval).__ptr[i];
			printf("%f \n",(*fval).__ptr[i]);
		}
			(*value)->__size=nr*nc;


	}
	catch(int j)
	{
		j=-1;
	}

	return SOAP_OK;
}


int ns__getparamstring(struct soap *soap, int id,char *name, char **value )
{
	string sval="";
	char *msval=(char *)sval.c_str();

	try
	{
	soap_call_ns__getparamstring(&m_soap, m_server, "", id,name,&msval);
	*value=(char *)soap_malloc(soap,(1+strlen(msval))*sizeof(char));
	strcpy(*value,msval);
	}
	catch(int j)
	{
		j=-1;
	}

	return SOAP_OK;
}


int ns__getparammmat3d(struct soap *soap, int id,char *name, int n, int p, int q, int nr, int nc, struct fdata **value  )
{
	double *darray=(double *)calloc(n*p*q*nr*nc,sizeof(double));
	struct fdata *fval;
    int na=n*p*q*nr*nc;
	try
	{
	fval=(struct fdata *)malloc(sizeof(struct fdata));
	(*fval).__ptr=(double *)malloc(n*p*q*nr*nc*sizeof(double));
	double *dfval=(*fval).__ptr;

	soap_call_ns__getparammmat3d(&m_soap, m_server, "", id,name,n,p,q,nr,nc,value);
		(*value)=(struct fdata *)soap_malloc(soap,sizeof(struct fdata));
		(*value)->__ptr=(double *)soap_malloc(soap,na*sizeof(double));

        
		for(int i=0; i<na; i++)
		{
			(*value)->__ptr[i]=dfval[i];
			printf("%f \n",dfval[i]);
		}
			(*value)->__size=na;


	}
	catch(int j)
	{
		j=-1;
	}

	return SOAP_OK;
}



int ns__getmetadata(struct soap *soap, int id, char *name, char **property)
{
	string sval="";
	char *msval=(char *)sval.c_str();

	try
	{
		soap_call_ns__getmetadata(&m_soap, m_server, "", id,name,&msval);
	*property=(char *)soap_malloc(soap,(1+strlen(msval))*sizeof(char));
	strcpy(*property,msval);
	}
	catch(int j)
	{
		j=-1;
	}
	return SOAP_OK;
}


int ns__setparamdouble(struct soap *soap, int id,char *name, double value, int *status )
{

	soap_call_ns__setparamdouble(&m_soap, m_server, "", id,name,value,status);

	return SOAP_OK;
}


int ns__setparamint(struct soap *soap, int id,char *name, int value, int *status  )
{
	soap_call_ns__setparamint(&m_soap, m_server, "", id,name,value,status);

	return SOAP_OK;
}


int ns__setparamvec(struct soap *soap, int id,char *name, struct fdata value, int n, int *status  )
{

	soap_call_ns__setparamvec(&m_soap, m_server, "", id,name,value,n,status);

	return SOAP_OK;
}


int ns__setparammat(struct soap *soap, int id,char *name, struct fdata value, int nr, int nc, int *status  )
{
	soap_call_ns__setparammat(&m_soap, m_server, "", id,name,value,nr,nc,status);

	return SOAP_OK;
}


int ns__setparamstring(struct soap *soap, int id,char *name, char *value, int *status  )
{

	soap_call_ns__setparamstring(&m_soap, m_server, "", id,name,value,status);

	return SOAP_OK;
}


int ns__setparammmat3d(struct soap *soap, int id,char *name, struct fdata value,  int n, int p, int q, int nr, int nc, int *status  )
{
	soap_call_ns__setparammmat3d(&m_soap, m_server, "", id,name,value,n,p,q,nr,nc,status);

	return SOAP_OK;
}



int ns__setmetadata(struct soap *soap,int id, char *name, char *property, int *status)
{
	soap_call_ns__setmetadata(&m_soap, m_server, "", id,name,property,status);

	return SOAP_OK;
}


int ns__deleteparam(struct soap *soap,char *name, int id, int *status )
{
	soap_call_ns__deleteparam(&m_soap, m_server, "", name,id, status);
	return SOAP_OK;
}

int ns__listparam(struct soap *soap,char *type, int id, char  **list )
{
	string sval="";
	char *msval=(char *)sval.c_str();

	try
	{
			soap_call_ns__listparam(&m_soap, m_server, "", type, id,&msval);

	*list=(char *)soap_malloc(&m_soap,(1+strlen(msval))*sizeof(char));
	strcpy(*list,msval);
	}
	catch(int j)
	{
		j=-1;
	}

	return SOAP_OK;
}




int ns__getnumobj(struct soap *soap,int id, int *numobj)
{
	soap_call_ns__getnumobj(&m_soap, m_server, "", id,numobj);
	return SOAP_OK;
}

int ns__getobjnum(struct soap *soap,int id, int *objnum)
{
	soap_call_ns__getobjnum(&m_soap, m_server, "", id,objnum);
	return SOAP_OK;
}






