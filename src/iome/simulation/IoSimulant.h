#ifndef IO_SIMULATION_SIMULANT_H
#define IO_SIMULATION_SIMULANT_H
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
// IoSimulant.h: interface for the CIoSimulant class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_IOSIMULANT_H__6EABA483_11F6_46CC_AEBE_B7910BA01271__INCLUDED_)
//#define AFX_IOSIMULANT_H__6EABA483_11F6_46CC_AEBE_B7910BA01271__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
#include <iome/simulation/IoEntitySet.h>



#include <iome/simulation/IoSimHandler.h>
#ifndef IO_MSVC
	#include <iome/utils/IoParams.h>
#else
	#include <iome/utils/IoParams.h>
#endif
#include <iome/simulation/CIoSimulantPort.h>
//#include <iome/simulation/IoWFExecutable.h>


using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::deque;


#define IO_SIMULANT_TYPE_SIMULATOR 1
#define IO_SIMULANT_TYPE_MODEL 0


//typedef CIoWFSimulantPort * PORTPTR;
//typedef deque<PORTPTR> dqportptr;


class CIoSimulation;
class CIoEntitySet;

class CIoSimulant : public CIoSimHandler  
{
public:
	CIoSimulant(CIoSimulation *pParentSimulation=NULL, CIoSimulant *pParentSimulant=NULL, CIoSimHandler *pParentHandler=NULL);
	virtual ~CIoSimulant();
	char *m_sSimulantName;
	CIoSimulant *m_pNextSimulant;
	CIoSimulant *m_pNextSimulantState;  //used to store a list of states
	int m_iSimulantType;
	int m_iStepNum;
	int m_iRunState; //OK ready,  1 running, 2 qwaiting, 3 waitingforinputport, 4 waitingforoutput, 5 finished
    int m_iprocid;
//	IoWFExecutable m_wfexecutable;
	int m_idistributemethod;
	int m_inumprocs;
	
	//dqspptr &GetInPorts(){return m_pInPorts;}
	//dqspptr &GetOutPorts(){return m_pOutPorts;}
	virtual void SetDistributeMethod(int imethod)=0;
	int GetDistributeMethod(){return m_idistributemethod;}
	virtual void SetNumProcs(int inumprocs)=0;
	int GetNumProcs(){return m_inumprocs;}
	int GetProcID(){return m_iprocid;}
	
	
	
//	char *GetHost(){return m_wfexecutable.GetHost();}
//	char *GetJobmanager(){return m_wfexecutable.GetJobmanager();}
	
	
	
	int GetRunState(){return m_iRunState;}
	void SetRunState(int istate){m_iRunState=istate;}

	
	
	//Follwoing must be overridden
	//Property Manager methods
	virtual void CreatePropNames(){;}
	virtual void CreatePropFlags(){;}
	virtual void CreatePropArrayFlags(){;}
	virtual void CreatePropArrayNames(){;}

	int m_iCreateMethod;  //0 if reading config from file  non zero int identifies a user specified creation method
	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL)=0;
	virtual int CreateEntitySets(int iNumES=0, CIoParam *pESClassName=NULL, CIoParam *pESParam=NULL, CIoParam *pETSParam=NULL , char *cESMap=NULL)=0;
    virtual int CreateConfig()=0;
	virtual CIoEntity *newEntity(CIoEntitySet *pES){return NULL;}
	virtual CIoEntityType *newEntityType(CIoEntitySet *pES, char *sETClass);
	virtual CIoEntityTypeSet *CopyEntityTypeSet(int iIndex=0){return NULL;}

	//Normally used by state
	inline int GetCurrentStep(){return m_iStepNum;}
	inline void SetCurrentStep(int istep){m_iStepNum=istep;}

	void SetCreateMethod(int imethod){m_iCreateMethod = imethod;}
	int GetCreateMethod(){return m_iCreateMethod;}

	//void SetParentSimulation(CIoSimulation *pSimulation){m_pParentSimulation=pSimulation;}
	//CIoSimulation *GetParentSimulation(){return m_pParentSimulation;}


	CIoSimulant *GetNextSimulant(){return m_pNextSimulant;}
	void SetNextSimulant(CIoSimulant *pNextSimulant){m_pNextSimulant = pNextSimulant;}
	CIoSimulant *GetNextSimulantState(){return m_pNextSimulantState;}
	void SetNextSimulantState(CIoSimulant *pNextSimulant){m_pNextSimulantState = pNextSimulant;}
	void AddSimulantState(CIoSimulant *pSimulant);
	CIoSimulant *GetSimulant(int i=0);

	void SetSimulantName(const char *name);
	char *GetSimulantName(){return m_sSimulantName;}
	virtual char *GetClassName()=0;

	//Methods for setting and getting an entity type set are required
	//need to get these objects from the ith entity set or the ith entity set from the jth simulant.
	//CIoEntityTypeSet *GetEntityTypeSet(){return m_pEntityTypeSet;}
	//void SetEntityTypeSet(CIoEntityTypeSet *pEntityTypeSet){m_pEntityTypeSet = pEntityTypeSet;}




	virtual void Add(CIoSimulant *pSimulant)=0;
	virtual void Remove(CIoSimulant *pSimulant)=0;
	virtual CIoSimulant *GetChild(int index)=0;

	virtual void CreateEntitySet(CIoParam *pEntitySetParams=NULL,
						 CIoParam *pEntityTypeSetParams=NULL, int iSimulant=-1)=0;

	virtual void RunSimulantStep()=0;

	virtual int ReadConfig(char *sConfigFilename, char *format=NULL)=0;
	virtual int WriteConfig(char *sConfigFilename, char *format=NULL)=0;

	virtual int ReadState(char *sStateFilename, int format=NULL)=0;
	virtual int WriteState(char *sStateFilename, int format=NULL)=0;

	virtual int ReadSimulantDefault(::istream &ifs){return 1;}
	virtual int WriteSimulantDefault(::ostream &ifs){return 1;}
	virtual int ReadSimulantConfigDefault(::istream &ifs){return 1;}
	virtual int WriteSimulantConfigDefault(::ostream &ifs){return 1;}
	virtual int ReadSimulantStateDefault(::istream &ifs){return 1;}
	virtual int WriteSimulantStateDefault(::ostream &ifs){return 1;}
	int GetSimulantType(){return m_iSimulantType;}


	//The following methods have to be pure virtual we don't know
	//ho we're going to create the set of entities yet

	//The user may override this class
    //to update the parameters
    //but will call this class
    //to handle interactions for the actual simulants
    //For each simulant hande the interactions
    virtual void HandleInteractions();


	 //The user may override this class
     //to update the parameters
     //but will call this class
     //to handle state transitions for the actual simulants
     //For each simulant hande the state transitions
	virtual void HandleStateTransitions();


	};

#endif 
