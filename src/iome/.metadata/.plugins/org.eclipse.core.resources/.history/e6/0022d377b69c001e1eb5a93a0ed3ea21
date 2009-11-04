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


// IoSimulant.cpp: implementation of the CIoSimulant class.
//
//////////////////////////////////////////////////////////////////////


#include "IoSimulant.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoSimulant::CIoSimulant(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoSimHandler(pParentSimulation, pParentSimulant, pParentHandler)
{
	//m_sSimulantName = new char [62];
	//m_sSimulantName [61] = '\0';
	m_sSimulantName = NULL;
	SetSimulantName("DefaultSimulant");
	m_pNextSimulant=NULL;
	m_pNextSimulantState=NULL;
	m_pParentSimulant = NULL;
	m_iCreateMethod = 1;
	m_inumprocs=1;

	
	m_iStepNum=0;
	
	//this->DeleteFlags();
	//this->DeleteNames();
	//this->CreatePropNames();
	//this->CreatePropFlags();
	//this->CreatePropArrayFlags();
	//this->CreatePropArrayNames();
}

CIoSimulant::~CIoSimulant()
{
	delete [] m_sSimulantName;


	//DeleteProperties();
	CIoSimulant *pTempSimulant = m_pNextSimulant;
	CIoSimulant *pCurrentSimulant = m_pNextSimulant;
	while(pTempSimulant)
	{
		pCurrentSimulant = pTempSimulant;
		pTempSimulant = pCurrentSimulant->GetNextSimulant();
		delete pCurrentSimulant;
	}


	//Delete any stored state simulants
	pTempSimulant = m_pNextSimulantState;
	pCurrentSimulant = m_pNextSimulantState;
	while(pTempSimulant)
	{
		pCurrentSimulant = pTempSimulant;
		pTempSimulant = pCurrentSimulant->GetNextSimulantState();
		delete pCurrentSimulant;
	}
	

}





CIoEntityType *CIoSimulant::newEntityType(CIoEntitySet *pES, char *sETClass)
{
	CIoEntityType *pEntityType = NULL;
	if(strcmp(sETClass, "EntityType")==0)
			pEntityType =  new CIoEntityType(m_pParentSimulation, this, (CIoSimHandler *)pES);
	return pEntityType;
}




void CIoSimulant::HandleInteractions()
{

}

void CIoSimulant::HandleStateTransitions()
{


}





void CIoSimulant::SetSimulantName(const char *name)
{
	if(m_sSimulantName && name)
	{
		delete [] m_sSimulantName;
		m_sSimulantName=NULL;
	}

	if(name)
	{
		m_sSimulantName = (char *) new char [1+strlen(name)];
		strcpy(m_sSimulantName, name);
	}


}

CIoSimulant *CIoSimulant::GetSimulant(int i)
{
	CIoSimulant *pSimulant = this;
	int count = 0;
	
    while(pSimulant && i<count++)
		pSimulant = pSimulant->GetNextSimulant();

	return pSimulant;
}


void CIoSimulant::AddSimulantState(CIoSimulant *pSimulant)
{
	CIoSimulant *pCurrentSimulant=this;
	while(pCurrentSimulant->GetNextSimulantState())
		pCurrentSimulant=pCurrentSimulant->GetNextSimulantState();

	pCurrentSimulant->m_pNextSimulantState=pSimulant;
}






#ifdef IO_GNUGPP
	#ifdef IO_CYGWIN_WIN32
		main(){}
	#endif
#endif



