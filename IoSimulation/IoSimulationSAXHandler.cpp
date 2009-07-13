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

/*!
Important note:  
The simulation flags and names are read from here. It is possible to set
the values by reading from here. The simulation and its entities only
need to have a set of default values.

Defined when we build the simulation.

Thus it is possible to use the simulation file to create a set of names and
flags and the developer is not required to define the methods for setting these.

The procedure is that developer provides a default input file which
is provided with the implementation of the simulation and this is read at start time.

If no inuput file is provided by the user then this simulation file is always read
and the default props, names and flags are read from this.

if no simulation is found
*/

#include "IoSimulationSAXHandler.h"
#define XLO(str) StrX(str).localForm()


//read in variables

CIoParam *CIoSimulationSAXHandler::m_pCArray=NULL;
int CIoSimulationSAXHandler::m_iCint=0;
float CIoSimulationSAXHandler::m_fCfloat=0;
vec *CIoSimulationSAXHandler::m_pCvec=NULL;
matrix *CIoSimulationSAXHandler::m_pCmat=NULL;
mmat3d *CIoSimulationSAXHandler::m_pCmmat3d=NULL;

char *CIoSimulationSAXHandler::m_pCstring=NULL;
CIoParam *CIoSimulationSAXHandler::m_pCprop=NULL;
CIoParam *CIoSimulationSAXHandler::m_pCPropArray=NULL;
IoStringArray *CIoSimulationSAXHandler::m_pStringArray=NULL;

int CIoSimulationSAXHandler::m_vecsize=0;
int CIoSimulationSAXHandler::m_matrows=0;
int CIoSimulationSAXHandler::m_matcols=0;

int CIoSimulationSAXHandler::m_mm3r=0;
int CIoSimulationSAXHandler::m_mm3c=0;
int CIoSimulationSAXHandler::m_mm3d=0;

int CIoSimulationSAXHandler::m_matcurrentrow=0;
CIoEntitySet *CIoSimulationSAXHandler::m_pEntitySet = NULL;
CIoSimulantLink *CIoSimulationSAXHandler::m_psimulantlink;
CIoSimulantPort *CIoSimulationSAXHandler::m_pport;

int CIoSimulationSAXHandler::m_inumentities=0;
CIoEntityType *CIoSimulationSAXHandler::m_pEntityType=NULL;
CIoEntityTypeSet *CIoSimulationSAXHandler::m_pEntityTypeSet=NULL;
int CIoSimulationSAXHandler::m_inumentitytypes=0;




CIoSimulationSAXHandler::CIoSimulationSAXHandler()
{
		m_pSimulation = NULL;
		fSawErrors = true;
		m_ElementStack.push(0);
		m_ParamStack.push(NULL);
		m_ParamArrayStack.push(NULL);
		m_ArrayStack.push(NULL);
		m_ArraySizeStack.push(0);
		m_SimElementStack.push(0);
		m_SimulantStack.push(NULL);
		m_pSimulant = NULL;
		m_sb.str("");

		m_ParamIndexStack.push(-1);


}

CIoSimulationSAXHandler::CIoSimulationSAXHandler(CIoXMLSimulation *pSimulation):
		fSawErrors(false)
{
	if(pSimulation)
		m_pSimulation = pSimulation;
	else
	{
		m_pSimulation = NULL;
		fSawErrors = true;
	}
	m_ElementStack.push(0);
	m_ParamStack.push(NULL);
	m_SimElementStack.push(0);
	m_SimulantStack.push(NULL);
	m_ParamArrayStack.push(NULL);
	m_ArrayStack.push(NULL);
	m_ArraySizeStack.push(0);
	
	m_ParamIndexStack.push(-1);

	//read in variables
	m_iCint=0;
	m_fCfloat=0;
	m_pCvec=NULL;
	m_pCmat=NULL;
	m_pCstring=NULL;
	m_pStringArray=NULL;
	m_pCprop=NULL;
	m_pCPropArray=NULL;
	m_pCArray=NULL;
	m_sb.str("");

	m_vecsize=0;
	m_matrows=0;
	m_matcols=0;
}

CIoSimulationSAXHandler::~CIoSimulationSAXHandler(void)
{
	if(m_pCvec) delete m_pCvec;
	if(m_pCmat) delete m_pCmat;
	if(m_pCstring) delete [] m_pCstring;
	if(m_pStringArray) delete m_pStringArray;
	
}

// ---------------------------------------------------------------------------
//  SAX2CountHandlers: Implementation of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------
void CIoSimulationSAXHandler::startElement(const XMLCh* const uri
                                   , const XMLCh* const localname
                                   , const XMLCh* const qname
                                   , const Attributes& attrs)
{
	
	if ((XMLString::compareIString(XLO(localname), "simulation")) == 0)
						StartSimulationElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "simulant")) == 0);
								
	else if((XMLString::compareIString(XLO(localname), "simulator")) == 0)
							StartSimulatorElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "model")) == 0)
							StartModelElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "props")) == 0)
							StartParamArrayElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "prop")) == 0)
							StartParamElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "array")) == 0)
							StartArrayElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "int")) == 0)
							StartIntElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "float")) == 0)
							StartFloatElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "string")) == 0)
							StartStringElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "stringarray")) == 0)
							StartStringArrayElement(uri, localname, qname, attrs);

	else if((XMLString::compareIString(XLO(localname), "vector")) == 0)
							StartVectorElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "vec")) == 0)
							StartVecElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "mat")) == 0)
							StartMatrixElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "mmat3d")) == 0)
							Startmmat3dElement(uri, localname, qname, attrs);

	else if((XMLString::compareIString(XLO(localname), "entityset")) == 0)
							StartEntitySetElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "entitytypeset")) == 0)
							StartEntityTypeSetElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "entitytype")) == 0)
							StartEntityTypeElement(uri, localname, qname, attrs);

	else if((XMLString::compareIString(XLO(localname), "steps")) == 0)
							StartStepsElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "fileprops")) == 0)
							StartfilepropsElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "entityprops")) == 0)
							StartEntitypropsElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "metadatalist")) == 0)
							StartMetadatalistElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "metadata")) == 0)
							StartMetadataElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "links")) == 0)
							StartLinksElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "link")) == 0)
							StartLinkElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "from")) == 0)
							StartFromElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "to")) == 0)
							StartToElement(uri, localname, qname, attrs);
							
							

}

void CIoSimulationSAXHandler::characters(  const   XMLCh* const    chars
								    , const unsigned int    length)
{
    //static char val1[1000];
	//val1 [0] = '\0';
	char *val1;
	
	CIoParam *pCprop;
	int lval;
	int irow, icol;
	int imr, imc, imd;

	lval = length>999 ? 999 : length;
    //strncpy( val1, XLO(chars), lval ); 

	val1 = XLO(chars);
	//val1[lval] = 0;

    int ielement;

	if(!m_ElementStack.empty())
		ielement = (int)m_ElementStack.top();
	switch(ielement)
	{
	case IO_XMLP_STACK_ELEMENT_STEPS :
		//Set simulation step numbers
		if(m_pSimulation)
		{
			char seps[] = " ,\t\n";

			int icycle=0;
			char *tokenptr;
			tokenptr = strtok(val1, seps);
			while(tokenptr !=NULL)
			{
				m_pSimulation->SetNumSteps(atoi(tokenptr));
				tokenptr = strtok(NULL, seps);
				icycle++;
			}
		}
		break;
	case IO_XMLP_STACK_ELEMENT_INT :
		pCprop = (CIoParam *)m_ParamStack.top();
		m_iCint = atoi(val1);
		//if(pCprop  && (pCprop->GetType()==IO_PARAM_INTEGER))
		//				pCprop->SetParam(&m_iCint);
		break;
	case IO_XMLP_STACK_ELEMENT_FLOAT :
		pCprop = (CIoParam *)m_ParamStack.top();
		m_fCfloat = atof(val1);
		//if(pCprop  && (pCprop->GetType()==IO_PARAM_FLOAT))
		//				pCprop->SetParam(&m_fCfloat);
		break;
	case IO_XMLP_STACK_ELEMENT_STRING :
		pCprop = (CIoParam *)m_ParamStack.top();

		if(m_pCstring) delete [] m_pCstring;
		m_pCstring = new char [strlen(val1)];
		strncpy(m_pCstring, val1, strlen(val1));
		m_sb.str("");
		m_sb<<val1;
		break;
	case IO_XMLP_STACK_ELEMENT_STRINGARRAY :
		pCprop = (CIoParam *)m_ParamStack.top();

		if(m_pStringArray) delete m_pStringArray;
		m_pStringArray = new IoStringArray();
		//strncpy(m_pCstring, val1, strlen(val1));
		m_sb.str("");
		m_sb<<val1;
		
		//tokenize string using ; as separator
		if(m_pStringArray)
		{
			char *tokenptr;
			char *stopstr;
			char seps1[] = " ,\t\n";

			tokenptr = strtok(val1, seps1);
			while(tokenptr !=NULL)
			{			
				m_pStringArray->AddString(tokenptr);
				tokenptr = strtok(NULL, seps1);				
			}
		}
					
		//if(pCprop  && (pCprop->GetType()==IO_PARAM_STRINGARRAY))
		//							pCprop->SetParam(m_pStringArray);
		break;		
	case IO_XMLP_STACK_ELEMENT_SIZE :
		m_vecsize = atoi(val1);
		break;
		case IO_XMLP_STACK_ELEMENT_VEC :
		{
			pCprop = (CIoParam *)m_ParamStack.top();
			if(m_vecsize==0) m_vecsize=1;
			vec tempvec(m_vecsize, 0);
			float fval;
			int ivecel=0;
			char *tokenptr;
			char *stopstr;
			char seps[] = " ,\t\n";

			tokenptr = strtok(val1, seps);
			while(tokenptr !=NULL)
			{			
				//fval = (float)atof(tokenptr, &stopstr);
				fval = (float)atof(tokenptr);
				if(ivecel<m_vecsize)
						tempvec.set(ivecel, fval);
				tokenptr = strtok(NULL, seps);
				ivecel++;
				

			}
			
			//pCprop->SetParam(&tempvec);
			if(m_pCvec) delete m_pCvec;
			m_pCvec=new vec(tempvec);
			
			
		}
		break;
		case IO_XMLP_STACK_ELEMENT_MATRIX :
		{
			pCprop = (CIoParam *)m_ParamStack.top();
			if(m_matrows==0) m_matcols=1;
			if(m_matcols==0) m_matcols=1;
			irow=0;
			icol=0;			
			matrix tempmat(m_matrows, m_matcols, 0, 0);
			float fval;
			int ivecel=0;
			char *tokenptr;
			char *stopstr;
			char seps[] = " ,\t\n";
			tokenptr = strtok(val1, seps);
			while(tokenptr !=NULL)
			{			
				//fval = (float)atof(tokenptr, &stopstr);
				fval = (float)atof(tokenptr);
				//std::cout<<irow << " " << icol << " "<<tokenptr << " " << fval <<std::endl;
				if(irow<m_matrows && icol<m_matcols)
						tempmat.setval(irow, icol, fval);
					
				icol++;	
				if(icol==m_matcols)
				{
					icol=0;
					irow++;					
				}
							
						
				tokenptr = strtok(NULL, seps);
				

			
			}
			
			//std::cout << tempmat;
			//pCprop->SetParam(&tempmat);
			if(m_pCmat) delete m_pCmat;
			m_pCmat=new matrix(tempmat);
			//std::cout << tempmat << std::endl;
			//std::cout << *m_pCmat << std::endl;
			
		}
		break;

		case IO_XMLP_STACK_ELEMENT_MMAT3D :
		{
			pCprop = (CIoParam *)m_ParamStack.top();
			if(m_matrows==0) m_matcols=1;
			if(m_matcols==0) m_matcols=1;
			if(m_mm3r==0) m_mm3r=1;
			if(m_mm3c==0) m_mm3c=1;
			if(m_mm3d==0) m_mm3d=1;

			irow=0;
			icol=0;
			imr=0;
			imc=0;
			imd=0;
			mmat3d tempmat(m_mm3r, m_mm3c, m_mm3d, m_matrows, m_matcols, 0, 0);
			float fval;
			int ivecel=0;
			char *tokenptr;
			char *stopstr;
			char seps[] = " ,\t\n";
			tokenptr = strtok(val1, seps);
			while(tokenptr !=NULL)
			{			
				//fval = (float)atof(tokenptr, &stopstr);
				fval = (float)atof(tokenptr);
				//std::cout<<irow << " " << icol << " "<<tokenptr << " " << fval <<std::endl;
				if(irow<m_matrows && icol<m_matcols && imr<m_mm3r && imc<m_mm3c && imd<m_mm3d)
						tempmat.setval(imr,imc,imd,irow, icol, fval);
					
				icol++;	
				if(icol==m_matcols)
				{
					icol=0;
					irow++;

					if(irow==m_matrows)
					{
						irow=0;
						imd++;

						if(imd==m_mm3d)
						{
							imd=0;
							imc++;

							if(imc==m_mm3c)
							{
								imc=0;
								imr++;
							}

						}

					}
				}
							
						
				tokenptr = strtok(NULL, seps);
				

			
			}
			
			//std::cout << tempmat;
			//pCprop->SetParam(&tempmat);
			if(m_pCmmat3d) delete m_pCmmat3d;
			m_pCmmat3d=new mmat3d(tempmat);
			//std::cout << tempmat << std::endl;
			//std::cout << *m_pCmat << std::endl;
			
		}
		break;


	/*case IO_XMLP_STACK_ELEMENT_ROWS :
		m_matrows = _wtoi(val1);
		break;
	case IO_XMLP_STACK_ELEMENT_COLS :
		m_matcols = _wtoi(val1);
		break;

	case IO_XMLP_STACK_ELEMENT_MATRIX :
		{
			if(m_matcols==0) m_matcols=1;
			if(m_matrows==0) m_matrows=1;
			tempmat= (matrix *)new matrix(m_matrows, m_matcols, 0, 0);
			int irow=0, icol=0;
			wchar_t seps[] = L" ,\t\n";
			float fval =0;
			int imatel=1;
			wchar_t *tokenptr;
			tokenptr = wcstok(val1, seps);
			while(tokenptr !=NULL)
			{
				irow = imatel%m_matcols;
				icol = imatel -(irow * m_matcols)-1;

				fval = (float)wcstod(tokenptr, &stopstr);
				tempmat->setval(irow, icol, fval);
				tokenptr = wcstok(NULL, seps);
				imatel++;
			}
			m_pCprop->SetParam(tempmat);

		}
		break;*/

	}

	//if(tempmat)
	//	delete tempmat;


}

void CIoSimulationSAXHandler::StartStepsElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_STEPS);
	int len;
	char sccf [100];
	char sscf [100];
	char scsf [100];
	char sssf [100];

	int iccf, iscf, icsf, issf;

	const XMLCh * ln, * vl; 
	int lnl, vll;

	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);
			if(m_pSimulation)
			{
				if( XMLString::compareNString(ln,XStr("configcyclefreq").unicodeForm(), lnl) == 0 )
				{
				    strcpy(sccf, XLO(vl));
					//m_pSimulation->m_iConfigCycleFreq=atoi(sccf);
				}
				else if( XMLString::compareNString(ln,XStr("statecyclefreq").unicodeForm(), lnl) == 0 )
				{
				    strcpy(sscf, XLO(vl));
					//m_pSimulation->m_iStateCycleFreq=atoi(sscf);
				}
				else if( XMLString::compareNString(ln,XStr("configstepfreq").unicodeForm(), lnl) == 0 )
				{
				    strcpy(scsf, XLO(vl));
					m_pSimulation->m_iConfigStepFreq=atoi(scsf);
				}
				else if( XMLString::compareNString(ln,XStr("statestepfreq").unicodeForm(), lnl) == 0 )
				{
				    strcpy(sssf, XLO(vl));
					m_pSimulation->m_iStateStepFreq=atoi(sssf);
				}
				
				
			}
		}

		//At end of creation if simulation exists create default 
		//configuration?


}

void CIoSimulationSAXHandler::StartfilepropsElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_FILEPROPS);
	int len;
	char sname [100];
	char sreadmeth [100];
	char swritemeth [100];

	int ireadmeth, iwritemeth;

	
	char sccf [100];
	char sscf [100];
	char scsf [100];
	char sssf [100];

	int iccf, iscf, icsf, issf;

	

	const XMLCh * ln, * vl; 
	int lnl, vll;

	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);
			if(m_pSimulation)
			{
				if( XMLString::compareNString(ln,XStr("simreadmethod").unicodeForm(), lnl) == 0 )
				{
				    strcpy(sreadmeth, XLO(vl));
					m_pSimulation->SetSimReadMethod(atoi(sreadmeth));
				}
				else if( XMLString::compareNString(ln,XStr("simwritemethod").unicodeForm(), lnl) == 0 )
				{
				    strcpy(swritemeth, XLO(vl));
					m_pSimulation->SetSimWriteMethod(atoi(swritemeth));
				}
				else if( XMLString::compareNString(ln,XStr("statereadmethod").unicodeForm(), lnl) == 0 )
				{
				    strcpy(sreadmeth, XLO(vl));
					m_pSimulation->SetStateReadMethod(atoi(sreadmeth));
				}
				else if( XMLString::compareNString(ln,XStr("statewritemethod").unicodeForm(), lnl) == 0 )
				{
				    strcpy(swritemeth, XLO(vl));
					m_pSimulation->SetStateWriteMethod(atoi(swritemeth));
				}
				else if( XMLString::compareNString(ln,XStr("configreadmethod").unicodeForm(), lnl) == 0 )
				{
				    strcpy(sreadmeth, XLO(vl));
					m_pSimulation->SetConfigReadMethod(atoi(sreadmeth));
				}
				else if( XMLString::compareNString(ln,XStr("configwritemethod").unicodeForm(), lnl) == 0 )
				{
				    strcpy(swritemeth, XLO(vl));
					m_pSimulation->SetConfigWriteMethod(atoi(swritemeth));
				}
				else if( XMLString::compareNString(ln,XStr("configfilename").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					m_pSimulation->SetConfigFileName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("statefilename").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					m_pSimulation->SetStateFileName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("configxslfile").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					if(sname && strlen(sname)>0)
						m_pSimulation->SetConfigXSLFileName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("statexslfile").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					if(sname && strlen(sname)>0)
						m_pSimulation->SetStateXSLFileName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("configxslfileprefix").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					if(sname && strlen(sname)>0)
						m_pSimulation->SetConfigXSLFilePrefix(sname);
				}
				else if( XMLString::compareNString(ln,XStr("statexslfileprefix").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					if(sname && strlen(sname)>0)
						m_pSimulation->SetStateXSLFilePrefix(sname);
				}
				
			}
		}

		//At end of creation if simulation exists create default 
		//configuration?


}


void CIoSimulationSAXHandler::StartSimulationElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	float fversion;
	int len;
	char sname [100];
	char classname [100];

  //compare class name from sim file
	                        //with class name froom simulation object
	                        //checks that we are working with
	                        //the correct object
	const XMLCh * ln, * vl; 
	int lnl, vll;

	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);
			if(m_pSimulation)
			{
				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
				    strcpy(sname, XLO(vl));
					m_pSimulation->SetSimName(XLO(vl));
				}
				else if( XMLString::compareNString(ln,XStr("distributemethod").unicodeForm(), lnl) == 0 )
				{
				    strcpy(sname, XLO(vl));
					m_pSimulation->SetDistributeMethod(atoi(XLO(vl)));
				}
				else if( XMLString::compareNString(ln,XStr("nprocs").unicodeForm(), lnl) == 0 )
				{
				    strcpy(sname, XLO(vl));
					m_pSimulation->SetNumProcs(atoi(XLO(vl)));
				}
				else if( XMLString::compareNString(ln,XStr("createmethod").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					m_pSimulation->SetCreateMethod(atoi(sname));
				}
				else if( XMLString::compareNString(ln,XStr("version").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					fversion = (atof(sname));
					if((m_pSimulation->GetVersion())>fversion)
											m_pSimulation = NULL;
				}
				else if( XMLString::compareNString(ln,XStr("class").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					strcpy(classname, m_pSimulation->GetSimClass());
					fversion = (atof(sname));
					if(strcmp(sname, classname)!=0)
										m_pSimulation = NULL;
				}
				else if( XMLString::compareNString(ln,XStr("simulantclass").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					m_pSimulation->SetSimulantClass(sname);

				}
				else if( XMLString::compareNString(ln,XStr("simulanttype").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					m_pSimulation->SetSimulantType(atoi(sname));

				}
			}
		}

		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_SIMULATION);
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_SIMULATION);

		//if(m_pSimulation) m_pSimulation->CreateDefaultParams();

		//At end of creation if simulation exists create default 
		//configuration?

}

void CIoSimulationSAXHandler::StartSimulantElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{





}

void CIoSimulationSAXHandler::StartSimulatorElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int len;
	char sname [100];
	char classname [100];
	int createmethod=0;

	CIoSimulator *pSimulator = NULL;
  //compare class name from sim file
	                        //with class name froom simulation object
	                        //checks that we are working with
	                        //the correct object
	const XMLCh * ln, * vl; 
	int lnl, vll;

	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();
	if(m_pSimulation )
		{		
		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);


				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
							strcpy(sname, XLO(vl));
							if(pSimulator) pSimulator->SetSimulatorName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("class").unicodeForm(), lnl) == 0 )
				{
							strcpy(classname, XLO(vl));
							pSimulator = m_pSimulation->newSimulator(classname);
							pSimulator->SetSimulatorClass(classname);
				}
				else if( XMLString::compareNString(ln,XStr("createmethod").unicodeForm(), lnl) == 0 )
				{
					createmethod = atoi(XLO(vl));
					if(pSimulator) pSimulator->SetCreateMethod(createmethod);
				}


			} //end of loop over attributes
			//if(pSimulator)
			//	pSimulator->CreateDefaultParams();
		}

		if(m_SimulantStack.top()==NULL) m_pSimulant = pSimulator;
		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_SIMULATOR);
		m_SimulantStack.push(pSimulator);
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_SIMULATOR);

		//At end of creation if simulation exists create default 
		//configuration?


}

void CIoSimulationSAXHandler::StartModelElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{

	int len;
	char sname [100];
	char classname [100];
	CIoModel *pModel = NULL;
 //compare class name from sim file
	                        //with class name froom simulation object
	                        //checks that we are working with
	                        //the correct object
	const XMLCh * ln, * vl; 
	int lnl, vll;
    int createmethod=0;
	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();
	if(m_pSimulation)
		{		
		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);


				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					if(pModel) pModel->SetModelName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("class").unicodeForm(), lnl) == 0 )
				{
					strcpy(classname, XLO(vl));
					if(pModel = m_pSimulation->newModel(classname))
					{
						            pModel->Create();
									pModel->SetModelClass(classname);
					}
				}
				else if( XMLString::compareNString(ln,XStr("createmethod").unicodeForm(), lnl) == 0 )
				{
					createmethod = atoi(XLO(vl));
					if(pModel) pModel->SetCreateMethod(createmethod);
				}
			}//end loop over attribs
		    //if(pModel) pModel->CreateDefaultParams();
		} //end of simulation check

		if(m_SimulantStack.top()==NULL) m_pSimulant = (CIoSimulant *)pModel;
		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_MODEL);
		m_SimulantStack.push(pModel);
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_MODEL);

		//At end of creation if simulation exists create default 
		//configuration?

}

void CIoSimulationSAXHandler::StartEntitySetElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{

	int len;
	char sname [100];
	char classname [100];
	CIoModel *pModel = NULL;
	CIoSimulator *pSimulator=NULL;
	CIoEntitySet *pEntitySet=NULL;
 //compare class name from sim file
	                        //with class name froom simulation object
	                        //checks that we are working with
	                        //the correct object
	const XMLCh * ln, * vl; 
	int lnl, vll;
 	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;
	CIoSimulant *pSimulant = m_SimulantStack.top();
	if(pSimulant && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_MODEL))
								pModel = (CIoModel *)pSimulant;
	else if(pSimulant && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
								pSimulator = (CIoSimulator *)pSimulant;

	m_pCPropArray = NULL;
	l=attrs.getLength();
	if(m_pSimulation && (pModel || pSimulator))
		{		
		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);


				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					if(pEntitySet) pEntitySet->SetEntitySetName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("class").unicodeForm(), lnl) == 0 )
				{
					strcpy(classname, XLO(vl));
					if(pModel )
					{
						if(pEntitySet = pModel->newEntitySet(classname))
						{
							pModel->AddEntitySet(pEntitySet);
							//pEntitySet->Create();
							m_pEntitySet=pEntitySet;
						}
					}
					//else if(pSimulator)
					//	pEntitySet = pSimulator->newEntitySet(classname);

					if(pEntitySet)
							pEntitySet->SetEntitySetClass(classname);
				}

			}//end loop over attribs
		    if(pEntitySet) 
			{
				m_pEntitySet = pEntitySet;
				pEntitySet->CreateDefaultParams();
				m_pCPropArray = pEntitySet->m_pProperties;
			}

		} //end of simulation check

		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYSET);
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYSET);




}

void CIoSimulationSAXHandler::StartEntitypropsElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
    int iSimElem;
	CIoSimulant *pSimulant = NULL;

    iSimElem = (int)m_SimElementStack.top();
	m_pCPropArray = (CIoParam *)m_ParamArrayStack.top();

    int iNumProps = 0;
	int len;
	char spropsname [100];
	char snumprops [100];
	int iFlag;

  //compare class name from sim file
	                        //with class name froom simulation object
	                        //checks that we are working with
	                        //the correct object
	const XMLCh * ln, * vl; 
	int lnl, vll;

	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
					strcpy(spropsname, XLO(vl));
				}
				else if( XMLString::compareNString(ln,XStr("numprops").unicodeForm(), lnl) == 0 )
				{
					strcpy(snumprops, XLO(vl));
					iNumProps = atoi(snumprops);
				}
				else if( XMLString::compareNString(ln,XStr("flag").unicodeForm(), lnl) == 0 )
				{
					//strcpy(sflags, XLO(vl));
					iFlag = atoi(XLO(vl));
					SetPropArrayFlag(0,iFlag);
				}			

		}





	if(m_pCPropArray)
	{
		CIoParam *pParam = NULL;
		int iParamIndex = (int)m_ParamIndexStack.top();
		if((pParam = m_pCPropArray->GetParam(iParamIndex)) && (pParam->GetType()==IO_PARAM_ARRAY))
			m_pCPropArray = pParam;
		else
			m_pCPropArray = NULL;
	}
	else
	{
		switch(iSimElem)
		{
			case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			case IO_XMLP_STACK_ELEMENT_ENTITYPROPS :
					if(m_pEntitySet)
						m_pCPropArray = m_pEntitySet->GetEDefaultParams();
				break;
		}//end of simulant case check
	}//end of prop array check
	m_ParamArrayStack.push(m_pCPropArray);
	//m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_PROPS);
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYPROPS);



}



void CIoSimulationSAXHandler::StartEntityTypeSetElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int len;
	char sname [100];
	char classname [100];
	CIoModel *pModel = NULL;
	CIoEntityTypeSet *pEntityTypeSet=NULL;
 //compare class name from sim file
	                        //with class name froom simulation object
	                        //checks that we are working with
	                        //the correct object
	const XMLCh * ln, * vl; 
	int lnl, vll;
 	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;

	if(m_pSimulation && (m_ElementStack.top()== IO_XMLP_STACK_ELEMENT_ENTITYSET) && m_pEntitySet)
	{
	l=attrs.getLength();
		
		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);


				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					if(pEntityTypeSet) pEntityTypeSet->SetEntityTypeSetName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("class").unicodeForm(), lnl) == 0 )
				{
					strcpy(classname, XLO(vl));
					if(m_pEntitySet )
					{
						pEntityTypeSet = m_pEntitySet->newEntityTypeSet(classname);
						m_pEntitySet->SetEntityTypeSet(pEntityTypeSet);
						pEntityTypeSet->CreateEntityTypeSet();
					}
					if(pEntityTypeSet)
					{
							m_pEntityTypeSet = pEntityTypeSet;
							pEntityTypeSet->SetEntityTypeSetClass(classname);
					}
				}


			}//end loop over attribs

		    if(pEntityTypeSet) pEntityTypeSet->CreateDefaultParams();
		} //end of simulation check

		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYTYPESET);




}

void CIoSimulationSAXHandler::StartEntityTypeElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{

	int len;
	char sname [100];
	char classname [100];
	CIoModel *pModel = NULL;
	CIoEntityType *pEntityType=NULL;
 //compare class name from sim file
	                        //with class name froom simulation object
	                        //checks that we are working with
	                        //the correct object
	const XMLCh * ln, * vl; 
	int lnl, vll;
 	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;

	if(m_pSimulation && (m_ElementStack.top()== IO_XMLP_STACK_ELEMENT_ENTITYTYPESET) && m_pEntityTypeSet && m_pEntitySet)
	{
	l=attrs.getLength();
		
		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);


				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					if(pEntityType) pEntityType->SetEntityTypeName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("class").unicodeForm(), lnl) == 0 )
				{
					strcpy(classname, XLO(vl));
					if(m_pEntitySet )
					{
						if(pEntityType = m_pEntitySet->newEntityType(classname))
						{
							m_pEntitySet->AddEntityType(pEntityType);
							pEntityType->CreateEntityType();
						}
					}
					if(pEntityType)
					{
							m_pEntityType = pEntityType;
							pEntityType->SetEntityTypeClass(classname);
					}
				}


			}//end loop over attribs
		    if(pEntityType) pEntityType->CreateDefaultParams();
		} //end of simulation check

		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYTYPE);





}

void CIoSimulationSAXHandler::StartMetadatalistElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	
	
	
	
}


void CIoSimulationSAXHandler::StartMetadataElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	string sname;
	string scontent;
	char csname [1000];
	char cscontent [1000];

	const XMLCh * ln, * vl; 
	int lnl, vll;


		int j,l;

	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
					strcpy(csname, XLO(vl));
					sname=csname;
					
				}
				else if( XMLString::compareNString(ln,XStr("content").unicodeForm(), lnl) == 0 )
				{
					strcpy(cscontent, XLO(vl));
					scontent=cscontent;
				}
		}


	if(m_pSimulation)
		m_pSimulation->AddMetadata(sname,scontent);
	
	
}


void CIoSimulationSAXHandler::StartParamArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
    int iSimElem;
	CIoSimulant *pSimulant = NULL;
	CIoPropertyManager *pman=NULL;
    iSimElem = (int)m_SimElementStack.top();
	m_pCPropArray = (CIoParam *)m_ParamArrayStack.top();

    int iNumProps = 0;
	int len;
	char spropsname [100];
	char snumprops [100];
	int iFlag;

  //compare class name from sim file
	                        //with class name froom simulation object
	                        //checks that we are working with
	                        //the correct object
	const XMLCh * ln, * vl; 
	int lnl, vll;

	char *temp;
	//push simulation element on element stack

	//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
					strcpy(spropsname, XLO(vl));
					
				}
				else if( XMLString::compareNString(ln,XStr("numprops").unicodeForm(), lnl) == 0 )
				{
					strcpy(snumprops, XLO(vl));
					iNumProps = atoi(snumprops);
				}
				else if( XMLString::compareNString(ln,XStr("flag").unicodeForm(), lnl) == 0 )
				{
					//strcpy(sflags, XLO(vl));
					iFlag = atoi(XLO(vl));
					SetPropArrayFlag(0,iFlag);
				}			

		}





	if(m_pCPropArray)
	{
		CIoParam *pParam = NULL;
		int iParamIndex = (int)m_ParamIndexStack.top();
		if((pParam = m_pCPropArray->GetParam(iParamIndex)) && (pParam->GetType()==IO_PARAM_ARRAY))
			m_pCPropArray = pParam;
		else
			m_pCPropArray = NULL;

		if(strlen(spropsname)>0)
			SetPropArrayName(1+iParamIndex,spropsname);
	}
	else
	{
		switch(iSimElem)
		{
			case IO_XMLP_STACK_ELEMENT_SIMULATION :
					if(pman=(CIoPropertyManager *)m_pSimulation)
						m_pCPropArray = m_pSimulation->GetSimProperties();
				break;
			case IO_XMLP_STACK_ELEMENT_SIMULATOR :
					pSimulant = (CIoSimulant *)m_SimulantStack.top();
					if((pman=(CIoPropertyManager *)pSimulant) && pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR )
						m_pCPropArray = pSimulant->GetParams();

				break;
			case IO_XMLP_STACK_ELEMENT_MODEL :
					pSimulant = (CIoSimulant *)m_SimulantStack.top();
					if((pman=(CIoPropertyManager *)pSimulant) && pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_MODEL )
					{
						m_pCPropArray = pSimulant->GetParams();
					}
				break;
			case IO_XMLP_STACK_ELEMENT_MODELCREATOR :
					pSimulant = (CIoSimulant *)m_SimulantStack.top();
					if((pman=(CIoPropertyManager *)pSimulant) && pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_MODEL )
						m_pCPropArray = pSimulant->GetParams();
				break;
			case IO_XMLP_STACK_ELEMENT_ENTITYSET :
					if(pman=(CIoPropertyManager *)m_pEntitySet)
						m_pCPropArray = m_pEntitySet->m_pProperties;
				break;
			case IO_XMLP_STACK_ELEMENT_ENTITYPROPS :
					if(pman=(CIoPropertyManager *)m_pEntitySet)
						m_pCPropArray = m_pEntitySet->GetEDefaultParams();
				break;
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
					if(pman=(CIoPropertyManager *)m_pEntityTypeSet)
						m_pCPropArray = m_pEntityTypeSet->m_pProperties;
				break;
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
					if(pman=(CIoPropertyManager *)m_pEntityType)
						m_pCPropArray = m_pEntityType->m_pProperties;
				break;
		}//end of simulant case check
		if((strlen(spropsname)>0))
			SetPropArrayName(0,spropsname);

		if(m_pCPropArray == NULL )
			m_pCPropArray=new CIoParam();
		int itest=0;
		while(m_pCPropArray && (m_pCPropArray->GetNumParams())<iNumProps)
		{
			m_pCPropArray->AddParam(&itest);
		}
		while(pman && pman->GetNumPropFlags()<iNumProps)
		{
			pman->AddPropFlag(7);
		}
		while(pman && pman->GetNumPropNames()<iNumProps)
		{
			pman->AddPropName("propname");
		}

		//If the parrays array have not been filled
		//then add default params and attributes for these
	}//end of prop array check
	m_ParamArrayStack.push(m_pCPropArray);
	//m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_PROPS);
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_PROPS);

}

void CIoSimulationSAXHandler::SetPropArrayFlag(int index,int iflag)
{
	int iSimElem;
	CIoSimulant *pSimulant = NULL;

    iSimElem = (int)m_SimElementStack.top();
	
	
	switch(iSimElem)
		{
			case IO_XMLP_STACK_ELEMENT_SIMULATION :
					if(m_pSimulation)
					{						
						while(m_pSimulation->GetNumArrayFlags()>index)
									m_pSimulation->AddArrayFlag(7);
						m_pSimulation->SetArrayFlag(index, iflag);													
					}
				break;
			case IO_XMLP_STACK_ELEMENT_SIMULATOR :
					if(pSimulant = (CIoSimulant *)m_SimulantStack.top())
					{
						while(pSimulant->GetNumArrayFlags()>index)
									pSimulant->AddArrayFlag(7);
						pSimulant->SetArrayFlag(index, iflag);
					}
				break;
			case IO_XMLP_STACK_ELEMENT_MODEL :
					if(pSimulant = (CIoSimulant *)m_SimulantStack.top())
					{
						while(pSimulant->GetNumArrayFlags()>index)
									pSimulant->AddArrayFlag(7);
						pSimulant->SetArrayFlag(index, iflag);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYSET :
					if(m_pEntitySet)
					{
						while(m_pEntitySet->GetNumArrayFlags()>index)
									m_pEntitySet->AddArrayFlag(7);
						m_pEntitySet->SetArrayFlag(index, iflag);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYPROPS :
					if(m_pEntitySet)
					{
						while(m_pEntitySet->GetNumEArrayFlags()>index)
									m_pEntitySet->AddEArrayFlag(7);
						m_pEntitySet->SetEArrayFlag(index, iflag);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
					if(m_pEntityTypeSet)
					{
						while(m_pEntityTypeSet->GetNumArrayFlags()>index)
									m_pEntityTypeSet->AddArrayFlag(7);
						m_pEntityTypeSet->SetArrayFlag(index, iflag);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
					{
						while(m_pEntityType->GetNumArrayFlags()>index)
									m_pEntityType->AddArrayFlag(7);
						m_pEntityType->SetArrayFlag(index, iflag);
					}
				break;
		}//end of simulant case check


}

void CIoSimulationSAXHandler::SetPropFlag(int index,int iflag)
{
	int iSimElem;
	CIoSimulant *pSimulant = NULL;

    iSimElem = (int)m_SimElementStack.top();
	
	
	switch(iSimElem)
		{
			case IO_XMLP_STACK_ELEMENT_SIMULATION :
					if(m_pSimulation)
					{						
						while(m_pSimulation->GetNumPropFlags()<index)
									m_pSimulation->AddPropFlag(7);
						m_pSimulation->SetPropertyFlag(index, iflag);													
					}
				break;
			case IO_XMLP_STACK_ELEMENT_SIMULATOR :
					if(pSimulant = (CIoSimulant *)m_SimulantStack.top())
					{
						while(pSimulant->GetNumPropFlags()>index)
									pSimulant->AddPropFlag(7);
						pSimulant->SetPropertyFlag(index, iflag);
					}
				break;
			case IO_XMLP_STACK_ELEMENT_MODEL :
					if(pSimulant = (CIoSimulant *)m_SimulantStack.top())
					{
						while(pSimulant->GetNumPropFlags()>index)
									pSimulant->AddPropFlag(7);
						pSimulant->SetPropertyFlag(index, iflag);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYSET :
					if(m_pEntitySet)
					{
						while(m_pEntitySet->GetNumPropFlags()>index)
									m_pEntitySet->AddPropFlag(7);
						m_pEntitySet->SetPropertyFlag(index, iflag);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYPROPS :
					if(m_pEntitySet)
					{
						while(m_pEntitySet->GetNumEPropFlags()>index)
									m_pEntitySet->AddEPropFlag(7);
						m_pEntitySet->SetEPropertyFlag(index, iflag);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
					if(m_pEntityTypeSet)
					{
						while(m_pEntityTypeSet->GetNumPropFlags()>index)
									m_pEntityTypeSet->AddPropFlag(7);
						m_pEntityTypeSet->SetPropertyFlag(index, iflag);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
					{
						while(m_pEntityType->GetNumPropFlags()>index)
									m_pEntityType->AddPropFlag(7);
						m_pEntityType->SetPropertyFlag(index, iflag);
					}
				break;
		}//end of simulant case check






}


void CIoSimulationSAXHandler::SetPropName(int index, char *sname)
{
	int iSimElem;
	CIoSimulant *pSimulant = NULL;
	
    iSimElem = (int)m_SimElementStack.top();
	
	
	switch(iSimElem)
		{
			case IO_XMLP_STACK_ELEMENT_SIMULATION :
					if(m_pSimulation)
					{						
						while(m_pSimulation->GetNumPropNames()>index)
									m_pSimulation->AddPropName(sname);
						m_pSimulation->SetPropertyName(index, sname);													
					}
					break;
			case IO_XMLP_STACK_ELEMENT_SIMULATOR :
					if(pSimulant = (CIoSimulant *)m_SimulantStack.top())
					{
						while(pSimulant->GetNumPropNames()>index)
									pSimulant->AddPropName(sname);
						pSimulant->SetPropertyName(index, sname);
					}
					break;
			case IO_XMLP_STACK_ELEMENT_MODEL :
					if(pSimulant = (CIoSimulant *)m_SimulantStack.top())
					{
						while(pSimulant->GetNumPropNames()>index)
									pSimulant->AddPropName(sname);
						pSimulant->SetPropertyName(index, sname);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYSET :
					if(m_pEntitySet)
					{
						while(m_pEntitySet->GetNumPropNames()>index)
									m_pEntitySet->AddPropName(sname);
						m_pEntitySet->SetPropertyName(index, sname);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYPROPS :
					if(m_pEntitySet)
					{
						while(m_pEntitySet->GetNumEPropNames()>index)
									m_pEntitySet->AddEPropName(sname);
						m_pEntitySet->SetEPropertyName(index, sname);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
					if(m_pEntityTypeSet)
					{
						while(m_pEntityTypeSet->GetNumPropNames()>index)
									m_pEntityTypeSet->AddPropName(sname);
						m_pEntityTypeSet->SetPropertyName(index, sname);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
					{
						while(m_pEntityType->GetNumPropNames()>index)
									m_pEntityType->AddPropName(sname);
						m_pEntityType->SetPropertyName(index, sname);
					}
				break;
		}//end of simulant case check


}


void CIoSimulationSAXHandler::SetPropArrayName(int index, char *sname)
{
	int iSimElem;
	CIoSimulant *pSimulant = NULL;
	
    iSimElem = (int)m_SimElementStack.top();
	
	
	switch(iSimElem)
		{
			case IO_XMLP_STACK_ELEMENT_SIMULATION :
					if(m_pSimulation)
					{						
						while(m_pSimulation->GetNumArrayNames()>index)
									m_pSimulation->AddArrayName(sname);
						m_pSimulation->SetArrayName(index, sname);													
					}
					break;
			case IO_XMLP_STACK_ELEMENT_SIMULATOR :
					if(pSimulant = (CIoSimulant *)m_SimulantStack.top())
					{
						while(pSimulant->GetNumArrayNames()>index)
									pSimulant->AddArrayName(sname);
						pSimulant->SetArrayName(index, sname);
					}
					break;
			case IO_XMLP_STACK_ELEMENT_MODEL :
					if(pSimulant = (CIoSimulant *)m_SimulantStack.top())
					{
						while(pSimulant->GetNumArrayNames()>index)
									pSimulant->AddArrayName(sname);
						pSimulant->SetArrayName(index, sname);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYSET :
					if(m_pEntitySet)
					{
						while(m_pEntitySet->GetNumArrayNames()>index)
									m_pEntitySet->AddArrayName(sname);
						m_pEntitySet->SetArrayName(index, sname);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYPROPS :
					if(m_pEntitySet)
					{
						while(m_pEntitySet->GetNumEArrayNames()>index)
									m_pEntitySet->AddEArrayName(sname);
						m_pEntitySet->SetEArrayName(index, sname);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
					if(m_pEntityTypeSet)
					{
						while(m_pEntityTypeSet->GetNumArrayNames()>index)
									m_pEntityTypeSet->AddArrayName(sname);
						m_pEntityTypeSet->SetArrayName(index, sname);
					}
			case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
					{
						while(m_pEntityType->GetNumArrayNames()>index)
									m_pEntityType->AddArrayName(sname);
						m_pEntityType->SetArrayName(index, sname);
					}
				break;
		}//end of simulant case check


}


void CIoSimulationSAXHandler::StartParamElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int iPropIndex=-1;
	const XMLCh * ln, * vl; 
	int lnl, vll;
	int iFlag=-1;
	string sinfile="";
	string soutfile="";
	string sname="";
	string stype="";
	m_pCPropArray = (CIoParam *)m_ParamArrayStack.top();
	CIoPropertyManager *pPropMan=NULL;

		//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();

	if(m_pCPropArray)
	{		
		switch(m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATION:
				pPropMan = (CIoPropertyManager *)m_pSimulation;
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULANT:
		case IO_XMLP_STACK_ELEMENT_MODEL:
		case IO_XMLP_STACK_ELEMENT_SIMULATOR:
				pPropMan = (CIoPropertyManager *)m_pSimulant;

			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET:
				pPropMan = (CIoPropertyManager *)m_pEntitySet;
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET:
				pPropMan = (CIoPropertyManager *)m_pEntityTypeSet;
			break;



		}

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
				{
							iPropIndex = atoi(XLO(vl));
				}
				else if( XMLString::compareNString(ln,XStr("flag").unicodeForm(), lnl) == 0 )
				{
					//strcpy(sflags, XLO(vl));
					iFlag = atoi(XLO(vl));

					
				}
				else if( XMLString::compareNString(ln,XStr("infile").unicodeForm(), lnl) == 0 )
				{
					//strcpy(sflags, XLO(vl));
					sinfile = XLO(vl);
					if(pPropMan) pPropMan->SetPropInfilename(iPropIndex,sinfile);
					
				}
				else if( XMLString::compareNString(ln,XStr("outfile").unicodeForm(), lnl) == 0 )
				{
					//strcpy(sflags, XLO(vl));
					soutfile = XLO(vl);
					if(pPropMan) pPropMan->SetPropOutfilename(iPropIndex,soutfile);
					
				}
				else if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
					//strcpy(sflags, XLO(vl));
					sname = XLO(vl);
					if(pPropMan) pPropMan->SetPropertyName(iPropIndex,(char *)sname.c_str());
					
				}
				else if( XMLString::compareNString(ln,XStr("type").unicodeForm(), lnl) == 0 )
				{
					//strcpy(sflags, XLO(vl));
					stype = XLO(vl);
					
				}
			}
		if(iFlag>=0 && iPropIndex>=0)
			SetPropFlag(iPropIndex,iFlag);
		
		//m_ParamStack.push(m_pCprop);
		m_pCPropArray = (CIoParam *)m_ParamArrayStack.top();
		m_pCprop = m_pCPropArray->GetParam(iPropIndex);

		//by setting the value in the appropriate way i.e. b overidding SetParam
		//the param is set to the correct type and value
		//the input file as first line should have the type fo the parameter
		//may be the following should be in the stream operator for param
		if(m_pCprop==NULL)
		{
		if(strlen((char *)stype.c_str())>0)
		{
			if(strcmp((char *)stype.c_str(),"int"))
			{
				int it=0;
				m_pCprop = new CIoParam(&it);
			}
			else if(strcmp(stype.c_str(),"float"))
			{
				float ft=0;
				m_pCprop = new CIoParam(&ft);
			}
			else if(strcmp(stype.c_str(),"vec"))
			{
				vec vt(3,0);
				m_pCprop = new CIoParam(&vt);
			}
			else if(strcmp(stype.c_str(),"mat"))
			{
				matrix mt(2,2,0,0);
				m_pCprop = new CIoParam(&mt);
			}
			else if(strcmp(stype.c_str(),"string"))
			{
				
				m_pCprop = new CIoParam("stest");
			}
			else if(strcmp(stype.c_str(),"stringarray"))
			{
				IoStringArray sat("st1");
				sat.AddString("st2");
				m_pCprop = new CIoParam(&sat);
			}
			else if(strcmp(stype.c_str(),"mmat3d"))
			{
				mmat3d mm3d(2,2,2,2,2,0,0);
				m_pCprop = new CIoParam(&mm3d);
			}
			else
				m_pCprop = new CIoParam();

			m_pCPropArray->AddParam(m_pCprop);
		}
		}

		if(m_pCprop && (sinfile.length()>0))
		{
			ifstream infile;
			infile.open (sinfile.c_str(), ifstream::in);
			infile >> *m_pCprop;
			infile.close();
		}

		m_ParamStack.push(m_pCprop);
		//m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_PROP);
		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_PROP);
		if(m_pCprop && (m_pCprop->GetType()==IO_PARAM_ARRAY))
								m_ParamIndexStack.push(iPropIndex);

		
	}


}

void CIoSimulationSAXHandler::StartIntElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{

	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_INT);


}

void CIoSimulationSAXHandler::StartArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	//if(m_pCvec) delete m_pCvec;
	CIoParam *pCprop = (CIoParam *)m_ParamStack.top();
	
	int iPropIndex;
	const XMLCh * ln, * vl; 
	int lnl, vll;
	int isize=0;
	CIoParam *pArray=new CIoParam;
		//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();


		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

							
				
	
				if( XMLString::compareNString(ln,XStr("n").unicodeForm(), lnl) == 0 )
				{
							isize = atoi(XLO(vl));
							//vec pv(iarraysize,0);
							//pCprop->SetParam(&pv);
							//m_pCvec = new vec(m_vecsize, 0);
							
				}
							
							
					
			}
	
	
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_ARRAY);
	m_ArraySizeStack.push(isize);
	m_ArrayStack.push(pArray);
	m_pCArray=pArray;


}

void CIoSimulationSAXHandler::StartFloatElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_FLOAT);
}

void CIoSimulationSAXHandler::StartStringElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_STRING);
}

void CIoSimulationSAXHandler::StartStringArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_STRINGARRAY);
}


void CIoSimulationSAXHandler::StartVectorElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int iPropIndex;
	const XMLCh * ln, * vl; 
	int lnl, vll;

		//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();


		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("size").unicodeForm(), lnl) == 0 )
							m_vecsize = atoi(XLO(vl));
					
			}
		
		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_VECTOR);
}

void CIoSimulationSAXHandler::StartVecElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	//if(m_pCvec) delete m_pCvec;
	CIoParam *pCprop = (CIoParam *)m_ParamStack.top();
	
		int iPropIndex;
	const XMLCh * ln, * vl; 
	int lnl, vll;

		//Get the attributes and set these to the simulation
	int j,l;

	l=attrs.getLength();


		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

							
				
	
				if( XMLString::compareNString(ln,XStr("size").unicodeForm(), lnl) == 0 )
				{
							m_vecsize = atoi(XLO(vl));
							vec pv(m_vecsize,0);
							pCprop->SetParam(&pv);
							//m_pCvec = new vec(m_vecsize, 0);
				}
							
							
					
			}
	
	
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_VEC);
}


void CIoSimulationSAXHandler::StartMatrixElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{


	int iPropIndex;
	const XMLCh * ln, * vl; 
	int lnl, vll;

	//Get the attributes and set these to the simulation
	int j,l;

	m_matcols = 0;
	m_matrows = 0;
	m_matcurrentrow = 0;
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_MATRIX);

	l=attrs.getLength();


		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("cols").unicodeForm(), lnl) == 0 )
							m_matcols = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("rows").unicodeForm(), lnl) == 0 )
							m_matrows = atoi(XLO(vl));
					
			}
		//m_vecsize = m_matcols;
		//if(m_pCmat) delete m_pCmat;
		//m_pCmat = new matrix(m_matrows, m_matcols, 0, 0);
		
		
}


void CIoSimulationSAXHandler::Startmmat3dElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{


	int iPropIndex;
	const XMLCh * ln, * vl; 
	int lnl, vll;

	//Get the attributes and set these to the simulation
	int j,l;

	m_matcols = 0;
	m_matrows = 0;
	m_mm3r=0;
	m_mm3c=0;
	m_mm3d=0;
	m_matcurrentrow = 0;
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_MMAT3D);

	l=attrs.getLength();


		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("mcol").unicodeForm(), lnl) == 0 )
							m_matcols = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("mrow").unicodeForm(), lnl) == 0 )
							m_matrows = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("row").unicodeForm(), lnl) == 0 )
							m_mm3r = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("col").unicodeForm(), lnl) == 0 )
							m_mm3c = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("dep").unicodeForm(), lnl) == 0 )
							m_mm3d = atoi(XLO(vl));

					
			}
		//m_vecsize = m_matcols;
		//if(m_pCmat) delete m_pCmat;
		//m_pCmat = new matrix(m_matrows, m_matcols, 0, 0);
		
		
}


void CIoSimulationSAXHandler::StartLinksElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	
	
}

void CIoSimulationSAXHandler::StartLinkElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int iSimElem;
	CIoSimulator *psimulator=NULL;

    iSimElem = (int)m_SimElementStack.top();
	if(iSimElem==IO_XMLP_STACK_ELEMENT_SIMULATOR)
	{			
		psimulator = (CIoSimulator *)m_SimulantStack.top();
		m_psimulantlink=new CIoSimulantLink();



					
	}
	
	
}

void CIoSimulationSAXHandler::StartFromElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int iSimElem;

	const XMLCh * ln, * vl; 
	int l, lnl, vll;

	CIoSimulator *psimulator=NULL;

	int iparamid;
	string sparammap;
	int ientitysetid;
	int ientityid;	
	int isimulantid;
	string ssimulantmap;

    iSimElem = (int)m_SimElementStack.top();
	if((iSimElem==IO_XMLP_STACK_ELEMENT_SIMULATOR) &&  (m_psimulantlink !=NULL))
	{			
		psimulator = (CIoSimulator *)m_SimulantStack.top();
		m_pport=(CIoSimulantPort *)new CIoSimulantPort();
        
			l=attrs.getLength();


		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("simulantmap").unicodeForm(), lnl) == 0 )
							ssimulantmap=(XLO(vl));
				if( XMLString::compareNString(ln,XStr("simulantid").unicodeForm(), lnl) == 0 )
							isimulantid = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("parammap").unicodeForm(), lnl) == 0 )
							sparammap=(XLO(vl));
				if( XMLString::compareNString(ln,XStr("paramid").unicodeForm(), lnl) == 0 )
							iparamid = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("entitysetid").unicodeForm(), lnl) == 0 )
							ientitysetid = atoi(XLO(vl));

					
		}

		m_pport->SetParamID(iparamid);
		m_pport->SetParammap(sparammap);
		m_pport->SetSimulantID(isimulantid);
		m_pport->SetSimulantmap(ssimulantmap);
		m_pport->SetEntitySetID(ientitysetid);
		

		m_psimulantlink->SetFromPort(m_pport);
		m_pport->m_simulant=psimulator->GetChildSimulant(isimulantid,(char *)ssimulantmap.c_str());


					
	}	
	
	
}

void CIoSimulationSAXHandler::StartToElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int iSimElem;

	const XMLCh * ln, * vl; 
	int l,lnl, vll;

	CIoSimulator *psimulator=NULL;

	int iparamid;
	string sparammap;
	int ientitysetid;
	int ientityid;	
	int isimulantid;
	string ssimulantmap;

    iSimElem = (int)m_SimElementStack.top();
	if((iSimElem==IO_XMLP_STACK_ELEMENT_SIMULATOR) &&  (m_psimulantlink !=NULL))
	{			
		psimulator = (CIoSimulator *)m_SimulantStack.top();
		m_pport=(CIoSimulantPort *)new CIoSimulantPort();
        
			l=attrs.getLength();


		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("simulantmap").unicodeForm(), lnl) == 0 )
							ssimulantmap= (XLO(vl));
				if( XMLString::compareNString(ln,XStr("simulantid").unicodeForm(), lnl) == 0 )
							isimulantid = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("parammap").unicodeForm(), lnl) == 0 )
							sparammap=(XLO(vl));
				if( XMLString::compareNString(ln,XStr("paramid").unicodeForm(), lnl) == 0 )
							iparamid = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("entitysetid").unicodeForm(), lnl) == 0 )
							ientitysetid = atoi(XLO(vl));

					
		}

		m_pport->SetParamID(iparamid);
		m_pport->SetParammap(sparammap);
		m_pport->SetSimulantID(isimulantid);
		m_pport->SetSimulantmap(ssimulantmap);
		m_pport->SetEntitySetID(ientitysetid);
		m_pport->m_simulant=psimulator->GetChildSimulant(isimulantid,(char *)ssimulantmap.c_str());

		m_psimulantlink->SetToPort(m_pport);


					
	}	
	
	
	
	
}



void CIoSimulationSAXHandler::endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	if ((XMLString::compareIString(XLO(localname), "int")) == 0)
		EndIntElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "array")) == 0)
		EndArrayElement(uri, localname, qname);	
	else if ((XMLString::compareIString(XLO(localname), "vec")) == 0)
		EndVecElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "float")) == 0)
		EndFloatElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "string")) == 0)
		EndStringElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "stringarray")) == 0)
		EndStringArrayElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "mat")) == 0)
		EndMatrixElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "mmat3d")) == 0)
		Endmmat3dElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "vector")) == 0)
		EndVectorElement(uri, localname, qname);
	else if((XMLString::compareIString(XLO(localname), "model")) == 0)
		EndModelElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "prop")) == 0)
		endParamElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "metadatalist")) == 0)
		EndMetadatalistElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "metadata")) == 0)
		EndMetadataElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "links")) == 0)
		EndLinksElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "link")) == 0)
		EndLinkElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "from")) == 0)
		EndFromElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "to")) == 0)
		EndToElement(uri, localname, qname);
		
	else if ((XMLString::compareIString(XLO(localname), "props")) == 0)
		endParamArrayElement(uri, localname, qname);
		else if((XMLString::compareIString(XLO(localname), "simulator")) == 0)
	{
		CIoSimulant *pSimulant=NULL, *pParentSimulant=NULL;
		//Determine parent of simulator
		if(m_pSimulant == m_SimulantStack.top())
		{
			m_pSimulant = (CIoSimulant *)m_SimulantStack.top();
			//pop the stack 
			m_SimulantStack.pop();
		}
		else
		{
			//Determine the parent of the simulator
			//current has to be top simulant in stack
			//add simulant to parent set its parent
			//finally pop the stack
			if(!m_SimulantStack.empty())
			{
				pSimulant = (CIoSimulant *)m_SimulantStack.top();
				m_SimulantStack.pop();
				if(!m_SimulantStack.empty())
					pParentSimulant = (CIoSimulant *)m_SimulantStack.top();
				if(pParentSimulant && pSimulant)
				{
					pParentSimulant->Add(pSimulant);
					pSimulant->SetParentSimulant(pParentSimulant);
				}
			}
		}//end of adding simulant to parent and setting parent
			

		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_SIMULATOR))	m_ElementStack.pop();
		if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_SIMULATOR))	m_SimElementStack.pop();
		if(!m_SimulantStack.empty() && ((CIoSimulant *)(m_SimulantStack.top())!= NULL))	m_SimulantStack.pop();

	}//if end element is simulator
	else if((XMLString::compareIString(XLO(localname), "modelcreator")) == 0)
	{
		CIoSimulant *pSimulant=NULL, *pParentSimulant=NULL;
		//Determine parent of simulator
		if(m_pSimulant == m_SimulantStack.top())
		{
			//m_pSimulant = (CIoSimulant *)m_SimulantStack.top();
			//pop the stack 
			m_SimulantStack.pop();
		}
		else
		{
			//Determine the parent of the simulator
			//current has to be top simulant in stack
			//add simulant to parent set its parent
			//finally pop the stack
			if(!m_SimulantStack.empty())
			{
				pSimulant = (CIoSimulant *)m_SimulantStack.top();
				m_SimulantStack.pop();
				if(!m_SimulantStack.empty())
					pParentSimulant = (CIoSimulant *)m_SimulantStack.top();
				if(pParentSimulant && pSimulant)
				{
					pParentSimulant->Add(pSimulant);
					pSimulant->SetParentSimulant(pParentSimulant);
				}
			}
		}//end of adding simulant to parent and setting parent
			

		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_MODELCREATOR))	m_ElementStack.pop();
		if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_MODELCREATOR))	m_SimElementStack.pop();
		if(!m_SimulantStack.empty() && ((CIoSimulant *)(m_SimulantStack.top())!= NULL))	m_SimulantStack.pop();
	}//if end element is modelcreator
	else if ((XMLString::compareIString(XLO(localname), "simulation")) == 0)
	{
		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_SIMULATION))	m_ElementStack.pop();
		if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_SIMULATION))	m_SimElementStack.pop();

		//At this point there had only better be one simulant left on the stack
		//so set this simulant to the simulation
        if(m_pSimulation && m_pSimulant)
		{
			m_pSimulation->SetSimulant(m_pSimulant);
			//m_pSimulation->CreateDefaultConfig();
		}
	}
	else if((XMLString::compareIString(XLO(localname), "steps")) == 0)
	{
		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_STEPS))	m_ElementStack.pop();
	}
	else if((XMLString::compareIString(XLO(localname), "fileprops")) == 0)
	{
		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_FILEPROPS))	m_ElementStack.pop();
	}
	else if((XMLString::compareIString(XLO(localname), "entityprops")) == 0)
	{
		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITYPROPS))	m_ElementStack.pop();
		if(!m_ParamArrayStack.empty()) m_ParamArrayStack.pop();
	}
	else if ((XMLString::compareIString(XLO(localname), "entityset")) == 0)
	{
		if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITYSET))	
						m_SimElementStack.pop();
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITYSET))	
		{
			m_ElementStack.pop();
			m_pEntitySet->Create();
			m_pEntitySet=NULL;
			m_inumentities=0;
		}
	}
	else if ((XMLString::compareIString(XLO(localname), "entitytypeset")) == 0)
	{
	if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITYTYPESET))	
		{
			m_ElementStack.pop();
			m_pEntityTypeSet=NULL;
			m_inumentitytypes=0;
		}
	}
	else if ((XMLString::compareIString(XLO(localname), "entitytype")) == 0)
	{
	if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITYTYPE))	
		{
			m_ElementStack.pop();
			//if(m_pEntityTypeSet)
			//	m_pEntityTypeSet->AddEntityType(m_pEntityType);
			m_pEntityType=NULL;
		}
	}
	//else if((XMLString::compareIString(XLO(localname), "simulant")) == 0);


}

void CIoSimulationSAXHandler::endParamArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_PROPS))	m_ElementStack.pop();
	//if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_PROPS))	m_SimElementStack.pop();
	//std::cout << *m_pCPropArray << std::endl;
	if(!m_ParamArrayStack.empty()) m_ParamArrayStack.pop();
}

void CIoSimulationSAXHandler::endParamElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	int iparamindex;

	//if(!m_ParamIndexStack.empty())	iparamindex = (int)m_ParamIndexStack.pop();	
	if((m_ParamStack.size()>1))
	{
		m_pCprop = (CIoParam *)m_ParamStack.top();
		m_ParamStack.pop();
	}
	else
		m_pCprop = NULL;

	if(m_pCprop && (m_pCprop->GetType()==IO_PARAM_ARRAY))
								m_ParamIndexStack.pop();

	if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_PROP))	m_ElementStack.pop();
	m_pCprop = NULL;
}

void CIoSimulationSAXHandler::EndIntElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_INT))	m_ElementStack.pop();
			if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
			{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top()) /* && (m_pCprop->GetType()==IO_PARAM_VEC)*/)
						m_pCprop->SetParam(&m_iCint);
			}			
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_ARRAY)
			{
				//update the parameter
				if((m_pCArray = (CIoParam *)m_ArrayStack.top()) /* && (m_pCArray->GetType()==IO_PARAM_ARRAY)*/)
						m_pCArray->AddParam(&m_iCint);
			}
}

void CIoSimulationSAXHandler::EndArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ARRAY))	m_ElementStack.pop();
			if(!m_ArraySizeStack.empty() )	m_ArraySizeStack.pop();
			CIoParam *pArray=NULL;
			
			if(!m_ArrayStack.empty())
			{
				m_pCArray=(CIoParam *)(m_ArrayStack.top());
				m_ArrayStack.pop();
				//std::cout << *m_pCArray << std::endl;
			}
			if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
			{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top())  /*&& (m_pCprop->GetType()==IO_PARAM_ARRAY)*/)
				{
						//std::cout << *m_pCprop << std::endl;
						//std::cout << *m_pCArray << std::endl;
						m_pCprop->SetParam(m_pCArray);
						//std::cout << *m_pCprop << std::endl;
						int jj;
						for(int ii=0;ii<10;ii++) jj++;//dummy end
				}
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_ARRAY)
			{
				//update the parameter
				if((pArray = (CIoParam *)m_ArrayStack.top())  /*&& (m_pCArray->GetType()==IO_PARAM_ARRAY)*/)
						pArray->AddParam(m_pCArray);
			}
			
									
			if(m_pCArray) 
			{
				delete m_pCArray;
				m_pCArray = NULL;
			}



}

void CIoSimulationSAXHandler::EndFloatElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_FLOAT))	m_ElementStack.pop();
			
			if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
			{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top()) /* && (m_pCprop->GetType()==IO_PARAM_VEC)*/)
						m_pCprop->SetParam(&m_fCfloat);
			}			
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_ARRAY)
			{
				//update the parameter
				if((m_pCArray = (CIoParam *)m_ArrayStack.top()) /* && (m_pCArray->GetType()==IO_PARAM_ARRAY)*/)
						m_pCArray->AddParam(&m_fCfloat);
			}
			

}

void CIoSimulationSAXHandler::EndStringElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_STRING))	m_ElementStack.pop();
			if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
			{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top()) /* && (m_pCprop->GetType()==IO_PARAM_VEC)*/)
				{
						m_pCprop->SetParam(m_sb.str().c_str());
						m_sb.str("");
				}
			}			
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_ARRAY)
			{
				//update the parameter
				if((m_pCArray = (CIoParam *)m_ArrayStack.top()) /* && (m_pCArray->GetType()==IO_PARAM_ARRAY)*/)
				{
						m_pCArray->AddParam(m_sb.str().c_str());
						m_sb.str("");
				}
			}

}

void CIoSimulationSAXHandler::EndStringArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_STRINGARRAY))	m_ElementStack.pop();
			if(m_pStringArray && m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
			{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top()) /* && (m_pCprop->GetType()==IO_PARAM_VEC)*/)
				{
						m_pCprop->SetParam(m_pStringArray);
						delete m_pStringArray;
						m_pStringArray=NULL;
						std::cout<<"m_pCprop: " << *m_pCprop << std::endl;
				}
			}			
			else if(m_pStringArray && m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_ARRAY)
			{
				//update the parameter
				if((m_pCArray = (CIoParam *)m_ArrayStack.top()) /* && (m_pCArray->GetType()==IO_PARAM_ARRAY)*/)
				{
						m_pCArray->AddParam(m_pStringArray);
						std::cout<<"m_pCArray: " << *m_pCArray << std::endl;

						delete m_pStringArray;
						m_pStringArray=NULL;
				}
			}

}




void CIoSimulationSAXHandler::EndVectorElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_VECTOR))	m_ElementStack.pop();

}

void CIoSimulationSAXHandler::EndVecElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_VEC))	m_ElementStack.pop();
			if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_MATRIX)
			{
				//Update the matrix

					if(m_pCmat && m_pCvec && m_matcurrentrow<m_matrows)
						for(int i=0; i<m_matcols; i++)
							m_pCmat->setval(m_matcurrentrow, i, m_pCvec->get(i));

					m_matcurrentrow++;
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_VECTOR)
			{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top())  && (m_pCprop->GetType()==IO_PARAM_VEC))
						m_pCprop->SetParam(m_pCvec);
						m_vecsize = 0;
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
			{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top())  && (m_pCprop->GetType()==IO_PARAM_VEC))
						m_pCprop->SetParam(m_pCvec);
						m_vecsize = 0;
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_ARRAY)
			{
				//update the parameter
				if((m_pCArray = (CIoParam *)m_ArrayStack.top()) /* && (m_pCArray->GetType()==IO_PARAM_ARRAY)*/)
						m_pCArray->AddParam(m_pCvec);
			}						
			if(m_pCvec) 
			{
				delete m_pCvec;
				m_pCvec = NULL;
			}



}

void CIoSimulationSAXHandler::EndMatrixElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
		/*if((m_pCprop = (CIoParam *)m_ParamStack.top())  && (m_pCprop->GetType()==IO_PARAM_MAT))
		{
					m_pCprop->SetParam(m_pCmat);
		}*/
		/*if(m_pCmat)
		{
			delete m_pCmat;
			m_pCmat = NULL;
		}
		m_matcols = 0;
		m_matrows = 0;
		m_matcurrentrow = 0;
		m_pCmat = NULL;*/
		
		
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_MATRIX))	m_ElementStack.pop();
		if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
		{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top()) /* && (m_pCprop->GetType()==IO_PARAM_VEC)*/)
						m_pCprop->SetParam(m_pCmat);
		}			
		else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_ARRAY)
		{
				//update the parameter
				if((m_pCArray = (CIoParam *)m_ArrayStack.top()) /* && (m_pCArray->GetType()==IO_PARAM_ARRAY)*/)
				{
					    //:cout << *m_pCArray <<std::endl;
					    //std::cout << *m_pCmat << std::endl;
						m_pCArray->AddParam(m_pCmat);
						//std::cout << *m_pCArray <<std::endl;
						
				}
		}




}

void CIoSimulationSAXHandler::Endmmat3dElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
		/*if((m_pCprop = (CIoParam *)m_ParamStack.top())  && (m_pCprop->GetType()==IO_PARAM_MAT))
		{
					m_pCprop->SetParam(m_pCmat);
		}*/
		/*if(m_pCmat)
		{
			delete m_pCmat;
			m_pCmat = NULL;
		}
		m_matcols = 0;
		m_matrows = 0;
		m_matcurrentrow = 0;
		m_pCmat = NULL;*/
		
		
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_MATRIX))	m_ElementStack.pop();
		if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
		{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top()) /* && (m_pCprop->GetType()==IO_PARAM_VEC)*/)
						m_pCprop->SetParam(m_pCmmat3d);
		}			
		else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_ARRAY)
		{
				//update the parameter
				if((m_pCArray = (CIoParam *)m_ArrayStack.top()) /* && (m_pCArray->GetType()==IO_PARAM_ARRAY)*/)
				{
					    //:cout << *m_pCArray <<std::endl;
					    //std::cout << *m_pCmat << std::endl;
						m_pCArray->AddParam(m_pCmmat3d);
						//std::cout << *m_pCArray <<std::endl;
						
				}
		}




}



void CIoSimulationSAXHandler::EndModelElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{

		CIoSimulant *pSimulant=NULL, *pParentSimulant=NULL;

		//Determine parent of simulator
		if(m_pSimulant == m_SimulantStack.top())
		{
			m_pSimulant = (CIoSimulant *)m_SimulantStack.top();
			//pop the stack 
			m_SimulantStack.pop();
		}
		else
		{
			//Determine the parent of the simulator
			//current has to be top simulant in stack
			//add simulant to parent set its parent
			//finally pop the stack
			if(!m_SimulantStack.empty())
			{
				pSimulant = (CIoSimulant *)m_SimulantStack.top();
				m_SimulantStack.pop();
				if(!m_SimulantStack.empty())
					pParentSimulant = (CIoSimulant *)m_SimulantStack.top();
				if(pParentSimulant && pSimulant)
				{
					pParentSimulant->Add(pSimulant);
					pSimulant->SetParentSimulant(pParentSimulant);
				}
			}
		}//end of adding simulant to parent and setting parent
			

		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_MODEL))	m_ElementStack.pop();
		if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_MODEL))	m_SimElementStack.pop();
		if(!m_SimulantStack.empty() && ((CIoSimulant *)(m_SimulantStack.top())!= NULL))	m_SimulantStack.pop();

}

void CIoSimulationSAXHandler::EndMetadatalistElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	
	
	
	
}


void CIoSimulationSAXHandler::EndMetadataElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	
	
	
}

void CIoSimulationSAXHandler::EndLinksElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{


}

void CIoSimulationSAXHandler::EndLinkElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	if(m_psimulantlink!=NULL)
	{
		delete m_psimulantlink;
		m_psimulantlink=NULL;
	}

}

void CIoSimulationSAXHandler::EndFromElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	if(m_pport!=NULL)
	{
		delete m_pport;
		m_pport=NULL;
	}
}

void CIoSimulationSAXHandler::EndToElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	if(m_pport!=NULL)
	{
		delete m_pport;
		m_pport=NULL;
	}

}
