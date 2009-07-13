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


#include "IoSimulation.h"

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
	m_pSimulant = NULL;
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
	DeleteProperties();
	delete [] m_sSimName;
	delete [] m_sConfigFileName;
	delete [] m_sStateFileName;
	
	delete [] m_sHomeDir;

	delete [] m_sSimClass;
	delete [] m_sSimulantClass;
	
	//if(m_pSimulant)
	//	delete m_pSimulant;
	DeleteSimulant();
		
	if(m_sOutputFiles)
		delete [] m_sOutputFiles;

	DeleteSimulantStates();



	
}

void CIoSimulation::DeleteSimulantStates()
{
	CIoSimulant *pSimulant;
	while(m_lSimStateList.size()>0) 
	{
		if(pSimulant=(*m_lSimStateList.begin()))
			delete pSimulant;
	}
}

void CIoSimulation::AddSimulantState(CIoSimulant *pSimulant)
{
	if(pSimulant)
		m_lSimStateList.push_back(pSimulant);
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
							m_lMetadataList.erase(m_lMetadataIterator);
							return;
		}
										
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


CIoSimulant *CIoSimulation::GetSimulantState(int index)
{
	CIoSimulant *pSimulant=NULL;
	int i=0;

	for(m_lSimStateIterator=m_lSimStateList.begin(); m_lSimStateIterator != m_lSimStateList.end(), i<=index;m_lSimStateIterator++ ,i++ )
		pSimulant=(CIoSimulant *)(*m_lSimStateIterator);
		
	return pSimulant;
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
		delete [] m_sSimClass;
		m_sSimClass = (char *) new char [1+strlen(name)];
		strcpy(m_sSimClass, name);
	}
}

void CIoSimulation::SetSimulantClass(const char *name)
{
	//if(m_sSimClass)
	//	strcpy(m_sSimClass, name);
	if(m_sSimulantClass && name)
	{
		delete [] m_sSimulantClass;
		m_sSimulantClass = (char *) new char [1+strlen(name)];
		strcpy(m_sSimulantClass, name);
	}
}

void CIoSimulation::SetSimName(char *name)
{
	if(m_sSimName && name)
	{
		delete [] m_sSimName;
		m_sSimName = (char *) new char [1+strlen(name)];
		strcpy(m_sSimName, name);
	}
}

void CIoSimulation::SetHomeDir(const char *name)
{
	if(m_sHomeDir && name)
	{
		delete [] m_sHomeDir;
		m_sHomeDir = (char *) new char [1+strlen(name)];
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




	/*!A virtual method that can be overridden method to create a simulation
    from simulation read in from XML file
	The default here is false to indicate that a simulation 
	was not created
	The user is not forced to use an XML parser
	may use their custom parser
	we'll always default to the case where simulation is created using default parameters
	*/
/*!A simulation consists of a singlemodel 
	This will probably be th case for most simulations
	virtual int CreateSimModel( CIoParam *pSimulationParams = NULL,
								  CIoParam *pModelParams = NULL,
							      CIoParam *pEntitySetParams = NULL,
							      CIoParam *pEntityTypeSetParams=NULL);

    This is use case 2 in which a simulation has a
	simulator with multiple models
	Will probably be of most use for discrete cell models
	Create  Simulation  reads an CIoParam of the following format
	ALWAYS IS AN ARRAY CONTAINING TWO ENTRIES
	the first entry is parameter array for the simulation parameters
	the second entry is the parameter array passed on for
	creation of simulators
	virtual int CreateSimSimulator(CIoParam *pSimulationParams=NULL,
									CIoParam *pSimulatorParams=NULL, 
									CIoParam *pSimulatorChildParams=NULL);


	//Method will attempt too create
    */
	/*!
	*****************************************************************
	Creating a Simulation

	1. Create an instance of a simulation then call create method
	   passing to this simulation parameters an, model parameters
	   and simulator params as required

    2. Call create entity sets method pass the number of entity sets required
	a param array containg class names of simulants
	pass the entity set and entity type set parameters

	I f an entity set does not possess an entity type set
	then these parameters are passed as null

	If simulant has only one entity set we pass just the param array
	otherwise we pass an array of param arrays
	
	********************************************************************
	*/

    /*!
	NOTE:CREATING PARAM ARRAYS FOR THE OBJECT TYPES
	This is easy to do sice all objects have a create defualt param methods
	To create a template array for an object
    Create the object

	e.g.

	pTempModel=newModel("Modelclassname")
	pTempModel->CreateDefaultParams();

	CIoParam *MyParam=new CIoParam(pTempModel->m_pProperties)
	delete Model;

	EntitySet create the model then call create entit set method
	andget default parameters for this and entity type set params
	as required

	Now: Modify these parameter arrays and construct 
	In put parameter arrays as required by the Create functions
	
	
	*/


	/*!

		The simulation must set the simulant type and class
		and most override the appropriate newSimulator
		or newModel method.

		Creates hierarchy of Simulants, EntitySets and Entity type sets
		required by CreateConfig

		Assumes m_pSimulant is NULL
	*/

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

	if(GetSimulantType()==IO_SIMULANT_TYPE_MODEL)
		m_pSimulant=(this->newModel(GetSimulantClass()));
	else if(GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR)
		m_pSimulant=(this->newSimulator(GetSimulantClass()));


	if(m_pSimulant)
	{
		m_pSimulant->SetParentSimulation(this);
		m_pSimulant->Create(pChildParams,p1,p2);
		m_pSimulant->SetCreateMethod(m_iCreateMethod);
	}
	else
		status=1;



	return status;

}




int CIoSimulation::CreateConfig()
{
	int status=0;
	if(GetCreateMethod()>0)
		status=m_pSimulant->CreateConfig();
	else
		status=ReadConfig(GetConfigFileName(), GetConfigReadMethod());

	return status;
}

int CIoSimulation::CreateEntitySets(int iNumES, CIoParam *pESClassName, CIoParam *pESParam, CIoParam *pETSParam , char *cESMap)
{
	int status = 1;  //false No default config created
    if(m_pSimulant)
	{
		m_pSimulant->SetCreateMethod(m_iCreateMethod);
		m_pSimulant->CreateEntitySets(iNumES, pESClassName, pESParam, pETSParam, cESMap);
	}

	return status;
}



CIoModel *CIoSimulation::GetModel(int i)
{
	CIoModel *pModel =NULL;
	CIoSimulant *pSimulant = m_pSimulant;
	
	if(pSimulant) pSimulant = pSimulant->GetSimulant(i);

	if(pSimulant && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_MODEL))
										pModel = (CIoModel *)pSimulant;
	return pModel;
}

//Get the ith simulator
CIoSimulator *CIoSimulation::GetSimulator(int i)
{
	CIoSimulator *pSimulator = NULL;

	CIoSimulant *pSimulant = m_pSimulant;

	if(pSimulant) pSimulant = pSimulant->GetSimulant(i);

	if(pSimulant && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
										pSimulator = (CIoSimulator *)pSimulant;

	return pSimulator;
}

CIoModel *CIoSimulation::GetChildModel(int i, char *cSimulantMap)
{
	CIoModel *pModel = NULL;
	CIoSimulant *pSimulant = GetChildSimulant(i, cSimulantMap); 

	if(pSimulant && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_MODEL))
										pModel = (CIoModel *)pSimulant;

	return pModel;
}

CIoSimulator *CIoSimulation::GetChildSimulator(int i, char *cSimulantMap)
{
	CIoSimulator *pSimulator = NULL;
	CIoSimulant *pSimulant = GetChildSimulant(i, cSimulantMap); 

	if(pSimulant && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
										pSimulator = (CIoSimulator *)pSimulant;

	return pSimulator;
}

CIoSimulant *CIoSimulation::GetChildSimulant(int i, char *cSimulantMap)
{
	CIoSimulant *pSimulant = NULL;

	char seps[] = " ,\t\n";
	int depth, index;
	int j=0;
	int *iarray;
	char *tokenptr;
	char *s;

	CIoSimulant *pCurrentSimulant = NULL;

    if(cSimulantMap)
	{
		s = new char [1+strlen(cSimulantMap)];
		//First read the Simulanteter map 
		strcpy(s, cSimulantMap);

		//Find the Simulanteter!
		index=0;

		tokenptr = strtok(s, seps);
		if((depth=atoi(tokenptr))<1) depth =1;
		
		iarray = new int [depth];

		while(tokenptr !=NULL)
		{
			tokenptr = strtok(NULL, seps);
			if(j<depth)
				iarray [j]=atoi(tokenptr);

			j++;
		}

		j=1;
		if(m_pSimulant)
			pSimulant = m_pSimulant->GetSimulant(iarray[0]);
		do
		{
			index=iarray[j];
			pSimulant = pSimulant->GetSimulant(index);
		}while(++j<depth && pSimulant !=NULL);

		delete [] s;
		delete [] iarray;

		if(pSimulant)
			return (pSimulant->GetSimulant(i));
		else
			return NULL;
	}
	else
		return (m_pSimulant==NULL?NULL:m_pSimulant->GetSimulant(i));
	return pSimulant;
}

CIoEntitySet *CIoSimulation::GetEntitySet(int i, char *csimulantmap)
{
	CIoEntitySet *pEntitySet = NULL;
	CIoModel *pModel = GetChildModel(i, csimulantmap);

	if(pModel)
		pEntitySet = pModel->GetEntitySet();

	return pEntitySet;
}

CIoEntity *CIoSimulation::GetEntity(int i, int iEntityIndex, char *csimulantmap)
{
	CIoEntity *pEntity = NULL;
	CIoEntitySet *pEntitySet = GetEntitySet(i, csimulantmap);

	if(pEntitySet)
		pEntity = pEntitySet->GetEntity(iEntityIndex);

	return pEntity;
}

CIoEntityTypeSet *CIoSimulation::GetEntityTypeSet(int i, char *csimulantmap)
{
	CIoEntityTypeSet *pEntityTypeSet = NULL;
	CIoModel *pModel = GetChildModel(i, csimulantmap);

	if(pModel)
		pEntityTypeSet = pModel->GetEntityTypeSet();
		
	return pEntityTypeSet;
}

CIoEntityType *CIoSimulation::GetEntityType(int i, int iEntityType, char *csimulantmap)
{
	CIoEntityType *pEntityType=NULL;
	CIoEntityTypeSet *pEntityTypeSet = GetEntityTypeSet(i, csimulantmap);

	if(pEntityTypeSet) pEntityType = pEntityTypeSet->GetEntityType(iEntityType);

	return pEntityType;
}






void CIoSimulation::RunSimulation()
{
	int i, j, iNumSteps;

		for(j=0; j<m_iNumSteps; j++)
		{
			RunSimulationStep(j);

			//Write the state data

			//Write the config data

		}
	


}

void CIoSimulation::RunSimulationStep(int iStepNum)
{
	char sconfigname [100];
	char sstatename [100];
	int i;
	char slisname [100];

	SetCurrentStep(iStepNum);
	if(m_pSimulant)
	{
		m_pSimulant->SetCurrentStep(iStepNum);
		m_pSimulant->SetNumSteps(m_iNumSteps);
		

		m_pSimulant->RunSimulantStep();
		//m_pSimulant->HandleInteractions();
		//m_pSimulant->HandleModelInteractions();
		//m_pSimulant->HandleStateTransitions();

		//Add the file with the list of configuration files to the 
		//list of output files but only if this is the first simulation step!
		if(iStepNum==0)
		{
			strcpy(slisname, m_sSimName);
			strcat(slisname, ".lis");
			//CIoFileUtils cOutFileList(GetOutputFiles(), 'a');
			//cOutFileList.WriteLine(slisname);
		}
			
			//if using MPI only proc rank 0 writes the state
			#ifdef USEMPI
				if(m_irank==0)
				{
			#endif
				if(m_sStateFileName && (strlen(m_sStateFileName)>0))
				{

					
					i=0;
					while((i <99) && (m_sStateFileName[i] !='.') && (m_sStateFileName[i]!='\0'))
						sstatename[i++]=m_sStateFileName[i];
					sstatename[i]='\0';

					sprintf(sstatename, "%s.xml",sstatename);
					//output config file and state file

						if(m_iStateStepFreq>0 && (((iStepNum%m_iStateStepFreq)==0) || (iStepNum==m_iNumSteps)))
				  			WriteState(sstatename, m_istatewritemethod, NULL, iStepNum);


				}
			#ifdef USEMPI
				}//end of testing irank
			#endif

		if(m_sConfigFileName && (strlen(m_sConfigFileName)>0))
		{
			i=0;
			while((i <99) && (m_sConfigFileName[i] !='.') && (m_sConfigFileName[i]!='\0'))
				sconfigname[i++]=m_sConfigFileName[i];
			sconfigname[i]='\0';
	#ifdef USEMPI
			sprintf(sconfigname, "%s_s%d_p%d.xml",sconfigname,iStepNum,m_irank);
	#else

			sprintf(sconfigname, "%s_s%d.xml",sconfigname,iStepNum);
	#endif
				if(m_iConfigStepFreq>0 && ((iStepNum%m_iConfigStepFreq)==0))
						WriteConfig(sconfigname, m_iconfigwritemethod, NULL, iStepNum);

		
		}
	}
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
    if(m_iCreateMethod == 0)
		status=this->ReadConfig(m_sConfigFileName,m_iconfigreadmethod);  //Has virtual override pickup the correct method
	
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
		if(m_pSimulant)
			m_pSimulant->ReadSimulantDefault(ifs);
		//no simulant created
		else
		{


			//calling the create function here
			//responsibility for creation of the complete hierarchy of objects
			//with their defualt values
			switch(m_iSimulantType)
			{
				case IO_SIMULANT_TYPE_MODEL :
					m_pSimulant=this->newModel(m_sSimulantClass);
					((CIoModel *)m_pSimulant)->Create();
				break;
				case IO_SIMULANT_TYPE_SIMULATOR :
					m_pSimulant=this->newSimulator(m_sSimulantClass);
					((CIoSimulator *)m_pSimulant)->Create();
				break;
			}
			m_pSimulant->ReadSimulantDefault(ifs);



		}

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
		if(m_pSimulant)
			m_pSimulant->WriteSimulantDefault(ofs);
		//no simulant created
		else
		{



			switch(m_iSimulantType)
			{
				case IO_SIMULANT_TYPE_MODEL :
					m_pSimulant=this->newModel(m_sSimulantClass);
					((CIoModel *)m_pSimulant)->Create();
				break;
				case IO_SIMULANT_TYPE_SIMULATOR :
					m_pSimulant=this->newSimulator(m_sSimulantClass);
					((CIoSimulator *)m_pSimulant)->Create();
				break;
			}




		}

	}


	return status;
}

int CIoSimulation::ReadConfigDefault(char *sSimFilename)
{
	int status=1;
	int i=0;
	int istep;
	//Always assumes correct simulation file read first
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
		skipcmt(ifs);
		//class
		ifs>>m_sSimClass;

		
		skipcmt(ifs);
		//steps
		ifs>>m_iCurrentStep;
							

		skipcmt(ifs);//skip prop names
		ReadFlaggedPropNames(ifs, GetArrayFlag(0),m_pPropFlags, GetNumProps());		
		
	
		skipcmt(ifs);//skip prop names
		//Read the actual flagged properties
		ReadFlaggedProps(ifs, GetArrayFlag(0), m_pPropFlags, GetNumProps());
		

		
		//simulant has been created
		if(m_pSimulant)
			m_pSimulant->ReadSimulantConfigDefault(ifs);


	}


	return status;
}

int CIoSimulation::WriteConfigDefault(char *sSimFilename)
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
		ofs<<"#Simulation class"<< ::endl;
		ofs<<m_sSimClass<< ::endl;



		//steps
		ofs<<"#Current Step:" << ::endl;
		ofs<<m_iCurrentStep<< ::endl;;

		//Write propnames
	
		ofs<<"#Property names "<<::endl;
		WriteFlaggedPropNames(ofs, GetArrayFlag(0),m_pPropFlags, GetNumProps());		
		
		
        //read simulation props
		ofs<<"#Selected Simulation properties"<<::endl;
		WriteFlaggedProps(ofs, GetArrayFlag(0), m_pPropFlags,GetNumProps());
		//must skip any comments
		//correpsonding to parameter names
		

		//format will be as follows
		//one line for each prop in prop names
		//assumes single level of iteration
		

		//simulantreadmethod

		//simulant has been created
		if(m_pSimulant)
			m_pSimulant->WriteSimulantConfigDefault(ofs);
	
	}


	return status;
}




int CIoSimulation::WriteStateDefault(char *sSimFilename)
{
	int status=1;
	int i=0;
	int istep;
	
	if(sSimFilename)
	{
		::ofstream ofs(sSimFilename, ::ios::app);
		
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
		ofs<<"#Simulation class"<< ::endl;
		ofs<<m_sSimClass<< ::endl;



		//steps
		ofs<<"#Current Step:" << ::endl;
		ofs<<m_iCurrentStep;

		//Write propnames
		ofs<<"#Property names "<<::endl;
		WriteFlaggedPropNames(ofs, GetArrayFlag(0), GetPropFlags(),GetNumProps());


		//simulation props
		ofs<<"#Simulation props:" << ::endl;
		WriteFlaggedProps(ofs, GetArrayFlag(0), GetPropFlags(), GetNumProps());
        

		//simulantreadmethod

		//simulant has been created
		if(m_pSimulant)
			m_pSimulant->WriteSimulantStateDefault(ofs);
	
	}


	return status;
}


/*!
		Read and write state information in to the simulation list;
*/
int CIoSimulation::ReadStateInfoDefault(char *sSimFilename)
{
	int i=0, j,k, iNumSteps;
	CIoEntitySet *pES1, *pES2;
	CIoModel *pM1, *pM2;

	int status=1;
	
	int istep, icycle;
	int iOldCreateMethod=m_iCreateMethod;
	CIoSimulant *pCurrentSimulant=NULL;
	CIoSimulant *pPreviousSimulant=NULL;
	//Set the create method 
	m_iCreateMethod=-1;
	//Always assumes correct simulation file read first
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
		skipcmt(ifs);
		//class
		ifs>>m_sSimClass;



		while(j<m_iNumSteps)
		{
	


		skipcmt(ifs);
		//cycles
		ifs>>icycle;
		
		skipcmt(ifs);
		//steps
		ifs>>istep;
							

		skipcmt(ifs);//skip line of prop names
		ReadFlaggedPropNames(ifs,GetArrayFlag(0),m_pPropFlags,GetNumPropNames());
		skipcmt(ifs);
		//Read the actual flagged properties
		ReadFlaggedProps(ifs, GetArrayFlag(0), m_pPropFlags, GetNumProps());
		if(!pCurrentSimulant)
		{

			//Note simulant create method is set to -1 so that 
			//full entity set/configuration is not created
			switch(m_iSimulantType)
			{
				case IO_SIMULANT_TYPE_MODEL :
					pM2=(CIoModel *)m_pSimulant;
					pCurrentSimulant=pM1=this->newModel(m_sSimulantClass);
					pCurrentSimulant->SetCreateMethod(m_iCreateMethod);
					pCurrentSimulant->CreateDefaultParams();
				
					((CIoModel *)m_pSimulant)->Create();
					if((pM1->GetNumEntitySets())>0)
					{
						for(k=0; k<pM1->GetNumEntitySets(); k++)
						{
							pES2=pM2->GetEntitySet(k);
							pES1=pM1->GetEntitySet(k);
							pES1->CopyFlags(pES2);
							pES1->CopyNames(pES2);
						}
					}
				break;
				case IO_SIMULANT_TYPE_SIMULATOR :
					pCurrentSimulant=this->newSimulator(m_sSimulantClass);
					pCurrentSimulant->SetCreateMethod(m_iCreateMethod);
					((CIoSimulator *)pCurrentSimulant)->Create();
				break;
			}
			pCurrentSimulant->CopyFlags(m_pSimulant);
			pCurrentSimulant->CopyNames(m_pSimulant);
		}
		pCurrentSimulant->SetCreateMethod(iOldCreateMethod);
		pCurrentSimulant->ReadSimulantStateDefault(ifs);
		
		pCurrentSimulant->SetCurrentStep(istep);
		pCurrentSimulant->SetNextSimulantState(pPreviousSimulant);
		pPreviousSimulant=pCurrentSimulant;
		pCurrentSimulant=NULL;

		AddSimulantState(pCurrentSimulant);
		
		//simulant has been created
		
				
				
				}
			j++;



	}

	m_iCreateMethod=iOldCreateMethod;
	return status;
}

int CIoSimulation::WriteStateInfoDefault(char *sSimFilename)
{
	int status=1;
	int i=0;
	int istep;
	CIoSimulant *pSim;
	
	if(sSimFilename)
	{
		::ofstream ofs(sSimFilename, ::ios::app);
		
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
			ofs<<"#Simulation class"<< ::endl;
			ofs<<m_sSimClass<< ::endl;
		for(m_lSimStateIterator=m_lSimStateList.begin(); m_lSimStateIterator != m_lSimStateList.end();m_lSimStateIterator++)
		{
			if(pSim=(CIoSimulant *)(*m_lSimStateIterator))
			{



			//steps
			ofs<<"#Current Step:" << ::endl;
			ofs<<pSim->GetCurrentStep();

			//Write propnames
			//ofs<<"#Property names "<<::endl;
			//WriteFlaggedPropNames(ofs, GetArrayFlag(0), GetPropFlags(),GetNumProps());


			//simulation props
			//ofs<<"#Simulation props:" << ::endl;
			//WriteFlaggedProps(ofs, GetArrayFlag(0), GetPropFlags(), GetNumProps());
	        

			//simulantreadmethod

			//simulant has been created
			if(pSim)
				pSim->WriteSimulantStateDefault(ofs);
			}
		}
	}

	return status;
}

int CIoSimulation::ReadConfig(char *sConfigFilename, int format)
{
	int status = 0;
	if(m_iconfigreadmethod==0)
		ReadConfigDefault(sConfigFilename);
	

	return status;
}



int CIoSimulation::WriteConfig(char *sConfigFilename, int format, char *sXSLFilename, int iStepNum)
{
	int status=1;
	int i=0;
	char soutname [100];
	char slisname [100];

	char stxtoutname [100];
	char c;


	//If the file was written OK then append its
	//name to the list of config files
	//i.e. the .lis file for this simulation
	strcpy(slisname, m_sSimName);
	strcat(slisname, "_cfg.lis");

	CIoFileUtils cCfgFileList(slisname, 'a');
	cCfgFileList.WriteLine(sConfigFilename);
	CIoFileUtils cOutFileList(GetOutputFiles(), 'a');
	cOutFileList.WriteLine(sConfigFilename);
	if(m_iconfigwritemethod==0)
		WriteConfigDefault(sConfigFilename);

 
	cOutFileList.CloseFile();
	cCfgFileList.CloseFile();
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

/*!
		Updates a state file as a simulation is in progress
*/
int CIoSimulation::WriteState(char *sStateFilename, int format, char *sXSLFilename, int iStepNum)
{
	int status=1;
	int i=0;
	int iNoEntities=1; //Tell config DOM writer 
	                   //not to output any entities to
	                   //the state file

	char soutname [100];
	char c;
	char stxtoutname [100];
	int isteptest, icycletest;

	if(m_istatewritemethod==0)
	{


		CIoFileUtils cOutFileList(GetOutputFiles(), 'a');
		cOutFileList.WriteLine(sStateFilename);


			WriteStateDefault(sStateFilename);

			cOutFileList.CloseFile();
	
	}
	return status;
}

int CIoSimulation::ReadStateInfo(char *sStateFilename, int format)
{
	int status=1;
	int i=0;
	int iNoEntities=1; //Tell config DOM writer 
	                   //not to output any entities to
	                   //the state file

	char soutname [100];
	char c;
	char stxtoutname [100];
	int isteptest, icycletest;

	if(m_istatereadmethod==0)
	{
			ReadStateInfoDefault(sStateFilename);
	
	}
	return status;
}

int CIoSimulation::WriteStateInfo(char *sStateFilename, int format, char *sXSLFilename, int iStepNum)
{
	int status=1;
	int i=0;
	int iNoEntities=1; //Tell config DOM writer 
	                   //not to output any entities to
	                   //the state file

	char soutname [100];
	char c;
	char stxtoutname [100];
	int isteptest, icycletest;

	if(m_istatewritemethod==0)
	{
			WriteStateInfoDefault(sStateFilename);
	
	}
	return status;
}

//General analytical operation ofr a simulation
void CIoSimulation::AnalyseSim(int iMethod, CIoParam *pAnalysisPar)
{
	//If a simulation name is set then open the simulation

	//call a configuration analysis

}

//General analytical operation for a configuration
void CIoSimulation::AnalyseConfig(int iMethod, CIoParam *pAnalysisPar)
{


}

//Apply analytical operations to a list of config files
void CIoSimulation::AnalyseConfigList(int iMethod, CIoParam *pAnalysisPar)
{
	//Open a list of config files read each entry
	//and perform analysis on each configuration

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
























