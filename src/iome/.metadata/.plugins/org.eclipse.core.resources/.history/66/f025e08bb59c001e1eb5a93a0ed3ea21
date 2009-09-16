/*
IOME LICENSE
IOME Version 2.2.1 

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


// IoModel.cpp: implementation of the CIoModel class.
//
//////////////////////////////////////////////////////////////////////


#include "IoModel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoModel::CIoModel(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoSimulant(pParentSimulation, pParentSimulant, pParentHandler)
{
	m_iSimulantType = IO_SIMULANT_TYPE_MODEL;
	//strcpy(m_sModelName, "DefaultModel");
	//strcpy(m_sModelClass, "Model");
	m_sModelName = NULL;
	m_sModelClass = NULL;
	SetModelName("DefaultModel");
	SetModelClass("Model");

	m_pEntitySet=NULL;


}

CIoModel::~CIoModel()
{
   if(m_sModelName) delete [] m_sModelName;
   if(m_sModelClass) delete [] m_sModelClass;

	CIoEntitySet *pEntitySet = m_pEntitySet;
   while(pEntitySet)
   {
	   m_pEntitySet = pEntitySet->GetNextEntitySet();
	   delete pEntitySet;
	   pEntitySet=m_pEntitySet;
   } 
}




void CIoModel::SetModelClass(const char *name)
{
	if(m_sModelClass)
	{
		delete [] m_sModelClass;
		m_sModelClass = NULL;
	}


	if(name)
	{
		m_sModelClass = (char *) new char [1+strlen(name)];
		strcpy(m_sModelClass, name);
	}
}

void CIoModel::SetModelName(const char *name)
{
	if(m_sModelName)
	{
		delete [] m_sModelName;
		m_sModelName = NULL;
	}



	if(name)
	{
		m_sModelName = (char *) new char [1+strlen(name)];
		strcpy(m_sModelName, name);
	}
}


int CIoModel::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=0;
	CIoParam *pEntitySetParams=NULL;
	CIoParam *pETSetParams = NULL;
	CIoParam *pParam = NULL;

	this->DeleteFlags();
	this->DeleteNames();

	//Must be called at creation not
	//at construction!
	this->CreatePropNames();
	this->CreatePropFlags();
	this->CreatePropArrayFlags();
	this->CreatePropArrayNames();

	if(pParams && CheckParamFormat(pParams))
	{
		if(m_pProperties)
		{
			delete m_pProperties;
			m_pProperties = NULL;
		}
		m_pProperties = new CIoParam(pParams);
	}
	else
		CreateDefaultParams();

	if(pChildParams && pChildParams->GetType()==IO_PARAM_ARRAY  && (pChildParams->GetIntParam()>=2))
	{
		if((pParam = pChildParams->GetParam(0)) && (pParam->GetType()==IO_PARAM_ARRAY))
		  pEntitySetParams = pParam;
		if((pParam = pChildParams->GetParam(1)) && (pParam->GetType()==IO_PARAM_ARRAY))
		  pETSetParams = pParam;
	}

	/*! Should not need to call this method create default params
	    below*/
	//this->CreateModel(pParams, pEntitySetParams, pETSetParams);

	return status;
}

int CIoModel::CreateEntitySets(int iNumES, CIoParam *pESClassName, CIoParam *pESParam, CIoParam *pETSParam , char *cESMap)
{
	int status=0;
	CIoParam *pESP=NULL, *pETSP=NULL;
	CIoEntitySet *pES=NULL;
	char *sClassName=NULL;

	for(int i=0; i<iNumES; i++)
	{
		if(pESParam && iNumES>1 && pESParam->IsArrayOfArrays(iNumES))
			pESP=pESParam->GetParamArray(i);
		else
			pESP=pESParam;

		if(pETSParam && iNumES>1 && pETSParam->IsArrayOfArrays(iNumES))
			pETSP=pETSParam->GetParamArray(i);
		else
			pETSP=pETSParam;

		if(pESClassName && iNumES>1  && pESClassName->IsArrayOfArrays(iNumES))
			sClassName=pESClassName->GetStringParam(i);
		else if(pESClassName)
			sClassName=pESClassName->GetStringParam();
		//Create entity set
		if(pES=this->newEntitySet(sClassName))
		{
			AddEntitySet(pES);

			//Following done in AddEntitySet
			//pES->SetID(i);
			//pES->SetParentHandler(this);
			//pES->SetParentSimulant(this);
			//pES->CreateEntitySet(pESP, pETSP);
			pES->Create(pESP, pETSP);
		}

	}

	return status;
}

CIoSimulant *CIoModel::GetChild(int index)
{
	CIoSimulant *pSimulant=NULL;

	return pSimulant;
}




int CIoModel::CheckParamFormat(CIoParam *pParamData)
{
	//this format will always be an array of data
	if(pParamData && m_pProperties)
		return (m_pProperties->CheckParam(pParamData));
	else
		return 0;

}







void CIoModel::RunSimulantStep()
{

    //This maybe overridden by the actual implementation of the
	//model to update the model  parameters
	//but this CIoModel method will be called to invoke
	//the actual handlers

	HandleInteractions();
	HandleStateTransitions();

}

CIoEntitySet *CIoModel::GetEntitySet(int iIndex)
{
	CIoEntitySet *pEntitySet=m_pEntitySet;
	CIoEntitySet *pNextEntitySet=NULL;
	int i=0;
	if(iIndex < GetNumEntitySets())
		while(i<iIndex && pEntitySet && 
		(pNextEntitySet=pEntitySet->GetNextEntitySet()))
		{
									i++;
									pEntitySet=pNextEntitySet;
		}

	return pEntitySet;
}

int CIoModel::AddEntitySet(CIoEntitySet *pNewEntitySet)
{
	//Add entity set to the end of the list
	
	CIoEntitySet *pEntitySet=m_pEntitySet;
	CIoEntitySet *pNextEntitySet=NULL;
	CIoEntitySet *pOldEntitySet=NULL;
	int id=0;

	if(pNewEntitySet)
	{
		pNewEntitySet->SetParentSimulant(this);
		pNewEntitySet->SetParentHandler(this);
		pNewEntitySet->SetParentSimulation(this->GetParentSimulation());
		if(m_pEntitySet==NULL)
		{
			m_pEntitySet=pNewEntitySet;
			pNewEntitySet->SetNextEntitySet(NULL);
			pNewEntitySet->SetPreviousEntitySet(NULL);
		}
		else
		{
			pEntitySet=m_pEntitySet;
			while(pEntitySet && (pNextEntitySet=pEntitySet->GetNextEntitySet()))
			{
				if(pNextEntitySet)
					pEntitySet=pNextEntitySet;

			}
			pEntitySet->SetNextEntitySet(pNewEntitySet);
			pNewEntitySet->SetPreviousEntitySet(pEntitySet);
			

		}

		for(int i=0; i<GetNumEntitySets(); i++)
           if(pOldEntitySet=GetEntitySet(i))
			   pOldEntitySet->SetID(i);

	}

	return GetNumEntitySets();
}

CIoEntitySet *CIoModel::RemoveEntitySet(int iIndex)
{
 
	int id=0;
	CIoEntitySet *pEntitySet=GetEntitySet(iIndex);
	CIoEntitySet *pNextEntitySet=NULL;
	CIoEntitySet *pOldEntitySet = pEntitySet;
	CIoEntitySet *pPrevEntitySet = m_pEntitySet;

	if(pEntitySet)
	{
		if(m_pEntitySet==pEntitySet)
		{
			m_pEntitySet=NULL;
			pEntitySet->SetNextEntitySet(NULL);
		}
		else
		{
			pEntitySet = m_pEntitySet;
			while(pEntitySet && 
				(pNextEntitySet=pEntitySet->GetNextEntitySet())
						&& (pNextEntitySet != pOldEntitySet))
									pEntitySet=pNextEntitySet;

			
			pEntitySet->SetNextEntitySet(pOldEntitySet->GetNextEntitySet());
			pEntitySet->SetPreviousEntitySet(pOldEntitySet->GetPreviousEntitySet());
			pOldEntitySet->SetPreviousEntitySet(NULL);
			pOldEntitySet->SetNextEntitySet(NULL);
			pEntitySet=pOldEntitySet;
		}
		for(int i=0; i<GetNumEntitySets(); i++)
		{
           if(pOldEntitySet=GetEntitySet(i))
			   pOldEntitySet->SetID(i);
		}

	}

	return pEntitySet;
}

void CIoModel::DeleteEntitySet(int iIndex)
{
	CIoEntitySet *pEntitySet=NULL;
	if(pEntitySet=RemoveEntitySet(iIndex))
		delete pEntitySet;
}

int CIoModel::GetNumEntitySets()
{
	int iCount=0;

	CIoEntitySet *pEntitySet=m_pEntitySet;
	CIoEntitySet *pNextEntitySet=NULL;

	if(pEntitySet !=NULL) iCount=1;
	while(pEntitySet && 
		(pEntitySet=pEntitySet->GetNextEntitySet()))
									iCount++;


	return iCount;
}

int CIoModel::GetNumEntities()
{
	int icount = 0;
	int i;
	CIoEntitySet *pEntitySet=NULL;
	int nentitysets=GetNumEntitySets();
	for(i=0; i<nentitysets; i++)
		if(pEntitySet=GetEntitySet(i))
			icount += (pEntitySet->GetNum());

	return icount;
}



void CIoModel::HandleInteractions()
{
	
		CIoEntitySet *pEntitySetA = m_pEntitySet;
	CIoEntitySet *pEntitySetB = m_pEntitySet;
	int n = GetNumEntitySets();
	int i, j;

	//Evaluate interactions amongs entities
	//in each set
	while(pEntitySetA)
	{
		pEntitySetA->HandleInteractions();
		pEntitySetA=pEntitySetA->GetNextEntitySet();
	}

	if(n>1)
	{
		for(i=0; i<n-1; i++ )
			for(j=i+1; j<n; j++ )
			{
				pEntitySetA = GetEntitySet(i);
				pEntitySetB = GetEntitySet(j);
				if(pEntitySetA && pEntitySetB && (pEntitySetA != pEntitySetB))
							pEntitySetA->HandleEntitySetInteraction(pEntitySetB);
			}
	}
	
	CIoSimulant::HandleInteractions();	
}

void CIoModel::HandleStateTransitions()
{
	CIoEntitySet *pEntitySet = m_pEntitySet;

	while(pEntitySet)
	{
		pEntitySet->HandleStateTransitions();
		pEntitySet=pEntitySet->GetNextEntitySet();
	}
	
	
	CIoSimulant::HandleStateTransitions();

}

void CIoModel::CreateDefaultParams()
{
	CIoParam *pModProperties, *pInteger;
    int i=1;

    pInteger = new CIoParam;
	pInteger->SetParam(&i);

	pModProperties = new CIoParam;
	pModProperties->AddParam(pInteger);

    CreateProperties(pModProperties);

	pModProperties->DeleteParams();
	delete pModProperties;
	delete pInteger;
}



CIoEntityTypeSet *CIoModel::CopyEntityTypeSet(int iIndex)
{
	CIoEntitySet *pEntitySet=GetEntitySet(iIndex);
	return(pEntitySet==NULL?NULL:pEntitySet->CopyEntityTypeSet());
}



void CIoModel::CreateEntitySet(CIoParam *pEntitySetParams,
						 CIoParam *pEntityTypeSetParams,int iSimulant)
{

	if(m_pEntitySet)
		m_pEntitySet->CreateEntitySet(pEntitySetParams,
								  pEntityTypeSetParams);


}

int CIoModel::ReadSimulantDefault(ifstream &ifs)
{
	int i;
	CIoEntitySet *pEntitySet=m_pEntitySet;
	//Skip model name
	skipcmt( ifs);
	ifs>>m_sModelName;

	//skip model class
	skipcmt(ifs);
	skipcmt(ifs);  //if model class is not the same should return status 1

	//create method
	skipcmt(ifs);
	ifs>>m_iCreateMethod;

       //model prop names
		skipcmt(ifs);//skip line of prop names
		//CIoParam *pTempParam=new CIoParam(m_pPropNames);
		//pTempParam->ReadParam(ifs,pTempParam->GetNumParams() );
		//delete pTempParam;
		ReadPropNames(ifs);

		//model prop array names
		skipcmt(ifs);
		//pTempParam=new CIoParam(m_pPropArrayNames);
		//pTempParam->ReadParam(ifs,pTempParam->GetNumParams() );
		//delete pTempParam;
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

	for(i=0; i<this->GetNumEntitySets(); i++)
	{
		if(pEntitySet=GetEntitySet(i))	
			pEntitySet->ReadEntitySetDefault(ifs);
		
	}

	return 1;

}

int CIoModel::WriteSimulantDefault(ofstream &ifs)
{
	int i;
	CIoEntitySet *pEntitySet=m_pEntitySet;
	//Skip model name
	ifs<<"#Model name:" << endl;
	ifs<<m_sModelName<< endl;

	//skip model class
	ifs<<"#Model class:" << endl;
	ifs<<m_sModelClass<<endl;  //if model class is not the same should return status 1

	//create method
	ifs<<"#Model create method:"<<endl;
	ifs<<m_iCreateMethod<<endl;;

       //model prop names
	ifs<<"#Model prop names:"<<endl;
		//CIoParam *pTempParam=new CIoParam(m_pPropNames);
		//pTempParam->WriteParam(ifs,m_pPropNames->GetNumParams());
		//delete pTempParam;
		WritePropNames(ifs);

		//model prop array names
		ifs<<"#Model prop array names:"<<endl;
		//pTempParam=new CIoParam(m_pPropArrayNames);
	//pTempParam->WriteParam(ifs,m_pPropNames->GetNumParams());
		//delete pTempParam;
		WriteArrayNames(ifs);


	
		ifs<<"#Model prop flags: " << endl;
			//m_pPropFlags->WriteParam(ifs, m_pPropFlags->GetNumParams());
		WritePropFlags(ifs);


		ifs<<"#Model prop array flags: " << endl;
		//m_pPropArrayFlags->WriteParam(ifs, m_pPropArrayFlags->GetNumParams());
		WriteArrayFlags(ifs);

		//Read properties
		ifs<<"#Model properties: " << endl;
		WriteProps(ifs, GetNumProps());

	
	for(i=0; i<this->GetNumEntitySets(); i++)
	{
		if(pEntitySet=GetEntitySet(i))	
			pEntitySet->WriteEntitySetDefault(ifs);
		
	}

	return 1;
}

int CIoModel::ReadSimulantConfigDefault(ifstream &ifs)
{
		int i;
	CIoEntitySet *pEntitySet=m_pEntitySet;
	//Skip model name
	skipcmt( ifs);
	ifs>>m_sModelName;


       //model prop names
		skipcmt(ifs);//skip line of prop names

		ReadFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());

		//model prop array names
		
	
		//Read the actual flagged properties
		skipcmt(ifs);
		ReadFlaggedProps(ifs, GetArrayFlag(0), m_pPropFlags, GetNumProps());


	for(i=0; i<this->GetNumEntitySets(); i++)
	{
		if(pEntitySet=GetEntitySet(i))	
			pEntitySet->ReadEntitySetConfigDefault(ifs);
		
	}

	return 1;
}

int CIoModel::WriteSimulantConfigDefault(ofstream &ifs)
{
		int i;
	CIoEntitySet *pEntitySet=m_pEntitySet;
	//Skip model name
	ifs<<"#Model name:" << endl;
	ifs<<m_sModelName<< endl;


       //model prop names
		ifs<<"#Model prop names:"<<endl;
		WriteFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());
	
	

		//Read properties
		ifs<<"#Model properties:"<<endl;
			WriteFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(),GetNumProps());

	

	for(i=0; i<this->GetNumEntitySets(); i++)
	{
		if(pEntitySet=GetEntitySet(i))	
			pEntitySet->WriteEntitySetConfigDefault(ifs);
		
	}

	return 1;
}

int CIoModel::ReadSimulantStateDefault(ifstream &ifs)
{
			int i;
	CIoEntitySet *pEntitySet=m_pEntitySet;
	//Skip model name
	skipcmt( ifs);
	ifs>>m_sModelName;



       //model prop names
		skipcmt(ifs);//skip line of prop names
		ReadFlaggedPropNames(ifs, GetArrayFlag(0),GetPropFlags(), GetNumProps());
	
	

		//Read the actual flagged properties
		skipcmt(ifs);
		ReadFlaggedProps(ifs, GetArrayFlag(0), m_pPropFlags, GetNumProps());


	for(i=0; i<this->GetNumEntitySets(); i++)
	{
		if(pEntitySet=GetEntitySet(i))	
			pEntitySet->ReadEntitySetStateDefault(ifs);
		
	}

	return 1;

}

int CIoModel::WriteSimulantStateDefault(ofstream &ifs)
{
	int i;
	CIoEntitySet *pEntitySet=m_pEntitySet;
	//Skip model name
	ifs<<"#Model name:" << endl;
	ifs<<m_sModelName<< endl;



       //model prop names
	ifs<<"#Model prop names:"<<endl;
	WriteFlaggedPropNames(ifs, GetArrayFlag(0),GetPropFlags(), GetNumProps());

	
		//Read properties
		ifs<<"#Model properties:"<<endl;
		WriteFlaggedProps(ifs, GetArrayFlag(0), m_pPropFlags, GetNumProps());

	
	for(i=0; i<this->GetNumEntitySets(); i++)
	{
		if(pEntitySet=GetEntitySet(i))	
			pEntitySet->WriteEntitySetStateDefault(ifs);
		
	}

	return 1;

}

CIoEntity  *CIoModel::newEntityES(CIoEntitySet *pES)
{
	CIoEntity *pE=NULL;
	pE=new CIoEntity(m_pParentSimulation,this,(CIoSimHandler *)pES);
	return pE;
}

CIoEntityType  *CIoModel::newEntityTypeES(CIoEntitySet *pES, char *sClassName)
{
	CIoEntityType *pET=NULL;
	if(strcmp(sClassName, "EntityType")==0)
		pET=new CIoEntityType(m_pParentSimulation, this, (CIoSimHandler *)pES);



	return pET;
}

CIoEntityTypeSet  *CIoModel::newEntityTypeSetES(CIoEntitySet *pES, char *sClassName)
{
	CIoEntityTypeSet *pEntityTypeSet = NULL;
	if(strcmp(sClassName, "EntityTypeSet")==0)
	{
		pEntityTypeSet = new CIoEntityTypeSet(m_pParentSimulation, this, (CIoSimHandler *)pES);
		if(pES)
			pES->SetEntityTypeSet(pEntityTypeSet);
	}
	return pEntityTypeSet;
}






/*!
	Notation:
	E   Entity
	ES  Entity Set
	ET  Entity Type
	ETS Entity Type Set

	A generic method to update the properties of E, ET's ETS's and ES's

*/
void CIoModel::ETUpdate(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntityType *pET, CIoEntitySet *pES )
{

	if(pET)
		pET->UpdateProperties(pParam);
}

void CIoModel::ESUpdate(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntitySet *pES)
{

	if(pES)
		pES->UpdateProperties(pParam);
}

void CIoModel::ETSUpdate(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntityTypeSet *pES )
{

	if(pES)
		pES->UpdateProperties(pParam);
	
}

void CIoModel::EUpdate(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntity *pE, CIoEntitySet *pES )
{
	if(pE)
		pE->UpdateProperties(pParam);

}

/*!
	UpdateState these are methods called after HandleInteraction and during
	a call to HandlStateTransition. These are Update state methods for entities, enetity sets, entity types 
	and entity type sets.

*/
void CIoModel::ETUpdateState(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntityType *pET, CIoEntitySet *pES )
{
	if(pET)pET->UpdateProperties(pParam);
}

void CIoModel::ESUpdateState(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntitySet *pES)
{
	if(pES) pES->UpdateProperties(pParam);
}

void CIoModel::ETSUpdateState(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntityTypeSet *pES )
{
	if(pES) pES->UpdateProperties(pParam);
}

void CIoModel::EUpdateState(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntity *pE, CIoEntitySet *pES )
{
	if(pE) pE->UpdateProperties(pParam);
}

/*!
Calls made by entity type sets to create their properties
developers normally overide these methods they may call
these base class methods from their derived model classes

*/

	//Virtual handlers of entity set used to create params
	//and properties for entity types and entity type sets
void CIoModel::CreateETSPropArrayFlags(CIoParam *pParam, CIoEntityTypeSet *pES)
{
	if(pES)
		pES->CreatePropArrayFlags();

}

void CIoModel::CreateETSPropArrayNames(CIoParam *pParam, CIoEntityTypeSet *pES)
{
	if(pES)
		pES->CreatePropArrayNames();
}


void CIoModel::CreateETSPropFlags(CIoParam *pParam, CIoEntityTypeSet *pES)
{
	if(pES)
		pES->CreatePropFlags();

}

void CIoModel::CreateETSPropNames(CIoParam *pParam, CIoEntityTypeSet *pES)
{
	if(pES)
		pES->CreatePropNames();
}

void CIoModel::CreateETSDefaultParams(CIoParam *pParam, CIoEntityTypeSet *pES)
{	
	if(pES)
		pES->CreateProperties(pParam);

}

/*!
Calls made by entity types to create their properties
developers normally overide these methods they may call
these base class methods from their derived model classes

*/
	//Need to update the correct entity type
void CIoModel::CreateETPropArrayFlags(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(pET) pET->CreatePropArrayFlags();

}

void CIoModel::CreateETPropArrayNames(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(pET) pET->CreatePropArrayNames();

}

void CIoModel::CreateETPropFlags(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(pET)pET->CreatePropFlags();
}

void CIoModel::CreateETPropNames(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(pET)pET->CreatePropNames();
}

void CIoModel::CreateETDefaultParams(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(pET)pET->CreateProperties(pParam);

}

/*!
Calls made by entity sets to create their properties
developers normally overide these methods they may call
these base class methods from their derived model classes

*/
	//Need to update the correct entity type
void CIoModel::CreateESPropArrayFlags(CIoParam *pParam, CIoEntitySet *pES)
{
	if(pES) pES->CreatePropArrayFlags();
}

void CIoModel::CreateESPropArrayNames(CIoParam *pParam, CIoEntitySet *pES)
{
	if(pES) pES->CreatePropArrayNames();
}

void CIoModel::CreateESPropFlags(CIoParam *pParam, CIoEntitySet *pES)
{
	if(pES) pES->CreatePropFlags();
}

void CIoModel::CreateESPropNames(CIoParam *pParam, CIoEntitySet *pES)
{
	if(pES) pES->CreatePropNames();
}




void CIoModel::CreateESDefaultParams(CIoParam *pParam, CIoEntitySet *pES)
{
	if(pES) pES->CreateProperties(pParam);
}


void CIoModel::CreateEntityDefaultParams(CIoParam *pParam, CIoEntity *pE, CIoEntitySet *pES)
{
	if(pE) pE->CreateProperties(pParam);
}




