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
#ifdef IO_MSVC
//	#include "stdafx.h"
#endif

#include <iome/simulation/IoAgentModel.h>

CIoAgentModel::CIoAgentModel(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoModel(pParentSimulation, pParentSimulant, pParentHandler)
{
	SetModelName("AgentModelDefault");
	SetModelClass("AgentModel");
	
	m_scafieldfparser=NULL;
	m_vecfieldfparser=NULL;
	m_iscafparser=NULL;
	m_ivecfparser=NULL;	
	m_scafparser=NULL;
	m_vecfparser=NULL;
	
	
	m_vars=NULL;
	m_varinfo=NULL;
	//m_ntotal=0;
}

CIoAgentModel::~CIoAgentModel(void)
{
	if(m_scafieldfparser) delete [] m_scafieldfparser;
	if(m_vecfieldfparser) delete [] m_vecfieldfparser;
	if(m_iscafparser) delete [] m_iscafparser;
	if(m_ivecfparser) delete [] m_ivecfparser;	
	if(m_scafparser) delete [] m_scafparser;
	if(m_scafparser) delete [] m_vecfparser;
	
	
	if(m_vars) delete [] m_vars;
	if(m_varinfo) delete [] m_varinfo;
}

void CIoAgentModel::SetSize(int n1,int n2,int n3)
{
	SetSizeScalarFields(n1,n2,n3);
	SetSizeScalarFields(n1,n2,n3);
}

void CIoAgentModel::SetSizeScalarFields(int n1,int n2,int n3)
{
    vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
    mmat3d *sfields=Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D);
	string ssfieldsfilename=GetPropInfilename(IO_AGENTMODEL_SCALARFIELDS_MMAT3D);
    CIoParam *pprop=NULL;

	if(n1>0 && n2>0 && n3>0)
	{
		if(vbox)
		{
     		vbox->set(0,n1);
     		vbox->set(1,n2);	
     		vbox->set(2,n3);
		}

		if(sfields)
			sfields->resize(n1,n2,n3,GetNumScaFieldProps(),1);

		//if the fields were written to a file 
		//rewrite this now
		if((ssfieldsfilename.length()>0) && (pprop=GetProperty(IO_AGENTMODEL_SCALARFIELDS_MMAT3D))!= NULL)
		{
			std::ofstream ssfieldsfile;
			ssfieldsfile.open((const char *)ssfieldsfilename.c_str() );
			ssfieldsfile<< *pprop;
			ssfieldsfile.close();
		}
	}



}

void CIoAgentModel::SetSizeVectorFields(int n1,int n2,int n3)
{
    vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
    mmat3d *vfields=Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D);
	string svfieldsfilename=GetPropInfilename(IO_AGENTMODEL_VECFIELDS_MMAT3D);
    CIoParam *pprop=NULL;

	if(n1>0 && n2>0 && n3>0)
	{
		if(vbox)
		{
     		vbox->set(0,n1);
     		vbox->set(1,n2);	
     		vbox->set(2,n3);
		}

		if(vfields)
			vfields->resize(n1,n2,n3,GetNumVecFieldProps(),3);

		//if the fields were written to a file 
		//rewrite this now
		if((svfieldsfilename.length()>0) && (pprop=GetProperty(IO_AGENTMODEL_VECFIELDS_MMAT3D))!= NULL)		{
			std::ofstream svfieldsfile;
			svfieldsfile.open((const char *)svfieldsfilename.c_str() );
			svfieldsfile<< *pprop;
			svfieldsfile.close();
		}



	}



}

void CIoAgentModel::CreatePropNames()
{

	AddPropName("ModelSizeVec");
	AddPropName("PBC");
	AddPropName("FloatProps");
	AddPropName("VecProps");
	AddPropName("ScalarFields");
	AddPropName("VectorFields");	
	AddPropName("IntermediateFloatProps");
	AddPropName("IntermediateVecProps");
		
	AddPropName("ScalarFieldNames");
	AddPropName("VectorFieldNames");
	AddPropName("FloatPropertyNames");
	AddPropName("VectorPropertyNames");
	AddPropName("IntermediateScalarPropertyNames");
	AddPropName("IntermediateVectorPropertyNames");	
	
	AddPropName("ScalarFieldFunctions");
	AddPropName("VectorFieldFunctions");
	AddPropName("ScalarPropFunctions");
	AddPropName("VectorPropFunctions");
	AddPropName("IntermediateScalarPropFunctions");
	AddPropName("IntermediateVectorPropFunctions");
		
	AddPropName("ScaFieldFuncType");
	AddPropName("VecFieldFuncType");
	AddPropName("IntermediateScaPropFuncType");
	AddPropName("IntermediateVecPropFuncType");	
	AddPropName("ScaPropFuncType");
	AddPropName("VecPropFuncType");
	
	AddPropName("NumAgentSets");
	AddPropName("NumAgentTypes");	
	AddPropName("NumAgents");	
		
		
}

void CIoAgentModel::CreatePropArrayNames()
{

	AddArrayName("AgentModelProps");

}

void CIoAgentModel::CreatePropFlags()
{
	int iflagcfg = 2;
	int iflagsim = 1;
	int iflagboth = 7;
	int iflagcstate = 6;
	int iflagstate = 4;


	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	
	
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);


	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);		
	AddPropFlag(iflagsim);
	AddPropFlag(iflagsim);
	
	AddPropFlag(iflagsim);
	
				
}

void CIoAgentModel::CreatePropArrayFlags()
{

	int iflagcfg = 2;
	int iflagsim = 1;
	int iflagboth = 7;

	AddArrayFlag(iflagboth);

}




void CIoAgentModel::CreateDefaultParams()
{
    vec vsize(3,4);
    vsize.set(2,1);

    vec vpbc(3,1);
    vpbc.set(2,0);

    vec vfprops(1,0);
    matrix mvecprops(1,1,0,0);
    
    mmat3d sfields(4,4,1,2,1,1,0);
    mmat3d vfields(4,4,1,1,1,0,0);
    
    sfields.setval(2,2,0,1,0,0);
    sfields.setval(3,2,0,1,0,0);
    sfields.setval(1,2,0,1,0,0);
    
     sfields.setval(2,2,0,1,0,1);
    sfields.setval(2,3,0,1,0,1);
    sfields.setval(2,1,0,1,0,1);
    
    vec visprops(1,0);
    matrix mivecprops(1,1,0,0);


    

    
    //IoStringArray savfnames("");
    char *sblank=NULL;
    IoStringArray savfnames("gradn"); //gradient of the nearest number field
    IoStringArray sasfnames("n"); //neighbours
    sasfnames.AddString("s");  //state
    IoStringArray saspnames(sblank);
    IoStringArray savpnames(sblank);
    IoStringArray saisnames(sblank);
    IoStringArray saivnames(sblank);
    
	IoStringArray scaffunc("s>0");
	//std::cout << scaffunc << std::endl;
	scaffunc.AddString("(n>1) & (n<4)");
	//scaffunc.AddString("0");
	std::cout << scaffunc << std::endl;
	IoStringArray vffunc("n");  //gradient of nearest number field
	IoStringArray scafunc(sblank);
	IoStringArray vfunc(sblank);	
	IoStringArray iscafunc(sblank);
	IoStringArray ivfunc(sblank);

	vec vsffunctype(2,0);
	vec vvffunctype(1,1);	
	vsffunctype.set(0,4);
	vec visfunctype(2,0);	
	vec vivfunctype(1,0);
	vec vspfunctype(1,0);
	vec vvpfunctype(1,0);
	
	AddVec(&vsize);
	AddVec(&vpbc);

    AddVec(&vfprops);
    AddMat(&mvecprops);
    Addmmat3d(&sfields);
    
    Addmmat3d(&vfields);
    AddVec(&visprops);
    AddMat(&mivecprops);

	AddStringArray(&sasfnames);
	AddStringArray(&savfnames);	
	AddStringArray(&saspnames);
	AddStringArray(&savpnames);
	AddStringArray(&saisnames);
	AddStringArray(&saivnames);		
	
	AddStringArray(&scaffunc);
	AddStringArray(&vffunc);
	AddStringArray(&scafunc);
	AddStringArray(&vfunc);
	AddStringArray (&iscafunc);
	AddStringArray (&ivfunc);
	
    AddVec(&vsffunctype);
    AddVec(&vvffunctype);
    AddVec(&visfunctype);
    AddVec(&vivfunctype);    
    AddVec(&vspfunctype);
    AddVec(&vvpfunctype); 
    
	//IoStringArray *ptrsa=GetStringArray(IO_AGENTMODEL_SCAFFUNC_STRARRAY);  
	//std::cout << "sf eqns str array is:"<< *ptrsa << std::endl;
	
	//std::cout << sfields << std::endl;
    //std::cout << "fields \n\n" << std::endl;
    //std::cout << *Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D) << std::endl;
	int inumagentsets=0;
	vec vnumagenttypes(1,2);
	vec vnumagents(1,5);
	AddInt(inumagentsets);
	AddVec(&vnumagenttypes);
	AddVec(&vnumagents);

}

int CIoAgentModel::CreateAgentConfig()
{
	int status=0;
	int inumsets=GetInt(IO_AGENTMODEL_NUMAGENTSETS_INT);
	//CIoAgentArray *peset=NULL;
	CIoEntitySet *peset=NULL;
	if(m_pEntitySet != NULL)
		peset=m_pEntitySet;
	while(peset != NULL)
	{
	  peset->CreateConfig();
	  peset=(peset->GetNextEntitySet());
	}
	return status;	
}



int CIoAgentModel::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int i;
	int status=CIoModel::Create(pParams, pChildParams, pArray);
	//create map of parameters
	int inumtypesets=GetInt(IO_AGENTMODEL_NUMAGENTSETS_INT);
	vec *vnumtypes=GetVec(IO_AGENTMODEL_NUMAGENTTYPES_VEC);


	CIoParam pEntitySetClasses("AgentArray");
	CIoParam pEntityTypeSetClass("AgentType");
	if(inumtypesets>0 && (vnumtypes != NULL))
	 //for(i=0; i<inumtypesets; i++)
		status=CreateEntitySets(inumtypesets, &pEntitySetClasses, &pEntityTypeSetClass, pArray);

  

	CreateFunctionHandlers();


	return status;
}

int CIoAgentModel::GetNumScaFieldEquations()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_SCAFFUNC_STRARRAY);
	
	return(sa?sa->GetSize():0);
}
	
int CIoAgentModel::GetNumVecFieldEquations()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_VECFFUNC_STRARRAY);
	
	return(sa?sa->GetSize():0);
}


int CIoAgentModel::GetNumIntermediateScaEquations()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_SCAIPFUNC_STRARRAY);
	
	return(sa?sa->GetSize():0);
}
	
int CIoAgentModel::GetNumIntermediateVecEquations()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_VECIPFUNC_STRARRAY);
	
	return(sa?sa->GetSize():0);
}


int CIoAgentModel::GetNumScaPropEquations()
{
	
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_SCAFUNC_STRARRAY);
	return(sa?sa->GetSize():0);
}

int CIoAgentModel::GetNumVecPropEquations()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_VECFUNC_STRARRAY);
	
	return(sa?sa->GetSize():0);
}


int CIoAgentModel::GetNumScaFieldProps()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY);
	
	return(sa?sa->GetSize():0);
}
	
int CIoAgentModel::GetNumVecFieldProps()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY);
	
	return(sa?sa->GetSize():0);
}


int CIoAgentModel::GetNumIntermediateScaProps()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_ISCAPROPNAMES_STRARRAY);
	
	return(sa?sa->GetSize():0);
}
	
int CIoAgentModel::GetNumIntermediateVecProps()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_IVECPROPNAMES_STRARRAY);
	
	return(sa?sa->GetSize():0);
}


int CIoAgentModel::GetNumScaProps()
{
	
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_FLOATPROPSNAMES_STRARRAY);
	return(sa?sa->GetSize():0);
}

int CIoAgentModel::GetNumVecProps()
{
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_VECPROPSNAMES_STRARRAY);
	
	return(sa?sa->GetSize():0);
}


string CIoAgentModel::GetScaFieldEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_SCAFFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;
}

string CIoAgentModel::GetVecFieldEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_VECFFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;
}


string CIoAgentModel::GetIntermediateScaEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_SCAIPFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;
}

string CIoAgentModel::GetIntermediateVecEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_VECIPFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;
}


string CIoAgentModel::GetScaPropEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_SCAFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;
}

string CIoAgentModel::GetVecPropEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTMODEL_VECFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;	
	
}


int CIoAgentModel::GetScaFieldEquationType(int i)
{
	vec *t;
	t=GetVec(IO_AGENTMODEL_SCAFFUNCTYPE_VEC);
	if(t && (i<GetNumScaFieldEquations()))
	  return (t->get(i));
	
	return 0;
}

int CIoAgentModel::GetVecFieldEquationType(int i)
{
	vec *t;
	t=GetVec(IO_AGENTMODEL_VECFFUNCTYPE_VEC);
	if(t && (i<GetNumVecFieldEquations()))
	  return (t->get(i));
	
	return 0;
}

int CIoAgentModel::GetIntermediateScaEquationType(int i)
{
	
	vec *t;
	t=GetVec(IO_AGENTMODEL_SCAIFUNCTYPE_VEC);
	if(t && (i<GetNumIntermediateScaEquations()))
	  return (t->get(i));
	
	return 0;	
	
}

int CIoAgentModel::GetIntermediateVecEquationType(int i)
{
	vec *t;
	t=GetVec(IO_AGENTMODEL_VECIFUNCTYPE_VEC);
	if(t && (i<GetNumIntermediateVecEquations()))
	  return (t->get(i));
	
	return 0;
}

int CIoAgentModel::GetScaPropEquationType(int i)
{
	vec *t;
	t=GetVec(IO_AGENTMODEL_SCAFUNCTYPE_VEC);
	if(t  && (i<GetNumScaPropEquations()))
	  return (t->get(i));
	
	return 0;
}



int CIoAgentModel::GetVecPropEquationType(int i)
{
	vec *t;
	t=GetVec(IO_AGENTMODEL_VECFUNCTYPE_VEC);
	if(t && (i<GetNumVecPropEquations()))
	  return (t->get(i));
	
	return 0;
	
}

int CIoAgentModel::GetVarAllIndex(int gindex, int dim, int field)
{
	int status;
	int tot=0;
	int stot=0;
	int i;
	int i1,i2,i3,i4,i5,i6;
	int index=0;
	i1=i2=i3=i4=i5=i6=0;
	


	IoStringArray *v1=GetStringArray(IO_AGENTMODEL_FLOATPROPSNAMES_STRARRAY);
	IoStringArray *v2=GetStringArray(IO_AGENTMODEL_VECPROPSNAMES_STRARRAY);
	IoStringArray *v3=GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY);
	IoStringArray *v4=GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY);
	IoStringArray *v5=GetStringArray(IO_AGENTMODEL_ISCAPROPNAMES_STRARRAY);
	IoStringArray *v6=GetStringArray(IO_AGENTMODEL_IVECPROPNAMES_STRARRAY);
		
	if(v1) i1=(v1->GetSize());
	if(v2) i2=(v2->GetSize());
	if(v3) i3=(v3->GetSize());
	if(v4) i4=(v4->GetSize());
	if(v5) i5=(v5->GetSize());
	if(v6) i6=(v6->GetSize());
	

	
	
	if((dim==1) && (field==0))
				index=4+gindex;
	else if((dim==3) && (field==0))
				index=4+gindex+i1;
	else if((dim==1) && (field==1))
				index=4+gindex+i1+i2;
	else if((dim==3) && (field==1))
				index=4+gindex+i1+i2+i3;
	else if((dim==1) && (field==2))
				index=4+gindex+i1+i2+i3+i4;
	else if((dim==3) && (field==2))
				index=4+gindex+i1+i2+i3+i4+i5;
	
	return index;		
	
	
	
}

int CIoAgentModel::GetVarGroupIndex(int allvarindex)
{
	int status;
	int tot=0;
	int stot=0;
	int i;
	int i1,i2,i3,i4,i5,i6;
	int index=0;
	i1=i2=i3=i4=i5=i6=0;
	
	IoStringArray *v1=GetStringArray(IO_AGENTMODEL_FLOATPROPSNAMES_STRARRAY);
	IoStringArray *v2=GetStringArray(IO_AGENTMODEL_VECPROPSNAMES_STRARRAY);
	IoStringArray *v3=GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY);
	IoStringArray *v4=GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY);
	IoStringArray *v5=GetStringArray(IO_AGENTMODEL_ISCAPROPNAMES_STRARRAY);
	IoStringArray *v6=GetStringArray(IO_AGENTMODEL_IVECPROPNAMES_STRARRAY);
		
	if(v1) i1=(v1->GetSize());
	if(v2) i2=(v2->GetSize());
	if(v3) i3=(v3->GetSize());
	if(v4) i4=(v4->GetSize());
	if(v5) i5=(v5->GetSize());
	if(v6) i6=(v6->GetSize());
	
	if(allvarindex < i1)
		index=allvarindex-4;
	else if(allvarindex < (i1+i2))		
		index=allvarindex-i1-4;
	else if(allvarindex < (i1+i2+i3))		
		index=allvarindex-i1-i2-4;	
	else if(allvarindex < (i1+i2+i3+i4))		
		index=allvarindex-i1-i2-i3-4;	
	else if(allvarindex < (i1+i2+i3+i4+i5))		
		index=allvarindex-i1-i2-i3-i4-4;	
	else if(allvarindex < (i1+i2+i3+i4+i5+i6))		
		index=allvarindex-i1-i2-i3-i4-i5-4;	
	
	return index;	
}

void CIoAgentModel::ClearFunctionHandlers()
{
	delete [] m_scafieldfparser;
	delete [] m_vecfieldfparser;
	delete [] m_iscafparser;
	delete [] m_ivecfparser;	
	delete [] m_scafparser;
	delete [] m_vecfparser;
	
	m_vnames.clear();
	delete [] m_vars;
	delete [] m_vars1;
	delete [] m_vars2;  //variables used for vector manipulations vars1, vars2 and vars3 will be the vector at the current filed position
	delete [] m_vars3;

	m_scafieldfparser=NULL;
	m_vecfieldfparser=NULL;
	m_iscafparser=NULL;
	m_ivecfparser=NULL;	
	m_scafparser=NULL;
	m_vecfparser=NULL;
	
	
	m_vars=NULL;
	m_varinfo=NULL;
	m_vars1=NULL;
	m_vars2=NULL;
	m_vars3=NULL;


	CIoAgentArray *pAgentArray=NULL;
	if(m_pEntitySet != NULL)
	{
		pAgentArray=(CIoAgentArray *)m_pEntitySet;
		pAgentArray->ClearFunctionHandlers();
		while((pAgentArray=(CIoAgentArray *)(pAgentArray->GetNextEntitySet())))
								pAgentArray->ClearFunctionHandlers();
			
	}

	
}

string CIoAgentModel::GetVarNames()
{
	string svarnames;
	int n1,n2,n3,n4,n5,n6=0;
	int tot=0;
	int i;
	int stot=0;

	n1=n2=n3=n4=n5=n6;
	IoStringArray *ptsra;
	
	if(ptsra=GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY))
		tot+=(n5=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY))
		tot+=(n6=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_FLOATPROPSNAMES_STRARRAY))
		tot+=(n1=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_VECPROPSNAMES_STRARRAY))
		tot+=(n2=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_ISCAPROPNAMES_STRARRAY))
		tot+=(n3=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_IVECPROPNAMES_STRARRAY))
		tot+=(n4=(ptsra->GetSize()));

	svarnames+="tt,px,py,pz";
	if((n1)>0)
			svarnames+=",";

	if(n1>0)
		for(i=0; i<n1; i++)
		{
		   //if(i !=0 ) m_vnames+=",";
		   svarnames+=(GetStringArray(IO_AGENTMODEL_FLOATPROPSNAMES_STRARRAY)->GetsString(i));
		  if(i<(n1-1) ) svarnames+=",";
		   stot++;
		}
	if((n2)>0 ) svarnames+=",";

	if(n2>0)
		for(i=0; i<n2; i++)
		{
		   //m_vnames+=",";
		   svarnames+=(GetStringArray(IO_AGENTMODEL_VECPROPSNAMES_STRARRAY)->GetsString(i));
		   if(i<(n2-1) ) svarnames+=",";		   
		   stot++;
		}
	if((n5)>0 ) svarnames+=",";	

	if(n5>0)
		for(i=0; i<n5; i++)
		{
		   //m_vnames+=",";
		   svarnames+=(GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY)->GetsString(i));
		   if(i<(n5-1) ) svarnames+=",";
		   stot++;
		}
	if((n6)>0 ) svarnames+=",";	
		
	//if(v4)
	//	for(i=0; i<(v4->mrows()); i++)
	if(n6>0)
		for(i=0; i<n6; i++)
		{
		   svarnames+=(GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY)->GetsString(i));
		  if(i<(n6-1) ) svarnames+=",";
		   stot++;
		}						
	if((n3)>0 ) svarnames+=",";	
	
	//if(v5)
	//	for(i=0; i<(v5->length()); i++)
	if(n3>0)
		for(i=0; i<n3; i++)
		{
		   //m_vnames+=",";
		   svarnames+=(GetStringArray(IO_AGENTMODEL_ISCAPROPNAMES_STRARRAY)->GetsString(i));
		  if(i<(n3-1) ) svarnames+=",";
		   stot++;
		}

	if((n4)>0 ) svarnames+=",";	

	//if(v6)
	//	for(i=0; i<(v6->depth()); i++)
	if(n4>0)
		for(i=0; i<n4; i++)
		{
		   svarnames+=(GetStringArray(IO_AGENTMODEL_IVECPROPNAMES_STRARRAY)->GetsString(i));
		  if(i<(n4-1) ) svarnames+=",";
		   stot++;
		}



	return svarnames;
}

int CIoAgentModel::CreateFunctionHandlers()
{
	int status=0;
	int tot=0;
	int stot=0; //stores number of variables
	int i,j,k;
	int itype=0;
	IoStringArray *saeqns=NULL;
	char *seqn, *sv1, *sv2, *svt1;
	
	vec *v1=GetVec(IO_AGENTMODEL_FLOATPROPS_VEC);
	matrix *v2=GetMat(IO_AGENTMODEL_VECPROPS_MAT);
	mmat3d *v3=Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D);
	mmat3d *v4=Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D);
	vec *v5=GetVec(IO_AGENTMODEL_IFLOATPROPS_VEC);
	matrix *v6=GetMat(IO_AGENTMODEL_IVECPROPS_MAT);
	
	vec *vt1=GetVec(IO_AGENTMODEL_SCAFUNCTYPE_VEC);
	vec *vt2=GetVec(IO_AGENTMODEL_VECFUNCTYPE_VEC);
	vec *vt3=GetVec(IO_AGENTMODEL_SCAIFUNCTYPE_VEC);
	vec *vt4=GetVec(IO_AGENTMODEL_VECIFUNCTYPE_VEC);
	vec *vt5=GetVec(IO_AGENTMODEL_SCAFFUNCTYPE_VEC);
	vec *vt6=GetVec(IO_AGENTMODEL_VECFFUNCTYPE_VEC);

	string sseqn;
	int n1,n2,n3,n4,n5,n6=0;
	n1=n2=n3=n4=n5=n6;
	
	/*if(v1) tot+=(n1=(v1->length()));
	if(v2) tot+=(n2=(v2->depth()));
	if(v3) tot+=(n3=(v3->mrows()));
	if(v4) tot+=(n4=(v4->mrows()));
	if(v5) tot+=(n5=(v5->length()));
	if(v6) tot+=(n6=(v6->depth()));*/
	
	IoStringArray *ptsra;
	
	if(ptsra=GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY))
		tot+=(n5=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY))
		tot+=(n6=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_FLOATPROPSNAMES_STRARRAY))
		tot+=(n1=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_VECPROPSNAMES_STRARRAY))
		tot+=(n2=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_ISCAPROPNAMES_STRARRAY))
		tot+=(n3=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_IVECPROPNAMES_STRARRAY))
		tot+=(n4=(ptsra->GetSize()));	

	
	std::cout << "num vec eqns"<<GetNumVecFieldEquations() << "\n";
	if(GetNumScaFieldEquations()>0)
		m_scafieldfparser=new FunctionParser[GetNumScaFieldEquations()];
	if(GetNumVecFieldEquations()>0)
		m_vecfieldfparser=new FunctionParser[GetNumVecFieldEquations()];
	if(GetNumIntermediateScaEquations()>0)
		m_iscafparser=new FunctionParser[GetNumIntermediateScaEquations()];
	if(GetNumIntermediateVecEquations()>0)
		m_ivecfparser=new FunctionParser[GetNumIntermediateVecEquations()];
	if(GetNumScaPropEquations()>0)
		m_scafparser=new FunctionParser[GetNumScaPropEquations()];
	if(GetNumVecPropEquations()>0)
		m_vecfparser=new FunctionParser[GetNumVecPropEquations()];


//IoStringArray *saeqns=NULL;
//	char *seqn;
//string sseqn;
  //  saeqns=GetStringArray(IO_AGENTMODEL_SCAFUNC_STRARRAY);
  //  seqn=(char *)(saeqns->GetsString(1)).c_str();
  //  sseqn=(saeqns->GetsString(1));
  //  std::cout << "end create funcseqn is: " << *saeqns <<" \n";
  //  std::cout << "end create funcsvars are: " << m_vnames <<" \n";
  

	m_vars1=new double[tot+4];	
	m_vars2=new double[tot+4];
	m_vars3=new double[tot+4];	
	m_vars=new double[tot+4];
	for(i=0; i<tot+4; i++) 
	{
		m_vars[i]=0;
		m_vars1[i]=0;		
		m_vars2[i]=0;
		m_vars3[i]=0;		
	}
	
	m_varinfo=new funcinputinfo [tot+4];
	
	m_vnames+="tt,px,py,pz";
	if((n1)>0)
			m_vnames+=",";
	m_varinfo[stot].field=0;
	m_varinfo[stot].dim=1;
	m_varinfo[stot].index=0;
	m_varinfo[stot].type=IO_AGENTMODEL_FLOATPROPS_VEC;
	
	stot++;
	//read the list of variable names
	//if(v1)
	//	for(i=0; i<(v1->length()); i++)
	if(n1>0)
		for(i=0; i<n1; i++)
		{
		   //if(i !=0 ) m_vnames+=",";
		   m_vnames+=(GetStringArray(IO_AGENTMODEL_FLOATPROPSNAMES_STRARRAY)->GetsString(i));
		  if(i<(n1-1) ) m_vnames+=",";
		   m_varinfo[stot].field=0;
		   m_varinfo[stot].dim=1;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTMODEL_FLOATPROPS_VEC;
		   stot++;
		}
	if((n2)>0 ) m_vnames+=",";

	//if(v2)
	//	for(i=0; i<(v2->depth()); i++)
	if(n2>0)
		for(i=0; i<n2; i++)
		{
		   //m_vnames+=",";
		   m_vnames+=(GetStringArray(IO_AGENTMODEL_VECPROPSNAMES_STRARRAY)->GetsString(i));
		   if(i<(n2-1) ) m_vnames+=",";
		   m_varinfo[stot].field=0;
		   m_varinfo[stot].dim=3;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTMODEL_VECPROPS_MAT;
		   
		   stot++;
		}
	if((n5)>0 ) m_vnames+=",";	
	//if(v3)
		//for(i=0; i<(v3->mrows()); i++)
	if(n5>0)
		for(i=0; i<n5; i++)
		{
		   //m_vnames+=",";
		   m_vnames+=(GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY)->GetsString(i));
		   if(i<(n5-1) ) m_vnames+=",";
		   m_varinfo[stot].field=1;
		   m_varinfo[stot].dim=1;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTMODEL_SCALARFIELDS_MMAT3D;
		   
		   stot++;
		}
	if((n6)>0 ) m_vnames+=",";	
		
	//if(v4)
	//	for(i=0; i<(v4->mrows()); i++)
	if(n6>0)
		for(i=0; i<n6; i++)
		{
		   //m_vnames+=",";
		   m_vnames+=(GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY)->GetsString(i));
		  if(i<(n6-1) ) m_vnames+=",";
		   m_varinfo[stot].field=1;
		   m_varinfo[stot].dim=3;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTMODEL_VECFIELDS_MMAT3D;

		   stot++;
		}						
	if((n3)>0 ) m_vnames+=",";	
	
	//if(v5)
	//	for(i=0; i<(v5->length()); i++)
	if(n3>0)
		for(i=0; i<n3; i++)
		{
		   //m_vnames+=",";
		   m_vnames+=(GetStringArray(IO_AGENTMODEL_ISCAPROPNAMES_STRARRAY)->GetsString(i));
		  if(i<(n3-1) ) m_vnames+=",";

		   m_varinfo[stot].field=2;
		   m_varinfo[stot].dim=1;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTMODEL_IFLOATPROPS_VEC;

		   stot++;
		}

	if((n4)>0 ) m_vnames+=",";	

	//if(v6)
	//	for(i=0; i<(v6->depth()); i++)
	if(n4>0)
		for(i=0; i<n4; i++)
		{
		   //m_vnames+=",";
		   m_vnames+=(GetStringArray(IO_AGENTMODEL_IVECPROPNAMES_STRARRAY)->GetsString(i));
		  if(i<(n4-1) ) m_vnames+=",";

		   m_varinfo[stot].field=2;
		   m_varinfo[stot].dim=3;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTMODEL_IVECPROPS_MAT;

		   stot++;
		}

    std::cout << "The " << tot << " variables are: " << m_vnames << std::endl;
	//if the function is a dot or cross product or involves an ordered pair of vectors
	//then the functionis of the form vecname1,vecname2
	//ids for these vectors contained in the var info process this now
	//read the list of variable names
	for(j=1; j<stot; j++)
	{
	if(vt1)
	{
		saeqns=GetStringArray(IO_AGENTMODEL_SCAFUNC_STRARRAY);
		for(i=0; i<(vt1->length()); i++)
		{
		
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt1->get(i);
		   //these are performinfg vector dot products nn sums etc
		   //format is always var1,var2
		   if((saeqns !=NULL) && ((itype==10) || (itype==11) || (itype==12) || (itype==13)|| (itype==14)))
		   {
		   	  //tokenize the equation
		   	  if(seqn=(char *)((saeqns->GetsString(i)).c_str()))
		   	  {
			   	  sv1=strtok(seqn,",");
			   	  sv2=strtok(NULL,",");
			   	  
			   	  svt1=strtok(((char *)m_vnames.c_str()),",");
			   	  for(k=1; k<stot; k++)
			   	  {
				   	  svt1=strtok(NULL,",");
				   	  if((strcmp(sv1,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id1=k;
				   	  if((strcmp(sv2,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id2=k;				   	  		
			   	  }
		   	  }
		   	  
		   	  
		   	
		   }
		   else if((j==1) && (saeqns !=NULL) && n1>0 )
		   {
		   	//parse the equation and set the variables
		   	sseqn=saeqns->GetsString(i);
			seqn=(char *)(sseqn.c_str());
		   	std::cout << "parsing eqns eqns " << *saeqns << std::endl;
		   	
		   	std::cout << "chr *eqn "<< i <<seqn <<" " << sseqn.length() <<  std::endl;
		   	if(sseqn.length()>0)
		   		m_scafparser[i].Parse(sseqn,m_vnames);
		   }
		}
	}


	if(vt2)
	{
		saeqns=GetStringArray(IO_AGENTMODEL_VECFUNC_STRARRAY);
		
	
		for(i=0; i<(vt2->length()); i++)
		{
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt2->get(i);
		   if((saeqns !=NULL) && ((itype==10) || (itype==11) || (itype==12) || (itype==13)|| (itype==14)))
		   {

		   	  //tokenize the equation
		   	  if(seqn=(char *)((saeqns->GetsString(i)).c_str()))
		   	  {
			   	  sv1=strtok(seqn,",");
			   	  sv2=strtok(NULL,",");
			   	  
			   	  svt1=strtok(((char *)m_vnames.c_str()),",");
			   	  for(k=1; k<stot; k++)
			   	  {
				   	  svt1=strtok(NULL,",");
				   	  if((strcmp(sv1,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id1=k;
				   	  if((strcmp(sv2,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id2=k;				   	  		
			   	  }
		   	  }		   	
		   	
		   }		   
		   else if((j==1) && (saeqns != NULL) && n2>0)
		   {
		   	//parse the equation and set the variables
		   	sseqn=saeqns->GetsString(i);
		   	//std::cout << "eqns " << *saeqns << std::endl;
		   	
		   	//std::cout << "eqn "<< i <<sseqn <<" " << sseqn.length() <<  std::endl;
		   	if(sseqn.length()>0)
		   		m_vecfparser[i].Parse(sseqn,m_vnames);
		   	
		   }
		}
	}
		
	if(vt3)
	{
		saeqns=GetStringArray(IO_AGENTMODEL_SCAIPFUNC_STRARRAY);
		for(i=0; i<(vt3->length()); i++)
		{
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt3->get(i);
		   if((saeqns !=NULL) && ((itype==10) || (itype==11) || (itype==12) || (itype==13)|| (itype==14)))
		   {
		   	
		   	  //tokenize the equation
		   	  if(seqn=(char *)((saeqns->GetsString(i)).c_str()))
		   	  {
			   	  sv1=strtok(seqn,",");
			   	  sv2=strtok(NULL,",");
			   	  
			   	  svt1=strtok(((char *)m_vnames.c_str()),",");
			   	  //find the names of the variables used for dot product or vector pair operation
			   	  for(k=1; k<stot; k++)
			   	  {
				   	  //std::cout << " tokenize eqn " << svt1 <<std::endl;
				   	  svt1=strtok(NULL,",");
				   	  if((strcmp(sv1,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id1=k;
				   	  if((strcmp(sv2,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id2=k;				   	  		
			   	  }
		   	  }
		   	
		   }
		   else if((j==1) && (saeqns!=NULL)  && n3>0)
		   {
		   	//parse the equation and set the variables
		   	std::cout << "sf eqns \n" << *saeqns << std::endl;
		   	sseqn=saeqns->GetsString(i);
		   	
		   	std::cout << "sf eqn "<< i<< "\n" <<sseqn <<" length " << sseqn.length() <<  std::endl;
		   	if(sseqn.length()>0)		   	
		   		m_iscafparser[i].Parse(sseqn,m_vnames);
		   	
		   }		   

		}
	}
		
	if(vt4)
	{
		saeqns=GetStringArray(IO_AGENTMODEL_VECIPFUNC_STRARRAY);
		
		for(i=0; i<(vt4->length()); i++)
		{
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt4->get(i);
		   if((saeqns !=NULL) && ((itype==10) || (itype==11) || (itype==12) || (itype==13)|| (itype==14)))
		   {
		   	
		   	  //tokenize the equation
		   	  if(seqn=(char *)((saeqns->GetsString(i)).c_str()))
		   	  {
			   	  sv1=strtok(seqn,",");
			   	  sv2=strtok(NULL,",");
			   	  
			   	  svt1=strtok(((char *)m_vnames.c_str()),",");
			   	  for(k=1; k<stot; k++)
			   	  {
				   	  svt1=strtok(NULL,",");
				   	  if((strcmp(sv1,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id1=k;
				   	  if((strcmp(sv2,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id2=k;				   	  		
			   	  }
		   	  }
		   	
		   }
		   else if((j==1) && (saeqns !=NULL) && n4>0)
		   {
		   	//parse the equation and set the variables
		   	sseqn=saeqns->GetsString(i);
		   	std::cout << "eqns " << *saeqns << std::endl;
		   	
		   	std::cout << "eqn "<< i <<sseqn <<" " << sseqn.length() <<  std::endl;
		   	std::cout << "vnames " <<m_vnames  <<  std::endl;
		   	if(sseqn.length()>0)		   	
		   		m_ivecfparser[i].Parse(sseqn,m_vnames);
		   	//if(sseqn.length()>0)
		   		//m_vecfieldfparser[i].Parse(tseqn,tvars);
				//m_vecfieldfparser[i].Parse(sseqn,m_vnames);
		   	
		   }		   
		}
	}						
	
	if(vt5)
	{
		saeqns=GetStringArray(IO_AGENTMODEL_SCAFFUNC_STRARRAY);
		
		for(i=0; i<(vt5->length()); i++)
		{
		   	sseqn=saeqns->GetsString(i);
		   	std::cout << "eqns " << *saeqns << std::endl;
		   	
		   	std::cout << "scaf eqn "<< i << " "<<n5<<" "<<sseqn <<" " << sseqn.length() <<  std::endl;			
			
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt5->get(i);
		   if((saeqns !=NULL) && ((itype==10) || (itype==11) || (itype==12) || (itype==13)|| (itype==14)))
		   {
		   	
		   	  //tokenize the equation
		   	  if(seqn=(char *)((saeqns->GetsString(i)).c_str()))
		   	  {
			   	  sv1=strtok(seqn,",");
			   	  sv2=strtok(NULL,",");
			   	  
			   	  svt1=strtok(((char *)m_vnames.c_str()),",");
			   	  for(k=1; k<stot; k++)
			   	  {
				   	  svt1=strtok(NULL,",");
				   	  if((strcmp(sv1,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id1=k;
				   	  if((strcmp(sv2,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id2=k;				   	  		
			   	  }
		   	  }
		   	
		   }
		   else if((j==1) && (saeqns != NULL) && n5>0)
		   {
		   	//parse the equation and set the variables
		   	sseqn=saeqns->GetsString(i);
		   	std::cout << "eqns " << *saeqns << std::endl;
		   	
		   	std::cout << "scaf eqn "<< i <<sseqn <<" " << sseqn.length() <<  std::endl;
		   	if(sseqn.length()>0)		   	
		   		m_scafieldfparser[i].Parse(sseqn,m_vnames);
		   	
		   }		  
		}
	}

	if(vt6)
	{
		saeqns=GetStringArray(IO_AGENTMODEL_VECFFUNC_STRARRAY);
		
		for(i=0; i<(vt6->length()); i++)
		{
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt6->get(i);
		   if((saeqns !=NULL) && ((itype==10) || (itype==11) || (itype==12) || (itype==13)|| (itype==14)))
		   {
		   	
		   	  //tokenize the equation
		   	  string s=saeqns->GetsString(i);
		   	  if(seqn=(char *)(s.c_str()))
		   	  {
			   	  sv1=strtok(seqn,",");
			   	  sv2=strtok(NULL,",");
			   	  
			   	  svt1=strtok(((char *)m_vnames.c_str()),",");
			   	  for(k=1; k<stot; k++)
			   	  {
				   	  svt1=strtok(NULL,",");
				   	  if((strcmp(sv1,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id1=k;
				   	  if((strcmp(sv2,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[j].id2=k;				   	  		
			   	  }
		   	  }
		   	
		   }
		   else if((j==1) && (saeqns !=NULL) && n6>0)
		   {
		   	//parse the equation and set the variables
		   			   	sseqn=saeqns->GetsString(i);
		   	std::cout << "eqns " << *saeqns << std::endl;
		   	
		   	std::cout << "eqn "<< i <<sseqn <<" " << sseqn.length() <<  std::endl;
		   	if(sseqn.length()>0)		   	
		   		m_vecfieldfparser[i].Parse(sseqn,m_vnames);
		   	
		   }		   
		}
	}		
	//create func input info
	
	//create functype info arrays these used in handle state transition
	}
	



	return status;	
	
}


int CIoAgentModel::setglobal()
{
	int status=0;
		
	return status;
}









int  CIoAgentModel::CreateAgentModelConfig()
{

    return CreateAgentConfig();

}






void CIoAgentModel::HandleInteractions()
{

}

void CIoAgentModel::HandleStateTransitions()
{
	int nx,ny,nz;
	int i,j,k;
	
	nx=0;
	ny=0;
	nz=0;
	
	CIoModel::HandleStateTransitions();
    
    //set variables
	SetAllProps();


    //Evaluate global scalar func
    EvaluateGlobalScalarFuncs();
    EvaluateGlobalVecFuncs();

	EvaluateScaFieldFuncs();        	
	EvaluateVecFieldFuncs();        	
              	
}

int CIoAgentModel::EvaluateGlobalScalarFuncs()
{
	int status=0;
	int i,j;
	vec *sv=NULL;
	matrix *vm=NULL;
	mmat3d *mm3d=NULL;
	FunctionParser *scafparser=NULL;
	int nspe=GetNumScaPropEquations();
	float newval;
	vec *vetype=NULL;
	int etype=0;
			
	vetype=GetVec(IO_AGENTMODEL_SCAFUNCTYPE_VEC);
	if(sv=GetVec(IO_AGENTMODEL_FLOATPROPS_VEC))	
		for(i=0; i<nspe; i++)
		{
			etype=0;
			if(vetype && (i<vetype->length()))
			  etype=vetype->get(i);
			  
			switch(etype)
			{
				case 0:  //just apply the equation
					if(m_scafparser)
						scafparser= &(m_scafparser[i]);
					if(scafparser)
					{
					     newval=scafparser->Eval(m_vars);					     
					}
					
					scafparser=NULL;				
				break;
				
				//unit  0
				//vector dot   1
				//sum vector dot 2
				//avergae vector dot 3
				//sum   4
				//average 5				
				
				case 1:  //scalar is dot prod of two vectors
					newval=Evalsp_dotprod(i);				
				break;
				
				case 2:  // sum vector dot 2
					newval=Evalsp_sumdotprod(i);				
				break;

				case 3:  //avergae vector dot 3
					newval=Evalsp_averagedotprod(i);				
				break;

				case 4:  //sum 4
					newval=Evalsp_sum(i);				
				break;

				case 5:  //average 5
					newval=Evalsp_average(i);				
				break;
				
				default : //just apply equation same as 1
					if(m_scafparser)
						scafparser= &(m_scafparser[i]);
					if(scafparser)
					{
					     newval=scafparser->Eval(m_vars);					     
					     //update actual scalar
					     if(i<sv->length())
						 	sv->set(i,newval);
					}					
					scafparser=NULL;								
				break;						
			}
			//update actual scalar
			if(i<sv->length())
					sv->set(i,newval);			
		}


	
				
	return status;		
}


int CIoAgentModel::EvaluateGlobalVecFuncs()
{
	int status=0;
	int i,j;
	vec *sv=NULL;
	matrix *vm=NULL;
	mmat3d *mm3d=NULL;
	FunctionParser *vecfparser=NULL;
	int nvpe=GetNumVecPropEquations();
	vec tvec(3,0); //test vec used for storing results of computations
	
	vec *vetype=NULL;
	int etype=0;
	vetype=GetVec(IO_AGENTMODEL_VECFUNCTYPE_VEC);
	if(vm=GetMat(IO_AGENTMODEL_VECPROPS_MAT))	
		for(i=0; i<nvpe; i++)
		{
			etype=0;
			if(vetype && (i<vetype->length()))
			  etype=vetype->get(i);
			  
			switch(etype)
			{
				case 0:  //just apply the equation
					if(m_vecfparser)
						vecfparser= &(m_vecfparser[i]);
					if(vecfparser)
					{
					     tvec.set(0,vecfparser->Eval(m_vars1));
					     tvec.set(1,vecfparser->Eval(m_vars2));					     
					     tvec.set(2,vecfparser->Eval(m_vars3));					     					     					     
					}
					
					vecfparser=NULL;				
				break;
				
				//unit  0
				//vector cross   1
				//sum vector cross 2
				//avergae vector cross 3
				//sum   4
				//average 5				
				
				case 1:  //vec is cross prod of two vectors
					Evalvp_crossprod(i, &tvec);				
				break;
				
				case 2:  // sum vector cross 2
					Evalvp_sumcrossprod(i, &tvec);				
				break;

				case 3:  //avergae vector dot 3
					Evalvp_averagecrossprod(i, &tvec);				
				break;

				case 4:  //sum 4 
					Evalvp_sum(i, &tvec);				
				break;

				case 5:  //average 5
					Evalvp_average(i, &tvec);				
				break;
				
				default : //just apply equation same as 1
					if(m_vecfparser)
						vecfparser= &(m_vecfparser[i]);
					if(vecfparser)
					{
					     tvec.set(0,vecfparser->Eval(m_vars1));
					     tvec.set(1,vecfparser->Eval(m_vars2));					     
					     tvec.set(2,vecfparser->Eval(m_vars3));					     					     					     
					}					
					vecfparser=NULL;								
				break;						
			}
			//update actual vector
			vm->setval(i,0,tvec.get(0));
			vm->setval(i,1,tvec.get(1));
			vm->setval(i,2,tvec.get(2));
					
								
		}

	return status;		
}

int CIoAgentModel::EvaluateIScaFunc(int ieqn, int i1, int i2, int i3)
{
	int status=0;
	int i,j,k;
	int nx,ny,nz;
	//int i1,i2,i3;
	vec *sv=NULL;
	matrix *vm=NULL;
	vec *visp=NULL;
	matrix *mivp=NULL;
	FunctionParser *sfparser=NULL;
	int ne=GetNumIntermediateScaEquations();
	
	float newval;
	vec *vetype=NULL;
	int etype=0;
		
    //Evaluate global vec func
     vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
     vetype=GetVec(IO_AGENTMODEL_SCAIFUNCTYPE_VEC);
     
     if(vbox)
     {
     	nx=vbox->get(0);
     	ny=vbox->get(1);	
     	nz=vbox->get(2);	     		
     }
	
			 	if((visp=GetVec(IO_AGENTMODEL_IFLOATPROPS_VEC)) )	
		 	{
	
						j=GetVarAllIndex(i,1,2);
					m_vars[j]=visp->get(i);
					m_vars1[j]=m_vars[j];
					m_vars2[j]=m_vars[j];
					m_vars3[j]=m_vars[j];
	
						etype=0;
					if(vetype && (i<vetype->length()))
					  etype=vetype->get(i);
					
					switch(etype)
					{
						case 0:  //just apply the equation
							if(m_iscafparser)
								sfparser= &(m_iscafparser[i]);
							if(sfparser)
							{
								//update intermediates at this point
								//for some functions it may be necessary
								//to update intermediates at each nn and nnn point 
								//to a current location
								//EvaluateIScaFuncs(i1,i2,i3);        	
								//EvaluateIVecFuncs(i1,i2,i3);    												
							     newval=sfparser->Eval(m_vars);					     
							}
							
							sfparser=NULL;				
						break;
						
					    //sca field func types (applies to intermediate field also)
					    //unit   0
						//grad   1
						//div    2  n.b. div must be div of vector values !
						//del^2  3
						//nnsum  4
						//nnav   5
						//nnnsum 6
						//nnnav   7
						//nn&nnnsum 8
						//nn&nnnav  9
						//dot     10    vector dot product see above for vec function
				
						
						case 1:  //scalar grad
							newval=Evalsip_grad(i,i1,i2,i3);				
						break;
						
						case 2:  // divergence...  of vector values
							newval=Evalsip_div(i,i1,i2,i3);				
						break;
		
						case 3:  //del2
							newval=Evalsip_del2(i,i1,i2,i3);				
						break;
		
						case 4:  //nnsum 4
							newval=Evalsip_nnsum(i,i1,i2,i3);				
						break;
		
						case 5:  //nnav 5
							newval=Evalsip_nnav(i,i1,i2,i3);				
						break;
						case 6:  //nn&nnnsum 6
							newval=Evalsip_nnannnsum(i,i1,i2,i3);				
						break;
		
						case 7:  //nn&nnnav 7
							newval=Evalsip_nnannnav(i,i1,i2,i3);				
						break;
						
						case 8:  //nnsumdot 8
							newval=Evalsip_nnsumdot(i,i1,i2,i3);				
						break;
		
						case 9:  //nnavdot 9
							newval=Evalsip_nnavdot(i,i1,i2,i3);				
						break;
						case 10:  //nnnsumdot 10
							newval=Evalsip_nnnsumdot(i,i1,i2,i3);				
						break;
		
						case 11:  //nnnavdot 11
							newval=Evalsip_nnnavdot(i,i1,i2,i3);				
						break;
						case 12:  //nn&nnnsumdot 12
							newval=Evalsip_nnannnsumdot(i,i1,i2,i3);				
						break;
		
						case 13:  //nn&nnnavdot 13
							newval=Evalsip_nnannnavdot(i,i1,i2,i3);				
						break;						
						case 14:  //dot 14
							newval=Evalsip_dot(i,i1,i2,i3);				
						break;


						
						default : //just apply equation same as 1
							if(m_iscafparser)
								sfparser= &(m_iscafparser[i]);
							if(sfparser)
							{
							     newval=sfparser->Eval(m_vars);					     
							     //update actual scalar
							     //if(i<sv->length())
								 //	sv->set(i,newval);
							}					
							sfparser=NULL;								
						break;						
					}
					//update actual scalar
					//if(i<sv->length())
					//		sv->set(i,newval);
					//std::cout  << "vars " << newval << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
					//std::cout << i<< " "<< i1<< " " << i2<< " " << i3<< " "<<newval << " \n"; 
					visp->set(i,newval);
					//update property to new value
					m_vars[j]=visp->get(i);
					m_vars1[j]=m_vars[j];
					m_vars2[j]=m_vars[j];
					m_vars3[j]=m_vars[j];		
									
		 	}
	
	return status;		
}




int CIoAgentModel::EvaluateIVecFunc(int ieqn, int i1, int i2, int i3)
{
	int status=0;
	int i,j,k;
	int nx,ny,nz;
	//int i1,i2,i3;
	vec *sv=NULL;
	matrix *vm=NULL;
	vec *visp=NULL;
	matrix *mivp=NULL;
	FunctionParser *vfparser=NULL;
	int ne=GetNumIntermediateVecEquations();
	
	float newval;
	vec *vetype=NULL;
	vec vresult(3,0);
	int etype=0;
		
    //Evaluate global vec func
     vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
     vetype=GetVec(IO_AGENTMODEL_VECIFUNCTYPE_VEC);
     
     if(vbox)
     {
     	nx=vbox->get(0);
     	ny=vbox->get(1);	
     	nz=vbox->get(2);	     		
     }
	
	
			 	if( (mivp = GetMat(IO_AGENTMODEL_IVECPROPS_MAT)))	
		 	{
		 		//SetScaFieldProps(i1,i2,i3);
				//SetVecFieldProps(i1,i2,i3);
		 		
		 		//set the vector vars to value of scalar field at next point
					j=GetVarAllIndex(ieqn,3,2);
					m_vars[j]=mivp->getval(ieqn,0);
					m_vars1[j]=mivp->getval(ieqn,0);
					m_vars2[j]=mivp->getval(ieqn,1);
					m_vars3[j]=mivp->getval(ieqn,2);																	
				
									etype=0;
					if(vetype && (i<vetype->length()))
					  etype=vetype->get(i);
					  
					switch(etype)
					{
						case 0:  //just apply the equation
							if(m_ivecfparser)
								vfparser= &(m_ivecfparser[i]);
							if(vfparser)
							{
								//update intermediates at this point
								//for some functions it may be necessary
								//to update intermediates at each nn and nnn point 
								//to a current location
								//EvaluateIScaFuncs(i1,i2,i3);        	
								//EvaluateIVecFuncs(i1,i2,i3);    												
							     vresult.set(0, vfparser->Eval(m_vars1));					     
						     	 vresult.set(1, vfparser->Eval(m_vars2));					     
							     vresult.set(2, vfparser->Eval(m_vars3));					     
							     //newval=vfparser->Eval(m_vars);					     
							}
							
							vfparser=NULL;				
						break;
						
					    //sca field func types (applies to intermediate field also)
					    //unit   0
						//grad   1
						//div    2  n.b. div must be div of vector values !
						//del^2  3
						//nnsum  4
						//nnav   5
						//nnnsum 6
						//nnnav   7
						//nn&nnnsum 8
						//nn&nnnav  9
						//cross     10    vector dot product see above for vec function
				
						
						case 1:  //vec grad
							Evalvip_grad(i,i1,i2,i3, &vresult);				
						break;
						
						case 2:  // curl...  of vector values
							Evalvip_curl(i,i1,i2,i3, &vresult);				
						break;
		
						case 3:  //del2
							Evalvip_del2(i,i1,i2,i3,&vresult);				
						break;
		
						case 4:  //nnsum 4
							Evalvip_nnsum(i,i1,i2,i3,&vresult);				
						break;
		
						case 5:  //nnav 5
							Evalvip_nnav(i,i1,i2,i3,&vresult);				
						break;
						case 6:  //nn&nnnsum 6
							Evalvip_nnannnsum(i,i1,i2,i3,&vresult);				
						break;
		
						case 7:  //nn&nnnav 7
							Evalvip_nnannnav(i,i1,i2,i3,&vresult);				
						break;
						
						case 8:  //nnsumcross 8
							Evalvip_nnsumcross(i,i1,i2,i3,&vresult);				
						break;
		
						case 9:  //nnavcross 9
							Evalvip_nnavcross(i,i1,i2,i3,&vresult);				
						break;
						case 10:  //nnnsumcross 10
							Evalvip_nnnsumcross(i,i1,i2,i3,&vresult);				
						break;
		
						case 11:  //nnnavcross 11
							Evalvip_nnnavcross(i,i1,i2,i3,&vresult);				
						break;
						case 12:  //nn&nnnsumcross 12
							Evalvip_nnannnsumcross(i,i1,i2,i3,&vresult);				
						break;
		
						case 13:  //nn&nnnavcross 13
							Evalvip_nnannnavcross(i,i1,i2,i3,&vresult);				
						break;						
						case 14:  //cross 14
							Evalvip_cross(i,i1,i2,i3,&vresult);				
						break;


						
						default : //just apply equation same as 1
							if(m_ivecfparser)
								vfparser= &(m_ivecfparser[i]);
							if(vfparser)
							{
							     //newval=vfparser->Eval(m_vars);
							     vresult.set(0, vfparser->Eval(m_vars1));					     
						     	 vresult.set(1, vfparser->Eval(m_vars2));					     
							     vresult.set(2, vfparser->Eval(m_vars3));					     
								     
							}					
							vfparser=NULL;								
						break;						
					}
					//update actual scalar
					//if(i<sv->length())
					//		sv->set(i,newval);
					for(j=0; j<3; j++)								
							mivp->setval(ieqn,j,vresult[j]);		
									
				
				
				
		 	}		//end of check for existence of mivp
	
	
	return status;	
}

int CIoAgentModel::EvaluateIScaFuncs(int i1, int i2, int i3)
{
	int status=0;	
	int i,j,k;
	int nx,ny,nz;
	//int i1,i2,i3;
	vec *sv=NULL;
	matrix *vm=NULL;
	vec *visp=NULL;
	matrix *mivp=NULL;
	FunctionParser *sfparser=NULL;
	int ne=GetNumIntermediateScaEquations();
	
	float newval;
	vec *vetype=NULL;
	int etype=0;
		
    //Evaluate global vec func
     vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
     vetype=GetVec(IO_AGENTMODEL_SCAIFUNCTYPE_VEC);
     
     if(vbox)
     {
     	nx=vbox->get(0);
     	ny=vbox->get(1);	
     	nz=vbox->get(2);	     		
     }

    
    //std::cout << "eval fields \n\n" << std::endl;
    //std::cout << *Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D) << std::endl;
    //for(i=0; i<ne;i++)
	//{
					//scalar values
	//				j=GetVarAllIndex(i,1,1);
					//std::cout << j << " " <<m_vars[j]<<" " << std::endl;
	//}
	//std::cout << "seqns calc\n"; 
    //for(i1=0; i1<nx; i1++)
    //  for(i2=0; i2<ny; i2++)
    //    for(i3=0; i3<nz; i3++)
      //  {
      		
      	//	std::cout <<  "scf eval results "  << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
      		//set each scalar property to the field point
		 	if((visp=GetVec(IO_AGENTMODEL_IFLOATPROPS_VEC))  && (mivp = GetMat(IO_AGENTMODEL_IVECPROPS_MAT)))	
		 	{
		 		//SetScaFieldProps(i1,i2,i3);
				//SetVecFieldProps(i1,i2,i3);
		 		Setpprop(i1,i2,i3);
		 		
		 		//set the vector vars to value of scalar field at next point
		 		for(i=0; i<ne;i++)
				{
					//scalar values
					j=GetVarAllIndex(i,1,2);
					m_vars[j]=visp->get(i);
					m_vars1[j]=m_vars[j];
					m_vars2[j]=m_vars[j];
					m_vars3[j]=m_vars[j];
					
					//vector values						
				}
				
				for(i=0; i<GetNumIntermediateVecProps();i++)
				{
					j=GetVarAllIndex(i,3,2);
					m_vars[j]=mivp->getval(i,0);
					m_vars1[j]=mivp->getval(i,0);
					m_vars2[j]=mivp->getval(i,1);
					m_vars3[j]=mivp->getval(i,2);																	
				}				

				
				for(i=0; i<ne; i++)
				{
					EvaluateIScaFunc(i,i1,i2,i3);
				}
				//for(i=0; i<ne; i++)								
				
		        	
        }//check for mm3d exists
        //}//end looping over spatial elements	
	
	CIoAgentArray *pAgentArray=NULL;
	if((status==0) && (m_pEntitySet != NULL))
	{
		pAgentArray=(CIoAgentArray *)m_pEntitySet;
		//status=pAgentArray->CreateFunctionHandlers();
		//while(((pAgentArray=(CIoAgentArray *)(pAgentArray->GetNextEntitySet()))) && (status==0))
		//						status=pAgentArray->CreateFunctionHandlers();
			
	}
	
	
	
	return status;
}


int CIoAgentModel::EvaluateIVecFuncs(int i1, int i2, int i3)
{
	int status=0;
	int i,j,k;
	int nx,ny,nz;
	//int i1,i2,i3;
	vec *sv=NULL;
	matrix *vm=NULL;
	vec *visp=NULL;
	matrix *mivp=NULL;
	FunctionParser *vfparser=NULL;
	int ne=GetNumIntermediateVecEquations();
	
	float newval;
	vec *vetype=NULL;
	vec vresult(3,0);
	int etype=0;
		
    //Evaluate global vec func
     vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
     vetype=GetVec(IO_AGENTMODEL_VECIFUNCTYPE_VEC);
     
     if(vbox)
     {
     	nx=vbox->get(0);
     	ny=vbox->get(1);	
     	nz=vbox->get(2);	     		
     }
     
    //for(i1=0; i1<nx; i1++)
      //for(i2=0; i2<ny; i2++)
        //for(i3=0; i3<nz; i3++)
        //{
      		
      		
      		//set each scalar property to the field point
		 	if((visp=GetVec(IO_AGENTMODEL_IFLOATPROPS_VEC))  && (mivp = GetMat(IO_AGENTMODEL_IVECPROPS_MAT)))	
		 	{
		 		//SetScaFieldProps(i1,i2,i3);
				//SetVecFieldProps(i1,i2,i3);
		 		Setpprop(i1,i2,i3);
		 		
		 		//set the vector vars to value of scalar field at next point
		 		for(i=0; i<GetNumIntermediateScaProps();i++)
				{
					//scalar values
					j=GetVarAllIndex(i,1,2);
					m_vars[j]=visp->get(i);
					m_vars1[j]=m_vars[j];
					m_vars2[j]=m_vars[j];
					m_vars3[j]=m_vars[j];
					
					//vector values						
				}
				
				for(i=0; i<ne;i++)
				{
					j=GetVarAllIndex(i,3,2);
					m_vars[j]=mivp->getval(i,0);
					m_vars1[j]=mivp->getval(i,0);
					m_vars2[j]=mivp->getval(i,1);
					m_vars3[j]=mivp->getval(i,2);																	
				}				

				
				for(i=0; i<ne; i++)
				{
				}				//for(i=0; i<ne; i++)
				
		        	
        }//check for mm3d exists
        //}//end looping over spatial elements	
	
	return status;		
}



int CIoAgentModel::EvaluateScaFieldFuncs()
{
	int status=0;
	int i,j,k;
	int nx,ny,nz;
	int i1,i2,i3;
	vec *sv=NULL;
	matrix *vm=NULL;
	mmat3d *mm3d=NULL;
	mmat3d *mm3dv=NULL;
	FunctionParser *sfparser=NULL;
	int ne=GetNumScaFieldEquations();
	
	float newval;
	vec *vetype=NULL;
	int etype=0;
		
    //Evaluate global vec func
     vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
     vetype=GetVec(IO_AGENTMODEL_SCAFFUNCTYPE_VEC);
     
     if(vbox)
     {
     	nx=vbox->get(0);
     	ny=vbox->get(1);	
     	nz=vbox->get(2);	     		
     }

    
    //std::cout << "eval fields \n\n" << std::endl;
    //std::cout << *Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D) << std::endl;
    for(i=0; i<ne;i++)
	{
					//scalar values
					j=GetVarAllIndex(i,1,1);
					//std::cout << j << " " <<m_vars[j]<<" " << std::endl;
	}
	//std::cout << "seqns calc\n"; 
    for(i1=0; i1<nx; i1++)
      for(i2=0; i2<ny; i2++)
        for(i3=0; i3<nz; i3++)
        {
      		
      		//std::cout <<  "scf eval results "  << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
      		//set each scalar property to the field point
		 	if((mm3d=Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D))  && (mm3dv = Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D)))	
		 	{
		 		//SetScaFieldProps(i1,i2,i3);
				//SetVecFieldProps(i1,i2,i3);
		 		Setpprop(i1,i2,i3);
		 		//set the vector vars to value of scalar field at next point
		 		for(i=0; i<ne;i++)
				{
					//scalar values
					j=GetVarAllIndex(i,1,1);
					m_vars[j]=mm3d->getval(i1,i2,i3,i,0);
					m_vars1[j]=m_vars[j];
					m_vars2[j]=m_vars[j];
					m_vars3[j]=m_vars[j];
					
					//vector values						
				}
				
				for(i=0; i<GetNumVecFieldProps();i++)
				{
					j=GetVarAllIndex(i,3,1);
					m_vars[j]=mm3dv->getval(i1,i2,i3,i,0);
					m_vars1[j]=mm3dv->getval(i1,i2,i3,i,0);
					m_vars2[j]=mm3dv->getval(i1,i2,i3,i,1);
					m_vars3[j]=mm3dv->getval(i1,i2,i3,i,2);																	
				}				

				
				for(i=0; i<ne; i++)
				{
					etype=0;
					if(vetype && (i<vetype->length()))
					  etype=vetype->get(i);
					
					switch(etype)
					{
						case 0:  //just apply the equation
							if(m_scafieldfparser)
								sfparser= &(m_scafieldfparser[i]);
							if(sfparser)
							{
								//update intermediates at this point
								//for some functions it may be necessary
								//to update intermediates at each nn and nnn point 
								//to a current location
								EvaluateIScaFuncs(i1,i2,i3);        	
								EvaluateIVecFuncs(i1,i2,i3);    												
							     newval=sfparser->Eval(m_vars);					     
							}
							Setpprop(i1,i2,i3);
							
							sfparser=NULL;				
						break;
						
					    //sca field func types (applies to intermediate field also)
					    //unit   0
						//grad   1
						//div    2  n.b. div must be div of vector values !
						//del^2  3
						//nnsum  4
						//nnav   5
						//nnnsum 6
						//nnnav   7
						//nn&nnnsum 8
						//nn&nnnav  9
						//dot     10    vector dot product see above for vec function
				
						
						case 1:  //scalar grad
							newval=Evalsfp_grad(i,i1,i2,i3);				
						break;
						
						case 2:  // divergence...  of vector values
							newval=Evalsfp_div(i,i1,i2,i3);				
						break;
		
						case 3:  //del2
							newval=Evalsfp_del2(i,i1,i2,i3);				
						break;
		
						case 4:  //nnsum 4
							newval=Evalsfp_nnsum(i,i1,i2,i3);				
						break;
		
						case 5:  //nnav 5
							newval=Evalsfp_nnav(i,i1,i2,i3);				
						break;
						case 6:  //nn&nnnsum 6
							newval=Evalsfp_nnannnsum(i,i1,i2,i3);				
						break;
		
						case 7:  //nn&nnnav 7
							newval=Evalsfp_nnannnav(i,i1,i2,i3);				
						break;
						
						case 8:  //nnsumdot 8
							newval=Evalsfp_nnsumdot(i,i1,i2,i3);				
						break;
		
						case 9:  //nnavdot 9
							newval=Evalsfp_nnavdot(i,i1,i2,i3);				
						break;
						case 10:  //nnnsumdot 10
							newval=Evalsfp_nnnsumdot(i,i1,i2,i3);				
						break;
		
						case 11:  //nnnavdot 11
							newval=Evalsfp_nnnavdot(i,i1,i2,i3);				
						break;
						case 12:  //nn&nnnsumdot 12
							newval=Evalsfp_nnannnsumdot(i,i1,i2,i3);				
						break;
		
						case 13:  //nn&nnnavdot 13
							newval=Evalsfp_nnannnavdot(i,i1,i2,i3);				
						break;						
						case 14:  //dot 14
							newval=Evalsfp_dot(i,i1,i2,i3);				
						break;


						
						default : //just apply equation same as 1
							if(m_scafieldfparser)
								sfparser= &(m_scafieldfparser[i]);
							if(sfparser)
							{
							     newval=sfparser->Eval(m_vars);					     
							     //update actual scalar
							     if(i<sv->length())
								 	sv->set(i,newval);
							}					
							sfparser=NULL;								
						break;						
					}
					//update actual scalar
					//if(i<sv->length())
					//		sv->set(i,newval);
					//std::cout  << "vars " << newval << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
					//std::cout << i<< " "<< i1<< " " << i2<< " " << i3<< " "<<newval << " \n"; 
					mm3d->setval(i1,i2,i3,i,0,newval);		
									
				}
				//for(i=0; i<ne; i++)								
				
		        	
        }//check for mm3d exists
        }//end looping over spatial elements	
	
	CIoAgentArray *pAgentArray=NULL;
	if((status==0) && (m_pEntitySet != NULL))
	{
		pAgentArray=(CIoAgentArray *)m_pEntitySet;
		status=pAgentArray->CreateFunctionHandlers();
		while(((pAgentArray=(CIoAgentArray *)(pAgentArray->GetNextEntitySet()))) && (status==0))
								status=pAgentArray->CreateFunctionHandlers();
			
	}
	
	
	return status;		
}

int CIoAgentModel::EvaluateVecFieldFuncs()
{
	
	int status=0;
	int i,j,k;
	int nx,ny,nz;
	int i1,i2,i3;
	vec *sv=NULL;
	matrix *vm=NULL;
	mmat3d *mm3d=NULL;
	mmat3d *mm3dv=NULL;
	FunctionParser *vfparser=NULL;
	int ne=GetNumVecFieldEquations();
	
	float newval;
	vec *vetype=NULL;
	vec vresult(3,0);
	int etype=0;
		
    //Evaluate global vec func
     vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
     vetype=GetVec(IO_AGENTMODEL_VECFFUNCTYPE_VEC);
     
     if(vbox)
     {
     	nx=vbox->get(0);
     	ny=vbox->get(1);	
     	nz=vbox->get(2);	     		
     }
     
    for(i1=0; i1<nx; i1++)
      for(i2=0; i2<ny; i2++)
        for(i3=0; i3<nz; i3++)
        {
      		
      		
      		//set each scalar property to the field point
		 	if((mm3dv=Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D))  && (mm3d = Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D)))	
		 	{
		 		//SetScaFieldProps(i1,i2,i3);
				//SetVecFieldProps(i1,i2,i3);
		 		Setpprop(i1,i2,i3);
		 		
		 		//set the vector vars to value of scalar field at next point
				for(i=0; i<GetNumScaFieldProps();i++)
				{
					//scalar values
					j=GetVarAllIndex(i,1,1);
					m_vars[j]=mm3d->getval(i1,i2,i3,0,i);
					m_vars1[j]=m_vars[j];
					m_vars2[j]=m_vars[j];
					m_vars3[j]=m_vars[j];
					
					//vector values						
				}
				
				for(i=0; i<ne;i++)
				{
					j=GetVarAllIndex(i,3,1);
					m_vars[j]=mm3dv->getval(i1,i2,i3,i,0);
					m_vars1[j]=mm3dv->getval(i1,i2,i3,i,0);
					m_vars2[j]=mm3dv->getval(i1,i2,i3,i,1);
					m_vars3[j]=mm3dv->getval(i1,i2,i3,i,2);																	
				}				

				
				for(i=0; i<ne; i++)
				{
					etype=0;
					if(vetype && (i<vetype->length()))
					  etype=vetype->get(i);
					  
					switch(etype)
					{
						case 0:  //just apply the equation
							if(m_vecfieldfparser)
								vfparser= &(m_vecfieldfparser[i]);
							if(vfparser)
							{
								//update intermediates at this point
								//for some functions it may be necessary
								//to update intermediates at each nn and nnn point 
								//to a current location
								EvaluateIScaFuncs(i1,i2,i3);        	
								EvaluateIVecFuncs(i1,i2,i3);    												
							     vresult.set(0, vfparser->Eval(m_vars1));					     
						     	 vresult.set(1, vfparser->Eval(m_vars2));					     
							     vresult.set(2, vfparser->Eval(m_vars3));					     
							     //newval=vfparser->Eval(m_vars);					     
							}
							Setpprop(i1,i2,i3);
							
							vfparser=NULL;				
						break;
						
					    //sca field func types (applies to intermediate field also)
					    //unit   0
						//grad   1
						//div    2  n.b. div must be div of vector values !
						//del^2  3
						//nnsum  4
						//nnav   5
						//nnnsum 6
						//nnnav   7
						//nn&nnnsum 8
						//nn&nnnav  9
						//cross     10    vector dot product see above for vec function
				
						
						case 1:  //vec grad
							Evalvfp_grad(i,i1,i2,i3, &vresult);				
						break;
						
						case 2:  // curl...  of vector values
							Evalvfp_curl(i,i1,i2,i3, &vresult);				
						break;
		
						case 3:  //del2
							Evalvfp_del2(i,i1,i2,i3,&vresult);				
						break;
		
						case 4:  //nnsum 4
							Evalvfp_nnsum(i,i1,i2,i3,&vresult);				
						break;
		
						case 5:  //nnav 5
							Evalvfp_nnav(i,i1,i2,i3,&vresult);				
						break;
						case 6:  //nn&nnnsum 6
							Evalvfp_nnannnsum(i,i1,i2,i3,&vresult);				
						break;
		
						case 7:  //nn&nnnav 7
							Evalvfp_nnannnav(i,i1,i2,i3,&vresult);				
						break;
						
						case 8:  //nnsumcross 8
							Evalvfp_nnsumcross(i,i1,i2,i3,&vresult);				
						break;
		
						case 9:  //nnavcross 9
							Evalvfp_nnavcross(i,i1,i2,i3,&vresult);				
						break;
						case 10:  //nnnsumcross 10
							Evalvfp_nnnsumcross(i,i1,i2,i3,&vresult);				
						break;
		
						case 11:  //nnnavcross 11
							Evalvfp_nnnavcross(i,i1,i2,i3,&vresult);				
						break;
						case 12:  //nn&nnnsumcross 12
							Evalvfp_nnannnsumcross(i,i1,i2,i3,&vresult);				
						break;
		
						case 13:  //nn&nnnavcross 13
							Evalvfp_nnannnavcross(i,i1,i2,i3,&vresult);				
						break;						
						case 14:  //cross 14
							Evalvfp_cross(i,i1,i2,i3,&vresult);				
						break;


						
						default : //just apply equation same as 1
							if(m_vecfieldfparser)
								vfparser= &(m_vecfieldfparser[i]);
							if(vfparser)
							{
							     //newval=vfparser->Eval(m_vars);
							     vresult.set(0, vfparser->Eval(m_vars1));					     
						     	 vresult.set(1, vfparser->Eval(m_vars2));					     
							     vresult.set(2, vfparser->Eval(m_vars3));					     
								     
							}					
							vfparser=NULL;								
						break;						
					}
					//update actual scalar
					//if(i<sv->length())
					//		sv->set(i,newval);
					for(j=0; j<3; j++)								
							mm3dv->setval(i1,i2,i3,i,j,vresult[j]);		
									
				}
				//for(i=0; i<ne; i++)
				
		        	
        }//check for mm3d exists
        }//end looping over spatial elements	
	
	return status;		
	
	
}


double CIoAgentModel::Evalsp_dotprod(int ieqn)
{
  double result;
  int i1 = m_varinfo [ieqn].id1;
  int i2 = m_varinfo [ieqn].id2; 
  
  result=GetVecDotProd(i1,i2);
  return result;	
}
			
double CIoAgentModel::Evalsp_sumdotprod(int ieqn)
{
  double tres,result;
  
  result=0;
  mmat3d *mm3d=NULL;
  int j1,j2,j3;
  int i1 = m_varinfo [ieqn].id1;
  int i2 = m_varinfo [ieqn].id2; 
  vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
  
  int ii1 = m_varinfo [i1].index;
  int ii2 = m_varinfo [i2].index;
  for(j1=0;j1<vdim->get(0);j1++)
    for(j2=0;j2<vdim->get(1);j2++)
    	for(j3=0;j3<vdim->get(2);j3++)
    	{
    		
    		//set the vector and sclar field properties
    		
    		if(m_varinfo [i1].field==1)
    		{
    			    		if(m_varinfo [i1].dim==3)
    			    		{
								//set values
								if(mm3d=Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D))
								{								
									m_vars[i1]=mm3d->getval(j1,j2,j3,m_varinfo [i1].index,0);
									m_vars1[i1]=mm3d->getval(j1,j2,j3,m_varinfo [i1].index,0);
									m_vars2[i1]=mm3d->getval(j1,j2,j3,m_varinfo [i1].index,1);
									m_vars3[i1]=mm3d->getval(j1,j2,j3,m_varinfo [i1].index,2);
								}						
										
								
    			    		}
    						
    		}
    		if(m_varinfo [i2].field==1)
    		{
    			    		if(m_varinfo [i1].dim==3)
    			    		{
								//set values
								if(mm3d=Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D))								
								{
									m_vars[i2]=mm3d->getval(j1,j2,j3,m_varinfo [i2].index,0);
									m_vars1[i2]=mm3d->getval(j1,j2,j3,m_varinfo [i2].index,0);
									m_vars2[i2]=mm3d->getval(j1,j2,j3,m_varinfo [i2].index,1);
									m_vars3[i2]=mm3d->getval(j1,j2,j3,m_varinfo [i2].index,2);
								}						
										
									
    			    		}    			
    		}
    		if(m_varinfo [i1].field==2)
    		{
				EvaluateIVecFunc(m_varinfo [i1].index,j1,j2,j3);    
    			
    		}
    		if(m_varinfo [i2].field==2)
    		{
				EvaluateIVecFunc(m_varinfo [i2].index,j1,j2,j3);    
    			
    		}
					
    		
    		tres=GetVecDotProd(i1,i2);
    		result+=tres;
    	}
  
  
  
  
  return result;	
}
				
double CIoAgentModel::Evalsp_averagedotprod(int ieqn)
{
  double result;
  vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
  
    result=Evalsp_sumdotprod(ieqn);
    int size=(vdim->get(0))*(vdim->get(1))*(vdim->get(2));
    
    result/=((double)size);
    
  return result;	
}
				
double CIoAgentModel::Evalsp_sum(int ieqn)
{
  double newval,result=0;
  int j1,j2,j3;
  FunctionParser *scafparser=NULL;
  vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
  
    for(j1=0;j1<vdim->get(0);j1++)
    for(j2=0;j2<vdim->get(1);j2++)
    	for(j3=0;j3<vdim->get(2);j3++)
    	{
 					//update the variables
 					//set the vector and sclar field properties
					SetScaFieldProps(j1, j2, j3);
					SetVecFieldProps(j1, j2, j3);
					
					EvaluateIScaFuncs(j1,j2,j3);        	
					EvaluateIVecFuncs(j1,j2,j3);
					  
 					if(m_scafparser)
						scafparser= &(m_scafparser[ieqn]);
					if(scafparser)
					{
					     newval=scafparser->Eval(m_vars);					     
					}
					result+=newval;  		
    	}
    	
  return result;	
}
			
double CIoAgentModel::Evalsp_average(int ieqn)
{
  double result;
  vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
  
    result=Evalsp_sum(ieqn);
    int size=(vdim->get(0))*(vdim->get(1))*(vdim->get(2));
    
    result/=((double)size);
    
  return result;	
}

double CIoAgentModel::Evalsfp_grad(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsfp_div(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsfp_del2(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsfp_nnsum(int ieqn,int i1,int i2,int i3)
{
  double result=0;
 
 
	int di1,di2,di3;
	int j1,j2,j3;
	int k;
	int adi[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
	int nnn=6;
	vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
	vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
	FunctionParser *sfparser=NULL;
	if(m_scafieldfparser)
							sfparser= &(m_scafieldfparser[ieqn]);
	
    int count=0;
IoStringArray *saeqns=NULL;
	char *seqn;
string sseqn;
    saeqns=GetStringArray(IO_AGENTMODEL_SCAFFUNC_STRARRAY);
    seqn=(char *)(saeqns->GetsString(ieqn)).c_str();
    sseqn=(saeqns->GetsString(ieqn));
    //std::cout << "evalsfp_nnsum eqn is: " << seqn <<" \n";
    //std::cout << "vars are: " << m_vnames <<" \n";
	//sfparser->Parse(seqn,m_vnames);
	if((vdim->get(2))==1)
	           nnn=4;
	
	//for(di1=-1;di1<=1; di1++)
	//	for(di2=-1;di2<=1; di2++)
	//		for(di3=-1;di3<=1; di3++)
	for(k=0; k<nnn; k++)
			{
				di1=adi[k][0];
				di2=adi[k][1];
				di3=adi[k][2];
				if((di1!=0)||(di2!=0)||(di3!=0) )
				//if((vdim->get(2)>1) || ((vdim->get(2)==1) && (di3==1)) )
				{
					j1=i1+di1;
					j2=i2+di2;
					j3=i3+di3;
					
					if(j1<0)
					{
					   if((vpbc->get(0))==1)
						  j1=(vdim->get(0))-1;
					   else
					   	  j1=0;
					}
					if(j2<0)
					{
						if((vpbc->get(1))==1)
						  j2=(vdim->get(1))-1;
					   else
					   	  j2=0;
					}
					if(j3<0)
					{
					   if((vpbc->get(2))==1)
						  j3=(vdim->get(2))-1;
					   else
					   	  j3=0;
					}
					if(j1>(vdim->get(0)))
					{
					   if((vpbc->get(0))==1)
						  j1=0;
					   else
					   	  j1=(vdim->get(0))-1;
					}
					if(j2>(vdim->get(1)))
					{
					   if((vpbc->get(1))==1)
						  j2=0;
					   else
					   	  j2=(vdim->get(1))-1;
					}
					if(j3>(vdim->get(2)))
					{
					   if((vpbc->get(2))==1)
						  j3=0;
					   else
					   	  j3=(vdim->get(2))-1;
					}
					
					
					//set the vector and sclar field properties
					SetScaFieldProps(j1, j2, j3);
					SetVecFieldProps(j1, j2, j3);
					
					EvaluateIScaFuncs(j1,j2,j3);        	
					EvaluateIVecFuncs(j1,j2,j3);    
					
					//std::cout << count << " " << result << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
					//std::cout <<"count nnsum "<< count << " " << result << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
					
					result+=sfparser->Eval(m_vars);
					count ++;										
				}	
			}
		//set vector and scalar field props to original value
		SetScaFieldProps(i1, i2, i3);
		SetVecFieldProps(i1, i2, i3);
		EvaluateIScaFuncs(i1,i2,i3);        	
		EvaluateIVecFuncs(i1,i2,i3); 
	  
	
	
 
 
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsfp_nnav(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}

double CIoAgentModel::Evalsfp_nnnsum(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsfp_nnnav(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}

double CIoAgentModel::Evalsfp_nnannnsum(int ieqn,int i1,int i2,int i3)
{
				int j1,j2,j3;
				int k1,k2,k3;
				
				FunctionParser *sfparser=NULL;
				if(m_scafieldfparser)
							sfparser= &(m_scafieldfparser[ieqn]);
	
			    vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
			    vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
				double result=0;
												
				
				//do nn
				for(j1=-1; j1<2; j1++)
					for(j2=-1; j2<2; j2++)
						for(j3=-1; j3<2; j3++)
						{
							k1=i1+j1;
							k2=i2+j2;
							k3=i3+j3;
							
							if(k1<0 && (vpbc->get(0))==0) 
								k1=0;
							else
							    k1=(vbox->get(0))-1;
							    
							if(k2<0 && (vpbc->get(1))==0) 
								k2=0;
							else
							    k2=(vbox->get(1))-1;
							    
							if(k3<0 && (vpbc->get(2))==0) 
								k3=0;
							else
							    k3=(vbox->get(2))-1;

							if(k1>(vbox->get(0)) && (vpbc->get(0))==0) 
								k1=(vbox->get(0));
							else
							    k1=0;
							if(k2>(vbox->get(1)) && (vpbc->get(1))==0) 
								k2=(vbox->get(1));
							else
							    k2=0;
							if(k3>(vbox->get(2)) && (vpbc->get(2))==0) 
								k3=(vbox->get(2));
							else
							    k3=0;

							//don't include self term!
							if( j1 !=0 && j2 !=0 && j3 !=0)
							{
								if(sfparser)
								{
									//update intermediates at this point
									//for some functions it may be necessary
									//to update intermediates at each nn and nnn point 
									//to a current location
									EvaluateIScaFuncs(k1,k2,k3);        	
									EvaluateIVecFuncs(k1,k2,k3);    												
								     result+=(sfparser->Eval(m_vars));					     
								}								
								
								 
							}

							
							
							
						}//end of looping over all nn and nnn points
						
				SetScaFieldProps(i1, i2, i3);
				SetVecFieldProps(i1, i2, i3);
				
				EvaluateIScaFuncs(i1,i2,i3);        	
				EvaluateIVecFuncs(i1,i2,i3);    				
				
				//do nnn   												
				return result;
	
}
				
double CIoAgentModel::Evalsfp_nnannnav(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}

double CIoAgentModel::Evalsfp_nnsumdot(int ieqn,int i1,int i2,int i3)
{
	
  double result=0;
  
  return result;	
	
	
}

				
double CIoAgentModel::Evalsfp_nnavdot(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}


double CIoAgentModel::Evalsfp_nnnsumdot(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}

				
double CIoAgentModel::Evalsfp_nnnavdot(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}


double CIoAgentModel::Evalsfp_nnannnsumdot(int ieqn,int i1,int i2,int i3)
{
	
  double result=0;
  
  return result;	
	
	
}

				
double CIoAgentModel::Evalsfp_nnannnavdot(int ieqn,int i1,int i2,int i3)
{
	
  double result=0;
  
  return result;	
	
	
}
				
double CIoAgentModel::Evalsfp_dot(int ieqn,int i1,int i2,int i3)
{
	
  double result=0;
  
  return result;	
	
	
}



double CIoAgentModel::Evalsip_grad(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsip_div(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsip_del2(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsip_nnsum(int ieqn,int i1,int i2,int i3)
{
  double result=0;
 
 
	int di1,di2,di3;
	int j1,j2,j3;
	int k;
	int adi[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
	int nnn=6;
	vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
	vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
	FunctionParser *sfparser=NULL;
	if(m_iscafparser)
							sfparser= &(m_iscafparser[ieqn]);
	
    int count=0;
IoStringArray *saeqns=NULL;
	char *seqn;
string sseqn;
    saeqns=GetStringArray(IO_AGENTMODEL_SCAIPFUNC_STRARRAY);
    seqn=(char *)(saeqns->GetsString(ieqn)).c_str();
    sseqn=(saeqns->GetsString(ieqn));
    //std::cout << "evalsfp_nnsum eqn is: " << seqn <<" \n";
    //std::cout << "vars are: " << m_vnames <<" \n";
	//sfparser->Parse(seqn,m_vnames);
	if((vdim->get(2))==1)
	           nnn=4;
	
	//for(di1=-1;di1<=1; di1++)
	//	for(di2=-1;di2<=1; di2++)
	//		for(di3=-1;di3<=1; di3++)
	for(k=0; k<nnn; k++)
			{
				di1=adi[k][0];
				di2=adi[k][1];
				di3=adi[k][2];
				if((di1!=0)||(di2!=0)||(di3!=0) )
				//if((vdim->get(2)>1) || ((vdim->get(2)==1) && (di3==1)) )
				{
					j1=i1+di1;
					j2=i2+di2;
					j3=i3+di3;
					
					if(j1<0)
					{
					   if((vpbc->get(0))==1)
						  j1=(vdim->get(0))-1;
					   else
					   	  j1=0;
					}
					if(j2<0)
					{
						if((vpbc->get(1))==1)
						  j2=(vdim->get(1))-1;
					   else
					   	  j2=0;
					}
					if(j3<0)
					{
					   if((vpbc->get(2))==1)
						  j3=(vdim->get(2))-1;
					   else
					   	  j3=0;
					}
					if(j1>(vdim->get(0)))
					{
					   if((vpbc->get(0))==1)
						  j1=0;
					   else
					   	  j1=(vdim->get(0))-1;
					}
					if(j2>(vdim->get(1)))
					{
					   if((vpbc->get(1))==1)
						  j2=0;
					   else
					   	  j2=(vdim->get(1))-1;
					}
					if(j3>(vdim->get(2)))
					{
					   if((vpbc->get(2))==1)
						  j3=0;
					   else
					   	  j3=(vdim->get(2))-1;
					}
					
					
					//set the vector and sclar field properties
					SetScaFieldProps(j1, j2, j3);
					SetVecFieldProps(j1, j2, j3);
					
					EvaluateIScaFuncs(j1,j2,j3);        	
					EvaluateIVecFuncs(j1,j2,j3);    
					
					//std::cout << count << " " << result << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
					//std::cout <<"count nnsum "<< count << " " << result << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
					
					result+=sfparser->Eval(m_vars);
					count ++;										
				}	
			}
		//set vector and scalar field props to original value
		SetScaFieldProps(i1, i2, i3);
		SetVecFieldProps(i1, i2, i3);
		EvaluateIScaFuncs(i1,i2,i3);        	
		EvaluateIVecFuncs(i1,i2,i3); 
	  
	
	
 
 
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsip_nnav(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}

double CIoAgentModel::Evalsip_nnnsum(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}
				
double CIoAgentModel::Evalsip_nnnav(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}

double CIoAgentModel::Evalsip_nnannnsum(int ieqn,int i1,int i2,int i3)
{
				int j1,j2,j3;
				int k1,k2,k3;
				
				FunctionParser *sfparser=NULL;
				if(m_iscafparser)
							sfparser= &(m_iscafparser[ieqn]);
	
			    vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
			    vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
				double result=0;
				//EvaluateIScaFuncs(i1,i2,i3);        	
				//EvaluateIVecFuncs(i1,i2,i3);    												
				
				//do nn
				for(j1=-1; j1<2; j1++)
					for(j2=-1; j2<2; j2++)
						for(j3=-1; j3<2; j3++)
						{
							k1=i1+j1;
							k2=i2+j2;
							k3=i3+j3;
							
							if(k1<0 && (vpbc->get(0))==0) 
								k1=0;
							else
							    k1=(vbox->get(0))-1;
							    
							if(k2<0 && (vpbc->get(1))==0) 
								k2=0;
							else
							    k2=(vbox->get(1))-1;
							    
							if(k3<0 && (vpbc->get(2))==0) 
								k3=0;
							else
							    k3=(vbox->get(2))-1;

							if(k1>(vbox->get(0)) && (vpbc->get(0))==0) 
								k1=(vbox->get(0));
							else
							    k1=0;
							if(k2>(vbox->get(1)) && (vpbc->get(1))==0) 
								k2=(vbox->get(1));
							else
							    k2=0;
							if(k3>(vbox->get(2)) && (vpbc->get(2))==0) 
								k3=(vbox->get(2));
							else
							    k3=0;

							//don't include self term!
							if( j1 !=0 && j2 !=0 && j3 !=0)
							{
								if(sfparser)
								{
									//update intermediates at this point
									//for some functions it may be necessary
									//to update intermediates at each nn and nnn point 
									//to a current location
									EvaluateIScaFuncs(k1,k2,k3);        	
									EvaluateIVecFuncs(k1,k2,k3);    												
								     result+=(sfparser->Eval(m_vars));					     
								}								
								
								 
							}

							
							
							
						}//end of looping over all nn and nnn points
				
				
				//do nnn   												
				return result;
	
}
				
double CIoAgentModel::Evalsip_nnannnav(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}

double CIoAgentModel::Evalsip_nnsumdot(int ieqn,int i1,int i2,int i3)
{
	
  double result=0;
  
  return result;	
	
	
}

				
double CIoAgentModel::Evalsip_nnavdot(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}


double CIoAgentModel::Evalsip_nnnsumdot(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}

				
double CIoAgentModel::Evalsip_nnnavdot(int ieqn,int i1,int i2,int i3)
{
  double result=0;
  
  return result;	
	
	
	
}


double CIoAgentModel::Evalsip_nnannnsumdot(int ieqn,int i1,int i2,int i3)
{
	
  double result=0;
  
  return result;	
	
	
}

				
double CIoAgentModel::Evalsip_nnannnavdot(int ieqn,int i1,int i2,int i3)
{
	
  double result=0;
  
  return result;	
	
	
}
				
double CIoAgentModel::Evalsip_dot(int ieqn,int i1,int i2,int i3)
{
	
  double result=0;
  int ii1 = m_varinfo [ieqn].id1;
  int ii2 = m_varinfo [ieqn].id2; 
  
  result=GetVecDotProd(ii1,ii2);
  
  return result;	
	
	
}








				

			




double CIoAgentModel::GetVecDotProd(int id1, int id2)
{
    vec v1(3,0);
    vec v2(3,0);
    
    v1.set(0,m_vars1[id1]);
    v1.set(1,m_vars2[id1]);
    v1.set(2,m_vars3[id1]);

    v2.set(0,m_vars1[id2]);
    v2.set(1,m_vars2[id2]);
    v2.set(2,m_vars3[id2]);
   
	return v1.dot(v2);
}

void CIoAgentModel::GetVecCrossProd(int id1, int id2, vec *result)
{
    vec v1(3,0);
    vec v2(3,0);
    vec v3(3,0);
    
    v1.set(0,m_vars1[id1]);
    v1.set(1,m_vars2[id1]);
    v1.set(2,m_vars3[id1]);

    v2.set(0,m_vars1[id2]);
    v2.set(1,m_vars2[id2]);
    v2.set(2,m_vars3[id2]);
    
    //*result = v1.cross(&v2);
   if(result)
   {
   		result->set(0,v1[1]*v2[2]-v1[2]*v2[1]);
   		result->set(1,-v1[0]*v2[2]+v1[2]*v2[0]);
      	result->set(2,v1[0]*v2[3]-v1[1]*v2[0]);  
   }
   
   
   
   
}

void CIoAgentModel::Evalvp_crossprod(int ieqn, vec *result)
{
  //double result;
  int i1 = m_varinfo [ieqn].id1;
  int i2 = m_varinfo [ieqn].id2; 
  
  GetVecCrossProd(i1,i2,result);
  //return result;	
	
}
				
void CIoAgentModel::Evalvp_sumcrossprod(int ieqn, vec *result)
{
	
	
	
}

		
void CIoAgentModel::Evalvp_averagecrossprod(int ieqn, vec *result)
{
	
	
	
}
				
void CIoAgentModel::Evalvp_sum(int ieqn, vec *result)
{
	
	
	
}
				
void CIoAgentModel::Evalvp_average(int ieqn, vec *result)
{
	
	
	
}

int CIoAgentModel::SetScaProps()
{
	int status=0;
	int i,j;
	vec *sv=NULL;
	//set values
	if(sv=GetVec(IO_AGENTMODEL_FLOATPROPS_VEC))
		for(i=0; i<GetNumScaProps();i++)
		{
			j=GetVarAllIndex(i,1,0);
			m_vars[j]=sv->get(i);
			m_vars1[j]=m_vars[j];
			m_vars2[j]=m_vars[j];
			m_vars3[j]=m_vars[j];
			
		}
	

	
	return status;	
}

int CIoAgentModel::SetVecProps()
{
	int status=0;
	int i,j;
	matrix *vm=NULL;
	//set values

	
	if(vm=GetMat(IO_AGENTMODEL_VECPROPS_MAT))
		for(i=0; i<GetNumVecProps();i++)
		{
			j=GetVarAllIndex(i,3,0);
			m_vars[j]=vm->getval(i,0);
			m_vars1[j]=vm->getval(i,0);
			m_vars2[j]=vm->getval(i,1);
			m_vars3[j]=vm->getval(i,2);
		}
	return status;	
}


int CIoAgentModel::SetScaIProps()
{
	int status=0;
	int i,j;
	vec *sv=NULL;

	if(sv=GetVec(IO_AGENTMODEL_IFLOATPROPS_VEC))		
		for(i=0; i<GetNumIntermediateScaProps();i++)
		{
			j=GetVarAllIndex(i,1,2);
			m_vars[j]=sv->get(i);
			m_vars1[j]=m_vars[j];
			m_vars2[j]=m_vars[j];
			m_vars3[j]=m_vars[j];
						
		}
	
	return status;	
}

int CIoAgentModel::SetVecIProps()
{
	int status=0;
	int i,j;
	matrix *vm=NULL;
	//set values
	if(vm=GetMat(IO_AGENTMODEL_IVECPROPS_MAT))					
		for(i=0; i<GetNumIntermediateVecProps();i++)
		{
			j=GetVarAllIndex(i,3,2);
			m_vars[j]=vm->getval(i,0);
			m_vars1[j]=vm->getval(i,0);
			m_vars2[j]=vm->getval(i,1);
			m_vars3[j]=vm->getval(i,2);						
		}		

	return status;	
}


int CIoAgentModel::SetScaFieldProps(int i1, int i2, int i3)
{
	int status=0;
	int i,j;
	mmat3d *mm3d=NULL;
	//set values

	if(mm3d=Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D))						
		for(i=0; i<GetNumScaFieldProps();i++)
		{
			j=GetVarAllIndex(i,1,1);
			
			m_vars[j]=mm3d->getval(i1,i2,i3,i,0);
			m_vars1[j]=m_vars[j];
			m_vars2[j]=m_vars[j];
			m_vars3[j]=m_vars[j];						
		}
			
	return status;	
}


int CIoAgentModel::SetVecFieldProps(int i1, int i2, int i3)
{
	int status=0;
	int i,j;
	mmat3d *mm3d=NULL;
	//set values
	if(mm3d=Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D))								
		for(i=0; i<GetNumVecFieldProps();i++)
		{
			j=GetVarAllIndex(i,3,1);
			m_vars[j]=mm3d->getval(i1,i2,i3,i,0);
			m_vars1[j]=mm3d->getval(i1,i2,i3,i,0);
			m_vars2[j]=mm3d->getval(i1,i2,i3,i,1);
			m_vars3[j]=mm3d->getval(i1,i2,i3,i,2);						
									
		}	
	
	return status;	
}

int CIoAgentModel::SetAllProps()
{
	int status=0;
	Settprop();
	Setpprop();
	SetScaProps();
	SetVecProps();
	SetScaIProps();
	SetVecIProps();
	SetScaFieldProps();
	SetVecFieldProps();
		
	return status;	
}

int CIoAgentModel::Settprop()
{
	int status=0;

    int is=GetCurrentStep();
	m_vars[0]=(double)is;
	m_vars1[0]=(double)is;
	m_vars2[0]=(double)is;
	m_vars3[0]=(double)is;
					
	return status;
}


int CIoAgentModel::Setpprop(int i, int j, int k)
{
	int status=0;

	m_vars[1]=(double)i;
	m_vars1[1]=(double)i;
	m_vars2[1]=(double)i;
	m_vars3[1]=(double)i;

	m_vars[2]=(double)j;
	m_vars1[2]=(double)j;
	m_vars2[2]=(double)j;
	m_vars3[2]=(double)j;

	m_vars[3]=(double)k;
	m_vars1[3]=(double)k;
	m_vars2[3]=(double)k;
	m_vars3[3]=(double)k;
					
	return status;	
}	


void CIoAgentModel::Evalvfp_grad(int ieqn,int i1,int i2,int i3, vec *vres)
{
    vec result(3,0);
 
    int i,j;
	int di1,di2,di3;
	int j1,j2,j3;
	vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
	vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
	FunctionParser *sfparser=NULL;
	if(m_vecfieldfparser)
							sfparser= &(m_vecfieldfparser[ieqn]);
	
    int count=0;
    //std::cout << "nnsum \n";
    for(i=0; i<3; i++)
    {
				for(j=-1; j<2; j+=2)
				{
				switch(i)
				{
					case 0:
						di1=j;
						di2=0;
						di3=0;
					break;
					case 1:
						di1=0;
						di2=j;
						di3=0;
					
					break;
					case 2:
						di1=0;
						di2=0;
						di3=j;
					break;	
				}
				
				if((di1!=0)||(di2!=0)||(di3!=0) )
				{
					j1=i1+di1;
					j2=i2+di2;
					j3=i3+di3;
					
					if(j1<0)
					{
					   if((vpbc->get(0))==1)
						  j1=(vdim->get(0))-1;
					   else
					   	  j1=0;
					}
					if(j2<0)
					{
						if((vpbc->get(1))==1)
						  j2=(vdim->get(1))-1;
					   else
					   	  j2=0;
					}
					if(j3<0)
					{
					   if((vpbc->get(2))==1)
						  j3=(vdim->get(2))-1;
					   else
					   	  j3=0;
					}
					if(j1>(vdim->get(0)))
					{
					   if((vpbc->get(0))==1)
						  j1=0;
					   else
					   	  j1=(vdim->get(0))-1;
					}
					if(j2>(vdim->get(1)))
					{
					   if((vpbc->get(1))==1)
						  j2=0;
					   else
					   	  j2=(vdim->get(1))-1;
					}
					if(j3>(vdim->get(2)))
					{
					   if((vpbc->get(2))==1)
						  j3=0;
					   else
					   	  j3=(vdim->get(2))-1;
					}
					
					
					//set the vector and sclar field properties
					SetScaFieldProps(j1, j2, j3);
					SetVecFieldProps(j1, j2, j3);
					
					EvaluateIScaFuncs(j1,j2,j3);        	
					EvaluateIVecFuncs(j1,j2,j3);    
					
					//std::cout << count << " " << result << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
					//result.set(i,result.get(i)+j*(sfparser->Eval(m_vars)));
															
				}	
				}
    }
		//set vector and scalar field props to original value
		SetScaFieldProps(i1, i2, i3);
		SetVecFieldProps(i1, i2, i3);
		EvaluateIScaFuncs(i1,i2,i3);        	
		EvaluateIVecFuncs(i1,i2,i3); 
		if(vres && (vres->length()>2))
		{
			for(i=0;i<3; i++)
			    vres->set(i, result.get(i));
					
		}
		  
	  
	
	
 
 
  
	
	
}
				
void CIoAgentModel::Evalvfp_curl(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}

				
void CIoAgentModel::Evalvfp_del2(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}

				
void CIoAgentModel::Evalvfp_nnsum(int ieqn,int i1,int i2,int i3, vec *vres)
{
	int di1,di2,di3;
	int j1,j2,j3;
	int k;
	vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
	vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
	FunctionParser *vfparser=NULL;
	if(m_vecfieldfparser)
							vfparser= &(m_vecfieldfparser[ieqn]);
	
	vec vsum(3,0);
	if(vres  && vres->length()>2)
	{
	for(di1=-1;di1<=1; di1++)
		for(di2=-1;di2<=1; di2++)
			for(di3=-1;di3<=1; di3++)
			{
				if((di1 !=0)&&(di2 !=0)&&(di3 !=0))
				{
					j1=i1+di1;
					j2=i2+di2;
					j3=i3+di3;
					
					if(j1<0)
					{
					   if((vpbc->get(0))==1)
						  j1=(vdim->get(0))-1;
					   else
					   	  j1=0;
					}
					if(j2<0)
					{
						if((vpbc->get(1))==1)
						  j2=(vdim->get(1))-1;
					   else
					   	  j2=0;
					}
					if(j3<0)
					{
					   if((vpbc->get(2))==1)
						  j3=(vdim->get(2))-1;
					   else
					   	  j3=0;
					}
					if(j1>(vdim->get(0)))
					{
					   if((vpbc->get(0))==1)
						  j1=0;
					   else
					   	  j1=(vdim->get(0))-1;
					}
					if(j2>(vdim->get(1)))
					{
					   if((vpbc->get(1))==1)
						  j2=0;
					   else
					   	  j2=(vdim->get(1))-1;
					}
					if(j3>(vdim->get(2)))
					{
					   if((vpbc->get(2))==1)
						  j3=0;
					   else
					   	  j3=(vdim->get(2))-1;
					}
					
					
					//set the vector and sclar field properties
					SetScaFieldProps(j1, j2, j3);
					SetVecFieldProps(j1, j2, j3);
					
					EvaluateIScaFuncs(j1,j2,j3);        	
					EvaluateIVecFuncs(j1,j2,j3);    
					
					vsum.set(0, vsum.get(0)+vfparser->Eval(m_vars1));
					vsum.set(1, vsum.get(1)+vfparser->Eval(m_vars2));
					vsum.set(2, vsum.get(2)+vfparser->Eval(m_vars3));
															
				}	
			}
	    for(k=0; k<3; k++)
	      vres->set(k, vsum.get(k));
		//set vector and scalar field props to original value
		SetScaFieldProps(i1, i2, i3);
		SetVecFieldProps(i1, i2, i3);
		EvaluateIScaFuncs(i1,i2,i3);        	
		EvaluateIVecFuncs(i1,i2,i3); 
	}   
	
	
}

				
void CIoAgentModel::Evalvfp_nnav(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


void CIoAgentModel::Evalvfp_nnnsum(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}

				
void CIoAgentModel::Evalvfp_nnnav(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}

				
void CIoAgentModel::Evalvfp_nnannnsum(int ieqn,int i1,int i2,int i3, vec *vres)
{
				int j1,j2,j3;
				int k1,k2,k3;
				int i;
				double result=0;
				
				FunctionParser *vfparser=NULL;
				
				if(vres)
				{
				if(m_vecfieldfparser)
							vfparser= &(m_vecfieldfparser[ieqn]);
	
			    vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
			    vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
				double res1=0, res2=0,res3=0;
				EvaluateIScaFuncs(i1,i2,i3);        	
				EvaluateIVecFuncs(i1,i2,i3);    												
				
				//do nn
				for(j1=-1; j1<2; j1++)
					for(j2=-1; j2<2; j2++)
						for(j3=-1; j3<2; j3++)
						{
							k1=i1+j1;
							k2=i2+j2;
							k3=i3+j3;
							
							if(k1<0 && (vpbc->get(0))==0) 
								k1=0;
							else
							    k1=(vbox->get(0))-1;
							    
							if(k2<0 && (vpbc->get(1))==0) 
								k2=0;
							else
							    k2=(vbox->get(1))-1;
							    
							if(k3<0 && (vpbc->get(2))==0) 
								k3=0;
							else
							    k3=(vbox->get(2))-1;

							if(k1>(vbox->get(0)) && (vpbc->get(0))==0) 
								k1=(vbox->get(0));
							else
							    k1=0;
							if(k2>(vbox->get(1)) && (vpbc->get(1))==0) 
								k2=(vbox->get(1));
							else
							    k2=0;
							if(k3>(vbox->get(2)) && (vpbc->get(2))==0) 
								k3=(vbox->get(2));
							else
							    k3=0;

							//don't include self term!
							if( j1 !=0 && j2 !=0 && j3 !=0)
							{
								if(vfparser)
								{
									//update intermediates at this point
									//for some functions it may be necessary
									//to update intermediates at each nn and nnn point 
									//to a current location
									EvaluateIScaFuncs(k1,k2,k3);        	
									EvaluateIVecFuncs(k1,k2,k3); 
								     res1+=(vfparser->Eval(m_vars1));
								     res2+=(vfparser->Eval(m_vars2));					     
								     res3+=(vfparser->Eval(m_vars3));					     
								     					     
								}								
								
								 
							}

							
							
							
						}//end of looping over all nn and nnn points
						
						vres->set(0,res1);
						vres->set(1,res2);
						vres->set(2,res3);												
				}//end of vres check
				
				//do nnn   												
	
	
}

				
void CIoAgentModel::Evalvfp_nnannnav(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvfp_nnsumcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvfp_nnavcross(int ieqn,int i1,int i2,int i3, vec *vres)	
{
	
	
}


			
void CIoAgentModel::Evalvfp_nnnsumcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvfp_nnnavcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvfp_nnannnsumcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvfp_nnannnavcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
					
void CIoAgentModel::Evalvfp_cross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}















void CIoAgentModel::Evalvip_grad(int ieqn,int i1,int i2,int i3, vec *vres)
{
    vec result(3,0);
 
    int i,j;
	int di1,di2,di3;
	int j1,j2,j3;
	vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
	vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
	FunctionParser *sfparser=NULL;
	if(m_ivecfparser)
							sfparser= &(m_ivecfparser[ieqn]);
	
    int count=0;
    //std::cout << "nnsum \n";
    for(i=0; i<3; i++)
    {
				for(j=-1; j<2; j+=2)
				{
				switch(i)
				{
					case 0:
						di1=j;
						di2=0;
						di3=0;
					break;
					case 1:
						di1=0;
						di2=j;
						di3=0;
					
					break;
					case 2:
						di1=0;
						di2=0;
						di3=j;
					break;	
				}
				
				if((di1!=0)||(di2!=0)||(di3!=0) )
				{
					j1=i1+di1;
					j2=i2+di2;
					j3=i3+di3;
					
					if(j1<0)
					{
					   if((vpbc->get(0))==1)
						  j1=(vdim->get(0))-1;
					   else
					   	  j1=0;
					}
					if(j2<0)
					{
						if((vpbc->get(1))==1)
						  j2=(vdim->get(1))-1;
					   else
					   	  j2=0;
					}
					if(j3<0)
					{
					   if((vpbc->get(2))==1)
						  j3=(vdim->get(2))-1;
					   else
					   	  j3=0;
					}
					if(j1>(vdim->get(0)))
					{
					   if((vpbc->get(0))==1)
						  j1=0;
					   else
					   	  j1=(vdim->get(0))-1;
					}
					if(j2>(vdim->get(1)))
					{
					   if((vpbc->get(1))==1)
						  j2=0;
					   else
					   	  j2=(vdim->get(1))-1;
					}
					if(j3>(vdim->get(2)))
					{
					   if((vpbc->get(2))==1)
						  j3=0;
					   else
					   	  j3=(vdim->get(2))-1;
					}
					
					
					//set the vector and sclar field properties
					SetScaFieldProps(j1, j2, j3);
					SetVecFieldProps(j1, j2, j3);
					
					EvaluateIScaFuncs(j1,j2,j3);        	
					EvaluateIVecFuncs(j1,j2,j3);    
					
					//std::cout << count << " " << result << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
					//result.set(i,result.get(i)+j*(sfparser->Eval(m_vars)));
					//use results to calculate components of grad
															
				}	
				}
    }
		//set vector and scalar field props to original value
		SetScaFieldProps(i1, i2, i3);
		SetVecFieldProps(i1, i2, i3);
		EvaluateIScaFuncs(i1,i2,i3);        	
		EvaluateIVecFuncs(i1,i2,i3); 
		if(vres && (vres->length()>2))
		{
			for(i=0;i<3; i++)
			    vres->set(i, result.get(i));
					
		}
		  
	  
	
	
 
 
  
	
	
}
				
void CIoAgentModel::Evalvip_curl(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}

				
void CIoAgentModel::Evalvip_del2(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}

				
void CIoAgentModel::Evalvip_nnsum(int ieqn,int i1,int i2,int i3, vec *vres)
{
	int di1,di2,di3;
	int j1,j2,j3;
	int k;
	vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
	vec *vdim=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
	FunctionParser *vfparser=NULL;
	if(m_ivecfparser)
							vfparser= &(m_ivecfparser[ieqn]);
	
	vec vsum(3,0);
	if(vres  && vres->length()>2)
	{
	for(di1=-1;di1<=1; di1++)
		for(di2=-1;di2<=1; di2++)
			for(di3=-1;di3<=1; di3++)
			{
				if((di1 !=0)&&(di2 !=0)&&(di3 !=0))
				{
					j1=i1+di1;
					j2=i2+di2;
					j3=i3+di3;
					
					if(j1<0)
					{
					   if((vpbc->get(0))==1)
						  j1=(vdim->get(0))-1;
					   else
					   	  j1=0;
					}
					if(j2<0)
					{
						if((vpbc->get(1))==1)
						  j2=(vdim->get(1))-1;
					   else
					   	  j2=0;
					}
					if(j3<0)
					{
					   if((vpbc->get(2))==1)
						  j3=(vdim->get(2))-1;
					   else
					   	  j3=0;
					}
					if(j1>(vdim->get(0)))
					{
					   if((vpbc->get(0))==1)
						  j1=0;
					   else
					   	  j1=(vdim->get(0))-1;
					}
					if(j2>(vdim->get(1)))
					{
					   if((vpbc->get(1))==1)
						  j2=0;
					   else
					   	  j2=(vdim->get(1))-1;
					}
					if(j3>(vdim->get(2)))
					{
					   if((vpbc->get(2))==1)
						  j3=0;
					   else
					   	  j3=(vdim->get(2))-1;
					}
					
					
					//set the vector and sclar field properties
					SetScaFieldProps(j1, j2, j3);
					SetVecFieldProps(j1, j2, j3);
					
					EvaluateIScaFuncs(j1,j2,j3);        	
					EvaluateIVecFuncs(j1,j2,j3);    
					
					vsum.set(0, vsum.get(0)+vfparser->Eval(m_vars1));
					vsum.set(1, vsum.get(1)+vfparser->Eval(m_vars2));
					vsum.set(2, vsum.get(2)+vfparser->Eval(m_vars3));
															
				}	
			}
	    for(k=0; k<3; k++)
	      vres->set(k, vsum.get(k));
		//set vector and scalar field props to original value
		SetScaFieldProps(i1, i2, i3);
		SetVecFieldProps(i1, i2, i3);
		EvaluateIScaFuncs(i1,i2,i3);        	
		EvaluateIVecFuncs(i1,i2,i3); 
	}   
	
	
}

				
void CIoAgentModel::Evalvip_nnav(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


void CIoAgentModel::Evalvip_nnnsum(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}

				
void CIoAgentModel::Evalvip_nnnav(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}

				
void CIoAgentModel::Evalvip_nnannnsum(int ieqn,int i1,int i2,int i3, vec *vres)
{
				int j1,j2,j3;
				int k1,k2,k3;
				int i;
				double result=0;
				
				FunctionParser *vfparser=NULL;
				
				if(vres)
				{
				if(m_ivecfparser)
							vfparser= &(m_ivecfparser[ieqn]);
	
			    vec *vbox=GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
			    vec *vpbc=GetVec(IO_AGENTMODEL_MODELPBC_VEC);
				double res1=0, res2=0,res3=0;
				EvaluateIScaFuncs(i1,i2,i3);        	
				EvaluateIVecFuncs(i1,i2,i3);    												
				
				//do nn
				for(j1=-1; j1<2; j1++)
					for(j2=-1; j2<2; j2++)
						for(j3=-1; j3<2; j3++)
						{
							k1=i1+j1;
							k2=i2+j2;
							k3=i3+j3;
							
							if(k1<0 && (vpbc->get(0))==0) 
								k1=0;
							else
							    k1=(vbox->get(0))-1;
							    
							if(k2<0 && (vpbc->get(1))==0) 
								k2=0;
							else
							    k2=(vbox->get(1))-1;
							    
							if(k3<0 && (vpbc->get(2))==0) 
								k3=0;
							else
							    k3=(vbox->get(2))-1;

							if(k1>(vbox->get(0)) && (vpbc->get(0))==0) 
								k1=(vbox->get(0));
							else
							    k1=0;
							if(k2>(vbox->get(1)) && (vpbc->get(1))==0) 
								k2=(vbox->get(1));
							else
							    k2=0;
							if(k3>(vbox->get(2)) && (vpbc->get(2))==0) 
								k3=(vbox->get(2));
							else
							    k3=0;

							//don't include self term!
							if( j1 !=0 && j2 !=0 && j3 !=0)
							{
								if(vfparser)
								{
									//update intermediates at this point
									//for some functions it may be necessary
									//to update intermediates at each nn and nnn point 
									//to a current location
									EvaluateIScaFuncs(k1,k2,k3);        	
									EvaluateIVecFuncs(k1,k2,k3); 
								     res1+=(vfparser->Eval(m_vars1));
								     res2+=(vfparser->Eval(m_vars2));					     
								     res3+=(vfparser->Eval(m_vars3));					     
								     					     
								}								
								
								 
							}

							
							
							
						}//end of looping over all nn and nnn points
						
						vres->set(0,res1);
						vres->set(1,res2);
						vres->set(2,res3);												
				}//end of vres check
				
				//do nnn   												
	
	
}

				
void CIoAgentModel::Evalvip_nnannnav(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvip_nnsumcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvip_nnavcross(int ieqn,int i1,int i2,int i3, vec *vres)	
{
	
	
}


			
void CIoAgentModel::Evalvip_nnnsumcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvip_nnnavcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvip_nnannnsumcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
void CIoAgentModel::Evalvip_nnannnavcross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}


				
					
void CIoAgentModel::Evalvip_cross(int ieqn,int i1,int i2,int i3, vec *vres)
{
	
	
}







CIoEntitySet *CIoAgentModel::newEntitySet(char *sEntitySetClass)
{
	CIoAgentArray *pEntitySet=NULL;
	//If the root entity set is the default entity set 
	//then delete the default
	if(strcmp(sEntitySetClass, "AgentArray")==0 /*|| strcmp(sEntitySetClass, "EntityArray3d")==0*/)
	{
		if(m_pEntitySet /*&& (strcmp(m_pEntitySet->GetEntitySetName(), "DefaultMagArray")==0)*/)
		{
			delete m_pEntitySet;
			m_pEntitySet = NULL;
		}
		pEntitySet = new CIoAgentArray(GetParentSimulation(),this, this);
		pEntitySet->SetEntityTypeSet(pEntitySet->newEntityTypeSet("EntityTypeSet"));
		pEntitySet->SetEntitySetName("NewAgentArray");
		
		
		//AddEntitySet((CIoEntitySet *)pEntitySet);
	}
	//Other types of entity set may be added if the model allows them!

	return pEntitySet;
}

CIoEntity  *CIoAgentModel::newEntityES(CIoEntitySet *pES)
{
	if(pES)
	{
		return(pES->newEntity());
	}
	return NULL;
}


