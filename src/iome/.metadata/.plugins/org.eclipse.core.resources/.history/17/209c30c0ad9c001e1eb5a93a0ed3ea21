#ifndef CIOWFSIMULATOR_H_
#define CIOWFSIMULATOR_H_

#include "IoSimulator.h"

#define IO_WFSIMULATOR_PARAMARAYSIZE_VEC 0
#define IO_WFSIMULATOR_STRINGPARAMNAMES_ARRAY 1  
#define IO_WFSIMULATOR_STRINGPARAMS_ARRAY 2   
#define IO_WFSIMULATOR_FLOATPARAMNAMES_ARRAY 3 
#define IO_WFSIMULATOR_FLOATPARAMS_ARRAY 4
#define IO_WFSIMULATOR_VECPARAMNAME_ARRAY 5 
#define IO_WFSIMULATOR_VECPARAMS_ARRAY 6
#define IO_WFSIMULATOR_MATARAMNAMES_ARRAY 7
#define IO_WFSIMULATOR_MATPARAMS_ARRAY 8


class CIoWFSimulator : public CIoSimulator
{
public:
	CIoWFSimulator();
	virtual ~CIoWFSimulator();
	
	void CreateDefaultParams();
	int CreateWFSimulatorConfig();
	int CreateConfig(){return CreateWFConfig();}
	int CreateWFConfig();
	void CreatePropNames();
	void CreatePropArrayNames();

	void CreatePropFlags();
	void CreatePropArrayFlags();

	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	int CreateSimulator(CIoParam *pSimulatorParams = NULL, CIoParam *pModelParams=NULL,
							 CIoParam *pEntitySetParams = NULL ){return(Create(pSimulatorParams, pModelParams, pEntitySetParams));}
	void HandleInteractions();
	void HandleStateTransitions();		
	
};

#endif /*CIOWFSIMULATOR_H_*/
