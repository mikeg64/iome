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


// IoEntitySet.cpp: implementation of the CIoEntitySet class.
//
//////////////////////////////////////////////////////////////////////


#include "IoEntitySet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoEntitySet::CIoEntitySet(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoSimHandler(pParentSimulation, pParentSimulant, pParentHandler)
{
	m_pEntityTypeSet = NULL;
	m_sEntitySetName = NULL;
	m_sEntitySetClass = NULL;
	m_sEntityClass = NULL;

	SetEntitySetName("EntitySet");
	SetEntitySetClass("EntitySet");
	SetEntityClass("Entity");
	m_pNextEntitySet=NULL;
	m_pPreviousEntitySet=NULL;

	m_pEDefaultParams=NULL;
	m_iID=0;
	//CreateEDefaultParams();



}

CIoEntitySet::~CIoEntitySet()
{
	if(m_sEntitySetClass)
		delete [] m_sEntitySetClass;

	if(m_sEntitySetName)
		delete [] m_sEntitySetName;

	if(m_sEntityClass)
		delete [] m_sEntityClass;

	if(m_pEntityTypeSet) delete m_pEntityTypeSet;

}

void CIoEntitySet::SetEntitySetClass(const char *name)
{
	if(m_sEntitySetClass)
	{
		delete [] m_sEntitySetClass;
		m_sEntitySetClass = NULL;
	}


	if(name)
	{
		m_sEntitySetClass = (char *) new char [1+strlen(name)];
		strcpy(m_sEntitySetClass, name);
	}
}


void CIoEntitySet::SetEntityClass(const char *name)
{
	if(m_sEntityClass)
	{
		delete [] m_sEntityClass;
		m_sEntityClass = NULL;
	}


	if(name)
	{
		m_sEntityClass = (char *) new char [1+strlen(name)];
		strcpy(m_sEntityClass, name);
	}
}


void CIoEntitySet::AddEntity(CIoEntity *pEntity)
{
	if(pEntity)
	{
		pEntity->SetParentHandler(this);
		pEntity->SetParentSimulant(GetParentSimulant());
		pEntity->SetParentSimulation(GetParentSimulation());
	}
}


CIoEntity *CIoEntitySet::newEntity()
{
	CIoEntity *pEntity=NULL;
	CIoSimulant *pParentSim=NULL;

	if(pParentSim=this->GetParentSimulant())
		pEntity=pParentSim->newEntityES(this);

	return pEntity;
}

void CIoEntitySet::SetEntitySetName(const char *name)
{
	if(m_sEntitySetName)
	{
		delete [] m_sEntitySetName;
		m_sEntitySetName = NULL;
	}



	if(name)
	{
		m_sEntitySetName = (char *) new char [1+strlen(name)];
		strcpy(m_sEntitySetName, name);
	}
}


int CIoEntitySet::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=0;
	this->DeleteFlags();
	this->DeleteNames();

	//Must be called at creation not
	//at construction!
	this->CreatePropNames();
	this->CreatePropFlags();
	this->CreatePropArrayFlags();
	this->CreatePropArrayNames();

	this->DeleteEFlags();
	this->DeleteENames();
	this->CreateEDefaultParams();
	this->CreateEPropNames();
	this->CreateEPropFlags();
	this->CreateEPropArrayFlags();
	this->CreateEPropArrayNames();

	if(pParams && (CheckParamFormat(pParams)))
		CreateProperties(pParams);
	else
		CreateDefaultParams();
     //Create the entity type set


	if(m_pParentHandler)
		status=m_pParentHandler->CreateESEntitySet(this);
	if(m_pEntityTypeSet)
		 m_pEntityTypeSet->CreateEntityTypeSet(pChildParams);


	return status;
}

CIoEntityTypeSet *CIoEntitySet::newEntityTypeSet(char *sEntityTypeSetClass)
{
	CIoEntityTypeSet *pEntityTypeSet = NULL;

	if(m_pParentHandler)
		pEntityTypeSet=m_pParentHandler->newEntityTypeSetES(this, sEntityTypeSetClass);

	return pEntityTypeSet;

}

CIoEntityType *CIoEntitySet::newEntityType(char *sEntityTypeClass)
{
	CIoSimulant *pSimulant=GetParentSimulant();
	CIoEntityType *pEntityType = NULL;
	if(pSimulant)
		pEntityType=pSimulant->newEntityType(this, sEntityTypeClass);


	return pEntityType;
}


void CIoEntitySet::CreateDefaultParams()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateESDefaultParams(NULL,this);
}

void CIoEntitySet::CreatePropNames()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateESPropNames(NULL,this);
}

void CIoEntitySet::CreatePropArrayNames()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateESPropArrayNames(NULL,this);
}


void CIoEntitySet::CreatePropFlags()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateESPropFlags(NULL,this);
}

void CIoEntitySet::CreatePropArrayFlags()
{
	if(m_pParentHandler)
		m_pParentHandler->CreateESPropArrayFlags(NULL,this);
}





void  CIoEntitySet::Update (CIoSimHandler *pHandler, CIoParam *pParam)
{
	if(m_pParentHandler)
		m_pParentHandler->ESUpdate(pHandler,pParam,this);
}

void CIoEntitySet::HandleEntitySetInteraction(CIoEntitySet *pEntitySet)
{
	if(m_pParentHandler)
		m_pParentHandler->ESHandleEntitySetInteraction(pEntitySet,this);


}

void CIoEntitySet::HandleInteractions()
{
	if(m_pParentHandler)
		m_pParentHandler->ESHandleInteractions(this);

}

/*!
Iterates over the entities and updates their state
*/
void CIoEntitySet::HandleStateTransitions()
{
	if(m_pParentHandler)
		m_pParentHandler->ESHandleStateTransitions(this);


}


//CIoEntity *CIoEntitySet::GetEntity(int iEntityIndex)
//{
//  CIoEntity *pCurrent=m_pEntity;
//  CIoEntity *pFound=NULL;
  /*int i=0;

  while(pCurrent && i<iEntityIndex)
  {
	  pCurrent=pCurrent->GetNextEntity();
	  i++;
  }

  if(i=iEntityIndex) pFound=pCurrent;*/

//  return pFound;
//}


	//Virtual handlers of entity set used to create params
	//and properties for entity types and entity type sets
void CIoEntitySet::CreateETSPropArrayFlags(CIoParam *pParam, CIoEntitySet *pES)
{
		if(m_pParentHandler)
			m_pParentHandler->CreateETSPropArrayFlags(pParam, GetEntityTypeSet());

}

void CIoEntitySet::CreateETSPropArrayNames(CIoParam *pParam, CIoEntitySet *pES)
{
		if(m_pParentHandler)
			m_pParentHandler->CreateETSPropArrayNames(pParam, GetEntityTypeSet());
}

void CIoEntitySet::CreateETSPropFlags(CIoParam *pParam, CIoEntitySet *pES)
{
		if(m_pParentHandler)
			m_pParentHandler->CreateETSPropFlags(pParam, GetEntityTypeSet());
}

void CIoEntitySet::CreateETSPropNames(CIoParam *pParam, CIoEntitySet *pES)
{
		if(m_pParentHandler)
			m_pParentHandler->CreateETSPropNames(pParam, GetEntityTypeSet());

}

void CIoEntitySet::CreateETSDefaultParams(CIoParam *pParam, CIoEntitySet *pES)
{
		if(m_pParentHandler)
			m_pParentHandler->CreateETSDefaultParams(pParam, GetEntityTypeSet());
}

	//Need to update the correct entity type
void CIoEntitySet::CreateETPropArrayFlags(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETPropArrayFlags(pParam, pET, this);
}


void CIoEntitySet::CreateETPropArrayNames(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETPropArrayNames(pParam, pET, this);

}

void CIoEntitySet::CreateETPropFlags(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETPropFlags(pParam, pET, this);

}

void CIoEntitySet::CreateETPropNames(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETPropNames(pParam, pET, this);

}

void CIoEntitySet::CreateETDefaultParams(CIoParam *pParam, CIoEntityType *pET, CIoEntitySet *pES)
{
	if(m_pParentHandler)
		m_pParentHandler->CreateETDefaultParams(pParam, pET, this);

}

//Update properties with parameter passed in
void CIoEntitySet::ETUpdate(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntityType *pET, CIoEntitySet *pES )
{
	if(m_pParentHandler) m_pParentHandler->ETUpdate(pHandler, pParam, pET, pES);

}

void CIoEntitySet::ESUpdate(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntitySet *pES)
{
	if(m_pParentHandler) m_pParentHandler->ESUpdate(pHandler, pParam, pES);
}

void CIoEntitySet::ETSUpdate(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntityTypeSet *pES )
{
	if(m_pParentHandler) m_pParentHandler->ETSUpdate(pHandler, pParam, pES);

}

void CIoEntitySet::EUpdate(CIoSimHandler *pHandler, CIoParam *pParam , CIoEntity *pE, CIoEntitySet *pES )
{
	if(m_pParentHandler) m_pParentHandler->EUpdate(pHandler, pParam, pE, pES);
}






void CIoEntitySet::EHandleInteractions(CIoEntity *pE)
{
	if(m_pParentHandler) m_pParentHandler->EHandleInteractions(pE);
}

void CIoEntitySet::EHandleStateTransitions(CIoEntity *pE)
{
	if(m_pParentHandler) m_pParentHandler->EHandleStateTransitions(pE);
}





int CIoEntitySet::ReadEntitySetDefault(::ifstream &ifs)
{
		int i;
	CIoEntitySet *pEntitySet=this;
	//Skip es name
	skipcmt( ifs);
	ifs>>m_sEntitySetName;

	//skip es class
	skipcmt(ifs);
	skipcmt(ifs);  //if model class is not the same should return status 1

	//num entities
	skipcmt(ifs);

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



      //Entity Props
		skipcmt(ifs);//skip line of prop names
		ReadEPropNames(ifs);
		//es prop array names
		skipcmt(ifs);
		ReadEArrayNames(ifs);

		//Read the flags for the properties
		//these will be used to determine which
		//properties get read from and writtent to config files and state files
		skipcmt(ifs);
		ReadEPropFlags(ifs);
		skipcmt(ifs);
		ReadEArrayFlags(ifs);

		//Read entity type set
		//Note a call to newModel must create the entittype set
		//instance (if this is required)
		if(m_pEntityTypeSet)	
			m_pEntityTypeSet->ReadEntityTypeSetDefault(ifs);




		return 1;
}

int CIoEntitySet::WriteEntitySetDefault(::ofstream &ifs)
{
	int i;
	CIoEntityTypeSet *pEntityTypeSet=m_pEntityTypeSet;
	//Skip EntitySet name
	ifs<<"#EntitySet name:" << ::endl;
	ifs<<m_sEntitySetName<< ::endl;

	//skip EntitySet class
	ifs<<"#EntitySet class:" << ::endl;
	ifs<<m_sEntitySetClass<<::endl;  //if EntitySet class is not the same should return status 1


       //EntitySet prop names
	ifs<<"#EntitySet prop names:"<<::endl;
	WritePropNames(ifs);

		//EntitySet prop array names
		ifs<<"#EntitySet prop array names:"<<::endl;
		WriteArrayNames(ifs);
		//Read properties
		ifs<<"#EntitySet properties:"<<::endl;
		WriteProps(ifs, GetNumProps());

		//Read the flags for the properties
		//these will be used to determine which
		//properties get read from and writtent to config files and state files
		ifs<<"#EntitySet prop flags:"<<::endl;
		WritePropFlags(ifs);
		ifs<<"#EntitySet prop array flags:"<<::endl;
		WriteArrayFlags(ifs);

		//Entity props
		ifs<<"#Entity prop names:"<<::endl;
		WriteEPropNames(ifs);

		//EntitySet prop array names
		ifs<<"#Entity prop array names:"<<::endl;
		WriteEArrayNames(ifs);
		//Read the flags for the properties
		//these will be used to determine which
		//properties get read from and writtent to config files and state files
		ifs<<"#Entity prop flags:"<<::endl;
		WriteEPropFlags(ifs);
		ifs<<"#Entity prop array flags:"<<::endl;
		WriteEArrayFlags(ifs);

		//Entity props
		if(pEntityTypeSet)	
			pEntityTypeSet->WriteEntityTypeSetDefault(ifs);
		


	return 1;

}

int CIoEntitySet::ReadEntitySetConfigDefault(::ifstream &ifs)
{
	int i;
	CIoEntitySet *pEntitySet=this;
	CIoEntity *pEntity;
	//Skip es name
	skipcmt( ifs);
	ifs>>m_sEntitySetName;




	//m_iNum is altered when 
	//entities added to entity set
	//ifs>>m_iNum;

       //es prop names
		skipcmt(ifs);//skip line of prop names
		ReadFlaggedPropNames(ifs,GetArrayFlag(0), GetPropFlags(), GetNumProps());
	
	
		//Read the actual flagged properties
		skipcmt(ifs);
		ReadFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(),  GetNumProps());


		//Read entity type set
		//Note a call to newModel must create the entittype set
		//instance (if this is required)
		if(m_pEntityTypeSet)	
			m_pEntityTypeSet->ReadEntityTypeSetConfigDefault(ifs);

		//skip entity data
		skipcmt(ifs);
		for(i=0; i<GetNum(); i++)
			if(pEntity=GetEntity(i))
				pEntity->ReadEntityConfigDefault(ifs);
		//skip end entity data
		skipcmt(ifs);

		if(m_pNextEntitySet)
			m_pNextEntitySet->ReadEntitySetConfigDefault(ifs);

		return 1;
}

int CIoEntitySet::WriteEntitySetConfigDefault(::ofstream &ifs)
{
	int i;

	CIoEntity *pEntity;
	CIoEntityTypeSet *pEntityTypeSet;
	//Skip EntitySet name
	ifs<<"#EntitySet name:" << ::endl;
	ifs<<m_sEntitySetName<< ::endl;



       //EntitySet prop names
	ifs<<"#EntitySet prop names:"<<::endl;
	WriteFlaggedPropNames(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());



		//Read properties
		ifs<<"#EntitySet properties:"<<::endl;
			WriteFlaggedProps(ifs, GetArrayFlag(0), GetPropFlags(), GetNumProps());

	

		if(m_pEntityTypeSet)	
			m_pEntityTypeSet->WriteEntityTypeSetConfigDefault(ifs);
		
		//skip entity data
		ifs<<"#EntitySet Data:"<<::endl;
		for(i=0; i<GetNum(); i++)
			if(pEntity=GetEntity(i))
				pEntity->WriteEntityConfigDefault(ifs, i);
		//skip end entity data
		ifs<<::endl<<"#End EntityData:"<<::endl;
		if(m_pNextEntitySet)
			m_pNextEntitySet->WriteEntitySetConfigDefault(ifs);

	return 1;

}

int CIoEntitySet::ReadEntitySetStateDefault(::ifstream &ifs)
{
			int i;
	CIoEntitySet *pEntitySet=this;
	//Skip es name
	skipcmt( ifs);
	ifs>>m_sEntitySetName;




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
		if(m_pEntityTypeSet)	
			m_pEntityTypeSet->ReadEntityTypeSetStateDefault(ifs);

		if(m_pNextEntitySet)
			m_pNextEntitySet->ReadEntitySetStateDefault(ifs);

		return 1;
}

int CIoEntitySet::WriteEntitySetStateDefault(::ofstream &ifs)
{
			int i;
	CIoEntityTypeSet *pEntityTypeSet=m_pEntityTypeSet;
	//Skip EntitySet name
	ifs<<"#EntitySet name:" << ::endl;
	ifs<<m_sEntitySetName<< ::endl;



       //EntitySet prop names
	ifs<<"#EntitySet prop names:"<<::endl;
	WriteFlaggedPropNames(ifs, GetArrayFlag(0),GetPropFlags(),GetNumProps());

	
		//Read properties
		ifs<<"#EntitySet properties:"<<::endl;
			WriteFlaggedProps(ifs, GetArrayFlag(0),GetPropFlags(),GetNumProps());

	

		if(pEntityTypeSet)	
			pEntityTypeSet->WriteEntityTypeSetStateDefault(ifs);
		
		if(m_pNextEntitySet)
			m_pNextEntitySet->WriteEntitySetConfigDefault(ifs);


	return 1;

}

void CIoEntitySet::DeleteENames()
{
	m_pEPropNames.clear();
	m_pEArrayNames.clear();
}

void CIoEntitySet::DeleteEFlags()
{
	m_pEPropFlags.clear();
	m_pEArrayFlags.clear();

}

//Methods for accessing individual enity names
char *CIoEntitySet::GetEName()  //Gets name of m_pProperties array
{
	char *s=NULL;
	string sget;

	if(m_pEArrayNames.size()>=0)
	{
		sget=(m_pEArrayNames[0]);
		s=(char *)sget.c_str();
	}

	return s;
}

string CIoEntitySet::GetEPropertyName(int i)
{
	char *s=NULL;
	string sget;

	if(m_pEPropNames.size()>0)
	{
		sget=(m_pEPropNames[i]);
		//s=(char *)sget.c_str();
	}

	return sget;
}

string CIoEntitySet::GetEPropInfilename(int i)
{
	char *s=NULL;
	string sget;

	if(m_pEPropInfilenames.size()>0)
	{
		sget=(m_pEPropInfilenames[i]);
		//s=(char *)sget.c_str();
	}

	return sget;
}

string CIoEntitySet::GetEPropOutfilename(int i)
{
	char *s=NULL;
	string sget;

	if(m_pEPropOutfilenames.size()>0)
	{
		sget=(m_pEPropOutfilenames[i]);
		//s=(char *)sget.c_str();
	}

	return sget;
}

string CIoEntitySet::GetEArrayName(int i)
{
	char *s=NULL;
	string sget;

	if(m_pEArrayNames.size()>0)
	{
		sget=(m_pEArrayNames[i]);
		//s=(char *)sget.c_str();
	}

	return sget;


}

string CIoEntitySet::GetEArrayInfilename(int i)
{
	char *s=NULL;
	string sget;

	if(m_pEArrayInfilenames.size()>0)
	{
		sget=(m_pEArrayInfilenames[i]);
		//s=(char *)sget.c_str();
	}

	return sget;


}

string CIoEntitySet::GetEArrayOutfilename(int i)
{
	char *s=NULL;
	string sget;

	if(m_pEArrayOutfilenames.size()>0)
	{
		sget=(m_pEArrayOutfilenames[i]);
		//s=(char *)sget.c_str();
	}

	return sget;


}

int CIoEntitySet::GetEPropertyFlag(int i)
{
	int iflag=0;

	if(m_pEPropFlags.size()>0)
		iflag=(m_pEPropFlags[i]);
	return iflag;
}

int CIoEntitySet::GetEArrayFlag(int i)
{
	int iflag=0;

	if(m_pEArrayFlags.size()>0)
		iflag=(m_pEArrayFlags[i]);
	return iflag;
}

void CIoEntitySet::SetEPropertyFlag(int i, int flag)
{
	if(m_pEPropFlags.size()>0 && m_pEPropFlags.size()>=i)
				m_pEPropFlags[i]=flag;
}

void CIoEntitySet::SetEArrayFlag(int i, int flag)
{
	if(m_pEArrayFlags.size()>0 && m_pEArrayFlags.size()>=i)
				m_pEArrayFlags[i]=flag;
}


void CIoEntitySet::SetEPropertyName(int i, char *sname)
{
	if(sname && m_pEPropNames.size()>=i)
				m_pEPropNames[i]=sname;


}

void CIoEntitySet::SetEPropInfilename(int i, char *sname)
{
	if(sname && m_pEPropInfilenames.size()>=i)
				m_pEPropInfilenames[i]=sname;


}

void CIoEntitySet::SetEPropOutfilename(int i, char *sname)
{
	if(sname && m_pEPropOutfilenames.size()>=i)
				m_pEPropOutfilenames[i]=sname;


}

void CIoEntitySet::SetEArrayInfilename(int i, char *sname)
{
	if(sname && m_pEArrayInfilenames.size()>0 && m_pEArrayInfilenames.size()>=i)
				m_pEArrayInfilenames [i]=sname;
}


void CIoEntitySet::SetEArrayOutfilename(int i, char *sname)
{
	if(sname && m_pEArrayOutfilenames.size()>0 && m_pEArrayOutfilenames.size()>=i)
				m_pEArrayOutfilenames [i]=sname;
}

void CIoEntitySet::SetEArrayName(int i, char *sname)
{
	if(sname && m_pEArrayNames.size()>0 && m_pEArrayNames.size()>=i)
				m_pEArrayNames [i]=sname;


}


void CIoEntitySet::AddEPropName(char *name)
{
	    string snam=name;
		m_pEPropNames.push_back(snam);
		m_pEPropInfilenames.push_back("");
		m_pEPropOutfilenames.push_back("");
}

void CIoEntitySet::AddEArrayName(char *name)
{
		string snam=name;
		m_pEArrayNames.push_back(snam);
		m_pEArrayInfilenames.push_back("");
		m_pEArrayOutfilenames.push_back("");
}

void CIoEntitySet::AddEPropName(string name)
{
	    
		m_pEPropNames.push_back(name);
		m_pEPropInfilenames.push_back("");
		m_pEPropOutfilenames.push_back("");
}

void CIoEntitySet::AddEArrayName(string name)
{
		
		m_pEArrayNames.push_back(name);
		m_pEArrayInfilenames.push_back("");
		m_pEArrayOutfilenames.push_back("");

}

void CIoEntitySet::AddEPropFlag(int flag)
{
	m_pEPropFlags.push_back(flag);
}

void CIoEntitySet::AddEArrayFlag(int flag)
{
	m_pEArrayFlags.push_back(flag);
}

//The following methods must call back to the parent 
//simulant/model

istream &CIoEntitySet::ReadFlaggedEPropNames(istream &s, int flag, dqint pArrayFlags, int noparams, int index)
{
	int num;
	int i;	
	CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumEPropNames(); i++)
			pTempParam->AddParam(GetEPropertyName(i));

	num=pTempParam->GetNumParams();
	pTempParam->ReadFlaggedParamArray(s, flag, m_pEPropFlags, num);

	delete pTempParam;

	return s;
}

ostream &CIoEntitySet::WriteFlaggedEPropNames(ostream &s, int flag, dqint pArrayFlags, int noparams, int index)
{
	int num;
	int i;	
	CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumEPropNames(); i++)
			pTempParam->AddParam(GetEPropertyName(i));

	num=pTempParam->GetNumParams();
	pTempParam->WriteFlaggedParamArray(s, flag, m_pEPropFlags, num);

	delete pTempParam;
	return s;
}

void CIoEntitySet::CreateEDefaultParams()
{
	CIoEntity *pE=newEntity();
	pE->CreateDefaultParams();
	if(m_pEDefaultParams)
		delete m_pEDefaultParams;

	m_pEDefaultParams=new CIoParam(pE->m_pProperties);

	delete pE;
}


void CIoEntitySet::ReadEPropNames(istream &s)
{
	int i;	
	CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumEPropNames(); i++)
			pTempParam->AddParam("TempName");

		pTempParam->ReadParam(s,pTempParam->GetNumParams() );
		for(i=0; i<GetNumEPropNames(); i++)
			SetEPropertyName(i, pTempParam->GetStringParam(i));

		delete pTempParam;
}



void CIoEntitySet::ReadEArrayNames(istream &s)
{
	int i;	
	CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumEArrayNames(); i++)
			pTempParam->AddParam("TempName");

		pTempParam->ReadParam(s,pTempParam->GetNumParams() );
		for(i=0; i<GetNumEArrayNames(); i++)
			SetEArrayName(i, pTempParam->GetStringParam(i));

		delete pTempParam;


}

void CIoEntitySet::ReadEPropFlags(istream &s)
{
	int i;	
	CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumEPropFlags(); i++)
			pTempParam->AddParam(&i);

		pTempParam->ReadParam(s,pTempParam->GetNumParams() );
		for(i=0; i<GetNumEPropFlags(); i++)
			SetEPropertyFlag(i, pTempParam->GetIntParam(i));

		delete pTempParam;



}

void CIoEntitySet::ReadEArrayFlags(istream &s)
{
	int i;	
	CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumEArrayFlags(); i++)
			pTempParam->AddParam(&i);

		pTempParam->ReadParam(s,pTempParam->GetNumParams() );
		for(i=0; i<GetNumEArrayFlags(); i++)
			SetEArrayFlag(i, pTempParam->GetIntParam(i));

		delete pTempParam;
}

void CIoEntitySet::WriteEPropNames(ostream &s)
{
	int i;	
	CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumPropNames(); i++)
			pTempParam->AddParam((char *)GetPropertyName(i).c_str());

		pTempParam->WriteParam(s,pTempParam->GetNumParams() );
		delete pTempParam;

}

void CIoEntitySet::WriteEArrayNames(ostream &s)
{
	int i;	
	CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumArrayNames(); i++)
			pTempParam->AddParam(GetArrayName(i));

		pTempParam->WriteParam(s,pTempParam->GetNumParams() );
		delete pTempParam;
}

void CIoEntitySet::WriteEPropFlags(ostream &s)
{
	int i,flag;	
	CIoParam *pTempParam=new CIoParam();
		for(i=0; i<GetNumPropFlags(); i++)
		{
			flag=GetPropertyFlag(i);
			pTempParam->AddParam(&flag);
		}

		pTempParam->WriteParam(s,pTempParam->GetNumParams() );
		delete pTempParam;



}

void CIoEntitySet::WriteEArrayFlags(ostream &s)
{
	int i, flag;	
	CIoParam *pTempParam=new CIoParam();
	for(i=0; i<GetNumArrayFlags(); i++)
			{
			flag=GetArrayFlag(i);
			pTempParam->AddParam(&flag);
		}
		pTempParam->WriteParam(s,pTempParam->GetNumParams() );
		delete pTempParam;
}




