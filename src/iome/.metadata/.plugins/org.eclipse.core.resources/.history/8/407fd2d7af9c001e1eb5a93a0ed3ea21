#ifndef IO_AGENTSIMULATION_AGENTTYPE_H
#define IO_AGENTSIMULATION_AGENTTYPE_H

/*#ifndef IO_MSVC
	#include "../IoSimulation/IoEntityType.h"
#else
	#include "..\IoSimulation\IoEntityType.h"
#endif*/
#include "IoEntityType.h"

#include "IoAgent.h"

class CIoAgentType :
	public CIoEntityType
{
public:
	CIoAgentType(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	~CIoAgentType(void);

	void CreateDefaultParams();

	void CreatePropNames();
	void CreatePropArrayNames();

	void CreatePropFlags();
	void CreatePropArrayFlags();

	void CreateEntityType(CIoParam *pEnityTypeParams=NULL);

};

#endif
