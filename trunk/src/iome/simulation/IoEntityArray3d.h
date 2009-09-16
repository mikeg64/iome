#ifndef IO_SIMULATION_ENTITYARRAY3D_H
#define IO_SIMULATION_ENTITYARRAY3D_H
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
#include <iome/simulation/IoEntitySet.h>

/*!
	The newEntitySet method (called by CIoSimulator or CIoModel)
	must set the correct the array 

	The entity must have a GetPos() method returning a location
	vector of the object which must be the same as the location 
	in the array of the entity

	A position must be defined for the entity before it can be
	added to the array
*/
/*!
	This class tests the ability of a derived class
	(i.e. one dervide from CIoEntityArray3d) to use
	the parameters of this object

	The following methods for the derived class
	virtual void CreateDefaultParams();
	virtual void CreatePropNames();
	virtual void CreatePropArrayNames();
	virtual void CreatePropFlags();
	virtual void CreatePropArrayFlags();

	Must make the follwing call in each method
	CIoEntitySetOct::CreateDefaultParams();
	CIoEntitySetOct::CreatePropNames();
	CIoEntitySetOct::CreatePropArrayNames();
	CIoEntitySetOct::CreatePropFlags();
	CIoEntitySetOct::CreatePropArrayFlags();

	Note that each of these methods must not create
	the new IoParam object but in each case add the new
	flags, names and parameters to the property.
*/

//#include <vector>
// To much work!!
//std::vector < std::vector <std::vector <int> > >
//m(3,std::vector< std::vector<int> >(4, std::vector<int>(4,0)));

// Easier to maintain
//typedef std::vector<int> Int1D;
//typedef std::vector<Int1D> Int2D;
//typedef std::vector<Int2D> Int3D;

//int main()
//{
//   Int3D My3DArray(10, Int2D(10, Int1D(10,0)));
//}

//The reason for the typedefs is that, at some point, you may need an iterator. When you define the iterator, what's easier?

//std::vector< std::vector< std::vector<int> > >::iterator it;
//or

//Int3D::iterator it;
#include <vector>
#include <list>
// To much work!!
//std::vector < std::vector <std::vector <int> > >
//m(3,std::vector< std::vector<int> >(4, std::vector<int>(4,0)));

// Easier to maintain
using std::vector;
using std::list;

typedef vector<EntityPtr > EPtr1D;
typedef vector<EPtr1D> EPtr2D;
typedef vector<EPtr2D> EPtr3D;




#define IO_ENTITYARRAY3D_DIMENSIONS_VEC 0

class CIoEntityArray3d :
	public CIoEntitySet
{
public:
	CIoEntityArray3d(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	~CIoEntityArray3d(void);

	int DeleteEntity(CIoEntity *pEntity);
	virtual CIoEntity *GetEntity(int iEntityIndex);
	CIoEntity *GetEntity(int f1, int f2, int f3);
	int GetEntityIndex(int f1, int f2, int f3);
	int GetEntityIndex(CIoEntity *pEntity);
	CIoEntity *SetEntity(CIoEntity *pEntity, int f1, int f2, int f3){return NULL;}

	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);
	
	virtual void AddEntity(CIoEntity *pEntity);
	virtual int GetNum();
	int GetSize(){return m_iSize;}
	CIoEntity *RemoveEntity(CIoEntity *pEntity);
	int GetEntityPos(CIoEntity *pEntity, vec *vpos);
	CIoEntity *UnSetEntity(CIoEntity *pEntity, int f1, int f2, int f3){return NULL;}
	virtual CIoEntity *newEntity(){return NULL;}



	void SetDimensions(int f1, int f2, int f3);
	virtual void Create3dArray(int size1=5, int size2=5, int size3=5);
	void Delete3dArray();


	EPtr3D m_Entities;
	EPtrList m_EList;
	EPtr3D::iterator m_it3d;
	EPtr2D::iterator m_it2d;
	EPtr1D::iterator m_it1d;

	EPtrList::iterator m_itlist;

	EntityPtr operator()(int i, int j, int k){return GetEntity(i,j,k);}
	EntityPtr operator()(int i){return GetEntity(i);}

	unsigned short int m_ipbc;  //Periodic boundary conditions
	int m_idim[3];
	void SetDim(int size, int index=-1);
	int GetDim(int index=0){return((index>=0 && index<3)?m_idim[index]:0);}


	//Setting and getting PBC's
	unsigned short int GetPBC(){return m_ipbc;}
	unsigned short int PBCOn(){return(m_ipbc=1);}
	unsigned short int PBCOff(){return(m_ipbc=0);}

	/*!
	Returns pointers to the 6 entities at the 6 nearest neighbour locations
	*/
	void GetNN6(int i1, int i2, int i3, VectorEPtr *pEVec);

	/*!
	Returns pointers to the 12 entities at the 12 next nearest neighbour locations
	*/
	void GetNNN12(int i1, int i2, int i3, VectorEPtr *pEVec);

	/*!
	Returns pointers to the 8 entities at the 8 next next nearest neighbour locations
	*/
	void GetNNNN8(int i1, int i2, int i3, VectorEPtr *pEVec);



	/*! The following should be inline!*/
	void SetEntityInt(int f1, int f2, int f3, int paramindex, int ival);
	int GetEntityInt(int f1, int f2, int f3, int paramindex);
	void SetEntityFloat(int f1, int f2, int f3, int paramindex, float fval);
	float GetEntityFloat(int f1, int f2, int f3, int paramindex);
	void SetEntityString(int f1, int f2, int f3, int paramindex, char *sstring);
	char *GetEntityString(int f1, int f2, int f3, int paramindex);
	void SetEntityVec(int f1, int f2, int f3, int paramindex, vec *vvec);
	vec *GetEntityVec(int f1, int f2, int f3, int paramindex);
	void SetEntityMat(int f1, int f2, int f3, int paramindex, matrix *mmat);
	matrix *GetEntityMat(int f1, int f2, int f3, int paramindex);

	void HandleStateTransitions();
};

#endif

