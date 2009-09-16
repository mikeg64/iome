#include <iome/simulation/IoAgentSimulator.h>

CIoAgentSimulator::CIoAgentSimulator(void)
{
}

CIoAgentSimulator::~CIoAgentSimulator(void)
{
}


void CIoAgentSimulator::CreateDefaultParams()
{


}

void CIoAgentSimulator::CreatePropNames()
{



}

void CIoAgentSimulator::CreatePropArrayNames()
{



}


void CIoAgentSimulator::CreatePropFlags()
{



}

void CIoAgentSimulator::CreatePropArrayFlags()
{




}

int CIoAgentSimulator::CreateSimulator(CIoParam *pSimulatorParams,
					           CIoParam *pModelParams,
							   CIoParam *pEntitySetParams	)
{

   int status=0;
   Create(pSimulatorParams,pModelParams,pEntitySetParams);
   return status;

}

int CIoAgentSimulator::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int i;
	CIoAgentModel *psimulant=NULL;
	CIoParam *pParam=NULL, *p1=NULL,*p2=NULL;
	int status=CIoSimulator::Create(pParams, pChildParams, pArray);
	//create map of parameters
	//int inumtypesets=GetInt(IO_AGENTMODEL_NUMAGENTSETS_INT);
	//vec *vnumtypes=GetVec(IO_AGENTMODEL_NUMAGENTTYPES_VEC);


	//CIoParam pEntitySetClasses("AgentArray");
	//CIoParam pEntityTypeSetClass("AgentType");
	//if(inumtypesets>0 && (vnumtypes != NULL))
	 //for(i=0; i<inumtypesets; i++)
	//	status=CreateEntitySets(inumtypesets, &pEntitySetClasses, &pEntityTypeSetClass, pArray);

  

	//CreateFunctionHandlers();

	//for i=0; i<nummodels <create models
	psimulant= (CIoAgentModel *)new CIoAgentModel(m_pParentSimulation,this,NULL);

	if(pChildParams && pChildParams->GetType()==IO_PARAM_ARRAY  && (pChildParams->GetIntParam()>=2))
	{
		if((pParam = pChildParams->GetParam(0)) && (pParam->GetType()==IO_PARAM_ARRAY))
		  p1 = pParam;
		if((pParam = pChildParams->GetParam(1)) && (pParam->GetType()==IO_PARAM_ARRAY))
		  p2 = pParam;
	}


	psimulant->Create(p1,p2,pArray);
	
	//createmodel
	//add model to simulator
	//this->AddS


	return status;
}

