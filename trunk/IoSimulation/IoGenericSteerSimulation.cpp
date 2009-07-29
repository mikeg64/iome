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


#include "IoGenericSteerSimulation.h"

CIoGenericSteerSimulation::CIoGenericSteerSimulation(void)
{
	SetSimName("GenericSim");
	SetSimClass("GenericSteerSimulation");
	SetSimulantClass("AgentModel");
	//strcpy(m_sSimName, "AgentSim");
	//strcpy(m_sSimClass, "GenericSteerSimulation");
	m_iNumSteps  = 2;
	m_ibarrier =0;
	m_isubproc = 0;
	//m_pConstParams=NULL;
    //m_iNumParams=0;
}

CIoGenericSteerSimulation::~CIoGenericSteerSimulation(void)
{
	m_pConstParams.clear(); //add param methods are used to add parameters to the model
	                                   //the parameters which are added define the default values
	                                   //for the parameters so these values are fixed
	m_pPropName.clear();
	m_pPropFlag.clear();
	m_pnodes.clear();
	m_pnodes.clear();
}

void CIoGenericSteerSimulation::CreatePropNames()
{
	//AddPropName("defaultint");
	
	string pstring;

	deque<string>::iterator  pIterator;
	for(pIterator=m_pPropName.begin();
		pIterator!=m_pPropName.end(); pIterator++)
	{
			pstring = (string) (*pIterator);
			AddPropName((char *)pstring.c_str());
	}
	
	
	
}

void CIoGenericSteerSimulation::CreatePropArrayNames()
{
	AddArrayName("AgentSimProps");


}

void CIoGenericSteerSimulation::CreatePropFlags()
{
	int iflag = 1;//sim only


	//AddPropFlag(iflag);

	deque<int>::iterator  pIterator;
	for(pIterator=m_pPropFlag.begin();
		pIterator!=m_pPropFlag.end(); pIterator++)
	{
			iflag = (int) (*pIterator);
			AddPropFlag(iflag);
	}
	

}

void CIoGenericSteerSimulation::CreatePropArrayFlags()
{
	int iflag = 5; //State, sim
	AddArrayFlag(iflag);

}

void CIoGenericSteerSimulation::CreateDefaultParams()
{
int i1;
i1 = 10;
CIoParam *pParam=NULL;

	if(m_pProperties)
		delete m_pProperties;

    m_pProperties  = new CIoParam;

	deque<CIoParam *>::iterator  pConstParamsIterator;
	for(pConstParamsIterator=m_pConstParams.begin();
		pConstParamsIterator!=m_pConstParams.end(); pConstParamsIterator++)
	{
			if(pParam = (CIoParam *) (*pConstParamsIterator))
								AddProperty(pParam);
	}
	//AddInt(i1);
 
}

int CIoGenericSteerSimulation::CheckParamFormat(CIoParam *pSimData)
{
	int status=0;
	CIoParam *pParam=NULL;

	if((pSimData && (pSimData->GetType()==IO_PARAM_ARRAY)))
		if((pParam=pSimData->GetParam(0)) && (pParam->GetType()==IO_PARAM_INTEGER))status=1;

	return status;
}

CIoModel *CIoGenericSteerSimulation::newModel(char *sModelClass)
{
	CIoModel *pmod=NULL;
	//CIoAgentModel *pAgentModel= new CIoAgentModel(this,NULL,NULL);

	/*! Unnecsssary the create method does this*/
	//pAgentModel->CreateDefaultParams();
	//return NULL;
	//return pAgentModel;
	
	return pmod;
}

/*CIoSimulator *CIoGenericSteerSimulation::newSimulator(char *sSimulatorClass)
{
	CIoAgentSimulator *pAgentSimulator= new CIoAgentSimulator;
	pAgentSimulator->CreateDefaultParams();

	return pAgentSimulator;
}*/




int  CIoGenericSteerSimulation::WriteConfig(char *sConfigFilename, int format, char *sXSLFilename, int iStepNum)
{
	int status=0;
		status = CIoXMLSimulation::WriteConfig(sConfigFilename, format);
    
    

	//We have stored all cell positions and energies
	//not always necessary so delete them again????
	return status;
}






int CIoGenericSteerSimulation::SetParamDouble(double value, string sparamname, int iflag)
{
	int status=0;
	CIoParam *pparam=NULL;
	
	int index=GetPropIndex(sparamname);
	if(index>=0)
	{
		//pparam=this->GetProperty(index);
		//if(pparam && (pparam->GetType()==IO_PARAM_FLOAT))
		  //pparam->SetParam(index,value);
		  this->SetFloat(index,value);
		
	}
	return status;	
}


int CIoGenericSteerSimulation::SetParamInt(int value, string sparamname, int iflag)
{
	int status=0;
	CIoParam *pparam=NULL;
	
	int index=GetPropIndex(sparamname);
	if(index>=0)
	{
		//pparam=this->GetProperty(index);
		//if(pparam && (pparam->GetType()==IO_PARAM_FLOAT))
		  //pparam->SetParam(index,value);
		  this->SetInt(index,value);
		
	}
	return status;	
}

int CIoGenericSteerSimulation::SetParamString(string value, string sparamname, int iflag)
{
	int status=0;
	CIoParam *pparam=NULL;
	
	int index=GetPropIndex(sparamname);
	if(index>=0)
	{
		//pparam=this->GetProperty(index);
		//if(pparam && (pparam->GetType()==IO_PARAM_FLOAT))
		  //pparam->SetParam(index,value);
		  this->SetString(index,value);
		
	}
	return status;	
}


int CIoGenericSteerSimulation::GetParamDouble(double *value, string sparamname)
{
	int status=0;
	CIoParam *pparam=NULL;
	
	int index=GetPropIndex(sparamname);
	if(index>=0)
	{
		pparam=this->GetProperty(index);
		if(pparam && (pparam->GetType()==IO_PARAM_FLOAT))
		  *value=pparam->GetFloatParam();
		
	}
	return status;		
}



int CIoGenericSteerSimulation::GetParamInt(int *value, string sparamname)
{
	int status=0;
	CIoParam *pparam=NULL;
	
	int index=GetPropIndex(sparamname);
	if(index>=0)
	{
		pparam=this->GetProperty(index);
		if(pparam && (pparam->GetType()==IO_PARAM_INTEGER))
		  *value=pparam->GetIntParam();
		
	}
	return status;		
}

int CIoGenericSteerSimulation::GetParamString(string *value, string sparamname)
{
	int status=0;
	CIoParam *pparam=NULL;
	char *svalue;
	
	int index=GetPropIndex(sparamname);
	if(index>=0)
	{
		pparam=this->GetProperty(index);
		if(pparam && (pparam->GetType()==IO_PARAM_STRING))
		  svalue=pparam->GetStringParam();
		*value=svalue;
		
	}
	return status;		
}

int CIoGenericSteerSimulation::GetParamVec(double *value, int n, string sparamname)
{
	int status=0;
	CIoParam *pparam=NULL;
	vec *tvec=NULL;
	int i;
	
	int index=GetPropIndex(sparamname);
	if(index>=0)
	{
		pparam=this->GetProperty(index);
		if(pparam && (pparam->GetType()==IO_PARAM_VEC))
		  if(tvec=pparam->GetVecParam())
		  {
		  	for(i=0; i<tvec->length(), i<n; i++)
		  		value[i]=tvec->get(i);
		  	
		  }
		
	}
	return status;
}



int CIoGenericSteerSimulation::SetParamVec(double *value, int n, string sparamname, int iflag)
{
	int status=0;
	CIoParam *pparam=NULL;
	vec *tvec=NULL;
	int i;
	
	int index=GetPropIndex(sparamname);
	if(index>=0)
	{
		pparam=this->GetProperty(index);
		if(pparam && (pparam->GetType()==IO_PARAM_VEC))
		  if(tvec=pparam->GetVecParam())
		  {
		  	for(i=0; i<tvec->length(), i<n; i++)
		  		tvec->set(i,value[i]);		  	
		  }
		
	}
	return status;
}

int CIoGenericSteerSimulation::GetParamMat(double *value, int nr, int nc,string sparamname)
{
	int status=0;
	CIoParam *pparam=NULL;
	matrix *tmat=NULL;
	int i,j,index;
	index=0;
	int count=0;
	
	index=GetPropIndex(sparamname);
	if(index>=0)
	{
		pparam=this->GetProperty(index);
		if(pparam && (pparam->GetType()==IO_PARAM_MAT))
		  if(tmat=pparam->GetMatParam())
		  {
		  	int nrm=(tmat->depth() < nr?tmat->depth():nr);
		  	int nrc=(tmat->width() < nc?tmat->width():nc);
		  	for(i=0; i<nrm; i++)
		  		for(j=0; j<nrc; j++)
		  				value[count++]=tmat->getval(i,j);

		  	
		  }
		
	}
	return status;
}


int CIoGenericSteerSimulation::SetParamMat(double *value, int nr, int nc,string sparamname, int iflag)
{
	int status=0;
	CIoParam *pparam=NULL;
	matrix *tmat=NULL;
	int i,j,index=0;
	int count=0;
	index=GetPropIndex(sparamname);
	if(index>=0)
	{
		pparam=this->GetProperty(index);
		if(pparam && (pparam->GetType()==IO_PARAM_MAT))
		  if(tmat=pparam->GetMatParam())
		  {
		  	for(i=0; i<tmat->rows(), i<nr; i++)
		  		for(j=0; j<tmat->cols(), j<nc; j++)
		  				tmat->setval(i,j,value[count++]);

		  	
		  }
		
	}
	return status;
}

int CIoGenericSteerSimulation::GetParammmat3d(double *value, int n ,int p, int q, int nr, int nc,string sparamname)
{
	int status=0;
	CIoParam *pparam=NULL;
	mmat3d *tmat=NULL;
	int i,j,index=0;
	int i1,i2,i3;
	int count=0;
	index=GetPropIndex(sparamname);
	if(index>=0)
	{
		pparam=this->GetProperty(index);
		if(pparam && (pparam->GetType()==IO_PARAM_MMAT3D))
		  if(tmat=pparam->Getmmat3dParam())
		  {
		  	
		  	for(i1=0;i1<n;i1++)
				for(i2=0;i2<p;i2++)
					for(i3=0;i3<q;i3++)
		  				for(i=0; i<tmat->mrows(), i<nr; i++)
		  					for(j=0; j<tmat->mcols(), j<nc; j++)
					  				value[++count]=tmat->getval(i1,i2,i3,i,j);

		  	
		  }
		
	}
	return status;
}


int CIoGenericSteerSimulation::SetParammmat3d(double *value, int n ,int p, int q, int nr, int nc,string sparamname, int iflag)
{
	int status=0;
	CIoParam *pparam=NULL;
	mmat3d *tmat=NULL;
	int i,j,index=0;
	int i1,i2,i3;
	
	index=GetPropIndex(sparamname);
	int count=0;
	if(index>=0)
	{
		pparam=this->GetProperty(index);
		if(pparam && (pparam->GetType()==IO_PARAM_MMAT3D))
		  if(tmat=pparam->Getmmat3dParam())
		  {
		  	
		  	for(i1=0;i1<n;i1++)
				for(i2=0;i2<p;i2++)
					for(i3=0;i3<q;i3++)
		  				for(i=0; i<tmat->mrows(), i<nr; i++)
		  					for(j=0; j<tmat->mcols(), j<nc; j++)
					  				tmat->setval(i1,i2,i3,i,j,value[++count]);

		  	
		  }
		
	}
	return status;
}


int CIoGenericSteerSimulation::AddParamDouble(double value, string sparamname, int iflag)
{
	int status=0;
	CIoPropertyManager *ppropman=(CIoPropertyManager *)this;
	float vf=value;
	CIoParam par=new CIoParam(&vf);
	ppropman->AddProperty(&par);
	ppropman->AddPropName(sparamname.c_str());
	ppropman->AddPropFlag(iflag);

	m_pConstParams.push_back(&par); 
	m_pPropName.push_back(sparamname);
	m_pPropFlag.push_back(iflag);
	
	
	return status;	
}



int CIoGenericSteerSimulation::AddParamInt(int value, string sparamname, int iflag)
{
	int status=0;
	CIoPropertyManager *ppropman=(CIoPropertyManager *)this;
	int vf=value;
	CIoParam par=new CIoParam(&vf);
	ppropman->AddProperty(&par);
	ppropman->AddPropName(sparamname.c_str());
	ppropman->AddPropFlag(iflag);

	m_pConstParams.push_back(&par); 
	m_pPropName.push_back(sparamname);
	m_pPropFlag.push_back(iflag);
	
	
	return status;	
}

int CIoGenericSteerSimulation::AddParamString(string value, string sparamname, int iflag)
{
	int status=0;
	CIoPropertyManager *ppropman=(CIoPropertyManager *)this;
	char *vf=(char *)value.c_str();
	CIoParam par=new CIoParam(vf);
	ppropman->AddProperty(&par);
	ppropman->AddPropName(sparamname.c_str());
	ppropman->AddPropFlag(iflag);

	m_pConstParams.push_back(&par); 
	m_pPropName.push_back(sparamname);
	m_pPropFlag.push_back(iflag);
	
	
	return status;	
}



int CIoGenericSteerSimulation::AddParamVec(double *value, int n, string sparamname,int iflag)
{
	int status=0;
	CIoPropertyManager *ppropman=(CIoPropertyManager *)this;
	vec vf(n,0);
	for(int i=0; i<n;i++)
		if(value != NULL)
			vf.set(i,value[i]);

	CIoParam par=new CIoParam(&vf);
	ppropman->AddProperty(&par);
	ppropman->AddPropName(sparamname.c_str());
	ppropman->AddPropFlag(iflag);

	m_pConstParams.push_back(&par); 
	m_pPropName.push_back(sparamname);
	m_pPropFlag.push_back(iflag);
	
	
	return status;	
}




	
int CIoGenericSteerSimulation::AddParamMat(double *value, int nr, int nc, string sparamname,int iflag)
{
	int status=0;
	CIoPropertyManager *ppropman=(CIoPropertyManager *)this;
	matrix vf(nr,nc,0,0);
	int count=0;
	for(int i=0; i<nr;i++)
		for(int j=0; j<nc;j++)
				if(value != NULL)
					vf.setval(i,j,value[count++]);

	CIoParam par=new CIoParam(&vf);
	ppropman->AddProperty(&par);
	ppropman->AddPropName(sparamname.c_str());
	ppropman->AddPropFlag(iflag);

	m_pConstParams.push_back(&par); 
	m_pPropName.push_back(sparamname);
	m_pPropFlag.push_back(iflag);
	
	
	return status;
}




	
int CIoGenericSteerSimulation::AddParammmat3d(double *value, int n, int p, int q, int nr, int nc, string sparamname, int iflag)
{
	int status=0;
	CIoPropertyManager *ppropman=(CIoPropertyManager *)this;
	mmat3d *tmat=NULL;
	mmat3d vf(n,p,q,nr,nc,0,0);

	int i,j,index=0;
	int i1,i2,i3;
	

		
		  if(tmat=&vf)
		  {
		  	
		  	for(i1=0;i1<n;i1++)
				for(i2=0;i2<p;i2++)
					for(i3=0;i3<q;i3++)
		  				for(i=0; i<nr; i++)
		  					for(j=0;  j<nc; j++)
					  		{
					  				tmat->setval(i1,i2,i3,i,j,value[index]);
					  				index++;
					  		}
		  	
		  }
		
	


	CIoParam par=new CIoParam(&vf);
	ppropman->AddProperty(&par);
	ppropman->AddPropName(sparamname.c_str());
	ppropman->AddPropFlag(iflag);

	m_pConstParams.push_back(&par); 
	m_pPropName.push_back(sparamname);
	m_pPropFlag.push_back(iflag);
	
	
	return status;
}

int CIoGenericSteerSimulation::CreateSimulation(char *sFilename)
{
	int status = 1;
	//CIoAgentSimulator *pSimulator=NULL;
	//CIoAgentModel *pModel = NULL;
	DeleteSimulant();
	DeleteSimulantStates();
	DeleteNames();
	DeleteFlags();
	DeleteMetadata();
	if(m_pProperties)
		delete m_pProperties;
	m_pProperties=new CIoParam;




    if(sFilename)
	{
		//free the parameters
		ReadSimulation(sFilename);
		//CreateConfig();
		//This will usually be called by a CreateSimulation Command
		//call create CIoSimulation::CreateSimulation
		//pModel = (CIoAgentModel *)(GetSimulator()->GetSimulant());
	//	if(pModel && (pModel->GetCreateMethod()==0))
	//					pModel->CreateAgentModelConfig();
		//if simulant is model if creator type is !=0 then create model
		//alternatively we just read the configuration from the config file

		//if simulant is simulator then check each model of the simulator
		//in turn for its creation method


	}
	//else
	//{
	//	CreateDefaultParams();
		//pSimulator=new CIoAgentSimulator;
		//pSimulator->CreateDefaultParams();
		//pSimulator->CreateSimulant();
		//m_pSimulant = pSimulator;
        //pModel=(CIoAgentModel *)this->newModel("AgentModel");
		//pModel = new CIoAgentModel(this);
		//pModel->CreateDefaultParams(); //unnecessary create model will do this
		//pModel->Create();
		//m_pSimulant = pModel;

	//	this->Create();


		//m_pSimulant->Add(pModel);
	//pModel->CreatePropArrayNames();
	//						pModel->CreatePropNames();
	//						pModel->CreatePropArrayFlags();
	//						pModel->CreatePropFlags();
		//CreateConfig();
	//	WriteSimulation();
	//}

	return status;
}

void CIoGenericSteerSimulation::RunSimulationStep(int iStepNum)
{
	int iresult=0;
	char *args=NULL;
	
	#ifndef IO_MSVC
		//char *path="$IOME_HOME/bin/jjobrun";
		char *path="iogenericsimstep.sh";
	#else
		//char *path="$IOME_HOME\bin\jjobrun";
		char *path="iogenericsimstep.bat";
	#endif
	//Run the model
	int pid,status,procstatus=0;
	
	//int pid,status,procstatus=0;
	
	//unix/linux/cygwin process call
	try
	{
	#ifndef IO_MSVC
		/*if((pid=fork())<0)
		         procstatus=-1;*/
		         
		//if( (procstatus==0))
		//{
		//	if((pid==0) )
		//	{
			       //the file to be executed
			       //and the parameters passed to the command
		//	       execvp(path,(char * const *)args);	
		//	}
			
		//	while(wait(&status) != pid)
		//	           ;/*do nothing*/
		//}
		system("../iogenericsimstep.sh");
	//windows process call
	#else
		//_flushall();
		//pid=_spawnv(_P_NOWAIT, path, (const char * const *)args);
		//if(pid != -1)
		//	_cwait(&status, pid, _WAIT_CHILD);
		system("../\iogenericsimstep.bat");
	#endif
	}
	catch(int j)
	{
      printf("Run Generic Simulation Step failed!");

	}
	
}

void CIoGenericSteerSimulation::RunSimulation()
{
	int iresult=0;
	const char *args=NULL;

		//19/06/2009 tasks outstanding
	//set the simulation name to the name sim jobid
	//set the filename to simname.xml
	//the simfilename should be the jobid .xml
	//the simulation name is set to jobid
	//pass the name of the simulation into the jobscript 
	//the name will be the jobid and the time stamp
	

	//Run the model
	int pid,status,procstatus=0;
	
	//int pid,status,procstatus=0;
	
	//unix/linux/cygwin process call
	try
	{
	#ifndef IO_MSVC
		//system("./iogenericsim.sh");
		pid=fork();
		if(pid !=0)
			m_ipid=pid;
		execl( "./iogenericsim.sh", "iogenericsim.sh", NULL );
		/*if((pid=fork())<0)
		         procstatus=-1;
		         
		if( (procstatus==0))
		{
			if((pid==0) )
			{
			       //the file to be executed
			       //and the parameters passed to the command
			       //execvp(path,(char * const *)args);
				;
			}
			
			//while(wait(&status) != pid)
			//           ;/*do nothing*/
		/*}*/
	//windows process call
	#else
		//system("iogenericsim.bat");	
		//_execl( "iogenericsim.bat", "iogenericsim.bat", NULL );
	//_flushall();
		m_ipid=_spawnl(_P_NOWAIT, "iogenericsim.bat", "iogenericsim.bat",NULL);

		//if(pid != -1)
		//	_cwait(&status, pid, _WAIT_CHILD);
	//;
		
	#endif
	}
	catch(int j)
	{
      printf("Run Generic Simulation  failed!");

	}	

}

int CIoGenericSteerSimulation::AddNode(int port, string server, int numsubprocs)
{
	struct nodeinfo *node=(struct nodeinfo *)malloc(sizeof(struct nodeinfo));
	node->portid=port;
	node->server=(char *)calloc(1+server.size(),sizeof(char));
	strcpy(node->server,server.c_str());
	node->numsubprocs=numsubprocs;
	m_pnodes.insert(m_pnodes.end(),node);
	return(m_pnodes.size()-1);

}

int CIoGenericSteerSimulation::GetNodePort(int id)
{
  int port=8080;
  if(id<m_pnodes.size())
	  return((NODEINFOPTR)m_pnodes[id])->portid;
  else
	  return port;
}

char *CIoGenericSteerSimulation::GetNodeServer(int id)
{
  char *sloc="localhost";
  if(id<m_pnodes.size())
	  return (char *)((NODEINFOPTR)m_pnodes[id])->server;
  else
	  return sloc;

}

int CIoGenericSteerSimulation::GetNumServerNodes()
{
	return m_pnodes.size();
}

int CIoGenericSteerSimulation::GetNumSubProcs(int id)
{
  if(id<m_pnodes.size())
	  return (int)((NODEINFOPTR)m_pnodes[id])->numsubprocs;
  else
	  return 1;
}


int CIoGenericSteerSimulation::AddJob(int procid, int subprocid)
{
	struct jobinfo *job=(struct jobinfo *)malloc(sizeof(struct jobinfo));
	job->procid=procid;
	job->subprocid=subprocid;
	
	m_pjobs.insert(m_pjobs.end(),job);
	return(m_pjobs.size()-1);
}

int CIoGenericSteerSimulation::GetJobProcid(int id)
{
  int pid=0;
  if(id<m_pjobs.size())
	  return((JOBINFOPTR)m_pjobs[id])->procid;
  else
	  return pid;

}

int CIoGenericSteerSimulation::GetJobSubprocid(int id)
{
  int pid=0;
  if(id<m_pjobs.size())
	  return((JOBINFOPTR)m_pjobs[id])->subprocid;
  else
	  return pid;

}

int CIoGenericSteerSimulation::GetJobPort(int id)
{
  int port=8080;
	int nid=0;

 if(id<m_pjobs.size())
	  nid= (int)((JOBINFOPTR)m_pjobs[id])->procid;
  else
	  return port;

  if(nid<m_pnodes.size())
	  return((NODEINFOPTR)m_pnodes[id])->portid;
  else
	  return port;


}

int CIoGenericSteerSimulation::GetJobid(int procid, int subprocid)
{
	int i=0;
	JOBINFOPTR jptr;

	for(i=0;i<m_pjobs.size(); i++)
	{
		jptr=  (JOBINFOPTR) m_pjobs[i];
		if(((jptr->procid)==procid) && ((jptr->subprocid)==subprocid))
			break;
	}

	return i;
}

char * CIoGenericSteerSimulation::GetJobServer(int id)
{
  char *sloc="localhost";
  int nid=0;

 if(id<m_pjobs.size())
	  nid= (int)((JOBINFOPTR)m_pjobs[id])->procid;
  else
	  return sloc;

  if(nid<m_pnodes.size())
	  return (char *)((NODEINFOPTR)m_pnodes[id])->server;
  else
	  return sloc;

}

int CIoGenericSteerSimulation::GetNumJobs()
{
	return m_pjobs.size();
}

int CIoGenericSteerSimulation::copynodes(vector<NODEINFOPTR> nodes)
{
	int status=0;
	vector<NODEINFOPTR>::iterator it;
    NODEINFOPTR nptr;
	m_pnodes.clear();
	for(it=nodes.begin(); it<nodes.end(); it++)
	{
		nptr=(NODEINFOPTR)(*it);
		AddNode(nptr->portid,nptr->server,nptr->numsubprocs);
	}

	return status;
}

int CIoGenericSteerSimulation::copyjobs(vector<JOBINFOPTR> jobs)
{
	int status=0;
	vector<JOBINFOPTR>::iterator it;
    JOBINFOPTR jptr;
	m_pjobs.clear();
	for(it=jobs.begin(); it<jobs.end(); it++)
	{
		jptr=(JOBINFOPTR)(*it);
		AddJob(jptr->procid,jptr->subprocid);
	}

	return status;
}

int CIoGenericSteerSimulation::DeleteParam(char *name)
{
		int status=0;

		string pstring;
	deque<string>::iterator  nameit;
	deque<CIoParam *>::iterator parit;
	deque<int>::iterator flagit;

    int icount=0;
	for(nameit=m_pPropName.begin(),parit=m_pConstParams.begin(),flagit=m_pPropFlag.begin();
		nameit!=m_pPropName.end(),parit!=m_pConstParams.end(),flagit!=m_pPropFlag.end();
		nameit++, parit++, flagit++)
//for(nameit=m_pPropName.begin();
//		nameit=m_pPropName.end();
//		nameit++)

	{
			
		pstring = (string) (*nameit);
		if(strcmp(pstring.c_str(), name)==0)
		{
			m_pPropName.erase(nameit);
			m_pConstParams.erase(parit);
			m_pPropFlag.erase(flagit);

			DeleteProp(icount);
			DeletePropFlag(icount);
			DeletePropName(icount);
			break;


		}
		icount++;
	}
		return status;
}

void CIoGenericSteerSimulation::ListParam(char *type, char *slist)
{
	int index;
	string sname;
	

	CIoParam *pparam=NULL;
	
		
	for(index=0; index<m_pProperties->GetNumParams();index++)
	{
		if(index>=0)
		{
			pparam=GetProperty(index);
			sname=m_pPropName[index];
			if(pparam && (pparam->GetType()==IO_PARAM_FLOAT)  && (strcmp(type,"double")==0))
			{
			    
				strcat(slist, (char *)sname.c_str());
				strcat(slist, "\n");
				//float	value=pparam->GetFloatParam();
				//printf("%s",slist.c_str());

			}
			else if(pparam && (pparam->GetType()==IO_PARAM_INTEGER)  && (strcmp(type,"int")==0))
			{
				strcat(slist, (char *)sname.c_str());
				strcat(slist, "\n");

				//int	value=pparam->GetIntParam();

			}	
			else if(pparam && (pparam->GetType()==IO_PARAM_STRING)  && (strcmp(type,"string")==0))
			{
				strcat(slist, (char *)sname.c_str());
				strcat(slist, "\n");

				//char	*value=pparam->GetStringParam();

			}		
			else if(pparam && (pparam->GetType()==IO_PARAM_VEC)  && (strcmp(type,"vec")==0))
			{
				vec *value=pparam->GetVecParam();
				if(value)
				{
					char sv[20];
					sprintf(sv," %d \n",value->length());
					strcat(slist, (char *)sname.c_str());
					strcat(slist ,sv);
					//slist += " \n";
					//printf("%s",slist.c_str());

				}

			}
			else if(pparam && (pparam->GetType()==IO_PARAM_MAT)  && (strcmp(type,"mat")==0))
			{
				matrix	*value=pparam->GetMatParam();
				if(value)
				{
					char sv[200];
					sprintf(sv," %d %d \n",value->rows(),value->cols());
					strcat(slist, (char *)sname.c_str());
					strcat(slist ,sv);
					//slist += " \n";
				}

			}
			else if(pparam && (pparam->GetType()==IO_PARAM_MMAT3D)  && (strcmp(type,"mmat3d")==0))
			{
				mmat3d *value=pparam->Getmmat3dParam();
				if(value)
				{
					char sv[200];
					sprintf(sv," %d %d %d %d %d \n",value->rows(),value->cols(),value->depth(),value->mrows(),value->mcols());
					strcat(slist, (char *)sname.c_str());
					strcat(slist ,sv);
					//slist += " \n";
				}
			}
		}
	}

	//return (slist);

}












