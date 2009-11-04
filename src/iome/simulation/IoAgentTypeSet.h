#ifndef IO_AGENTSIMULATION_AGENTTYPESET_H
#define IO_AGENTSIMULATION_AGENTTYPESET_H

/*#ifndef IO_MSVC
	#include "../IoSimulation/IoEntityTypeSet.h"
#else
	#include "..\IoSimulation\IoEntityTypeSet.h"
#endif*/

#include <iome/simulation/IoEntityTypeSet.h>
#include <iome/simulation/IoAgentType.h>




class CIoAgentTypeSet :
	public CIoEntityTypeSet
{
public:
	CIoAgentTypeSet(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	~CIoAgentTypeSet(void);

	void CreateDefaultParams();
	void CreatePropNames();
	void CreatePropArrayNames();
	void CreatePropArrayFlags();
	void CreatePropFlags();

	//void CreateEntityTypeSet(CIoParam *pEntityTypeSetParams=NULL);
	int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	 CIoEntityType *newEntityType(char *sEntityTypeClass);


};

#endif
