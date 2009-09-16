#ifndef IO_SIMULATION_SIMHANDLER_H
#define IO_SIMULATION_SIMHANDLER_H
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
// IoSimHandler.h: interface for the CIoSimHandler class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_IOSIMHANDLER_H__0A5ACAAF_6897_419E_8EF9_0D2D0B97A692__INCLUDED_)
//#define AFX_IOSIMHANDLER_H__0A5ACAAF_6897_419E_8EF9_0D2D0B97A692__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
//#define USEMPI
#ifdef USEMPI
	#include <mpi.h>
	
#endif


#ifndef IO_MSVC
	#include <iome/utils/IoPropertyManager.h>
#else
	#include <iome/utils/IoPropertyManager.h>
#endif




class CIoSimulant;
class CIoEntity;
class CIoSimulation;
class CIoEntityType;
class CIoEntityTypeSet;
class CIoEntitySet;



using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::endl;



class CIoSimHandler : public CIoPropertyManager  
{
public:
	CIoSimHandler(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	virtual ~CIoSimHandler();

	void SetParentSimulation(CIoSimulation *pParentSimulation){m_pParentSimulation=pParentSimulation;}
	CIoSimulation *GetParentSimulation(){return m_pParentSimulation;}

	void SetParentSimulant(CIoSimulant *pParentSimulant){m_pParentSimulant=pParentSimulant;}
	CIoSimulant *GetParentSimulant(){return m_pParentSimulant;}
	CIoSimulation *m_pParentSimulation;
	CIoSimulant *m_pParentSimulant;
	CIoSimHandler *m_pParentHandler;

	void SetParentHandler(CIoSimHandler *pParentHandler){m_pParentHandler=pParentHandler;}
	CIoSimHandler *GetParentHandler(){return m_pParentHandler;}

	/*! These parameters are set by the simulation when it runs a step*/
	static int m_iNumCycles;
	static int m_iCurrentCycle;
	static int m_iCurrentStep;
	static int m_iNumSteps;

    inline CIoParam *GetParams(){return m_pProperties;}
	inline int GetNumCycles(){return m_iNumCycles;}
	inline int GetCurrentCycle(){return m_iCurrentCycle;}
	inline int GetCurrentStep(){return m_iCurrentStep;}
	inline int GetNumSteps(){return m_iNumSteps;}

	inline void SetNumCycles(int iNumCycles){m_iNumCycles=iNumCycles;}
	inline void SetCurrentCycle(int iCurrentCycle){m_iCurrentCycle=iCurrentCycle;}
	inline void SetCurrentStep(int iCurrentStep){m_iCurrentStep=iCurrentStep;}
	inline void SetNumSteps(int iNumSteps){m_iNumSteps=iNumSteps;}

	virtual CIoEntity *newEntity(){return NULL;}
	virtual CIoEntityType *newEntityType(CIoEntitySet *pES, char *sETClass){return NULL;}
	virtual CIoEntityTypeSet *CopyEntityTypeSet(int iIndex=0){return NULL;}
	virtual CIoEntitySet *newEntitySet(char *sEntitySetClass){return NULL;}

	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL){return 0;}


	virtual void HandleInteractions();
	virtual void HandleStateTransitions();

	//Handle interactions between different models
	virtual void HandleModelInteractions();

	//These methods pure virtual
	//require a concrete entity to define an interaction
	//and its state transition



	virtual void ESHandleEntitySetInteraction(CIoEntitySet *pESInteract, CIoEntitySet *pESToUpdate){};
	virtual void ESHandleInteractions(CIoEntitySet *pES){};
	virtual void ESHandleStateTransitions(CIoEntitySet *pES){};
	virtual void EHandleInteractions(CIoEntity *pE){};
	virtual void EHandleStateTransitions(CIoEntity *pE){};

	virtual void Update(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL ){};
	virtual void ETUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL ){};
	virtual void ESUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntitySet *pES=NULL){};
	virtual void ETSUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntityTypeSet *pES=NULL ){};
	virtual void EUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntity *pE=NULL, CIoEntitySet *pES=NULL ){};


	//Virtual handlers of entity set used to create params
	//and properties for entity types and entity type sets
	virtual void CreateETSPropArrayFlags(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL){};
	virtual void CreateETSPropArrayNames(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL){};

	virtual void CreateETSPropFlags(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL){};
	virtual void CreateETSPropNames(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL){};

	virtual void CreateETSDefaultParams(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL){};

	//Need to update the correct entity type
	virtual void CreateETPropArrayFlags(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL){};
	virtual void CreateETPropArrayNames(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL){};

	virtual void CreateETPropFlags(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL){};
	virtual void CreateETPropNames(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL){};

	virtual void CreateETDefaultParams(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL){};

	//Need to update the correct entity type
	virtual void CreateESPropArrayFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};
	virtual void CreateESPropArrayNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};

	virtual void CreateESPropFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};
	virtual void CreateESPropNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};

	virtual void CreateESDefaultParams(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};

	//The following methods must call back to the parent 
	//simulant/model
	//The model or simulant receives a copy of the pointer to the entity set
	//requesting create parameters operation
	//This must always be called in the model constructor function
	//Note entity sets always call these methods from their cosntructor
	virtual void CreateESEPropNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){;}
	virtual void CreateESEPropArrayNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){;}
	virtual void CreateESEPropFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){;}
	virtual void CreateESEPropArrayFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){;}




	virtual void CreateEntityDefaultParams(CIoParam *pParam=NULL, CIoEntity *pE=NULL, CIoEntityTypeSet *pES=NULL){};

	/*!When the new operator is called it must 
	  pass the correct parent simulant, parent simulation and parent handler
	  to the constructor of the object to be created
	  Any new objects that are derived must call the constructor in the 
	  correct way
	  */
	virtual CIoEntity  *newEntityES(CIoEntitySet *pES=NULL){return NULL;}
	virtual CIoEntityType  *newEntityTypeES(CIoEntitySet *pES=NULL, char *sClassName=NULL){return NULL;}
	virtual CIoEntityTypeSet  *newEntityTypeSetES(CIoEntitySet *pES=NULL, char *sClassName=NULL){return NULL;}

	virtual int CreateESEntitySet(CIoEntitySet *pES=NULL){return 0;}

	#ifdef USEMPI
		MPI::Intracomm m_comm;
		int m_nprocs;
		int m_irank;

		int SendRecvParam(int fromproc, int toproc, int iparamid,  char *sparammap);		
		int SendRecvParams(int fromproc, int toproc);
		int BroadcastParams(int fromproc);
		int BroadcastParam(int fromproc, int iparamid, char *sparammap);

	#endif

};

#endif
