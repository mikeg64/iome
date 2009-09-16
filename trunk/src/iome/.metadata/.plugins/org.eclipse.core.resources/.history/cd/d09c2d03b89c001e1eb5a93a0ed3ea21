#ifndef IO_SIMULATION_SIMULATOR_H
#define IO_SIMULATION_SIMULATOR_H
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
// IoSimulator.h: interface for the CIoSimulator class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_IOSIMULATOR_H__01291E7A_CC9A_4907_B34A_FBE3FCC6803A__INCLUDED_)
//#define AFX_IOSIMULATOR_H__01291E7A_CC9A_4907_B34A_FBE3FCC6803A__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#include "IoSimulant.h"
#include "CIoSimulantLink.h"
#include "IoModel.h"
//#include "IoSimulation.h"
#ifndef IO_MSVC
	#include "../IoUtils/IoParams.h"
#else
	#include "..\IoUtils\IoParams.h"
#endif
using std::deque;
typedef CIoSimulantLink * SIMULANTLINKPTR;
typedef deque<SIMULANTLINKPTR> dqslptr;

//The default case is that where the simulator has only one child which is a CIoModel
//this will be the case for most simulations
//Will probably be most use for dicrete event cell models (CELL DEVS)

class CIoSimulator : public CIoSimulant  
{
public:
	CIoSimulator(CIoSimulation *pParentSimulation=NULL,
	CIoSimulant *pParentSimulant=NULL,
	CIoSimHandler *pParentHandler=NULL);
	virtual ~CIoSimulator();



    CIoSimulant *m_pSimulant;
	char *m_sSimulatorName;
	char *m_sSimulatorClass;
	
	deque<SIMULANTLINKPTR> m_pLinks;
	
	dqslptr &Getlinks(){return m_pLinks;}
	int GetNumLinks(){return (m_pLinks.size());}
	
	CIoSimulantLink *GetLink(int id);

	CIoSimulantPort *GetLinkFromPort(int id);
	CIoSimulantPort *GetLinkToPort(int id);	

	CIoSimulant *GetLinkFromSim(int id);
	CIoSimulant *GetLinkToSim(int id);	
	void SetDistributeMethod(int imethod);
	void SetNumProcs(int inumprocs);

	
	void AddLink(CIoSimulantPort *from=NULL, CIoSimulantPort *to=NULL);
    int movedata(CIoSimulantLink *link);
	int alldatamoves();


	void movesimulantparam(int fsimid, int fparamid, int tsimid, int tparamid); 
	void moveentitysetparam(int fsimid, int fes, int fparamid, int tsimid, int tes, int tparamid); 
    void moveentityparam(int fsimid, int fes, int fe, int fparamid,int tsimid, int tes, int te, int tparamid);

    int GetSimulantID(CIoSimulant *psim);
	
	void SetSimulatorName(const char *name);
	char *GetSimulatorName(){return m_sSimulatorName;}
	void SetSimulatorClass(const char *name);
	char *GetSimulatorClass(){return m_sSimulatorClass;}
	int GetNumSimulants();
	char *GetClassName(){return m_sSimulatorClass;}


	int ReadConfig(char *sConfigFilename, char *format=NULL){return 0;}
	int WriteConfig(char *sConfigFilename, char *format=NULL){return 0;}

	int ReadState(char *sStateFilename, int format=NULL){return 0;}
	int WriteState(char *sStateFilename, int format=NULL){return 0;}


	virtual	int CheckParamFormat(CIoParam *pSimData){return((pSimData && (pSimData->GetType()==IO_PARAM_ARRAY)));}
	virtual void CreateDefaultParams();
	//When creating the simulator pass the parameters for that child
	//and pass any parameter sets for its children
	virtual int CreateEntitySets(int iNumES=0, CIoParam *pESClassName=NULL, CIoParam *pESParam=NULL, CIoParam *pETSParam=NULL , char *cESMap=NULL){return 0;}

	virtual int CreateConfig(){return 0;}
	virtual void CreateSimulant(CIoParam *pParentParams=NULL, CIoParam *pChildParams=NULL);
	virtual int CreateSimulator(CIoParam *pSimulatorParams=NULL,
					           CIoParam *pModelParams=NULL,
							   CIoParam *pEntitySetParams=NULL	){return Create(pSimulatorParams, pModelParams, pEntitySetParams);}

	virtual int Create(CIoParam *pParams=NULL, CIoParam *pChildParams=NULL, CIoParam *pArray=NULL);

	CIoSimulant *GetSimulant(){return m_pSimulant;}
	CIoSimulant *GetSimulant(int simid){return GetChild(simid);}
	CIoSimulant *GetChildSimulant(int i, char *ssimulantmap=NULL);


	virtual void Add(CIoSimulant *pSimulant);
	virtual void Remove(CIoSimulant *pSimulant);
	virtual CIoSimulant *GetChild(int index);

	virtual void CreateEntitySet(CIoParam *pEntitySetParams=NULL,
						 CIoParam *pEntityTypeSetParams=NULL, int iModel=-1);

	virtual void RunSimulantStep();


	
	//The user may override this class
    //to update the parameters
    //but will call this class
    //to handle interactions for the actual simulants
    //For each simulant hande the interactions
	virtual void HandleInteractions();

	//The user may override this class
     //to update the parameters
     //but will call this class
     //to handle state transitions for the actual simulants
    //For each simulant hande the state transitions
	virtual void HandleStateTransitions();

	//Handle interactions between different models
	void HandleModelInteractions();

};

#endif
