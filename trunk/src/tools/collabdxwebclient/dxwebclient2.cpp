#include <stdio.h>

#ifndef IO_MSVC
   #include <unistd.h>  //the sleep function
#else

#endif
#include <stdlib.h>
#include <string.h>


#include "dxl.h"

#ifndef IO_MSVC
	#include <iome/simulation/IoInitialiser.h>
	#include <iome/simulation/soapH.h>
	#include <iome/simulation/IoGenericSteerSimulation.h>
	#include <iome/simulation/IoSteerWS.nsmap>
#else
	#include <iome/simulation/IoInitialiser.h>
	#include <iome/simulation/soapH.h>
	#include <iome/simulation/IoGenericSteerSimulation.h>
	#include <iome/simulation/IoSteerWS.nsmap>
#endif





#ifndef BASE
#define BASE "/usr/lpp/dx"
#endif

char m_server[200] = "http://localhost:8080/";
struct soap m_soap;

int m_iclosedx=0;
int m_iupdatelocal=0;
int m_iupdateserver=0;

int m_id=0;
int m_clientid=0;
int m_nfinputs=0;
int m_nfoutputs=0;
int m_niinputs=0;
int m_nioutputs=0;
int m_nvinputs=0;
int m_nvoutputs=0;
int m_nsinputs=0;
int m_nsoutputs=0;

int m_infinit=0; /*if this is 0 input ouput ports have not been initialised */
int m_outfinit=0; /*if this is 0 input ouput ports have not been initialised */
int m_iniinit=0; /*if this is 0 input ouput ports have not been initialised */
int m_outiinit=0; /*if this is 0 input ouput ports have not been initialised */
int m_invinit=0; /*if this is 0 input ouput ports have not been initialised */
int m_outvinit=0; /*if this is 0 input ouput ports have not been initialised */
int m_insinit=0; /*if this is 0 input ouput ports have not been initialised */
int m_outsinit=0; /*if this is 0 input ouput ports have not been initialised */

//float params
char **m_sfinputs=NULL;  /*The actual inputs*/
char **m_sifvalues=NULL; /*Current values*/
char **m_sfoutputs=NULL;
char **m_sofvalues=NULL;

//integer params
char **m_siinputs=NULL;  /*The actual inputs*/
char **m_siivalues=NULL; /*Current values*/
char **m_sioutputs=NULL;
char **m_soivalues=NULL;

//vector params
char **m_svinputs=NULL;  /*The actual inputs*/
char **m_sivvalues=NULL; /*Current values*/
char **m_svoutputs=NULL;
char **m_sovvalues=NULL;
int *m_ilenvvals=NULL; /*length of vector values*/

//string params
char **m_ssinputs=NULL;  /*The actual inputs*/
char **m_sisvalues=NULL; /*Current values*/
char **m_ssoutputs=NULL;
char **m_sosvalues=NULL;

DXLConnection *conn = NULL;



void SyncAfterExecute(DXLConnection *conn)
{
  int status=1;

   while (status) {
      #ifndef IO_MSVC
		sleep(0.1);
	  #else
        Sleep(0.1);
      #endif
      if (DXLIsMessagePending(conn))
         DXLHandlePendingMessages(conn);
      DXLGetExecutionStatus(conn, &status);
   }
}


/* 
 * this routine simply prints the maximum value as received from the
 * DXLOutput tool 
 */

//set state to finish
void closedx_handler(DXLConnection *conn, const char *name, const char *value,    void *data)
{
//printf("closedx handler\n");
//if(m_iuselocal==0)		
       m_iclosedx=atoi(value);
}


void updatelocal_handler(DXLConnection *conn, const char *name, const char *value,    void *data)
{
  //printf("uselocal handler\n"); 


			m_iupdatelocal=atoi(value);
   //if(m_iuselocal==1)
   //{
	//		
	//		DXLExecuteOnce(conn);
   //}
}
//send our values to remote server
void updateserver_handler(DXLConnection *conn, const char *name, const char *value,    void *data)
{
 //printf("updateserver handler\n");  

			m_iupdateserver=atoi(value);
   //if(m_iupdateserver==0)
   //{
	//		
	//		DXLExecuteOnce(conn);
   //}

}

void savestate_handler(DXLConnection *conn, const char *name, const char *value,    void *data)
{
 //printf("savestate handler\n");   

char snhis[20]="";
	char sxmlfile[600]="";
	int nhistory;
	char content[400];
	char *scont;
    scont=content;
		char *scontent;

	scontent=(char *)calloc(5000,sizeof(char));

	int status=0;
	
  //get nhistory
	//soap_call_ns__getparamint(&m_soap, m_server, "", "nhistory", &nhistory );

  //incerement nhistory
  nhistory++;

  sprintf(snhis,"%d",nhistory);

  //get metadata.name and create new name
  //soap_call_ns__getmetadata(&m_soap, m_server, "", 0, "name", &scont);
  sprintf(sxmlfile,"%s_%d.xml",scont,nhistory);

  //soap_call_ns__writesimulation(&m_soap, m_server, "",  sxmlfile, &scontent);

  
  //Write simulation using new name

  DXLSetValue(conn, "nhistory", snhis);
  //soap_call_ns__setparamint(&m_soap, m_server, "", "nhistory",nhistory, &status );

 free(scontent);

}

void ihistory_handler(DXLConnection *conn, const char *name, const char *value,    void *data)
{
//printf("ihistory handler\n");

		int ihistory;
		int status;
		sscanf(value,"%d",&ihistory);
       //soap_call_ns__setparamint(&m_soap, m_server, "", "ihistory",ihistory, &status );

}

void loadstate_handler(DXLConnection *conn, const char *name, const char *value,    void *data)
{
 //printf("locadstatehandler\n");
	char sxmlfile[600]="";
	char content[400];
	char *scont;
    scont=content;
	
	int status=0;
	int ihistory;



  //get nhistory
//	soap_call_ns__getparamint(&m_soap, m_server, "", "ihistory", &ihistory );
 //get metadata.name and create new name
 // soap_call_ns__getmetadata(&m_soap, m_server, "", 0, "name", &scont);
 // sprintf(sxmlfile,"%s_%d.xml",scont,ihistory);


  //soap_call_ns__readsimulation(&m_soap, m_server, "",  sxmlfile, &status);

}
//Output value handlers
   
void output_fvalue_handler(DXLConnection *conn, const char *name, const char *value, void *data)
{
  //printf("output fvalue handler %s %s\n",name , value);
 int i=0, j, n, ioutput=-1, noutput;
   char **s,**sval, buf[16];
   double dval;
    char sname[400]="";
   
 	int status=0;
	
	if(m_sfoutputs && (m_iupdateserver ==1))
	{
		  
		  for(j=0; j<m_nfoutputs; j++)
		  {
		  	printf("actual out float stuff %s %s\n",m_sfoutputs[j],m_sofvalues[j]);
		  	if(strcmp(m_sfoutputs[j], name)==0)
		  	{
		  		sprintf(m_sofvalues[j],"%s", value);
				strncpy(sname,name,strlen(name)-1);
				dval=atof(value);
				//printf("actual out float stuff %s %f\n",sname,dval);
				soap_call_ns__setparamdouble(&m_soap, m_server, "", m_id, sname,dval, &status );

    			//soap_call_ns__status(&m_soap, m_server, "", m_clientid, &status);
    			//soap_call_ns__setinput(&m_soap, m_server, "", m_clientid, m_sfoutputs[j], m_sofvalues[j], &status);
				if (m_soap.error)
				{ 
		  			printf("output fvalue handler\n");
		  			soap_print_fault(&m_soap, stderr);
		  			exit(1);
				}    			  		
		  		break;
		  	}		  	
		  }//end count over m_noutputs
	}//end check on m_soutputs
}

void output_ivalue_handler(DXLConnection *conn, const char *name, const char *value, void *data)
{
 //printf("output ivalue handler\n");
  int i=0, j, n, ioutput=-1, noutput;
   char **s,**sval, buf[16];
   char sname[400]="";
   int ival;
   
 	int status=0;

	if(m_sioutputs  && (m_iupdateserver ==1))
	{
		  for(j=0; j<m_nioutputs; j++)
		  {
		  	if(strcmp(m_sioutputs[j], name)==0)
		  	{
		  		sprintf(m_soivalues[j],"%s", value);
		  		//printf(m_sofvalues[j],"%s", value);
						  		//sprintf(m_sofvalues[j],"%s", value);
				strncpy(sname,name,strlen(name)-1);
				sscanf(value,"%d",&ival);
				//printf("i out soap vals %s %s %s %s %s %d\n",name, sname,m_sioutputs[j],m_soivalues[j], value,ival);
				soap_call_ns__setparamint(&m_soap, m_server, "", m_id,sname,ival, &status );

    			//soap_call_ns__status(&m_soap, m_server, "", m_clientid, &status);
    			//soap_call_ns__setinput(&m_soap, m_server, "", m_clientid, m_sfoutputs[j], m_sofvalues[j], &status);
				if (m_soap.error)
				{ 
		  			printf("output ivalue handler\n");
		  			soap_print_fault(&m_soap, stderr);
		  			exit(1);
				}    			  		
		  		break;
		  	}		  	
		  }//end count over m_noutputs
	}//end check on m_soutputs
}

void output_vvalue_handler(DXLConnection *conn, const char *name, const char *value, void *data)
{
   int i=0, j, n, ioutput=-1, noutput;
   char **s,**sval, buf[16];
   int vecsize;
   double *vval;
   int vsize=0;
   char *newval;
   char *snewval;
   int ifirst,ilast;
   char *pch;
   char sname[400]="";
   //printf("output vvalue handler %s %s\n", name, value);
 	int status=0;

	if(m_svoutputs   && (m_iupdateserver ==1))
	{
		  for(j=0; j<m_nvoutputs; j++)
		  {
		  	if(strcmp(m_svoutputs[j], name)==0)
		  	{
		  		newval=(char *)calloc(strlen(value),sizeof(char));
		  		snewval=(char *)calloc(strlen(value),sizeof(char));
		  		
		  		pch=strchr(value,'[');
				ifirst=(int)(pch-value+1);
				pch=strchr(value,']');
				ilast=(int)(pch-value+1);
				strncpy(newval,value+ifirst,ilast-ifirst-1);
                //printf("newval before strtok %s\n",newval);
                
                strcpy(snewval,newval);
                //cout tokens
				pch = strtok (newval," ");
				vsize=0;
				while (pch != NULL)
				{
					vsize++;
					//printf ("%s\n",pch);
					pch = strtok (NULL, " ");
				}
                
				//allocate memory for array
                vval=(double *)calloc(vsize,sizeof(double));
                int i=0;
				pch = strtok (snewval," ");
				while (pch != NULL)
				{
					vval[i]=atof(pch);
					pch = strtok (NULL, " ");
					i++;
				}
               //printf("strtok values %f %f %f %d newval %s \n",vval[0],vval[1],vval[2],vsize,newval);



				sprintf(m_sovvalues[j],"%s", value);
				strncpy(sname,name,strlen(name)-1);
				//sscanf(value,"%d",&vval);
                

				struct fdata sdata;
				sdata.__ptr=vval;
				sdata.__size=vsize;
                m_ilenvvals[j]=vsize;
                
                //printf("actual output vvalue handler %s %s\n", sname, value);
                //printf("values %f %f %f %d",vval[0],vval[1],vval[2],vecsize);
				soap_call_ns__setparamvec(&m_soap, m_server, "",m_id, sname,sdata,vsize, &status );
                free(vval);
                free(newval);
                free(snewval);
    			//soap_call_ns__status(&m_soap, m_server, "", m_clientid, &status);
    			//soap_call_ns__setinput(&m_soap, m_server, "", m_clientid, m_sfoutputs[j], m_sofvalues[j], &status);
				if (m_soap.error)
				{ 
		  			printf("output vvalue handler %s %s\n", name, value);
		  			soap_print_fault(&m_soap, stderr);
		  			exit(1);
				}    			  		
		  		break;
		  	}		  	
		  }//end count over m_noutputs
	}//end check on m_soutputs
}

void output_svalue_handler(DXLConnection *conn, const char *name, const char *value, void *data)
{
   int i=0, j, n, ioutput=-1, noutput;
   char **s,**sval, buf[16];
   char sname[400]="";
   printf("output svalue handler\n");
 	int status=0;

	if(m_ssoutputs  && (m_iupdateserver ==1))
	{
		  for(j=0; j<m_nsoutputs; j++)
		  {
		  	if(strcmp(m_ssoutputs[j], name)==0)
		  	{
		  		sprintf(m_sosvalues[j],"%s", value);

				strncpy(sname,name,strlen(name)-1);
				//sscanf(value,"%f",&dval);
				//printf("actual output svalue handler %s %s\n", sname, value);
				//soap_call_ns__setparamstring(&m_soap, m_server, "", sname,(char *)value, &status );

    			//soap_call_ns__status(&m_soap, m_server, "", m_clientid, &status);
    			//soap_call_ns__setinput(&m_soap, m_server, "", m_clientid, m_sfoutputs[j], m_sofvalues[j], &status);
				if (m_soap.error)
				{ 
		  			printf("output svalue handler\n");
		  			soap_print_fault(&m_soap, stderr);
		  			exit(1);
				}    			  		
		  		break;
		  	}		  	
		  }//end count over m_noutputs
	}//end check on m_soutputs
}

//input value handlers


//input list handlers
void finput_list_handler(DXLConnection *conn, const char *name, const char *value, 
                 void *data)
{
   char *tokenptr, *tp2;
   char **sn, **sv;
   char cvalue[2048];
   
   int i=0, n=0;

	//printf("finput list handler\n");   
	   
	   if(m_infinit==0)
	   {
	   		strcpy(cvalue,value);
	   	   /*tokenize the values string determine number of inputs*/
	   	   tokenptr=strtok((char *)value, "  ,");
	   	   while(tokenptr != NULL)
	   	   {
	   	   	n++;
	   	   	tokenptr=strtok(NULL, "  ,");
	   	   }
	   	   
	   	   if(n>1) n-=2;
	   	   m_nfinputs=n; 
	   	   sn=m_sfinputs=(char **)calloc(n,sizeof(char *));
		   sv=m_sifvalues=(char **)calloc(n,sizeof(char *));
		   for(i=0; i<n; i++)
		   {
		    	sn[i]=(char *)calloc(201,sizeof(char));
		    	sv[i]=(char *)calloc(2048,sizeof(char));
		   }
		   //printf("found %d values in %s\n",n ,cvalue);
		   i=0;		   
	   	   tp2=strtok(cvalue, " ,");
	   	   while(tp2 != NULL)
	   	   {
	   	   	if((n==1) && (i==0))
	   	   		strcpy(sn[i], tp2);
	   	   	
	   	   	if((n>1) && i>0 && i<n+1)
	   	   	{
	   	   		strcpy(sn[i-1], tp2);
	   	   	}
	   	   	i++;
	   	   	
	   	   	tp2=strtok(NULL, " ,");
	   	   }
	   	   	   	   
	   	   /*tokenize value string get each input*/
		   m_infinit=1;
	   }
}


void iinput_list_handler(DXLConnection *conn, const char *name, const char *value, 
                 void *data)
{
   char *tokenptr, *tp2;
   char **sn, **sv;
   char cvalue[2048];
   
   int i=0, n=0;
//printf("iinput list handler\n");
	   
	   
	   if(m_iniinit==0)
	   {
	   		strcpy(cvalue,value);
	   	   /*tokenize the values string determine number of inputs*/
	   	   tokenptr=strtok((char *)value, "  ,");
	   	   while(tokenptr != NULL)
	   	   {
	   	   	n++;
	   	   	tokenptr=strtok(NULL, "  ,");
	   	   }
	   	   
	   	   if(n>1) n-=2;
	   	   m_niinputs=n; 
	   	   sn=m_siinputs=(char **)calloc(n,sizeof(char *));
		   sv=m_siivalues=(char **)calloc(n,sizeof(char *));
		   for(i=0; i<n; i++)
		   {
		    	sn[i]=(char *)calloc(201,sizeof(char));
		    	sv[i]=(char *)calloc(2048,sizeof(char));
		   }
		   //printf("found %d values in %s\n",n ,cvalue);
		   i=0;		   
	   	   tp2=strtok(cvalue, " ,");
	   	   while(tp2 != NULL)
	   	   {
	   	   	if((n==1) && (i==0))
	   	   	{
	   	   		strcpy(sn[i], tp2);
	   	   		//printf("iinput list handler value %d %s %s\n",i,m_siinputs[i],sn[i]);
	   	   	}
	   	   	
	   	   	if((n>1) && i>0 && i<n+1)
	   	   	{
	   	   		strcpy(sn[i-1], tp2);
	   	   		//printf("iinput list handler i-2 value %d %s %s\n",i-2,m_siinputs[i-2],sn[i-2]);
	   	   		
	   	   	}
	   	   	i++;
	   	   	
	   	   	tp2=strtok(NULL, " ,");
	   	   }
	   	   	   	   
	   	   /*tokenize value string get each input*/
		   m_iniinit=1;
	   }
}


void vinput_list_handler(DXLConnection *conn, const char *name, const char *value, 
                 void *data)
{
   char *tokenptr, *tp2;
   char **sn, **sv;
   char cvalue[2048];
   
   int i=0, n=0;

	//printf("vinput list handler\n");   
	   
	   if(m_invinit==0)
	   {
	   		strcpy(cvalue,value);
	   	   /*tokenize the values string determine number of inputs*/
	   	   tokenptr=strtok((char *)value, "  ,");
	   	   while(tokenptr != NULL)
	   	   {
	   	   	n++;
	   	   	tokenptr=strtok(NULL, "  ,");
	   	   }
	   	   
	   	   if(n>1) n-=2;
	   	   m_nvinputs=n; 
	   	   sn=m_svinputs=(char **)calloc(n,sizeof(char *));
		   sv=m_sivvalues=(char **)calloc(n,sizeof(char *));
		   m_ilenvvals=(int *)calloc(n,sizeof(int));
		   for(i=0; i<n; i++)
		   {
		    	sn[i]=(char *)calloc(201,sizeof(char));
		    	sv[i]=(char *)calloc(2048,sizeof(char));
				m_ilenvvals[i]=0;
		   }
		   //printf("found %d values in %s\n",n ,cvalue);
		   i=0;		   
	   	   tp2=strtok(cvalue, " ,");
	   	   while(tp2 != NULL)
	   	   {
	   	   	if((n==1) && (i==0))
	   	   		strcpy(sn[i], tp2);
	   	   	
	   	   	if((n>1) && i>0 && i<n+1)
	   	   	{
	   	   		strcpy(sn[i-1], tp2);
	   	   	}
	   	   	i++;
	   	   	
	   	   	tp2=strtok(NULL, " ,");
	   	   }
	   	   	   	   
	   	   /*tokenize value string get each input*/
		   m_invinit=1;
	   }
}

void sinput_list_handler(DXLConnection *conn, const char *name, const char *value, 
                 void *data)
{
   char *tokenptr, *tp2;
   char **sn, **sv;
   char cvalue[2048];
   
   int i=0, n=0;

	printf("sinput list handler\n");   
	   
	   if(m_insinit==0)
	   {
	   		strcpy(cvalue,value);
	   	   /*tokenize the values string determine number of inputs*/
	   	   tokenptr=strtok((char *)value, "  ,");
	   	   while(tokenptr != NULL)
	   	   {
	   	   	n++;
	   	   	tokenptr=strtok(NULL, "  ,");
	   	   }
	   	   
	   	   if(n>1) n-=2;
	   	   m_nsinputs=n; 
	   	   sn=m_ssinputs=(char **)calloc(n,sizeof(char *));
		   sv=m_sisvalues=(char **)calloc(n,sizeof(char *));
		   for(i=0; i<n; i++)
		   {
		    	sn[i]=(char *)calloc(201,sizeof(char));
		    	sv[i]=(char *)calloc(2048,sizeof(char));
		   }
		   //printf("found %d values in %s\n",n ,cvalue);
		   i=0;		   
	   	   tp2=strtok(cvalue, " ,");
	   	   while(tp2 != NULL)
	   	   {
	   	   	if((n==1) && (i==0))
	   	   		strcpy(sn[i], tp2);
	   	   	
	   	   	if((n>1) && i>0 && i<n+1)
	   	   	{
	   	   		strcpy(sn[i-1], tp2);
	   	   	}
	   	   	i++;
	   	   	
	   	   	tp2=strtok(NULL, " ,");
	   	   }
	   	   	   	   
	   	   /*tokenize value string get each input*/
		   m_insinit=1;
	   }
}
//output list handlers

void foutput_list_handler(DXLConnection *conn, const char *name, const char *value, 
                 void *data)
{
   char *tokenptr, *tp2;
   char **sn, **sv;
   char cvalue[2048];
   
   int i=0, n=0;

	   
	   
	   if(m_outfinit==0)
	   {
	   		strcpy(cvalue,value);
	   	   /*tokenize the values string determine number of inputs*/
	   	   tokenptr=strtok((char *)value, "  ,");
	   	   while(tokenptr != NULL)
	   	   {
	   	   	n++;
	   	   	tokenptr=strtok(NULL, "  ,");
	   	   }
	   	   
	   	   if(n>1) n-=2;
	   	   m_nfoutputs=n;  
	   	   sn=m_sfoutputs=(char **)calloc(n,sizeof(char *));
		   sv=m_sofvalues=(char **)calloc(n,sizeof(char *));
		   for(i=0; i<n; i++)
		   {
		    	sn[i]=(char *)calloc(201,sizeof(char));
		    	sv[i]=(char *)calloc(2048,sizeof(char));
		   }
		   i=0;		   
	   	   tp2=strtok(cvalue, " ,");
	   	   while(tp2 != NULL)
	   	   {
	   	   	if((n==1) && (i==0))
	   	   		strcpy(sn[i], tp2);
	   	   	
	   	   	if((n>1) && i>0 && i<n+1)
	   	   	{
	   	   		strcpy(sn[i-1], tp2);
	   	   	}
	   	   	i++;
	   	   	
	   	   	tp2=strtok(NULL, " ,");
	   	   }
		   for(i=0; i<n; i++)
		   {
	   			DXLSetValueHandler(conn, sn[i], output_fvalue_handler, NULL);
		   }
	   	   /*tokenize value string get each input*/
		   m_outfinit=1;
	   }
}

void ioutput_list_handler(DXLConnection *conn, const char *name, const char *value, 
                 void *data)
{
   char *tokenptr, *tp2;
   char **sn, **sv;
   char cvalue[2048];
   
   int i=0, n=0;

	   
	   
	   if(m_outiinit==0)
	   {
	   		strcpy(cvalue,value);
	   	   /*tokenize the values string determine number of inputs*/
	   	   tokenptr=strtok((char *)value, "  ,");
	   	   while(tokenptr != NULL)
	   	   {
	   	   	n++;
	   	   	tokenptr=strtok(NULL, "  ,");
	   	   }
	   	   
	   	   if(n>1) n-=2;
	   	   m_nioutputs=n;  
	   	   sn=m_sioutputs=(char **)calloc(n,sizeof(char *));
		   sv=m_soivalues=(char **)calloc(n,sizeof(char *));
		   for(i=0; i<n; i++)
		   {
		    	sn[i]=(char *)calloc(201,sizeof(char));
		    	sv[i]=(char *)calloc(2048,sizeof(char));
		   }
		   i=0;		   
	   	   tp2=strtok(cvalue, " ,");
	   	   while(tp2 != NULL)
	   	   {
	   	   	if((n==1) && (i==0))
	   	   	{
	   	   		strcpy(sn[i], tp2);
	   	   		//printf("output ivalue handler %d %s %s\n",i,sn[i],m_sioutputs[i]);
	   	   	}
	   	   	
	   	   	if((n>1) && i>0 && i<n+1)
	   	   	{
	   	   		strcpy(sn[i-1], tp2);
	   	   	    //printf("output ivalue handler %d %s %s\n",i-2,sn[i-2],m_sioutputs[i-2]);
	   	   		
	   	   	}
	   	   	i++;
	   	   	
	   	   	tp2=strtok(NULL, " ,");
	   	   }
	   	   	 for(i=0; i<n; i++)
		   {
	   			DXLSetValueHandler(conn, sn[i], output_ivalue_handler, NULL);
		   }  	   
	   	   /*tokenize value string get each input*/
		   m_outiinit=1;
	   }
}


void voutput_list_handler(DXLConnection *conn, const char *name, const char *value, 
                 void *data)
{
   char *tokenptr, *tp2;
   char **sn, **sv;
   char cvalue[2048];
   
   int i=0, n=0;

	   
	   
	   if(m_outvinit==0)
	   {
	   		strcpy(cvalue,value);
	   	   /*tokenize the values string determine number of inputs*/
	   	   tokenptr=strtok((char *)value, "  ,");
	   	   while(tokenptr != NULL)
	   	   {
	   	   	n++;
	   	   	tokenptr=strtok(NULL, "  ,");
	   	   }
	   	   
	   	   if(n>1) n-=2;
	   	   m_nvoutputs=n;  
	   	   sn=m_svoutputs=(char **)calloc(n,sizeof(char *));
		   sv=m_sovvalues=(char **)calloc(n,sizeof(char *));
		   for(i=0; i<n; i++)
		   {
		    	sn[i]=(char *)calloc(201,sizeof(char));
		    	sv[i]=(char *)calloc(2048,sizeof(char));
		   }
		   i=0;		   
	   	   tp2=strtok(cvalue, " ,");
	   	   while(tp2 != NULL)
	   	   {
	   	   	if((n==1) && (i==0))
	   	   		strcpy(sn[i], tp2);
	   	   	
	   	   	if((n>1) && i>0 && i<n+1)
	   	   	{
	   	   		strcpy(sn[i-1], tp2);
	   	   	}
	   	   	i++;
	   	   	
	   	   	tp2=strtok(NULL, " ,");
	   	   }
	   	   	 for(i=0; i<n; i++)
		   {
	   			DXLSetValueHandler(conn, sn[i], output_vvalue_handler, NULL);
		   }  	   
	   	   /*tokenize value string get each input*/
		   m_outvinit=1;
	   }
}

void soutput_list_handler(DXLConnection *conn, const char *name, const char *value, 
                 void *data)
{
   char *tokenptr, *tp2;
   char **sn, **sv;
   char cvalue[2048];
   
   int i=0, n=0;

	   
	   
	   if(m_outsinit==0)
	   {
	   		strcpy(cvalue,value);
	   	   /*tokenize the values string determine number of inputs*/
	   	   tokenptr=strtok((char *)value, "  ,");
	   	   while(tokenptr != NULL)
	   	   {
	   	   	n++;
	   	   	tokenptr=strtok(NULL, "  ,");
	   	   }
	   	   
	   	   if(n>1) n-=2;
	   	   m_nioutputs=n;  
	   	   sn=m_ssoutputs=(char **)calloc(n,sizeof(char *));
		   sv=m_sosvalues=(char **)calloc(n,sizeof(char *));
		   for(i=0; i<n; i++)
		   {
		    	sn[i]=(char *)calloc(201,sizeof(char));
		    	sv[i]=(char *)calloc(2048,sizeof(char));
		   }
		   i=0;		   
	   	   tp2=strtok(cvalue, " ,");
	   	   while(tp2 != NULL)
	   	   {
	   	   	if((n==1) && (i==0))
	   	   		strcpy(sn[i], tp2);
	   	   	
	   	   	if((n>1) && i>0 && i<n+1)
	   	   	{
	   	   		strcpy(sn[i-1], tp2);
	   	   	}
	   	   	i++;
	   	   	
	   	   	tp2=strtok(NULL, " ,");
	   	   }
	   	   	for(i=0; i<n; i++)
		   {
	   			DXLSetValueHandler(conn, sn[i], output_svalue_handler, NULL);
		   }   	   
	   	   /*tokenize value string get each input*/
		   m_outsinit=1;
	   }
}

void initialise()
{
	
	
}

void initsetvaluehandlers()
{
	int nin=1, nout=2;
	int i,j;
	char **sfin, **sfiv, **sfon, **sfov;

		sfin=m_sfinputs=(char **)calloc(2,sizeof(char *));
		sfiv=m_sifvalues=(char **)calloc(2,sizeof(char *));
		sfon=m_sfoutputs=(char **)calloc(1,sizeof(char *));
		sfov=m_sofvalues=(char **)calloc(1,sizeof(char *));
		
		m_nfinputs=1;
		m_nfoutputs=2;
		
		sfon[0]=(char *)calloc(201,sizeof(char));
		sfov[0]=(char *)calloc(2048,sizeof(char));
		strcpy(sfon[0],"inmaptoplane_max");
		strcpy(sfov[0],"0.0");
		DXLSetValueHandler(conn, sfon[0], output_fvalue_handler, NULL);		


		
		sfin[0]=(char *)calloc(201,sizeof(char));
		sfiv[0]=(char *)calloc(2048,sizeof(char));
		strcpy(sfin[0],"maptoplane_point");
		strcpy(sfiv[0],"[0 0 0]");
		printf("input 0 %s %s \n",sfon[0],sfov[0]);
		sfin[1]=(char *)calloc(201,sizeof(char));
		sfiv[1]=(char *)calloc(2048,sizeof(char));
		strcpy(sfin[1],"file_to_import");
		strcpy(sfiv[1],"temperature");
		printf("input 1 %s %s \n",sfon[1],sfov[1]);
	
	
	
	
}

void *freearrays()
{
	free(m_sfinputs);  
	free(m_sifvalues);
	free(m_sfinputs);  
	free(m_sifvalues);

	return NULL;
}

void *help()
{
	printf("dxwebclient2 help.\n");	
	return NULL;
}

/*client started up specifying name of input .net file and the contact
 * for the server and port
 * 
 * The client will also start a non interactive ssh session
 * using
 *  user must provide a username
 * assumes single sign on is enabled for the remote client
 * 	-X port forwarding
 *  -N don't start a command on a remote machine
 *  -L dxwebserviceport:mydxwebserver:dxwebserviceport
 * 
 * 
 * the above assume user has ssh certs for client machine
 * on the remote server
 * */
 
 /*
  * to start client must provide
  * .net filename
  * user name (on remote server)
  * server contact name
  * client number
  * port (default to 8080)
  * 
  * ./dxwebclient2 filename.net myusername server.org.type.country 8080
  * */
 
main(int argc, char *argv[])
{
    int status=0;
    int pid,i,j;
    char result[100];
    char svalue[2048];
    char outputname[200];
    char soapresp[2000];
    int port=8080;
    char susername[200];
    char shost[200];
    char sshcom[300];
    int isync=1;
    
    if(argc<4)
    {
    	help();
    	exit(1);	    	
    }
    
    
    if(argc>2)
    strcpy(shost,argv[3]);
    
    if(argc>2)
      port=atoi(argv[2]);
      
    sprintf(m_server,"http://%s:%d",shost,port);
    
    
    
    /*sprintf(sshcom,"%s@%s -Y -f -n -q -N -R%d:%s:%d",susername, shost, port, shost, port );      
    printf("%s\n",sshcom);
    
    /*fork process to start ssh tunnel*/
    
    	/*execl("/usr/bin/", "ssh", sshcom, 0);*/
    
    
    /* 
     * Start Data explorer user interface in -edit mode, with certain
     * in -edit mode, with certain menus turned off.
     */
    //conn = DXLStartDX("dx -image -suppress -noExitOptions  -noConnectionMenus",NULL);
    conn = DXLStartDX("dx -image -suppress",NULL);
  	soap_init(&m_soap);


    if (conn == NULL)
    {
	fprintf(stderr,"Could not connect\n");
	perror("DXLStartDX");
	exit(1);
    }

    /* 
     *  Set the handler for the DXLOutput tool which is labelled 
     *  "maptoplane_max"
     */
     /*initialise();*/
     /*initsetvaluehandlers();*/
    /*DXLSetValueHandler(conn, "maptoplane_max", max_handler, NULL);
	DXLSetValueHandler(conn, "image_out", image_handler, NULL);
	DXLSetValueHandler(conn, outputname, output_value_handler, NULL);*/

    DXLSetValueHandler(conn, "float_input_list", finput_list_handler, NULL);
    DXLSetValueHandler(conn, "float_output_list", foutput_list_handler, NULL);

    DXLSetValueHandler(conn, "int_input_list", iinput_list_handler, NULL);
    DXLSetValueHandler(conn, "int_output_list", ioutput_list_handler, NULL);

    DXLSetValueHandler(conn, "string_input_list", sinput_list_handler, NULL);
    DXLSetValueHandler(conn, "string_output_list", soutput_list_handler, NULL);

    DXLSetValueHandler(conn, "vector_input_list", vinput_list_handler, NULL);
    DXLSetValueHandler(conn, "vector_output_list", voutput_list_handler, NULL);

    DXLSetValueHandler(conn, "closedx", closedx_handler, NULL);
    DXLSetValueHandler(conn, "updateserver", updateserver_handler, NULL);
    //DXLSetValueHandler(conn, "savestate", savestate_handler, NULL);
    //DXLSetValueHandler(conn, "loadstate", loadstate_handler, NULL);
    DXLSetValueHandler(conn, "updatelocal", updatelocal_handler, NULL);
    //DXLSetValueHandler(conn, "ihistory", ihistory_handler, NULL);

    /* 
     * Load the visual program to run. Set the value of the DXLInput
     * tool which is labelled "file_to_import".
     * Also set the value of the DXLInput tool which is labelled
     * "maptoplane_point". 
     */
    DXLLoadVisualProgram(conn, argv[1]);
    
    /*Execute once to set inputs and outputs*/
    //DXLExecuteOnce(conn);
    SyncAfterExecute(conn);    
    
    
    
    
    /*DXLSetString(conn, "file_to_import","temperature");*/
    /*DXLSetValue(conn, "file_to_import","temperature");
    DXLSetValue(conn, "maptoplane_point", "[0 5000 5000]");*/
    printf("dx web client started with net file: %s\n",argv[1]);

    
    /*printf("Hit return to continue:");
    gets(result);*/
    #ifndef IO_MSVC
		sleep(0.1);
	#else
        Sleep(0.1);
    #endif
    while(m_iclosedx !=1)
	{
    /*
     * Execute the visual program and check for input from maptoplane_max.
     */
         #ifndef IO_MSVC
		sleep(0.1);
	#else
        Sleep(0.1);
    #endif
     //if(isync==1)
     //{
    //DXLExecuteOnChange(conn);
    //SyncAfterExecute(conn);
    
      if (DXLIsMessagePending(conn))
         DXLHandlePendingMessages(conn);

         if(m_iupdateserver==0)
	{
         	printf("Hit return to continue:");
          	gets(result);
	}
    			DXLExecuteOnce(conn);
			SyncAfterExecute(conn);
    isync=0;
     //}

    /* Change the value for the DXLInput tool labelled "maptoplane_point
     * and execute again.
     */
    /*DXLSetValue(conn, "maptoplane_point", "[10000 5000 5000]");*/
    //DXLExecuteOnce(conn);
    //SyncAfterExecute(conn);
    
    /*get input list from server*/
    
       	
    	//soap_call_ns__status(&m_soap, m_server, "", m_clientid, &status);    	
    	/*printf("svalue=%d\n",status);*/
    	/*status=0;*/
		if (m_soap.error)
		{ 
		//	m_soap.
		  soap_print_fault(&m_soap, stderr);
		  //exit(1);
		}
		
		/*Check the server for any input*/
		
		if(m_iupdatelocal==1)
		{
			isync=1;
			for(i=0; i<m_nfinputs;i++)
			{
				char *sname;
				double dvalue;
				sname=(char *)calloc(strlen(m_sfinputs[i])-1,sizeof(char));
				strncpy(sname,m_sfinputs[i],strlen(m_sfinputs[i])-1);
				soap_call_ns__getparamdouble(&m_soap, m_server, "", m_id,sname, &dvalue );
				sprintf(m_sifvalues[i],"%f",dvalue);
				//soap_call_ns__getinput(&m_soap, m_server, "", m_clientid, m_sfinputs[i], &soapresp);
				printf("finput %d %s value=%f %s %s\n",i,sname,dvalue,m_sfinputs[i], m_sifvalues[i]);
		    	DXLSetScalar(conn, m_sfinputs[i], dvalue);
		    	//DXLExecuteOnChange(conn);
		    	//SyncAfterExecute(conn);
		    	free(sname);
			}
			for(i=0; i<m_niinputs;i++)
			{
				int ivalue;
				char *sname;
				sname=(char *)calloc(strlen(m_siinputs[i])-1,sizeof(char));
				strncpy(sname,m_siinputs[i],strlen(m_siinputs[i])-1);
				soap_call_ns__getparamint(&m_soap, m_server, "",m_id, sname, &ivalue );
				sprintf(m_siivalues[i],"%d",ivalue);
				printf("iinput %d %s %s value=%d\n",i,sname,m_siinputs[i],ivalue);
		    	DXLSetInteger(conn, m_siinputs[i], ivalue);
		    	//DXLExecuteOnChange(conn);
		    	//SyncAfterExecute(conn);
		    	
		    	free(sname);
			}
			for(i=0; i<m_nsinputs;i++)
			{
				char *sname;
				char svalue[2000]="";
				char *ssvalue=svalue;
				sname=(char *)calloc(strlen(m_ssinputs[i])-1,sizeof(char));
				strncpy(sname,m_ssinputs[i],strlen(m_ssinputs[i])-1);
				//soap_call_ns__getparamstring(&m_soap, m_server, "", sname, &ssvalue );
				//sprintf(m_sisvalues[i],"%s",svalue);
				strcpy(m_sisvalues[i],svalue);
				printf("sinput %d %s %s value=%s\n",i,sname,m_ssinputs[i],m_sisvalues[i]);
		    	DXLSetString(conn, m_ssinputs[i], m_sisvalues[i]);
		    	//DXLExecuteOnChange(conn);
		    	//SyncAfterExecute(conn);
		    	
		    	free(sname);
		    	
			}
			for(i=0; i<m_nvinputs;i++)
			{
				char *sname;
				char svalue[8000]="";
				char tsvalue[8000]="";
				int vlen=3;
				double *vval;
				
              
				//compute the length of the vector else assume length 3
				if(m_ilenvvals[i]==0)
						m_ilenvvals[i]=3;
				vval=(double *)calloc(m_ilenvvals[i],sizeof(double));
				struct fdata sdata;
				struct fdata *psdata;
				sdata.__ptr=vval;
				sdata.__size=m_ilenvvals[i];
				psdata=&sdata;
                sname=(char *)calloc(strlen(m_svinputs[i])-1,sizeof(char));
				strncpy(sname,m_svinputs[i],strlen(m_svinputs[i])-1);
				soap_call_ns__getparamvec(&m_soap, m_server, "", m_id,sname,m_ilenvvals[i], &psdata );
				for(j=0; j<m_ilenvvals[i];j++)
					sprintf(tsvalue,"%s %f", tsvalue, psdata->__ptr[j]);
				sprintf(m_sivvalues[i],"[ %s ]",tsvalue);

				printf("vinput %d %s %s value=%f %f %f  as str %s\n",i,sname,m_svinputs[i],psdata->__ptr[0],psdata->__ptr[1],psdata->__ptr[2],m_sivvalues[i]);
				
		    	DXLSetValue(conn, m_svinputs[i], m_sivvalues[i]);
		    	//DXLExecuteOnChange(conn);
		    	//SyncAfterExecute(conn);
		    	
		    	free(sname);
		    	
			}

		}
    	
     	
    
	}
    printf("Client %d Quiting\n", m_clientid);
    /*gets(result);*/
    freearrays();
    DXLExitDX(conn);
}
