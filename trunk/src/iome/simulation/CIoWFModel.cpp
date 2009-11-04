#include <iome/simulation/CIoWFModel.h>

CIoWFModel::CIoWFModel(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler)
{
	SetModelName("WFModelDefault");
	SetModelClass("WFModel");	
}

CIoWFModel::~CIoWFModel()
{
}

void CIoWFModel::CreateDefaultParams()
{
	CreateProperties();
	
	CIoParam pstringparamnames;
	CIoParam pstringparams;
	CIoParam pfloatparamnames;
	CIoParam pfloatparams;
	CIoParam pmatparamnames;
	CIoParam pmatparams;
	CIoParam pvecparamnames;
	CIoParam pvecparams;

    vec nparams(4,1);
    float f=0;
    matrix pmat(1,1,1,1);
    vec pvec(3,0);
	pstringparamnames.AddParam("stringparam1");
	pstringparams.AddParam("stringparam1");
	pfloatparamnames.AddParam("floatparam1");
	pfloatparams.AddParam(&f);
	pvecparamnames.AddParam("vecparam1");
    pvecparams.AddParam(&pvec);	
    pmatparamnames.AddParam("matparam1");
    pmatparams.AddParam(&pmat);

	AddVec(&nparams);
	AddArray(&pstringparamnames);
	AddArray(&pstringparams);
	AddArray(&pfloatparamnames);
	AddArray(&pfloatparams);
	AddArray(&pvecparamnames);
	AddArray(&pvecparams);
	AddArray(&pmatparamnames);
	AddArray(&pmatparams);

		

}


int CIoWFModel::CreateWFModelConfig()
{
	int result=0;
	
	return result;
}



int CIoWFModel::CreateWFConfig()
{
	int result=0;
	
	return result;
}


void CIoWFModel::CreatePropNames()
{
	AddPropName("StringParamNames");
	AddPropName("StringParams");
	AddPropName("FloatParamNames");
	AddPropName("FloatParams");
	AddPropName("VecParamNames");	
	AddPropName("VecParams");
	AddPropName("MatParamNames");	
	AddPropName("MatParams");

}



void CIoWFModel::CreatePropArrayNames()
{
	AddArrayName("WfModelProps");
	
}



void CIoWFModel::CreatePropFlags()
{
	int iflagcfg = 2;
	int iflagsim = 1;
	int iflagboth = 7;
	int iflagcstate = 6;
	int iflagstate = 4;

	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
}



void CIoWFModel::CreatePropArrayFlags()
{
	int iflagcfg = 2;
	int iflagsim = 1;
	int iflagboth = 7;

	AddArrayFlag(iflagboth);
	
}



int CIoWFModel::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=CIoModel::Create(pParams, pChildParams, pArray);


	return status;
}

void CIoWFModel::HandleInteractions()
{
	CIoModel::HandleInteractions();
}

void CIoWFModel::HandleStateTransitions()
{

	CIoModel::HandleStateTransitions();

}
