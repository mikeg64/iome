#include "IoAgentType.h"

CIoAgentType::CIoAgentType(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoEntityType(pParentSimulation, pParentSimulant, pParentHandler)
{
}

CIoAgentType::~CIoAgentType(void)
{
}

void CIoAgentType::CreateEntityType(CIoParam *pEntityTypeParams)
{
	CIoEntityType::Create(pEntityTypeParams);
	int i,j;
	//set some properties at random for the agent type
	float fval=(rand()%1000)/100;
	
	vec *v=GetVec(IO_AGENTTYPE_SCAPROPS_VEC);
	if(v)
	{
		for(i=0; i<v->length();i++)
		{
			fval=(rand()%1000)/100;
			v->set(i,fval);
		}
	}

	matrix *m=GetMat(IO_AGENTTYPE_VECPROPS_MAT);
	if(m)
	{
		for(i=0; i<m->depth();i++)
				for(j=0; j<m->width();j++)
				{
					fval=(rand()%1000)/100;
					m->setval(i,j,fval);
				}
	}


}

void CIoAgentType::CreatePropNames()
{
	AddPropName("AgentTypeScalarProps");
	AddPropName("AgentTypeVecProps");
}

void CIoAgentType::CreatePropArrayNames()
{
	AddArrayName("AgentTypeProperties");
}

void CIoAgentType::CreatePropFlags()
{
	int iflagcfg = 2;
	int iflagsim = 1;
	int iflagboth = 7;
	
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
}

void CIoAgentType::CreatePropArrayFlags()
{
	int iflagcfg = 2;
	int iflagsim = 1;
	int iflagboth = 0;

	AddArrayFlag(iflagboth);
}


void CIoAgentType::CreateDefaultParams()
{
	vec vsprops(1,1);
	matrix mvprops(1,1,0,0);

    AddVec(&vsprops);
	AddMat(&mvprops);

}


