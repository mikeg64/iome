#pragma once
#ifndef IO_MSVC
	#include "../IoUtils/fparser.h"
#else
	#include "..\IoUtils\fparser.h"
#endif
#include "IoSimulator.h"
#include "IoAgentModel.h"


class CIoAgentSimulator :
	public CIoSimulator
{
public:
	CIoAgentSimulator(void);
	~CIoAgentSimulator(void);

	void CreateDefaultParams();
	void CreatePropNames();
	void CreatePropArrayNames();

	void CreatePropFlags();
	void CreatePropArrayFlags();


	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	virtual int CreateSimulator(CIoParam *pSimulatorParams=NULL,
					           CIoParam *pModelParams=NULL,
							   CIoParam *pEntitySetParams=NULL	);

};
