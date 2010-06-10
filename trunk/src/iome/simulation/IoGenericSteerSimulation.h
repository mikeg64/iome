#ifndef IO_GENERICSTEERSIMULATION_GENERICSTEERSIMULATION_H
#define IO_GENERICSTEERSIMULATION_GENERICSTEERSIMULATION_H
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
	#include "../IoSimulation/IoWFSimulation.h"
#else
	#include "..\IoSimulation\IoWFSimulation.h"
#endif*/


#include <iome/simulation/IoXMLSimulation.h>
#include <iome/simulation/IoModel.h>
//#include "IoAgentSimulator.h"
#ifndef IO_MSVC
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/wait.h>
#else
	#include <windows.h>  //not sure if this is required??
	#include <process.h>
#endif
#include <vector>

using std::deque;
using std::vector;

#define IO_STARSIM_NUMEQULIBSTEPS_INT 0

struct nodeinfo 
{
public :
	int portid;
	char *server;
	int numsubprocs;
};

struct jobinfo 
{
public :
	int procid;
	int subprocid;
};

typedef struct nodeinfo*   NODEINFOPTR;
typedef struct jobinfo*   JOBINFOPTR;

class CIoGenericSteerSimulation :
	public CIoXMLSimulation
{
public:
	CIoGenericSteerSimulation(void);
	~CIoGenericSteerSimulation(void);

	void CreatePropNames();
	void CreatePropArrayNames();
	void CreatePropFlags();
	void CreatePropArrayFlags();

	CIoModel *newModel(char *sModelClass);
	//CIoSimulator *newSimulator(char *sSimulatorClass);
	//CIoSimulant *WriteConfigSimulatorIterator(CIoSimulant *pSimulant, char *sConfigFilename, char *format=NULL, char *sXSLFilename=NULL);
	//CIoSimulant *ReadConfigSimulatorIterator(CIoSimulant *pSimulant, char *sConfigFilename, char *format=NULL);

	/*!
	Following read simulation is required since the SAX simulation parser may
	not call a default model configuration creator. This makes sure
	that the configuration gets created with the correct parameter set
	*/
	//int ReadSimulation(char *sSimFilename);
	int WriteConfig(char *sConfigFilename, int format=0, char *sXSLFilename=NULL, int iStepNum=-1);
	
	int CheckParamFormat(CIoParam *pSimData);
    void CreateDefaultParams();

	//Life simulation reads an unconventional array
	//we have to define our own type of config file

	int SetParamDouble(double value, string sparamname, int iflag=1);
	int GetParamDouble(double *value, string sparamname);
	int SetParamInt(int value, string sparamname, int iflag=1);
	int GetParamInt(int *value, string sparamname);
	int SetParamString(string value, string sparamname, int iflag=1);
	int GetParamString(string *value, string sparamname);

	int GetParamVec(double *value, int n, string sparamname);
	int SetParamVec(double *value, int n, string sparamname, int iflag=1);
	int GetParamMat(double *value, int nr, int nc,string sparamname);
	int SetParamMat(double *value, int nr, int nc,string sparamname, int iflag=1);
	int GetParammmat3d(double *value, int n ,int p, int q, int nr, int nc,string sparamname);
	int SetParammmat3d(double *value, int n ,int p, int q, int nr, int nc,string sparamname, int iflag=1);
	
	
	int AddParamDouble(double value, string sparamname, int iflag);
	int AddParamInt(int value, string sparamname, int iflag);
	int AddParamString(string value, string sparamname, int iflag);

	int AddParamVec(double *value, int n, string sparamname,int iflag);	
	int AddParamMat(double *value, int nr, int nc, string sparamname,int iflag);	
	int AddParammmat3d(double *value, int n, int p, int q, int nr, int nc, string sparamname, int iflag);
	
	int DeleteParam(char *name);
	void ListParam(char *type, char *slist);

	int CreateSimulation(char *sFilename=NULL);
    void RunSimulationStep(int iStepNum);
	void RunSimulation();

	//int ReadMachinefile(); //reads machinefile
	int AddNode(int port, string server, int numsubprocs);
	int DeleteNode(int id);
	int DeleteNodes();
	
	int GetNodePort(int id);
	//int SetNodePort(int id, int port);
	char *GetNodeServer(int id);
	int GetNumServerNodes();
	int GetNumSubProcs(int id);
	//int SetNodePort(int id, int port);

	int AddJob(int procid, int subprocid);
	int DeleteJob(int id);
	int DeleteJobs();
	int GetJobProcid(int id);
	int GetJobSubprocid(int id);

	int GetJobPort(int id);
	char * GetJobServer(int id);
	int GetNumJobs();

	int GetJobid(int procid, int subprocid);

	int copynodes(vector<NODEINFOPTR> nodes);
	int copyjobs(vector<JOBINFOPTR> jobs);
	
    deque<CIoParam *>  m_pConstParams; //add param methods are used to add parameters to the model
	                                   //the parameters which are added define the default values
	                                   //for the parameters so these values are fixed
	deque<string>  m_pPropName;
	deque<int>  m_pPropFlag;
	vector<NODEINFOPTR>  m_pnodes;
	vector<JOBINFOPTR>  m_pjobs;
	int m_ipid;
    int m_isubproc;
	int m_ijobid;
	int m_iprocid;
	int m_ibarrier; //default==0 i.e. false and not at barrier
};



#endif
