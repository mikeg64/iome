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


//#include <iome/simulation/IoSimulator.h>
//#include <iome/simulation/IoModel.h>
#include <iome/simulation/IoMetadata.h>










//typedef CIoSimulant * SIMULANTPTR;
//typedef std::list<SIMULANTPTR> SIMULANT_LIST;

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
	//SIMULANT_LIST m_lSimStateList;
	//SIMULANT_LIST::iterator m_lSimStateIterator;
	//SIMULANT_LIST::size_type m_size;

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

	


	

	//CIoSimulant *m_pSimulant;
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

	void DeleteAllMetadata();
	void DeleteMetadata(string sname);	
	void AddMetadata(string sname, string scontent);
	void SetMetadata(string sname, string scontent);
	string GetMetadata(string sname);
	void ListMetadata(char *slist);

	CIoMetadata *GetMetadata(int index);
	string GetMetadataContent(string sname);
	//void AddSimulantState(CIoSimulant *pSim);
	//CIoSimulant *GetSimulantState(int index);
	//void DeleteSimulantStates();
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
	void SetDistributeMethod(int imethod){m_idistributemethod = imethod;}
	int GetDistributeMethod(){return m_idistributemethod;}

	void SetNumProcs(int inumprocs){m_inumprocs = inumprocs;}
	int GetNumProcs(){return m_inumprocs;}


	void SetCreateMethod(int imethod){m_iCreateMethod = imethod;}
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



	virtual CIoSimulation *newSimulation(){return NULL;}
	virtual void RunSimulation(){;}
	virtual void SetSimProperties(CIoParam *pSimProperties);
	

	//Checks that parameter is an array of two parameters
	//each parameter is itself a parameter array
	virtual	int CheckParamFormat(CIoParam *pSimData){return((pSimData && (pSimData->GetType()==IO_PARAM_ARRAY)));}

	/*!
	This function creates only the parameters for the object
	it will not create a default configuration.
	*/
	virtual void CreateDefaultParams();
    virtual int Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray);

	virtual int CreateSimulation(char *sFilename=NULL){return 0;}
 	virtual int ReadSimulation(char *sSimFilename);
	virtual int WriteSimulation(char *sSimFilename=NULL, char *sXSLFilename=NULL);



	virtual int ReadSimulationDefault(char *sSimFilename);
	virtual int WriteSimulationDefault(char *sSimFilename);
};

#endif 
