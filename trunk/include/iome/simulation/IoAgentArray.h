#ifndef IO_AGENTSIMULATION_AGENTARRAY_H
#define IO_AGENTSIMULATION_AGENTARRAY_H

/*#ifndef IO_MSVC
	#include "../IoSimulation/IoEntityArray3d.h"
	#include "../IoSimulation/IoSimulant.h"
#else
	#include "..\IoSimulation\IoEntityArray3d.h"
	#include "../IoSimulation/IoSimulant.h"
#endif*/
#include <iome/simulation/IoEntityArray3d.h>
#include <iome/simulation/IoSimulant.h>

#include <iome/simulation/IoAgent.h>
#include <iome/simulation/IoAgentTypeSet.h>
#ifndef IO_MSVC
	#include <iome/utils/fparser.h>
#else
	#include <iome/utils/fparser.h>
#endif*
#include <iostream>
//#include "fparser.h"


//#define IO_AGENTARRAY_AVGDIRECTION_VEC 8  //Average direction of boids
//Functions to determine entity props from field and model props
struct funcinputinfo {
	int field; //field is 1, global is zero, intermediate is 2,entitytype is 3
	int dim; //dimension s	for(i=0; i<nspe; i++)
              //scalar is 1, vector is 3
	int type;
	int index;
	int id1;  //id1 and id2 are id's of vectors used 
	          //in vector pair operations such as dot and cross product
	int id2;
};

struct functypeinfo {
	int type; //e.g. div, del2, curl, grad, nnsum
	int field;//field is 1, global is zero, intermediate is 2
};
 



class CIoAgentArray :
	public CIoEntityArray3d
{
public:
	CIoAgentArray(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	~CIoAgentArray(void);
	CIoEntity *newEntity();
	CIoEntityTypeSet *newEntityTypeSet(char *sEntityTypeSetClass);


	void CreateDefaultParams();

	void CreatePropNames();
	void CreatePropArrayNames();

	void CreatePropFlags();
	void CreatePropArrayFlags();
	
	void CreateEPropNames();
	void CreateEPropArrayNames();

	void CreateEPropFlags();
	void CreateEPropArrayFlags();


   int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);
	void CreateConfig();

	inline void setarraydim(vec *bbmax){SetVec(IO_ENTITYARRAY3D_DIMENSIONS_VEC, bbmax);}
	inline vec *getarraydim(){return GetVec(IO_ENTITYARRAY3D_DIMENSIONS_VEC);}

	void setpos(int i1, int i2, int i3, vec *vpos);
	vec *getpos(int i1, int i2, int i3);
	
	int Update();
	void HandleStateTransitions();
	void HandleInteractions();


	vec *GetPos(int iNum=0);
	float GetEnergy(int iNum=0);
	vec *GetRot(int iNum=0);

	int CreateFunctionHandlers();
	void ClearFunctionHandlers();
	
	int SetVars();
	int GetVarAllIndex(int gindex, int dim, int type);
	int GetVarGroupIndex(int allvarindex); /*! Given its index amongst the array of all variables
	                                get the index of a variable within its group e.g. sca prop, vec prop , sca field prop, intermediate vec field prop */
	FunctionParser *m_scafieldfparser;
	FunctionParser *m_vecfieldfparser;
	FunctionParser *m_scaagentpropfparser;
	FunctionParser *m_vecagentpropfparser;
	FunctionParser m_vecposfparser;
	
	CIoAgent *m_pCurrentAgent;	
	string m_vnames;
	double *m_vars;
	double *m_vars1;
	double *m_vars2;  //variables used for vector manipulations vars1, vars2 and vars3 will be the vector at the current filed position
	double *m_vars3;
	
	funcinputinfo *m_varinfo;
	int m_currentx, m_currenty, m_currentz; //current position in the field array
	
	int GetNumScaFieldEquations();
	int GetNumVecFieldEquations();
	int GetNumScaAgentEntityPropEquations();
	int GetNumVecAgentEntityPropEquations();

	int GetNumScaProps();
	int GetNumVecProps();
	int GetNumScaFields();
	int GetNumVecFields();

	int GetScaFieldEquationType(int i);
	int GetVecFieldEquationType(int i);
	int GetScaPropEquationType(int i);
	int GetVecPropEquationType(int i);
	
	string GetScaFieldEquation(int i);
	string GetVecFieldEquation(int i);
	string GetScaAgentEntityPropEquation(int i);
	string GetVecAgentEntityPropEquation(int i);
	
	int EvaluateScaPropFuncs();
	int EvaluateVecPropFuncs();
	int EvaluateScaFieldFuncs();
	int EvaluateVecFieldFuncs();
	int EvaluateVecPosFunc();
		
	int SetAllProps();
	int Settprop();
	int SetEPosProp();	
	int SetScaEProps();
	int SetVecEProps();
	int SetScaETProps();
	int SetVecETProps();
	int SetScaFieldProps(int i1=0, int i2=0, int i3=0);
	int SetVecFieldProps(int i1=0, int i2=0, int i3=0);



	double GetVecDotProd(int id1, int id2);
	void GetVecCrossProd(int id1, int id2, vec *result);
	
	double Evalsp_dotprod(int ieqn);				
	void Evalvp_crossprod(int ieqn, vec *result);				
	
	
};

#endif
