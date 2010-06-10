#ifndef IO_SIMULATION_SIMULATIONSAXHANDLER_H
#define IO_SIMULATION_SIMULATIONSAXHANDLER_H
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
//#pragma warning(disable:4786)
// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
//#include "IoConfigDOMBuilder.h"
#include <iome/simulation/IoXStr.h>
#include <iome/simulation/IoXMLSimulation.h>






#include <stack>

#ifndef IO_MSVC
 #include <iome/utils/IoParams.h>
//#include <iome/simulation/IoModel.h>
//#include <iome/simulation/IoSimulator.h>
//#include <iome/simulation/IoEntitySet.h>
//#include <iome/simulation/IoEntityTypeSet.h>
#else
 #include <iome/utils/IoParams.h>
//	#include <iome/simulation/IoModel.h>
//	#include <iome/simulation/IoSimulator.h>
//	#include <iome/simulation/IoEntitySet.h>
//	#include <iome/simulation/IoEntityTypeSet.h>
#endif



#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>

//#include <iostream.h>
#include <iome/simulation/IoStrX.h>

using std::ostringstream;
//using namespace std ;
using namespace xercesc;

typedef CIoParam *   PARAMPTR;
//typedef CIoSimulant * SIMULANTPTR;
typedef std::stack<PARAMPTR> PARAM_STACK;
typedef std::stack<int> ELEMENT_STACK;
//typedef std::stack<SIMULANTPTR> SIMULANT_STACK;
typedef std::stack<int> PARAMINDEX_STACK;
typedef std::stack<int> ARRAYSIZE_STACK;

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
#define IO_XMLP_STACK_ELEMENT_STRING 21
#define IO_XMLP_STACK_ELEMENT_FILEPROPS 22
#define IO_XMLP_STACK_ELEMENT_ENTITYPROPS 23
#define IO_XMLP_STACK_ELEMENT_MMAT3D 24
#define IO_XMLP_STACK_ELEMENT_STRINGARRAY 25
#define IO_XMLP_STACK_ELEMENT_METADATALIST 26
#define IO_XMLP_STACK_ELEMENT_METADATA 27


class CIoXMLSimulation;




class CIoSimulationSAXHandler :
	public DefaultHandler
{
public:
	CIoSimulationSAXHandler();
	CIoSimulationSAXHandler(CIoXMLSimulation *pSimulation);
	~CIoSimulationSAXHandler(void);

//	CIoSimulant *m_pSimulant;
	CIoXMLSimulation *m_pSimulation;
	PARAM_STACK  m_ParamStack;   //Used for building param arrays
	PARAM_STACK  m_ParamArrayStack;   //Used for building param arrays
	PARAM_STACK  m_ArrayStack;   //Used for building arrays
	ARRAYSIZE_STACK m_ArraySizeStack;

	ELEMENT_STACK m_ElementStack;  //For general parser control
	ELEMENT_STACK m_SimElementStack;  //For parser control to indicate current simulation object
//	SIMULANT_STACK m_SimulantStack;  //For parsing models and simulators in particular 
	PARAMINDEX_STACK m_ParamIndexStack;

	    //read in variables
	    static int m_iCint;
		static float m_fCfloat;
		static vec *m_pCvec;
		static matrix *m_pCmat;
		static mmat3d *m_pCmmat3d;
		static IoStringArray *m_pStringArray;

		static char *m_pCstring;
		std::ostringstream m_sb;
		static CIoParam *m_pCprop;
		static CIoParam *m_pCPropArray;
		static CIoParam *m_pCArray;

		//static CIoEntitySet *m_pEntitySet;
		//static int m_inumentities;
		//static CIoEntityTypeSet *m_pEntityTypeSet;
		//static int m_inumentitytypes;
		//static CIoEntityType *m_pEntityType;
		static int m_vecsize;
		static int m_matrows;
		static int m_matcols;
		static int m_mm3r;
		static int m_mm3c;
		static int m_mm3d;

		static int m_matcurrentrow;
		//static CIoSimulantLink *m_psimulantlink;
		//static CIoSimulantPort *m_pport;

    // -----------------------------------------------------------------------
    //  Handlers for the SAX ContentHandler interface
    // -----------------------------------------------------------------------
    void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);

    void StartSimulationElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	//void StartSimulantElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
    //void StartSimulatorElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	//void StartModelElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartParamArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartParamElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);

	void StartIntElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartFloatElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartStringElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartStringArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartVectorElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartVecElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartMatrixElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void Startmmat3dElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);

    //void StartEntitySetElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
    //void StartEntityTypeSetElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
    //void StartEntityTypeElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
    void StartStepsElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
    void StartfilepropsElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	//void StartEntitypropsElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartMetadatalistElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	void StartMetadataElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	//void StartLinksElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	//void StartLinkElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	//void StartFromElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	//void StartToElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);

	void SetPropArrayFlag(int index, int iflag);
	void SetPropArrayName(int index, char *sname);
	void SetPropFlag(int index, int iflag);
	void SetPropName(int index, char *sname);




	void endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void endParamArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void endParamElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void EndIntElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void EndArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	
	void EndFloatElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void EndStringElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void EndStringArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	
	void EndVectorElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void EndVecElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void EndMatrixElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void Endmmat3dElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);

	//void EndModelElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);

	void EndMetadatalistElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	void EndMetadataElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);

	//void EndLinksElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	//void EndLinkElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	//void EndFromElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);
	//void EndToElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname);



    void characters(const XMLCh* const chars, const unsigned int length);
    //void ignorableWhitespace(const XMLCh* const chars, const unsigned int length);
    //void resetDocument();


    // -----------------------------------------------------------------------
    //  Handlers for the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
	//void warning(const SAXParseException& exception);
    //void error(const SAXParseException& exception);
    //void fatalError(const SAXParseException& exception);
    //void resetErrors();
	bool getSawErrors() const
    {
        return fSawErrors;
    }

	 bool            fSawErrors;
};

#endif
