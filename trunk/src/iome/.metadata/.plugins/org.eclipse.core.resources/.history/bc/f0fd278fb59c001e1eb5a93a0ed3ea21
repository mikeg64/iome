#ifndef IO_SIMULATION_MODEL_H
#define IO_SIMULATION_MODEL_H
// IoModel.h: interface for the CIoModel class.
//
//////////////////////////////////////////////////////////////////////
/*
IOME LICENSE
IOME Version 2.1.1 

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
//#if !defined(AFX_IOMODEL_H__8E17A515_81AE_4D5B_8A7F_CA3C38480E48__INCLUDED_)
//#define AFX_IOMODEL_H__8E17A515_81AE_4D5B_8A7F_CA3C38480E48__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#include "IoSimulant.h"



class CIoModel : public CIoSimulant  
{
public:
	CIoModel(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	virtual ~CIoModel();

	char *m_sModelName;
	char *m_sModelClass;
	CIoEntitySet *m_pEntitySet;


	void SetModelName(const char *name);/*{strcpy(m_sModelName, name);}*/
	char *GetModelName(){return m_sModelName;}
	void SetModelClass(const char *name);/*{strcpy(m_sModelClass, name);}*/
	char *GetModelClass(){return m_sModelClass;}

	char *GetClassName(){return m_sModelClass;}

	int CreateModel(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL){return Create(pParams, pChildParams, pArray);}

	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);
	void SetDistributeMethod(int imethod){if(((m_idistributemethod = imethod)>=0) )m_idistributemethod=imethod;}
	void SetNumProcs(int inumprocs){if(((m_inumprocs = inumprocs)>=0) )m_inumprocs=inumprocs;}

  
	/*!
		Over ridden by developer
		Assumes 
		1.create method defined
		2.Model Params defined
		3.Entity set params passed in are in array of arrays
		  entity set pars for each entity set
		4.Entity Type set params passed in are in array of arrays
		  entity type set pars for each entity set
		  always the same size as num entity sets
		  if an entity set has no entity type set
		  then its et type set pars will be null

	
	*/
	virtual int CreateEntitySets(int iNumES=0, CIoParam *pESClassName=NULL, CIoParam *pESParam=NULL, CIoParam *pETSParam=NULL , char *cESMap=NULL);

	//Called after create entity sets
	//or after simulation read
	//virtual int CreateConfig(){return 0;}
	//Default action for add, GetChild and remove is to do nothing
	//meaningless for a model!
	virtual void Add(CIoSimulant *pSimulant){;}
	virtual void Remove(CIoSimulant *pSimulant){;}
	virtual CIoSimulant *GetChild(int index);

	virtual	int CheckParamFormat(CIoParam *pSimData);
	virtual void CreateDefaultParams();
	//virtual void CreateEntitySet(CIoParam *pEntitySetParams=NULL,
	//							 CIoParam *pEntityTypeSetParams=NULL, int iModel=0);
	virtual int ReadConfig(char *sConfigFilename, char *format=NULL){return 0;}
	virtual int WriteConfig(char *sConfigFilename, char *format=NULL){return 0;}
	int ReadState(char *sStateFilename, int format=NULL){return 0;}
	int WriteState(char *sStateFilename, int format=NULL){return 0;}

	virtual int ReadSimulantDefault(::ifstream &ifs);
	virtual int WriteSimulantDefault(::ofstream &ifs);
	virtual int ReadSimulantConfigDefault(::ifstream &ifs);
	virtual int WriteSimulantConfigDefault(::ofstream &ifs);
	virtual int ReadSimulantStateDefault(::ifstream &ifs);
	virtual int WriteSimulantStateDefault(::ofstream &ifs);
    //following three methods unnecssary as they are
	//derived from CIoSimulant and CIoSimHandler

	//This maybe overridden by the actual implementation of the
	//model to update the model  parameters
	//but this CIoModel method will be called to invoke
	//the actual handlers
	virtual void RunSimulantStep();


    CIoEntitySet *GetEntitySet(int iIndex=0);
	int AddEntitySet(CIoEntitySet *pNewEntitySet);
	virtual CIoEntitySet *newEntitySet(char *sEntitySetClass){return NULL;}

	//Removed but not deleted
	//lost but not forgotten
	CIoEntitySet *RemoveEntitySet(int iIndex=0);
	void DeleteEntitySet(int iIndex=0);
	int GetNumEntitySets();
	int GetNumEntities();
	CIoEntityTypeSet *GetEntityTypeSet(){return(m_pEntitySet==NULL?NULL:m_pEntitySet->GetEntityTypeSet());}

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
	CIoEntityTypeSet *CopyEntityTypeSet(int iIndex);



	void CreateEntitySet(CIoParam *pEntitySetParams,
						 CIoParam *pEntityTypeSetParams,int iSimulant=-1);

	virtual int CreateESEntitySet(	CIoEntitySet *pES=NULL){return 0;}


	virtual void ETUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL );
	virtual void ESUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntitySet *pES=NULL);
	virtual void ETSUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntityTypeSet *pES=NULL );
	virtual void EUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntity *pE=NULL, CIoEntitySet *pES=NULL );

	virtual void ETUpdateState(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL );
	virtual void ESUpdateState(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntitySet *pES=NULL);
	virtual void ETSUpdateState(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntityTypeSet *pES=NULL );
	virtual void EUpdateState(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntity *pE=NULL, CIoEntitySet *pES=NULL );


	//Virtual handlers of entity set used to create params
	//and properties for entity types and entity type sets
	virtual void CreateETSPropArrayFlags(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL);
	virtual void CreateETSPropArrayNames(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL);

	virtual void CreateETSPropFlags(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL);
	virtual void CreateETSPropNames(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL);

	virtual void CreateETSDefaultParams(CIoParam *pParam=NULL, CIoEntityTypeSet *pES=NULL);

	//Need to update the correct entity type
	virtual void CreateETPropArrayFlags(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);
	virtual void CreateETPropArrayNames(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);

	virtual void CreateETPropFlags(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);
	virtual void CreateETPropNames(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);

	virtual void CreateETDefaultParams(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);

	//Need to update the correct entity type
	virtual void CreateESPropArrayFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);
	virtual void CreateESPropArrayNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);

	virtual void CreateESPropFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);
	virtual void CreateESPropNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);

	virtual void CreateESDefaultParams(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);

	virtual void CreateEntityDefaultParams(CIoParam *pParam=NULL, CIoEntity *pE=NULL, CIoEntitySet *pES=NULL);


	/*!
		These methods create object instances with their default properties
		the user must ensure that E, ETS and E are created with correct
		pointers to parents i.e. call cosntructors in correct way
	
	*/
	virtual CIoEntity  *newEntityES(CIoEntitySet *pES=NULL);
	virtual CIoEntityType  *newEntityTypeES(CIoEntitySet *pES=NULL, char *sClassName=NULL);
	virtual CIoEntityTypeSet  *newEntityTypeSetES(CIoEntitySet *pES=NULL, char *sClassName=NULL);

};

#endif
