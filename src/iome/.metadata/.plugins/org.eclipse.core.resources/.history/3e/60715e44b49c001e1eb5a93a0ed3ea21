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


// IoEntityType.cpp: implementation of the CIoEntityType class.
//
//////////////////////////////////////////////////////////////////////

#include "IoEntityType.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoEntityType::CIoEntityType(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoSimHandler(pParentSimulation, pParentSimulant, pParentHandler)
{
	m_pNextEntityType = NULL;
	m_sEntityTypeName = NULL;
	m_sEntityTypeClass = NULL;
	SetEntityTypeName("DefaultEntityType");
	SetEntityTypeClass("EntityType");

	m_pParentEntitySet=(CIoEntitySet *)pParentHandler;

	m_iID=0;

	

}

CIoEntityType::~CIoEntityType()
{
	if(m_sEntityTypeClass)
		delete [] m_sEntityTypeClass;

	if(m_sEntityTypeName)
		delete [] m_sEntityTypeName;
}

void CIoEntityType::SetEntityTypeClass(const char *name)
{
	if(m_sEntityTypeClass)
	{
		delete [] m_sEntityTypeClass;
		m_sEntityTypeClass = NULL;
	}


	if(name)
	{
		m_sEntityTypeClass = (char *) new char [1+strlen(name)];
		strcpy(m_sEntityTypeClass, name);
	}
}

void CIoEntityType::SetEntityTypeName(const char *name)
{
	if(m_sEntityTypeName)
	{
		delete [] m_sEntityTypeName;
		m_sEntityTypeName = NULL;
	}



	if(name)
	{
		m_sEntityTypeName = (char *) new char [1+strlen(name)];
		strcpy(m_sEntityTypeName, name);
	}
}


CIoEntityType *CIoEntityType::CopyEntityType()
{
	CIoEntityType *pET=new CIoEntityType;

	CIoParam *pETParam=NULL;
	char sname[100];

	sprintf(sname, "Copy_%s", GetEntityTypeName());
	pET->SetEntityTypeClass(GetEntityTypeClass());
	pET->SetEntityTypeName(sname);

	pETParam=new CIoParam(m_pProperties);
	pET->DeleteProperties();
	pET->m_pProperties=pETParam;

	return pET;
}




int CIoEntityType::CheckParamFormat(CIoParam *pParamData)
{
	//this format will always be an array of data
	if(pParamData && pParamData->GetType()==IO_PARAM_ARRAY)
		return 1;
	else
		return 0;
}



/*void CIoEntityType::UpdateState(CIoEntity *pEntity)
{

    int i;

     //Check each of the beahviours and use these to update the 
	 //state of the entity
	if(m_pBehaviours)
		m_pBehaviours->UpdateState(pEntity);



}*/

int CIoEntityType::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=0;
	if(m_pProperties==NULL) CreateDefaultParams();
	if((m_pProperties->CheckParam(pParams))==1)
		/*!
			Call the action for creating the entity type 
		*/
		CreateProperties(pParams);

	else CreateDefaultParams();

	//call at entity type creation time
	this->DeleteFlags();
	this->DeleteNames();
	this->CreatePropNames();
	this->CreatePropFlags();
	this->CreatePropArrayFlags();
	this->CreatePropArrayNames();

	return status;

}

	//Need to update the correct entity type
void CIoEntityType::CreatePropArrayFlags()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETPropArrayFlags(NULL, this, m_pParentEntitySet);

}

void CIoEntityType::CreatePropArrayNames()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETPropArrayNames(NULL, this, m_pParentEntitySet);

}


void CIoEntityType::CreatePropFlags()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETPropFlags(NULL, this, m_pParentEntitySet);


}

void CIoEntityType::CreatePropNames()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETPropNames(NULL, this,m_pParentEntitySet );


}

	//calls parent handler to create its params
void CIoEntityType::CreateDefaultParams()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETDefaultParams(NULL, this, m_pParentEntitySet);

}

void CIoEntityType::Update(CIoSimHandler *pHandler, CIoParam *pParam )
{
	if(m_pParentHandler)
		m_pParentHandler->ETUpdate(pHandler, pParam, this, m_pParentEntitySet);
}



int CIoEntityType::ReadEntityTypeDefault(ifstream &ifs)
{

	//Skip et name
	skipcmt( ifs);
	ifs>>m_sEntityTypeName;

	//skip et class
	skipcmt(ifs);
	skipcmt(ifs);  //if model class is not the same should return status 1



       //et prop names
		skipcmt(ifs);//skip line of prop names
		ReadPropNames(ifs);

		//et prop array names
		skipcmt(ifs);
		ReadArrayNames(ifs);
	
		//Read properties
		skipcmt(ifs);
		ReadProps(ifs, GetNumProps());

		//Read the flags for the properties
		//these will be used to determine which
		//properties get read from and writtent to config files and state files
		skipcmt(ifs);
		ReadPropFlags(ifs);
		skipcmt(ifs);
		ReadArrayFlags(ifs);
	
		return 1;
}

int CIoEntityType::WriteEntityTypeDefault(ofstream &ifs)
{

	//Skip EntityType name
	ifs<<"#EntityType name:" << ::endl;
	ifs<<m_sEntityTypeName<< ::endl;

	//skip EntityType class
	ifs<<"#EntityType class:" << ::endl;
	ifs<<m_sEntityTypeClass<<::endl;  //if EntityType class is not the same should return status 1


       //EntityType prop names
		ifs<<"#EntityType prop names:"<<::endl;
		WritePropNames(ifs);
		//EntityType prop array names
		ifs<<"#EntityType prop array names:"<<::endl;
		WriteArrayNames(ifs);
		//Read properties
		ifs<<"#EntityType properties:"<<::endl;
		WriteProps(ifs, GetNumProps());

		//Read the flags for the properties
		//these will be used to determine which
		//properties get read from and writtent to config files and state files
		ifs<<"#EntityType prop flags:"<<::endl;
	WritePropFlags(ifs);
	ifs<<"#EntityType prop array flags:"<<::endl;
	WriteArrayFlags(ifs);
	return 1;

}

int CIoEntityType::ReadEntityTypeConfigDefault(ifstream &ifs)
{
				int i;
	
	//Skip es name
	skipcmt( ifs);
	ifs>>m_sEntityTypeName;




	//m_iNum is altered when 
	//entities added to entity set
	//ifs>>m_iNum;

       //es prop names
		skipcmt(ifs);//skip line of prop names
		ReadFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(),GetNumProps());
	

		//es prop array names
	
		//Read the actual flagged properties
		skipcmt(ifs);
		ReadFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());


	

		return 1;

}

int CIoEntityType::WriteEntityTypeConfigDefault(ofstream &ifs)
{
			int i;
			CIoEntityType *pEntityType;

	//Skip EntityType name
	ifs<<"#EntityType name:" << ::endl;
	ifs<<m_sEntityTypeName<< ::endl;



       //EntityType prop names
	ifs<<"#EntityType prop names:"<<::endl;
	WriteFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());
	

		//EntityType prop array names
		//ifs<<"#EntityType prop array names:"<<::endl;

		//Read properties
		ifs<<"#EntityType properties:"<<::endl;
		WriteFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(),GetNumProps());

	

	


	return 1;
}

int CIoEntityType::ReadEntityTypeStateDefault(ifstream &ifs)
{
				int i;
	
	//Skip es name
	skipcmt( ifs);
	ifs>>m_sEntityTypeName;




	//m_iNum is altered when 
	//entities added to entity set
	//ifs>>m_iNum;

       //es prop names
		skipcmt(ifs);//skip line of prop names
		ReadFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());
	

		//es prop array names
		//skipcmt(ifs);

		//Read the actual flagged properties
		skipcmt(ifs);
		ReadFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());


	

		return 1;

}

int CIoEntityType::WriteEntityTypeStateDefault(ofstream &ifs)
{
		int i;
		CIoEntityType *pEntityType;

		//Skip EntityType name
		ifs<<"#EntityType name:" << ::endl;
		ifs<<m_sEntityTypeName<< ::endl;



       //EntityType prop names
		ifs<<"#EntityType prop names:"<<::endl;
		WriteFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());

		//EntityType prop array names
		//ifs<<"#EntityType prop array names:"<<::endl;
		//	m_pPropArrayNames->WriteFlaggedParamArray(ifs, m_pPropArrayFlags->GetParam(0), m_pPropArrayFlags->GetParam(1), m_pPropArrayNames->GetNumParams());

		//Read properties
		ifs<<"#EntityType properties:"<<::endl;
		WriteFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());

	

	


	return 1;
}






