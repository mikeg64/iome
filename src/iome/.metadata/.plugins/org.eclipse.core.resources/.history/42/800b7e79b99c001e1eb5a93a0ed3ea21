#include "IoWFSimulation.h"

extern "C" void *ThreadStartup(void *);

//simulator must get state information from the master processor
//if myprocid>0
//get state info from master
//or set state info using master
// This function is a helper function. It has normal C linkage, and is
// as the base for newly created ThreadClass objects. It runs the
// run method on the ThreadClass object passed to it (as a void *).
// After the ThreadClass method completes normally (i.e returns),
// we delete the object.
void *ThreadStartup(void *_tgtObject) {

  simparstruct *tgtObject = (simparstruct *)_tgtObject;
  printf("Running thread object in a new thread\n");
  (tgtObject->psimulant)->SetRunState(1);
  void *threadResult;
  if((tgtObject->psimulant)->GetJobmanager())
  						//run the task
  	((CIoWFSimulation *)(tgtObject->psimulation))->RunTask(tgtObject->psimulant);
  						
  						
  	 
  (tgtObject->psimulant)->HandleStateTransitions();
  CIoSimulator *psimulator=(CIoSimulator *)((tgtObject->psimulant)->GetParentSimulant());
  //simulant has run it is now ready to move data
  //reset state so that it is waiting for outputs to complete
  (tgtObject->psimulant)->SetRunState(4);
  
  //to waiting simulants
  if(psimulator)
	  ((CIoWFSimulation *)(tgtObject->psimulation))->MoveDataFrom(psimulator,tgtObject->psimulant);
  (tgtObject->psimulant)->SetRunState(4);
  
  //Update the master processor with this simulants parameters
 int myprocid=((CIoWFSimulation *)(tgtObject->psimulation))->m_iProcid;
 int distsavemode=((CIoWFSimulation *)(tgtObject->psimulation))->m_iDistrSaveMode;
 if((myprocid != 0) && ((distsavemode==1) || (distsavemode==3))) //distsavemode is the method
	                                                             //we are using to save distributed objects
	 ((CIoWFSimulation *)(tgtObject->psimulation))->UpdateMasterSimulantParams((tgtObject->psimulant));
  
  
  printf("Deleting object\n");
  //delete tgtObject;
  return threadResult;
}

CIoWFSimulation::CIoWFSimulation(void)
{
	SetSimName("WFSim");
	SetSimClass("WFSimulation");
	SetSimulantClass("WFModel");
	//strcpy(m_sSimName, "WFSim");
	//strcpy(m_sSimClass, "WFSimulation");
	m_iNumSteps  = 2;
	m_sbuffer=NULL;
	m_iProcid=0;
	m_inprocs=1;
	//SetOutputFiles("OutputResults.txt");
	m_istate=3;
	m_iDistrSaveMode=0;
	m_isteercheckpoint=0; //0=off 1=on
	m_isteerlog=0;  //0=off 1=on 2=full
	
}

CIoWFSimulation::~CIoWFSimulation(void)
{
}

/*!The distributed simulation runs on a master server and has a number of slaves
//to start the simulation we start n copies of the simulation on each host
//each simulation has the same copy of the simulation file and any required config files

//each slave process makes a web service request 
//GetProcID("hostname")

//procid hostname simulantid simulantmap
//char *m_sMasterServerHost;
//int m_iMasterServerPort;
//int m_iProcid;
//int m_inprocs;

//The master simulation will start and set the 
//m_iprocid to 0
//The slave simulations will be started and m_iprocid set to -1 
//simulations are started with the following inputs
//m_iprocid=-1 m_sMyHostname m_inprocs themasterservername themasterserverport thesimxmlfile.xml
//each simulation then starts up its own web server*/
void CIoWFSimulation::InitialiseDistributedProcs()
{

	
	char *shostname;
	int imasterstate=3;
	int i;
    if(m_iProcid !=0)//the processor is not the master processor
    {
    	
    	//send a requeste to the master process;
    	ws__setsimulationprocid(m_sMasterServerHost, m_iMasterServerPort, m_sMyHostname,m_iProcid);
    	
    	//wait for master simulation to get all info from slaves
    	do
    	{
    		imasterstate=ws__getsimulationstate(m_sMasterServerHost, m_iMasterServerPort, m_iProcid);
    	}while(imasterstate !=0);
    	
    	//get hostnames for all the slaves
    	int ifinished=0;
    	int j;
    	for(i=1; i<m_inprocs; i++)
    	{
    		ifinished=0;
    		j=0;
    		if(i != m_iProcid)
    		{
    			shostname=ws__getsimulationhostname(m_sMasterServerHost, m_iMasterServerPort, i);
    			while(!ifinished)
    			{
    				if(GetProcID(j)==i)
    					SetProcHostname(j,shostname);
    				if(j>=m_pProcs.size())
    					ifinished=1;
    			}   			
    		}    			
    	}//finished getting hostnames from each process
    	
    }
    else
    {
    	if(m_inprocs==1)
    		m_istate=0;
    }
	
}


/*!Save modes
//The distribute tag has an attribute savemode
//This attribute determines whether the config data is
//saved by the master processor only or by each processor
//The mode determines whether the master is updated with config data
//by the worker processor
//For worker processors the config filename is appended with pidXXX
//xxx is the procid of the worker process
//Thus when rereading such a simulation worker simulation with savemode
//set appropriately will read the current configuration (along with simulation file
//this is distributed to all workers) will also read the config file appended with
//with pidxxx 
//int m_iDistrSaveMode; //masterproconly=0, masterproconly, master updated at end of each step=1, simulant configs savesd on all procs proc saves only simulant that it runs=2, as for 2 but master proc is also updated with the parameters
*/

void CIoWFSimulation::UpdateMasterSimulantParams(CIoSimulant *psimulant)
{
	char simmap[50]="";
	int simid=GetSimulantID(psimulant);
	GetSimulantMap(psimulant,simmap);
	
	CIoParam *pparam, *simparam;
	
	int iparamid=0;
	char sparammap[50]="";
	int ifinished=0;
	CIoParam *testparam=psimulant->GetParams();
	int idarray[10];
	int idepth=0;
	CIoParam *paramparent[10];
	int i;
	
	
	while(!ifinished)
	{
		//if testsim is simulator
		if((testparam->m_type)==IO_PARAM_ARRAY)
		{
			paramparent[idepth]=testparam;
			idepth=idepth++;
			idarray[idepth]=simid;
			testparam=testparam->m_pParam;
			iparamid=0;
		}
		
		
		


		
		//case where we have finished looping over all the 
		//simulants in a simulator
		if((testparam==NULL) && idepth>0)
		{
			iparamid=idarray[idepth];
			testparam=paramparent[idepth-1];
			idepth--;
			
		}
		else if(testparam==NULL)
		{
			ifinished=1;
			break;			
		}
		
		
		
		
		
		//construct the simmap
		if(idepth>0)
		{
			for(i=0; i<idepth; i++)
			{
				sprintf(sparammap,"%s, %d",sparammap,idarray[i]);
			}
		}		
		ws__setsimulantparam(m_sMasterServerHost, m_iMasterServerPort, iparamid, sparammap, simid, simmap, pparam);
		testparam=testparam->GetNextParam();
		iparamid++;
		


	}
	
}



int CIoWFSimulation::GetSimulantProcID(CIoSimulant *psimulant)
{
	int simid=0;
	int ifinished=0;
	CIoSimulant *testsim=m_pSimulant;
	int idarray[10];
	int idepth=0;
	CIoSimulant *simparent[10];
	
	
	while(!ifinished)
	{
		//if testsim is simulator
		if((testsim->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
		{
			simparent[idepth]=testsim;
			idepth=idepth++;
			idarray[idepth]=simid;
			testsim=m_pSimulant;
			simid=0;
		}
		
		
		
		if((testsim==psimulant))
		{
			ifinished=1;
			break;
		}


		
		//case where we have finished looping over all the 
		//simulants in a simulator
		if((testsim==NULL) && idepth>0)
		{
			simid=idarray[idepth];
			testsim=simparent[idepth-1];
			idepth--;
			
		}
		else if(testsim==NULL)
		{
			ifinished=1;
			break;			
		}
		
		
		
		testsim=testsim->GetNextSimulant();
		simid++;
		


	}
	
	return simid;
}


void CIoWFSimulation::GetSimulantMap(CIoSimulant *psimulant, char *simmap)
{
	//char simmap[50]="";
	int simid=0;
	int i;
	int ifinished=0;
	CIoSimulant *testsim=m_pSimulant;
	int idarray[10];
	int idepth=0;
	CIoSimulant *simparent[10];
	
	
	while(!ifinished)
	{
		//if testsim is simulator
		if((testsim->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
		{
			simparent[idepth]=testsim;
			idepth=idepth++;
			idarray[idepth]=simid;
			testsim=m_pSimulant;
			simid=0;
		}
		
		
		
		if((testsim==psimulant))
		{
			ifinished=1;
			break;
		}


		
		//case where we have finished looping over all the 
		//simulants in a simulator
		if((testsim==NULL) && idepth>0)
		{
			simid=idarray[idepth];
			testsim=simparent[idepth-1];
			idepth--;
			
		}
		else if(testsim==NULL)
		{
			ifinished=1;
			break;			
		}
		
		
		
		testsim=testsim->GetNextSimulant();
		simid++;
		


	}
	
	
	//construct the simmap
	if(idepth>0)
	{
		for(i=0; i<idepth; i++)
		{
			sprintf(simmap,"%s, %d",simmap,idarray[i]);
		}
	}
	else
		return;
	
	//return simmap;
}
 

CIoSimulant *CIoWFSimulation::GetSimulant(int isimid, char *simmap)
{
	CIoSimulant *psimulant=NULL;
	char seps[] = " ,\t\n";
	int depth, index;
	int j=0;
	int *iarray;
	char *tokenptr;
	char *s;

	CIoParam *pParam = NULL;
	CIoParam *pCurrentParam = NULL;

    if(simmap)
	{
		s = (char *)new char [1+strlen(simmap)];
		//First read the parameter map 
		strcpy(s, simmap);

		//Find the parameter!
		index=0;

		tokenptr = strtok(s, seps);
		if((depth=atoi(tokenptr))<1) depth =1;
		
		iarray = (int *)new int [depth];

		while(tokenptr !=NULL)
		{
			tokenptr = strtok(NULL, seps);
			if(j<depth)
				iarray [j]=atoi(tokenptr);

			j++;
		}

		j=1;
		psimulant = m_pSimulant->GetSimulant(iarray[0]);
		do
		{
			index=iarray[j];
			psimulant = psimulant->GetSimulant(index);
		}while(++j<depth && psimulant !=NULL);

		if(psimulant)
			psimulant=psimulant->GetSimulant(isimid);
		else
			psimulant=NULL;
	}
	else if(isimid>0)
		psimulant=m_pSimulant->GetSimulant(isimid);
	else
		psimulant=m_pSimulant;
	
	return psimulant;
}


int CIoWFSimulation::GetSimulantID(CIoSimulant *psim)
{
	int procid=0;
	CIoSimulant *testsim;
	CIoProc *proc;
	int i;
	if(psim)
	{
		for(i=0; i<m_pProcs.size(); i++)
		{
			proc=m_pProcs[i];
			if(proc)
			{
				testsim=this->GetSimulant(proc->GetSimulantID(), proc->GetSimulantMap());
				if(testsim=psim)
				{
					procid=proc->GetID();
					i=m_pProcs.size();
					break;
				}
					
				
			}
		}
		
	}
	
	return procid;
	
}


void CIoWFSimulation::MoveDataFrom(CIoSimulator *psimulator, CIoSimulant *psimulant)
{
	
}

void CIoWFSimulation::MoveData(CIoSimulator *psimulator, CIoSimulant *psimulant,CIoSimulant *tosimulant,CIoSimulantPort *fromport,CIoSimulantPort *toport,CIoSimulantLink *fromlink,CIoSimulantLink *tolink)
{
}

	

		

//makes a request to the iome java application server
//the request has n parameters
//a specific function will be called
//the function takes as input an array of params contained in
//sparams. This will be converted to a comma/space separated list
//response will be received from the application server when the
//processing step has completed
int CIoWFSimulation::jserver(int nparams, char *function , char **sparams)
{
	int iresult=0;
	
	return iresult;	
}


int CIoWFSimulation::RunTask(CIoSimulant *psimulant)
{
	int iresult=0;
	if(psimulant)
	{
		jjobrun((psimulant->m_wfexecutable).GetMethod(), (psimulant->m_wfexecutable).GetJobmanager(),(psimulant->m_wfexecutable).GetHost(),(psimulant->m_wfexecutable).GetUsername(),(psimulant->m_wfexecutable).GetEncryptedpassword(),(psimulant->m_wfexecutable).GetCommand(),(psimulant->m_wfexecutable).GetParameters());
	}
	return iresult;		
}


int CIoWFSimulation::jfileput(char *method, char *remotehost, char *username, char *encpassword, char *localfile, char *remotefile)
{
	int iresult=0;
	char *args[6];
	
	#ifndef IO_MSVC
		char *path="$IOME_HOME/bin/jfiletransfer";
	#else
		char *path="$IOME_HOME\bin\jfiletransfer";
	#endif
	//Run the model
	int pid,status,procstatus=0;
	args[0]=method;
	args[1]=remotehost;
	args[2]=username;
	args[3]=encpassword;
	args[4]=remotefile;
	args[5]=localfile;
	//int pid,status,procstatus=0;
	
	//unix/linux/cygwin process call
	#ifndef IO_MSVC
		if((pid=fork())<0)
		         procstatus=-1;
		         
		if( (procstatus==0))
		{
			if((pid==0) )
			{
			       //the file to be executed
			       //and the parameters passed to the command
			       execvp(path,args);	
			}
			
			while(wait(&status) != pid)
			           ;/*do nothing*/
		}
	//windows process call
	#else
		//_flushall();
		pid=_spawnv(_P_NOWAIT, path, args);
		if(pid != -1)
			_cwait(&status, pid, _WAIT_CHILD);
		
	#endif	
	return iresult;			
}


int CIoWFSimulation::jfileget(char *method, char *remotehost, char *username, char *encpassword, char *remotefile, char *localfile)
{
	int iresult=0;
	char *args[6];
	
	#ifndef IO_MSVC
		char *path="$IOME_HOME/bin/jfiletransfer";
	#else
		char *path="$IOME_HOME\bin\jfiletransfer";
	#endif
	//Run the model
	int pid,status,procstatus=0;
	args[0]="get";
	args[1]=method;
	args[2]=remotehost;
	args[3]=username;
	args[4]=encpassword;
	args[5]=remotefile;
	args[6]=localfile;
	
	//unix/linux/cygwin process call
	#ifndef IO_MSVC
		if((pid=fork())<0)
		         procstatus=-1;
		         
		if( (procstatus==0))
		{
			if((pid==0) )
			{
			       //the file to be executed
			       //and the parameters passed to the command
			       execvp(path,args);	
			}
			
			while(wait(&status) != pid)
			           ;/*do nothing*/
		}
	//windows process call
	#else
		//_flushall();
		pid=_spawnv(_P_NOWAIT, path, args);
		if(pid != -1)
			_cwait(&status, pid, _WAIT_CHILD);
		
	#endif	
	return iresult;			
}



int CIoWFSimulation::jjobrun(char *method, char *jobmanager, char *remotehost, char *username, char *encpassword, char *command, char *parameters)
{
	int iresult=0;
	char *args[7];
	
	#ifndef IO_MSVC
		char *path="$IOME_HOME/bin/jjobrun";
	#else
		char *path="$IOME_HOME\bin\jjobrun";
	#endif
	//Run the model
	int pid,status,procstatus=0;
	args[0]=method;
	args[1]=jobmanager;
	args[2]=remotehost;
	args[3]=username;
	args[4]=encpassword;
	args[5]=command;
	args[6]=parameters;	
	//int pid,status,procstatus=0;
	
	//unix/linux/cygwin process call
	#ifndef IO_MSVC
		if((pid=fork())<0)
		         procstatus=-1;
		         
		if( (procstatus==0))
		{
			if((pid==0) )
			{
			       //the file to be executed
			       //and the parameters passed to the command
			       execvp(path,args);	
			}
			
			while(wait(&status) != pid)
			           ;/*do nothing*/
		}
	//windows process call
	#else
		//_flushall();
		pid=_spawnv(_P_NOWAIT, path, args);
		if(pid != -1)
			_cwait(&status, pid, _WAIT_CHILD);
		
	#endif	
	return iresult;		
}



//functions used by server requests this is called by the web server response
//function responding to the client call ws__setsimulationprocid
void CIoWFSimulation::setsimulationprocid(char *shostname)
{
	int i=0;
	int id;
	char *prochostname=NULL;
	//for(i=0; i<m_pProcs.size(); i++)
	int ifinished=0;
	
	while(!ifinished)
	{
		if((prochostname=GetProcHostname(i))==NULL)
		{
			id=GetProcID(i);
			while(!ifinished)
			{
				SetProcHostname(i,prochostname);				
				if(i>=m_pProcs.size()) ifinished=1;				
				i++;
				if(GetProcID(i)!=id) ifinished=1;
			}
			
		}
		if(i>=m_pProcs.size()) ifinished=1;				
		i++;
		
			
	}
	
	//see if all processes have been allocated 
	//if so set simulation state so that ready to go
	ifinished=1;
	for(i=0; i<m_pProcs.size(); i++)
		if((prochostname=GetProcHostname(i))==NULL) ifinished=0;
	if(ifinished==1)
		m_istate=0;  //slaves set and simulation ready to run
	
}



//client requests
int CIoWFSimulation::ws__setsimulationprocid(char *ssever, int iwsport, char *shostname, int iprocid)
{
	//char soapcontact[200]=sprintf("%s:%d",sserver,iwsport);
	int soapresp;
	int *theid; 
	//soap_call_ns__setsimulationprocid(&m_soap, soapcontact, "", shostname, theid, &soapresp);
	if (m_soap.error)
	{ 
	  soap_print_fault(&m_soap, stderr);
	  return 0;
	}
	
	return *theid;
}

void CIoWFSimulation::ws__setsimulationparam(char *sserver, int iwsport, int paramid, char *parammap, CIoParam *newparam)
{
	//char soapcontact[200]=sprintf("%s:%d",sserver,iwsport);
	int soapresp;
	//soap_call_ns__setsimulationparam(&m_soap, soapcontact, "", paramid, parammap,type ,sparam, &soapresp);
	if (m_soap.error)
	{ 
	  soap_print_fault(&m_soap, stderr);
	  return;
	}
}	
	
	
CIoParam *CIoWFSimulation::ws__getsimulationparam(char *sserver, int iwsport, int paramid, char *parammap)
{
	CIoParam *pparam=NULL;
	
	return pparam;
}	
	
	

void CIoWFSimulation::ws__setsimulantparam(char *sserver, int iwsport, int paramid, char *parammap, int simulantid, char *simmap, CIoParam *newparam)
{
	
}	
	
	
CIoParam *CIoWFSimulation::ws__getsimulantparam(char *sserver, int iwsport, int paramid, char *parammap, int simulantid, char *simmap)
{
	CIoParam *pparam=NULL;
	
	return pparam;
}	
	
	

int CIoWFSimulation::ws__getstep(char *sserver, int iwsport, int id)
{
	int iret=-1;
	
	return iret;
}	
	
	
void CIoWFSimulation::ws__setstep(char *sserver, int iwsport, int id, int newstep)
{
	
}	
	
	

int CIoWFSimulation::ws__getnsteps(char *sserver, int iwsport, int id)
{
	int iret=-1;
	
	return iret;	
}	
	
	
void CIoWFSimulation::ws__setnsteps(char *sserver, int iwsport, int id, int newnsteps)
{
	
}


int CIoWFSimulation::ws__getsimulationstate(char *ssever, int iwsport, int id)
{
	int iret=-1;
	
	return iret;		
}	
	
	
int CIoWFSimulation::ws__setsimulationstate(char *ssever, int iwsport, int id, int inewstate)
{
	int iret=-1;
	
	return iret;		
}	
	
	

int CIoWFSimulation::ws__getsimulantstate(char *ssever, int iwsport, int id, char *simmap)
{
	int iret=-1;
	
	return iret;		
}	
	
	
int CIoWFSimulation::ws__setsimulantstate(char *ssever, int iwsport, int id, char *simmap, int inewstate)
{
	int iret=-1;
	
	return iret;		
}	
	
	

int CIoWFSimulation::ws__getsimulantinportstate(char *ssever, int iwsport, int id, char *simmap, int portid)
{
	int iret=-1;
	
	return iret;		
}	
	
	
int CIoWFSimulation::ws__setsimulantinportstate(char *ssever, int iwsport, int id, char *simmap, int portid, int inewstate)
{
	int iret=-1;
	
	return iret;		
}	
	
	

int CIoWFSimulation::ws__getsimulantoutportstate(char *ssever, int iwsport, int id, char *simmap, int portid)
{
	int iret=-1;
	
	return iret;		
}	
	
	
	
int CIoWFSimulation::ws__setsimulantoutportstate(char *ssever, int iwsport, int id, char *simmap, int portid, int inewstate)
{
	int iret=-1;
	
	return iret;		
}








//int CIoWFSimulation::ws__setsimulationprocid(char *ssever, int iwsport, char *shostname)
//{
//	int iret=-1;
	
//	return iret;		
//}


char  *CIoWFSimulation::ws__getsimulationhostname(char *ssever, int iwsport, int id)
{
	char *shostname=NULL;
	
	return shostname;	
}


int CIoWFSimulation::ws__getfile(char *ssever, int iwsport, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char **sfile)
{
	int iret=-1;
	
	return iret;		
}

int CIoWFSimulation::ws__putfile(char *ssever, int iwsport,int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char *sdata,char **sfile)
{
	int iret=-1;
	
	return iret;		
}

int CIoWFSimulation::ws__setcheckpoint(char *ssever, int iwsport,int id, int inewstate, int *istate)
{
	int iret=-1;
	
	return iret;		
}


int CIoWFSimulation::ws__getcheckpoint(char *ssever, int iwsport,int id, int *istate)
{
	int iret=-1;
	
	return iret;		
}


	
int CIoWFSimulation::ws__setsteerlog(char *ssever, int iwsport,int id, int inewsteerlog, int *isteerlog)
{
	int iret=-1;
	
	return iret;		
}


int CIoWFSimulation::ws__getsteerlog(char *ssever, int iwsport,int id, int *isteerlog)
{
	int iret=-1;
	
	return iret;		
}




void CIoWFSimulation::setsimulationparam(struct soap *soap,int paramid, char *parammap, char *newvalue, char **value)
{


	if(m_isteercheckpoint>0)
			steercheckpoint();

    if(m_isteerlog>1)
			steerupdatesteerlog();



		CIoParam *newparam;
		string paramstring(newvalue);
		//std::cout << "wfsim new value " << newvalue <<" " << paramstring << std::endl;
		CIoParam *nparam=m_pProperties->GetChildParam(paramid,parammap);
		//std::cout << "param is " << *nparam << std::endl;
		
		newparam=new CIoParam(nparam);
		//std::cout << "newparam is " << *newparam << std::endl;
		
		newparam=nparam->String2Param(paramstring,newparam);
		//std::cout << "newparam is " << *newparam << std::endl;
		
		nparam->SetParam(newparam);
		//std::cout << "nparam is " << *nparam << std::endl;
				
		string nparamstring=nparam->Param2String(newparam);
		*value = (char*)soap_malloc(soap, nparamstring.size());
		sprintf(*value,"%s",nparamstring.c_str());
		//*value=new char[nparamstring.size()];
		//strcpy(*value,nparamstring.c_str());
}

void CIoWFSimulation::getsimulationparam(struct soap *soap,int paramid, char *parammap, char **value)
{		
		//string paramstring();
		CIoParam *nparam=m_pProperties->GetChildParam(paramid,parammap);
		string paramstring=nparam->Param2String(nparam);
		//*value=new char[paramstring.size()];
		//strcpy(*value,paramstring.c_str());
		*value = (char*)soap_malloc(soap, paramstring.size());
		sprintf(*value,"%s",paramstring.c_str());

}

void CIoWFSimulation::setsimulantparam(struct soap *soap,int paramid, char *parammap, int simulantid, char *simmap, char *newvalue, char **value)
{
		CIoParam *newparam;
		string paramstring(newvalue);

		if(m_isteercheckpoint>0)
			steercheckpoint();

    	if(m_isteerlog>1)
			steerupdatesteerlog();




		CIoSimulant *psimulant =GetChildSimulant(simulantid,simmap);
		
		if(psimulant)
		{
			string paramstring(newvalue);
			//CIoParam *nparam=psimulant->m_pProperties->GetChildParam(paramid,parammap);
			CIoParam *nparam=psimulant->m_pProperties->GetParam(paramid);
			newparam=new CIoParam(nparam);
            std::cout << "nparam is " << *nparam << std::endl;

            std::cout << "new string is " << newvalue << std::endl;
			std::cout <<" current nparam is " << *newparam << std::endl;
			newparam=nparam->String2Param(paramstring,newparam);
			std::cout <<paramstring << std::endl <<" nparam is " << *newparam << std::endl;
			//newparam=new CIoParam(nparam->String2Param(paramstring,newparam));
			nparam->SetParam(newparam);		
			string nparamstring=nparam->Param2String(newparam);
			std::cout << "newparam is " << *newparam << std::endl;

			nparam->SetParam(newparam);
			std::cout << "nparam is " << *nparam << std::endl;
				
			//string nparamstring=nparam->Param2String(newparam);
			//*value=new char[nparamstring.size()];
			//strcpy(*value,nparamstring.c_str());
  			
			*value = (char*)soap_malloc(soap, nparamstring.size());
			sprintf(*value,"%s",nparamstring.c_str());

			std::cout << "new value string is " << *value << std::endl;

			
		}	
	
	
}

void CIoWFSimulation::getsimulantparam(struct soap *soap,int paramid, char *parammap, int simulantid, char *simmap, char **value)
{
		CIoSimulant *psimulant =GetChildSimulant(simulantid,simmap);
		//*value = (char*)soap_malloc(soap, 11); 
		//sprintf(*a, "%d", i); 

		if(psimulant)
		{
			CIoParam *nparam=psimulant->m_pProperties->GetChildParam(paramid,parammap);
			string paramstring=nparam->Param2String(nparam);
			*value = (char*)soap_malloc(soap, paramstring.size());
			//if(m_sbuffer != NULL)
			//		free(m_sbuffer);
			//m_sbuffer=(char *)calloc(paramstring.size(),sizeof(char));
			sprintf(*value,"%s",paramstring.c_str());
			//value=&m_sbuffer;
		}	
	
}
	
void CIoWFSimulation::getstep(struct soap *soap,int id, int *step)
{
	
	*step=m_iCurrentStep;
}

void CIoWFSimulation::setstep(struct soap *soap,int id, int newstep, int *step)
{
	SetCurrentStep(newstep);
	*step=m_iCurrentStep;		
}
	
void CIoWFSimulation::getnsteps(struct soap *soap,int id, int *nsstep)
{
	*nsstep=m_iNumSteps;
		
}

void CIoWFSimulation::setnsteps(struct soap *soap,int id, int newnsteps, int *nsteps)
{
	SetNumSteps(newnsteps);
	*nsteps=m_iNumSteps;		
}
	
void CIoWFSimulation::getsimulationstate(struct soap *soap,int id, int *istate)
{
	
	
	
}

void CIoWFSimulation::setsimulationstate(struct soap *soap,int id, int inewstate, int *istate)
{
	
	m_istate=inewstate;
	*istate=m_istate;
	
}
	
void CIoWFSimulation::getsimulantstate(struct soap *soap,int id, char *simmap, int *istate)
{
	
	
	
	
}


void CIoWFSimulation::setsimulantstate(struct soap *soap,int id, char *simmap, int inewstate, int *istate)
{
	
	
	
}
	
void CIoWFSimulation::getsimulantinportstate(struct soap *soap,int id, char *simmap, int portid, int *istate)
{
	
	
	
}



void CIoWFSimulation::setsimulantinportstate(struct soap *soap,int id, char *simmap, int portid, int inewstate, int *istate)
{
	
	
	
}
	
void CIoWFSimulation::getsimulantoutportstate(struct soap *soap,int id, char *simmap, int portid, int *istate)
{
	
	
	
}

void CIoWFSimulation::setsimulantoutportstate(struct soap *soap,int id, char *simmap, int portid, int inewstate, int *istate)
{
	
	
	
}
	
	
void CIoWFSimulation::setsimulationprocid(struct soap *soap,char  *hostname, int *isimulationprocid)
{
	
	
}

void CIoWFSimulation::getsimulationhostname(struct soap *soap,int isimulationid, char **shostname)
{
	
		//		*hostname = (char*)soap_malloc(soap, nparamstring.size());
		//	sprintf(*hostname,"%s",nparamstring.c_str());

	
}



int CIoWFSimulation::getfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char **sfile)
{


			ifstream infile;
			string infilename="";
			infilename+=remotefilepath;
			infilename+=remotefilename;
			stringstream ss(stringstream::in | stringstream::out);
			infile.open(infilename.c_str(),ifstream::in);
			string sfilebuffer="";
			string sdata="";
			
			while(infile.good())
			{
				ss << (char)infile.get();
				ss >>  sdata;
				sfilebuffer+=sdata;
				sdata.clear();
				
			}
			infile.close();
			
			
			*sfile = (char*)soap_malloc(soap, sfilebuffer.size());
			sprintf(*sfile,"%s",sfilebuffer.c_str());
			//if(m_sbuffer != NULL)
			//		free(m_sbuffer);
			//m_sbuffer=(char *)calloc(paramstring.size(),sizeof(char));
			//sprintf(*value,"%s",paramstring.c_str());
			//value=&m_sbuffer;
			return 0;
	
}

int CIoWFSimulation::putfile(struct soap *soap, int id,char *localfilename, char *localpath, char *remotefilename, char *remotefilepath ,char *sdata,char **sfile)
{
	

			ofstream outfile;
			string outfilename="";
			outfilename+=remotefilepath;
			outfilename+=remotefilename;
			//stringstream ss(stringstream::in | stringstream::out);
			outfile.open(outfilename.c_str(),ofstream::out);
			string sfilebuffer="";
			string ssdata=sdata;
			//outfile << 
			while(outfile.good())
			{
				outfile << ssdata;
				
			}
			outfile.close();
			
			
			*sfile = (char*)soap_malloc(soap, sfilebuffer.size());
			sprintf(*sfile,"%s",sfilebuffer.c_str());
			//if(m_sbuffer != NULL)
			//		free(m_sbuffer);
			//m_sbuffer=(char *)calloc(paramstring.size(),sizeof(char));
			//sprintf(*value,"%s",paramstring.c_str());
			//value=&m_sbuffer;
				
			return 0;
	
}

int CIoWFSimulation::setcheckpoint(struct soap *soap,int id, int inewstate, int *istate)
{
	int istatus=0;
	
	
	return istatus;
}




int CIoWFSimulation::getcheckpoint(struct soap *soap,int id, int *istate)
{
	int istatus=0;
	
	
	return istatus;
}



	
int CIoWFSimulation::setsteerlog(struct soap *soap,int id, int inewsteerlog, int *isteerlog)
{
	int istatus=0;
	
	
	return istatus;
}



int CIoWFSimulation::getsteerlog(struct soap *soap,int id, int *isteerlog)
{
	int istatus=0;
	
	
	return istatus;
}

int CIoWFSimulation::steercheckpoint()
{
  int istatus=0;
  char cstep[6];
  CIoSimDOMBuilder DOMSimulation;
  CIoConfigDOMBuilder DOMConfig;
  
  string soldcfgname=this->m_sConfigFileName;
  string soldsimname=this->m_sSimName;
  sprintf(cstep,"%d",this->m_iCurrentStep);
  string snewsimname=soldsimname+"_ckpoint_"+cstep+".xml";
  string snewcfgname=soldcfgname+"_ckpoint_"+cstep+".xml";
  this->SetSimName((char *)(snewsimname.c_str()));
  this->SetConfigFileName((char *)(snewcfgname.c_str()));
  

  DOMConfig.CreateConfigDOM((char *)(snewcfgname.c_str()), this, m_iCurrentStep);
  DOMConfig.WriteConfigDOM((char *)(snewcfgname.c_str()));
  

  DOMSimulation.CreateSimDOM((char *)snewsimname.c_str(), this);
  DOMSimulation.WriteSimDOM((char *)snewsimname.c_str());
      
  this->SetSimName((char *)(soldsimname.c_str()));
  this->SetConfigFileName((char *)(soldcfgname.c_str()));
  
  return istatus;			
}

int CIoWFSimulation::steerupdatesteerlog()
{
  int istatus=0;
    char cstep[6];
    int inoparams=0;
    int ifileprops=1;
    int iNoEntities=0;
  
	CIoConfigDOMBuilder *DOMSteerState;
	DOMSteerState = m_pDOMSteerState;

	CIoSimulant *pSim=m_pSimulant;

	int ioldstep=GetCurrentStep();
    int iStepNum=GetCurrentStep();
    int iNoParams=0;

    if(m_isteerlog>1)
       inoparams=1;
	  string soldcfgname=this->m_sConfigFileName;
	  string soldsimname=this->m_sSimName;
	  sprintf(cstep,"%d",this->m_iCurrentStep);
	  string snewsimname=soldsimname+"_ckpoint_"+cstep+".xml";
	  string snewcfgname=soldcfgname+"_ckpoint_"+cstep+".xml";
	  this->SetSimName((char *)snewsimname.c_str());
	  this->SetConfigFileName((char *)snewcfgname.c_str());


  

		for(m_lSteerStateIterator=m_lSteerStateList.begin(); m_lSteerStateIterator != m_lSteerStateList.end();m_lSteerStateIterator++)
		{
			if(pSim=(CIoSimulant *)(*m_lSteerStateIterator))
			{
				//SetSimulant(pSim);
				//SetCurrentCycle(pSim->GetCurrentCycle());
				//SetCurrentStep(pSim->GetCurrentStep());
				if(DOMSteerState)
				{
					
					DOMSteerState->m_pRootElem->appendChild(DOMSteerState->CreateSimulationElement(this, iStepNum, iNoEntities));
				}
				else
				{
					m_pDOMSteerState=(CIoConfigDOMBuilder *)new CIoSimDOMBuilder;
					DOMSteerState = m_pDOMSteerState;
					DOMSteerState->CreateConfigDOM((char *)snewcfgname.c_str(), this, iStepNum, iNoEntities, inoparams, ifileprops );
				}

				//if last simulant in list don't know if this is the last one
				//so write anyway
				//if(m_lSimStateIterator == m_lSimStateList.end())
					DOMSteerState->WriteConfigDOM((char *)snewcfgname.c_str(), iNoEntities, inoparams, ifileprops);
			}
		}

	  this->SetSimName((char *)soldsimname.c_str());
	  this->SetConfigFileName((char *)soldcfgname.c_str());


  
  return istatus;				
}





//gets and sets port states for the master processor which contains
//all the state info
int CIoWFSimulation::GetSimulantOutPortState(CIoSimulant *psim, int iport)
{
	int iret=-1;
	    
	return iret;		
}
	
	
	
	
int CIoWFSimulation::GetSimulantInPortState(CIoSimulant *psim, int iport)
{
	int iret=-1;
	return iret;}
	
	
	
int CIoWFSimulation::SetSimulantOutPortState(CIoSimulant *psim, int iport, int istate)
{
	int iret=-1;
	return istate;		
}
	
	
	
int CIoWFSimulation::SetSimulantInPortState(CIoSimulant *psim, int iport, int istate)
{
	int iret=-1;
	return istate;			
}

#ifdef USEMPI

int CIoWFSimulation::BroadcastHostname(int ifromid)
{
	int status=0;
	char *shostname=(char *)calloc(1000,sizeof(char));

	if(m_irank=ifromid)
		strcpy(shostname,m_sHostname.c_str());
	m_comm.Bcast(&shostname,strlen(shostname),MPI::INT,ifromid);
	if(m_irank!=ifromid)
		m_sHostname=shostname;

	free(shostname);
	return status;
}
#endif
	
	

