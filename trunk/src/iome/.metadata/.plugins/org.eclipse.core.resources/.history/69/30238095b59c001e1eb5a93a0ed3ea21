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


// IoOctNode.cpp: implementation of the CIoOctNode class.
//
//////////////////////////////////////////////////////////////////////


#include "IoOctNode.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoOctNode::CIoOctNode()
{
	int i,j,k;
	
	m_iNumEntity=0;
	m_iMinNumEntity=5;
	m_iMaxLevelRecurse=0;


	//2x2x2 Array of octants for this node
	
	for(i=0; i<2; i++)
		for(j=0; j<2; j++)
			for(k=0; k<2; k++)
				m_pOctant [i] [j] [k] = NULL;

	// Bounds for the octant
	float m_pFmaxd[3];
	float m_pFmind[3];
	//Location of Octant
	float m_pFloc[3];
	for(i=0; i<3; i++)
	{
		m_pFmaxd [i] = 200;
		m_pFmind [i] = -200;
		m_pFloc[i] = 0.5*(m_pFmaxd[i] + m_pFmind[i]);

	}

	m_bAddToOctants=0;
	m_bIsRootNode=1;

}

CIoOctNode::~CIoOctNode()
{
	int i, j, k;
	for(i=0; i<2; i++)
			for(j=0; j<2; j++)
					for(k=0; k<2; k++)
						if(m_pOctant [i] [j] [k])
							delete m_pOctant [i] [j] [k];


}

void CIoOctNode::SetBounds(vec *vmaxd, vec *vmind)
{

	float fOmaxd [3];
	float fOmind [3];
	float maxd [3];
	float mind [3];
	vec vmax(3, 0);
	vec vmin(3, 0);
	int i1, i, j, k;
	for(i=0; i<3; i++)
	{
		if(maxd)
			maxd [1]=vmaxd->get(i);
		if(mind)
			mind [1]=vmind->get(i);
	}

    int set=1;

	for(i=0; i<3; i++)
		if(maxd [i]<mind [i])
						set = 0;

	if(set)
	{
	for(i=0; i<2; i++)
			for(j=0; j<2; j++)
					for(k=0; k<2; k++)
						if(m_pOctant [i] [j] [k])
						{
							fOmaxd [0] = (i==0? 0.5*(maxd [0]-mind[0]):maxd[0]);
							fOmind [0] = (i==0? mind [0] : 0.5*(maxd [0]-mind[0]));

							fOmaxd [1] = (j==0? 0.5*(maxd [1]-mind[1]):maxd[1]);
							fOmind [1] = (j==0? mind [1] : 0.5*(maxd [1]-mind[1]));

							fOmaxd [2] = (k==0? 0.5*(maxd [2]-mind[2]):maxd[2]);
							fOmind [2] = (k==0? mind [2] : 0.5*(maxd [2]-mind[2]));

							for(i1=0; i1<3; i1++)
							{
								vmax.set(i, fOmaxd [i]);
								vmin.set(i, fOmind [i]);
							}

							m_pOctant [i] [j] [k]->SetBounds(&vmax, &vmin);
						}
		//Now set bounds for this octant
		for(i=0; i<3; i++)
		{
			m_pFmaxd [i] = maxd [i];
			m_pFmind [i] = mind [i];
			m_pFloc [i] = 0.5*(maxd [i] + mind [i]);
		}
	}

}

void CIoOctNode::SetMinNumEntity(int iMinNumEntity)
{
	int i, j, k;
	if(iMinNumEntity>0)
	{
		for(i=0; i<2; i++)
				for(j=0; j<2; j++)
						for(k=0; k<2; k++)
							if(m_pOctant [i] [j] [k])
								m_pOctant [i] [j] [k]->SetMinNumEntity(iMinNumEntity);

		m_iMinNumEntity = iMinNumEntity;
	}

}

void CIoOctNode::SetMaxLevelRecurse(int iMaxLevelRecurse)
{
	int i,j,k;
	if(iMaxLevelRecurse>=0)
	{

		for(i=0; i<2; i++)
				for(j=0; j<2; j++)
						for(k=0; k<2; k++)
							if(m_pOctant [i] [j] [k])
								(m_pOctant [i] [j] [k]->m_iMaxLevelRecurse)=(iMaxLevelRecurse-1);

		m_iMaxLevelRecurse = iMaxLevelRecurse;

	}

}

void CIoOctNode::AddEntity(CIoEntity *pEntity)
{
	CIoEntity *pTempEntity, *pCurrentEntity;
	/*vec *pos;
	int i,j,k;
	int set=0;

	if(pEntity && m_bIsRootNode)
	{

		//Check that the bounds are set correctly
		pos = pEntity->GetPos();
		for(i=0; i<3; i++)
		{
			if((m_pFmaxd [i] < pos->get(i)))
			{
				m_pFmaxd [i] = pos->get(i);
				set = 1;
			}
			if((m_pFmind [i] > pos->get(i)))
			{
				m_pFmind [i] = pos->get(i);
				set = 1;
			}
		}
		if(set) SetBounds(m_pFmaxd, m_pFmind);

	}
    
	//If the node is  a leaf node
	//we can add the object to this node
	if(!m_bAddToOctants)
	{
		if(m_pEntityList)
		{
		  if(pEntity)
		  {
			pTempEntity = m_pEntityList;
			m_pEntityList = pEntity;
			m_pEntityList->SetNextEntity(pTempEntity);
			m_iNumEntity++;
		  }
		}
		else
		{
			m_pEntityList = pEntity;
			m_pEntityList->SetNextEntity(NULL);
			m_iNumEntity++;
		}

		//Check if we need to move the objects to the next level
		if(m_iNumEntity>m_iMinNumEntity && m_iMaxLevelRecurse>0)
												MoveEntityToOctants();

	}
	else
	{
		//Determine the node to add the object to
		pos=pEntity->GetPos();
		i=((pos->get(0))>(m_pFloc [0]));
		j=((pos->get(1))>(m_pFloc [1]));
		k=((pos->get(2))>(m_pFloc [2]));

		//Check that the octant is created
		if(!(m_pOctant [i] [j] [k]))
		{
			m_pOctant [i] [j] [k] = new CIoOctNode;
			m_pOctant [i] [j] [k]->m_bIsRootNode = false;
			m_pOctant [i] [j] [k]->SetMaxLevelRecurse(m_iMaxLevelRecurse-1);
			m_pOctant [i] [j] [k]->SetMinNumEntity(m_iMinNumEntity);
			SetBounds(m_pFmaxd, m_pFmind);
		}

		m_pOctant [i] [j] [k]->AddEntity(pEntity);
	}*/

}

void CIoOctNode::MoveEntityToOctants(CIoEntityList *pEntityList)
{
	/*CIoEntity *pCurrentEntity=m_pEntityList;
	vec *pos;
	int i,j,k;

    if(pCurrentEntity)
	{
	//Check if we need to create the Octants
		for(i=0; i<2; i++)
				for(j=0; j<2; j++)
						for(k=0; k<2; k++)
							if(m_pOctant [i] [j] [k]==NULL)
							{
								m_pOctant [i] [j] [k] = new CIoOctNode;
								m_pOctant [i] [j] [k]->m_bIsRootNode = false;
								m_pOctant [i] [j] [k]->SetMaxLevelRecurse(m_iMaxLevelRecurse-1);
								m_pOctant [i] [j] [k]->SetMinNumEntity(m_iMinNumEntity);
							}
		//Remember nodes are leaf nodes by default

		//Ensure that octants set with the correct
		//properties
		SetBounds(m_pFmaxd, m_pFmind);
		while(pCurrentEntity)
		{
			pos=pCurrentEntity->GetPos();
			i=((pos->get(0))>(m_pFloc [0]));
			j=((pos->get(1))>(m_pFloc [1]));
			k=((pos->get(2))>(m_pFloc [2]));

			m_pOctant [i] [j] [k]->AddEntity(pCurrentEntity);
			pCurrentEntity = pCurrentEntity->GetNextEntity();



		}

		m_pEntityList=NULL;
		m_iNumEntity =0;
		m_bAddToOctants=true;

	}*/


}

void CIoOctNode::MoveEntityOctToList(CIoEntityList *pEntityList, ENTITY_LIST *m_plParentEntityList )
{

	int i,j,k;
	


	/*if(m_pEntityList )
	{

		//Don't nee to walk the list of octants because this is the leaf node

	


		pEntityList->GetNum();

		pParentEntityList->InsertEntityList(pEntityList);

        //Remove the list from this node
		m_pEntityList = NULL;
		m_iNumEntity=0;


	}
	else
	{
		//Traverse the list of octants 
		for(i=0; i<2; i++)
			for(j=0; j<2; j++)
				for(k=0; k<2; k++)
					if(m_pOctant [i] [j] [k])
					{
						m_pOctant [i] [j] [k]->MoveEntityOctToList(pParentEntityList);
						//If the octant is empty and it is a leaf node delete it
						if(m_pOctant [i] [j] [k]->m_bAddToOctants)
						{
							delete m_pOctant [i] [j] [k];
							m_pOctant [i] [j] [k] = NULL;
						}
					}


	}*/


}

void RemoveEntity(CIoEntity *pEntity)
{


}

CIoEntity *GetEntity(vec *vpos)
{
	CIoEntity *pEntity=NULL;

	return pEntity;
}