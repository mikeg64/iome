#ifndef IO_GENERICSTEER_GENERICSTEER_H
#define IO_GENERICSTEER_GENERICSTEER_H
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
#include <iome/simulation/IoInitialiser.h>
#include <iome/simulation/IoGenericSteerSimulation.h>





CIoGenericSteerSimulation *m_steer=NULL;
static CIoInitialiser m_Init;
pthread_t m_servertid;

//Methods to be used
int InitIOME(char *simname, char *statefilename=NULL, char *configfilename=NULL);
int CreateSimulation();
int ExitIOME();
int StartServer();
int ConfigureParams();
int CreateDefaultParams();
int GetParamDouble(double *value, string sparamname);
int SetParamDouble(double value, string sparamname, int iflag=1);
int GetParamInt(int *value, string sparamname);
int SetParamInt(int value, string sparamname, int iflag=1);
int GetParamVec(double *value, int n, string sparamname);
int SetParamVec(double *value, int n, string sparamname, int iflag=1);
int GetParamMat(double *value, int nr, int nc,string sparamname);
int SetParamMat(double *value, int nr, int nc,string sparamname, int iflag=1);
int GetParammmat3d(double *value, int n, int p, int q, int nr, int nc, string sparamname);
int SetParammmat3d(double *value, int n, int p, int q, int nr, int nc, string sparamname, int iflag=1);
int WriteSimulation();
int WriteState();
int WriteConfig();

int UpdateParams();

int AddParamDouble(double value, string sparamname, int iflag);
int AddParamInt(int value, string sparamname, int iflag);
int AddParamVec(double *value, int n, string sparamname, int iflag);
int AddParamMatrix(double *value, int nr, int nc, string sparamname, int iflag);
int AddParammmat3d(double *value, int n, int p, int q, int nr, int nc, string sparamname, int iflag);


#endif
