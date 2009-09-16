// IoEntity.cpp: implementation of the CIoEntity class.
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

#include "IoEntity.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoEntity::CIoEntity(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoSimHandler(pParentSimulation, pParentSimulant, pParentHandler)
{
	m_pEntityType = NULL;
	m_iEntityTypeID=-1;
	m_pNextEntity=NULL;
	m_pPreviousEntity=NULL;
	m_iID=0;

}

CIoEntity::~CIoEntity()
{

}



int CIoEntity::CheckParamFormat(CIoParam *pParamData)
{

	//this format will always be an array of data
	if(pParamData && pParamData->GetType()==IO_PARAM_ARRAY)
		return 1;
	else
		return 0;


}

int CIoEntity::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=0;

	if(pParams && m_pProperties && (m_pProperties->CheckParam(pParams)))
	{
		CreateProperties(pParams);
	}
	else
		CreateDefaultParams();

	return status;
}

int CIoEntity::ReadEntityDefault(::istream &ifs)
{
	
	return 1;

}

int CIoEntity::WriteEntityDefault(::ostream &ifs)
{
	
	return 1;
}

int CIoEntity::ReadEntityConfigDefault(::istream &ifs)
{
        int iid;
		ifs >> iid;
		ReadProps(ifs, GetNumProps());
		return 1;

}

int CIoEntity::WriteEntityConfigDefault(::ostream &ifs, int index)
{
	ifs << index;
	WriteProps(ifs, GetNumProps());
	return 1;
}






