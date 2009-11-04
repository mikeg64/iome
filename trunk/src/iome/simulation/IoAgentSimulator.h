#pragma once
#ifndef IO_MSVC
	#include <iome/utils/fparser.h>
#else
	#include <iome/utils/fparser.h>
#endif
#include <iome/simulation/IoSimulator.h>
#include <iome/simulation/IoAgentModel.h>


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
