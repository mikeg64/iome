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


#include "IoEntityArray1d.h"

CIoEntityArray1d::CIoEntityArray1d(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoEntitySet(pParentSimulation, pParentSimulant, pParentHandler)
{
	SetEntitySetName("EntityArray1d");
	SetEntitySetClass("EntityArray1d");
	m_pEntity=NULL;  //Pointer to first element in the
	                       //entity collection
	m_iSize=100;
	m_iNum=0;

	//The default array size is 100 elements
	m_pEntity = (CIoEntity **)new CIoEntity * [100];
	for(int i=0; i<m_iSize; i++) m_pEntity [i]=NULL;
}

CIoEntityArray1d::~CIoEntityArray1d(void)
{
	CIoEntity *pEntity;
	if(m_pEntity)
	{
		for(int i=0; i<m_iNum; i++)
		{
			if(pEntity= m_pEntity [i])
						delete pEntity;

		}
		delete [] m_pEntity;
		m_iNum=0;
	}
}

int CIoEntityArray1d::GetNum()
{
	return m_iNum;
}




void CIoEntityArray1d::AddEntity(CIoEntity *pEntity)
{
  CIoEntity **pNewEntity;
  int i;
  int iOldSize=m_iSize;
	
	if(pEntity)
	{
		if(m_iSize==m_iNum)
		{
			m_iSize+=100;
			pNewEntity = (CIoEntity **)new CIoEntity * [m_iSize];
			for(i=0; i<iOldSize; i++) 
			{
				pNewEntity [i]= m_pEntity [i];
				pNewEntity [i]->SetID(i);
			}
			for(i=iOldSize; i<m_iSize; i++) pNewEntity [i]= NULL;

			delete [] m_pEntity;
			m_pEntity = pNewEntity;
		}

		pEntity->SetID(m_iNum);
		m_pEntity [ m_iNum ] = pEntity;
		m_iNum ++;
  }

}


CIoEntity *CIoEntityArray1d::GetEntity(int iIndex)
{
	if(iIndex<m_iSize)
		return m_pEntity [iIndex];
	else
		return NULL;
}

void CIoEntityArray1d::HandleStateTransitions()
{
   	CIoEntity *pEntity;
	if(m_pEntity)
	{
		for(int i=0; i<m_iNum; i++)
		{
			if(pEntity= m_pEntity [i])
						pEntity->HandleStateTransitions();

		}
	}

	CIoEntitySet::HandleStateTransitions();
}
