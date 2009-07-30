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
#include "IoSimulationSteerTest.h"


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
      	//jobscript jobname appxsl port numtasks numsubprocs numprocs procid
    		if(argc>11)
				InitIOME(argv[2],argv[3],argv[4],atoi(argv[5]),argv[6],atoi(argv[7]),atoi(argv[8]),atoi(argv[9]),atoi(argv[10]),atoi(argv[11]));                
     		if(argc>10)
				InitIOME(argv[2],argv[3],argv[4],atoi(argv[5]),argv[6],atoi(argv[7]),atoi(argv[8]),atoi(argv[9]),atoi(argv[10]),0);                
     		if(argc>9)
				InitIOME(argv[2],argv[3],argv[4],atoi(argv[5]),argv[6],atoi(argv[7]),atoi(argv[8]),atoi(argv[9]),1,0);                
     		if(argc>8)
				InitIOME(argv[2],argv[3],argv[4],atoi(argv[5]),argv[6],atoi(argv[7]),atoi(argv[8]),1,1,0);                
     		if(argc>7)
				InitIOME(argv[2],argv[3],argv[4],atoi(argv[5]),argv[6],atoi(argv[7]),1,1,1,0);
			else if(argc>6)
				InitIOME(argv[2],argv[3],argv[4],atoi(argv[5]),argv[6],10,1,1,1,0);
			else if(argc>5)
				InitIOME(argv[2],argv[3],argv[4],atoi(argv[5]),"localhost",10,1,1,1,0);
			else if(argc>4)
				InitIOME(argv[2],argv[3],argv[4],8080,"localhost",10,1,1,1,0);
			else if(argc>3)
				InitIOME(argv[2],argv[3],"null",8080,"localhost",10,1,1,1,0);    	

    	}
		else if(strcmp("runsimulation",method)==0)
    	{
			status=RunSimulation(argc,argv);
		}
		else if(strcmp("submitsimulation",method)==0)
    	{
			status=SubmitSimulation(argc,argv);
		}
		else if(strcmp("requestsimulation",method)==0)
    	{
			status=RequestSimulation(argc,argv);
		}
		else if(strcmp("runrequestedsimulation",method)==0)
    	{
			status=RunRequestedSimulation(argc,argv);
		}
		else if(strcmp("simulationstatus",method)==0)
    	{
			status=SimulationStatus(argc,argv);
		}
		else if(strcmp("setsimulationstatus",method)==0)
    	{
			status=SetSimulationStatus(argc,argv);
		}
		else if(strcmp("getsimulationresults",method)==0)
    	{
			status=GetSimulationResults(argc,argv);
		}
		else if(strcmp("deletesimulation",method)==0)
    	{
			status=DeleteSimulation(argc,argv);
		}
		else if(strcmp("runsimulationstep",method)==0)
    	{
			status=RunSimulationStep(argc,argv);
		}
		else if(strcmp("getobjnum",method)==0)
    	{
			status=GetProcID(argc,argv);
		}
		else if(strcmp("getnumobj",method)==0)
    	{
			status=GetNumProcs(argc,argv);
		}
		else if(strcmp("setmetadata",method)==0)
    		status=SetMetadata(argc,argv);
    	else if(strcmp("createsimulation",method)==0)
				status=CreateSimulation(argc,argv);
    	else if(strcmp("newsimulation",method)==0)
				status=NewSimulation(argc,argv);
    	else if(strcmp("writesimulation",method)==0)
				status=WriteSimulation(argc,argv);
    	else if(strcmp("readsimulation",method)==0)
				status=ReadSimulation(argc,argv);
		else if(strcmp("writelocalsimulation",method)==0)
				status=WriteLocalSimulation(argc,argv);
    	else if(strcmp("readlocalsimulation",method)==0)
				status=ReadLocalSimulation(argc,argv);
    	/*else if(strcmp("writeconfig",method)==0)
				status=WriteConfig(argc,argv);
    	else if(strcmp("readconfig",method)==0)
				status=ReadConfig(argc,argv);
    	else if(strcmp("writestate",method)==0)
				status=WriteState(argc,argv);
    	else if(strcmp("readstate",method)==0)
					status=ReadState(argc,argv);*/
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
  		else if(strcmp("groupbarrier",method)==0)
		{
				status=GroupBarrier(argc, argv);
		}
    else if(strcmp("add",method)==0)
	{
			
				int port=atoi(argv[4]);
			        double result=0;
                                double val1=atof(argv[2]);
			         double val2=atof(argv[3]);
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			
			

			soap_call_ns__add(&m_soapclient, m_serverclient, "", val1 , val2, &result );
                         printf("Result is %f\n",result);

			if (m_soapclient.error)
			  { soap_print_fault(&m_soapclient, stderr);
			    exit(1);
			  }
	}
else if(strcmp("getstep",method)==0)
	{
			
				int port=atoi(argv[3]);
			        int result=0;
                     int id= atoi(argv[2]);         
				sprintf(m_serverclient,"%s:%d",argv[4],port);
			
			

			soap_call_ns__getstep(&m_soapclient, m_serverclient, "", id, &result );
                         printf("%f",result);

			if (m_soapclient.error)
			  { soap_print_fault(&m_soapclient, stderr);
			    exit(1);
			  }
	}
	else if(strcmp("getnsteps",method)==0)
	{
			
				int port=atoi(argv[3]);
				 int id=  atoi(argv[2]);  
			        int result=0;
                                
				sprintf(m_serverclient,"%s:%d",argv[4],port);
			
			

			soap_call_ns__getnsteps(&m_soapclient, m_serverclient, "", id, &result );
                         printf("%f",result);

			if (m_soapclient.error)
			  { soap_print_fault(&m_soapclient, stderr);
			    exit(1);
			  }
	}
else if(strcmp("setstep",method)==0)
	{
			 int id=  atoi(argv[3]);  
				int step=atoi(argv[2]);
				int port=atoi(argv[4]);
			        int result=0;
                                
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			
			

			soap_call_ns__setstep(&m_soapclient, m_serverclient, "", id,step, &result );
                         printf("%d",result);

			if (m_soapclient.error)
			  { soap_print_fault(&m_soapclient, stderr);
			    exit(1);
			  }
	}
	else if(strcmp("setnsteps",method)==0)
	{
			
				int steps=atoi(argv[2]);
				int port=atoi(argv[4]);
				 int id=  atoi(argv[3]);  
			        int result=0;
                                
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			
			

			soap_call_ns__setnsteps(&m_soapclient, m_serverclient, "", id,steps, &result );
                         printf("%f",result);

			if (m_soapclient.error)
			  { soap_print_fault(&m_soapclient, stderr);
			    exit(1);
			  }
	}
	 if(strcmp("deleteparam",method)==0)
    	{
				int port=atoi(argv[4]);
			        int result=0;
					char *paramname=argv[2];
                     int id=atoi(argv[3]);           
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			
			

			soap_call_ns__deleteparam(&m_soapclient, m_serverclient, "",paramname,id, &result );
                         printf("%d\n",result);

			if (m_soapclient.error)
			  { soap_print_fault(&m_soapclient, stderr);
			    exit(1);
			  }
		}
	 if(strcmp("listparam",method)==0)
    	{
				int port;
				if(argc>4)
				   port=atoi(argv[4]);
				else port=8080;

			        char  *result;
					result=(char *)calloc(5000,sizeof(char));
					result="\0";
					char *paramtype=argv[2];
					int id;
					if(argc>3)
                         id=atoi(argv[3]);
					else
						id=0;

					if(argc>5)
						sprintf(m_serverclient,"%s:%d",argv[5],port);
					else
						sprintf(m_serverclient,"%s:%d","localhost",port);
			
			

			soap_call_ns__listparam(&m_soapclient, m_serverclient, "",paramtype,id, &result );
                         printf("%s\n",result);

			//if (m_soapclient.error)
			//  { soap_print_fault(&m_soapclient, stderr);
			//    exit(1);
			//  }

			  free(result);
		}
	 if(strcmp("deletemetadata",method)==0)
    	{
				int port=atoi(argv[4]);
			        int result=0;
					char *name=argv[2];
                     int id=atoi(argv[3]);           
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			
			

			soap_call_ns__deletemetadata(&m_soapclient, m_serverclient, "",id,name, &result );
                         printf("%d\n",result);

			if (m_soapclient.error)
			  { soap_print_fault(&m_soapclient, stderr);
			    exit(1);
			  }
		}
	 if(strcmp("listmetadata",method)==0)
    	{
				int port;
				if(argc>3)
				   port=atoi(argv[3]);
				else port=8080;

			        char  *result;
					result=(char *)calloc(5000,sizeof(char));
					result="\0";
					
					int id;
					if(argc>2)
                         id=atoi(argv[2]);
					else
						id=0;

					if(argc>4)
						sprintf(m_serverclient,"%s:%d",argv[4],port);
					else
						sprintf(m_serverclient,"%s:%d","localhost",port);
			
			

			soap_call_ns__listmetadata(&m_soapclient, m_serverclient, "",id, &result );
                         printf("%s\n",result);

			//if (m_soapclient.error)
			//  { soap_print_fault(&m_soapclient, stderr);
			//    exit(1);
			//  }

			  free(result);
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

int InitIOME(char *scriptname, char *simname, char *simxslfile, int port , char *hostname="localhost", int maxsims=10, int numtasks=1,int numsubprocs=1, int numprocs=1, int procid=0)
//int InitIOME(char *simname, char *simxslfile, char *simfilename, char *statefilename, char *configfilename, int port, int istandalone)
{
	int status=0;
	pthread_t simtid;
	//pthread_t *scitid;
	string sserver;
	struct soap *tsoap;
    pthread_t tid;
	int j;
	int m, s; /* master and slave sockets */
    //int port=8080;
	struct soap soap;
	
	
	int finished=0;
 	CIoGenericSteerSimulation *LocalSimulation=NULL;
    m_maxsims=maxsims;
	int i;

 	standalone=1;
	//enable all of the services (default setting)
    for(i=0;i<49;i++)
		m_wsflags[i]=1;

	char *siogscfgfile="iogs.config";
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


	if(TestSimulation = (CIoGenericSteerSimulation *)new CIoGenericSteerSimulation)
	{	
		if(simxslfile)
			if((strlen(simxslfile)>0)  && (strcmp(simxslfile,"NULL") !=0) && (strcmp(simxslfile,"null") !=0))
				TestSimulation->SetSimXSLFileName(simxslfile);
		
		TestSimulation->SetSimName(simname);
		TestSimulation->SetStateFileName("statefile.xml");
		TestSimulation->SetConfigFileName("configfile.xml");		
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
		m_port=port;
        sprintf(svar,"%d",port);
		sprintf(m_serverclient,"%s:%d",hostname,port);
		strcpy(m_hostname,hostname);
		sprintf(simportfile,"%s%d_port.txt",simname,procid);
        fstream filestr;
		filestr.open (simportfile, fstream::out );
        filestr<<svar<<" "<<hostname; 
		filestr.close();
		printf("INIT IOME has started listening on port %d\n",port);
		//TestSimulation->AddNode(port,"localhost");

		int ret;
		#ifndef IO_MSVC
			//ret = putenv(svar);
		#else
			//ret = _putenv(svar);
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
				//all nodes set
			}
			else
			{
				sserver="localhost";
				TestSimulation->AddNode(port,sserver,numsubprocs);
				for(j=0;j<numsubprocs;j++)
						TestSimulation->AddJob(0,j);

			}
		}




		simdataarray=(struct simdata *)calloc(numsubprocs+m_maxsims, sizeof(struct simdata ));
		for(int j=0; j<(numsubprocs+m_maxsims); j++)
		{
			simdataarray[j].simptr=NULL;
			simdataarray[j].isimid=-1;
			simdataarray[j].status=-1;
			simdataarray[j].userid=NULL;
		}


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
				LocalSimulation->m_iprocid=procid;

				LocalSimulation->SetStateFileName("statefile.xml");
				LocalSimulation->SetConfigFileName("configfile.xml");		

				//TestSimulation->SetStateFileName(statefilename);
				//TestSimulation->SetConfigFileName(configfilename);

				if(simxslfile)
					if((strlen(simxslfile)>0)  && (strcmp(simxslfile,"NULL") !=0) && (strcmp(simxslfile,"null") !=0))
						LocalSimulation->SetSimXSLFileName(simxslfile);
				
				simdataarray[j].simptr=LocalSimulation;
				simdataarray[j].isimid=j;
				simdataarray[j].status=0;
				//simdataarray[j].sscript=scriptname;
				simdataarray[j].sscript=(char *)calloc(1+strlen(scriptname),sizeof(char));
				strcpy(simdataarray[j].sscript,scriptname);
				
				//does not currently start off work one option is for user to specify
				//a script or executable to start job
				//in the case of a null script file no thread is started
				if((scriptname != NULL) && (strlen(scriptname)>0) && (strcmp(scriptname,"null") !=0) && (strcmp(scriptname,"NULL") !=0))
						pthread_create(&(simdataarray[j].tid), NULL, (void*(*)(void*))runscript, (void*)LocalSimulation);
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
					//    	s = soap_accept(&soap);
		    	// copy soap environment and spawn thread
		      	//tsoap = soap_copy(&soap);
		      	//pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)tsoap);
		    	    
		      /*fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);*/
		      //if (s < 0)
		      //{ soap_print_fault(&soap, stderr);
		      //  exit(-1);
		      //} 
		      //soap_serve(&soap);
			  //soap_destroy(&soap);
			  //soap_end(&soap);

		}
		 pthread_cancel(tid);
		soap_done(&soap);
		printf("INIT IOME has finished\n");
		      //soap_destroy(&soap);
		 //  }
		//}
			//TestSimulation->RunSimulation();
		//delete TestSimulation;
				
	}

	return status;

}


int NewSimulation( int argc, char **argv)
{
	int newjobid=0;
	int port=8080;
	char *servername="";
	char *simname="";
	char *xslname="";
	char *content="";
	char *sservername="";
	int id=0;



    		if(argc>5)
			{
				simname=argv[2];
				xslname=argv[3];
				id=atoi(argv[4]);
				port=atoi(argv[5]);
				sservername=argv[6];
			}
			else if(argc>4)
			{
				simname=argv[2];
				xslname=argv[3];
				id=atoi(argv[4]);
				port=atoi(argv[5]);
				sservername="localhost";
			}
			else if(argc>3)
			{
				simname=argv[2];
				xslname=argv[3];
				id=atoi(argv[4]);
				port=8080;
				sservername="localhost";
			}
			else if(argc>2)
			{
				simname=argv[2];
				xslname=argv[3];
				id=0;
				port=8080;
				sservername="localhost";
			}
			else
			{
				simname="simulation";
				xslname="";
				port=8080;
				sservername="localhost";
			}







    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns__newsimulation(&m_soapclient, m_serverclient, "", id,simname,xslname, &newjobid);


	return newjobid;
}




int ExitIOME(int argc, char **argv)
{
	int status=0;
	int id=0;
	int port;

	if(argc>2)
		id=atoi(argv[2]);

	if(argc>3)
		port=atoi(argv[3]);
	else
		port=8080;

	if(argc>4)
		sprintf(m_serverclient,"%s:%d",argv[4],port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);

	soap_call_ns__exitiome(&m_soapclient, m_serverclient, "",id, &status);

	return status;
}


int ns__add(struct soap *soap, double a, double b, double *result)
{ *result = a + b;
   printf("hello\n");
  return SOAP_OK;
} 


void *runscript(void *simulation)
{ 
	pthread_detach(pthread_self());
    char startscript[200]="";
    //startscilab+=getenv("SCILAB_HOME");

	struct simdata *lsimdat=(struct simdata *)simulation;
	string sscript=lsimdat->sscript;
    

    //system( "WScilex.exe" );

	//Run the model
	int pid,status,procstatus=0;
        


	//unix/linux/cygwin process call
	#ifndef IO_MSVC
	sprintf(startscript,"%s",sscript.c_str());
		system(startscript);
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

	sprintf(startscript,"%s",sscript.c_str());
    		system( startscript);
		//system( startscilab.c_str() );
		//pid=_spawnv(_P_NOWAIT, path, args);
		//if(pid != -1)
		//	_cwait(&status, pid, _WAIT_CHILD);
		
	#endif	




	//m_isimfinished=1;
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
			   	  chdir("..");
			#else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir("..");
			#endif	
		}
		catch(int j)
		{
			printf("run simulation thread caught exception\n");
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
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
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
			    if((TestSimulation->m_inumprocs==1) && (id <(m_numsubprocs+MAXNUMSIMS)))
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
		if((numsims < m_numsubprocs+MAXNUMSIMS) )
		{
	
			if((standalone==1) && (numsims>MAXNUMTHREADS))
				return SOAP_OK;
	
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
			   		mkdir(jobdir.c_str(),0755);
					sprintf(command,"cp iogenericsim.sh %s/iogenericsim.sh",jobdir.c_str());
					system(command);
			   		chdir(jobdir.c_str());
				#else
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
			   	  chdir("..");
			   	  string sdelcommand="/bin/rm -rf ";
			   	  sdelcommand.append(jobdir);
			   	  system(sdelcommand.c_str());
			#else
			   	  remove("*");
			   	  _chdir("..");
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
	
	int iisimid;
	int status=0;

    if(m_wsflags[IDns__submitsimulation]==1)
	{
	try
	{
	if((numsims < m_numsubprocs+MAXNUMSIMS) )
	{

		if((standalone==1) && (numsims>MAXNUMTHREADS))
			return SOAP_OK;

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
			   	  mkdir(jobdir.c_str(),0755);
				  sprintf(command,"cp iogenericsim.sh %s/iogenericsim.sh",jobdir.c_str());
				  system(command);
			   	  chdir(jobdir.c_str());
			#else
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

		simdataarray[simid].dir=(char *)calloc(strlen(jobdir.c_str()),sizeof(char));
		strcpy(simdataarray[simid].dir,jobdir.c_str());

		isimid=&(simdataarray[simid].isimid);
		pthread_create(&simdataarray[simid].tid, NULL, (void*(*)(void*))runsimulation, (void*)&simid);
		printf("Job submitted id=%d status=1  dir=%s  threadid=%d numjobs=%d \n",simid,simdataarray[simid].dir,simdataarray[simid].tid,numsims);

			   	#ifndef IO_MSVC
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir("..");
			   	#else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir("..");
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

		if((standalone==1) && (numsims>MAXNUMTHREADS))
			return SOAP_OK;

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
			   	  mkdir(jobdir.c_str(),0755);
				  sprintf(command,"cp iogenericsim.sh %s/iogenericsim.sh",jobdir.c_str());
				  system(command);
			   	  chdir(jobdir.c_str());
			#else
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
			   	  chdir("..");
			   	#else
			   	  //_mkdir(jobdir.c_str());

			   	  _chdir("..");
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
	int status=0;
    if(m_wsflags[IDns__runrequestedsimulation]==1)
	{
    try
    {
	if((numsims <= m_maxsims) && (isimid <= numsims))
	{
		if((standalone==1) && (numsims>MAXNUMTHREADS))
			return SOAP_OK;

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
			   	  chdir(jobdir.c_str());
	    #else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir(jobdir.c_str());
		#endif
        
        
		//isimid=&(simdataarray[isimid].isimid);
		pthread_create(&simdataarray[isimid].tid, NULL, (void*(*)(void*))runsimulation, (void*)&isimid);
		printf("Job runrequested id=%d status=1  dir=%s  threadid=%d numjobs=%d \n",isimid,simdataarray[isimid].dir,simdataarray[isimid].tid,numsims);

        #ifndef IO_MSVC
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir("..");
	    #else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir("..");
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
			   	  //mkdir(jobdir.c_str(),0755);
			   	  chdir("..");
			#else
			   	  //_mkdir(jobdir.c_str());
			   	  _chdir("..");
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
		*status=simdataarray[isimid].status;

		pthread_cancel(simdataarray[isimid].tid);
		simdataarray[isimid].isimid=-1;
		simdataarray[isimid].simptr=NULL;
		simdataarray[isimid].status=-1;
		simdataarray[isimid].userid=NULL;
		//simdataarray[isimid].tid=0;



		numsims--;
		if(/*(standalone!=1 ) && */(LocalTestSimulation != NULL))
			delete LocalTestSimulation;
			
		#ifndef IO_MSVC
			   	  
			   	  string sdelcommand="/bin/rm -rf ";
			   	  sdelcommand.append(sjobdir);
			   	  system(sdelcommand.c_str());
				  chdir("..");
				  rmdir(sjobdir.c_str());
			#else
			   	  remove("*");
			   	  _chdir("..");
			   	  _rmdir(sjobdir.c_str());
			#endif

		   pthread_cancel(simdataarray[isimid].tid);

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


//client calls
int GroupBarrier( int argc, char **argv)
{
	int status=0;
	int testnotcomplete=1;
	int i;
	int numobj;
	int myid;
	int newstate;
	int *iprocstate;
	int state;
	int port;


	if(argc>2)
		myid=atoi(argv[2]);

	if(argc>3)
		port=atoi(argv[3]);
	else
		port=8080;

	if(argc>4)
		sprintf(m_serverclient,"%s:%d",argv[4],port);
	else
		sprintf(m_serverclient,"%s:%d","localhost",port);

	//get num objects in my group
	soap_call_ns__getnumobj(&m_soapclient, m_serverclient, "", 0, &numobj );
	soap_call_ns__getobjnum(&m_soapclient, m_serverclient, "", 0, &myid );


	if(numobj>1)
	{
		iprocstate=(int *)calloc(numobj,sizeof(int));
		for(i=0; i<numobj;i++)
			iprocstate[i]=0;
		//this process has already reached the barrier get my id and set the barrier 
		soap_call_ns__setgroupbarrier(&m_soapclient, m_serverclient, "", myid, 1, &newstate );
		iprocstate[myid]=1;


		//test for processorcs which have arrived at the barrier
		//test only those which have not yet reached the barrier
		while(testnotcomplete==1)
		{
			testnotcomplete=0;
			for(i=0; i<numobj; i++)
			{
				if(iprocstate[i]==0)
				{
					soap_call_ns__testgroupbarrier(&m_soapclient, m_serverclient, "", i, &state );
					if(state==0)
						testnotcomplete=1;
					else
						iprocstate[i]=1;
				}
			}
		}

		free(iprocstate);
		//reset the barrier
		soap_call_ns__setgroupbarrier(&m_soapclient, m_serverclient, "", myid, 0, &newstate );	
	}
	
	return status;
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


int AddParam(int itype, int argc, char **argv)
{
	int status=0;
	int isize;
	double *darray;
	int port;
	char *name;
	int iflag;
	int id=0;
	name=argv[3];

	switch(itype)
	{

	case 0:

		if(argc>=4)
		{
			double dvalue=(double)atof(argv[4]);
			iflag=atoi(argv[5]);
			if(argc>6)
				id=atoi(argv[6]);

			if(argc>7)
				port=atoi(argv[7]);
			else
				port=8080;

			if(argc>8)
				sprintf(m_serverclient,"%s:%d",argv[8],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns__addparamdouble(&m_soapclient, m_serverclient, "", id,name, dvalue, iflag, &status );
		}
		else
			status=1;
		
		break;
	case 1:
		int dint;
		//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, (int *)data );
		if(argc>=4)
		{
			int dvalue=atoi(argv[4]);
			iflag=atoi(argv[5]);
			if(argc>6)
				id=atoi(argv[6]);

			if(argc>7)
				port=atoi(argv[7]);
			else
				port=8080;

			if(argc>8)
				sprintf(m_serverclient,"%s:%d",argv[8],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", id, name, dvalue, iflag, &status );
		}
		else
			status=1;		

		break;
	case 2:
		isize=1;
		darray=(double *)calloc(isize,sizeof(double));
		//soap_call_ns__addparamvec(&m_soapclient, m_serverclient, "", name, size,(double **)data );
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
				id=atoi(argv[7]);

			if(argc>8)
				port=atoi(argv[8]);
			else
				port=8080;

			if(argc>9)
				sprintf(m_serverclient,"%s:%d",argv[9],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			struct fdata thedata;
			thedata.__ptr=data;
			thedata.__size=size;
			soap_call_ns__addparamvec(&m_soapclient, m_serverclient, "", id, name, thedata,size,iflag,&status );
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
				id=atoi(argv[8]);

			if(argc>9)
				port=atoi(argv[9]);
			else
				port=8080;

			if(argc>10)
				sprintf(m_serverclient,"%s:%d",argv[10],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			struct fdata thedata;
			thedata.__ptr=data;
			thedata.__size=nr*nc;

			//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", id, name, thedata,nr,nc,iflag,&status );
		}
		else
			status=1;

		//	soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, data,nr,nc,iflag,(int *)status );		
		//soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );			
		//free(darray);

		break;
	case 4:
			if(argc>=4)
		{
			char*dvalue=(char *)(argv[4]);
			iflag=atoi(argv[5]);

			if(argc>6)
				id=atoi(argv[6]);

			if(argc>7)
				port=atoi(argv[7]);
			else
				port=8080;

			if(argc>8)
				sprintf(m_serverclient,"%s:%d",argv[8],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns__addparamstring(&m_soapclient, m_serverclient, "", id, name, dvalue, iflag, &status );
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
				id=atoi(argv[11]);

			if(argc>12)
				port=atoi(argv[12]);
			else
				port=8080;

			if(argc>13)
				sprintf(m_serverclient,"%s:%d",argv[13],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			struct fdata thedata;
			thedata.__ptr=data;
			thedata.__size=n*p*q*nr*nc;


			//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns__addparammmat3d(&m_soapclient, m_serverclient, "", id, name, thedata,n,p,q,nr,nc,iflag,&status );
		}
		else
			status=1;

		//	soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, data,nr,nc,iflag,(int *)status );		
		//soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );			
		//free(darray);


		//soap_call_ns__addparammmat3d(&m_soapclient, m_serverclient, "", name,size, &dmmat3d );
		//free(darray);

		break;

	}
	
			if (m_soapclient.error)
			  { soap_print_fault(&m_soapclient, stderr);
			    exit(1);
			  }

	return status;
}


int AddMetadata( int argc, char **argv)
{
	int status=0;
	int port=atoi(argv[3]);
	char *content;
	char *name;
	int id=0;

	if(argc>2)
	{
			content=argv[3];
			name=argv[2];
			sprintf(m_serverclient,"%s:%d","localhost",port);
			if(argc>4)
				id=atoi(argv[4]);


			if(argc>5)
				port=atoi(argv[5]);
			else
				port=8080;

			if(argc>6)
				sprintf(m_serverclient,"%s:%d",argv[6],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

			soap_call_ns__addmetadata(&m_soapclient, m_serverclient, "", id, name, content, &status);
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
	int id=0;
	name=argv[3];
char *dvalue=(char *)calloc(500,sizeof(char));
strcpy(dvalue,"junkjunkjunk");
	switch(itype)
	{
	case 0:
		{
			double dvalue=0;
			if(argc>4)
				id=atoi(argv[4]);

			if(argc>5)
				port=atoi(argv[5]);
			else
				port=8080;

			if(argc>6)
				sprintf(m_serverclient,"%s:%d",argv[6],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			soap_call_ns__getparamdouble(&m_soapclient, m_serverclient, "", id, name, &dvalue );
			//print the value
			printf("%f\n",dvalue);
		}
		break;
	case 1:
		{
		//int dint;
			int dvalue=0;
			if(argc>4)
				id=atoi(argv[4]);

			if(argc>5)
				port=atoi(argv[5]);
			else
				port=8080;

			if(argc>6)
				sprintf(m_serverclient,"%s:%d",argv[6],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			soap_call_ns__getparamint(&m_soapclient, m_serverclient, "", id, name, &dvalue );
			//print the value
			printf("%d",dvalue);
		}

		break;
	case 2:
		{
		isize=1;
		//soap_call_ns__addparamvec(&m_soapclient, m_serverclient, "", name, size,(double **)data );
					int dvalue=0;

			if(argc>3)
			{
				isize=atoi(argv[4]);
				darray=(double *)calloc(isize,sizeof(double));

				if(argc>5)
						id=atoi(argv[5]);


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
					//fval.__size=isize;
					soap_call_ns__getparamvec(&m_soapclient, m_serverclient, "", id, name,isize, &fval );
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
						id=atoi(argv[6]);


				if(argc>7)
						port=atoi(argv[7]);
					else
						port=8080;

					if(argc>8)
						sprintf(m_serverclient,"%s:%d",argv[8],port);
					else
						sprintf(m_serverclient,"%s:%d","localhost",port);
					

					struct fdata *fval;
					fval=(struct fdata *)malloc(sizeof(struct fdata));
					(*fval).__ptr=(double *)malloc(isize*sizeof(double));

					//soap_call_ns__getparamvec(&m_soapclient, m_serverclient, "", name,isize, &darray );
					soap_call_ns__getparammat(&m_soapclient, m_serverclient, "", id, name, nr,nc,&fval );
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
		
		//soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );
			
		//free(darray);
		}

		break;
	case 4:
		isize=1;
		//darray=(double *)calloc(isize,sizeof(double));

		//soap_call_ns__addparamstring(&m_soapclient, m_serverclient, "", name,(char **)data );
		//free(darray);
				{
		//int dint;
			//char *dvalue;
			
			//char dvalue[500];
			//char **strptr=&dvalue;
			if(argc>4)
				id=atoi(argv[4]);

					
			if(argc>5)
				port=atoi(argv[5]);
			else
				port=8080;

			if(argc>6)
				sprintf(m_serverclient,"%s:%d",argv[6],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			soap_call_ns__getparamstring(&m_soapclient, m_serverclient, "", id, name, &dvalue );
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
						id=atoi(argv[9]);


				if(argc>10)
						port=atoi(argv[10]);
					else
						port=8080;

					if(argc>11)
						sprintf(m_serverclient,"%s:%d",argv[11],port);
					else
						sprintf(m_serverclient,"%s:%d","localhost",port);
							//soap_call_ns__addparammmat3d(&m_soapclient, m_serverclient, "", name,size, &dmmat3d );
					struct fdata *fval;
					fval=(struct fdata *)malloc(sizeof(struct fdata));
					(*fval).__ptr=(double *)malloc(n*p*q*nr*nc*sizeof(double));

					//soap_call_ns__getparamvec(&m_soapclient, m_serverclient, "", name,isize, &darray );
					soap_call_ns__getparammmat3d(&m_soapclient, m_serverclient, "", id, name, n,p,q,nr,nc,&fval );
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
		
		//soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );
			
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
				id=atoi(argv[3]);


			if(argc>4)
				port=atoi(argv[4]);
			else
				port=8080;

			if(argc>5)
				sprintf(m_serverclient,"%s:%d",argv[5],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

			soap_call_ns__getmetadata(&m_soapclient, m_serverclient, "", id, name, &scont);
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
    int id=0;

	switch(itype)
	{

	case 0:

		if(argc>4)
		{
			double dvalue=atof(argv[4]);
			if(argc>5)
				id=atoi(argv[5]);

			if(argc>6)
				port=atoi(argv[6]);
			else
				port=8080;

			if(argc>7)
				sprintf(m_serverclient,"%s:%d",argv[7],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns__setparamdouble(&m_soapclient, m_serverclient, "", id, name, dvalue, &status );
		}
		else
			status=1;
		
		break;
	case 1:
		int dint;
		//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, (int *)data );
		if(argc>4)
		{
			int dvalue=atoi(argv[4]);
			if(argc>5)
				id=atoi(argv[5]);


			if(argc>6)
				port=atoi(argv[6]);
			else
				port=8080;

			if(argc>7)
				sprintf(m_serverclient,"%s:%d",argv[7],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns__setparamint(&m_soapclient, m_serverclient, "", id, name, dvalue, &status );
		}
		else
			status=1;		

		break;
	case 2:
		isize=1;
		darray=(double *)calloc(isize,sizeof(double));
		//soap_call_ns__addparamvec(&m_soapclient, m_serverclient, "", name, size,(double **)data );
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
				id=atoi(argv[6]);

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
			sdata.__size=size;
			//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns__setparamvec(&m_soapclient, m_serverclient, "", id, name, sdata,size,&status );
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
				id=atoi(argv[7]);

			if(argc>8)
				port=atoi(argv[8]);
			else
				port=8080;

			if(argc>9)
				sprintf(m_serverclient,"%s:%d",argv[9],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			struct fdata sdata;
			sdata.__ptr=data;
			sdata.__size=nr*nc;

			//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns__setparammat(&m_soapclient, m_serverclient, "", id, name, sdata,nr,nc,&status );
		}
		else
			status=1;

		//	soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, data,nr,nc,iflag,(int *)status );		
		//soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );			
		//free(darray);

		break;
	case 4:
			if(argc>4)
		{
			char*dvalue=(char *)(argv[4]);
			if(argc>5)
				id=atoi(argv[5]);

			if(argc>6)
				port=atoi(argv[6]);
			else
				port=8080;

			if(argc>7)
				sprintf(m_serverclient,"%s:%d",argv[7],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			

			soap_call_ns__setparamstring(&m_soapclient, m_serverclient, "", id, name, dvalue, &status );
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
				id=atoi(argv[10]);

			if(argc>11)
				port=atoi(argv[11]);
			else
				port=8080;

			if(argc>12)
				sprintf(m_serverclient,"%s:%d",argv[12],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);
			
			struct fdata sdata;
			sdata.__ptr=data;
			sdata.__size=n*p*q*nr*nc;

			//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
			soap_call_ns__setparammmat3d(&m_soapclient, m_serverclient, "", id, name, sdata,n,p,q,nr,nc,&status );
		}
		else
			status=1;

		//	soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, data,nr,nc,iflag,(int *)status );		
		//soap_call_ns__addparammat(&m_soapclient, m_serverclient, "", name, size,(double **)data );			
		//free(darray);


		//soap_call_ns__addparammmat3d(&m_soapclient, m_serverclient, "", name,size, &dmmat3d );
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
				id=atoi(argv[4]);


			if(argc>5)
				port=atoi(argv[5]);
			else
				port=8080;

			if(argc>6)
				sprintf(m_serverclient,"%s:%d",argv[6],port);
			else
				sprintf(m_serverclient,"%s:%d","localhost",port);

			soap_call_ns__setmetadata(&m_soapclient, m_serverclient, "", id, name, content, &status);
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
	int id=0;

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
			id=atoi(argv[4]);
	}

	if(argc>4 && (argv[5]!=NULL))
	{
          port=atoi(argv[5]);

		if(argc>5 && (argv[6]!=NULL))
					sservername=argv[6];

 	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns__createsimulation(&m_soapclient, m_serverclient, "", id, filename, &status);

	//call create simulation

	return status;
}


int RunSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername="";
	char *input="";
	char *content="";
    char *infile="";
	char *outfile="";
	char *sservername="";
	char *sresults="";
	char *sin=NULL;
	int id=0;
	string simfilecontent;

	if(argc>1 && (argv[2]!=NULL))
					infile=argv[2];
	

	if(argc>2 && (argv[3]!=NULL))
					outfile=argv[3];
	else 
		content="outfile.xml";

	if(argc>3 && (argv[4]!=NULL))
	{
          id=atoi(argv[4]);
	}

	if(argc>4 && (argv[5]!=NULL))
	{
          port=atoi(argv[5]);

		if(argc>5 && (argv[6]!=NULL))
					sservername=argv[6];

 	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);

	if(strcmp(infile,"")!=0)
	{
			string sinput="";
			string sline="";
			FILE *inf;
			if((inf=fopen(infile,"r")) != NULL )
			{
			char c;
			do
			{
				c=fgetc(inf);
				sline=c;
				if(c != EOF)
				 sinput.append(sline);
			}
			while(c != EOF);
			}
			fclose(inf);
			sin=(char *)sinput.c_str();
	}
	else
	  return status;




			soap_call_ns__runsimulation(&m_soapclient, m_serverclient, "",id, sin , &sresults);

	//call create simulation
    fstream filestr;
	filestr.open (outfile, fstream::out );
    filestr<<sresults; 
	filestr.close();
	printf("%s\n",sresults);
	//strcpy(input,simfilecontent.c_str());

	return status;
}

int SubmitSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername="";
	char *input="";
	char *content="";
    char *infile="";
	char *outfile="";
	char *sservername="";
	char *sresults="";
	char *sin=NULL;
	string simfilecontent;
	int isimid;
	

	if(argc>1 && (argv[2]!=NULL))
					infile=argv[2];
	

	/*if(argc>2 && (argv[3]!=NULL))
					outfile=argv[3];
	else 
		content="outfile.xml";*/

	if(argc>2)
	{
  
		port=atoi(argv[3]);

		if(argc>3 && (argv[4]!=NULL))
					sservername=argv[4];

 	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);

	if((strcmp(infile,"")!=0) &&  (strcmp(infile,"null")!=0))
	{
			string sinput="";
			string sline="";
			FILE *inf;
			if((inf=fopen(infile,"r")) != NULL )
			{
			char c;
			do
			{
				c=fgetc(inf);
				sline=c;
				if(c != EOF)
				 sinput.append(sline);
			}
			while(c != EOF);
			}
			fclose(inf);
			sin=(char *)sinput.c_str();
	}
	else
      return status;



			soap_call_ns__submitsimulation(&m_soapclient, m_serverclient, "",sin , &isimid);

	
	printf("%d\n",isimid);
	//strcpy(input,simfilecontent.c_str());

	return status;
}


int RequestSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername="";
	char *input="";
	char *content="";
    char *infile="";
	char *outfile="";
	char *sservername="";
	char *sresults="";
	char *sin=NULL;
	string simfilecontent;
	int isimid;
			string sinput="";
			string sline="";
	

	if(argc>1 && (argv[2]!=NULL))
					infile=argv[2];
	

	/*if(argc>2 && (argv[3]!=NULL))
					outfile=argv[3];
	else 
		content="outfile.xml";*/

	if(argc>2)
	{
  
		port=atoi(argv[3]);

		if(argc>3 && (argv[4]!=NULL))
					sservername=argv[4];

 	}
	else
		sservername="localhost";



    sprintf(m_serverclient,"%s:%d",sservername,port);

	if((strcmp(infile,"")!=0) && (strcmp(infile,"null")!=0))
	{
			//string sinput="";
			//ifstream sinfile;
			//ostringstream oss (ostringstream::out);
			//sinfile.open (infile, ifstream::in);
			//while (sinfile.good())
			//	oss << (char) sinfile.get();
			//sinput=oss.str();

			//sinfile.close();
			
			FILE *inf;
			if((inf=fopen(infile,"r")) != NULL )
			{
			char c;
			do
			{
				c=fgetc(inf);
				sline=c;
				if(c != EOF)
				 sinput.append(sline);
			}
			while(c != EOF);
			}
			fclose(inf);
			sin=(char *)sinput.c_str();
	}
	else 
		sin="null";

	//printf("file content\n");
	//printf("%s\n",sin);


	soap_call_ns__requestsimulation(&m_soapclient, m_serverclient, "",sin , &isimid);

	
	printf("%d\n",isimid);
	//strcpy(input,simfilecontent.c_str());

	return status;
}


int RunRequestedSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername="";
	char *input="";
	char *content="";
    char *infile="";
	char *outfile="";
	char *sservername="";
	char *sresults="";
	char *sin=NULL;
	string simfilecontent;
	int isimid;
	int istatus=-1;

	if(argc>1 && (argv[2]!=NULL))
					isimid=atoi(argv[2]);
	else
	{
		printf("%d\n",istatus);
		return status = 1;
	}
	

	/*if(argc>2 && (argv[3]!=NULL))
					outfile=argv[3];
	else 
		content="outfile.xml";*/

	if(argc>2 )
	{
        //id=atoi(argv[3]);

		port=atoi(argv[3]);

		if(argc>3 && (argv[4]!=NULL))
					sservername=argv[4];

 	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);


	soap_call_ns__runrequestedsimulation(&m_soapclient, m_serverclient, "",isimid , &istatus);
	
	printf("%d\n",istatus);
	//strcpy(input,simfilecontent.c_str());

	return status;
}

int SetSimulationStatus( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername="";
	char *input="";
	char *content="";
    char *infile="";
	char *outfile="";
	char *sservername="";
	char *sresults="";
	char *sin=NULL;
	string simfilecontent;
	int isimid;
	int istatus=-1;
	int newstatus=-1;

	if(argc>2 && (argv[2]!=NULL)&& (argv[3]!=NULL))
	{
					isimid=atoi(argv[3]);
					newstatus=atoi(argv[2]);
	}
	else
	{
		printf("%d\n",istatus);
		return status = 1;
	}
	

	/*if(argc>2 && (argv[3]!=NULL))
					outfile=argv[3];
	else 
		content="outfile.xml";*/

	if(argc>3 )
	{
        //id=atoi(argv[3]);

		port=atoi(argv[4]);

		if(argc>4 && (argv[5]!=NULL))
					sservername=argv[5];

 	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);


	soap_call_ns__setsimulationstatus(&m_soapclient, m_serverclient, "",newstatus,isimid , &istatus);
	
	printf("%d\n",istatus);
	//strcpy(input,simfilecontent.c_str());

	return status;
}



int SimulationStatus( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername="";
	char *input="";
	char *content="";
    char *infile="";
	char *outfile="";
	char *sservername="";
	char *sresults="";
	char *sin=NULL;
	string simfilecontent;
	int isimid;
	int istatus=-1;

	if(argc>1 && (argv[2]!=NULL))
					isimid=atoi(argv[2]);
	else
	{
		printf("%d\n",istatus);
		return status = 1;
	}
	

	/*if(argc>2 && (argv[3]!=NULL))
					outfile=argv[3];
	else 
		content="outfile.xml";*/

	if(argc>2 )
	{
        //id=atoi(argv[3]);

		port=atoi(argv[3]);

		if(argc>3 && (argv[4]!=NULL))
					sservername=argv[4];

 	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);


	soap_call_ns__simulationstatus(&m_soapclient, m_serverclient, "",isimid , &istatus);
	
	printf("%d\n",istatus);
	//strcpy(input,simfilecontent.c_str());

	return status;
}

int GetSimulationResults( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername="";
	char *input="";
	char *content="";
    char *infile="";
	char *outfile="";
	char *sservername="";
	char *sresults="";
	char *sin=NULL;
	string simfilecontent;
	int id;
	int istatus=-1;

	if(argc>1 && (argv[2]!=NULL))
	{
		//content=(char *)calloc(strlen(argv[2])+1,sizeof(char));			
		content=argv[2];
	}
	else
	{
		printf("%d\n",istatus);
		return status = 1;
	}
	

	if(argc>2 && (argv[3]!=NULL))
					id=atoi(argv[3]);
	else 
		//content="outfile.xml";
		id=0;

	if(argc>3 )
	{
        //id=atoi(argv[4]);
 
		port=atoi(argv[4]);
		if(argc>4 && (argv[5]!=NULL))
					sservername=argv[5];
 	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);



	soap_call_ns__getsimulationresults(&m_soapclient, m_serverclient, "",id , &sresults);
	
	//call create simulation
    fstream filestr;
	filestr.open (outfile, fstream::out );
    filestr<<sresults; 
	filestr.close();
	printf("%s\n",sresults);
    //free(content);
	
	return status;
}

int DeleteSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername="";
	char *input="";
	char *content="";
    char *infile="";
	char *outfile="";
	char *sservername="";
	char *sresults="";
	char *sin=NULL;
	string simfilecontent;
	int isimid;
	int istatus=-1;

	if(argc>1 && (argv[2]!=NULL))
					isimid=atoi(argv[2]);
	else
	{
		printf("%d\n",istatus);
		return status = 1;
	}
	

	/*if(argc>2 && (argv[3]!=NULL))
					outfile=argv[3];
	else 
		content="outfile.xml";*/

	if(argc>2 )
	{
        //id=atoi(argv[3]);
 
		port=atoi(argv[3]);

		if(argc>3 && (argv[4]!=NULL))
					sservername=argv[4];

 	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);


	soap_call_ns__deletesimulation(&m_soapclient, m_serverclient, "",isimid , &istatus);
	
	printf("%d\n",istatus);
	//strcpy(input,simfilecontent.c_str());

	return status;
}



int RunSimulationStep( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *sservername="";
	int step;
    int id=0;

	if(argc>1 && (argv[2]!=NULL))
					step=atoi(argv[2]);
	

	
	if(argc>3 )
	{
		id=atoi(argv[3]);
		port=atoi(argv[4]);

		if(argc>4 && (argv[5]!=NULL))
					sservername=argv[5];

	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns__runsimulationstep(&m_soapclient, m_serverclient, "",id, step , &status);


	return status;
}

int GetNumProcs( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *sservername="";
	int id;
	int numprocs;
		
	if(argc>3 )
	{
        id=atoi(argv[2]);
           port=atoi(argv[3]);

		
		if(argc>3 && (argv[4]!=NULL))
			sservername=argv[4];
	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	//soap_call_ns__getnumprocs(&m_soapclient, m_serverclient, "",id , &numprocs);
	soap_call_ns__getnumobj(&m_soapclient, m_serverclient, "",id , &numprocs);
	printf("%d\n",numprocs);

	return status;
}

int GetProcID( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *sservername="";
	int id=0;
	int procid;
		
	if(argc>3)
	{
        id=atoi(argv[2]);
        port=atoi(argv[3]);

		if(argc>3 && (argv[4]!=NULL))
					sservername=argv[4];

	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	//soap_call_ns__getnumprocs(&m_soapclient, m_serverclient, "",id , &procid);
	soap_call_ns__getobjnum(&m_soapclient, m_serverclient, "",id , &procid);
	printf("%d\n",procid);


	return status;
}



int ReadSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername=NULL;
	char *filename=argv[2];
	char *content=NULL;
	char *sservername=NULL;
	char *scontent;

	int id=0;
	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>3)
	{
        id=atoi(argv[3]);

		port=atoi(argv[4]);

		if(argc>4 && (argv[5]!=NULL))
					sservername=argv[5];

	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns__readsimulation(&m_soapclient, m_serverclient, "", id, filename, &status);

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
	int id=0;

	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>3 )
	{
        id=atoi(argv[3]);
        port=atoi(argv[4]);

		if(argc>4 && (argv[5]!=NULL))
					sservername=argv[5];

	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns__writesimulation(&m_soapclient, m_serverclient, "",  id, filename, &scontent);

	printf("%s\n",scontent);
	//if strlen(scontent)>0 
	//write content to file

	//call create simulation

	return status;
}

int ReadLocalSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername=NULL;
	char *filename=argv[2];
	char *content=NULL;
	char *sservername=NULL;
	char *scontent;

	int id=0;
	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>3)
	{
        id=atoi(argv[3]);

		port=atoi(argv[4]);

		if(argc>4 && (argv[5]!=NULL))
					sservername=argv[5];

	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
    
    
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
      
	soap_call_ns__readlocalsimulation(&m_soapclient, m_serverclient, "", id, (char *)sresult.c_str(), &status);

	//call create simulation

	return status;
}

int WriteLocalSimulation( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername=argv[5];
	char *filename=argv[2];
	char *sservername=NULL;
	char *scontent;
	int id=0;

	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>3 )
	{
        id=atoi(argv[3]);
        port=atoi(argv[4]);

		if(argc>4 && (argv[5]!=NULL))
					sservername=argv[5];

	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns__writelocalsimulation(&m_soapclient, m_serverclient, "",  id, filename, &scontent);

	printf("%s\n",scontent);
	int slen = strlen(scontent)-1;
	char *sout=(char *)calloc(slen,sizeof(char));
    strncpy(sout,scontent,slen);
	

	//if strlen(scontent)>0 
	//write content to file
	//string sresult="";
	ofstream outfile;
	//ostringstream oss (ostringstream::out);
	outfile.open (filename, ofstream::out);
	outfile << sout;
	
	outfile.close();
	//call create simulation
	free(sout);
	return status;
}

int ReadState( int argc, char **argv)
{
	int status=0;
	int port=atoi(argv[3]);
	int id=0;
    sprintf(m_serverclient,"%s:%d","localhost",port);

	return status;
}

/* int WriteState( int argc, char **argv)
{
	int status=0;
	int port=8080;
	int id=0;
	char *servername=argv[5];
	char *filename=argv[3];
	char *sservername=NULL;
	char *scontent;

	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>3 && (argv[4]!=NULL))
	{
           port=atoi(argv[4]);

		if(argc>4 && (argv[5]!=NULL))
					sservername=argv[5];

	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns__writestate(&m_soapclient, m_serverclient, "", id, filename, &scontent);

	//if strlen(scontent)>0 
	//write content to file

	//call create simulation

	return status;
}*/

/*int ReadConfig( int argc, char **argv)
{
	int status=0;
	int port=atoi(argv[3]);
	int id=0;
    sprintf(m_serverclient,"%s:%d","localhost",port);

	return status;
}*/

/*int WriteConfig( int argc, char **argv)
{
	int status=0;
	int port=8080;
	char *servername=argv[5];
	char *filename=argv[3];
	char *sservername=NULL;
	char *scontent;
	int id=0;

	scontent=(char *)calloc(5000,sizeof(char));

	if(argc>3 && (argv[4]!=NULL))
	{
           port=atoi(argv[4]);

		if(argc>4 && (argv[5]!=NULL))
					sservername=argv[5];

	}
	else
		sservername="localhost";
    sprintf(m_serverclient,"%s:%d",sservername,port);
	soap_call_ns__writeconfig(&m_soapclient, m_serverclient, "",  id,filename, &scontent);

	//if strlen(scontent)>0 
	//write content to file

	//call create simulation

	return status;
}*/





