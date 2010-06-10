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

// IoSimulation.cpp: implementation of the CIoSimulation class.
//
//////////////////////////////////////////////////////////////////////


#include <iome/simulation/IoSimulation.h>

/*!////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////*/
/*!Possible use cases
    1.  The simulation has a single model 
	2. The simulation has a collection of models
	   contained within a simulator


//////////////////////////////////////////////////////////////////
Read and write methods
/////////////////////////////////////////////////////////////////////


 \param ReadMethod=0 calls default read methods
 \param Read Method=1 reserved calls xml read method
 \param WriteMethod=0 calls default write methods
 \param WriteMethod=1 reserved calls xml write method

 \brief method indices > 1 may be used to call users defined read and write methods



//////////////////////////////////////////////////////////////////
Create methods
/////////////////////////////////////////////////////////////////////


 \param CreateMethod=0 is set when config is read from a file
 a default creation method must be provided
 if create config can't find a read config method then the default create method
 will be called

//////////////////////////////////////////////////////////////////
  Setting flags for writing to state, config or simulation files
/////////////////////////////////////////////////////////////////////
Available methods

(Sim, State, Config)Flag(on, off) toggles the flag for ith property or ith array 
\param bit0  = sim flag	  if(flag & 1) simflag-1 
\param bit1  = config flag  if(flag & 2) cfgflag-2
\param bit2  = state flag   if(flag & 4) cfgflag-4

\brief Get(Sim, Config, State)Flag)

*/
CIoSimulation::CIoSimulation()
{
	m_sConfigFileName = new char [100];
	m_sStateFileName = new char [100];
	m_idistributemethod=0; //0=local, 1=mpi, 2=pthread
	m_inumprocs=1;


	m_sHomeDir = new char [200];
	m_sOutputFiles = new char [100];

	m_sSimClass = new char [100];
	m_sSimulantClass = new char [100];
	m_sSimName = new char [100];

	//m_sConfigFileName [0] = '\0';
	//m_sStateFileName [0] = '\0';

	//m_sSimClass [100] = '\0';
	//m_sSimName [100] = '\0';
	//SetSimClass("Simulation");
	//SetSimName("DefaultSimulation");
	//SetConfigFileName("SimConfigFile");
	m_iNumSteps = 1;
	
	m_iCurrentStep=0;

	m_iSimType = 0;
	m_iSimulantType=0;
//	m_pSimulant = NULL;
	m_fVersion = 1.0;
	m_iCreateMethod = 1;  //default is to call the config creation method
	//m_sSimClass = "Simulation";
	m_isimreadmethod=m_istatereadmethod=m_iconfigreadmethod=0;
	m_isimwritemethod=m_istatewritemethod=m_iconfigwritemethod=0;

	m_iConfigStepFreq=1;
	m_iStateStepFreq=1;

	m_nprocs=1;
	m_irank=1;

	#ifdef USEMPI
		m_comm=MPI::COMM_WORLD;
		m_nprocs=m_comm.Get_size();
		m_irank=m_comm.Get_rank();
	#endif
	//SetOutputFiles("OutputResults.txt");



	//XMLPlatformUtils::Initialize();
				
	//m_pDOMImpl =  DOMImplementationRegistry::getDOMImplementation(X("Core"));

/*	try
	{
		XMLPlatformUtils::Initialize();
		XalanTransformer::initialize();
	}
   catch(const XMLException& toCatch)
    {
        char *pMsg = XMLString::transcode(toCatch.getMessage());
        /*cerr << "Error during Xerces-c Initialization.\n"
             << "  Exception message:"
             << pMsg;*/
       // delete [] pMsg;
   // }*/

}

CIoSimulation::~CIoSimulation()
{
	//CIoSimulant *pSimulant=NULL;
	//DeleteProperties();
	delete [] m_sSimName;
	delete [] m_sConfigFileName;
	delete [] m_sStateFileName;
	
	delete [] m_sHomeDir;

	delete [] m_sSimClass;
	delete [] m_sSimulantClass;
	
	//if(m_pSimulant)
	//	delete m_pSimulant;
	//DeleteSimulant();
		
	if(m_sOutputFiles)
		delete [] m_sOutputFiles;

	//DeleteSimulantStates();
	DeleteAllMetadata();



	
}



void CIoSimulation::AddMetadata(string sname, string scontent)
{
	CIoMetadata *pmetadata=new CIoMetadata(sname, scontent);
	m_lMetadataList.push_back(pmetadata);
}

void CIoSimulation::DeleteMetadata(string sname)
{

 	CIoMetadata *metadata=NULL;
	int i=0;

    for(m_lMetadataIterator=m_lMetadataList.begin(); m_lMetadataIterator != m_lMetadataList.end();m_lMetadataIterator++ ,i++ )
	{
		metadata=(CIoMetadata *)(*m_lMetadataIterator);
		if(metadata && ((metadata->m_sname).compare(sname)==0))
		{
							delete metadata;
							m_lMetadataList.erase(m_lMetadataIterator);
							return;
		}
										
	}

}

void CIoSimulation::DeleteAllMetadata()
{

 	CIoMetadata *metadata=NULL;
	int i=0;

    for(m_lMetadataIterator=m_lMetadataList.begin(); m_lMetadataIterator != m_lMetadataList.end();m_lMetadataIterator++ ,i++ )
	{
		metadata=(CIoMetadata *)(*m_lMetadataIterator);
		delete metadata;
		m_lMetadataList.erase(m_lMetadataIterator);										
	}

}

void CIoSimulation::ListMetadata(char *slist)
{
 	CIoMetadata *metadata=NULL;
	string sname;
	int i=0;

    for(m_lMetadataIterator=m_lMetadataList.begin(); m_lMetadataIterator != m_lMetadataList.end();m_lMetadataIterator++ ,i++ )
	{
		metadata=(CIoMetadata *)(*m_lMetadataIterator);
		sname=metadata->m_sname;
		strcat(slist, (char *)sname.c_str());
		strcat(slist, "\n");
	}
	
	
}

void CIoSimulation::SetMetadata(string sname, string scontent)
{
	string sresult;
	CIoMetadata *metadata=NULL;
	int i=0;

    for(m_lMetadataIterator=m_lMetadataList.begin(); m_lMetadataIterator != m_lMetadataList.end();m_lMetadataIterator++ ,i++ )
	{
		if((metadata=(CIoMetadata *)(*m_lMetadataIterator)) != NULL)
									if(sname.compare(metadata->m_sname)==0)
											(metadata->m_scontent)=scontent;
	}


}


string CIoSimulation::GetMetadata(string sname)
{

 	CIoMetadata *metadata=NULL;
	string svalue;
	int i=0;

    for(m_lMetadataIterator=m_lMetadataList.begin(); m_lMetadataIterator != m_lMetadataList.end();m_lMetadataIterator++ ,i++ )
	{
		metadata=(CIoMetadata *)(*m_lMetadataIterator);
		if(metadata && ((metadata->m_sname).compare(sname)==0))
										return (svalue=metadata->m_scontent);
	}

	if(metadata)
		svalue=metadata->m_scontent;
   return svalue;


}


CIoMetadata *CIoSimulation::GetMetadata(int index)
{
 	CIoMetadata *metadata=NULL;
	int i=0;

    for(m_lMetadataIterator=m_lMetadataList.begin(); m_lMetadataIterator != m_lMetadataList.end();m_lMetadataIterator++ ,i++ )
	{
		
		if((i==index)  &&  ((metadata=(CIoMetadata *)(*m_lMetadataIterator)) != NULL))
																	return metadata;
	}

   return metadata;
}


string CIoSimulation::GetMetadataContent(string sname)
{
	string sresult;
	CIoMetadata *metadata=NULL;
	int i;

    for(m_lMetadataIterator=m_lMetadataList.begin(); m_lMetadataIterator != m_lMetadataList.end();m_lMetadataIterator++ ,i++ )
	{
		if((metadata=(CIoMetadata *)(*m_lMetadataIterator)) != NULL)
									if(sname.compare(metadata->m_sname)==0)
											return(sresult=(metadata->m_scontent));
	}
	return sresult;

}




void CIoSimulation::CreatePropNames()
{
	AddPropName("TestInt1");
}

void CIoSimulation::CreatePropArrayNames()
{
	AddArrayName("SimtestProps");

}


void CIoSimulation::SetConfigFileName(const char *name)
{
	if(m_sConfigFileName) 
		strcpy(m_sConfigFileName, name);
}

void CIoSimulation::SetStateFileName(const char *name)
{
	if(m_sStateFileName) 
		strcpy(m_sStateFileName, name);

}



void CIoSimulation::SetSimClass(const char *name)
{
	//if(m_sSimClass)
	//	strcpy(m_sSimClass, name);
	if(m_sSimClass && name)
	{
		//delete [] m_sSimClass;
		//m_sSimClass = (char *) new char [1+strlen(name)];
		strcpy(m_sSimClass, name);
	}
}

void CIoSimulation::SetSimulantClass(const char *name)
{
	//if(m_sSimClass)
	//	strcpy(m_sSimClass, name);
	if(m_sSimulantClass && name)
	{
		//delete [] m_sSimulantClass;
		//m_sSimulantClass = (char *) new char [1+strlen(name)];
		strcpy(m_sSimulantClass, name);
	}
}

void CIoSimulation::SetSimName(char *name)
{
	if(m_sSimName && name)
	{
		//delete [] m_sSimName;
		//m_sSimName = (char *) new char [1+strlen(name)];
		strcpy(m_sSimName, name);
	}
}

void CIoSimulation::SetHomeDir(const char *name)
{
	if(m_sHomeDir && name)
	{
		//delete [] m_sHomeDir;
		//m_sHomeDir = (char *) new char [1+strlen(name)];
		strcpy(m_sHomeDir, name);
	}
}

void CIoSimulation::SetOutputFiles(const char *name)
{
	if(m_sOutputFiles && name)
	{
		//delete [] m_sOutputFiles;
		//m_sOutputFiles = (char *) new char [1+strlen(name)];
		strcpy(m_sOutputFiles, name);
		strcat(m_sOutputFiles, "_out.lis");
	}
}

int CIoSimulation::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=0;

	this->DeleteFlags();
	this->DeleteNames();
	this->CreatePropNames();
	this->CreatePropFlags();
	this->CreatePropArrayFlags();
	this->CreatePropArrayNames();


	this->UpdateProperties(pParams);

	CIoParam *p1=NULL, *p2=NULL;
	if(pArray && (pArray->GetType()==IO_PARAM_ARRAY) && ((pArray->GetNumParams())==2))
	{
		p1=pArray->GetParamArray(0);
		p2=pArray->GetParamArray(1);
	}

	


	return status;

}









void CIoSimulation::CreateDefaultParams()
{
	CIoParam *pSimProperties, *pInteger;
    int i=1;

    pInteger = new CIoParam;
	pInteger->SetParam(&i);

	pSimProperties = new CIoParam;
	pSimProperties->AddParam(pInteger);

    CreateProperties(pSimProperties);

	pSimProperties->DeleteParams();
	delete pSimProperties;
	delete pInteger;
}

void CIoSimulation::SetSimProperties(CIoParam *pSimProperties)
{

	if(pSimProperties && CheckParamFormat(pSimProperties))
								CreateProperties(pSimProperties);

}

int CIoSimulation::ReadSimulation(char *sSimFilename)
{
	int status = 0;
	
    ReadSimulationDefault(sSimFilename);
	//This will uually be called by a CreateSimulation Command
	//call create CIoSimulation::CreateSimulation
	//Normally select config read method according to readmethod
    //if(m_iCreateMethod == 0)
	//	status=this->ReadConfig(m_sConfigFileName,m_iconfigreadmethod);  //Has virtual override pickup the correct method
	
	//if simulant is model if creator type is !=0 then create model


	//if simulant is simulator then check each model of the simulator
	//in turn for its creation method

	return status;
}

int CIoSimulation::ReadSimulationDefault(char *sSimFilename)
{
	int status=1;
	int i=0;
	int istep;
	
	if(sSimFilename)
	{
		::ifstream ifs(sSimFilename, ::ios::in);
		
		if(!ifs)
		{
			::cerr << "Failed to find simulation file.\n";
			return 1;			
		}
		//skip comments
		skipcmt(ifs);
		//name
		skipcmt(ifs);
		ifs>>m_sSimName;
		
		//class
		skipcmt(ifs);
		ifs>>m_sSimClass;
		
		//simulanttype
		skipcmt(ifs);
		ifs>>m_iSimulantType;
		
		skipcmt(ifs);
		//simulantclass
		ifs>>m_sSimulantClass;


		skipcmt(ifs);
		//configfilename
		ifs>>m_sConfigFileName;


		//statefilename
		skipcmt(ifs);
		ifs>>m_sStateFileName;

		skipcmt(ifs);
		//createmethod
		ifs>>m_iCreateMethod;

		skipcmt(ifs);
		//readmethod
		ifs>>m_isimreadmethod;

		skipcmt(ifs);
		//writemethod
		ifs>>m_isimwritemethod;



		skipcmt(ifs);
		//steps

			ifs>>istep;
			SetNumSteps(istep);
		


		skipcmt(ifs);

		skipcmt(ifs);
		//configstepfreq
		ifs>>m_iConfigStepFreq;


		skipcmt(ifs);
		//statestepfreq
		ifs>>m_iStateStepFreq;

        //simulation prop names
		skipcmt(ifs);//skip line of prop names
		CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumPropNames(); i++)
			pTempParam->AddParam("TempName");

		pTempParam->ReadParam(ifs,pTempParam->GetNumParams() );
		delete pTempParam;

		//simulation prop array names
		skipcmt(ifs);
		pTempParam=new CIoParam();
		for(i=0; i<GetNumArrayNames(); i++)
			pTempParam->AddParam("TempName");

		pTempParam->ReadParam(ifs,pTempParam->GetNumParams() );
		delete pTempParam;

		//Read properties
		skipcmt(ifs);
		ReadProps(ifs, GetNumProps());

		//Read the flags for the properties
		//these will be used to determine which
		//properties get read from and writtent to config files and state files
		skipcmt(ifs);
		pTempParam=new CIoParam();
		for(i=0; i<GetNumPropFlags(); i++)
			pTempParam->AddParam(&i);

		pTempParam->ReadParam(ifs,pTempParam->GetNumParams() );
		for(i=0; i<GetNumPropFlags(); i++)
			this->SetPropertyFlag(i, pTempParam->GetIntParam(i));
		delete pTempParam;
		//m_pPropFlags->ReadParam(ifs, m_pPropFlags->GetNumParams());
		skipcmt(ifs);
		
		pTempParam=new CIoParam();
		for(i=0; i<GetNumArrayFlags(); i++)
			pTempParam->AddParam(&i);

		pTempParam->ReadParam(ifs,pTempParam->GetNumParams() );
		for(i=0; i<GetNumArrayFlags(); i++)
			this->SetArrayFlag(i, pTempParam->GetIntParam(i));
		delete pTempParam;		

		//simulantreadmethod

		//simulant has been created
		//if(m_pSimulant)
		//	m_pSimulant->ReadSimulantDefault(ifs);
		//no simulant created


	}


	return status;
}

int CIoSimulation::WriteSimulationDefault(char *sSimFilename)
{
	int status=1;
	int i=0;
	int istep;
	
	if(sSimFilename)
	{
		::ofstream ofs(sSimFilename, ::ios::out);
		
		if(!ofs)
		{
			::cerr << "Failed to find simulation file.\n";
			return 1;			
		}
		//skip comments
		ofs << "#Put comments here on this line only" << ::endl;
		
		//name
		ofs<< "#Simulation name: " << ::endl;
		ofs<<m_sSimName<< ::endl;
		
		//class
		ofs<<"#Simulation class:" << ::endl;
		ofs<<m_sSimClass<< ::endl;
		
		//simulanttype
		ofs << "#Simulant type:" << ::endl;
		ofs<<m_iSimulantType<< ::endl;
		
		
		//simulantclass
		ofs<< "#Simulant class:" << ::endl;
		ofs<<m_sSimulantClass<< ::endl;


		
		//configfilename
		ofs << "#Config filename:" << ::endl;
		ofs<<m_sConfigFileName<< ::endl;


		//statefilename
		ofs << "#state filename:"<< ::endl;
		ofs<<m_sStateFileName<< ::endl;

		//createmethod
		ofs << "#Create method:" << ::endl;
		ofs<<m_iCreateMethod<< ::endl;

		
		//readmethod
		ofs<<"#SimRead method:" << ::endl;
		ofs<<m_isimreadmethod<< ::endl;
		
		//writemethod
		ofs<<"#SimWrite method:" << ::endl;
		ofs<<m_isimwritemethod<< ::endl;


		ofs<< "#Num steps:" << ::endl;
			ofs<<m_iNumSteps<<" ";
		ofs << ::endl;
		


		

		//configstepfreq
		ofs<<"#Config step freq:" << ::endl;
		ofs<<m_iConfigStepFreq<< ::endl;

		
		//statestepfreq
		ofs<<"#State step freq:" << ::endl;
		ofs<<m_iStateStepFreq<< ::endl;

        //read simulation props
		//write sim param names
		ofs<<"#Sim param names"<<::endl;
		WritePropNames(ofs);
		//write sim param array names
		ofs<<"#sim param array names"<< ::endl;

		WriteArrayNames(ofs);
		ofs<<"#Simulation properties: " << ::endl;
		WriteProps(ofs, GetNumProps());

		ofs<<"#Simulation prop flags: " << ::endl;
		WritePropFlags(ofs);		

		ofs<<"#Simulation prop array flags: " << ::endl;
		WriteArrayFlags(ofs);

		//simulantreadmethod

		//simulant has been created
		//if(m_pSimulant)
		//	m_pSimulant->WriteSimulantDefault(ofs);
		//no simulant created
		

	}


	return status;
}


int CIoSimulation::WriteSimulation(char *sSimFilename, char *sXSLFilename)
{
	int status=1;
	char sxml[] = ".xml";
	char *sTempFilename=NULL;
	
	if(sSimFilename == NULL)
	{
		sTempFilename = (char *)new char [4+strlen(m_sSimName)];
		sprintf(sTempFilename, "%s%s",m_sSimName,sxml); 
		//sSimFilename = strcat(m_sSimName,sxml);
		sSimFilename = sTempFilename;
	}
	WriteSimulationDefault(sSimFilename);

	if(sTempFilename) delete [] sTempFilename;
	return status;

}






#ifdef USEMPI

	int CIoSimulation::SendRecvSimulationParam(int fromproc, int toproc, int iparamid,  char *sparammap)
	{
		int status=0;
		CIoParam *pparam=NULL;
		int sval;
		float sfval;
		float rfval;
		int rval;

		if((m_irank==fromproc) && (pparam=GetChildParam(iparamid, sparammap))!=NULL)
		{
				switch(pparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=pparam->GetIntParam();
						m_comm.Send(&sval,1,MPI::INT,toproc,1);
					break;
				case IO_PARAM_FLOAT:
						sfval=pparam->GetFloatParam();
						m_comm.Send(&sfval,1,MPI::FLOAT,toproc,1);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
		}


	if((m_irank==toproc) && (pparam=GetChildParam(iparamid, sparammap))!=NULL)
			{
				//void MPI::Comm::Recv(void* buf, int count, const MPI::Datatype& datatype, int source, int tag) const
				switch(pparam->GetType())
				{
				case IO_PARAM_INTEGER:
					    
						m_comm.Recv(&rval, 1,MPI::INT,fromproc,1);
						pparam->SetParam(&rval);
					break;
				case IO_PARAM_FLOAT:
					    
						m_comm.Recv(&rfval, 1,MPI::FLOAT,fromproc,1);
						pparam->SetParam(&rfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}



		return status;
	}

	//param arays not yet sent simple loop
	int CIoSimulation::SendRecvSimulationParams(int fromproc, int toproc)
	{
		int status=0;
		char *parammap=NULL;
		for(int i=0; i<GetNumProps(); i++)
			SendRecvSimulationParam(fromproc, toproc, i,parammap);

		return status;
	}

	//param arays not yet sent simple loop
	int CIoSimulation::BroadcastSimulationParams(int fromproc)
	{
		int status=0;
		char *parammap=NULL;
		for(int i=0; i<GetNumProps(); i++)
			BroadcastSimulationParam(fromproc, i,parammap);

		return status;
	}

	int CIoSimulation::BroadcastSimulationParam(int fromproc, int iparamid, char *sparammap)
	{
		int status=0;
		CIoParam *pparam=NULL;
		int sval;
		float sfval;
		float rfval;
		int rval;

		if(( (pparam=GetChildParam(iparamid, sparammap))!=NULL))
		{
				switch(pparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=pparam->GetIntParam();
						m_comm.Bcast(&sval,1,MPI::INT,fromproc);
					break;
				case IO_PARAM_FLOAT:
						sfval=pparam->GetFloatParam();
						m_comm.Bcast(&sfval,1,MPI::FLOAT,fromproc);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
		}

		return status;
	}

	int CIoSimulation::BroadcastStep(int fromproc)
	{
		int status=0;
		int sval=GetCurrentStep();
		m_comm.Bcast(&sval,1,MPI::INT,fromproc);

		if(m_irank != fromproc)
			this->SetCurrentStep(sval);

		return status;

	}

	int CIoSimulation::BroadcastNSteps(int fromproc)
	{
		int status=0;
		int sval=GetNumSteps();
		m_comm.Bcast(&sval,1,MPI::INT,fromproc);

		if(m_irank != fromproc)
			SetNumSteps(sval);
		return status;

	}

#endif
























