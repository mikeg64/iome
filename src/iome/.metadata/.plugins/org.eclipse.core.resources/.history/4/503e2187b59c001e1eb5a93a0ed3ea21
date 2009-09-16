#ifndef IO_SIMULATION_OCTNODE_H
#define IO_SIMULATION_OCTNODE_H

// IoOctNode.h: interface for the CIoOctNode class.
//
//////////////////////////////////////////////////////////////////////
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

#include "IoEntityList.h"

class CIoOctNode  
{
public:
	CIoOctNode();
	virtual ~CIoOctNode();

	void SetBounds(vec *maxd, vec *mind);
	void SetMinNumEntity(int iMinNumEntity);
	void SetMaxLevelRecurse(int iMaxLevelRecurse);

	void AddEntity(CIoEntity *pEntity);
	void RemoveEntity(CIoEntity *pEntity);
	void GetEntity(vec *vpos);
	//Move a list of entites to octants
	void MoveEntityToOctants(CIoEntityList *pEntityList);
	//Move entities in oct tree to a list
	void MoveEntityOctToList(CIoEntityList *pEntityList, ENTITY_LIST *m_plParentEntityList=NULL);
	virtual int GetNum(){return((int) m_lEntityList.size());}

	int m_iNumEntity;
	int m_iMinNumEntity;
	int m_iMaxLevelRecurse;

	ENTITY_LIST m_lEntityList;
	ENTITY_LIST::iterator m_lEntityIterator;
	ENTITY_LIST::size_type m_size;

	//2x2x2 Array of octants for this node
	CIoOctNode *m_pOctant [2] [2] [2];

	// Bounds for the octant
	float m_pFmaxd[3];
	float m_pFmind[3];
	//Location of Octant
	float m_pFloc[3];

	//Entity only get placed in leaf nodes
	//if this flag is false the node is a leaf node 
	int m_bAddToOctants;
	int m_bIsRootNode;

};

#endif


