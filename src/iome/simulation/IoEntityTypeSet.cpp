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


// IoEntityTypeSet.cpp: implementation of the CIoEntityTypeSet class.
//
//////////////////////////////////////////////////////////////////////

#include <iome/simulation/IoEntityTypeSet.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoEntityTypeSet::CIoEntityTypeSet(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoSimHandler(pParentSimulation, pParentSimulant, pParentHandler)
{
	m_iNumEntityTypes = 0;
	m_iMaxSize = 10;
	m_pEntityTypes = NULL;
	m_sEntityTypeSetName = NULL;
	m_sEntityTypeSetClass = NULL;
	SetEntityTypeSetName("DefaultEntityTypeSet");
	SetEntityTypeSetClass("EntityTypeSet");
	SetEntityTypeClass("EntityType");

	m_pParentEntitySet=(CIoEntitySet *)pParentHandler;

	//The default array size is 100 elements
	m_pEntityTypes = (CIoEntityType **)new CIoEntityType * [10];
	for(int i=0; i<m_iMaxSize; i++)
	{
		m_pEntityTypes [i]=NULL;
	}

	

}

CIoEntityTypeSet::~CIoEntityTypeSet()
{
	int i;
    CIoEntityType *pEntityType;
	
	if(m_pEntityTypes != NULL)
	{
		
			for(i=0; i<m_iNumEntityTypes; i++)
			{
				pEntityType = m_pEntityTypes [i];
				if(pEntityType)
					delete pEntityType;

			}

		delete [] m_pEntityTypes;
	 }

	if(m_sEntityTypeSetClass)
		delete [] m_sEntityTypeSetClass;

	if(m_sEntityTypeSetName)
		delete [] m_sEntityTypeSetName;
}



CIoEntityTypeSet *CIoEntityTypeSet::CopyEntityTypeSet()
{
	CIoEntityTypeSet *pETSet=new CIoEntityTypeSet;
	CIoParam *pETSetParam=NULL;
	char sname[100];
	CIoEntityType *pET=NULL, *pETCopy=NULL;

	sprintf(sname, "Copy_%s", GetEntityTypeSetName());
	pETSet->SetEntityTypeSetClass(GetEntityTypeSetClass());
	pETSet->SetEntityTypeSetName(sname);

	pETSetParam=new CIoParam(m_pProperties);
	pETSet->DeleteProperties();
	pETSet->m_pProperties=pETSetParam;

	for(int i=0; i<GetNumEntityTypes(); i++)
	{
		pET=GetEntityType(i);
		if(pETCopy=pET->CopyEntityType())
			pETSet->AddEntityType(pETCopy, i);
	}

	//Check propertymanager members are set correctly
	//check prop names and array names set correctly
	return pETSet;
}

void CIoEntityTypeSet::SetEntityTypeSetClass(const char *name)
{
	if(m_sEntityTypeSetClass)
	{
		delete [] m_sEntityTypeSetClass;
		m_sEntityTypeSetClass = NULL;
	}


	if(name)
	{
		m_sEntityTypeSetClass = (char *) new char [1+strlen(name)];
		strcpy(m_sEntityTypeSetClass, name);
	}
}

void CIoEntityTypeSet::SetEntityTypeSetName(const char *name)
{
	if(m_sEntityTypeSetName)
	{
		delete [] m_sEntityTypeSetName;
		m_sEntityTypeSetName = NULL;
	}



	if(name)
	{
		m_sEntityTypeSetName = (char *) new char [1+strlen(name)];
		strcpy(m_sEntityTypeSetName, name);
	}
}


CIoEntityType *CIoEntityTypeSet::GetEntityType(int i)
{
   if(i<m_iMaxSize && m_iMaxSize >0)
	   return  m_pEntityTypes [i];
   else
	   return NULL;
}

void CIoEntityTypeSet::AddEntityType(CIoEntityType *pEntityType, int ipos, int del)
{
   CIoEntityType **pNewEntityType;
  int i;
  int iOldSize=m_iMaxSize;
	
	if(pEntityType)
	{
		if(m_iMaxSize==m_iNumEntityTypes)
		{
			m_iMaxSize+=100;
			pNewEntityType = (CIoEntityType **)new CIoEntityType * [m_iMaxSize];
			for(i=0; i<iOldSize; i++) pNewEntityType [i]= m_pEntityTypes [i];
			for(i=iOldSize; i<m_iMaxSize; i++) pNewEntityType [i]= NULL;

			delete [] m_pEntityTypes;
			m_pEntityTypes = pNewEntityType;
		}

		pEntityType->SetID(m_iNumEntityTypes);
		pEntityType->SetParentEntitySet(this->GetParentEntitySet());
		m_pEntityTypes [ m_iNumEntityTypes ] = pEntityType;
		m_iNumEntityTypes ++;
		

  }

}

void CIoEntityTypeSet::RemoveEntityType(CIoEntityType *pEntityType)
{
	int i=0;
	int ifound = 0;

	while(i<m_iNumEntityTypes && !ifound)
	{
		if(m_pEntityTypes [i] == pEntityType)
						             ifound = 1;
		else
		  i++;
	}

	if(ifound)
		RemoveEntityType(i);
}

void CIoEntityTypeSet::RemoveEntityType(int i)
{

   int icount = 0;
   int j;
   int inewmaxsize=m_iMaxSize;
   CIoEntityType **pTempTypeSet;
   CIoEntityType *pEntityType=NULL;

   if(i<m_iNumEntityTypes)
   {
	   if((m_iMaxSize-m_iNumEntityTypes)>10)
						inewmaxsize = m_iMaxSize-5;

		//Create a temporary array
		pTempTypeSet = (CIoEntityType **)new CIoEntityType * [inewmaxsize];
		for(j=0; j<inewmaxsize; j++)
				pTempTypeSet [j] = NULL;

		//Copy in the old array
		for(j=0; j<i; j++)
			pTempTypeSet [j] = m_pEntityTypes [j];

		for(j=i; j<m_iNumEntityTypes-1; j++)
			pTempTypeSet [j] = m_pEntityTypes [j+1];

		m_iNumEntityTypes --;
		m_iMaxSize = inewmaxsize;

		//set correct ids for entity type
		for(j=0; j<m_iNumEntityTypes; j++)
			if(pEntityType=m_pEntityTypes [j])
				pEntityType->SetID(j);

		delete [] m_pEntityTypes;
		m_pEntityTypes = pTempTypeSet;
   }

}

int CIoEntityTypeSet::CheckParamFormat(CIoParam *pParamData)
{


	//this format will always be an array of data
	if(pParamData && pParamData->GetType()==IO_PARAM_ARRAY)
		return 1;
	else
		return 0;


}

void CIoEntityTypeSet::SetNumEntityTypes(int iNumEntityTypes, int idelete)
{
	int iCount;
	
	CIoEntityType *pEntityType;
	CIoEntityType **pTempEntityTypes;
	int i;

    pTempEntityTypes = (CIoEntityType **)new CIoEntityType * [iNumEntityTypes];
	{
		for(i=0; i<iNumEntityTypes; i++)
			pTempEntityTypes [i] = NULL;
		
        if(idelete && m_pEntityTypes)
			for(i=0; i<m_iNumEntityTypes, i<iNumEntityTypes; i++)
				pTempEntityTypes [i] = m_pEntityTypes [i];
	}
	
	if(m_pEntityTypes != NULL)
	{
		if(!idelete)
		{
			for(i=0; i<m_iNumEntityTypes; i++)
			{
				pEntityType = m_pEntityTypes [i];
				if(pEntityType)
					delete pEntityType;

			}
		}
		else if(idelete && iNumEntityTypes < m_iNumEntityTypes)
		{
            //case where m_iNumEntityTypes > iNumEntityTypes
			//EntityType set is shrinking!
			//Must remember to delete the extra behaviours
			for(i=iNumEntityTypes; i<m_iNumEntityTypes; i++)
			{
				pEntityType = m_pEntityTypes [i];
				if(pEntityType)
					delete pEntityType;

			}

		}
		delete [] m_pEntityTypes;
	 } 

	iCount = iNumEntityTypes;
	if(m_pEntityTypes)
	{
		iCount = 0;
		for(i=0; i<iNumEntityTypes; i++)
		{
			pEntityType = m_pEntityTypes [i];
			if(pEntityType)
					iCount++;
		}
	}

	m_pEntityTypes = pTempEntityTypes;
	m_iMaxSize = iNumEntityTypes;
	m_iNumEntityTypes = iCount;
}


int CIoEntityTypeSet::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int i,status=0;
	CIoEntityType *pET=NULL;

	//Delete any existing entity types
	for(i=0; i<GetNumEntityTypes(); i++)
	{
		if(pET=GetEntityType(i))
		{
			RemoveEntityType(pET);
			delete pET;
		}

	}


	if(m_pProperties==NULL) CreateDefaultParams();
	if((m_pProperties->CheckParam(pParams))==1)
		/*!
			Call the action for creating the entity type set
		*/
		CreateProperties(pParams);
	else CreateDefaultParams();

	//Must be called at creation
	this->DeleteFlags();
	this->DeleteNames();
	this->CreatePropNames();
	this->CreatePropFlags();
	this->CreatePropArrayFlags();
	this->CreatePropArrayNames();

	return status;
}

void CIoEntityTypeSet::SetEntityTypeInt(int typeindex, int paramindex, int ival)
{
	CIoEntityType *pEntityType=GetEntityType(typeindex);
	if(pEntityType)
		pEntityType->SetInt(paramindex, ival);
}

int CIoEntityTypeSet::GetEntityTypeInt(int typeindex, int paramindex)
{
	int ival=0;
	CIoEntityType *pEntityType=GetEntityType(typeindex);
	if(pEntityType)
		ival=pEntityType->GetInt(paramindex);

	return ival;
}

void CIoEntityTypeSet::SetEntityTypeFloat(int typeindex, int paramindex, float fval)
{
	CIoEntityType *pEntityType=GetEntityType(typeindex);
	if(pEntityType)
		pEntityType->SetFloat(paramindex, fval);

}

float CIoEntityTypeSet::GetEntityTypeFloat(int typeindex, int paramindex)
{
	float fval=0;
	CIoEntityType *pEntityType=GetEntityType(typeindex);
	if(pEntityType)
		fval=pEntityType->GetFloat(paramindex);

	return fval;
}

void CIoEntityTypeSet::SetEntityTypeString(int typeindex, int paramindex, char *sstring)
{
	CIoEntityType *pEntityType=GetEntityType(typeindex);
	if(pEntityType)
		pEntityType->SetString(paramindex, sstring);
}

char *CIoEntityTypeSet::GetEntityTypeString(int typeindex, int paramindex)
{
	char *sval=NULL;
	CIoEntityType *pEntityType=GetEntityType(typeindex);
	if(pEntityType)
		sval=pEntityType->GetString(paramindex);

	return sval;
}

void CIoEntityTypeSet::SetEntityTypeVec(int typeindex, int paramindex, vec *vvec)
{
	
	if(CIoEntityType *pEntityType=GetEntityType(typeindex))
		pEntityType->SetVec(paramindex, vvec);
}

vec *CIoEntityTypeSet::GetEntityTypeVec(int typeindex, int paramindex)
{
	vec *mval=NULL;

	CIoEntityType *pEntityType=GetEntityType(typeindex);
	if(pEntityType)
		mval=pEntityType->GetVec(paramindex);

	return mval;
}

void CIoEntityTypeSet::SetEntityTypeMat(int typeindex, int paramindex, matrix *mmat)
{
	CIoEntityType *pEntityType=GetEntityType(typeindex);
	if(pEntityType)
		pEntityType->SetMat(paramindex, mmat);
}

matrix *CIoEntityTypeSet::GetEntityTypeMat(int typeindex, int paramindex)
{
	matrix *mval=NULL;

	CIoEntityType *pEntityType=GetEntityType(typeindex);
	if(pEntityType)
		mval=pEntityType->GetMat(paramindex);

	return mval;

}

	//Need to update the correct entity type
void CIoEntityTypeSet::CreatePropArrayFlags()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETSPropArrayFlags(NULL, this);

}

void CIoEntityTypeSet::CreatePropArrayNames()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETSPropArrayNames(NULL, this);

}


void CIoEntityTypeSet::CreatePropFlags()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETSPropFlags(NULL, this);


}

void CIoEntityTypeSet::CreatePropNames()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETSPropNames(NULL, this);


}

	//calls parent handler to create its params
void CIoEntityTypeSet::CreateDefaultParams()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETSDefaultParams(NULL, this);

}

void CIoEntityTypeSet::Update(CIoSimHandler *pHandler, CIoParam *pParam )
{
	if(m_pParentHandler)
		m_pParentHandler->ETSUpdate(pHandler, pParam, this);

}



int CIoEntityTypeSet::ReadEntityTypeSetDefault(::ifstream &ifs)
{
	int i, iNumET;
	CIoEntityType *pET;
	//Skip es name
	skipcmt( ifs);
	ifs>>m_sEntityTypeSetName;

	//skip es class
	skipcmt(ifs);
	skipcmt(ifs);  //if model class is not the same should return status 1

	//num entity types
	skipcmt(ifs);
	ifs>>iNumET;

	//m_iNum is altered when 
	//entities added to entity set
	//ifs>>m_iNum;

       //es prop names
		skipcmt(ifs);//skip line of prop names
		ReadPropNames(ifs);
		//es prop array names
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
		//Read entity type set
		//Note a call to newModel must create the entittype set
		//instance (if this is required)
		//number of entity types
		//must be written here
		for(i=0; i<iNumET; i++)
		{
			pET=newEntityType(m_sEntityTypeClass);//newEntityType will set parent correctly
			AddEntityType(pET);
			pET->ReadEntityTypeDefault(ifs);
		}




		return 1;
}

int CIoEntityTypeSet::WriteEntityTypeSetDefault(::ofstream &ifs)
{
	int i;
	int iNumET=GetNumEntityTypes();
	CIoEntityType *pET;
	//Skip EntityTypeSet name
	ifs<<"#EntityTypeSet name:" << ::endl;
	ifs<<m_sEntityTypeSetName<< ::endl;

	//skip EntityTypeSet class
	ifs<<"#EntityTypeSet class:" << ::endl;
	ifs<<m_sEntityTypeSetClass<<::endl;  //if EntityTypeSet class is not the same should return status 1


       //EntityTypeSet prop names
	ifs<<"#EntityTypeSet prop names:"<<::endl;
	WritePropNames(ifs);
		//EntityTypeSet prop array names
		ifs<<"#EntityTypeSet prop array names:"<<::endl;
		WriteArrayNames(ifs);
		//Read properties
		ifs<<"#EntityTypeSet properties:"<<::endl;
		WriteProps(ifs, GetNumProps());

		//Read the flags for the properties
		//these will be used to determine which
		//properties get read from and writtent to config files and state files
		ifs<<"#EntityTypeSet prop flags:"<<::endl;
		WritePropFlags(ifs);
		ifs<<"#EntityTypeSet prop array flags:"<<::endl;
		WriteArrayFlags(ifs);
		
		for(i=0; i<iNumET; i++)
		{
			if(pET=(this->GetEntityType(i)))
					pET->WriteEntityTypeDefault(ifs);
		}

	return 1;

}

int CIoEntityTypeSet::ReadEntityTypeSetConfigDefault(::ifstream &ifs)
{
			int i;
	CIoEntityType *pEntityType;
	//Skip es name
	skipcmt( ifs);
	ifs>>m_sEntityTypeSetName;




	//m_iNum is altered when 
	//entities added to entity set
	//ifs>>m_iNum;

       //es prop names
		skipcmt(ifs);//skip line of prop names
		ReadFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());
	
			//Read the actual flagged properties
		skipcmt(ifs);
		ReadFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());


		//Read entity type set
		//Note a call to newModel must create the entittype set
		//instance (if this is required)
		for(i=0; i<GetNumEntityTypes(); i++)
		{
			if((pEntityType=GetEntityType(i)))
						pEntityType->ReadEntityTypeConfigDefault(ifs);
		}

		return 1;

}

int CIoEntityTypeSet::WriteEntityTypeSetConfigDefault(::ofstream &ifs)
{
		int i;
			CIoEntityType *pEntityType;

	//Skip EntityTypeSet name
	ifs<<"#EntityTypeSet name:" << ::endl;
	ifs<<m_sEntityTypeSetName<< ::endl;



       //EntityTypeSet prop names
	ifs<<"#EntityTypeSet prop names:"<<::endl;
	WriteFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());
	

	
		//Read properties
		ifs<<"#EntityTypeSet properties:"<<::endl;
			WriteFlaggedProps(ifs, GetArrayFlag(0), m_pPropFlags,GetNumProps());

	

		for(i=0; i<GetNumEntityTypes(); i++)
		{
			if(pEntityType=GetEntityType(i))
						pEntityType->WriteEntityTypeConfigDefault(ifs);
		}


	return 1;
}

int CIoEntityTypeSet::ReadEntityTypeSetStateDefault(::ifstream &ifs)
{
			int i;
	CIoEntityType *pEntityType;
	//Skip es name
	skipcmt( ifs);
	ifs>>m_sEntityTypeSetName;




	//m_iNum is altered when 
	//entities added to entity set
	//ifs>>m_iNum;

       //es prop names
		skipcmt(ifs);//skip line of prop names

		ReadFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());

		//es prop array names

		//Read the actual flagged properties
		skipcmt(ifs);
		ReadFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());


		//Read entity type set
		//Note a call to newModel must create the entittype set
		//instance (if this is required)
		for(i=0; i<GetNumEntityTypes(); i++)
		{
			if(pEntityType=this->GetEntityType(i))
						pEntityType->ReadEntityTypeStateDefault(ifs);
		}

		return 1;

}

int CIoEntityTypeSet::WriteEntityTypeSetStateDefault(::ofstream &ifs)
{
			int i;
			CIoEntityType *pEntityType;

	//Skip EntityTypeSet name
	ifs<<"#EntityTypeSet name:" << ::endl;
	ifs<<m_sEntityTypeSetName<< ::endl;



       //EntityTypeSet prop names
	ifs<<"#EntityTypeSet prop names:"<<::endl;
	WriteFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());

		//EntityTypeSet prop array names

		//Read properties
		ifs<<"#EntityTypeSet properties:"<<::endl;
			WriteFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());

	

		for(i=0; i<GetNumEntityTypes(); i++)
		{
			if(pEntityType=this->GetEntityType(i))
						pEntityType->WriteEntityTypeStateDefault(ifs);
		}


	return 1;

}





