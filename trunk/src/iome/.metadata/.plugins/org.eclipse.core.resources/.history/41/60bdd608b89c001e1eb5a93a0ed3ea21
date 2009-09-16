


// IoSimulator.cpp: implementation of the CIoSimulator class.
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

#include "IoSimulator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*!The default case is that where the simulator has only one child which is a CIoModel
//this will be the case for most simulations
//Will probably be most use for dicrete event cell models (CELL DEVS)*/

CIoSimulator::CIoSimulator(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoSimulant(pParentSimulation, pParentSimulant, pParentHandler)
{
	m_iSimulantType=  IO_SIMULANT_TYPE_SIMULATOR;

	m_sSimulatorClass = NULL;
	m_sSimulatorName = NULL;

	SetSimulatorName("DefaultSimulator");
	SetSimulatorClass("Simulator");
}

CIoSimulator::~CIoSimulator()
{
   if(m_sSimulatorName) delete [] m_sSimulatorName;
   if(m_sSimulatorClass) delete [] m_sSimulatorClass;
   m_pLinks.clear();

}

void CIoSimulator::SetSimulatorClass(const char *name)
{
	if(m_sSimulatorClass)
	{
		delete [] m_sSimulatorClass;
		m_sSimulatorClass=NULL;
	}


	if(name)
	{
		m_sSimulatorClass = (char *) new char [1+strlen(name)];
		strcpy(m_sSimulatorClass, name);
	}
}

void CIoSimulator::SetSimulatorName(const char *name)
{
	if(m_sSimulatorName)
	{
		delete [] m_sSimulatorName;
		m_sSimulatorName = NULL;
	}


	if(name)
	{
		m_sSimulatorName = (char *) new char [1+strlen(name)];
		strcpy(m_sSimulatorName, name);
	}
}



/*void CIoSimulator::SetSimulatorClass(const char *name)
{
	m_sSimulatorClass = new char [1+strlen(name)];
	strcpy(m_sSimulatorClass, name);
}

void CIoSimulator::SetSimulatorName(const char *name)
{
	m_sSimulatorName = new char [strlen(name)];
	strcpy(m_sSimulatorName, name);
}*/

void CIoSimulator::CreateDefaultParams()
{
	CIoParam *pSimProperties, *pInteger;
    int i=1;
	int i2 = 3;


    pInteger = new CIoParam;
	pInteger->SetParam(&i);

	pSimProperties = new CIoParam;
	pSimProperties->AddParam(pInteger);
	pSimProperties->AddParam(&i2);

    CreateProperties(pSimProperties);

	pSimProperties->DeleteParams();
	delete pSimProperties;
	delete pInteger;
}

int CIoSimulator::GetNumSimulants()
{
	int icount=0;
	CIoSimulant *pCurrentSim = m_pSimulant;

	while(pCurrentSim != NULL)
	{
		 pCurrentSim=pCurrentSim->GetNextSimulant();
		 icount ++;
	 }
	return icount;
}


void CIoSimulator::CreateSimulant(CIoParam *pParentParams, CIoParam *pChildParams)
{
	CIoParam *pSimulantParentParams=NULL;
	CIoParam *pSimulantChildParams = NULL;
	CIoParam *pSimParamArray = NULL;
	CIoParam *pParam;
	int isimcount = 0;

	int inumsim=GetNumSimulants();
	//Use the parent params to create this simulator

	 CIoSimulant  *pCurrentSim;

  //The user may override this class
  //to update the parameters
  //but will call this class
  //to handle state transitions for the actual simulants

  //For each simulant hande the state transitions

	 pCurrentSim = m_pSimulant;
	 while(pCurrentSim != NULL)
	 {
		if(inumsim>1)
		{
			if(pChildParams && pChildParams->GetType()==IO_PARAM_ARRAY  && (pChildParams->GetIntParam()>=isimcount) )
			{		
				
				if((pSimParamArray=pChildParams->GetParam(isimcount)) && pSimParamArray->GetType()==IO_PARAM_ARRAY  && (pSimParamArray->GetIntParam()>=2))
				{
					if((pParam = pSimParamArray->GetParam(0)) && (pParam->GetType()==IO_PARAM_ARRAY))
						pSimulantParentParams = pParam;
					if((pParam = pSimParamArray->GetParam(1)) && (pParam->GetType()==IO_PARAM_ARRAY))
						pSimulantChildParams = pParam;
				}
			}
		}
		else
		{
			//if its a parameter array with 2 parameter arrays
			if(pChildParams && pChildParams->GetType()==IO_PARAM_ARRAY  && (pChildParams->GetIntParam()>=2))
			{
				if((pParam = pChildParams->GetParam(0)) && (pParam->GetType()==IO_PARAM_ARRAY))
					pSimulantParentParams = pParam;
				if((pParam = pChildParams->GetParam(1)) && (pParam->GetType()==IO_PARAM_ARRAY))
					pSimulantChildParams = pParam;
			}

		}
		 
		 
		 //Use the parent params to create this simulator

		 pCurrentSim->Create(pSimulantParentParams, pSimulantChildParams);
		 pCurrentSim=pCurrentSim->GetNextSimulant();
		 isimcount ++;

		 pSimulantParentParams=NULL;
		 pSimulantChildParams = NULL;
		 pSimParamArray = NULL;
	 }

}


int CIoSimulator::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=0;
	CIoSimulant *psimulant=NULL;

	//Assume the Simulator Params are all valid
	//If we pass NULL parameter for the model
	//There are two cases
	// 1...  The properties have already been set
	//       check them against the default parameter set
	//       i.e. we have read
	// 2...  The parameter is NULL and we have not read in any of the 
	//       parametrs this will usually be the default case in which the
	//       parameter is a single integer and it fails the check param
	if(pParams)
	{
		if(m_pProperties)
		{
			delete m_pProperties;
			m_pProperties = NULL;
		}
		m_pProperties = new CIoParam(pParams);
	}

	CIoParam *p1=NULL, *p2=NULL;
	if(pArray && (pArray->GetType()==IO_PARAM_ARRAY) && ((pArray->GetNumParams())==2))
	{
		p1=pArray->GetParamArray(0);
		p2=pArray->GetParamArray(1);
	}

	//depending on provided params will be over ridden by user
	//to call simulator createsimulant functions
	//creating the hierarchy of models and simulators
	psimulant=m_pSimulant;
	while(psimulant != NULL)
	{
		psimulant->SetParentSimulation(GetParentSimulation());
		psimulant->Create(pChildParams,p1,p2);
		psimulant->SetCreateMethod(m_iCreateMethod);
		psimulant=psimulant->GetNextSimulant();
	}
	//Now set up the entity type collection

	//set up the entities

	//Since a model has an array of entity sets
	// we pass a array of parameters for each of the entity sets
	/*if(m_pEntitySet)
		CreateEntitySet(pEntitySetParams, pEntityTypeSetParams);*/
	return status;
}





void CIoSimulator::Add(CIoSimulant *pSimulant)
{
	 CIoSimulant *pTempSim, *pCurrentSim;
	 pTempSim = this;
	 pCurrentSim = m_pSimulant;
	 if(pSimulant) pSimulant->SetParentSimulant(this);
	 if(pCurrentSim==NULL)
		 m_pSimulant = pSimulant;
	 else
	 {
		while(pCurrentSim != NULL)
		{
			pTempSim = pCurrentSim;
			pCurrentSim = pCurrentSim->GetNextSimulant();
		}
		pTempSim->m_pNextSimulant = pSimulant;
	 }

}

void CIoSimulator::Remove(CIoSimulant *pSimulant)
{
	CIoSimulant *pCurrentSimulant = m_pSimulant;
	CIoSimulant *pTempSimulant=NULL;
	CIoSimulant *pPreviousSimulant = NULL;
	if(pCurrentSimulant== m_pSimulant)
	{
		m_pSimulant = pCurrentSimulant->GetNextSimulant();
		//Don't delete simulant this is responsibility of the creator

	}
	else
	{
		while(pCurrentSimulant != pSimulant)
		{
			pPreviousSimulant = pTempSimulant;
			pTempSimulant=pCurrentSimulant;
			pCurrentSimulant = pCurrentSimulant->GetNextSimulant();
		}
		if(pPreviousSimulant)
			pPreviousSimulant->SetNextSimulant(pCurrentSimulant);
		else
			if(pTempSimulant)
				pTempSimulant->SetNextSimulant(NULL);

	}

}

CIoSimulant *CIoSimulator::GetChild(int index)
{
	CIoSimulant *pSimulant=m_pSimulant;
	CIoSimulant *pTempSimulant = NULL;
	int i=0;

	pTempSimulant = pSimulant;
	while(pTempSimulant && i<index)
	{
		pSimulant = pTempSimulant;
		pTempSimulant = pTempSimulant->GetNextSimulant();
	}
	
	return pSimulant;
}

CIoSimulant *CIoSimulator::GetChildSimulant(int i, char *ssimulantmap)
{

		char seps[] = " ,\t\n";
	int depth, index;
	int j=0;
	int *iarray;
	char *tokenptr;
	char *s;

	CIoSimulant *pSimulant = NULL;
	CIoSimulant *pCurrentSimulant = NULL;

    if(ssimulantmap)
	{
		s = (char *)new char [1+strlen(ssimulantmap)];
		//First read the parameter map 
		strcpy(s, ssimulantmap);

		//Find the parameter!
		index=0;

		tokenptr = strtok(s, seps);
		if((depth=atoi(tokenptr))<1) depth =1;
		
		iarray = (int *)new int [depth];

		while(tokenptr !=NULL)
		{
			tokenptr = strtok(NULL, seps);
			if(j<depth)
				iarray [j]=atoi(tokenptr);

			j++;
		}

		j=1;
		pSimulant = GetChild(iarray[0]);
		do
		{
			index=iarray[j];
			if((pSimulant != NULL) && ((pSimulant->GetSimulantType())==IO_SIMULANT_TYPE_SIMULATOR))
				pSimulant = ((CIoSimulator *)pSimulant)->GetChild(index);
		}while(++j<depth && pSimulant !=NULL);

		if(pSimulant && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
			return (((CIoSimulator *)pSimulant)->GetChild(i));
		else
			return NULL;
	}
	else
		return GetChild(i);


}


void CIoSimulator::CreateEntitySet(CIoParam *pEntitySetParams,
						 CIoParam *pEntityTypeSetParams, int iModel)
{
	/*if(iModel==-1)
	{
		if(m_pEntitySet)
			m_pEntitySet->CreateEntitySet(pEntitySetParams,
								  pEntityTypeSetParams);

	}
	else
	{*/
		CIoSimulant *pSimulant=GetChild(iModel);
		if(pSimulant )
			pSimulant->CreateEntitySet(pEntitySetParams, pEntityTypeSetParams, -1);
	//}
}


void CIoSimulator::HandleInteractions()
{
	 CIoSimulant  *pCurrentSim;

  //The user may override this class
  //to update the parameters
  //but will call this class
  //to handle interactions for the actual simulants

  //For each simulant hande the interactions

	/* pCurrentSim = m_pSimulant;
	 while(pCurrentSim != NULL)
	 {
		 pCurrentSim->HandleInteractions();
		 pCurrentSim=pCurrentSim->GetNextSimulant();
	 }*/



}

void CIoSimulator::HandleStateTransitions()
{

	 CIoSimulant  *pCurrentSim;

  //The user may override this class
  //to update the parameters
  //but will call this class
  //to handle state transitions for the actual simulants

  //For each simulant hande the state transitions

	/* pCurrentSim = m_pSimulant;
	 while(pCurrentSim != NULL)
	 {
		 pCurrentSim->HandleStateTransitions();
		 pCurrentSim=pCurrentSim->GetNextSimulant();
	 }*/



}

void CIoSimulator::RunSimulantStep()
{
   //Loop over the lis of simulants and run each of
   //them in turn
	 CIoSimulant  *pCurrentSim;

  //The user may override this class
  //to update the parameters
  //but will call this class
  //to handle state transitions for the actual simulants

  //


  //For each simulant hande the state transitions
	 pCurrentSim = m_pSimulant;
	 while(pCurrentSim != NULL)
	 {
		 pCurrentSim->HandleInteractions();
		 pCurrentSim=pCurrentSim->GetNextSimulant();
	 }
	 alldatamoves();
	 pCurrentSim = m_pSimulant;
	 while(pCurrentSim != NULL)
	 {
		 pCurrentSim->HandleStateTransitions();
		 pCurrentSim=pCurrentSim->GetNextSimulant();
	 }

}

void CIoSimulator::HandleModelInteractions()
{

	 CIoSimulant  *pCurrentSim;

  //The user may override this class
  //to update the parameters
  //but will call this class
  //to handle mmodel interactions for the actual simulants

  //For each simulant hande the model interactions

	 pCurrentSim = m_pSimulant;
	 while(pCurrentSim != NULL)
	 {
		 pCurrentSim->HandleModelInteractions();
		 pCurrentSim=pCurrentSim->GetNextSimulant();
	 }



}

void CIoSimulator::SetDistributeMethod(int imethod)
{
	if(((m_idistributemethod = imethod)>=0))
					m_idistributemethod=imethod;
	CIoSimulant *psim=m_pSimulant;
	while(psim != NULL)
	{
		psim->SetDistributeMethod(imethod);
		psim=psim->GetNextSimulant();
	}
	
}

void CIoSimulator::SetNumProcs(int inumprocs)
{
	if(((m_inumprocs = inumprocs)>=0))
					m_inumprocs=inumprocs;
	CIoSimulant *psim=m_pSimulant;
	while(psim != NULL)
	{
		psim->SetNumProcs(inumprocs);
		psim=psim->GetNextSimulant();
	}
	
}

CIoSimulantLink *CIoSimulator::GetLink(int id)
{
	CIoSimulantLink *link=NULL;
	if((id>=0) && id<(m_pLinks.size()))
		link=m_pLinks[id];
	return link;	
}



CIoSimulantPort *CIoSimulator::GetLinkFromPort(int id)
{
	CIoSimulantLink *link=NULL;
	if((id>=0) && id<(m_pLinks.size()))
		link=m_pLinks[id];
	
	if(link)
		return link->GetFromPort();
	else
		return NULL;
	
}



CIoSimulantPort *CIoSimulator::GetLinkToPort(int id)	
{
	CIoSimulantLink *link=NULL;
	if((id>=0) && id<(m_pLinks.size()))
		link=m_pLinks[id];
	
	if(link)
		return link->GetToPort();
	else
		return NULL;	
}



CIoSimulant *CIoSimulator::GetLinkFromSim(int id)
{
	CIoSimulantLink *link=NULL;
	if((id>=0) && id<(m_pLinks.size()))
		link=m_pLinks[id];
	
	if(link)
		return link->GetFromSimulant();
	else
		return NULL;
	
}

CIoSimulant *CIoSimulator::GetLinkToSim(int id)	
{
	CIoSimulantLink *link=NULL;
	if((id>=0) && id<(m_pLinks.size()))
		link=m_pLinks[id];
	
	if(link)
		return link->GetToSimulant();
	else
		return NULL;	
}



void CIoSimulator::AddLink(CIoSimulantPort *from, CIoSimulantPort *to)
{

		m_pLinks.push_back(new CIoSimulantLink(from,to));

}

int CIoSimulator::movedata(CIoSimulantLink *link)
{
	int status=1;
	if(link)
		status=link->movedata();
	return status;
}

void CIoSimulator::movesimulantparam(int fsimid, int fparamid, int tsimid, int tparamid)
{


}

void CIoSimulator::moveentitysetparam(int fsimid, int fes, int fparamid, int tsimid, int tes, int tparamid)
{



}

void CIoSimulator::moveentityparam(int fsimid, int fes, int fe, int fparamid,int tsimid, int tes, int te, int tparamid)
{


}



int CIoSimulator::alldatamoves()
{
	int status=1;
	deque<SIMULANTLINKPTR>::const_iterator qit;
	CIoSimulantLink *plink;

	for(qit=m_pLinks.begin();qit<m_pLinks.end();qit++)
		if(plink=(CIoSimulantLink *)(*qit))
						status = plink->movedata();
	return status;
}


int CIoSimulator::GetSimulantID(CIoSimulant *psim)
{
	int simid=0;
	int inotfinished=1;
	CIoSimulant *psimulant=m_pSimulant;
	
	while((psimulant != psim))
	{
		psimulant=psimulant->GetNextSimulant();
		simid++;
	}
	
	
	return simid;
}




