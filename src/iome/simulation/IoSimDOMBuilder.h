#ifndef IO_SIMULATION_SIMDOMBUILDER_H
#define IO_SIMULATION_SIMDOMBUILDER_H
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
//#pragma once
#include <iome/simulation/IoXMLSimulation.h>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
//#include <iostream.h>



#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>

#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

//#include <stdio.h>

#include <iome/simulation/IoSimDOMPrintFilter.hpp>

#include <string.h>
#include <stdlib.h>
#include <stack>
#include <string>
#include <sstream>

//using namespace std ;
using namespace xercesc;

//typedef CIoSimulant * SIMULANTPTR;
typedef std::stack<int> ELEMENT_STACK;
//typedef std::stack<SIMULANTPTR> SIMULANT_STACK;



#define IO_XMLP_STACK_ELEMENT_SIMULATION 1
#define IO_XMLP_STACK_ELEMENT_SIMULANT 2 
#define IO_XMLP_STACK_ELEMENT_SIMULATOR 3
#define IO_XMLP_STACK_ELEMENT_MODEL 4
#define IO_XMLP_STACK_ELEMENT_ENTITYSET 5
#define IO_XMLP_STACK_ELEMENT_ENTITYTYPESET 6
#define IO_XMLP_STACK_ELEMENT_PROPS 7
#define IO_XMLP_STACK_ELEMENT_PROP 8
#define IO_XMLP_STACK_ELEMENT_INT 9
#define IO_XMLP_STACK_ELEMENT_FLOAT 10
#define IO_XMLP_STACK_ELEMENT_VEC 11
#define IO_XMLP_STACK_ELEMENT_VECTOR 12
#define IO_XMLP_STACK_ELEMENT_MATRIX 13
#define IO_XMLP_STACK_ELEMENT_MAT 14
#define IO_XMLP_STACK_ELEMENT_ARRAY 15
#define IO_XMLP_STACK_ELEMENT_STEPS 16
#define IO_XMLP_STACK_ELEMENT_ROWS 17
#define IO_XMLP_STACK_ELEMENT_COLS 18
#define IO_XMLP_STACK_ELEMENT_SIZE 19
#define IO_XMLP_STACK_ELEMENT_MODELCREATOR 20
#define IO_XMLP_STACK_ELEMENT_ENTITYTYPE 21
#define IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE 22
#define IO_XMLP_STACK_ELEMENT_MMAT3D 23
#define IO_XMLP_STACK_ELEMENT_STRINGARRAY 24

#define IO_MAXDEPTH 100

class CIoXMLSimulation;

#include "IoXStr.h"

#ifndef IO_MSVC
    XERCES_CPP_NAMESPACE_USE
#endif

using namespace xercesc;

class CIoSimDOMBuilder
{
public:
	CIoSimDOMBuilder(void);
	~CIoSimDOMBuilder(void);

	DOMImplementation *m_pDOMImpl;
	xercesc::DOMDocument *m_pDOMDoc;
	ELEMENT_STACK m_SimElementStack;  //For parser control to indicate current simulation object
	//SIMULANT_STACK m_SimulantStack;  //For parsing models and simulators in particular 

	//Variable for controlling and mappin position in array
	int m_iArrayDepth;
	int m_iCurrentProp;
	int m_iCurrentIndex;
	char *m_sArrayMap;
	int m_iflagtype; 
	int m_iMapArray [IO_MAXDEPTH];

	//CIoModel *m_pCurrentModel;
	//CIoEntitySet *m_pCurrentEntitySet;
	//CIoEntityTypeSet *m_pCurrentEntityTypeSet;
	//CIoEntityType *m_pCurrentEntityType;
	//CIoSimulator *m_pCurrentSimulator;
	CIoParam *m_pCurrentParamArray;
	CIoXMLSimulation *m_pSimulation;

	string GetPropName();
	string GetPropArrayName();
	string GetPropInfilename();
	string GetPropArrayInfilename();
	string GetPropOutfilename();
	string GetPropArrayOutfilename();

	void CreateArrayMap();
	void ResetDepthArray();
	int GetPropFlag();
	int GetPropsFlag();
	int TestPropFlag();
	int TestPropsFlag();
	int CreateSimDOM(char *docname, CIoXMLSimulation *pSimulation);
    int WriteSimDOM(char *docname);
	char *WriteMemSimDOM();
	DOMElement *CreatePropsElement(string sName, int iFlag, int inumprops, DOMElement *ParentEleme);//parent could be simulant, modelparams or prop
	DOMElement *CreateArrayElement(CIoParam *pParams, DOMElement *ParentProps);//parent could be simulant, modelparams or prop
	
	DOMElement *CreatePropElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateIntElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateFloatElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateVectorElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateMatElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *Createmmat3dElement(CIoParam *pParams, DOMElement *ParentProps);

	DOMElement *CreateStringElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateStringArrayElement(CIoParam *pParams, DOMElement *ParentProps);

	DOMElement *CreateMetadatalistElement(CIoXMLSimulation *psim, DOMElement *parentsim);


	DOMElement *CreateVecElement(CIoParam *pParams, DOMElement *ParentProps);
    DOMElement *CreateStepsElement(CIoXMLSimulation *pSimulation, DOMElement *ParentSim);
	DOMElement *CreatefilepropsElement(CIoXMLSimulation *pSimulation, DOMElement *ParentSim);

};

#endif
