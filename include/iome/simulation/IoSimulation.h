#ifndef IO_SIMULATION_SIMULATION_H
#define IO_SIMULATION_SIMULATION_H
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
// IoSimulation.h: interface for the CIoSimulation class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_IOSIMULATION_H__0C90F4FD_B515_497F_807F_EC47DE354F3C__INCLUDED_)
//#define AFX_IOSIMULATION_H__0C90F4FD_B515_497F_807F_EC47DE354F3C__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
#ifdef USEMPI
	#include <mpi.h>
	
#endif
#ifndef IO_MSVC
	#include <iome/utils/IoPropertyManager.h>
	#include <iome/utils/IoFileUtils.h>
#else
	#include <iome/utils/IoPropertyManager.h>
	#include <iome/utils/IoFileUtils.h>
#endif

//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <list>
//#include <cstdio>
//#include <cstdlib>
//#include <io.h>


#include <iome/simulation/IoSimulator.h>
#include <iome/simulation/IoModel.h>
#include <iome/simulation/IoMetadata.h>










typedef CIoSimulant * SIMULANTPTR;
typedef std::list<SIMULANTPTR> SIMULANT_LIST;

typedef CIoMetadata * METADATAPTR;
typedef std::list<METADATAPTR> METADATA_LIST;

using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;

class CIoSimulation : public CIoPropertyManager 
{
public:
	CIoSimulation();
	virtual ~CIoSimulation();

	char *m_sSimName;
	char *m_sSimClass;
	char *m_sSimulantClass;
	char *m_sConfigFileName;
	char *m_sStateFileName;

	//CIoSimulation *m_pNextSimulation; //Used for analysis to collect a list of simulations

	//Used to store state information
	//used when undertaking analysis and when transforming stet output information
	SIMULANT_LIST m_lSimStateList;
	SIMULANT_LIST::iterator m_lSimStateIterator;
	SIMULANT_LIST::size_type m_size;

	METADATA_LIST m_lMetadataList;
	METADATA_LIST::iterator m_lMetadataIterator;
	int m_nprocs;
	int m_irank;

	#ifdef USEMPI
		MPI::Intracomm m_comm;

		int SendRecvSimulationParam(int fromproc, int toproc, int iparamid,  char *sparammap);		
		int SendRecvSimulationParams(int fromproc, int toproc);
		int BroadcastSimulationParams(int fromproc);
		int BroadcastSimulationParam(int fromproc, int iparamid, char *sparammap);
		int BroadcastStep(int fromproc=0);
		int BroadcastNSteps(int fromproc=0);

	#endif

	char *m_sHomeDir;
	char *m_sOutputFiles;


	int m_iNumSteps;
	//int m_iNumCycles;

	//int m_iCurrentCycle;
	int m_iCurrentStep;

	int m_iSimType;
	int m_iSimulantType;

	//int m_iConfigCycleFreq;
	int m_iConfigStepFreq;
	//int m_iStateCycleFreq;
	int m_iStateStepFreq;

	


	

	CIoSimulant *m_pSimulant;
	float m_fVersion;

	//This parameter array always has the following 
	//minimum structure
	//m_pSimProperties should always return
	//an integer which is the number of parameters
	//in the array always at least 1
	//it is an array of parameters
	//The properties for the simulation has the following structure
	//int parameter is 1+number of cycles
	//it is an array of parameter arrays
	// an array of fixed parameters
	// the next arrays are arrays of parameters used for each cycle of
	// the simulation these will be used to set simulant properties
	// for each cycle of the simulation
	int m_iCreateMethod;  //0 if creating config using default method  non zero int identifies a user specified creation method
                          //-1 Reading config from an input file

	int m_isimreadmethod;
	int m_isimwritemethod;
	int m_istatereadmethod;
	int m_istatewritemethod;
	int m_iconfigreadmethod;
	int m_iconfigwritemethod;

	int m_idistributemethod;
	int m_inumprocs;


	void DeleteMetadata(string sname);
	void DeleteAllMetadata();	
		
	void AddMetadata(string sname, string scontent);
	void SetMetadata(string sname, string scontent);
	string GetMetadata(string sname);
	void ListMetadata(char *slist);

	CIoMetadata *GetMetadata(int index);
	string GetMetadataContent(string sname);
	void AddSimulantState(CIoSimulant *pSim);
	CIoSimulant *GetSimulantState(int index);
	void DeleteSimulantStates();
	//Follwoing must be overridden
	//Property Manager methods
	virtual void CreatePropNames();
	virtual void CreatePropArrayNames();
	
	/*!
		These methods not overidden
		assume that flag is 1 by default 
		i.e. always write we only
		pply this to simulants, entity sets, entities etc...

		
	
	//virtual void CreatePropArrayFlags();
	//virtual void CreatePropArrayNames(){;}
	*/	
	void SetDistributeMethod(int imethod){if(((m_idistributemethod = imethod)>=0) && m_pSimulant)m_pSimulant->SetDistributeMethod(imethod);}
	int GetDistributeMethod(){return m_idistributemethod;}

	void SetNumProcs(int inumprocs){if(((m_inumprocs = inumprocs)>0) && m_pSimulant)m_pSimulant->SetNumProcs(inumprocs);}
	int GetNumProcs(){return m_inumprocs;}


	void SetCreateMethod(int imethod){if(((m_iCreateMethod = imethod)>=0) && m_pSimulant)m_pSimulant->SetCreateMethod(imethod);}
	int GetCreateMethod(){return m_iCreateMethod;}
	
	void SetSimWriteMethod(int imethod){m_isimwritemethod = imethod;}
	int GetSimWriteMethod(){return m_isimwritemethod;}
	void SetSimReadMethod(int imethod){m_isimreadmethod = imethod;}
	int GetSimReadMethod(){return m_isimreadmethod;}

	void SetStateWriteMethod(int imethod){m_istatewritemethod = imethod;}
	int GetStateWriteMethod(){return m_istatewritemethod;}
	void SetStateReadMethod(int imethod){m_istatereadmethod = imethod;}
	int GetStateReadMethod(){return m_istatereadmethod;}
	
	void SetConfigWriteMethod(int imethod){m_iconfigwritemethod = imethod;}
	int GetConfigWriteMethod(){return m_iconfigwritemethod;}
	void SetConfigReadMethod(int imethod){m_iconfigreadmethod = imethod;}
	int GetConfigReadMethod(){return m_iconfigreadmethod;}

	float GetVersion(){return m_fVersion;}

	
	void SetNumSteps(int iNumSteps){if(iNumSteps>=0) m_iNumSteps=iNumSteps;}
	int GetNumSteps(){return m_iNumSteps;}
	//int GetNumCycles(){return m_iNumCycles;}

	//inline int GetCurrentCycle(){return m_iCurrentCycle;}	
	inline int GetCurrentStep(){return m_iCurrentStep;}
	//inline void SetCurrentCycle(int icycle){if((icycle<m_iNumCycles) && (icycle>=0)) m_iCurrentCycle=icycle;}
	inline void SetCurrentStep(int istep){if((istep>=0) ) m_iCurrentStep=istep;}



	//probably need to modify so that get and set applies to actual simulant
	void SetSimType(int iSimType){m_iSimType = iSimType;}
	void SetSimulantType(int iSimulantType){m_iSimulantType = iSimulantType;}
	int GetSimType(){return m_iSimType;}
 	int GetSimulantType(){return m_iSimulantType;}
	//void AddSimulantState(CIoSimulant *pSimulant){if(m_pSimulant)(m_pSimulant->AddSimulantState(pSimulant));}


	//void SetConfigCycleFreq(int iConfigCycleFreq){if(iConfigCycleFreq>0) m_iConfigCycleFreq=iConfigCycleFreq;}
	//int GetConfigCycleFreq(){return m_iConfigCycleFreq;}
	void SetConfigStepFreq(int iConfigStepFreq){if(iConfigStepFreq>0) m_iConfigStepFreq=iConfigStepFreq;}
	int GetConfigStepFreq(){return m_iConfigStepFreq;}

	//void SetStateCycleFreq(int iStateCycleFreq){if(iStateCycleFreq>0) m_iStateCycleFreq=iStateCycleFreq;}
	//int GetStateCycleFreq(){return m_iStateCycleFreq;}
	void SetStateStepFreq(int iStateStepFreq){if(iStateStepFreq>0) m_iStateStepFreq=iStateStepFreq;}
	int GetStateStepFreq(){return m_iStateStepFreq;}

	CIoParam *GetSimProperties(){return m_pProperties;}
	void SetSimName(char *name);/*{for(int i=0; i<strlen(name), i<100; i++)m_sSimName [i]=name [i];}*/
	char *GetSimName(){return m_sSimName;}
	void SetSimClass(const char *name);/*{for(int i=0; i<strlen(name), i<100; i++)m_sSimClass [i]=name [i];}*/
	char *GetSimClass(){return m_sSimClass;}
	void SetSimulantClass(const char *name);/*{for(int i=0; i<strlen(name), i<100; i++)m_sSimClass [i]=name [i];}*/
	char *GetSimulantClass(){return m_sSimulantClass;}

	void SetConfigFileName(const char *name);/*{for(int i=0; i<strlen(name), i<100; i++)m_sConfigFileName [i]=name [i];}*/
	char *GetConfigFileName(){return m_sConfigFileName;}
	void SetStateFileName(const char *name);
	char *GetStateFileName(){return m_sStateFileName;}

	void SetHomeDir(const char *name);
	char *GetHomeDir(){return m_sHomeDir;}
	void SetOutputFiles(const char *name);
	char *GetOutputFiles(){return m_sOutputFiles;}


	CIoSimulant *GetSimulant(){return m_pSimulant;}
	void SetSimulant(CIoSimulant *pSimulant){m_pSimulant=pSimulant;}

    //If unsucceessfull these routines will always return NULL
	//Get the ith model
	CIoModel *GetModel(int i=0);

	//Get the ith simulator
	CIoSimulator *GetSimulator(int i=0);

	//Method to read parameters from child, grand child, great grand child simulants....
	//See IoUtils
	//These will normally be passed on to the simulant
	//Do we need set methods?
	CIoModel *GetChildModel(int i, char *cSimulantMap=NULL);
	CIoSimulator *GetChildSimulator(int i, char *cSimulantMap=NULL);
	CIoSimulant *GetChildSimulant(int i, char *cSimulantMap=NULL);

	//Get the following objects from the i'th simulant (which must be a model)
	//of the simulant hierarchy 
	//Do we need set methods?
	CIoEntitySet *GetEntitySet(int i, char *csimulantmap=NULL);
	CIoEntity *GetEntity(int i, int iEntityIndex, char *csimulantmap=NULL);
	CIoEntityTypeSet *GetEntityTypeSet(int i, char *csimulantmap=NULL);
	CIoEntityType *GetEntityType(int i, int iEntityType, char *csimulantmap=NULL);



	virtual CIoModel *newModel(char *sModelClass){return NULL;}
	virtual void DeleteSimulant(){if(m_pSimulant) delete m_pSimulant;}
	virtual CIoSimulator *newSimulator(char *sSimulatorClass){return NULL;}
	virtual CIoSimulation *newSimulation(){return NULL;}

	virtual void SetSimProperties(CIoParam *pSimProperties);
	
	virtual void RunSimulationStep(int iStepNum);
	virtual void RunSimulation();

	//Checks that parameter is an array of two parameters
	//each parameter is itself a parameter array
	virtual	int CheckParamFormat(CIoParam *pSimData){return((pSimData && (pSimData->GetType()==IO_PARAM_ARRAY)));}

	/*!
	This function creates only the parameters for the object
	it will not create a default configuration.
	*/
	virtual void CreateDefaultParams();


	virtual int CreateSimulation(char *sFilename=NULL){return 0;}
 	virtual int ReadSimulation(char *sSimFilename);
	virtual int WriteSimulation(char *sSimFilename=NULL, char *sXSLFilename=NULL);

	//Models, simulators, entity sets, entities etc...
	//will have flags to determine which properties
	//are each parameter has write flag which has default 1 meaning
	//write the parameter may be set using the property manager or the property

	//A format string identifier
	virtual int ReadConfig(char *sConfigFilename, int format=0);
	virtual int WriteConfig(char *sConfigFilename, int format=0, char *sXSLFilename=NULL, int iStepNum=-1);

	virtual int ReadStateInfo(char *sStateFilename, int format=0);
	virtual int WriteStateInfo(char *sStateFilename, int format=0, char *sXSLFilename=NULL, int iStepNum=-1);

	/*!
		Updates a state file as a simulation is in progress
	*/
	virtual int ReadState(char *sStateFilename, int format=0){return 0;}
	virtual int WriteState(char *sStateFilename, int format=0, char *sXSLFilename=NULL, int iStepNum=-1);

	/*!A simulation consists of a singlemodel 
	//This will probably be th case for most simulations
	//virtual int CreateSimModel( CIoParam *pSimulationParams = NULL,
	//							  CIoParam *pModelParams = NULL,
	//						      CIoParam *pEntitySetParams = NULL,
	//						      CIoParam *pEntityTypeSetParams=NULL);

    //This is use case 2 in which a simulation has a
	//simulator with multiple models
	//Will probably be of most use for discrete cell models
	//Create  Simulation  reads an CIoParam of the following format
	//ALWAYS IS AN ARRAY CONTAINING TWO ENTRIES
	//the first entry is parameter array for the simulation parameters
	//the second entry is the parameter array passed on for
	//creation of simulators
	//virtual int CreateSimSimulator(CIoParam *pSimulationParams=NULL,
	//								CIoParam *pSimulatorParams=NULL, 
	//								CIoParam *pSimulatorChildParams=NULL);


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
	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	/*!
	  iNUmES=Number of Entity sets in model if simulant is model
	  if the simulant is a simlator cESMap has number of entity sets
	  for each child simulant

	  pESClassName is an array containg class name for each entity set type
	  for a model will be of size iNumES
		
	*/
 	virtual int CreateEntitySets(int iNumES=0, CIoParam *pESClassName=NULL, CIoParam *pESParam=NULL, CIoParam *pETSParam=NULL , char *cESMap=NULL);

	//We don't know how to create a simulator
	//so we need a realisation of the simulation to tell us how to 
	//create the simulation hence this is pure virtual

	/*!
	  Create the actual configuration as soon as actual entiy sets and entity type sets have been
	  created. Assumes create method has been set.
	*/
	virtual int CreateConfig();


	//Simulation analysis functions

	//General analytical operation ofr a simulation
	virtual void AnalyseSim(int iMethod, CIoParam *pAnalysisPar=NULL);

	//General analytical operation for a configuration
	virtual void AnalyseConfig(int iMethod, CIoParam *pAnalysisPar=NULL);

	//Apply analytical operations to a list of config files
	virtual void AnalyseConfigList(int iMethod, CIoParam *pAnalysisPar=NULL);

	virtual int ReadSimulationDefault(char *sSimFilename);
	virtual int WriteSimulationDefault(char *sSimFilename);
	virtual int ReadConfigDefault(char *sSimFilename);
	virtual int WriteConfigDefault(char *sSimFilename);
	virtual int ReadStateDefault(char *sSimFilename){return 0;}
	virtual int WriteStateDefault(char *sSimFilename);

	/*!
		Read and write state information in to the simulation list;
	*/
	virtual int ReadStateInfoDefault(char *sSimFilename);
	virtual int WriteStateInfoDefault(char *sSimFilename);
};

#endif 
