#ifndef IO_XMLSIMULATION_SIMULATION_H
#define IO_XMLSIMULATION_SIMULATION_H
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
// IoSimulation.h: interface for the CIoXMLSimulation class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_IOSIMULATION_H__0C90F4FD_B515_497F_807F_EC47DE354F3C__INCLUDED_)
//#define AFX_IOSIMULATION_H__0C90F4FD_B515_497F_807F_EC47DE354F3C__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
#ifndef IO_MSVC
	#include "../IoUtils/IoPropertyManager.h"
	#include "../IoUtils/IoFileUtils.h"
	#include "IoSimulator.h"
	#include "IoSimulation.h"
	#include "IoModel.h"
#else
	#include "..\IoUtils\IoPropertyManager.h"
	#include "..\IoUtils\IoFileUtils.h"
	#include "IoSimulator.h"
	#include "IoSimulation.h"
	#include "IoModel.h"
	
#endif

	#include "IoConfigDOMBuilder.h"
	#include "IoSimDOMBuilder.h"
	#include "IoSimulationReader.h"
	#include "IoConfigReader.h"



#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>
#include <xalanc/XalanTransformer/XalanCompiledStylesheet.hpp>
#include <xalanc/XSLT/XSLTInputSource.hpp>
#include <xalanc/XSLT/XSLTResultTarget.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include <xalanc/XMLSupport/FormatterToXML.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>
#include <xalanc/XalanTransformer/XercesDOMParsedSource.hpp>
#include <xalanc/XalanTransformer/XercesDOMWrapperParsedSource.hpp>
#include <xalanc/XercesParserLiaison/XercesDOMSupport.hpp>
#include <xalanc/XercesParserLiaison/XercesParserLiaison.hpp>
#include <xalanc/XercesParserLiaison/FormatterToXercesDOM.hpp>

//XALAN_USING_XERCES(DOMDocument)
XALAN_USING_XERCES(DOMImplementation)

XALAN_USING_XALAN(FormatterToXML)
XALAN_USING_XALAN(XalanCompiledStylesheet)



XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XalanTransformer)
//XALAN_USING_XALAN(XSLTInputSource)
//XALAN_USING_XALAN(XSLTResultTarget)
//Minimise the nummber of methods that a developer needs to override
//using namespace xercesc;

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::endl;

class CIoConfigDOMBuilder;


class CIoXMLSimulation : public CIoSimulation 
{
public:
	CIoXMLSimulation();
	virtual ~CIoXMLSimulation();

	char *m_sSimXSLFileName;
	char *m_sConfigXSLFileName;
	char *m_sStateXSLFileName;

	char *m_sConfigXSLFilePrefix;
	char *m_sStateXSLFilePrefix;



	CIoConfigDOMBuilder *m_pDOMState;

	#ifndef IO_XERCESCVERSION
	    xercesc_2_7::DOMDocument *m_pConfigDOM;
	#else  	
		IO_XERCESCVERSION::DOMDocument *m_pConfigDOM;
	#endif
	//xercesc_2_8::DOMDocument *m_pConfigDOM;	
	//xercesc_2_7::DOMDocument *m_pConfigDOM;
	//xercesc_2_6::DOMDocument *m_pConfigDOM;
	XalanCompiledStylesheet *m_pCompiledStyleSheet;


	#ifndef IO_XERCESCVERSION
	    xercesc_2_7::DOMDocument *m_pTransformedConfigDOM;
	#else  	
		IO_XERCESCVERSION::DOMDocument *m_pTransformedConfigDOM;
	#endif
	//xercesc_2_8::DOMDocument *m_pTransformedConfigDOM;
	//xercesc_2_7::DOMDocument *m_pTransformedConfigDOM;
	//xercesc_2_6::DOMDocument *m_pTransformedConfigDOM;
 

	XalanCompiledStylesheet *CreateCompiledStyleSheet();
	void DeleteCompiledStyleSheet();

	int CreateTransformedConfigDOM();
	void DeleteTransformedConfigDOM();

	virtual int CreateConfig();
	int CreateConfigDOM();
	void DeleteConfigDOM();




	virtual void CreatePropNames();
	virtual void CreatePropArrayNames();

	void SetStateXSLFileName(const char *name);
	char *GetStateXSLFileName(){return m_sStateXSLFileName;}
	void SetConfigXSLFileName(const char *name);/*{for(int i=0; i<strlen(name), i<100; i++)m_sConfigFileName [i]=name [i];}*/
	void SetSimXSLFileName(const char *name);/*{for(int i=0; i<strlen(name), i<100; i++)m_sConfigFileName [i]=name [i];}*/

	char *GetConfigXSLFileName(){return m_sConfigXSLFileName;}
	char *GetSimXSLFileName(){return m_sSimXSLFileName;}

	void SetStateXSLFilePrefix(const char *name);
	char *GetStateXSLFilePrefix(){return m_sStateXSLFilePrefix;}
	void SetConfigXSLFilePrefix(const char *name);/*{for(int i=0; i<strlen(name), i<100; i++)m_sConfigFileName [i]=name [i];}*/
	char *GetConfigXSLFilePrefix(){return m_sConfigXSLFilePrefix;}




	
	//A virtual method that can be overridden method to create a simulation
    //from simulation read in from XML file
	//The default here is false to indicate that a simulation 
	//was not created
	//The user is not forced to use an XML parser
	//may use their custom parser
	//we'll always default to the case where simulation is created using default parameters
	virtual int ReadSimulation(char *sSimFilename);
	virtual int WriteSimulation(char *sSimFilename=NULL, char *sXSLFilename=NULL);

	//Models, simulators, entity sets, entities etc...
	//will have flags to determine which properties
	//are each parameter has write flag which has default 1 meaning
	//write the parameter may be set using the property manager or the property

	//A format string identifier
	virtual int ReadConfig(char *sConfigFilename, int format=0);
	virtual int WriteConfig(char *sConfigFilename, int format=0, char *sXSLFilename=NULL, int iStepNum=-1);

	virtual int ReadState(char *sStateFilename, int format=NULL);
	virtual int WriteState(char *sStateFilename, int format=NULL, char *sXSLFilename=NULL, int iStepNum=-1);

	virtual int ReadStateInfo(char *sStateFilename, int format=0);
	virtual int WriteStateInfo(char *sStateFilename, int format=0, char *sXSLFilename=NULL, int iStepNum=-1);


	int XSLTransform(char *sxmlin, char *sxslin, char *sxmlout);
	int SimTrans2AscFormat(char *ssimfile, char *ssimoutfile, int method=1);
	int SimTransAscFormat2XML(char *ssimfile, char *ssimoutfile);

	int StateTrans2AscFormat(char *sstatefile, char *sstateoutfile, int method=1);
	int StateTransAscFormat2XML(char *sstatefile, char *sstateoutfile, int method=1);

	int CfgTrans2AscFormat(char *scfgfile, char *scfgoutfile, int method=1);
	int CfgTransAscFormat2XML(char *scfgfile, char *scfgoutfile, int method=1);

};

#endif 
