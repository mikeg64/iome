#ifndef IO_SIMULATION_ENTITY_H
#define IO_SIMULATION_ENTITY_H
// IoEntity.h: interface for the CIoEntity class.
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
//#if !defined(AFX_IOENTITY_H__50132151_7FF4_4777_AF0A_43BBC5D35EE6__INCLUDED_)
//#define AFX_IOENTITY_H__50132151_7FF4_4777_AF0A_43BBC5D35EE6__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#include <iome/simulation/IoSimHandler.h>
#include <iome/simulation/IoEntityType.h>


enum eIoEntityType{IO_ENTITY_CELL,
				   IO_ENTITY_EXTERNALFIELD,
				   IO_ENTITY_CELLSTRUCTURE 
						 };

class CIoEntity : public CIoSimHandler  
{
public:
	CIoEntity(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	virtual ~CIoEntity();
	virtual void CreateDefaultParams(){if(m_pParentHandler)m_pParentHandler->CreateEntityDefaultParams(NULL, this);}

	virtual void HandleInteractions(){if(m_pParentHandler)m_pParentHandler->EHandleInteractions(this);}
	virtual void HandleStateTransitions(){if(m_pParentHandler)m_pParentHandler->EHandleStateTransitions(this);}

	virtual void Update(CIoSimHandler *pHandler=NULL, CIoParam *pParam =NULL){if(m_pParentHandler)m_pParentHandler->EUpdate(pHandler, pParam, this);}
	virtual int CheckParamFormat(CIoParam *pParamData=NULL);

	CIoEntity *GetNextEntity(){return m_pNextEntity;}
	void SetNextEntity(CIoEntity *pEntity){if(pEntity)m_pNextEntity=pEntity;}
	CIoEntity *GetPreviousEntity(){return m_pPreviousEntity;}
	void SetPreviousEntity(CIoEntity *pEntity){if(pEntity)m_pPreviousEntity=pEntity;}

	CIoEntityType *GetEntityType(){return m_pEntityType;}
	void SetEntityType(CIoEntityType *pEntityType){m_pEntityType = pEntityType;}
    eIoEntityType GetEntityTypeEnum(){return m_eEntityType;}
	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	virtual void CreateEntity(CIoParam *pEntityParams=NULL){Create(pEntityParams);}
	void SetEntityTypeID(int iTypeID){m_iEntityTypeID=(iTypeID>=0?iTypeID:0);}
	int GetEntityTypeID(){return m_iEntityTypeID;}
	int m_iEntityTypeID;
	CIoEntityType *m_pEntityType;
	eIoEntityType m_eEntityType;
	CIoEntity *m_pNextEntity;
	CIoEntity *m_pPreviousEntity;
	int m_iID;


	int GetID(){return m_iID;}
	void SetID(int iID){m_iID=iID;}

	virtual vec *GetPos(){return NULL;}

	virtual int ReadEntityDefault(::istream &ifs);
	virtual int WriteEntityDefault(::ostream &ifs);
	virtual int ReadEntityConfigDefault(::istream &ifs);
	virtual int WriteEntityConfigDefault(::ostream &ifs, int index=0);
	
};

#endif 
