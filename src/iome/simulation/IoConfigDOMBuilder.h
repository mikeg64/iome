#ifndef IO_SIMULATION_CONFIGDOMBUILDER_H
#define IO_SIMULATION_CONFIGDOMBUILDER_H
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

#ifndef IO_MSVC
	#include <iome/simulation/IoEntity.h>
#else
	#include <iome/simulation/IoEntity.h>
#endif

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
#include <xalanc/Include/PlatformDefinitions.hpp>

//#include <stdio.h>

#include <xalanc/XalanTransformer/XalanTransformer.hpp>
//#include <xalanc/XSLT/XSLTInputSource.hpp>
//#include <xalanc/XSLT/XSLTResultTarget.hpp>

#include <iome/simulation/IoConfigDOMPrintFilter.hpp>

#include <string.h>
#include <stdlib.h>
#include <stack>

//using namespace std ;
XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XalanTransformer)

typedef CIoSimulant * SIMULANTPTR;
typedef std::stack<int> ELEMENT_STACK;
typedef std::stack<SIMULANTPTR> SIMULANT_STACK;



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
#define IO_XMLP_STACK_ELEMENT_ENTITY 21
#define IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE 22
#define IO_XMLP_STACK_ELEMENT_MMAT3D 23
#define IO_XMLP_STACK_ELEMENT_STRINGARRAY 24

#define IO_MAXDEPTH 100

class CIoXMLSimulation;

#include <iome/simulation/IoXStr.h>
   
#ifndef IO_MSVC
    XERCES_CPP_NAMESPACE_USE
#endif

//using namespace xercesc;
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::endl;
class CIoConfigDOMBuilder
{
public:
	CIoConfigDOMBuilder(void);
	~CIoConfigDOMBuilder(void);

	DOMImplementation *m_pDOMImpl;
	xercesc::DOMDocument *m_pDOMDoc;
	DOMElement *m_pRootElem;
	ELEMENT_STACK m_SimElementStack;  //For parser control to indicate current simulation object
	SIMULANT_STACK m_SimulantStack;  //For parsing models and simulators in particular 

	//Variable for controlling and mappin position in array
	int m_iArrayDepth;
	int m_iCurrentProp;
	int m_iCurrentIndex;
	char *m_sArrayMap;
	int m_iMapArray [IO_MAXDEPTH];
	int m_iflagtype; /*! Flag determines what bit field to check  always 2*/
	CIoXMLSimulation *m_pSimulation;
	CIoModel *m_pCurrentModel;
	CIoSimulator *m_pCurrentSimulator;
	CIoParam *m_pCurrentParamArray;
	CIoEntitySet *m_pCurrentEntitySet;
	CIoEntity *m_pCurrentEntity;
	CIoEntityType *m_pCurrentEntityType;
	int m_iNoEntities;
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

	int CreateConfigDOM(char *docname, CIoXMLSimulation *pSimulation, int iStep=-1, int iNoEntities=0, int inoparams=1, int ifileprops=0);
    int WriteConfigDOM(char *docname, int iNoEntities=0, int inoparams=1, int ifileprops=0 );
	DOMElement *CreateSimulantElement(CIoXMLSimulation *pSimulation, DOMElement *SimulationElem);
	DOMElement *CreateSimulatorChildElement(CIoSimulant *pSimulant, DOMElement *SimulatorElem, int iIndex=0);
	DOMElement *CreateSimulatorElement(CIoSimulant *pSimulant, DOMElement *SimulantElem, int iIndex=0);
	DOMElement *CreateModelElement(CIoSimulant *pSimulant, DOMElement *SimulantEleme, int iIndex=0);
	DOMElement *CreateModelParamsElement(CIoModel *pModel, DOMElement *ModelElem);
	DOMElement *CreateSimulationElement(CIoXMLSimulation *pSimulation, int iStep=-1, int iNoEntities=0, int inoparams=1, int ifileprops=0 );
	DOMElement *CreateMetadatalistElement(CIoXMLSimulation *psim, DOMElement *parentsim);

	//1 flag increate prop element
	//indicates we are not create a prop tag, 
	//writin an index or property name label
	// the default is 0
	DOMElement *CreatePropsElement(string sName, int inumprops, DOMElement *ParentEleme, int iShowAllTags=0);//parent could be simulant, modelparams or prop
	DOMElement *CreateEntityPropsElement(string sName, int iFlag, int inumprops, DOMElement *ParentEleme);

	//1 flag increate prop element
	//indicates we are not create a prop tag, 
	//writin an index or property name label
	// the default is 0
	DOMElement *CreatePropElement(CIoParam *pParams, DOMElement *ParentProps, int iShowAllTags=0);
	DOMElement *CreateEntityPropElement(CIoParam *pParams, DOMElement *ParentProps, int iShowAllTags=0);

	DOMElement *CreateArrayElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateIntElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateFloatElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateVectorElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateMatElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *Createmmat3dElement(CIoParam *pParams, DOMElement *ParentProps);

	DOMElement *CreateStringElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateStringArrayElement(CIoParam *pParams, DOMElement *ParentProps);
	
	DOMElement *CreateVecElement(CIoParam *pParams, DOMElement *ParentProps);
	DOMElement *CreateEntitySetElement(CIoEntitySet *pEntitySet, DOMElement *ModelElem);
	DOMElement *CreateEntityElement(CIoEntity *pEntity, DOMElement *EntitySetElem, int id=-1);
	//DOMElement *CreateEntityTypeElement(CIoEntity *pEntity, DOMElement *EntitySetElem);

	DOMElement *CreateFilePropsElement(CIoXMLSimulation *pSimulation, DOMElement *ParentSim);


};
#endif
