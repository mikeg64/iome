#include "IoAgentArray.h"

CIoAgentArray::CIoAgentArray(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoEntityArray3d(pParentSimulation, pParentSimulant, pParentHandler)
{
	SetEntityTypeSet(newEntityTypeSet("AgentTypeSet"));
	SetEntitySetClass("AgentArray");
	m_pCurrentAgent=NULL;
}

CIoAgentArray::~CIoAgentArray(void)
{
}

CIoEntityTypeSet *CIoAgentArray::newEntityTypeSet(char *sEntityTypeSetClass)
{
	CIoEntityTypeSet *pEntityTypeSet = NULL;
    if(strcmp(sEntityTypeSetClass, "AgentTypeSet")==0)
		pEntityTypeSet = new CIoAgentTypeSet(GetParentSimulation(),GetParentSimulant(), this);
    return pEntityTypeSet;
}

CIoEntity *CIoAgentArray::newEntity()
{
	CIoEntity *pEntity = NULL;
	pEntity =  new CIoAgent(GetParentSimulation(), GetParentSimulant(), this);
    return pEntity;
}

void CIoAgentArray::CreatePropNames()
{
	AddPropName("Dimensions");
	AddPropName("ConfigType");
	AddPropName("ConfigCreateParamMatrix");
	AddPropName("PositionVector");
	AddPropName("ScalarAgentEntityTypePropNames");
	AddPropName("VectorAgentEntityTypePropNames");
	AddPropName("ScalarAgentEntityPropNames");
	AddPropName("VectorAgentEntityPropNames");
	
	AddPropName("ScalarAgentPropFunctions");
	AddPropName("VectorAgentPropFunctions");
	AddPropName("ScalarFieldEvolutionFunctions");
	AddPropName("VectorFieldEvolutionFunctions");
    AddPropName("PositionVectorEvolutionFunction");
	AddPropName("ScalarAgentPropFunctionTypes");
	AddPropName("VectorAgentPropFunctionTypes");
	AddPropName("ScalarFieldEvolutionFunctionTypes");
	AddPropName("VectorFieldEvolutionFunctionTypes");
    AddPropName("PositionVectorEvolutionFunctionType");
	
	AddPropName("NumAgentTypes");	
	
}

void CIoAgentArray::CreatePropArrayNames()
{
	AddArrayName("AgentArrayProperties");
}

void CIoAgentArray::CreatePropFlags()
{
	int iflagcfg = 7;
	int iflagsim = 7;
	int iflagboth = 7;

	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);
	AddPropFlag(iflagboth);


}

void CIoAgentArray::CreatePropArrayFlags()
{
	int iflagcfg = 2;
	int iflagsim = 1;
	int iflagboth = 7;

	AddArrayFlag(iflagboth);
}

void CIoAgentArray::CreateEPropNames()
{
	AddEPropName("Position");
	AddEPropName("AgentScalarParams");
	AddEPropName("AgentVectorParams");
}

void CIoAgentArray::CreateEPropArrayNames()
{
	AddEArrayName("AgentArrayProperties");
}

void CIoAgentArray::CreateEPropFlags()
{
	int iflagcfg = 7;
	int iflagsim = 7;
	int iflagboth = 7;

	AddEPropFlag(iflagcfg);
	AddEPropFlag(iflagcfg);
	AddEPropFlag(iflagcfg);
	/*AddEPropFlag(iflagboth);
	AddEPropFlag(iflagboth);
	AddEPropFlag(iflagboth);

*/
}

void CIoAgentArray::CreateEPropArrayFlags()
{
	int iflagcfg = 2;
	int iflagsim = 1;
	int iflagboth = 7;

	AddEArrayFlag(iflagboth);
}



void CIoAgentArray::CreateDefaultParams()
{
	int i;
	CreateProperties();
	CIoParam *pmodpars=m_pParentHandler->m_pProperties;
	
    vec *vmoddim=pmodpars->GetVecParam(IO_AGENTMODEL_MODELSIZE_VEC);
    AddVec(vmoddim);
    
    int iconfigtype=0;
    AddInt(iconfigtype);
    
    matrix mconfcreatepars(1,1,0,0);
    AddMat(&mconfcreatepars);

    vec varraypos(3,0);
    AddVec(&varraypos);
    
    char *sblank=NULL;
    
    //setting a single test property for
    //each scalar and vec property for E's and ET's
    IoStringArray saespnames("asp");//speed
    IoStringArray saevpnames("avp");//direction
    IoStringArray saetspnames("aetsntc");
    saetspnames.AddString("aetsnac");
    IoStringArray saetvpnames(sblank);
    
    AddStringArray(&saespnames);
    AddStringArray(&saevpnames);
    AddStringArray(&saetspnames);
    AddStringArray(&saetvpnames);
    
    IoStringArray saaspeqn("asp+s");
    IoStringArray saavpeqn("avp");
    IoStringArray saasfeqn("n+asp");
    saasfeqn.AddString("s");
    
    IoStringArray saavfeqn(sblank);
    
    AddStringArray(&saaspeqn);
    AddStringArray(&saavpeqn);
    AddStringArray(&saasfeqn);
    AddStringArray(&saavfeqn);
    AddString("pos+gradn*(aetsntc-aetsnac)");
   
    vec vaspeqnt(1,0);
    vec vavpeqnt(1,0);
    vec vasfeqnt(2,0);
    vec vavfeqnt(1,0);

	AddVec(&vaspeqnt);
	AddVec(&vavpeqnt);
	AddVec(&vasfeqnt);
	AddVec(&vavfeqnt);
	AddInt(0);
	AddInt(2);

	if(m_pEntityTypeSet) m_pEntityTypeSet->CreateDefaultParams();


}

int  CIoAgentArray::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=0;
	CIoParam *pmodpars=m_pParentHandler->m_pProperties;
	CIoEntityArray3d::Create(pParams);
	int id=GetID();
	vec *vt=m_pParentHandler->GetVec(IO_AGENTMODEL_NUMAGENTTYPES_VEC);
	SetInt(IO_AGENTARRAY_NUMTYPES_INT, vt->get(id));
	
	if(m_pEntityTypeSet==NULL) m_pEntityTypeSet=newEntityTypeSet("AgentTypeSet");
	m_pEntityTypeSet->Create(pChildParams);
	CreateFunctionHandlers(); //called via model create functions
	

	return status;
}

void CIoAgentArray::CreateConfig()
{
	vec *vnent=m_pParentHandler->GetVec(IO_AGENTMODEL_NUMAGENTS_VEC);
	vec *vmaxd=m_pParentHandler->GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
	int id=GetID();
	int nent=0;
	int fmax;
	int j,k;
	int tid,types=0;
	if(vnent && (id<(vnent->length())))
	   nent=vnent->get(id);
	   
	vnent=m_pParentHandler->GetVec(IO_AGENTMODEL_NUMAGENTTYPES_VEC);
	if(vnent && (id<(vnent->length())))
	   types=vnent->get(id);
	
	
	CIoAgent *pAg=NULL;
	CIoAgentType *pAgType=NULL;
	vec *vpos, *vsp;
	matrix *mvp;  
	for(int i=0; i<nent; i++)
	{
			pAg=(CIoAgent *)newEntity();
			tid=(rand()%types);
			
			pAgType=(CIoAgentType *)(m_pEntityTypeSet->GetEntityType(tid));
			if(pAg)
			{
				pAg->SetEntityType(pAgType);
				vpos=pAg->GetVec(IO_AGENT_POS_VEC);
				vsp=pAg->GetVec(IO_AGENT_SCAPROPS_VEC);
				mvp=pAg->GetMat(IO_AGENT_VECPROPS_MAT);
				
				
				//set agent pos
				for(j=0; j<3; j++)
				{
				   fmax=(int)(vmaxd->get(j));
				   vpos->set(j, (float)(rand()%fmax));	
				}
				
				//set agent scalar props
				for(j=0; j<vsp->length();j++)
				   vsp->set(j,(float)(rand()%100)/100);
				//set agent scalar props
				for(j=0; j<mvp->depth();j++)
					for(k=0; k<mvp->width();k++)				
				   		mvp->setval(j,k,(float)(rand()%100)/100);
				
				
				//set agent vector props			
			}
	}

}




	






void CIoAgentArray::setpos(int i1, int i2, int i3, vec *vpos)
{
	CIoAgent *pAgent=NULL;
	if(pAgent=(CIoAgent *)GetEntity(i1,i2,i3))
		pAgent->setpos(vpos);



}

vec *CIoAgentArray::getpos(int i1, int i2, int i3)
{
	vec *v=NULL;
	CIoAgent *pAgent=NULL;
	if(pAgent=(CIoAgent *)GetEntity(i1,i2,i3))
		v=pAgent->getpos();

	return v;
}


void CIoAgentArray::HandleInteractions()
{
	//Update the effective field experienced by
	//each moment
	int i1, i2, i3;
	//vec nbox=*(getarraydim());
	//setenergyzero();
	//First of use the modified external field
	//to update the local field
	//	for(i1 = 0; i1 < nbox [0]; i1++)
	//		for(i2 = 0; i2 < nbox [1]; i2++)
	//				for(i3 = 0; i3 < nbox [2]; i3++)
	//								;//calc_fieldenergy(i1, i2, i3);		


}










int CIoAgentArray::Update()
{
	int status=0;
	//Update the effective field experienced by
	//each moment
	int i1, i2, i3;
	float rmsmt, ei,ef;
	vec nbox=*(getarraydim());
	CIoAgent *pAgent=NULL;
	//First of use the modified external field
	//to update the local field
	//	for(i1 = 0; i1 < nbox [0]; i1++)
	//		for(i2 = 0; i2 < nbox [1]; i2++)
	//				for(i3 = 0; i3 < nbox [2]; i3++)
	//				{
	//					if(pAgent=(CIoAgent *)GetEntity(i1,i2,i3))
	//						;//pAgent->energymin(&rmsmt, &ei, &ef);
	//				}
		
	return status;
}

void CIoAgentArray::HandleStateTransitions()
{
	int nx,ny,nz;
	int i,j,k;
	
	nx=0;
	ny=0;
	nz=0;
	CIoAgent *pAgent;	
	int inum=GetNum();
	SetAllProps();
	
	for(i=0; i<inum; i++)
	{
		if(pAgent=(CIoAgent *)GetEntity(i))
		{
			m_pCurrentAgent=pAgent;
			SetEPosProp();
			SetScaEProps();
			SetVecEProps();
			SetScaETProps();
			SetVecETProps();
			
			//set variables
		    //Evaluate global scalar func
		    EvaluateScaPropFuncs();
		    EvaluateVecPropFuncs();
		    
		    EvaluateVecPosFunc();			
		}
	}


	for(i=0; i<inum; i++)
	{
		if(pAgent=(CIoAgent *)GetEntity(i))
		{
			m_pCurrentAgent=pAgent;
			//set variables
			SetScaEProps();
			SetVecEProps();
			SetScaETProps();
			SetVecETProps();
		    //Evaluate global scalar func
			EvaluateScaFieldFuncs();        	
			EvaluateVecFieldFuncs();
		}
	}    
}

vec *CIoAgentArray::GetPos(int iNum)
{
		vec *vPos=NULL;
		CIoAgent *pAgent=NULL;
		if(pAgent = (CIoAgent *)GetEntity(iNum))
							;
		return vPos;
}



float CIoAgentArray::GetEnergy(int iNum)
{

	float fenergy=0;
	CIoAgent *pAgent=NULL;
	if(pAgent = (CIoAgent *)GetEntity(iNum))
							;

	return fenergy;

}

int CIoAgentArray::CreateFunctionHandlers()
{
	int status=0;
	int tot=0;
	int stot=0; //stores number of variables
	int i,j,k;
	int itype=0;
	IoStringArray *saeqns=NULL;
	char *seqn, *sv1, *sv2, *svt1;
	CIoParam *pmodpars=m_pParentHandler->m_pProperties;
	string svpeqn;
	vec *v1=NULL,*v5=NULL;
	matrix *v2=NULL,*v6=NULL;
	mmat3d *v3=NULL,*v4=NULL;
	vec *vt1=NULL,*vt2=NULL,*vt3=NULL;
	vec *vt4=NULL,*vt5=NULL,*vt6=NULL;
		
	CIoEntity *pE=GetEntity(0);
	CIoEntityType *pET=GetEntityType(0);
	if(pE)
	{
		v1=pE->GetVec(IO_AGENT_SCAPROPS_VEC);
		v2=pE->GetMat(IO_AGENT_VECPROPS_MAT);
		vt1=GetVec(IO_AGENTARRAY_SCAAGENTPROPFUNCTYPE_VEC);
		vt2=GetVec(IO_AGENTARRAY_VECAGENTPROPFUNCTYPE_VEC);		
	}

	if(m_pParentHandler)
	{
		v3=m_pParentHandler->Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D);
		v4=m_pParentHandler->Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D);
		vt3=GetVec(IO_AGENTARRAY_SCAFFUNCTYPE_VEC);
		vt4=GetVec(IO_AGENTARRAY_VECFFUNCTYPE_VEC);		
	}
	
	if(pET)
	{
		v5=pET->GetVec(IO_AGENTTYPE_SCAPROPS_VEC);
		v6=pET->GetMat(IO_AGENTTYPE_VECPROPS_MAT);
	}
	

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
	//IO_AGENTARRAY_SCAAGENTENTITYPROPNAMES_STRARRAY
	if(ptsra=GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYPROPNAMES_STRARRAY))
		tot+=(n1=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTARRAY_VECAGENTENTITYPROPNAMES_STRARRAY))
		tot+=(n2=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYTYPEPROPNAMES_STRARRAY))
		tot+=(n5=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTARRAY_VECAGENTENTITYTYPEPROPNAMES_STRARRAY))
		tot+=(n6=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY))
		tot+=(n3=(ptsra->GetSize()));
	if(ptsra=GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY))
		tot+=(n4=(ptsra->GetSize()));	
	
	
	if(GetNumScaFieldEquations()>0)
		m_scafieldfparser=new FunctionParser[GetNumScaFieldEquations()];
	if(GetNumVecFieldEquations()>0)
		m_vecfieldfparser=new FunctionParser[GetNumVecFieldEquations()];
	if(GetNumScaAgentEntityPropEquations()>0)
		m_scaagentpropfparser=new FunctionParser[GetNumScaAgentEntityPropEquations()];
	if(GetNumVecAgentEntityPropEquations()>0)
		m_vecagentpropfparser=new FunctionParser[GetNumVecAgentEntityPropEquations()];
	

    //add 2 first is for time var second is position var
	m_vars1=new double[tot+2];	
	m_vars2=new double[tot+2];
	m_vars3=new double[tot+2];	
	m_vars=new double[tot+2];
	for(i=0; i<tot+2; i++) 
	{
		m_vars[i]=0;
		m_vars1[i]=0;		
		m_vars2[i]=0;
		m_vars3[i]=0;		
	}
	
	m_varinfo=new funcinputinfo [tot+2];
	
	m_vnames+="tt,rp,";
	m_varinfo[stot].field=0;
	m_varinfo[stot].dim=1;
	m_varinfo[stot].index=0;
	m_varinfo[stot].type=IO_AGENTMODEL_FLOATPROPS_VEC;
	
	stot++;
	
	m_varinfo[stot].field=0;
	m_varinfo[stot].dim=3;
	m_varinfo[stot].index=1;
	m_varinfo[stot].type=IO_AGENTMODEL_FLOATPROPS_VEC;
	
	stot++;	
	
	//read the list of variable names
	if(v1)
		for(i=0; i<(v1->length()); i++)
		{
		   //if(i !=0 ) m_vnames+=",";
		   
		  m_vnames+=(GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYPROPNAMES_STRARRAY)->GetsString(i));
		  if(i<(n1-1) ) m_vnames+=",";
		   m_varinfo[stot].field=0;
		   m_varinfo[stot].dim=1;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENT_SCAPROPS_VEC;
		   stot++;
		}

	if((n2)>0 ) m_vnames+=",";	

	if(v2)
		for(i=0; i<(v2->depth()); i++)
		{
		   //if(i !=0 ) m_vnames+=",";
		   m_vnames+=(GetStringArray(IO_AGENTARRAY_VECAGENTENTITYPROPNAMES_STRARRAY)->GetsString(i));
		  if(i<(n2-1) ) m_vnames+=",";
		   m_varinfo[stot].field=0;
		   m_varinfo[stot].dim=3;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENT_VECPROPS_MAT;
		   
		   stot++;
		}
	
	if((n3)>0 ) m_vnames+=",";	
	
		
	if(v3 && m_pParentHandler)
		for(i=0; i<(v3->mrows()); i++)
		{
		   //if(i !=0 ) m_vnames+=",";
		   m_vnames+=((m_pParentHandler->GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY))->GetsString(i));
		   if(i<(n3-1) ) m_vnames+=",";
		   m_varinfo[stot].field=1;
		   m_varinfo[stot].dim=1;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTMODEL_SCALARFIELDS_MMAT3D;
		   
		   stot++;
		}
	if((n4)>0 ) m_vnames+=",";	
		
	if(v4 && m_pParentHandler)
		for(i=0; i<(v4->mrows()); i++)
		{
		   //if(i !=0 ) m_vnames+=",";
		   m_vnames+=((m_pParentHandler->GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY))->GetsString(i));
		   if(i<(n4-1) ) m_vnames+=",";
		   
		   m_varinfo[stot].field=1;
		   m_varinfo[stot].dim=3;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTMODEL_VECFIELDS_MMAT3D;

		   stot++;
		}						
	if((n5)>0 ) m_vnames+=",";	
	
	if(v5)
		for(i=0; i<(v5->length()); i++)
		{
		   //if(i !=0 ) m_vnames+=",";
		   if(i <(n5-1) ) m_vnames+=",";
		   m_vnames+=(GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYTYPEPROPNAMES_STRARRAY)->GetsString(i));
		   m_varinfo[stot].field=2;
		   m_varinfo[stot].dim=1;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTTYPE_SCAPROPS_VEC;
		   stot++;
		}
		
	if((n6)>0 ) m_vnames+=",";	


	if(v6)
		for(i=0; i<(v6->depth()); i++)
		{
		   //if(i !=0 ) m_vnames+=",";
		   if(i <(n6-1) ) m_vnames+=",";
		   
		   m_vnames+=(GetStringArray(IO_AGENTARRAY_VECAGENTENTITYTYPEPROPNAMES_STRARRAY)->GetsString(i));
		   m_varinfo[stot].field=2;
		   m_varinfo[stot].dim=3;
		   m_varinfo[stot].index=i;
		   m_varinfo[stot].type=IO_AGENTTYPE_VECPROPS_MAT;
		   stot++;
		}

    std::cout << "The variables are: " << m_vnames << std::endl;
	//if the function is a dot or cross product or involves an ordered pair of vectors
	//then the functionis of the form vecname1,vecname2
	//ids for these vectors contained in the var info process this now
	//read the list of variable names
	for(j=2; j<stot; j++)
	{
	if(vt1)
	{
		saeqns=GetStringArray(IO_AGENTARRAY_SCAAGENTPROPFUNC_STRARRAY);
		for(i=0; i<(vt1->length()); i++)
		{
		
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt1->get(i);
		   if(saeqns && (itype==1))
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
		   else if((j==2) && saeqns && n1>0 )
		   {
		   	//parse the equation and set the variables
		   	sseqn=saeqns->GetsString(i);
		   	std::cout << "eqns " << *saeqns << std::endl;
		   	
		   	std::cout << "eqn "<< i <<sseqn <<" " << sseqn.length() <<  std::endl;
		   	if(sseqn.length()>0)
		   		m_scaagentpropfparser[i].Parse(sseqn,m_vnames);
		   }
		}
	}


	if(vt2)
	{
		saeqns=GetStringArray(IO_AGENTARRAY_VECAGENTPROPFUNC_STRARRAY);
		
	
		for(i=0; i<(vt2->length()); i++)
		{
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt2->get(i);
		   if(saeqns && (itype==1) )
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
		   else if((j==2) && saeqns && n2>0)
		   {
		   	//parse the equation and set the variables
		   	sseqn=saeqns->GetsString(i);
		   	//std::cout << "eqns " << *saeqns << std::endl;
		   	
		   	//std::cout << "eqn "<< i <<sseqn <<" " << sseqn.length() <<  std::endl;
		   	if(sseqn.length()>0)
		   		m_vecagentpropfparser[i].Parse(sseqn,m_vnames);
		   	
		   }
		}
	}
		
	if(vt3)
	{
		saeqns=GetStringArray(IO_AGENTARRAY_SCAFFUNC_STRARRAY);
		for(i=0; i<(vt3->length()); i++)
		{
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt3->get(i);
		   if(saeqns && (itype==1))
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
		   else if((j==2) && saeqns  && n3>0)
		   {
		   	//parse the equation and set the variables
		   	std::cout << "sf eqns \n" << *saeqns << std::endl;
		   	sseqn=saeqns->GetsString(i);
		   	
		   	std::cout << "sf eqn "<< i<< "\n" <<sseqn <<" length " << sseqn.length() <<  std::endl;
		   	if(sseqn.length()>0)		   	
		   		m_scafieldfparser[i].Parse(sseqn,m_vnames);
		   	
		   }		   

		}
	}
		
	if(vt4)
	{
		saeqns=GetStringArray(IO_AGENTARRAY_VECFFUNC_STRARRAY);
		
		for(i=0; i<(vt4->length()); i++)
		{
		   m_varinfo[j].id1=0;
		   m_varinfo[j].id2=0;
		   itype=vt4->get(i);
		   if(saeqns && (itype==1) )
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
		   else if((j==2) && saeqns && n4>0)
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
	
	//pos evo equation

	svpeqn=GetString(IO_AGENTARRAY_VECPOSFUNC_STRING);
		
		   m_varinfo[1].id1=0;
		   m_varinfo[1].id2=0;
		   itype=GetInt(IO_AGENTARRAY_VECAGENTPOSFUNCTYPE_INT);
		   if(itype==1)
		   {
		   	
		   	  //tokenize the equation
		   	  if((char *)svpeqn.c_str())
		   	  {
			   	  sv1=strtok(seqn,",");
			   	  sv2=strtok(NULL,",");
			   	  
			   	  svt1=strtok(((char *)m_vnames.c_str()),",");
			   	  for(k=2; k<stot; k++)
			   	  {
				   	  svt1=strtok(NULL,",");
				   	  if((strcmp(sv1,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[1].id1=k;
				   	  if((strcmp(sv2,svt1)==0) && (m_varinfo[k].dim==3))
				   	  		m_varinfo[1].id2=k;				   	  		
			   	  }
		   	  }
		   	
		   }
		   else
		   {
		   	//parse the equation and set the variables
		   	
		   	std::cout << "eqns " << svpeqn << std::endl;
		   	
		   	if(svpeqn.length()>0)
				m_vecposfparser.Parse(svpeqn,m_vnames);
		   	
		   }		   
		
	
	
	return status;	
	
}

void CIoAgentArray::ClearFunctionHandlers()
{
	
	FunctionParser *m_scafieldfparser;
	FunctionParser *m_vecfieldfparser;
	FunctionParser *m_scaagentpropfparser;
	FunctionParser *m_vecagentpropfparser;
	
	delete [] m_scafieldfparser;
	delete [] m_vecfieldfparser;
	delete [] m_scaagentpropfparser;
	delete [] m_vecagentpropfparser;
	
	m_vnames.clear();
	delete [] m_vars;
	delete [] m_vars1;
	delete [] m_vars2;  //variables used for vector manipulations vars1, vars2 and vars3 will be the vector at the current filed position
	delete [] m_vars3;
}




int CIoAgentArray::SetVars()
{
	int status=0;
	CIoParam *pmodpars=m_pParentHandler->m_pProperties;
	
	return status;	
}


int CIoAgentArray::GetVarAllIndex(int gindex, int dim, int type)
{
	int status=0;
	
	int tot=0;
	int stot=0;
	int i;
	int i1,i2,i3,i4,i5,i6;
	int index=0;
	i1=i2=i3=i4=i5=i6=0;
	CIoParam *pmodpars=m_pParentHandler->m_pProperties;
	
	IoStringArray *v1=GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYPROPNAMES_STRARRAY);
	IoStringArray *v2=GetStringArray(IO_AGENTARRAY_VECAGENTENTITYPROPNAMES_STRARRAY);
	IoStringArray *v3=m_pParentHandler->GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY);
	IoStringArray *v4=m_pParentHandler->GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY);
	IoStringArray *v5=GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYTYPEPROPNAMES_STRARRAY);
	IoStringArray *v6=GetStringArray(IO_AGENTARRAY_VECAGENTENTITYTYPEPROPNAMES_STRARRAY);
	
	
		
	if(v1) i1=(v1->GetSize());
	if(v2) i2=(v2->GetSize());
	if(v3) i3=(v3->GetSize());
	if(v4) i4=(v4->GetSize());
	if(v5) i5=(v5->GetSize());
	if(v6) i6=(v6->GetSize());
	
	if((dim==1) && (type==0))
				index=2+gindex;
	else if((dim==3) && (type==0))
				index=2+gindex+i1;
	else if((dim==1) && (type==1))
				index=2+gindex+i1+i2;
	else if((dim==3) && (type==1))
				index=2+gindex+i1+i2+i3;
	else if((dim==1) && (type==3))
				index=2+gindex+i1+i2+i3+i4;
	else if((dim==3) && (type==3))
				index=2+gindex+i1+i2+i3+i4+i5;
		
	return index;		
	
}



int CIoAgentArray::GetVarGroupIndex(int allvarindex)
{
	CIoParam *pmodpars=m_pParentHandler->m_pProperties;
	int tot=0;
	int stot=0;
	int i;
	int i1,i2,i3,i4,i5,i6;
	int index=0;
	i1=i2=i3=i4=i5=i6=0;
	
	IoStringArray *v1=GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYPROPNAMES_STRARRAY);
	IoStringArray *v2=GetStringArray(IO_AGENTARRAY_VECAGENTENTITYPROPNAMES_STRARRAY);
	IoStringArray *v3=m_pParentHandler->GetStringArray(IO_AGENTMODEL_SCAFIELDSNAMES_STRARRAY);
	IoStringArray *v4=m_pParentHandler->GetStringArray(IO_AGENTMODEL_VECFIELDSNAMES_STRARRAY);
	IoStringArray *v5=GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYTYPEPROPNAMES_STRARRAY);
	IoStringArray *v6=GetStringArray(IO_AGENTARRAY_VECAGENTENTITYTYPEPROPNAMES_STRARRAY);
		
	if(v1) i1=(v1->GetSize());
	if(v2) i2=(v2->GetSize());
	if(v3) i3=(v3->GetSize());
	if(v4) i4=(v4->GetSize());
	if(v5) i5=(v5->GetSize());
	if(v6) i6=(v6->GetSize());
	
	if(allvarindex < i1)
		index=allvarindex-2;
	else if(allvarindex < (i1+i2))		
		index=allvarindex-i1-2;
	else if(allvarindex < (i1+i2+i3))		
		index=allvarindex-i1-i2-2;	
	else if(allvarindex < (i1+i2+i3+i4))		
		index=allvarindex-i1-i2-i3-2;	
	else if(allvarindex < (i1+i2+i3+i4+i5))		
		index=allvarindex-i1-i2-i3-i4-2;	
	else if(allvarindex < (i1+i2+i3+i4+i5+i6))		
		index=allvarindex-i1-i2-i3-i4-i5-2;	
	
	return index;	
}

int CIoAgentArray::GetNumScaFieldEquations()
{
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_SCAFFUNC_STRARRAY);
	
	return(sa?sa->GetSize():0);
}
	
int CIoAgentArray::GetNumVecFieldEquations()
{
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_VECFFUNC_STRARRAY);
	
	return(sa?sa->GetSize():0);
}



int CIoAgentArray::GetNumScaAgentEntityPropEquations()
{
	
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYPROPNAMES_STRARRAY);
	return(sa?sa->GetSize():0);
}

int CIoAgentArray::GetNumVecAgentEntityPropEquations()
{
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_VECAGENTENTITYPROPNAMES_STRARRAY);
	
	return(sa?sa->GetSize():0);
}


int CIoAgentArray::GetNumScaFields()
{
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_SCAFFUNC_STRARRAY);
	
	return(sa?sa->GetSize():0);
}
	
int CIoAgentArray::GetNumVecFields()
{
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_VECFFUNC_STRARRAY);
	
	return(sa?sa->GetSize():0);
}



int CIoAgentArray::GetNumScaProps()
{
	
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_SCAAGENTENTITYPROPNAMES_STRARRAY);
	return(sa?sa->GetSize():0);
}

int CIoAgentArray::GetNumVecProps()
{
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_VECAGENTENTITYPROPNAMES_STRARRAY);
	
	return(sa?sa->GetSize():0);
}


string CIoAgentArray::GetScaFieldEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_SCAFFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;
}

string CIoAgentArray::GetVecFieldEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_VECFFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;
}




string CIoAgentArray::GetScaAgentEntityPropEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_SCAAGENTPROPFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;
}

string CIoAgentArray::GetVecAgentEntityPropEquation(int i)
{
	string svsc("");
	IoStringArray *sa=GetStringArray(IO_AGENTARRAY_VECAGENTPROPFUNC_STRARRAY);
	if(sa)
	  return sa->GetsString(i);
	
	return svsc;	
	
}


int CIoAgentArray::GetScaFieldEquationType(int i)
{
	vec *t;
	t=GetVec(IO_AGENTARRAY_SCAFFUNCTYPE_VEC);
	if(t && (i<GetNumScaFieldEquations()))
	  return (t->get(i));
	
	return 0;
}

int CIoAgentArray::GetVecFieldEquationType(int i)
{
	vec *t;
	t=GetVec(IO_AGENTARRAY_VECFFUNCTYPE_VEC);
	if(t && (i<GetNumVecFieldEquations()))
	  return (t->get(i));
	
	return 0;
}



int CIoAgentArray::GetScaPropEquationType(int i)
{
	vec *t;
	t=GetVec(IO_AGENTARRAY_SCAAGENTPROPFUNCTYPE_VEC);
	if(t  && (i<GetNumScaAgentEntityPropEquations()))
	  return (t->get(i));
	
	return 0;
}



int CIoAgentArray::GetVecPropEquationType(int i)
{
	vec *t;
	t=GetVec(IO_AGENTARRAY_VECAGENTPROPFUNCTYPE_VEC);
	if(t && (i<GetNumVecAgentEntityPropEquations()))
	  return (t->get(i));
	
	return 0;
	
}

int CIoAgentArray::SetAllProps()
{
	int status=0;
	Settprop();
	SetEPosProp();
	SetScaEProps();
	SetVecEProps();
	SetScaETProps();
	SetVecETProps();
	SetScaFieldProps();
	SetVecFieldProps();
		
	return status;	
}

int CIoAgentArray::Settprop()
{
	int status=0;
   	int is=m_pParentSimulant->GetCurrentStep();
	m_vars[0]=(double)is;
	m_vars1[0]=(double)is;
	m_vars2[0]=(double)is;
	m_vars3[0]=(double)is;
	
	return status;
}

int CIoAgentArray::SetScaEProps()
{
	int status=0;
		int i,j;
	vec *sv=NULL;
	vec *pos=NULL;
	//set values
	if(m_pCurrentAgent)
	{
		if(sv=(m_pCurrentAgent->GetVec(IO_AGENT_SCAPROPS_VEC)))
			for(i=0; i<GetNumScaProps();i++)
			{
				j=GetVarAllIndex(i,1,0);
				m_vars[j]=sv->get(i);
				m_vars1[j]=m_vars[j];
				m_vars2[j]=m_vars[j];
				m_vars3[j]=m_vars[j];
				
			}
	}
	else status=1;
	return status;	
}

int CIoAgentArray::SetEPosProp()
{
	int status=0;
	vec *pos=NULL;
	//set values
	if(m_pCurrentAgent && (pos=m_pCurrentAgent->GetVec(IO_AGENT_POS_VEC)))
	{
				m_vars[1]=pos->get(0);
				m_vars1[1]=pos->get(0);
				m_vars2[1]=pos->get(1);
				m_vars3[1]=pos->get(2);		
	}	
	return status;	
}	

int CIoAgentArray::SetVecEProps()
{
	int status=0;
		int i,j;
	matrix *sv=NULL;
	//set values
	if(m_pCurrentAgent)
	{
		if(sv=(m_pCurrentAgent->GetMat(IO_AGENT_VECPROPS_MAT)))
			for(i=0; i<GetNumVecProps();i++)
			{
				j=GetVarAllIndex(i,3,0);
				m_vars[j]=sv->getval(i,0);
				m_vars1[j]=sv->getval(i,0);
				m_vars2[j]=sv->getval(i,1);
				m_vars3[j]=sv->getval(i,2);				
			}
	}
	else status=1;
	return status;	
}



int CIoAgentArray::SetScaETProps()
{
	int status=0;
		int i,j;
	vec *sv=NULL;
	vec *pos=NULL;
	CIoAgentType *pType=NULL;
	//set values
	if(m_pCurrentAgent && (pType=(CIoAgentType *)(m_pCurrentAgent->GetEntityType())))
	{
		if(sv=(pType->GetVec(IO_AGENTTYPE_SCAPROPS_VEC)))
			for(i=0; i<(sv->length());i++)
			{
				j=GetVarAllIndex(i,1,3);
				m_vars[j]=sv->get(i);
				m_vars1[j]=m_vars[j];
				m_vars2[j]=m_vars[j];
				m_vars3[j]=m_vars[j];
				
			}
	}
	else status=1;
	return status;	
}



int CIoAgentArray::SetVecETProps()
{
	int status=0;
		int i,j;
	matrix *sv=NULL;
	CIoAgentType *pType=NULL;
	//set values
	if(m_pCurrentAgent && (pType=(CIoAgentType *)(m_pCurrentAgent->GetEntityType())))
	{
		if(sv=(pType->GetMat(IO_AGENTTYPE_VECPROPS_MAT)))
			for(i=0; i<(sv->depth());i++)
			{
				j=GetVarAllIndex(i,3,3);
				m_vars[j]=sv->getval(i,0);
				m_vars1[j]=sv->getval(i,0);
				m_vars2[j]=sv->getval(i,1);
				m_vars3[j]=sv->getval(i,2);
				
			}
	}
	else status=1;
	return status;
}



int CIoAgentArray::SetScaFieldProps(int i1, int i2, int i3)
{
	int status=0;
	int i,j;
	mmat3d *mm3d=NULL;
	//set values

	if(mm3d=(m_pParentHandler->Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D)))						
		for(i=0; i<GetNumScaFields();i++)
		{
			j=GetVarAllIndex(i,1,1);
			
			m_vars[j]=mm3d->getval(i1,i2,i3,i,0);
			m_vars1[j]=m_vars[j];
			m_vars2[j]=m_vars[j];
			m_vars3[j]=m_vars[j];						
		}
			
	return status;	
}



int CIoAgentArray::SetVecFieldProps(int i1, int i2, int i3)
{
	int status=0;
	int i,j;
	mmat3d *mm3d=NULL;
	//set values
	if(mm3d=(m_pParentHandler->Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D)))								
		for(i=0; i<GetNumVecFields();i++)
		{
			j=GetVarAllIndex(i,3,1);
			m_vars[j]=mm3d->getval(i1,i2,i3,i,0);
			m_vars1[j]=mm3d->getval(i1,i2,i3,i,0);
			m_vars2[j]=mm3d->getval(i1,i2,i3,i,1);
			m_vars3[j]=mm3d->getval(i1,i2,i3,i,2);						
									
		}	
	
	return status;
}







int CIoAgentArray::EvaluateScaPropFuncs()
{
	int status=0;
	int i,j;
	vec *sv=NULL;
	matrix *vm=NULL;
	mmat3d *mm3d=NULL;
	FunctionParser *scafparser=NULL;
	int nspe=GetNumScaAgentEntityPropEquations();
	float newval;
	vec *vetype=NULL;
	int etype=0;
			
	vetype=GetVec(IO_AGENTARRAY_SCAAGENTPROPFUNCTYPE_VEC);
	if((m_pCurrentAgent != NULL) && (sv=(m_pCurrentAgent->GetVec(IO_AGENT_SCAPROPS_VEC))))	
		for(i=0; i<nspe; i++)
		{
			etype=0;
			if(vetype && (i<vetype->length()))
			  etype=vetype->get(i);
			  
			switch(etype)
			{
				case 0:  //just apply the equation
					if(m_scaagentpropfparser)
						scafparser= &(m_scaagentpropfparser[i]);
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
				

				
				default : //just apply equation same as 1
					if(m_scaagentpropfparser)
						scafparser= &(m_scaagentpropfparser[i]);
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


int CIoAgentArray::EvaluateVecPropFuncs()
{
	int status=0;
	int i,j;
	vec *sv=NULL;
	matrix *vm=NULL;
	mmat3d *mm3d=NULL;
	FunctionParser *vecfparser=NULL;
	int nvpe=GetNumVecAgentEntityPropEquations();
	vec tvec(3,0); //test vec used for storing results of computations
	
	vec *vetype=NULL;
	int etype=0;
	vetype=GetVec(IO_AGENTARRAY_VECAGENTPROPFUNCTYPE_VEC);
	if((m_pCurrentAgent != NULL) && (vm=m_pCurrentAgent->GetMat(IO_AGENT_VECPROPS_MAT)))	
		for(i=0; i<nvpe; i++)
		{
			etype=0;
			if(vetype && (i<vetype->length()))
			  etype=vetype->get(i);
			  
			switch(etype)
			{
				case 0:  //just apply the equation
					if(m_vecagentpropfparser)
						vecfparser= &(m_vecagentpropfparser[i]);
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
				

				
				default : //just apply equation same as 1
					if(m_vecagentpropfparser)
						vecfparser= &(m_vecagentpropfparser[i]);
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

int CIoAgentArray::EvaluateVecPosFunc()
{
	int status=0;
	int i,j;
	vec *sv=NULL;
	mmat3d *mm3d=NULL;
	FunctionParser *vecfparser=NULL;
	int nvpe=GetNumVecAgentEntityPropEquations();
	vec tvec(3,0); //test vec used for storing results of computations
	vec *vm;
	int etype=GetInt(IO_AGENTARRAY_VECAGENTPOSFUNCTYPE_INT);
	if((m_pCurrentAgent != NULL) )
	{	

		  vm=m_pCurrentAgent->GetVec(IO_AGENT_POS_VEC);
			switch(etype)
			{
				case 0:  //just apply the equation
					if(m_vecagentpropfparser)
						vecfparser= &(m_vecposfparser);
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
				

				
				default : //just apply equation same as 1
					if(m_vecagentpropfparser)
						vecfparser= &(m_vecposfparser);
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
			vm->set(0,tvec.get(0));
			vm->set(1,tvec.get(1));
			vm->set(2,tvec.get(2));
					
	}						
		

	return status;	
	
	
}


int CIoAgentArray::EvaluateScaFieldFuncs()
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
	
	
	
	CIoParam *pmodpars=m_pParentHandler->m_pProperties;
	vec *vpos=NULL;
	int il[3];
	if(m_pCurrentAgent && (vpos=(m_pCurrentAgent->getpos())))
	{
		for(i=0; i<3; i++) il[i]=(int)(vpos->get(i));
		    //Evaluate global vec func
	     vec *vbox=m_pParentHandler->GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
	     vetype=GetVec(IO_AGENTARRAY_SCAFFUNCTYPE_VEC);
	     
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
		i1=il[0];
		i2=il[1];
		i3=il[2];
		 	if((mm3d=(m_pParentHandler->Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D)))  && (mm3dv = (m_pParentHandler->Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D))))	
		 	{
		 		//SetScaFieldProps(i1,i2,i3);
				//SetVecFieldProps(i1,i2,i3);
		 		
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
				
				for(i=0; i<GetNumScaFields();i++)
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
							     newval=sfparser->Eval(m_vars);					     
							}
							
							sfparser=NULL;				
						break;
						
					    //sca field func types (applies to intermediate field also)
					    //unit   0
						//dot   1

				
						
						case 1:  //scalar grad
							newval=Evalsp_dotprod(i);				
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
		
	}
		
	return status;	
}



int CIoAgentArray::EvaluateVecFieldFuncs()
{
	int status=0;
	CIoParam *pmodpars=m_pParentHandler->m_pProperties;
	vec *vpos=NULL;
	
	int i,j,k;
	int nx,ny,nz;
	int i1,i2,i3;
	vec *sv=NULL;
	matrix *vm=NULL;
	mmat3d *mm3d=NULL;
	mmat3d *mm3dv=NULL;
	FunctionParser *sfparser=NULL;
	int ne=GetNumScaFieldEquations();
	vec vresult(3,0);
	float newval;
	vec *vetype=NULL;
	int etype=0;
		
    //Evaluate global vec func
     vec *vbox=m_pParentHandler->GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
     vetype=GetVec(IO_AGENTARRAY_VECFFUNCTYPE_VEC);
	int il[3];
	if(m_pCurrentAgent && (vpos=(m_pCurrentAgent->getpos())))
	{
		for(i=0; i<3; i++) il[i]=(int)(vpos->get(i));
		if(vbox)
	     {
	     	nx=vbox->get(0);
	     	ny=vbox->get(1);	
	     	nz=vbox->get(2);	     		
	     }
	
	    i1=il[0];
		i2=il[1];
		i3=il[2];
	    //std::cout << "eval fields \n\n" << std::endl;
	    //std::cout << *Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D) << std::endl;
	    for(i=0; i<ne;i++)
		{
						//scalar values
						j=GetVarAllIndex(i,1,1);
						//std::cout << j << " " <<m_vars[j]<<" " << std::endl;
		}
		if(m_pParentHandler && (mm3d=(m_pParentHandler->Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D)))  && (mm3dv = (m_pParentHandler->Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D))))	
		 	{
		 		//SetScaFieldProps(i1,i2,i3);
				//SetVecFieldProps(i1,i2,i3);
		 		
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
				
				for(i=0; i<GetNumVecFields();i++)
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
								sfparser= &(m_vecfieldfparser[i]);
							if(sfparser)
							{
							     vresult.set(0, sfparser->Eval(m_vars1));					     
						     	 vresult.set(1, sfparser->Eval(m_vars2));					     
							     vresult.set(2, sfparser->Eval(m_vars3));					     
							}
							
							sfparser=NULL;				
						break;
						
					    //sca field func types (applies to intermediate field also)
					    //unit   0
						//cross   1  vector cross product
				
						
					
						case 1:  //dot 1
							Evalvp_crossprod(i,&vresult);				
						break;


						
						default : //just apply equation same as 1
							if(m_vecfieldfparser)
								sfparser= &(m_vecfieldfparser[i]);
							if(sfparser)
							{
							     //newval=vfparser->Eval(m_vars);
							     vresult.set(0, sfparser->Eval(m_vars1));					     
						     	 vresult.set(1, sfparser->Eval(m_vars2));					     
							     vresult.set(2, sfparser->Eval(m_vars3));					     
								     
							}					
							sfparser=NULL;								
						break;						
					}
					//update actual scalar
					//if(i<sv->length())
					//		sv->set(i,newval);
					//std::cout  << "vars " << newval << " " << m_vars[0] << " " << m_vars[1] << " "<< m_vars[2]<< "\n";
					//std::cout << i<< " "<< i1<< " " << i2<< " " << i3<< " "<<newval << " \n"; 
					for(j=0; j<3; j++)								
							mm3d->setval(i1,i2,i3,i,j,vresult[j]);
					
					//mm3d->setval(i1,i2,i3,i,0,newval);		
									
				}
				//for(i=0; i<ne; i++)								
				
		        	
        }//check for mm3d exists
		
		
		
		
		
	}


		
	return status;	
}

double CIoAgentArray::GetVecDotProd(int id1, int id2)
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

void CIoAgentArray::GetVecCrossProd(int id1, int id2, vec *result)
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


double CIoAgentArray::Evalsp_dotprod(int ieqn)
{
  double result;
  int i1 = m_varinfo [ieqn].id1;
  int i2 = m_varinfo [ieqn].id2; 
  
  result=GetVecDotProd(i1,i2); 
  return result;	
}

void CIoAgentArray::Evalvp_crossprod(int ieqn, vec *result)
{
	int i1 = m_varinfo [ieqn].id1;
	int i2 = m_varinfo [ieqn].id2;
	
	GetVecCrossProd(i1,i2,result);
	
}
