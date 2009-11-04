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

#include <iome/genericsimulationlib/IoGenericSimulationLib.h>


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

int oldmain(int argc, char* argv[])
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
    
	return 0;
}


int exitiome_(int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	int id=0;

	if(sserver != NULL)
				sprintf(m_serverclient,"%s:%d",sserver,port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

	soap_call_ns__exitiome(&m_soapclient, m_serverclient, "",id, &status);

	return status;
}


int runsimulationstep_(int id, int istepnum, int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	//int id=0;

	if(sserver != NULL)
				sprintf(m_serverclient,"%s:%d",sserver,port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

	soap_call_ns__runsimulationstep(&m_soapclient, m_serverclient, "",id, istepnum, &status);

	return status;

}




int newsimulation_(int id, char *simname, char *xslname, int port, char *sserver )
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;	
	if((sserver==NULL))
	{

		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__newsimulation(&m_soapclient, m_serverclient, "", id, simname,xslname, &status);
	return status;

}

int createsimulation_(int id, char *simfile, char *simname, int port, char *sserver )
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;	
	if((sserver==NULL))
	{

		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__createsimulation(&m_soapclient, m_serverclient, "", id, simfile, &status);
	return status;

}

int runsimulation_(int id, char *simfilecontent, int port, char *sserver )
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;	
	
	//int ns__createandrunsimulation(struct soap *soap,char *simfilecontent, char **result)
    char *sresult;
	
	if((sserver==NULL))
	{

		sserver="localhost";
	}

    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__runsimulation(&m_soapclient, m_serverclient, "", id, simfilecontent, &sresult);
	printf("%s",sresult);
	return status;

}

int requestsimulation_(char *simfilecontent, int *isimid, int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
		if(sserver==NULL)
	{
		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__requestsimulation(&m_soapclient, m_serverclient, "", simfilecontent, isimid);
	return status;
}

int runrequestedsimulation_(int isimid, int *status, int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int istatus=0;
		if(sserver==NULL)
	{
		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__runrequestedsimulation(&m_soapclient, m_serverclient, "", isimid, status);
	return istatus;
}


int submitsimulation_(char *simfilecontent, int *isimid, int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
		if(sserver==NULL)
	{
		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__submitsimulation(&m_soapclient, m_serverclient, "", simfilecontent, isimid);
	return status;
}

int simulationstatus_(int isimid, int *status, int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int istatus=0;
		if(sserver==NULL)
	{
		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__simulationstatus(&m_soapclient, m_serverclient, "", isimid, status);
	return istatus;
}

int getsimulationresults_(int isimid, char **result, int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	char *scontent;

	scontent=(char *)calloc(5000,sizeof(char));


		if(sserver==NULL)
	{
		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__getsimulationresults(&m_soapclient, m_serverclient, "", isimid, &scontent);
	strcpy(scontent, *result);

	return status;
}


int deletesimulation_(int isimid, int *status, int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int istatus=0;
		if(sserver==NULL)
	{
		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__deletesimulation(&m_soapclient, m_serverclient, "", isimid, status);
	return istatus;

}

int readsimulation_(int id, char *simfile, int port, char *sserver )
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
		if(sserver==NULL)
	{
		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__readsimulation(&m_soapclient, m_serverclient, "", id, simfile, &status);
	return status;
}

int readlocalsimulation_(int id, char *simfile, int port, char *sserver )
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
		if(sserver==NULL)
	{
		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__readlocalsimulation(&m_soapclient, m_serverclient, "", id, simfile, &status);
	return status;
}


int writesimulation_(int id, char *simfile,  int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	char *scontent;

	scontent=(char *)calloc(5000,sizeof(char));

	if(sserver==NULL)
	{

		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__writesimulation(&m_soapclient, m_serverclient, "",  id, simfile, &scontent);

	//if strlen(scontent)>0 
	//write content to file

	//call create simulation

	return status;
}

int writelocalsimulation_(int id, char *simfile,  int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	char *scontent;

	scontent=(char *)calloc(5000,sizeof(char));

	if(sserver==NULL)
	{

		sserver="localhost";
	}
    sprintf(m_serverclient,"%s:%d",sserver,port);
	soap_call_ns__writesimulation(&m_soapclient, m_serverclient, "",  id, simfile, &scontent);

	//if strlen(scontent)>0 
	//write content to file

	//call create simulation

	return status;
}

int addintparam_(int id, char *sname,int iv,int iflag,  int port, char *sserver )
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	int isize;
	double *darray;
	char *name;
	name=sname;	
	int dvalue=iv;
				

	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
			

	soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", id, name, dvalue, iflag, &status );
    
	return status;
}


int adddoubleparam_(int id, char *sname,double fv,int iflag,  int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	int isize;
	double *darray;
	char *name;
	name=sname;	
	double dvalue=fv;
				

	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);

	soap_call_ns__addparamdouble(&m_soapclient, m_serverclient, "", id, name, dvalue, iflag, &status );


	return status;
}


int addstringparam_(int id, char *sname,char *sv,int iflag,  int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	int isize;
	double *darray;
	char *name;
	name=sname;	
	
	char*dvalue=(char *)(sv);
	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
			
	soap_call_ns__addparamstring(&m_soapclient, m_serverclient, "", id, name, dvalue, iflag, &status );	
	return status;
}


int addmatparam_(int id, char *sname,double *vv,int nr, int nc,int iflag,   int port, char *sserver){

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	int isize;
	double *darray;
	char *name;
	name=sname;		
	int size=nr*nc;
	float fv;
	int ind=0;

	//the array of floats is string consisting of a comma separated list
	//with no white space


	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
			
	struct fdata thedata;
	thedata.__ptr=vv;
	thedata.__size=nr*nc;

	//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
	soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", id, name, thedata,nr,nc,iflag,&status );
	return status;
}

int addvecparam_(int id, char *sname,double *vv,int n,int iflag,   int port, char *sserver){

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	int isize;
	double *darray;
	char *name;
	name=sname;		
	int size=n;
	float fv;
	int ind=0;

	//the array of floats is string consisting of a comma separated list
	//with no white space


	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
			
	struct fdata thedata;
	thedata.__ptr=vv;
	thedata.__size=n;

	//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
	soap_call_ns__addparamvec(&m_soapclient, m_serverclient, "", id, name, thedata,n,iflag,&status );
	return status;
}


int addmmat3dparam_(int id, char *sname,double *vv ,int ni, int nj, int nk, int nr, int nc,int iflag,   int port, char *sserver){

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	int isize;
	double *darray;
	char *name;
	name=sname;		
	float fv;
	int ind=0;

	//the array of floats is string consisting of a comma separated list
	//with no white space


	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
			
	struct fdata thedata;
	thedata.__ptr=vv;
	thedata.__size=nr*nc;

	//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
	soap_call_ns__addparammmat3d(&m_soapclient, m_serverclient, "", id, name, thedata,ni,nj,nk,nr,nc,iflag,&status );
	return status;
}



int addmetadata_(int id, char *sname, char *sproperty,  int port, char *sserver)
{	
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	char *content=sproperty;
	char *name=sname;

	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);

	soap_call_ns__addmetadata(&m_soapclient, m_serverclient, "", id, name, content, &status);
	
	return status;
}


int setmetadata_(int id, char *sname, char *sproperty,  int port, char *sserver)
{

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	char *content=sproperty;
	char *name=sname;
	//int id=0;

	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);

	soap_call_ns__setmetadata(&m_soapclient, m_serverclient, "", id, name, content, &status);
	printf("%s",content);
	

	return status;
}


int getmetadata_(int id, char *sname, char *sproperty,  int port, char *sserver)
{	
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	char *content=sproperty;
	char *name=sname;
	//int id=0;

	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);

	soap_call_ns__getmetadata(&m_soapclient, m_serverclient, "", id, name, &content);
	printf("%s",content);
	

	return status;
}

int deletemetadata_(int id, char *sname,  int port, char *sserver)
{	
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


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

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

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



int setintparam_(int id, char *sname,int iv,  int port, char *sserver )
{	
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;
	
	int status=0;
	int isize;
	double *darray;
	char *name=sname;

	int dvalue=iv;

	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
	

	soap_call_ns__setparamint(&m_soapclient, m_serverclient, "", id, name, dvalue, &status );

	return status;

}


int setdoubleparam_(int id, char *sname,double fv,  int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	int isize;
	char *name=sname;


	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
	

	soap_call_ns__setparamdouble(&m_soapclient, m_serverclient, "", id, name, fv, &status );

	return status;

}


int setstringparam_(int id, char *sname,char *sv,  int port, char *sserver)
{	
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	int isize;
	char *name=sname;


	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
	

	soap_call_ns__setparamstring(&m_soapclient, m_serverclient, "", id, name, sv, &status );
	return status;

}


int setmatparam_(int id, char *sname,double *vv,int nr, int nc,   int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	int isize;
	double *darray;
	char *name=sname;


	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
	struct fdata sdata;
	sdata.__ptr=vv;
	sdata.__size=nr*nc;

	//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
	soap_call_ns__setparammat(&m_soapclient, m_serverclient, "", id, name, sdata,nr,nc,&status );

	return status;

}


int setvecparam_(int id, char *sname,double *vv,int n,   int port, char *sserver)
{

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	int isize;
	double *darray;
	char *name=sname;


	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
	
	struct fdata sdata;
	sdata.__ptr=vv;
	sdata.__size=n;
	//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
	soap_call_ns__setparamvec(&m_soapclient, m_serverclient, "", id, name, sdata,n,&status );

	return status;

}


int setmmat3dparam_(int id, char *sname,double *vv ,int ni, int nj, int nk, int nr, int nc,   int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	int isize;
	double *darray;
	char *name=sname;


	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
	
	struct fdata sdata;
	sdata.__ptr=vv;
	sdata.__size=ni*nj*nk*nr*nc;

	//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
	soap_call_ns__setparammmat3d(&m_soapclient, m_serverclient, "", id, name, sdata,ni,nj,nk,nr,nc,&status );

	return status;


}



int getintparam_(int *id, char *sname,int *iv,  int *port, char *sserver )
{	

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	
	int status=0;
	//int isize;
	//double *darray;
	//int port;
	//char *name;
	//name=argv[3];
	//char *dvalue=(char *)calloc(500,sizeof(char));


				int dvalue=0;

			if(sserver != NULL)
				sprintf(m_serverclient,"%s:%d",sserver,*port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",*port);
			
			soap_call_ns__getparamint(&m_soapclient, m_serverclient, "", *id, sname, &dvalue );
			//print the value
			printf("here\n%s\n%s\n",sname, sserver);
			*iv=dvalue;

	return status;
}
int getdoubleparam_(int id, char *sname,double *fv,  int port, char *sserver){	

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	int isize;
	double *darray;
	//int port;
	//char *name;
	//name=argv[3];
	//char *dvalue=(char *)calloc(500,sizeof(char));


				double dvalue=0;

			if(sserver != NULL)
				sprintf(m_serverclient,"%s:%d",sserver,port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			soap_call_ns__getparamdouble(&m_soapclient, m_serverclient, "", id, sname, &dvalue );
			//print the value
			printf("%d",dvalue);
			*fv=dvalue;

	return status;
}
int getstringparam_(int id, char *sname,char **sv,  int port, char *sserver){
	
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;
	int isize;
	double *darray;
	//int port;
	//char *name;
	//name=argv[3];
	char *dvalue=(char *)calloc(500,sizeof(char));



			if(sserver != NULL)
				sprintf(m_serverclient,"%s:%d",sserver,port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

			soap_call_ns__getparamstring(&m_soapclient, m_serverclient, "", id, sname, &dvalue );
			//print the value
			printf("%s",dvalue);
			strcpy(*sv,dvalue);
			//*fv=dvalue;

	return status;
}
int getmatparam_(int id, char *sname,double **vv,int nr, int nc,   int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;
	
	
		int status=0;
	int isize=nr*nc;
	double *darray;
	//int port;
	//char *name;
	//name=argv[3];
	//char *dvalue=(char *)calloc(500,sizeof(char));


				double dvalue=0;

			if(sserver != NULL)
				sprintf(m_serverclient,"%s:%d",sserver,port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

					struct fdata *fval;
					fval=(struct fdata *)malloc(sizeof(struct fdata));
					(*fval).__ptr=(double *)malloc(isize*sizeof(double));

					//soap_call_ns__getparamvec(&m_soapclient, m_serverclient, "", name,isize, &darray );
					soap_call_ns__getparammat(&m_soapclient, m_serverclient, "", id, sname, nr,nc,&fval );
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
							{
								(*vv)[itot]=fval->__ptr[itot];
								itot++;
							}
						}
						
					}
					printf("\n");
				free(darray);
	return status;
}

int getvecparam_(int id, char *sname,double **vv,int n,   int port, char *sserver)
{

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


int status=0;
	int isize=n;
	double *darray;
	//int port;
	//char *name;
	//name=argv[3];
	//char *dvalue=(char *)calloc(500,sizeof(char));


				double dvalue=0;

			if(sserver != NULL)
				sprintf(m_serverclient,"%s:%d",sserver,port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

					struct fdata *fval;
					fval=(struct fdata *)malloc(sizeof(struct fdata));
					(*fval).__ptr=(double *)malloc(isize*sizeof(double));

					//soap_call_ns__getparamvec(&m_soapclient, m_serverclient, "", name,isize, &darray );
					soap_call_ns__getparamvec(&m_soapclient, m_serverclient, "", id, sname,isize, &fval );
					//print the value
					int i,j;
					int itot=0;
					for(i=0; i<n;i++)
					{
							printf("%f ",fval->__ptr[itot]);
							if(itot>n)
								break;
							else
							{
								(*vv)[itot]=fval->__ptr[itot];
								itot++;
							}
						
						
					}
					printf("\n");
				free(darray);
	return status;
}
int getmmat3dparam_(int id, char *sname,double **vv ,int ni, int nj, int nk, int nr, int nc,   int port, char *sserver){
	
	int status=0;
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	
	//int port;
	//char *name;
	//name=argv[3];
	//char *dvalue=(char *)calloc(500,sizeof(char));
				int isize;
				double *darray;
				double dvalue=0;
				isize=ni*nj*nk*nr*nc;
				darray=(double *)calloc(isize,sizeof(double));


			if(sserver != NULL)
				sprintf(m_serverclient,"%s:%d",sserver,port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			
					struct fdata *fval;
					fval=(struct fdata *)malloc(sizeof(struct fdata));
					(*fval).__ptr=(double *)malloc(ni*nj*nk*nr*nc*sizeof(double));

					//soap_call_ns__getparamvec(&m_soapclient, m_serverclient, "", name,isize, &darray );
					soap_call_ns__getparammmat3d(&m_soapclient, m_serverclient, "", id, sname, ni,nj,nk,nr,nc,&fval );
					//print the value
					int i1,i2,i3;
					int i,j;
					int itot=0;
					for(i1=0; i1<ni;i1++)
					{
						for(i2=0; i2<nj;i2++)
						{
							for(i3=0; i3<nk;i3++)
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
										{
											(*vv)[itot]=fval->__ptr[itot];
											itot++;
										}
									}
									
								}
					printf("\n");
							}
					}
					}
	free(darray);
					return status;
}


int deleteparam_(char *name, int id, int *status,  int port, char *sserver )
{

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int istatus=0;
	
	int isize;


	if(sserver != NULL)
		sprintf(m_serverclient,"%s:%d",sserver,port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);
	

	soap_call_ns__deleteparam(&m_soapclient, m_serverclient, "", name, id, status );
	


	return istatus;
}




int listparam_(char *type, int id, char  **list ,  int port, char *sserver)
{

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;


	return status;
}



int getnumobj_(int *numobj, int id,  int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;


	return status;
}


int getobjnum_(int *objnum, int id,  int port, char *sserver)
{

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;


	return status;
}




int testgroupbarrier_(int id, int *state,  int port, char *sserver)
{

	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;


	return status;
}

int setgroupbarrier_(int id, int *state,  int port, char *sserver)
{
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;


	int status=0;


	return status;
}


















