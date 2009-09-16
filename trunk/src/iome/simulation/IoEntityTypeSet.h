#ifndef IO_SIMULATION_ENTITYTYPESET_H
#define IO_SIMULATION_ENTITYTYPESET_H

// IoEntityTypeSet.h: interface for the CIoEntityTypeSet class.
//
//////////////////////////////////////////////////////////////////////
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
//#if !defined(AFX_IOENTITYTYPESET_H__64465770_63FA_4188_8ED1_ECE534E15EA5__INCLUDED_)
//#define AFX_IOENTITYTYPESET_H__64465770_63FA_4188_8ED1_ECE534E15EA5__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#ifndef IO_MSVC
	#include <iome/utils/IoPropertyManager.h>
#else
	#include <iome/utils/IoPropertyManager.h>
#endif
#include <iome/simulation/IoEntityType.h>
#include <iome/simulation/IoSimHandler.h>

class CIoEntitySet;

class CIoEntityTypeSet : public CIoSimHandler  
{
public:
	CIoEntityTypeSet(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	virtual ~CIoEntityTypeSet();

	char *m_sEntityTypeSetName;
	char *m_sEntityTypeSetClass;
	char *m_sEntityTypeClass;

	CIoEntitySet *m_pParentEntitySet;

	CIoEntitySet *GetParentEntitySet(){return m_pParentEntitySet;}
	void SetParentEntitySet(CIoEntitySet *pEntitySet){m_pParentEntitySet=pEntitySet;}

	void SetEntityTypeSetName(const char *name);
	char *GetEntityTypeSetName(){return m_sEntityTypeSetName;}
	void SetEntityTypeSetClass(const char *name);
	char *GetEntityTypeSetClass(){return m_sEntityTypeSetClass;}
	void SetEntityTypeClass(const char *name){};
	char *GetEntityTypeClass(){return m_sEntityTypeClass;}

	virtual CIoEntityTypeSet *CopyEntityTypeSet();
	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	virtual void CreateEntityTypeSet(CIoParam *pEntityTypeSetParams=NULL){Create(pEntityTypeSetParams);}

	CIoEntityType **m_pEntityTypes;

	int GetNumEntityTypes(){return m_iNumEntityTypes;}
	void SetNumEntityTypes(int iNumEntityTypes, int idelete = 0);
	CIoEntityType *GetEntityType(int i);

	//if ipos = -1 the default then the new entity type is appended to the end of the 
	// array else it ovewrites the exitsin entity type at i
	//if the array is not large enough to accomadate the new entity it is increased in size by 5
	void AddEntityType(CIoEntityType *pEntityType, int ipos=0, int del = -1);

	//if removal of an entity type means that more than 5 of the entity types are NULL
	//the array is reduced in size by 5
	void RemoveEntityType(CIoEntityType *pEntityType);
	void RemoveEntityType(int iIndex);
	int CheckParamFormat(CIoParam *pParamData=NULL);
	virtual CIoEntityType *newEntityType(char *sEntityTypeClass){return( new CIoEntityType(m_pParentSimulation, m_pParentSimulant, (CIoSimHandler *)this));}


	/*! The following should be inline!*/
	void SetEntityTypeInt(int typeindex, int paramindex, int ival);
	int GetEntityTypeInt(int typeindex, int paramindex);
	void SetEntityTypeFloat(int typeindex, int paramindex, float fval);
	float GetEntityTypeFloat(int typeindex, int paramindex);
	void SetEntityTypeString(int typeindex, int paramindex, char *sstring);
	char *GetEntityTypeString(int typeindex, int paramindex);
	void SetEntityTypeVec(int typeindex, int paramindex, vec *vvec);
	vec *GetEntityTypeVec(int typeindex, int paramindex);
	void SetEntityTypeMat(int typeindex, int paramindex, matrix *mmat);
	matrix *GetEntityTypeMat(int typeindex, int paramindex);

	//calls parent handler to create its params
	//Need to update the correct entity type
	virtual void CreatePropArrayFlags();
	virtual void CreatePropArrayNames();

	virtual void CreatePropFlags();
	virtual void CreatePropNames();

	
	virtual void CreateDefaultParams();

	//Required methods if eTS to be updated
	virtual void Update(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL );

	virtual int ReadEntityTypeSetDefault(::ifstream &ifs);
	virtual int WriteEntityTypeSetDefault(::ofstream &ifs);
	virtual int ReadEntityTypeSetConfigDefault(::ifstream &ifs);
	virtual int WriteEntityTypeSetConfigDefault(::ofstream &ifs);
	virtual int ReadEntityTypeSetStateDefault(::ifstream &ifs);
	virtual int WriteEntityTypeSetStateDefault(::ofstream &ifs);

private:
	int m_iNumEntityTypes;
	int m_iMaxSize;


};

#endif 
