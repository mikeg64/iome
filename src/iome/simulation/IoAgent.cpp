#include <iome/simulation/IoAgent.h>

CIoAgent::CIoAgent(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoEntity(pParentSimulation, pParentSimulant, pParentHandler)
{
}

CIoAgent::~CIoAgent(void)
{
}



void CIoAgent::CreateDefaultParams()
{
	vec vpos(3,0);
	vec sprops(1,0);
	matrix vprops(1,1,0,0);

	AddVec(&vpos);
	AddVec(&sprops);
	AddMat(&vprops);


}




void CIoAgent::HandleStateTransitions()
{
	//Using the calculated effective field
	//for this moment dettermine the new minimum energy location
	//adjust the moment accordingly

	//if selected method LLG


	//selected method energy minimiser

}

