#include "IoAgentTypeSet.h"

CIoAgentTypeSet::CIoAgentTypeSet(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoEntityTypeSet(pParentSimulation, pParentSimulant, pParentHandler)
{
	SetEntityTypeSetName("AgentTypeSetDefault");
	SetEntityTypeSetClass("AgentTypeSet");
}

CIoAgentTypeSet::~CIoAgentTypeSet(void)
{
}

void CIoAgentTypeSet::CreateDefaultParams()
{
	CreateProperties();
    


}

void CIoAgentTypeSet::CreatePropNames()
{
	

	
}

void CIoAgentTypeSet::CreatePropArrayNames()
{
	AddArrayName("AgentTypeSetProps");

}

void CIoAgentTypeSet::CreatePropArrayFlags()
{
	int iflagcfg = 7;
	int iflagsim = 7;
	int iflagboth = 7;

	AddArrayFlag(iflagboth);

}

void CIoAgentTypeSet::CreatePropFlags()
{
	int iflagcfg = 7;
	int iflagsim = 7;
	int iflagboth = 7;


}



int CIoAgentTypeSet::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=0;
	int i,j;
	CIoParam *pmodpar=(m_pParentHandler->m_pParentHandler)->m_pProperties;
	CIoParam *parraypar=(m_pParentHandler)->m_pProperties;
	
	vec *vng;
	CIoAgentType *pAgentType;
	CIoParam *pTypeParam;
	vec *pv;
	int ntypes=0;
	status=CIoEntityTypeSet::Create(pParams);
	ntypes=parraypar->GetIntParam(IO_AGENTARRAY_NUMTYPES_INT);

	for(j=0; j<ntypes; j++)
	{
		pAgentType=(CIoAgentType *)newEntityType("AgentType");
		//pTypeParam = new CIoParam;
		//pv=new vec(3,0);
		//pTypeParam->AddParam(&i);
		//pTypeParam->AddParam(pv);

		//Set some parameters for the EntityType
		pAgentType->CreateEntityType();

		AddEntityType(pAgentType);

		//delete pTypeParam;
		//delete pv;
	}


		
	
	return status;
}


CIoEntityType *CIoAgentTypeSet::newEntityType(char *sEntityTypeClass)
{
	CIoAgentType *pAgentType=new CIoAgentType();
	pAgentType->SetEntityTypeClass(sEntityTypeClass);
	
	return pAgentType;
}




