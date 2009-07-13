#ifndef IO_AGENTSIMULATION_AGENT_H
#define IO_AGENTSIMULATION_AGENT_H

/*#ifndef IO_MSVC
	#include "../IoSimulation/IoEntity.h"
#else
	#include "..\IoSimulation\IoEntity.h"
#endif*/

#include "IoEntity.h"


#include "IoAgentType.h"

#define IO_AGENT_POS_VEC 0
#define IO_AGENT_SCAPROPS_VEC 1
#define IO_AGENT_VECPROPS_MAT 2

#define IO_AGENTTYPE_SCAPROPS_VEC 0
#define IO_AGENTTYPE_VECPROPS_MAT 1

//Parameters for model
#define IO_AGENTMODEL_MODELSIZE_VEC 0
#define IO_AGENTMODEL_MODELPBC_VEC 1 
#define IO_AGENTMODEL_FLOATPROPS_VEC 2
#define IO_AGENTMODEL_VECPROPS_MAT 3
#define IO_AGENTMODEL_SCALARFIELDS_MMAT3D 4
#define IO_AGENTMODEL_VECFIELDS_MMAT3D 5
#define IO_AGENTMODEL_IFLOATPROPS_VEC 6
#define IO_AGENTMODEL_IVECPROPS_MAT 7

#define IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY 8
#define IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY 9
#define IO_AGENTMODEL_FLOATPROPSNAMES_STRARRAY 10
#define IO_AGENTMODEL_VECPROPSNAMES_STRARRAY 11
#define IO_AGENTMODEL_ISCAPROPNAMES_STRARRAY 12
#define IO_AGENTMODEL_IVECPROPNAMES_STRARRAY 13
//Evolution functions for scalar field array of equations for each field type



#define IO_AGENTMODEL_SCAFFUNC_STRARRAY 14
#define IO_AGENTMODEL_VECFFUNC_STRARRAY 15

//Evolution functions for scalar field array of equations for each field type
#define IO_AGENTMODEL_SCAFUNC_STRARRAY 16
#define IO_AGENTMODEL_VECFUNC_STRARRAY 17

//Evolution functions for scalar field	AddPropName("ScalarFields");

//	AddPropName("VectorFields"); array of equations for each field type
//intermediate field properties scalars and vectors calculated
//at each field point
#define IO_AGENTMODEL_SCAIPFUNC_STRARRAY 18
#define IO_AGENTMODEL_VECIPFUNC_STRARRAY 19

#define IO_AGENTMODEL_SCAFFUNCTYPE_VEC 20
#define IO_AGENTMODEL_VECFFUNCTYPE_VEC 21

//function type for intermediate vectors and scalars
#define IO_AGENTMODEL_SCAIFUNCTYPE_VEC 22
#define IO_AGENTMODEL_VECIFUNCTYPE_VEC 23

//function type for intermediate vectors and scalars
#define IO_AGENTMODEL_SCAFUNCTYPE_VEC 24
#define IO_AGENTMODEL_VECFUNCTYPE_VEC 25

#define IO_AGENTMODEL_NUMAGENTSETS_INT 26
#define IO_AGENTMODEL_NUMAGENTTYPES_VEC 27 //number of agent types for each set
#define IO_AGENTMODEL_NUMAGENTS_VEC 28
	//vec field func types (applies to intermediate field also)
	//unit   0
	//grad   1
	//curl   2
	//del^2  3
	//nnsum  4
	//nnav   5
	//nnnsum 6
	//nnnav   7
	//nn&nnnsum 8
	//nn&nnn av 9
	//plaquet 10
	//cross   11  vector cross product does not use equation parser
	//             equation is pair of vectors (names separated by commas)

    //sca field func types (applies to intermediate field also)
    //sca field func types (applies to intermediate field also)
    //unit   0
	//grad   1
	//div    2  n.b. div must be div of vector values !
	//del^2  3
	//nnsum  4
	//nnav   5
	//nn&nnnsum 6
	//nn&nnnav  7
	//nnnsum  8
	//nnnav   9	
	//nnnsumdot 10
	//nnnavdot   11
	//nn&nnnsum dot 12
	//nn&nnnav  dot 13
	//dot     14    vector dot product see above for vec function

		//sca func prop types
	//can perform summation and average operations
	
				//unit  0
				//vector dot   1
				//sum vector dot 2
				//avergae vector dot 3
				//sum   4
				//average 5			
	
	
	//vec func prop types
	//can perform summation and average operations
	
	//unit  0
	//vector cross 1	
	//sum vector cross 2	
	//average vector cross 3
	//sum   4
	//average 5
	//
//This is a copy of the default
//settings for each entity in the entity set
#define IO_ENTITYARRAY3D_DIMENSIONS_VEC 0
#define IO_ENTITYARRAY3D_CONFIGTYPE_INT 1
#define IO_ENTITYARRAY3D_CONFIGCREATEPARAMS_MAT  2  /*!Each row of the matrix may correpsond
                                                   to creation parameters for different phases*/
#define IO_AGENTARRAY_AGENTPOS_VEC 3

#define IO_AGENTARRAY_SCAAGENTENTITYTYPEPROPNAMES_STRARRAY 4
#define IO_AGENTARRAY_VECAGENTENTITYTYPEPROPNAMES_STRARRAY 5
#define IO_AGENTARRAY_SCAAGENTENTITYPROPNAMES_STRARRAY 6
#define IO_AGENTARRAY_VECAGENTENTITYPROPNAMES_STRARRAY 7

#define IO_AGENTARRAY_SCAAGENTPROPFUNC_STRARRAY 8
#define IO_AGENTARRAY_VECAGENTPROPFUNC_STRARRAY 9
#define IO_AGENTARRAY_SCAFFUNC_STRARRAY 10
#define IO_AGENTARRAY_VECFFUNC_STRARRAY 11

#define IO_AGENTARRAY_VECPOSFUNC_STRING 12  //equation determines evolution of agent position
//types are 0 or 1 normal dot product scalars vec product for vectors
#define IO_AGENTARRAY_SCAFFUNCTYPE_VEC 13
#define IO_AGENTARRAY_VECFFUNCTYPE_VEC 14
#define IO_AGENTARRAY_SCAAGENTPROPFUNCTYPE_VEC 15
#define IO_AGENTARRAY_VECAGENTPROPFUNCTYPE_VEC 16
#define IO_AGENTARRAY_VECAGENTPOSFUNCTYPE_INT 17
#define IO_AGENTARRAY_NUMTYPES_INT 18
//Parameters used to define names 
//of entity parameters

//#define IO_AGENTARRAY_AGENTPOS_VEC 1
//#define IO_AGENTARRAY_AGENTROT_VEC 2


/*!
	Each grain is a different entity type in this
	case each entity type has a different anistropy
*/
#define IO_AGENTTYPESET_ID_INT 0     /*!Number of grains of each phase*/



class CIoAgent :
	public CIoEntity
{
public:
	CIoAgent(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	~CIoAgent(void);

	void CreateDefaultParams();




	void HandleStateTransitions();

	inline void setpos(vec *vpos){SetVec(IO_AGENT_POS_VEC, vpos);}
	inline vec *getpos(){return GetVec(IO_AGENT_POS_VEC);}

	vec *GetPos(){return GetVec(IO_AGENT_POS_VEC);}


};

#endif
