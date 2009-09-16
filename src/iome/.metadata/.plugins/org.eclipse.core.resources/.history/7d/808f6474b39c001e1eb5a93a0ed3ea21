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


#include "IoEntityArray3d.h"

CIoEntityArray3d::CIoEntityArray3d(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler):CIoEntitySet(pParentSimulation, pParentSimulant, pParentHandler)
{
	SetEntitySetName("EntityArray3d");
	SetEntitySetClass("EntityArray3d");

	CreateDefaultParams();
	m_idim[2]=m_idim[0]=m_idim[1]=5;
	//m_dim={5,5,5};

	m_iSize=125;
	m_iNum=0;

	//The default array size is 125 elements

	//for(int i=0; i<m_iSize; i++) m_pEntity [i]=NULL;
	m_ipbc=0;  //Default periodic boundary conditions off

}

CIoEntityArray3d::~CIoEntityArray3d(void)
{
		Delete3dArray();
		m_iNum=0;
		m_iSize=0;
}

/*!
	Creates a 3d array which is of fixed dimensions but may possess a variable number of entities
	warning any exisitng entities are destroyed by a call to create3d array
	The first parameter of the array must be the array dimensions

*/
void CIoEntityArray3d::Create3dArray(int size1, int size2, int size3)
{
	int i, j, k;
	int s1, s2, s3;
	EPtr2D *pE2D;
	EPtr1D *pE1D;
	EntityPtr pE=NULL;

	Delete3dArray();
	SetDimensions(size1, size2, size3);
	m_Entities.resize(m_idim[0]);
	/*m_Entities= *new EPtr3D(m_idim[0]);*/

	for(i=0; i<m_idim[0]; i++)
	{
		m_Entities[i].resize(m_idim[1]);
		/*pE2D=new EPtr2D(m_idim[1]);*/
		for( j=0; j<m_idim[1]; j++)
		{
			m_Entities[i][j].resize(m_idim[2]);
			/*pE1D=new EPtr1D(m_idim[2]);*/
			for(k=0; k<m_idim[2]; k++)
				m_Entities[i][j][k]=pE;
				/*pE1D->push_back(pE);*/
			
			//pE2D->push_back(*pE1D);
		}
		//m_Entities.push_back(*pE2D);
	}
	//The default array size is 100 elements

}

void CIoEntityArray3d::Delete3dArray()
{
	EPtr2D *pE2D;
	EPtr1D *pE1D;
	CIoEntity *pEntity=NULL;

	/*for(m_it3d=m_Entities.begin();m_it3d !=m_Entities.end(); m_it3d++ )
	{
		for(m_it2d=(*m_it3d).begin();m_it2d !=(*m_it3d).end(); m_it2d++ )
		{			
			(*m_it2d).clear();
			pE1D=&(*m_it2d);
			delete pE1D;
		}
		(*m_it3d).clear();
		pE2D=&(*m_it3d);
		delete pE2D;
	}*/
	m_Entities.clear();

	//Now clear the actual entites from the list

	EPtrList m_EList;
	for(m_itlist=m_EList.begin(); m_itlist !=m_EList.end(); m_itlist++)
		if(pEntity=(CIoEntity *)(*m_itlist))
					delete pEntity;
	m_EList.clear();

	

}

int CIoEntityArray3d::GetNum()
{
	return (m_iNum=m_EList.size());
}

void CIoEntityArray3d::SetDim(int size, int index)
{
	int i;
	if((index>=0) && index<3)
		if(size>0) m_idim[index]=size;
	else
		if(size>0) 
			for(i=0; i<3; i++) m_idim[i]=size; 

	m_iSize=(m_idim[0])*(m_idim[1])*(m_idim[2]);

}
/*!
	The first parameter of the array must be the array dimensions
*/
int CIoEntityArray3d::Create(CIoParam *pParams, CIoParam *pChildParams, CIoParam *pArray)
{
	int status=0;
	vec *vdim=NULL;

	status=CIoEntitySet::Create(pParams,pChildParams,pArray);
	if((m_pProperties->CheckParam(pParams))==1)
	{
		CreateProperties(pParams);
		if(vdim=GetVec(IO_ENTITYARRAY3D_DIMENSIONS_VEC))
			Create3dArray((int)vdim->get(0),(int)vdim->get(1),(int)vdim->get(2));
		else
			Create3dArray();
	}
	else 
	{
		//status=CIoEntitySet::Create();
		if(vdim=GetVec(IO_ENTITYARRAY3D_DIMENSIONS_VEC))
			Create3dArray((int)vdim->get(0),(int)vdim->get(1),(int)vdim->get(2));
		else
			Create3dArray();
	}

	return status;

}

/*!
	If an entity exists at the location of the new entity
	then that entity is deleted
*/
void CIoEntityArray3d::AddEntity(CIoEntity *pEntity)
{
 	int s1, s2, s3;
	int i,j,k;
	int index;
	vec *vpos=NULL;
	CIoEntity *pCurrentEntity=NULL;

	if(pEntity  && (vpos=pEntity->GetPos()) )
	{	
		
		
		s1=(int)(GetDim(0));
		s2=(int)(GetDim(1));
		s3=(int)(GetDim(2));

		i=(int)(vpos->get(0));
		j=(int)(vpos->get(1));
		k=(int)(vpos->get(2));

		//Check that positions for the entity are correct
		if((i>=0) && (j>=0) && (k>=0) && (i<s1) && (j<s2) && (k<s3) )
		{

			if(pCurrentEntity=GetEntity(i,j,k))
						DeleteEntity(pCurrentEntity);
			
			//m_pPreviousEntity
			m_EList.push_back(pEntity);

			
			m_Entities[i][j][k]=pEntity;
			m_iNum ++;
		}
	}
		


}

int CIoEntityArray3d::GetEntityIndex(int f1, int f2, int f3)
{
	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	return GetEntityIndex(pEntity);
}

int CIoEntityArray3d::GetEntityIndex(CIoEntity *pEntity)
{
	int index=-1, icount=0;
	for(m_itlist=m_EList.begin(), icount=0; m_itlist != m_EList.end(),icount<=GetNum(); m_itlist++,icount++)
		if(	pEntity==(CIoEntity *)(*m_itlist))
									return icount;

	return index;
}


CIoEntity *CIoEntityArray3d::GetEntity(int iIndex)
{
	CIoEntity *pCurrentEntity=NULL;
	CIoEntity *pEntity=pCurrentEntity;;
	int icount=0;
	if(iIndex>=0 && iIndex<GetNum())
	{
		for(m_itlist=m_EList.begin(), icount=0; m_itlist != m_EList.end(),icount<=iIndex; m_itlist++,icount++)
			pEntity=(CIoEntity *)(*m_itlist);
	}
	return pEntity;
}













void CIoEntityArray3d::SetDimensions(int f1, int f2, int f3)
{
	SetDim(f1, 0);
	SetDim(f2,1);
	SetDim(f3,2);


}

CIoEntity *CIoEntityArray3d::GetEntity(int f1, int f2, int f3)
{
	if(f1>=0 && f1<GetDim(0) && f2>=0 && f2<GetDim(1) && f3>=0 && f3<GetDim(2))
	{
		if(m_Entities.size()>0)
			//m_Entities.at(
			return m_Entities[f1][f2][f3];
		else
			return NULL;
	}
	else
		return NULL;
}

int CIoEntityArray3d::DeleteEntity(CIoEntity *pEntity)
{
	int status=0;
	CIoEntity *pREntity=NULL;
	if(pREntity=RemoveEntity(pEntity))
		delete pREntity;
	return status;

}






CIoEntity *CIoEntityArray3d::RemoveEntity(CIoEntity *pEntity)
{
	
	CIoEntity *pCurrentEntity=NULL;
	int s1, s2, s3;
	int i,j,k;
	int index;
	vec *vdim, *vpos;

	vec vnewpos(3,0);
	
	s1=(int)(GetDim(0));
	s2=(int)(GetDim(1));
	s3=(int)(GetDim(2));

	if(pEntity && (vpos=pEntity->GetPos()))
	{
	i=(int)(vpos->get(0));
	j=(int)(vpos->get(1));
	k=(int)(vpos->get(2));

	if((i>=0) && (j>=0) && (k>=0) && (i<s1) && (j<s2) && (k<s3 ))
	{
		if((pCurrentEntity=GetEntity(i,j,k))&& (pCurrentEntity==pEntity))
		{
			//Entity located at correct location so remove it
			m_Entities[i][j][k]=NULL;
			m_EList.remove(pEntity);
			m_iNum--;
			return  pCurrentEntity;

		}
		else
		{
			//Search for entity in the array then remove it
			if(!GetEntityPos(pEntity,  &vnewpos))
			{
					m_Entities[(int)(vnewpos.get(0))][(int)(vnewpos.get(1))][(int)(vnewpos.get(2))]=NULL;
					m_EList.remove(pEntity);
					m_iNum--;
					return pEntity;

			}


		}


	}
	}
	return NULL;
}

int CIoEntityArray3d::GetEntityPos(CIoEntity *pEntity, vec *vpos)
{
	int status=0;
	CIoEntity *pREntity=NULL;
	CIoEntity *pCurrentEntity=NULL;
	CIoEntity *pTestEntity=NULL;
	int s1, s2, s3;
	int i,j,k;
	int l,m,n;
	int ll;
	int index;
	vec *vdim, *acpos;
	
	s1=(int)(GetDim(0));
	s2=(int)(GetDim(1));
	s3=(int)(GetDim(2));

	if(vpos && ((vpos->length())>=3) && pEntity && (acpos=pEntity->GetPos()))
	{

		i=(int)(acpos->get(0));
		j=(int)(acpos->get(1));
		k=(int)(acpos->get(2));

		if((i>=0) && (j>=0) && (k>=0) && (i<s1) && (j<s2) && (k<s3 ))
		{
			if((pCurrentEntity=GetEntity(i,j,k)) && (pCurrentEntity==pEntity))
			{
				//Entity located at correct location so remove it
				for(ll=0; ll<3; ll++)
					vpos->set(ll, acpos->get(ll));

				return status;

			}
			else
			{
				//Search for entity in the array then remove it
				for(m_it3d=m_Entities.begin(),l=0;m_it3d !=m_Entities.end(); m_it3d++ ,l++)
				{
					for(m_it2d=(*m_it3d).begin(),m=0;m_it2d !=(*m_it3d).end(); m_it2d++,m++ )
					{	
						for(m_it1d=(*m_it2d).begin(),n=0;m_it1d !=(*m_it2d).end(); m_it1d++,n++ )
						{			

							if((pTestEntity=(CIoEntity *)(*m_it1d)) && (pTestEntity==pEntity))
							{
								for(ll=0; ll<3; ll++)
									vpos->set(ll, (float)(l*(ll==0)+m*(ll=1)+n*(ll=2)));
								return status;

							}

						}
					}
				}
				//Loop got to here so entity not found
				status=1;

			}//check for entity at correct location


		}//conditions on entity pos
	}//entity position check





	return status;

}


/*!
Returns pointers to the 6 entities at the 6 nearest neighbour locations
*/
void CIoEntityArray3d::GetNN6(int i1, int i2, int i3, VectorEPtr *pEVec){;}

/*!
Returns pointers to the 12 entities at the 12 next nearest neighbour locations
*/
void CIoEntityArray3d::GetNNN12(int i1, int i2, int i3, VectorEPtr *pEVec){;}

/*!
Returns pointers to the 8 entities at the 8 next next nearest neighbour locations
*/
void CIoEntityArray3d::GetNNNN8(int i1, int i2, int i3, VectorEPtr *pEVec){;}



void CIoEntityArray3d::SetEntityInt(int f1, int f2, int f3, int paramindex, int ival)
{
	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	if(pEntity)
		pEntity->SetInt(paramindex, ival);
}

int CIoEntityArray3d::GetEntityInt(int f1, int f2, int f3, int paramindex)
{
	int ival=0;
	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	if(pEntity)
		ival=pEntity->GetInt(paramindex);

	return ival;
}

void CIoEntityArray3d::SetEntityFloat(int f1, int f2, int f3, int paramindex, float fval)
{
	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	if(pEntity)
		pEntity->SetFloat(paramindex, fval);

}




float CIoEntityArray3d::GetEntityFloat(int f1, int f2, int f3, int paramindex)
{
	float fval=0;
	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	if(pEntity)
		fval=pEntity->GetFloat(paramindex);

	return fval;
}

void CIoEntityArray3d::SetEntityString(int f1, int f2, int f3, int paramindex, char *sstring)
{
	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	if(pEntity)
		pEntity->SetString(paramindex, sstring);
}

char *CIoEntityArray3d::GetEntityString(int f1, int f2, int f3, int paramindex)
{
	char *sval=NULL;
	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	if(pEntity)
		sval=pEntity->GetString(paramindex);

	return sval;
}

void CIoEntityArray3d::SetEntityVec(int f1, int f2, int f3, int paramindex, vec *vvec)
{
	
	if(CIoEntity *pEntity=GetEntity(f1,f2,f3))
		pEntity->SetVec(paramindex, vvec);
}

vec *CIoEntityArray3d::GetEntityVec(int f1, int f2, int f3, int paramindex)
{
	vec *mval=NULL;

	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	if(pEntity)
		mval=pEntity->GetVec(paramindex);

	return mval;
}

void CIoEntityArray3d::SetEntityMat(int f1, int f2, int f3, int paramindex, matrix *mmat)
{
	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	if(pEntity)
		pEntity->SetMat(paramindex, mmat);
}

matrix *CIoEntityArray3d::GetEntityMat(int f1, int f2, int f3, int paramindex)
{
	matrix *mval=NULL;

	CIoEntity *pEntity=GetEntity(f1,f2,f3);
	if(pEntity)
		mval=pEntity->GetMat(paramindex);

	return mval;

}
/*!
Iterates over the entities and updates their state
*/
void CIoEntityArray3d::HandleStateTransitions()
{
	int i, j, k;
	int s1, s2, s3;
	vec *vdim;
	CIoEntity *pEntity;
	//The default array size is 100 elements
		s1=GetDim(0);
		s2=GetDim(1);
		s3=GetDim(2);

		for(i=0; i<s1; i++)
				for(j=0; j<s2; j++)
						for(k=0; k<s3; k++)
						{
							if(pEntity=GetEntity(i,j,k))
								pEntity->HandleStateTransitions();
						}
	


	CIoEntitySet::HandleStateTransitions();



}





