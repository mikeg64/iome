#ifndef IO_SIMULATION_ENTITYTYPE_H
#define IO_SIMULATION_ENTITYTYPE_H

// IoEntityType.h: interface for the CIoEntityType class.
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
//#if !defined(AFX_IOENTITYTYPE_H__4DE3A1A5_CC85_4ABF_AB64_0059D260378F__INCLUDED_)
//#define AFX_IOENTITYTYPE_H__4DE3A1A5_CC85_4ABF_AB64_0059D260378F__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#ifndef IO_MSVC
	#include <iome/utils/IoPropertyManager.h>
#else
	#include <iome/utils/IoPropertyManager.h>
#endif
#include <iome/simulation/IoSimHandler.h>
//It's possible for an entity to be characterised by a number of differenty types
//for instancea charged particle
// can be of type mass m1
// and of type charge q1
// However we require a mechanism
//preventing the following use case
//type has type mass m1
//and has type mass m2
enum eIoEntityTypeType{IO_ENTITY_TYPE_TYPE_STAR 
						 };


class CIoEntity;
class CIoEntityType : public CIoSimHandler
{
public:
	CIoEntityType(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	virtual ~CIoEntityType();
	
	char *m_sEntityTypeName;
	char *m_sEntityTypeClass;

	int m_iID;

	CIoEntitySet *m_pParentEntitySet;

	CIoEntitySet *GetParentEntitySet(){return m_pParentEntitySet;}
	void SetParentEntitySet(CIoEntitySet *pEntitySet){m_pParentEntitySet=pEntitySet;}

	int GetID(){return m_iID;}
	void SetID(int iID){m_iID=iID;}

	void SetEntityTypeName(const char *name);
	char *GetEntityTypeName(){return m_sEntityTypeName;}
	void SetEntityTypeClass(const char *name);
	char *GetEntityTypeClass(){return m_sEntityTypeClass;}

	virtual CIoEntityType *CopyEntityType();

	CIoEntityType *m_pNextEntityType;

	
    eIoEntityTypeType  m_eEntityTypeType;

	eIoEntityTypeType GetEntityTypeType(){return m_eEntityTypeType;}
	CIoEntityType *GetNext(){return m_pNextEntityType;}
	void SetNext(CIoEntityType *pNextEntityType){m_pNextEntityType = pNextEntityType;}
	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	virtual void CreateEntityType(CIoParam *pEntityTypeParams=NULL){Create(pEntityTypeParams);}
	virtual int CheckParamFormat(CIoParam *pParamData=NULL);
	//virtual void CreateDefaultBehaviourParams()=0;
	//virtual int CheckBehaviourParamFormat(CIoParam *pBehaviourParams=NULL);
	//virtual void UpdateInteraction(CIoEntity *pEntity, CIoEntity *pInteractingEntity){;}
	//virtual void UpdateState(CIoEntity *pEntity);

	//calls parent handler to create its params
	//Need to update the correct entity type
	virtual void CreatePropArrayFlags();
	virtual void CreatePropArrayNames();

	virtual void CreatePropFlags();
	virtual void CreatePropNames();

	
	virtual void CreateDefaultParams();
	//Required methods if eTS to be updated
	virtual void Update(CIoSimHandler *pHandler=NULL, CIoParam *pParam=NULL );
	virtual int ReadEntityTypeDefault(ifstream &ifs);
	virtual int WriteEntityTypeDefault(ofstream &ifs);
	virtual int ReadEntityTypeConfigDefault(ifstream &ifs);
	virtual int WriteEntityTypeConfigDefault(ofstream &ifs);
	virtual int ReadEntityTypeStateDefault(ifstream &ifs);
	virtual int WriteEntityTypeStateDefault(ofstream &ifs);

};

#endif 
