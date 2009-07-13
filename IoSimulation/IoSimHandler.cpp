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

// IoSimHandler.cpp: implementation of the CIoSimHandler class.
//
//////////////////////////////////////////////////////////////////////


#include "IoSimHandler.h"

int CIoSimHandler::m_iNumCycles=0;
int CIoSimHandler::m_iCurrentCycle=0;
int CIoSimHandler::m_iCurrentStep=0;
int CIoSimHandler::m_iNumSteps=0;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoSimHandler::CIoSimHandler(CIoSimulation *pParentSimulation,
	CIoSimulant *pParentSimulant,
	CIoSimHandler *pParentHandler)
	{
	m_pParentSimulation = pParentSimulation;
	m_pParentHandler = pParentHandler;
	m_pParentSimulant= pParentSimulant;

	#ifdef USEMPI
		m_comm=MPI::COMM_WORLD;
		m_nprocs=m_comm.Get_size();
		m_irank=m_comm.Get_rank();
	#endif

}

CIoSimHandler::~CIoSimHandler()
{

}

void CIoSimHandler::HandleInteractions()
{



}


void CIoSimHandler::HandleModelInteractions()
{


}

void CIoSimHandler::HandleStateTransitions()
{




}

#ifdef USEMPI

	int CIoSimHandler::SendRecvParam(int fromproc, int toproc, int iparamid,  char *sparammap)
	{
		int status=0;
		CIoParam *pparam=NULL;
		int sval;
		float sfval;
		float rfval;
		int rval;

		if((m_irank==fromproc) && (pparam=GetChildParam(iparamid, sparammap))!=NULL)
		{
				switch(pparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=pparam->GetIntParam();
						m_comm.Send(&sval,1,MPI::INT,toproc,1);
					break;
				case IO_PARAM_FLOAT:
						sfval=pparam->GetFloatParam();
						m_comm.Send(&sfval,1,MPI::FLOAT,toproc,1);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
		}


	if((m_irank==toproc) && (pparam=GetChildParam(iparamid, sparammap))!=NULL)
			{
				//void MPI::Comm::Recv(void* buf, int count, const MPI::Datatype& datatype, int source, int tag) const
				switch(pparam->GetType())
				{
				case IO_PARAM_INTEGER:
					    
						m_comm.Recv(&rval, 1,MPI::INT,fromproc,1);
						pparam->SetParam(&rval);
					break;
				case IO_PARAM_FLOAT:
					    
						m_comm.Recv(&rfval, 1,MPI::FLOAT,fromproc,1);
						pparam->SetParam(&rfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}



		return status;
	}

	//param arays not yet sent simple loop
	int CIoSimHandler::SendRecvParams(int fromproc, int toproc)
	{
		int status=0;
		char *parammap=NULL;
		for(int i=0; i<GetNumProps(); i++)
			SendRecvParam(fromproc, toproc, i,parammap);

		return status;
	}

	//param arays not yet sent simple loop
	int CIoSimHandler::BroadcastParams(int fromproc)
	{
		int status=0;
		char *parammap=NULL;
		for(int i=0; i<GetNumProps(); i++)
			BroadcastParam(fromproc, i,parammap);

		return status;
	}

	int CIoSimHandler::BroadcastParam(int fromproc, int iparamid, char *sparammap)
	{
		int status=0;
		CIoParam *pparam=NULL;
		int sval;
		float sfval;
		float rfval;
		int rval;

		if(( (pparam=GetChildParam(iparamid, sparammap))!=NULL))
		{
				switch(pparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=pparam->GetIntParam();
						m_comm.Bcast(&sval,1,MPI::INT,fromproc);
					break;
				case IO_PARAM_FLOAT:
						sfval=pparam->GetFloatParam();
						m_comm.Bcast(&sfval,1,MPI::FLOAT,fromproc);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
		}

		return status;
	}

#endif




