#ifndef CIOWFMODEL_H_
#define CIOWFMODEL_H_

#include <iome/simulation/IoModel.h>

#define IO_WFMODEL_PARAMARAYSIZE_VEC 0
#define IO_WFMODEL_STRINGPARAMNAMES_ARRAY 1  
#define IO_WFMODEL_STRINGPARAMS_ARRAY 2   
#define IO_WFMODEL_FLOATPARAMNAMES_ARRAY 3 
#define IO_WFMODEL_FLOATPARAMS_ARRAY 4
#define IO_WFMODEL_VECPARAMNAME_ARRAY 5 
#define IO_WFMODEL_VECPARAMS_ARRAY 6
#define IO_WFMODEL_MATARAMNAMES_ARRAY 7
#define IO_WFMODEL_MATPARAMS_ARRAY 8



class CIoWFModel : public CIoModel
{
public:
	CIoWFModel(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	virtual ~CIoWFModel();
	
	void CreateDefaultParams();
	int CreateWFModelConfig();
	int CreateConfig(){return CreateWFConfig();}
	int CreateWFConfig();
	void CreatePropNames();
	void CreatePropArrayNames();

	void CreatePropFlags();
	void CreatePropArrayFlags();

	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	void CreateModel(CIoParam *pModelParams = NULL,
							 CIoParam *pEntitySetParams = NULL,
							 CIoParam *pEntityTypeSetParams=NULL	){Create(pModelParams, pEntitySetParams, pEntityTypeSetParams);}
	void HandleInteractions();
	void HandleStateTransitions();	
};

#endif /*CIOWFMODEL_H_*/
