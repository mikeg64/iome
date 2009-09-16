#include <stdio.h>
//#include <stream.h>
#include <ctype.h>

#ifndef IO_MSVC
   #include <unistd.h>  //the sleep function
#else

#endif
#include <stdlib.h>
#include <string.h>

#include <Xm/Xm.h>
#include <Xm/MainW.h>
#include <Xm/ToggleBG.h>
#include <Xm/RowColumn.h>
#include <Xm/Frame.h>
#include <Xm/PushB.h>
#include <Xm/CascadeB.h>
#include <Xm/MessageB.h>
#include <Xm/Form.h>
#include <Xm/Text.h>
#include <Xm/LabelG.h>
#include <Xm/PanedW.h>
#include <Xm/DialogS.h>
#include <Xm/PushBG.h>
#include <Xm/FileSB.h>

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



Widget myWindow,myForm, theparent, thebar, theframe,updateserverbutton, updatelocalbutton, thefilebutton,thefilesavebutton,syncdxbutton,theparamupdatebutton, theparamupdatemenu, thefilemenu, thehelpmenu,helpbutton, quitbutton, paramupdatecontrolbutton;
Widget       helpdialog, helppane, helptext_w, helpform, helpsep, helpwidget, helplabel;

Widget playbutton,theplaymenu;
Widget     w,        *cascade_btns,help_dlg;
    int                num_btns;

XtAppContext    app;
/* The following help text information is a continuous stream of characters
** that will all be placed in a single ScrolledText object. If a specific
** newline is desired, you must do that yourself. See "index_help" below.
*/
String context_help[] = {
    "This application is used to demonstrate collaborative visualisation.",
    "and computational steering using IBM data explorer.\n\n",
    "             ",
    "The updateserver button is used to send the current DX control.",
    "outputs to the IOME server.\n\n",
    "             ",
    "The updatelocal button is used to receive the current DX control.",
    "inputs stored on the IOME server.\n\n",  
     "             ",       
    "The file open menu can be used to open a saved configuration and  .",
    "set the current parameters on the IOME server.\n\n",
    
    "             ",
    "The file save menu can be used to save  .",
    "the current parameters on the IOME server.\n\n",

    "             ",
    "The application can be used with any user provide data explorer network file.",
    "The user provide data explorer network file must include DXLInput controls.\n\n",

    "             ",
        NULL};

String window_help[] = {
    "Each of the windows in your application should have an",
    "XmNhelpCallback associated with it so you can monitor when",
    "the user presses the Help key over any particular widget.",
    "This is another way to provide context-sensitive help.",
    "The MenuBar should always have a Help entry at the far right",
    "that provides help for most aspects of the program, including",
    "the user interface. By providing different levels of help",
    "indexing, you can provide multiple stages of help, making the",
    "entire help system easier to use.",
    NULL};

String index_help[] = {
    "This is a small demonstration program, so there is very little",
    "material to provide an index. However, an index should contain",
    "a summary of the type of help available. For example, we have:\n",
    "    Help On Context\n",
    "    Help On Windows\n",
    "    This Index\n",
    "\n",
    "Higher-end applications might also provide a tutorial.",
    NULL};

String *help_texts[] = {context_help, window_help, index_help};




char m_server[200] = "http://localhost:8080/";
struct soap m_soap;

int m_id=0; //id of the simulation we are going to change

int m_iclosedx=0;
int m_iuselocal=1;
int m_iupdateserver=1;

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

static String DefaultResources[] =
{
    "*background:              #b4b4b4b4b4b4",
    "*foreground:              black",
#ifdef sgi
    "*fontList:                 -adobe-helvetica*bold-r*14*=bold\n\
                                -adobe-helvetica*medium-r*14*=normal\n\
                                -adobe-helvetica*medium-o*14*=oblique",
#else
    "*fontList:                 -adobe-helvetica*bold-r*14*=bold\
                                -adobe-helvetica*medium-r*14*=normal\
                                -adobe-helvetica*medium-o*14*=oblique",
#endif
   "*XmToggleButton.selectColor:            CadetBlue",
    "*XmText.shadowThickness:                1",
    NULL
};


long int tog_mousemeth_item_set,tog_mousedim_item_set;




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
		  	//printf("actual out float stuff %s %s\n",m_sfoutputs[j],m_sofvalues[j]);
		  	if(strcmp(m_sfoutputs[j], name)==0)
		  	{
		  		sprintf(m_sofvalues[j],"%s", value);
				strncpy(sname,name,strlen(name)-1);
				dval=atof(value);
				//printf("actual out float stuff %s %f\n",sname,dval);
				soap_call_ns__setparamdouble(&m_soap, m_server, "", m_id,sname,dval, &status );

    			//soap_call_ns__status(&m_soap, m_server, "", m_clientid, &status);
    			//soap_call_ns__setinput(&m_soap, m_server, "", m_clientid, m_sfoutputs[j], m_sofvalues[j], &status);
				if (m_soap.error)
				{ 
		  			printf("output fvalue handler\n");
		  			soap_print_fault(&m_soap, stderr);
		  			//exit(1);
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
		  			//exit(1);
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
				//soap_call_ns__setparamvec(&m_soap, m_server, "", sname,sdata,vsize, &status );
                free(vval);
                free(newval);
                free(snewval);
    			//soap_call_ns__status(&m_soap, m_server, "", m_clientid, &status);
    			//soap_call_ns__setinput(&m_soap, m_server, "", m_clientid, m_sfoutputs[j], m_sofvalues[j], &status);
				if (m_soap.error)
				{ 
		  			printf("output vvalue handler %s %s\n", name, value);
		  			soap_print_fault(&m_soap, stderr);
		  			//exit(1);
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
		  			//exit(1);
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

	printf("finput list handler\n");   
	   
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
printf("iinput list handler\n");
	   
	   
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
	   	   		strcpy(sn[i], tp2);
	   	   	
	   	   	if((n>1) && i>0 && i<n+1)
	   	   	{
	   	   		strcpy(sn[i-1], tp2);
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

	printf("vinput list handler\n");   
	   
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
	   			DXLSetValueHandler(conn, sn[i], output_ivalue_handler, NULL);
		   }  	   
	   	   /*tokenize value string get each input*/
		   m_outfinit=1;
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



void toggled_mousemeth (Widget widget, XtPointer client_data, XtPointer call_data)
{
    long int which = (long int) client_data;
    XmToggleButtonCallbackStruct *state =
                        (XmToggleButtonCallbackStruct *) call_data;
    //printf ("%s: %s\n", XtName (widget),
    //                state->set == XmSET ? "on" : 
    //                state->set == XmOFF ? "off" : "indeterminate");
    if (state->set == XmSET)
        tog_mousemeth_item_set = (int)which;
    else
        tog_mousemeth_item_set = 0;
}

void toggled_mousedim (Widget widget, XtPointer client_data, XtPointer call_data)
{
    long int which = (long int) client_data;
    XmToggleButtonCallbackStruct *state =
                        (XmToggleButtonCallbackStruct *) call_data;
    //printf ("%s: %s\n", XtName (widget),
    //                state->set == XmSET ? "on" : 
    //                state->set == XmOFF ? "off" : "indeterminate");
    if (state->set == XmSET)
        tog_mousedim_item_set = (int)which;
    else
        tog_mousedim_item_set = 0;
}

/* climb widget tree until we get to the top. Return the Shell */
Widget GetTopShell (Widget w)
{
    while (w && !XtIsWMShell (w))
    w = XtParent (w);
    return w;
}

/* The callback function for the "OK" button. Since this is not a 
** predefined Motif dialog, the "widget" parameter is not the dialog
** itself. That is only done by Motif dialog callbacks. Here in the
** real world, the callback routine is called directly by the widget
** that was invoked. Thus, we must pass the dialog as the client
** data to get its handle. (We could get it using GetTopShell(),
** but this way is quicker, since it's immediately available.)
*/
void DestroyShell (Widget widget, XtPointer client_data,
                   XtPointer call_data)
{
    Widget shell = (Widget) client_data;
    XtDestroyWidget (shell);
}



/*Callback for quit button*/
void updateserverbutton_func(Widget w, XtPointer client_data, XtPointer call_data)
{
long item_no = (long) client_data;
    
    printf ("update server Item %d (%s) selected\n", item_no + 1, XtName (w));
			//m_iupdateserver=atoi(value);
			
   
   m_iupdateserver=1;		
   if (DXLIsMessagePending(conn))
         DXLHandlePendingMessages(conn); 
     
     /*Execute once to set inputs and outputs*/
    DXLExecuteOnce(conn);
    //SyncAfterExecute(conn); 
    
    m_iupdateserver=0; 	
   		
   		
}

void updatelocalbutton_func(Widget w, XtPointer client_data, XtPointer call_data)
{
	long item_no = (long) client_data;
	int i,j;
    char *sname;
    
    printf ("updte local Item %d (%s) selected\n", item_no + 1, XtName (w));
    
    
 			for(i=0; i<m_nfinputs;i++)
			{
				char *sname;
				double dvalue;
				sname=(char *)calloc(strlen(m_sfinputs[i])-1,sizeof(char));
				strncpy(sname,m_sfinputs[i],strlen(m_sfinputs[i])-1);
				//printf("finput %d %s value=%f %s %s\n",i,sname,dvalue,m_sfinputs[i], m_sifvalues[i]);

				soap_call_ns__getparamdouble(&m_soap, m_server, "", m_id,sname, &dvalue );
				sprintf(m_sifvalues[i],"%f",dvalue);
				//soap_call_ns__getinput(&m_soap, m_server, "", m_clientid, m_sfinputs[i], &soapresp);
				//printf("finput %d %s value=%f %s %s\n",i,sname,dvalue,m_sfinputs[i], m_sifvalues[i]);
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
				soap_call_ns__getparamint(&m_soap, m_server, "", m_id,sname, &ivalue );
				sprintf(m_siivalues[i],"%d",ivalue);
				//printf("iinput %d %s %s value=%d\n",i,sname,m_siinputs[i],ivalue);
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
				//printf("sinput %d %s %s value=%s\n",i,sname,m_ssinputs[i],m_sisvalues[i]);
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

				//printf("vinput %d %s %s value=%f %f %f  as str %s\n",i,sname,m_svinputs[i],psdata->__ptr[0],psdata->__ptr[1],psdata->__ptr[2],m_sivvalues[i]);
				
		    	DXLSetValue(conn, m_svinputs[i], m_sivvalues[i]);
		    	//DXLExecuteOnChange(conn);
		    	//SyncAfterExecute(conn);
		    	
		    	free(sname);
		    	
			}
    

}



void quitbutton_func(Widget w, XtPointer client_data, XtPointer call_data)
{
	printf("Quit button selected, terminating program.");
	
	exit(0);		
}

void widgetcancel_cb(Widget w, XtPointer client_data, XtPointer call_data)
{
 XtUnmanageChild(w);
 //XtDestroyWidget (w);	
}

void loadsimulation_cb (Widget w, XtPointer client_data, XtPointer call_data)
{
    char *filename;
    XmFileSelectionBoxCallbackStruct *cbs =
                        (XmFileSelectionBoxCallbackStruct *) call_data;

    filename = (char *) XmStringUnparse (cbs->value,
                                         XmFONTLIST_DEFAULT_TAG,
                                         XmCHARSET_TEXT,
                                         XmCHARSET_TEXT,
                                         NULL, 0, XmOUTPUT_ALL);
    if (!filename)
        /* must have been an internal error */
        return;
    if (!*filename) {
        /* nothing typed? */
        puts ("No file selected.");
        /* even "" is an allocated byte */
        XtFree (filename);
        return;
    }
    printf ("Load Filename given: \"%s\"\n", filename);
    
   			string sresult="";
			ifstream infile;
			ostringstream oss (ostringstream::out);
			infile.open (filename, ifstream::in);
			while (infile.good())
				oss << (char) infile.get();
			sresult=oss.str();
			infile.close(); 
		int status;	
    soap_call_ns__readsimulation(&m_soap, m_server, "",  m_id,(char *)sresult.c_str(), &status);
    
    XtFree (filename);
	
}

void savesimulation_cb (Widget w, XtPointer client_data, XtPointer call_data)
{
    char *filename;
    
	char content[400];
	char *scont;
    scont=content;
		char *scontent;

	scontent=(char *)calloc(5000,sizeof(char));
    
    XmFileSelectionBoxCallbackStruct *cbs =
                        (XmFileSelectionBoxCallbackStruct *) call_data;

    filename = (char *) XmStringUnparse (cbs->value,
                                         XmFONTLIST_DEFAULT_TAG,
                                         XmCHARSET_TEXT,
                                         XmCHARSET_TEXT,
                                         NULL, 0, XmOUTPUT_ALL);
    if (!filename)
        /* must have been an internal error */
        return;
    if (!*filename) {
        /* nothing typed? */
        puts ("No file selected.");
        /* even "" is an allocated byte */
        XtFree (filename);
        return;
    }
    printf ("Save Filename given: \"%s\"\n", filename);
    
    soap_call_ns__writesimulation(&m_soap, m_server, "",  m_id,"simxmlfile.xml", &scontent);
    
			string sresult="";
			ofstream outfile;
			outfile.open (filename, ofstream::out);
			outfile << scontent;
			outfile.close();

    
    
    
    XtFree (filename);
	
}


void fileopen_cb(Widget w, XtPointer client_data, XtPointer call_data)
{
	Widget dialog, remove;
	XmString mask;
	Arg args[1];
	
	/*Create file selection dalog*/
	mask=XmStringCreateLocalized("*.xml");
	XtSetArg(args[0], XmNdirMask, mask);
	printf ("Creating fs dialog\n");
	dialog=XmCreateFileSelectionDialog(w, "select", args, 1);
	
	//remove=XmSelectionBoxGetChild(dialog, XmDIALOG_HELP_BUTTON);
	//XtUnmanageChild(remove);
	
	XtAddCallback(dialog, XmNokCallback,loadsimulation_cb,NULL);
	XtAddCallback(dialog, XmNcancelCallback,widgetcancel_cb,NULL);
	
	XtManageChild(dialog);
	XtPopup(XtParent(dialog), XtGrabNone);
}

void filesave_cb(Widget w, XtPointer client_data, XtPointer call_data)
{
	Widget dialog, remove;
	XmString mask;
	Arg args[1];
	
	/*Create file selection dalog*/
	mask=XmStringCreateLocalized("*.xml");
	XtSetArg(args[0], XmNdirMask, mask);
	printf ("Creating fs dialog\n");
	dialog=XmCreateFileSelectionDialog(w, "select", args, 1);
	
	//remove=XmSelectionBoxGetChild(dialog, XmDIALOG_HELP_BUTTON);
	//XtUnmanageChild(remove);
	
	XtAddCallback(dialog, XmNokCallback,savesimulation_cb,NULL);
	XtAddCallback(dialog, XmNcancelCallback,widgetcancel_cb,NULL);
	
	XtManageChild(dialog);
	XtPopup(XtParent(dialog), XtGrabNone);
}


/* callback for all the entries in the File pulldown menu. */
void file_cb (Widget w, XtPointer client_data, XtPointer call_data)
{
    long item_no = (long) client_data;
 
	
    if (item_no == 2)
        /* the Quit menu button */
        exit (0);

    printf ("Item %d (%s) selected\n", item_no + 1, XtName (w));
    
  
    
}



/* callback for all the entries in the File pulldown menu. */
void play_cb (Widget w, XtPointer client_data, XtPointer call_data)
{
    long item_no = (long) client_data;
    if (item_no == 2)
        /* the Quit menu button */
        exit (0);
    printf ("Item %d (%s) selected\n", item_no + 1, XtName (w));
}




void syncdx_cb (Widget w, XtPointer client_data, XtPointer call_data)
{
    if (DXLIsMessagePending(conn))
         DXLHandlePendingMessages(conn); 
     
     /*Execute once to set inputs and outputs*/
    DXLExecuteOnce(conn);
    //SyncAfterExecute(conn);    	
}



void help_cb (Widget w, XtPointer client_data, XtPointer call_data)
{
    void         DestroyShell(Widget, XtPointer, XtPointer);
	//Pixel        fg, bg;
	//Pixmap       pixmap;

    Arg          args[10];
    int          n = 0;
    int          i;
    char         *p, buf[BUFSIZ];
    //int          item_no = *((int *) client_data); 
    Dimension    h=200;
    

    
    
    /* Set up a DialogShell as a popup window. Set the delete
    ** window protocol response to XmDESTROY to make sure that
    ** the window goes away appropriately. Otherwise, it's XmUNMAP
    ** which means it'd be lost forever, since we're not storing
    ** the widget globally or statically to this function. 
    */
    i = 0;
    
    XtSetArg (args[i], XmNdeleteResponse, XmDESTROY); 
    i++;
    XtSetArg (args[i], XmNwidth, 600); 
    i++;
    XtSetArg (args[i], XmNheight, 400); 
    i++;
    //helpdialog = XmCreateDialogShell ( GetTopShell(w), "Help", args, i);
    helpdialog = XmCreateDialogShell ( GetTopShell(w), "Help",args, i);
                 
    /* Create a PanedWindow to manage the stuff in this dialog. */
    /* PanedWindow won't let us set these to 0! */
    i=0;
    XtSetArg (args[i], XmNsashWidth, 1);  
    i++;  
    /* Make small so user doesn't try to resize */ 
    XtSetArg (args[i], XmNsashHeight, 1);
    i++;    
    helppane = XmCreatePanedWindow (helpdialog, "pane", args, 2);
    /* Create a RowColumn in the form for Label and Text widgets.
    ** This is the control area. 
    */
    helpform = XmCreateForm (helppane, "form1", NULL, 0);
    //XtVaGetValues (form, /* once created, we can get its colors */
    //               XmNforeground, &fg,
    //               XmNbackground, &bg,
     //              NULL);
    /* create the pixmap of the appropriate depth using the colors 
    ** that will be used by the parent (form). 
    */
    /*pixmap = XCreatePixmapFromBitmapData (XtDisplay (form),
    RootWindowOfScreen (XtScreen (form)),
                        (char *) info_bits, info_width, info_height,
                        fg, bg,
                        DefaultDepthOfScreen (XtScreen (form)));*/
    /* Create a label gadget using this pixmap */
    //i = 0;
    //XtSetArg (args[n], XmNlabelType,        XmPIXMAP);      n++;
    //XtSetArg (args[n], XmNlabelPixmap,      pixmap);        n++;
    
    //XtSetArg (args[i], XmNleftAttachment,   XmATTACH_FORM); i++;
    //XtSetArg (args[i], XmNtopAttachment,    XmATTACH_FORM); i++;
    //XtSetArg (args[i], XmNbottomAttachment, XmATTACH_FORM); i++;
    //helplabel = XmCreateLabelGadget (helpform, "label", args, n);
    //XtManageChild (helplabel); 
    /* prepare the text for display in the ScrolledText object 
    ** we are about to create. 
    */
    for (p = buf, i = 0; help_texts[0][i]; i++) {
        p += strlen (strcpy (p, help_texts[0][i]));
        if (!isspace (p[-1]))
        /* spaces, tabs and newlines are spaces. */
            *p++ = ' '; /* lines are concatenated together, insert space */
    }
    *--p = 0; /* get rid of trailing space... */
    n = 0;
    XtSetArg (args[n], XmNscrollVertical,        True);              n++;
    XtSetArg (args[n], XmNscrollHorizontal,      False);             n++;
    XtSetArg (args[n], XmNeditMode,              XmMULTI_LINE_EDIT); n++;
    XtSetArg (args[n], XmNeditable,              False);             n++;
    XtSetArg (args[n], XmNcursorPositionVisible, False);             n++;
    XtSetArg (args[n], XmNwordWrap,              True);              n++;
    XtSetArg (args[n], XmNvalue,                 buf);               n++;
    XtSetArg (args[n], XmNrows,                  10);                 n++;
    helptext_w = XmCreateScrolledText (helpform, "help_text", args, n);
    /* Attachment values must be set on the Text widget's PARENT, 
    ** the ScrolledWindow. This is the object that is positioned. 
    */ 
    XtVaSetValues (XtParent (helptext_w),
                   XmNleftAttachment,   XmATTACH_WIDGET,
                   XmNleftWidget,       helplabel,
                   XmNtopAttachment,    XmATTACH_FORM,
                   XmNrightAttachment,  XmATTACH_FORM,
                   XmNbottomAttachment, XmATTACH_FORM,
                   NULL);
    XtManageChild (helptext_w);
    XtManageChild (helpform);
    /* Create another form to act as the action area for the dialog */
    XtSetArg (args[0], XmNfractionBase, 5);
    helpform = XmCreateForm (helppane, "form2", args, 1);
    /* The OK button is under the pane's separator and is 
    ** attached to the left edge of the form. It spreads from
    ** position 0 to 1 along the bottom (the form is split into 
    ** 5 separate grids via XmNfractionBase upon creation). 
    */
    helpwidget = XmCreatePushButtonGadget (helpform, "OK", NULL, 0);
    XtVaSetValues (helpwidget,
                   XmNtopAttachment,                XmATTACH_FORM,  
                   XmNbottomAttachment,             XmATTACH_FORM,   
                   XmNleftAttachment,               XmATTACH_POSITION,  
                   XmNleftPosition,                 1, 
                   XmNrightAttachment,              XmATTACH_POSITION, 
                   XmNrightPosition,                2, 
                   XmNshowAsDefault,                True,
                   XmNdefaultButtonShadowThickness, 1,
                   NULL);
    XtManageChild (helpwidget);
    XtAddCallback (helpwidget, XmNactivateCallback, DestroyShell,
                   (XtPointer) helpdialog);
    /* This is created with its XmNsensitive resource set to False 
    ** because we don't support "more" help. However, this is the 
    ** place to attach it to if there were any more. 
    */
    helpwidget = XmCreatePushButtonGadget (helpform, "More", NULL, 0);
    XtVaSetValues (helpwidget,
                   XmNsensitive,                    False, 
                   XmNtopAttachment,                XmATTACH_FORM,
                   XmNbottomAttachment,             XmATTACH_FORM,
                   XmNleftAttachment,               XmATTACH_POSITION,
                   XmNleftPosition,                 3,
                   XmNrightAttachment,              XmATTACH_POSITION,
                   XmNrightPosition,                4,
                   XmNshowAsDefault,                False,
                   XmNdefaultButtonShadowThickness, 1,
                   NULL);
    //XtManageChild (helpwidget);
    /* Fix the action area pane to its current height -- never let it resize */
    XtManageChild (helpform);
    XtVaGetValues (helpwidget, XmNheight, &h, NULL);
    XtVaSetValues (helpform, XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);
    /* This also pops up the dialog, as it is the child of a DialogShell */
    XtManageChild (helppane);
}

void paramupdate_cb (Widget w, XtPointer client_data, XtPointer call_data)
{
    Widget       help_dialog, pane, text_w, form, sep, widget, label;
    Widget         mm_radio_box, mmtrans, mmrot, mmsca, mmoff;
    Widget         form2,md_radio_box, mdxy, mdyz, mdxz;
    
    void         DestroyShell(Widget, XtPointer, XtPointer);
	//Pixel        fg, bg;
	//Pixmap       pixmap;

    Arg          args[10];
    int          n = 0;
    int          i;
    char         *p, buf[BUFSIZ];
    int          item_no = *((int *) client_data); 
    Dimension    h;
    /* Set up a DialogShell as a popup window. Set the delete
    ** window protocol response to XmDESTROY to make sure that
    ** the window goes away appropriately. Otherwise, it's XmUNMAP
    ** which means it'd be lost forever, since we're not storing
    ** the widget globally or statically to this function. 
    */
    i = 0;
    XtSetArg (args[i], XmNdeleteResponse, XmDESTROY); 
    i++;
    help_dialog = XmCreateDialogShell ( GetTopShell(w), "ParamUpdateControl", args, i);

    /* Create a PanedWindow to manage the stuff in this dialog. */
    /* PanedWindow won't let us set these to 0! */
    XtSetArg (args[0], XmNsashWidth, 1);    
    /* Make small so user doesn't try to resize */ 
    XtSetArg (args[1], XmNsashHeight, 1);    
    pane = XmCreatePanedWindow (help_dialog, "pane", args, 2);
    /* Create a RowColumn in the form for Label and Text widgets.
    ** This is the control area. 
    */
    form = XmCreateForm (pane, "form1", NULL, 0);
    form2 = XmCreateForm (pane, "form2", NULL, 0);
    //XtVaGetValues (form, /* once created, we can get its colors */
    //               XmNforeground, &fg,
    //               XmNbackground, &bg,
     //              NULL);
    /* create the pixmap of the appropriate depth using the colors 
    ** that will be used by the parent (form). 
    */
    /*pixmap = XCreatePixmapFromBitmapData (XtDisplay (form),
    RootWindowOfScreen (XtScreen (form)),
                        (char *) info_bits, info_width, info_height,
                        fg, bg,
                        DefaultDepthOfScreen (XtScreen (form)));*/
    /* Create a label gadget using this pixmap */
    n = 0;
    //XtSetArg (args[n], XmNlabelType,        XmPIXMAP);      n++;
    //XtSetArg (args[n], XmNlabelPixmap,      pixmap);        n++;
    XtSetArg (args[n], XmNleftAttachment,   XmATTACH_FORM); n++;
    XtSetArg (args[n], XmNtopAttachment,    XmATTACH_FORM); n++;
    XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
    label = XmCreateLabelGadget (form, "label", args, n);
    XtManageChild (label); 
    /* prepare the text for display in the ScrolledText object 
    ** we are about to create. 
    */
    for (p = buf, i = 0; help_texts[item_no][i]; i++) {
        p += strlen (strcpy (p, help_texts[item_no][i]));
        if (!isspace (p[-1]))
        /* spaces, tabs and newlines are spaces. */
            *p++ = ' '; /* lines are concatenated together, insert space */
    }
    *--p = 0; /* get rid of trailing space... */
    n = 0;
    XtSetArg (args[n], XmNscrollVertical,        True);              n++;
    XtSetArg (args[n], XmNscrollHorizontal,      False);             n++;
    XtSetArg (args[n], XmNeditMode,              XmMULTI_LINE_EDIT); n++;
    XtSetArg (args[n], XmNeditable,              False);             n++;
    XtSetArg (args[n], XmNcursorPositionVisible, False);             n++;
    XtSetArg (args[n], XmNwordWrap,              True);              n++;
    XtSetArg (args[n], XmNvalue,                 buf);               n++;
    XtSetArg (args[n], XmNrows,                  5);                 n++;
 
 mm_radio_box = XmCreateRadioBox (form, "Mouse method radio_box", NULL, 0);

    mmtrans = XmCreateToggleButtonGadget (mm_radio_box, "Translation", NULL, 0);
    XtAddCallback (mmtrans, XmNvalueChangedCallback, toggled_mousemeth, (XtPointer) 1);
    XtManageChild (mmtrans);

    mmrot = XmCreateToggleButtonGadget (mm_radio_box, "Rotation", NULL, 0);
    XtAddCallback (mmrot, XmNvalueChangedCallback, toggled_mousemeth, (XtPointer) 2);
    XtManageChild (mmrot);

    mmsca = XmCreateToggleButtonGadget (mm_radio_box, "Scale", NULL, 0);
    XtAddCallback (mmsca, XmNvalueChangedCallback, toggled_mousemeth, (XtPointer) 3);
    XtManageChild (mmsca);

    mmoff = XmCreateToggleButtonGadget (mm_radio_box, "Off", NULL, 0);
    XtAddCallback (mmoff, XmNvalueChangedCallback, toggled_mousemeth, (XtPointer) 4);
    XtManageChild (mmoff);


    XtManageChild (mm_radio_box);
    

md_radio_box = XmCreateRadioBox (form2, "Mouse Dimension radio_box", NULL, 0);

    mdxy = XmCreateToggleButtonGadget (md_radio_box, "xy", NULL, 0);
    XtAddCallback (mdxy, XmNvalueChangedCallback, toggled_mousedim, (XtPointer) 1);
    XtManageChild (mdxy);

    mdyz = XmCreateToggleButtonGadget (md_radio_box, "yx", NULL, 0);
    XtAddCallback (mdyz, XmNvalueChangedCallback, toggled_mousedim, (XtPointer) 2);
    XtManageChild (mdyz);

    mdxz = XmCreateToggleButtonGadget (md_radio_box, "xz", NULL, 0);
    XtAddCallback (mdxz, XmNvalueChangedCallback, toggled_mousedim, (XtPointer) 3);
    XtManageChild (mdxz);



    XtManageChild (md_radio_box);
 
 
    
    XtManageChild (form);
    XtManageChild (form2);
    
    
    
    
    /* Create another form to act as the action area for the dialog */
    XtSetArg (args[0], XmNfractionBase, 5);
    form = XmCreateForm (pane, "form2", args, 1);
    /* The OK button is under the pane's separator and is 
    ** attached to the left edge of the form. It spreads from
    ** position 0 to 1 along the bottom (the form is split into 
    ** 5 separate grids via XmNfractionBase upon creation). 
    */
    widget = XmCreatePushButtonGadget (form, "OK", NULL, 0);
    XtVaSetValues (widget,
                   XmNtopAttachment,                XmATTACH_FORM,  
                   XmNbottomAttachment,             XmATTACH_FORM,   
                   XmNleftAttachment,               XmATTACH_POSITION,  
                   XmNleftPosition,                 1, 
                   XmNrightAttachment,              XmATTACH_POSITION, 
                   XmNrightPosition,                2, 
                   XmNshowAsDefault,                True,
                   XmNdefaultButtonShadowThickness, 1,
                   NULL);
    XtManageChild (widget);
    XtAddCallback (widget, XmNactivateCallback, DestroyShell,
                   (XtPointer) help_dialog);
    /* This is created with its XmNsensitive resource set to False 
    ** because we don't support "more" help. However, this is the 
    ** place to attach it to if there were any more. 
    */
    widget = XmCreatePushButtonGadget (form, "More", NULL, 0);
    XtVaSetValues (widget,
                   XmNsensitive,                    False, 
                   XmNtopAttachment,                XmATTACH_FORM,
                   XmNbottomAttachment,             XmATTACH_FORM,
                   XmNleftAttachment,               XmATTACH_POSITION,
                   XmNleftPosition,                 3,
                   XmNrightAttachment,              XmATTACH_POSITION,
                   XmNrightPosition,                4,
                   XmNshowAsDefault,                False,
                   XmNdefaultButtonShadowThickness, 1,
                   NULL);
    XtManageChild (widget);
    /* Fix the action area pane to its current height -- never let it resize */
    XtManageChild (form);
    XtVaGetValues (widget, XmNheight, &h, NULL);
    XtVaSetValues (form, XmNpaneMaximum, h, XmNpaneMinimum, h, NULL);
    /* This also pops up the dialog, as it is the child of a DialogShell */
    XtManageChild (pane);
}



/* callback for all the entries in the File pulldown menu. */
void help_menu_cb (Widget w, XtPointer client_data, XtPointer call_data)
{
    long item_no = (long) client_data;
    if (item_no == 1)
        /* the Quit menu button */
        help_cb(w, client_data, call_data);
    printf ("Item %d (%s) selected\n", item_no + 1, XtName (w));
}



void
setUpGraphics(void) {

   XmString           str1, str2, str3,str4,str5,str6;
   Arg wargs[15];
  int n;
   
   
   XtSetLanguageProc (NULL, NULL, NULL);

   
   
    
   if (myWindow == NULL) {
     cerr << "myWindow is null. bye!\n";
     exit(1); 
   }

   
myForm = XtVaCreateManagedWidget("form",
                 xmFormWidgetClass, myWindow,
                 XmNwidth,    350,
                 XmNheight,   50,
                 XmNfractionBase, 5,
                 NULL);





//myForm = XmCreateForm(myWindow, "form", wargs, n);
  //XtManageChild(myForm);
  
    n = 0;
  XtSetArg(wargs[n], XtNx, 30); 
  n++;
  XtSetArg(wargs[n], XtNy, 30); 
  n++;
  XtSetArg(wargs[n], XmNbottomAttachment, XmATTACH_FORM); 
  n++;
  XtSetArg(wargs[n], XmNleftAttachment, XmATTACH_FORM); 
  n++;
  XtSetArg(wargs[n], XmNrightAttachment, XmATTACH_FORM); 
  n++;
  XtSetArg(wargs[n], XmNtopAttachment, XmATTACH_FORM); 
  n++;
  XtSetArg(wargs[n], XmNleftOffset, 30); 
  n++;
  XtSetArg(wargs[n], XmNbottomOffset, 30); 
  n++;
  XtSetArg(wargs[n], XmNrightOffset, 30); 
  n++;
  XtSetArg(wargs[n], XmNtopOffset, 30); 
  n++;
  //theframe = XmCreateFrame (myForm, "frame", wargs, n);
  //XtManageChild (theframe);
  
  
  
  
  
    //myForm = XtCreateWidget("Form", xmFormWidgetClass, myWindow, NULL, 0);

    str1 = XmStringCreateLocalized ("File");
    str4 = XmStringCreateLocalized ("Help");
    str2 = XmStringCreateLocalized ("Update");
    str3 = XmStringCreateLocalized ("Play");
str5 = XmStringCreateLocalized ("updateserver");
str6 = XmStringCreateLocalized ("updatelocal");
    thebar = XmVaCreateSimpleMenuBar (myForm, "MenuBar",
                                       XmVaCASCADEBUTTON, str1, 'F',
					XmVaCASCADEBUTTON, str4, 'H',
                                       NULL);
 
 	XmStringFree (str1);
    XmStringFree (str2);
    XmStringFree (str3); 
    XmStringFree (str4);
XmStringFree (str5); 
    XmStringFree (str6);  
    /* create the "File" pulldown menu -- callback is file_cb() */
    str1 = XmStringCreateLocalized ("New");
    str2 = XmStringCreateLocalized ("Open");
    str3 = XmStringCreateLocalized ("Quit");
    thefilemenu=XmVaCreateSimplePulldownMenu (thebar, "file_menu", 0, file_cb, 
                                    NULL);
    XmStringFree (str1);
    XmStringFree (str2);
    XmStringFree (str3);
    thefilebutton=XtVaCreateManagedWidget("Open", xmPushButtonWidgetClass, thefilemenu, NULL);
    thefilesavebutton=XtVaCreateManagedWidget("Save", xmPushButtonWidgetClass, thefilemenu, NULL);
    syncdxbutton=XtVaCreateManagedWidget("ExecuteDX", xmPushButtonWidgetClass, thefilemenu, NULL);    
        
   	quitbutton=XtVaCreateManagedWidget("Quit", xmPushButtonWidgetClass, thefilemenu, NULL);
    
    
       	updateserverbutton=XtVaCreateManagedWidget("updateserver", xmPushButtonWidgetClass, thebar, NULL);
   	updatelocalbutton=XtVaCreateManagedWidget("updatelocal", xmPushButtonWidgetClass, thebar, NULL);

    str1 = XmStringCreateLocalized ("ReadConfig");
    str2 = XmStringCreateLocalized ("PlayFileList");
    str3 = XmStringCreateLocalized ("VideoFileList");
    str4 = XmStringCreateLocalized ("SaveViewImage");
    
    /*theplaymenu=XmVaCreateSimplePulldownMenu (thebar, "play_menu", 1, play_cb, 
                                  XmVaPUSHBUTTON, str1, 'R', NULL, NULL, 
                                  XmVaPUSHBUTTON, str2, 'P', NULL, NULL,
                                  XmVaPUSHBUTTON, str3, 'V', NULL, NULL,
                                 XmVaPUSHBUTTON, str4, 'S', NULL, NULL,
                                  NULL);*/
    XmStringFree (str1);
    XmStringFree (str2);
    XmStringFree (str3);    
    XmStringFree (str4);    
    
    
    
    /* create the "Help" menu -- callback is help_cb() */
    str1 = XmStringCreateLocalized ("On Context");
    str2 = XmStringCreateLocalized ("On Window");
    str3 = XmStringCreateLocalized ("Index");
    thehelpmenu = XmVaCreateSimplePulldownMenu (thebar, "Help", 1, help_menu_cb,
                                      NULL);
    XmStringFree (str1);
    XmStringFree (str2);
    XmStringFree (str3);

    
    
    /* Identify the Help Menu for the MenuBar */
    XtVaGetValues (thebar, XmNchildren, &cascade_btns, XmNnumChildren, 
                    &num_btns, NULL);
    XtVaSetValues (thebar, XmNmenuHelpWidget, cascade_btns[num_btns-1], 
                   NULL);

    XtManageChild(thebar);
    //theframe=XtVaCreateManagedWidget("theframe", xmFrameWidgetClass, myForm, NULL);
   	
   	//thefilebutton=XtVaCreateManagedWidget("thefilebutton",xmCascadeButtonWidgetClass,thebar,NULL);
   	//theviewbutton=XtVaCreateManagedWidget("theviewbutton",xmCascadeButtonWidgetClass,thebar,NULL);
   	
   	//thefilemenu=XmCreatePulldownMenu(thebar, "file", NULL, 0);
   	//theviewmenu=XmCreatePulldownMenu(thebar, "view", NULL, 0);
   	//playbutton=XtVaCreateManagedWidget("playbutton", xmPushButtonWidgetClass, theplaymenu, NULL);
   	helpbutton=XtVaCreateManagedWidget("helpbutton", xmPushButtonWidgetClass, thehelpmenu, NULL);
    
 


   	//XtVaSetValues(thefilebutton, XmNsubMenuId, thefilemenu, NULL);
   	//XtVaSetValues(thehelpbutton, XmNsubMenuId, thehelpmenu, NULL);   	
   	XtAddCallback(quitbutton, XmNactivateCallback, quitbutton_func, 0);
   	XtAddCallback(helpbutton, XmNactivateCallback, help_cb, 0);
   	
   	XtAddCallback(thefilebutton, XmNactivateCallback, fileopen_cb, 0);
   	XtAddCallback(thefilesavebutton, XmNactivateCallback, filesave_cb, 0);
   	XtAddCallback(syncdxbutton, XmNactivateCallback, syncdx_cb, 0);
   	
	XtAddCallback(updateserverbutton, XmNactivateCallback, updateserverbutton_func, 0);
   	XtAddCallback(updatelocalbutton, XmNactivateCallback, updatelocalbutton_func, 0);
     
 
 
   
   // Set up viewer:
   //myViewer = new SoXtExaminerViewer(myWindow);
   //myViewer = new SoXtExaminerViewer(theframe);
   //myViewer->setDrawStyle(SoXtViewer::STILL, SoXtViewer::VIEW_LINE);
   //myViewer->setSize(SbVec2s(600, 450)); 
   //myViewer->setTitle("SimViewer");
   //myViewer->setTransparencyType(SoGLRenderAction::DELAYED_ADD);
   //myViewer->setSceneGraph(root);
   //myViewer->setHeadlight(TRUE);
   
   	//XmMainWindowSetAreas(myWindow,myForm, theframe,  NULL, NULL, NULL);

 
   //myViewer->show();
   
  
   XtManageChild (theframe);

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
    
    myWindow = XtVaAppInitialize (&app, "Demos", 
                                 NULL, 0, &argc, argv, 
                                 DefaultResources, NULL);
                                 
    setUpGraphics();
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

    /*DXLSetValueHandler(conn, "closedx", closedx_handler, NULL);
    DXLSetValueHandler(conn, "updateserver", updateserver_handler, NULL);
    //DXLSetValueHandler(conn, "savestate", savestate_handler, NULL);
    //DXLSetValueHandler(conn, "loadstate", loadstate_handler, NULL);
    DXLSetValueHandler(conn, "uselocal", uselocal_handler, NULL);*/
    //DXLSetValueHandler(conn, "ihistory", ihistory_handler, NULL);

    /* 
     * Load the visual program to run. Set the value of the DXLInput
     * tool which is labelled "file_to_import".
     * Also set the value of the DXLInput tool which is labelled
     * "maptoplane_point". 
     */
    DXLLoadVisualProgram(conn, argv[1]);
    
    /*Execute once to set inputs and outputs*/
    DXLExecuteOnce(conn);
    SyncAfterExecute(conn);    
    
    
    
    
    /*DXLSetString(conn, "file_to_import","temperature");*/
    /*DXLSetValue(conn, "file_to_import","temperature");
    DXLSetValue(conn, "maptoplane_point", "[0 5000 5000]");*/
    printf("dx web client started with net file: %s\n",argv[1]);
    
    XtRealizeWidget(myWindow); /* instantiate it now */
    XtAppMainLoop (app);
    

    printf("Client %d Quiting\n", m_clientid);
    /*gets(result);*/
    freearrays();
    DXLExitDX(conn);
}
