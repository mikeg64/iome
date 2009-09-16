#ifndef IO_AGENTSIMULATION_AGENTMODEL_H
#define IO_AGENTSIMULATION_AGENTMODEL_H
/*
IOME LICENSE
IOME Version 1.1.1

IOME Development  Tools
Copyright (C) 2001-2004, Michael Kenneth Griffiths, All Rights Reserved.

--------------------------------------------------------------------------------
IOME public license.

The contents of this file are subject to the IOME Public License Version 1.3
(the "License"); you may not use this file except in compliance with the
License. You may obtain a copy of the License at
http://81.174.178.112/iome/licensing/iomelicense.html
Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the License.

The Initial Developer of the Original Code is Michael Kenneth Griffiths.
Copyright (C) 2000-2004 Michael Kenneth Griffiths. All Rights Reserved.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
mikeg@photon0.freeserve.co.uk
--------------------------------------------------------------------------------
*/
/*#ifndef IO_MSVC
	#include "../IoSimulation/IoModel.h"
#else
	#include "..\IoSimulation\IoModel.h"
#endif
#include "fparser.h"*/


#ifndef IO_MSVC
	#include <iome/utils/fparser.h>
#else
	#include <iome/utils/fparser.h>
#endif
#include <iome/simulation/IoModel.h>

#include <iome/simulation/IoAgentArray.h>
#include <iome/simulation/IoAgentTypeSet.h>
//The intermediate scalar and vector fields are recalculated at
//each field point but take only a single value

	


class CIoAgentModel :
	public CIoModel
{
public:
	CIoAgentModel(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	~CIoAgentModel(void);

	void SetSize(int n1,int n2,int n3);
	void SetSizeScalarFields(int n1,int n2,int n3);
	void SetSizeVectorFields(int n1,int n2,int n3);

	void CreateDefaultParams();
	int CreateAgentModelConfig();
	int CreateConfig(){return CreateAgentConfig();}
	int CreateAgentConfig();
	void CreatePropNames();
	void CreatePropArrayNames();

	void CreatePropFlags();
	void CreatePropArrayFlags();

	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	void CreateModel(CIoParam *pModelParams = NULL,
							 CIoParam *pEntitySetParams = NULL,
							 CIoParam *pEntityTypeSetParams=NULL	){Create(pModelParams, pEntitySetParams, pEntityTypeSetParams);}
	string GetVarNames();
	int CreateFunctionHandlers();
	void ClearFunctionHandlers();
	int SetVars();
	int GetVarAllIndex(int gindex, int dim, int field);
	int GetVarGroupIndex(int allvarindex); /*! Given its index amongst the array of all variables
	                                get the index of a variable within its group e.g. sca prop, vec prop , sca field prop, intermediate vec field prop */

    void HandleInteractions();  //Update fields using entity prop and model
	void HandleStateTransitions(); //Update entity props and model props using the field settings
	int setglobal();

	int CreatePropMap(); //Maps names of properties of agentmodel, entitysets, entitytypesets, entities

	FunctionParser *m_scafieldfparser;
	FunctionParser *m_vecfieldfparser;
	FunctionParser *m_iscafparser;
	FunctionParser *m_ivecfparser;	
	FunctionParser *m_scafparser;
	FunctionParser *m_vecfparser;
	
	
	string m_vnames;
	double *m_vars;
	double *m_vars1;
	double *m_vars2;  //variables used for vector manipulations vars1, vars2 and vars3 will be the vector at the current filed position
	double *m_vars3;
	
	funcinputinfo *m_varinfo;
	int m_currentx, m_currenty, m_currentz; //current position in the field array
	
	int GetNumScaFieldEquations();
	int GetNumVecFieldEquations();

	int GetNumIntermediateScaEquations();
	int GetNumIntermediateVecEquations();

	int GetNumScaPropEquations();
	int GetNumVecPropEquations();

	int GetNumScaFieldProps();
	int GetNumVecFieldProps();

	int GetNumIntermediateScaProps();
	int GetNumIntermediateVecProps();

	int GetNumScaProps();
	int GetNumVecProps();



	int GetScaFieldEquationType(int i);
	int GetVecFieldEquationType(int i);

	int GetIntermediateScaEquationType(int i);
	int GetIntermediateVecEquationType(int i);
	
	
	int SetAllProps();
	int Settprop();
	int Setpprop(int i=0, int j=0, int =0);	
	int SetScaProps();
	int SetVecProps();
	int SetScaIProps();
	int SetVecIProps();
	int SetScaFieldProps(int i1=0, int i2=0, int i3=0);
	int SetVecFieldProps(int i1=0, int i2=0, int i3=0);

	int GetScaPropEquationType(int i);
	int GetVecPropEquationType(int i);
	
	string GetScaFieldEquation(int i);
	string GetVecFieldEquation(int i);
	
	string GetIntermediateScaEquation(int i);
	string GetIntermediateVecEquation(int i);	
	
	string GetScaPropEquation(int i);
	string GetVecPropEquation(int i);	
	
	int EvaluateGlobalScalarFuncs();
	int EvaluateGlobalVecFuncs();
	int EvaluateScaFieldFuncs();
	int EvaluateVecFieldFuncs();
	int EvaluateIScaFuncs(int i1, int i2, int i3);
	int EvaluateIVecFuncs(int i1, int i2, int i3);
	int EvaluateIScaFunc(int ieqn, int i1, int i2, int i3);
	int EvaluateIVecFunc(int ieqn, int i1, int i2, int i3);
	

	double GetVecDotProd(int id1, int id2);
	void GetVecCrossProd(int id1, int id2, vec *result);

	//function evaluator for scalar props
	double Evalsp_dotprod(int ieqn);				
	double Evalsp_sumdotprod(int ieqn);				
	double Evalsp_averagedotprod(int ieqn);				
	double Evalsp_sum(int ieqn);				
	double Evalsp_average(int ieqn);

	//function evaluator for vec props
	void Evalvp_crossprod(int ieqn, vec *result);				
	void Evalvp_sumcrossprod(int ieqn, vec *result);				
	void Evalvp_averagecrossprod(int ieqn, vec *result);				
	void Evalvp_sum(int ieqn, vec *result);				
	void Evalvp_average(int ieqn, vec *result);

	//function evaluator for scalar field props
	double Evalsfp_dot(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_grad(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_div(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_del2(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnsum(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnav(int ieqn,int i1,int i2,int i3);
	double Evalsfp_nnnsum(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnnav(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnannnsum(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnannnav(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnsumdot(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnavdot(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnnsumdot(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnnavdot(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnannnsumdot(int ieqn,int i1,int i2,int i3);				
	double Evalsfp_nnannnavdot(int ieqn,int i1,int i2,int i3);				

	//function evaluator for scalar field props
	double Evalsip_dot(int ieqn,int i1,int i2,int i3);					
	double Evalsip_grad(int ieqn,int i1,int i2,int i3);				
	double Evalsip_div(int ieqn,int i1,int i2,int i3);				
	double Evalsip_del2(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnsum(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnav(int ieqn,int i1,int i2,int i3);
	double Evalsip_nnnsum(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnnav(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnannnsum(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnannnav(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnsumdot(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnavdot(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnnsumdot(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnnavdot(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnannnsumdot(int ieqn,int i1,int i2,int i3);				
	double Evalsip_nnannnavdot(int ieqn,int i1,int i2,int i3);

					


	//function evaluator for scalar field props
	void Evalvfp_grad(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_curl(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_del2(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnsum(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnav(int ieqn,int i1,int i2,int i3, vec *vres);
	void Evalvfp_nnnsum(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnnav(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnannnsum(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnannnav(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnsumcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnavcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnnsumcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnnavcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnannnsumcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvfp_nnannnavcross(int ieqn,int i1,int i2,int i3, vec *vres);									
	void Evalvfp_cross(int ieqn,int i1,int i2,int i3, vec *vres);

	//function evaluator for intermediate vector props
	void Evalvip_grad(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_curl(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_del2(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnsum(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnav(int ieqn,int i1,int i2,int i3, vec *vres);
	void Evalvip_nnnsum(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnnav(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnannnsum(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnannnav(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnsumcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnavcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnnsumcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnnavcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnannnsumcross(int ieqn,int i1,int i2,int i3, vec *vres);				
	void Evalvip_nnannnavcross(int ieqn,int i1,int i2,int i3, vec *vres);									
	void Evalvip_cross(int ieqn,int i1,int i2,int i3, vec *vres);



	CIoEntitySet *newEntitySet(char *sEntitySetClass);
	CIoEntity  *newEntityES(CIoEntitySet *pES);	
	
	private :




};

#endif
