#ifndef IO_SIMULATION_ENTITYSET_H
#define IO_SIMULATION_ENTITYSET_H
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
// IoEntitySet.h: interface for the CIoEntitySet class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_IOENTITYSET_H__47A85C02_59E2_4B22_9A83_90CD80A94075__INCLUDED_)
//#define AFX_IOENTITYSET_H__47A85C02_59E2_4B22_9A83_90CD80A94075__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000


#include "IoSimHandler.h"
#include "IoEntityTypeSet.h"
#include "IoEntity.h"
#include "IoSimulant.h"


using std::string;
using std::deque;
using std::vector;
using std::list;


typedef deque<string> dqstr;
typedef deque<int>    dqint;
typedef CIoEntity  *EntityPtr;


typedef vector<EntityPtr> VectorEPtr;
typedef vector<EntityPtr> VecEPtr;
typedef list<EntityPtr> EPtrList;



class CIoSimulant;

class CIoEntitySet : public CIoSimHandler  
{
public:
	CIoEntitySet(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	virtual ~CIoEntitySet();
	CIoEntitySet *m_pPreviousEntitySet;
	CIoEntitySet *m_pNextEntitySet;
	CIoEntitySet *GetNextEntitySet(){return m_pNextEntitySet;}
	void SetNextEntitySet(CIoEntitySet *pEntitySet){m_pNextEntitySet=((pEntitySet==NULL) && (pEntitySet != this)? m_pNextEntitySet:pEntitySet );}
	CIoEntitySet *GetPreviousEntitySet(){return m_pPreviousEntitySet;}
	void SetPreviousEntitySet(CIoEntitySet *pEntitySet){m_pPreviousEntitySet=((pEntitySet==NULL) && (pEntitySet != this)? m_pPreviousEntitySet:pEntitySet );}

	//Setting entity properties and names
	deque<string> m_pEPropNames;
	deque<string> m_pEPropInfilenames;
	deque<string> m_pEPropOutfilenames;

	deque<int> m_pEPropFlags;
	deque<string> m_pEArrayNames;
	deque<string> m_pEArrayInfilenames;
	deque<string> m_pEArrayOutfilenames;

	deque<int> m_pEArrayFlags;
	CIoParam *m_pEDefaultParams;

	void DeleteENames();
	void DeleteEFlags();

	CIoParam *GetEDefaultParams(){return m_pEDefaultParams;}
	void CreateEDefaultParams();
	dqstr GetEPropNames(){return m_pEPropNames;}
	dqint GetEPropFlags(){return m_pEPropFlags;}
	dqstr GetEPropArrayNames(){return m_pEArrayNames;}
	dqint GetEPropArrayFlags(){return m_pEArrayFlags;}
	//Methods for accessing individual enity names
	char *GetEName();  //Gets name of m_pProperties array
	string GetEPropertyName(int i);
	string GetEArrayName(int i=0);
	string GetEPropInfilename(int i);
	string GetEPropOutfilename(int i);
	string GetEArrayInfilename(int i);
	string GetEArrayOutfilename(int i);

	void SetEPropertyName(int i, char *sname);
	void SetEPropInfilename(int i, char *sname);
	void SetEPropOutfilename(int i, char *sname);
	void SetEArrayInfilename(int i, char *sname);
	void SetEArrayOutfilename(int i, char *sname);

	void SetEArrayName(int i, char *sname);
	void SetEPropertyFlag(int i, int flag);
	void SetEArrayFlag(int i, int flag);
    int GetEPropertyFlag(int i);
	int GetEArrayFlag(int i);
	void AddEPropName(char *name);
	void AddEArrayName(char *name);
void AddEPropName(string name);
	void AddEArrayName(string name);
	void AddEPropFlag(int flag);
	void AddEArrayFlag(int flag);
	void AddEntityType(CIoEntityType *pET){if(m_pEntityTypeSet)m_pEntityTypeSet->AddEntityType(pET);}
	CIoEntityType *GetEntityType(int index){return(m_pEntityTypeSet==NULL?NULL:m_pEntityTypeSet->GetEntityType(index));}
	//The following methods must call back to the parent 
	//simulant/model
	virtual void CreateEPropNames(){if(m_pParentHandler)m_pParentHandler->CreateESEPropNames(NULL,this);}
	virtual void CreateEPropArrayNames(){if(m_pParentHandler)m_pParentHandler->CreateESEPropArrayNames(NULL,this);}
	virtual void CreateEPropFlags(){if(m_pParentHandler)m_pParentHandler->CreateESEPropFlags(NULL,this);}
	virtual void CreateEPropArrayFlags(){if(m_pParentHandler)m_pParentHandler->CreateESEPropArrayFlags(NULL,this);}

	int GetNumEPropNames(){return (int)(m_pEPropNames.size());}
	int GetNumEArrayNames(){return (int)(m_pEArrayNames.size());}
	int GetNumEPropFlags(){return (int)(m_pEPropFlags.size());}
	int GetNumEArrayFlags(){return (int)(m_pEArrayFlags.size());}

	



	void ReadEPropNames(istream &s);
	void ReadEArrayNames(istream &s);
	void ReadEPropFlags(istream &s);
	void ReadEArrayFlags(istream &s);
	void WriteEPropNames(ostream &s);
	void WriteEArrayNames(ostream &s);
	void WriteEPropFlags(ostream &s);
	void WriteEArrayFlags(ostream &s);

	istream &ReadFlaggedEPropNames(istream &s, int flag, dqint pArrayFlags, int noparams, int index=0);
	ostream &WriteFlaggedEPropNames(ostream &s, int flag, dqint pArrayFlags, int noparams, int index=0);


	char *m_sEntitySetName;
	char *m_sEntitySetClass;

	int m_iSize;
	int m_iNum;

	int m_iID;

	CIoEntityTypeSet *m_pEntityTypeSet;
	//CIoEntity *m_pEntity;

	//Entity set class thisis the name of the class
	//which is used to create entities belonging to this set
	char *m_sEntityClass;

	void SetEntitySetName(const char *name);
	char *GetEntitySetName(){return m_sEntitySetName;}
	void SetEntitySetClass(const char *name);
	char *GetEntitySetClass(){return m_sEntitySetClass;}
	void SetEntityClass(const char *name);
	char *GetEntityClass(){return m_sEntityClass;}

	int GetID(){return m_iID;}
	void SetID(int iID){m_iID=iID;}

	virtual CIoEntityTypeSet *CopyEntityTypeSet(){return ((m_pEntityTypeSet==NULL)?NULL:m_pEntityTypeSet->CopyEntityTypeSet());}
	//The following methods have to be pure virtual we don't know
	//how we're going to create the set of entities yet
  virtual void CreateEntitySet(CIoParam *pEntitySetParam=NULL,
	  CIoParam *pEntityTypeSetParam=NULL){Create(pEntitySetParam, pEntityTypeSetParam);}

	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

   virtual void CreateConfig(){;}
 
	virtual	int CheckParamFormat(CIoParam *pParamData){return((pParamData && (pParamData->GetType()==IO_PARAM_ARRAY)));}
	virtual void CreateDefaultParams();
	virtual void CreatePropNames();
	virtual void CreatePropArrayNames();

	virtual void CreatePropFlags();
	virtual void CreatePropArrayFlags();
	virtual void  Update (CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL); 


	CIoEntityTypeSet *GetEntityTypeSet(){return m_pEntityTypeSet;}
	virtual CIoEntity *GetEntity(int iEntityIndex)=0;



	/*!
	   Method called by all child classes 
	   sets parent handler, simulant and simulation
	   also sets entity id
	*/
	virtual void AddEntity(CIoEntity *pEntity);
	virtual int GetNum(){return m_iNum;}/*{return 0;}*/
	void SetEntityTypeSet(CIoEntityTypeSet *pEntityTypeSet){m_pEntityTypeSet = pEntityTypeSet;}
	virtual CIoEntityType *newEntityType(char *sEntityTypeClass);
	virtual CIoEntity *newEntity(); //This is the entity type that an entity set creates
	                                  //has to be pure abstract
	virtual CIoEntityTypeSet *newEntityTypeSet(char *sEntityTypeSetClass);

	virtual void HandleEntitySetInteraction(CIoEntitySet *pEntitySet);
	virtual void HandleInteractions();
	virtual void HandleStateTransitions();

	/*! The following should be inline!*/
	inline void SetEntityTypeInt(int typeindex, int paramindex, int ival){if(m_pEntityTypeSet)m_pEntityTypeSet->SetEntityTypeInt(typeindex, paramindex, ival);}
	inline int GetEntityTypeInt(int typeindex, int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetEntityTypeInt(typeindex, paramindex):0) ;}
	inline void SetEntityTypeFloat(int typeindex, int paramindex, float fval){if(m_pEntityTypeSet)m_pEntityTypeSet->SetEntityTypeFloat(typeindex, paramindex, fval);}
	inline float GetEntityTypeFloat(int typeindex, int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetEntityTypeFloat(typeindex, paramindex):0) ;}
	inline void SetEntityTypeString(int typeindex, int paramindex, char *sstring){if(m_pEntityTypeSet)m_pEntityTypeSet->SetEntityTypeString(typeindex, paramindex, sstring);}
	inline char *GetEntityTypeString(int typeindex, int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetEntityTypeString(typeindex, paramindex):NULL) ;}
	inline void SetEntityTypeVec(int typeindex, int paramindex, vec *vvec){if(m_pEntityTypeSet)m_pEntityTypeSet->SetEntityTypeVec(typeindex, paramindex, vvec);}
	inline vec *GetEntityTypeVec(int typeindex, int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetEntityTypeVec(typeindex, paramindex):NULL) ;}
	inline void SetEntityTypeMat(int typeindex, int paramindex, matrix *mmat){if(m_pEntityTypeSet)m_pEntityTypeSet->SetEntityTypeMat(typeindex, paramindex, mmat);}
	inline matrix *GetEntityTypeMat(int typeindex, int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetEntityTypeMat(typeindex, paramindex):NULL) ;}

	/*! The following should be inline!*/
	inline void SetEntityTypeSetInt( int paramindex, int ival){if(m_pEntityTypeSet)m_pEntityTypeSet->SetInt( paramindex, ival);}
	inline int GetEntityTypeSetInt( int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetInt( paramindex):0) ;}
	inline void SetEntityTypeSetFloat( int paramindex, float fval){if(m_pEntityTypeSet)m_pEntityTypeSet->SetFloat( paramindex, fval);}
	inline float GetEntityTypeSetFloat( int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetFloat( paramindex):0) ;}
	inline void SetEntityTypeSetString( int paramindex, char *sstring){if(m_pEntityTypeSet)m_pEntityTypeSet->SetString( paramindex, sstring);}
	inline char *GetEntityTypeSetString( int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetString( paramindex):NULL) ;}
	inline void SetEntityTypeSetVec( int paramindex, vec *vvec){if(m_pEntityTypeSet)m_pEntityTypeSet->SetVec( paramindex, vvec);}
	inline vec *GetEntityTypeSetVec( int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetVec( paramindex):NULL) ;}
	inline void SetEntityTypeSetMat( int paramindex, matrix *mmat){if(m_pEntityTypeSet)m_pEntityTypeSet->SetMat( paramindex, mmat);}
	inline matrix *GetEntityTypeSetMat( int paramindex){return(m_pEntityTypeSet?m_pEntityTypeSet->GetMat( paramindex):NULL) ;}
	
	//Virtual handlers of entity set used to create params
	//and properties for entity types and entity type sets

	//These handlers will actually update the default entitytypeset
	//and entity types

	//The developer will override these but these must be called at the end 
	//of the overridden routine to do the actual update
	//e.g. CIoEntitySet::CreateETSPropArrayFlags();
	//must be added to the end of the routine

	//These methods should probably be private and not overideable by the 
	//developer as they just pass methods back to the parent class
	virtual void ETUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL );
	virtual void ESUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntitySet *pES=NULL);
	virtual void ETSUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntityTypeSet *pES=NULL );
	virtual void EUpdate(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL , CIoEntity *pE=NULL, CIoEntitySet *pES=NULL );


	virtual void EHandleInteractions(CIoEntity *pE);
	virtual void EHandleStateTransitions(CIoEntity *pE);

	//Virtual handlers of entity set used to create params
	//and properties for entity types and entity type sets
	virtual void CreateETSPropArrayFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);
	virtual void CreateETSPropArrayNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);

	virtual void CreateETSPropFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);
	virtual void CreateETSPropNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);

	virtual void CreateETSDefaultParams(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL);

	//Need to update the correct entity type
	virtual void CreateETPropArrayFlags(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);
	virtual void CreateETPropArrayNames(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);

	virtual void CreateETPropFlags(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);
	virtual void CreateETPropNames(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);

	virtual void CreateETDefaultParams(CIoParam *pParam=NULL, CIoEntityType *pET=NULL, CIoEntitySet *pES=NULL);

	//Need to update the correct entity type
	//virtual void CreateESPropArrayFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};
	//virtual void CreateESPropArrayNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};

	//virtual void CreateESPropFlags(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};
	//virtual void CreateESPropNames(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};

	//virtual void CreateESDefaultParams(CIoParam *pParam=NULL, CIoEntitySet *pES=NULL){};

	virtual void CreateEntityDefaultParams(CIoParam *pParam=NULL, CIoEntity *pE=NULL, CIoEntitySet *pES=NULL){};


	virtual int ReadEntitySetDefault(::ifstream &ifs);
	virtual int WriteEntitySetDefault(::ofstream &ifs);
	virtual int ReadEntitySetConfigDefault(::ifstream &ifs);
	virtual int WriteEntitySetConfigDefault(::ofstream &ifs);
	virtual int ReadEntitySetStateDefault(::ifstream &ifs);
	virtual int WriteEntitySetStateDefault(::ofstream &ifs);


};

#endif
