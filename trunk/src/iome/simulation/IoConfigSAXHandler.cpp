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

#include <iome/simulation/IoConfigSAXHandler.h>
#define XLO(str) StrX(str).localForm()

CIoParam *CIoConfigSAXHandler::m_pCArray=NULL;
CIoParam *CIoConfigSAXHandler::m_pCprop=NULL;
CIoParam *CIoConfigSAXHandler::m_pCPropArray=NULL;
int	CIoConfigSAXHandler::m_ientitysetcount=0;
CIoEntity *CIoConfigSAXHandler::m_pEntity=NULL;
CIoEntitySet *CIoConfigSAXHandler::m_pEntitySet = NULL;
int	CIoConfigSAXHandler::m_inumentities=0;
int	CIoConfigSAXHandler::m_iPropCount=0;
vec	*CIoConfigSAXHandler::m_pCvec=NULL;
matrix	*CIoConfigSAXHandler::m_pCmat=NULL;
mmat3d	*CIoConfigSAXHandler::m_pCmmat3d=NULL;
IoStringArray *CIoConfigSAXHandler::m_pStringArray=NULL;


int CIoConfigSAXHandler::m_mm3r=0;
int CIoConfigSAXHandler::m_mm3c=0;
int CIoConfigSAXHandler::m_mm3d=0;


CIoConfigSAXHandler::CIoConfigSAXHandler()
{
		m_pSimulation = NULL;
		fSawErrors = true;
		m_ElementStack.push(0);
		m_ParamStack.push(NULL);
		m_ParamArrayStack.push(NULL);
		m_ArrayStack.push(NULL);
		
		m_SimElementStack.push(0);
		m_SimulantStack.push(NULL);
		m_pSimulant = NULL;

		m_ParamIndexStack.push(-1);

	    //read in variables
	    m_iCint=0;
		m_fCfloat=0;
		m_pCvec=NULL;
		m_pCmat=NULL;
		m_pCmmat3d=NULL;
		m_pCstring=NULL;
		m_pStringArray=NULL;
		
		//m_pCprop=NULL;
		//m_pCPropArray=NULL;

		m_vecsize=0;
		m_matrows=0;
		m_matcols=0;
		m_matcurrentrow=0;
		m_istep=0;
		m_icycle=0;
		m_sb.str("");
		//m_pEntitySet = NULL;
		//m_inumentities=0;
		//m_ientitysetcount=0;
		//m_pEntity=NULL;
		m_iNoEntities=0;
		m_iSimulationCount=0;
}

CIoConfigSAXHandler::CIoConfigSAXHandler(CIoXMLSimulation *pSimulation):
		fSawErrors(false)
{
	if(pSimulation)
		m_pSimulation = pSimulation;
	/*else
	{
		m_pSimulation = NULL;
		fSawErrors = true;
	}*/
	m_ElementStack.push(0);
	m_ParamStack.push(NULL);
	m_ArrayStack.push(NULL);
	
	m_SimElementStack.push(0);
	m_SimulantStack.push(NULL);
	m_ParamArrayStack.push(NULL);
	m_ParamIndexStack.push(-1);
m_iNoEntities=0;
m_iSimulationCount=0;
	//read in variables
	m_iCint=0;
	m_fCfloat=0;
	m_pCvec=NULL;
	m_pCmat=NULL;
	m_pCstring=NULL;
	m_pCprop=NULL;
	m_pCPropArray=NULL;
	m_pCArray=NULL;
	m_index=0;
	m_pStringArray=NULL;

	m_vecsize=0;
	m_matrows=0;
	m_matcols=0;

	m_iPropCount =0;

	m_istep=0;
	m_icycle=0;
	m_sb.str("");


}

CIoConfigSAXHandler::~CIoConfigSAXHandler(void)
{
		if(m_pCvec) delete m_pCvec;
		if(m_pCmat) delete m_pCmat;
		if(m_pCstring) delete [] m_pCstring;
		if(m_pStringArray) delete m_pStringArray;
		
}

// ---------------------------------------------------------------------------
//  SAX2CountHandlers: Implementation of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------
void CIoConfigSAXHandler::startElement(const XMLCh* const uri
                                   , const XMLCh* const localname
                                   , const XMLCh* const qname
                                   , const Attributes& attrs)
{
	
	if ((XMLString::compareIString(XLO(localname), "simulation")) == 0)
						StartSimulationElement(uri, localname, qname, attrs);
	else if(( XMLString::compareIString(XLO(localname),"steps")) == 0 )
						m_ElementStack.push(IO_XMLP_STACK_ELEMENT_STEPS);
	//else if((XMLString::compareIString(XLO(localname), "simulant")) == 0);
	else if((XMLString::compareIString(XLO(localname), "simulator")) == 0)
							StartSimulatorElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "model")) == 0)
							StartModelElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "props")) == 0)
							StartParamArrayElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "prop")) == 0)
							StartParamElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "int")) == 0)
							StartIntElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "array")) == 0)
							StartArrayElement(uri, localname, qname, attrs);
							
	else if((XMLString::compareIString(XLO(localname), "float")) == 0)
							StartFloatElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "string")) == 0)
							StartStringElement(uri, localname, qname, attrs);
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
	else if((XMLString::compareIString(XLO(localname), "entity")) == 0)
							StartEntityElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "metadatalist")) == 0)
							StartMetadatalistElement(uri, localname, qname, attrs);
	else if((XMLString::compareIString(XLO(localname), "metadata")) == 0)
							StartMetadataElement(uri, localname, qname, attrs);

	/*Config SAX handler can safely ignore entity props
	  these are for user information only*/
	/*else if((XMLString::compareIString(XLO(localname), "entityprops")) == 0)
							StartEntitypropsElement(uri, localname, qname, attrs);*/

}

void CIoConfigSAXHandler::characters(  const   XMLCh* const    chars
								    ,  const unsigned int    length)
{
    char *val1;
	CIoParam *pCprop;
	int lval;
	lval = length>999 ? 999 : length;
	int irow, icol;
	int imr, imc, imd;

    //strncpy( val1, XLO(chars), lval ); 
	//val1[lval] = 0;
    matrix *m=NULL;
	vec *v=NULL;
	val1 = XLO(chars);

    int ielement;

	if(!m_ElementStack.empty())
		ielement = (int)m_ElementStack.top();
	switch(ielement)
	{
	case IO_XMLP_STACK_ELEMENT_STEPS :
		//Set simulation step numbers
		if(m_pSimulation)
		{
			
			m_pSimulation->SetNumSteps(atoi(val1));
			/*char seps[] = " ,\t\n";

			int icycle=0;
			char *tokenptr;
			tokenptr = strtok(val1, seps);
			while(tokenptr !=NULL)
			{
				m_pSimulation->SetNumSteps(atoi(tokenptr));
				tokenptr = strtok(NULL, seps);
				icycle++;
			}*/
		}
		break;
	case IO_XMLP_STACK_ELEMENT_INT :
		m_iCint = atoi(val1);
		//pCprop = (CIoParam *)m_ParamStack.top();
		//if(pCprop   && (pCprop->GetType()==IO_PARAM_INTEGER))
		//				pCprop->SetParam(&m_iCint);
		break;
	case IO_XMLP_STACK_ELEMENT_FLOAT :
		m_fCfloat = atoi(val1);
		//if((pCprop = (CIoParam *)m_ParamStack.top())  && (pCprop->GetType()==IO_PARAM_FLOAT))
		//				pCprop->SetParam(&m_fCfloat);
		break;
	case IO_XMLP_STACK_ELEMENT_STRING :
		//if(m_pCstring) delete [] m_pCstring;
		//m_pCstring = new char [strlen(val1)];
		//strncpy(m_pCstring, val1, strlen(val1));
		//if((pCprop = (CIoParam *)m_ParamStack.top())  && (pCprop->GetType()==IO_PARAM_STRING))
		//				pCprop->SetParam(m_pCstring);
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
		
		
		
	//case IO_XMLP_STACK_ELEMENT_SIZE :
		//m_vecsize = atoi(val1);
		//break;
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
			if(m_pCvec)
			   delete m_pCvec;
			m_pCvec=new vec(tempvec);
			//if(pCprop)
			//   pCprop->SetParam(&tempvec);
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
				if(icol<m_matcols && irow<m_matrows)
						tempmat.setval(irow, icol, fval);
				tokenptr = strtok(NULL, seps);
				
				icol++;
				if(icol>=m_matcols)
				{
					icol=0;
					irow++;					
				}
			
			}
			//pCprop->SetParam(&tempmat);
			if(m_pCmat)
			   delete m_pCmat;
			m_pCmat=new matrix(tempmat);
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

void CIoConfigSAXHandler::StartSimulationElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
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

	    if(m_pSimulation && m_iSimulationCount==0)
		{
			for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);
			if(m_pSimulation)
			{
				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{

					XMLString::copyString(sname, StrX(vl).localForm());
					if(strcmp(m_pSimulation->GetSimName(), sname)!=0)
					 m_pSimulation=NULL;
				}
				else if( XMLString::compareNString(ln,XStr("configfilename").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					//m_pSimulation->SetConfigFileName(sname);
				}
				else if( XMLString::compareNString(ln,XStr("step").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					m_pSimulation->SetCurrentStep(atoi(sname));
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
			}
		}
		}
		else
		{
			m_iSimulationCount++;

			for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("cycle").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					SetCycle(atoi(sname));
				}
				else if( XMLString::compareNString(ln,XStr("step").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					SetStep(atoi(sname));
				}
			
		}

		}
		//if(m_pSimulation) m_pSimulation->CreateDefaultParams();
			m_ElementStack.push(IO_XMLP_STACK_ELEMENT_SIMULATION);

		//At end of creation if simulation exists create default 
		//configuration?

}

void CIoConfigSAXHandler::StartSimulantElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{





}

void CIoConfigSAXHandler::StartSimulatorElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int len;
	char sname [100];
	char classname [100];
	int createmethod=0;

	CIoSimulator *pSimulator = NULL;
	CIoSimulant *pSimulant = NULL;
	CIoSimulator *pParentSimulator= NULL;
  //compare class name from sim file
	                        //with class name froom simulation object
	                        //checks that we are working with
	                        //the correct object
	const XMLCh * ln, * vl; 
	int lnl, vll;
	int iIndex = 0;

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
							XMLString::copyString(sname, StrX(vl).localForm());
				else if( XMLString::compareNString(ln,XStr("class").unicodeForm(), lnl) == 0 )
					strcpy(classname, XLO(vl));
				else if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
					iIndex = atoi(XLO(vl));
				else if( XMLString::compareNString(ln,XStr("createmethod").unicodeForm(), lnl) == 0 )
					createmethod = atoi(XLO(vl));


			}
		}


		if(m_pSimulation)
		{
			//if(pSimulator = m_pSimulation->newSimulator(classname))
			//{
			//	pSimulator->SetSimulatorClass(classname);
			//	pSimulator->SetSimulatorName(sname);
			//	pSimulator->CreateDefaultParams();
			//}
			if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_SIMULATION)
			{
				if(m_iSimulationCount<=1  && !m_iNoEntities)
				{
				if((m_pSimulation->GetSimulant()->GetSimulantType())==IO_SIMULANT_TYPE_SIMULATOR)
					pSimulator = (CIoSimulator *)m_pSimulation->GetSimulant();
				}
				else
				{
					pSimulator=m_pSimulation->newSimulator(classname);

				}
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_SIMULATOR)
			{
				if(m_iSimulationCount<=0 && !m_iNoEntities)
				{
				if((pSimulant = (CIoSimulant *)m_SimulantStack.top()) && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
				{
					pParentSimulator = (CIoSimulator *)pSimulant;
					if((pSimulant=pParentSimulator->GetChild(iIndex))&& (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
																		pSimulator = (CIoSimulator *)pSimulant;
				}
				else				
				{
							pSimulator = (CIoSimulator *)m_pSimulation->newSimulator(classname);
				}
				}
			}

			//Check simulator class is correct
			if(pSimulator && (strcmp(classname, pSimulator->GetSimulatorClass())!=0))pSimulator = NULL;

		}

		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_SIMULATOR);
		m_SimulantStack.push(pSimulator);
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_SIMULATOR);

		//At end of creation if simulation exists create default 
		//configuration?



}

void CIoConfigSAXHandler::StartModelElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{

	int len;
	char sname [100];
	char classname [100];
	int iIndex = 0;
	CIoModel *pModel = NULL;
  //compare class name from sim file
	    //with class name froom simulation object
	 //checks that we are working with
	 //the correct object
	CIoSimulant *pSimulant=NULL;
	CIoSimulator *pParentSimulator = NULL;

	const XMLCh * ln, * vl; 
	int lnl, vll;
    int createmethod=0;
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
							XMLString::copyString(sname, StrX(vl).localForm());
				else if( XMLString::compareNString(ln,XStr("class").unicodeForm(), lnl) == 0 )
					strcpy(classname, XLO(vl));
				else if( XMLString::compareNString(ln,XStr("createmethod").unicodeForm(), lnl) == 0 )
					createmethod = atoi(XLO(vl));
				else if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
					iIndex = atoi(XLO(vl));
			}
		}


		if(m_pSimulation)
		{
			if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_SIMULATION)
			{
				if((m_pSimulation->GetSimulant()->GetSimulantType())==IO_SIMULANT_TYPE_MODEL)
				{
					if(m_iSimulationCount<=1 && !m_iNoEntities)
						pModel = (CIoModel *)m_pSimulation->GetSimulant();
					else
					{
						pModel = (CIoModel *)m_pSimulation->newModel(classname);
						pModel->DeleteFlags();
						pModel->DeleteNames();
						pModel->CreatePropNames();
						pModel->CreatePropFlags();
						pModel->CreatePropArrayFlags();
						pModel->CreatePropArrayNames();
						pModel->CreateDefaultParams();
					}
				}
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_SIMULATOR)
			{
				if((pSimulant = (CIoSimulant *)m_SimulantStack.top()) && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
				{
					pParentSimulator = (CIoSimulator *)pSimulant;
					if((pSimulant=pParentSimulator->GetChild(iIndex))&& (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_MODEL))
					{
						if(m_iSimulationCount<=1  && !m_iNoEntities)
							pModel = (CIoModel *)pSimulant;
						else
						{
							pModel = (CIoModel *)m_pSimulation->newModel(classname);
							pModel->DeleteFlags();
							pModel->DeleteNames();
							pModel->CreatePropNames();
							pModel->CreatePropFlags();
							pModel->CreatePropArrayFlags();
							pModel->CreatePropArrayNames();
							pModel->CreateDefaultParams();
						}
									
					}
				}
			}
			if(pModel && (strcmp(classname, pModel->GetModelClass())!=0))pModel = NULL;

		}

		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_MODEL);
		m_SimulantStack.push(pModel);
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_MODEL);

		//At end of creation if simulation exists create default 
		//configuration?


}

void CIoConfigSAXHandler::StartEntitySetElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{

	int len;
	char sname [100];
	char classname [100];
	CIoModel *pModel = NULL;
	CIoSimulator *pSimulator = NULL;
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
	{
								pModel = (CIoModel *)pSimulant;
								pEntitySet=pModel->GetEntitySet(m_ientitysetcount);
								m_pEntitySet = pEntitySet;
	}
	/*else if(pSimulant && (pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR))
	{
								pSimulator = (CIoSimulator *)pSimulant;
								pEntitySet=pSimulator->GetEntitySet(m_ientitysetcount);
								m_pEntitySet = pEntitySet;
	}*/
	l=attrs.getLength();
	if(m_pSimulation && pEntitySet)
		{		
		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);


				if( XMLString::compareNString(ln,XStr("name").unicodeForm(), lnl) == 0 )
				{
					strcpy(sname, XLO(vl));
					pEntitySet->SetEntitySetName(sname);
				}
				//else if( XMLString::compareNString(ln,XStr("class").unicodeForm(), lnl) == 0 )
				//{
				//can do a check here
				//	strcpy(classname, XLO(vl));

				//			pEntitySet->SetEntitySetClass(classname);
				//}
				else if( XMLString::compareNString(ln,XStr("numentities").unicodeForm(), lnl) == 0 )
				{
					if(pEntitySet)
						m_inumentities=atoi(XLO(vl));
				}
				m_inumentities=0;
			}//end loop over attribs
		    //if(pEntitySet) pEntitySet->CreateDefaultParams();
		} //end of simulation check

		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYSET);
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYSET);




}

/*!
	Assumption: The entity set is not updated here and there are no entities
	in the entity set the action of start entity set is to create each entity 
	as it is found and add it to the appropriate entity set.
*/

void CIoConfigSAXHandler::StartEntityElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int len;
	char sname [100];
	char classname [100];
	CIoModel *pModel = NULL;
	CIoEntity *pEntity=NULL;
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
	int id;


	l=attrs.getLength();
	if((m_SimElementStack.top()==IO_XMLP_STACK_ELEMENT_ENTITYSET) && m_pEntitySet && !m_iNoEntities)
		{	
			if(m_pEntity == NULL)
			{
				m_pEntity = m_pEntitySet->newEntity();
				m_pEntity->CreateEntity();
			}
		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);


				if( XMLString::compareNString(ln,XStr("type").unicodeForm(), lnl) == 0 )
				{
					id=atoi(XLO(vl));
					m_pEntity->SetEntityTypeID(id);
					m_pEntity->SetEntityType(m_pEntitySet->GetEntityType(id));
				}
		

			}//end loop over attribs
		    //if(pEntitySet) pEntitySet->CreateDefaultParams();
				m_iPropCount = 0;
				m_ElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITY);
				m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITY);
				m_inumentities++;
				//if(m_pEntitySet)
				//	m_pEntitySet->AddEntity(m_pEntity);

				/*Should not need to call teh method below SAX 
				  should do this automatically*/
				//StartParamArrayElement(uri, localname, qname, attrs);
				//m_pCPropArray = m_pEntity->m_pProperties;
				//m_ParamArrayStack.push(m_pCPropArray);

		} //end of simulation check





}

void CIoConfigSAXHandler::StartEntitypropsElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
    int iSimElem;
	CIoSimulant *pSimulant = NULL;

    iSimElem = (int)m_SimElementStack.top();
	m_pCPropArray = (CIoParam *)m_ParamArrayStack.top();

    int iNumProps = 0;
	int len;
	char spropsname [100];
	char snumprops [100];

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



void CIoConfigSAXHandler::StartParamArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
    int iSimElem;
	CIoSimulant *pSimulant = NULL;

    iSimElem = (int)m_SimElementStack.top();
	m_pCPropArray = (CIoParam *)m_ParamArrayStack.top();

    int iNumProps = 0;
	int len;
	char spropsname [100];
	char snumprops [100];

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
			
				if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
							m_index = atoi(XLO(vl));

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
			case IO_XMLP_STACK_ELEMENT_SIMULATION :
					if(m_pSimulation)
						m_pCPropArray = m_pSimulation->GetSimProperties();
				break;
			case IO_XMLP_STACK_ELEMENT_SIMULATOR :
					pSimulant = (CIoSimulant *)m_SimulantStack.top();
					if(pSimulant && pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR )
						m_pCPropArray = pSimulant->GetParams();

				break;
			case IO_XMLP_STACK_ELEMENT_MODEL :
					pSimulant = (CIoSimulant *)m_SimulantStack.top();
					if(pSimulant && pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_MODEL )
						m_pCPropArray = pSimulant->GetParams();
				break;
			case IO_XMLP_STACK_ELEMENT_ENTITYSET :
					if(m_pEntitySet)
						m_pCPropArray = m_pEntitySet->m_pProperties;
				break;
			case IO_XMLP_STACK_ELEMENT_ENTITYPROPS :
					if(m_pEntitySet)
						m_pCPropArray = m_pEntitySet->GetEDefaultParams();
				break;
			case IO_XMLP_STACK_ELEMENT_ENTITY :
					if(m_pEntity)
						m_pCPropArray = m_pEntity->m_pProperties;

				break;
		}//end of simulant case check
	}//end of prop array check
	m_iPropCount=0;
	m_ParamArrayStack.push(m_pCPropArray);
	//m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_PROPS);
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_PROPS);
}

void CIoConfigSAXHandler::StartParamElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int iPropIndex=-1;
	int iOldIndex = 0;
	const XMLCh * ln, * vl; 
	int lnl, vll;
	string strprop;
	string sinfile="";
	string soutfile="";
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



		}



		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
							iPropIndex = atoi(XLO(vl));
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
			
					
		}
		m_pCPropArray = (CIoParam *)m_ParamArrayStack.top();		
		if(iPropIndex==-1 && m_pEntity)
		{
			iOldIndex = -1;
			iPropIndex = m_iPropCount;
		}
		m_pCprop = m_pCPropArray->GetParam(iPropIndex);

		if(m_pCprop && (sinfile.length()>0))
		{
			
			
			    #ifdef USEMPI
					//if number of procs > 0and filename length is >0
					//modify prop filename so that read from correct config file
					//propfile.XXX wil be modified to
					//propfile_pnnnn.XXX where nnnn is the proc id
					if((m_pSimulation->m_inumprocs>1) /*&& (strprop.size()>0)*/)
					{
						char c;
						int i=0,jext=0;
						char soutname[300];
						char snoutname[400];
						char sext[300];
						char *sfilename;

						sfilename=(char *)sinfile.c_str();			
						while(((c=sfilename[i])!='.') && (i < strlen(sfilename)))
										soutname[i++]=c;

						if((i < strlen(sfilename)) && (c=='.'))
							while(( ++i < strlen(sfilename)))
							{
								c=sfilename[i];		       
								sext[jext++]=c;
							}

						sprintf(snoutname, "$s_p%d.%s",soutname,m_pSimulation->m_irank,sext);
						sinfile=snoutname;


					}
					#endif

			
			
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

		if(iOldIndex == -1)
			m_iPropCount ++;

		
	}


}

void CIoConfigSAXHandler::StartIntElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	const XMLCh * ln, * vl; 
	int lnl, vll;
	int i,l;
  	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

					if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
							m_index = atoi(XLO(vl));
					
			}


	//if((!m_ElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY))) StartParamElement(uri, localname, qname, attrs);
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_INT);


}

void CIoConfigSAXHandler::StartArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
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
	//m_pCArray=pArray;


}

void CIoConfigSAXHandler::StartFloatElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	const XMLCh * ln, * vl; 
	int lnl, vll;
	int i,l;
  	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

					if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
							m_index = atoi(XLO(vl));
					
			}
	
	//if((!m_ElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY))) StartParamElement(uri, localname, qname, attrs);
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_FLOAT);

}

void CIoConfigSAXHandler::StartStringElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	const XMLCh * ln, * vl; 
	int lnl, vll;
	int i,l;
  	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

					if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
							m_index = atoi(XLO(vl));
					
			}

	//if((!m_ElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY))) StartParamElement(uri, localname, qname, attrs);
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_STRING);
}


void CIoConfigSAXHandler::StartStringArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	const XMLCh * ln, * vl; 
	int lnl, vll;
	int i,l;
  	l=attrs.getLength();

		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

					if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
							m_index = atoi(XLO(vl));
					
			}

	//if((!m_ElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY))) StartParamElement(uri, localname, qname, attrs);
	m_ElementStack.push(IO_XMLP_STACK_ELEMENT_STRINGARRAY);
}


void CIoConfigSAXHandler::StartVectorElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	int iPropIndex;
	const XMLCh * ln, * vl; 
	int lnl, vll;

		//Get the attributes and set these to the simulation
	int j,l;
    int vecsize=1;
	l=attrs.getLength();


		for ( int i=0; i<l; i++ ) {
	
			ln = attrs.getLocalName(i); 
			vl = attrs.getValue(i);
			vll = XMLString::stringLen(vl);
			lnl = XMLString::stringLen(ln);

				if( XMLString::compareNString(ln,XStr("size").unicodeForm(), lnl) == 0 )
							m_vecsize = atoi(XLO(vl));
				else if( XMLString::compareNString(ln,XStr("index").unicodeForm(), lnl) == 0 )
							m_index = atoi(XLO(vl));
					
			}
	//if((!m_ElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY)))
	//{
	//	StartParamElement(uri, localname, qname, attrs);
	//}
	
		m_ElementStack.push(IO_XMLP_STACK_ELEMENT_VECTOR);
}

void CIoConfigSAXHandler::StartVecElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	//if(m_pCvec) delete m_pCvec;
	//m_pCvec = new vec(m_vecsize, 0);
	//m_ElementStack.push(IO_XMLP_STACK_ELEMENT_VEC);
	
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


void CIoConfigSAXHandler::StartMatrixElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
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


void CIoConfigSAXHandler::Startmmat3dElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
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
				if( XMLString::compareNString(ln,XStr("rows").unicodeForm(), lnl) == 0 )
							m_mm3r = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("cols").unicodeForm(), lnl) == 0 )
							m_mm3c = atoi(XLO(vl));
				if( XMLString::compareNString(ln,XStr("depth").unicodeForm(), lnl) == 0 )
							m_mm3d = atoi(XLO(vl));

					
			}
		
}


void CIoConfigSAXHandler::StartMetadatalistElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
{
	
	
	
}

void CIoConfigSAXHandler::StartMetadataElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs)
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
		m_pSimulation->SetMetadata(sname,scontent);
	
	

	
	
}



void CIoConfigSAXHandler::endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	if ((XMLString::compareIString(XLO(localname), "entityset")) == 0)
									endEntitySetElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "entity")) == 0)
									endEntityElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "int")) == 0)
		EndIntElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "array")) == 0)
		EndArrayElement(uri, localname, qname);	
	else if ((XMLString::compareIString(XLO(localname), "vec")) == 0)
		EndVecElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "float")) == 0)
		EndFloatElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "string")) == 0)
		EndStringElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "prop")) == 0)
		endParamElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "props")) == 0)
		endParamArrayElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "mat")) == 0)
		EndMatrixElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "mmat3d")) == 0)
		Endmmat3dElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "metadatalist")) == 0)
		EndMetadatalistElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "metadata")) == 0)
		EndMetadataElement(uri, localname, qname);
	else if ((XMLString::compareIString(XLO(localname), "vector")) == 0)
		EndVectorElement(uri, localname, qname);
	else if((XMLString::compareIString(XLO(localname), "entityprops")) == 0)
	{
		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITYPROPS))	m_ElementStack.pop();
		if(!m_ParamArrayStack.empty()) m_ParamArrayStack.pop();
	}
	else if ((XMLString::compareIString(XLO(localname), "simulation")) == 0)
	{
		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_SIMULATION))	m_ElementStack.pop();
		if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_SIMULATION))	m_SimElementStack.pop();


	}
	else if((XMLString::compareIString(XLO(localname), "steps")) == 0)
		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_STEPS))	m_ElementStack.pop();
	//else if((XMLString::compareIString(XLO(localname), "simulant")) == 0);
	else if((XMLString::compareIString(XLO(localname), "simulator")) == 0)
	{
		CIoSimulant *pSimulatorState;
		CIoSimulant *pParentSimulant;

		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_SIMULATOR))	m_ElementStack.pop();
		if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_SIMULATOR))	m_SimElementStack.pop();
		if(!m_SimulantStack.empty() && ((CIoSimulant *)(m_SimulantStack.top())!= NULL))	
		{
			pSimulatorState=(CIoSimulant *)m_SimulantStack.top();
			m_SimulantStack.pop();
		}
		m_ientitysetcount=0;
		//check if m_iSimulationCount
		if((m_iSimulationCount>=1) && pSimulatorState && m_iNoEntities)
		{
			//check if model belongs to a simulator
			if(m_SimulantStack.empty() )
			{
				pSimulatorState->SetCurrentCycle(m_icycle);
				pSimulatorState->SetCurrentStep(m_istep);

				if(m_pSimulation)
					m_pSimulation->AddSimulantState(pSimulatorState);
				else
					delete pSimulatorState;
			}
			else
			{
				
				if(!m_SimulantStack.empty())
					pParentSimulant = (CIoSimulant *)m_SimulantStack.top();
				if(pParentSimulant && pSimulatorState)
				{
					pParentSimulant->Add(pSimulatorState);
					pSimulatorState->SetParentSimulant(pParentSimulant);
				}
				else if(pSimulatorState) delete pSimulatorState;


			}

		}

	}//if end element is simulator
	else if((XMLString::compareIString(XLO(localname), "model")) == 0)
	{
		//This must always be the first element pushed onto stack
		//there will normally be only 1!!!!
		CIoSimulant *pModelState;
		CIoSimulant *pParentSimulant;
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_MODEL))	m_ElementStack.pop();
		if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_MODEL))	m_SimElementStack.pop();
		if(!m_SimulantStack.empty() && ((CIoSimulant *)(m_SimulantStack.top())!= NULL))
		{
            pModelState=(CIoSimulant *)m_SimulantStack.top();		
			m_SimulantStack.pop();
		}

		//check if m_iSimulationCount
		if((m_iSimulationCount>=1) && pModelState && m_iNoEntities)
		{
			//check if model belongs to a simulator
			if(m_SimulantStack.empty() )
			{
				pModelState->SetCurrentCycle(m_icycle);
				pModelState->SetCurrentStep(m_istep);

				if(m_pSimulation)
					m_pSimulation->AddSimulantState(pModelState);
				else
					delete pModelState;
			}
			else
			{
				
				if(!m_SimulantStack.empty())
					pParentSimulant = (CIoSimulant *)m_SimulantStack.top();
				if(pParentSimulant && pModelState)
				{
					pParentSimulant->Add(pModelState);
					pModelState->SetParentSimulant(pParentSimulant);
				}
				else if(pModelState) delete pModelState;


			}

		}
	



		m_ientitysetcount=0;
		m_pEntitySet=NULL;
		m_inumentities=0;
	}//if end element is model	



}

void CIoConfigSAXHandler::endEntitySetElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{

		if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITYSET))	
												m_SimElementStack.pop();

		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITYSET))	
		{
			m_ElementStack.pop();
			m_pEntitySet=NULL;
			m_inumentities=0;
			m_ientitysetcount++;
		}

}

void CIoConfigSAXHandler::endEntityElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{

	if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_PROPS))	
		m_ElementStack.pop();
	if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY))	
												m_SimElementStack.pop();
	if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY))	
		{
			m_ElementStack.pop();
			m_iPropCount = 0;

			if(m_pEntity )
			{
				if(m_pEntitySet)
					m_pEntitySet->AddEntity(m_pEntity);
				//endParamArrayElement(uri, localname, qname);
			}
			m_pEntity=NULL;
		}


}


void CIoConfigSAXHandler::endParamArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_PROPS))	m_ElementStack.pop();
	//if(!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_PROPS))	m_SimElementStack.pop();
	if(!m_ParamArrayStack.empty()) m_ParamArrayStack.pop();
}

void CIoConfigSAXHandler::endParamElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	int iparamindex;

	//if(!m_ParamIndexStack.empty())	iparamindex = (int)m_ParamIndexStack.pop();	
	if(m_ParamStack.size()>1)
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

void CIoConfigSAXHandler::EndIntElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_INT))	m_ElementStack.pop();
			if((!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY))) /*endParamElement(uri, localname, qname);*/
			{
				if(m_pEntity)
					m_pEntity->SetInt(m_index, m_iCint);
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
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

void CIoConfigSAXHandler::EndArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ARRAY))	m_ElementStack.pop();
			if(!m_ArraySizeStack.empty() )	m_ArraySizeStack.pop();
			CIoParam *pArray=NULL;
			
			if(!m_ArrayStack.empty())
			{
				m_pCArray=(CIoParam *)(m_ArrayStack.top());
				m_ArrayStack.pop();
			}
			if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
			{
				//update the parameter
				if((m_pCprop = (CIoParam *)m_ParamStack.top())  /*&& (m_pCprop->GetType()==IO_PARAM_ARRAY)*/)
						m_pCprop->SetParam(m_pCArray);
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
void CIoConfigSAXHandler::EndFloatElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_FLOAT))	m_ElementStack.pop();
			if((!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY)))
			{
				if(m_pEntity)
					m_pEntity->SetFloat(m_index, m_fCfloat);
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
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

void CIoConfigSAXHandler::EndStringElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_STRING))	m_ElementStack.pop();
			if((!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY)))
			{
				if(m_pEntity)
				{
					m_pEntity->SetString(m_index, m_sb.str().c_str());
					m_sb.str("");
				}
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
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

void CIoConfigSAXHandler::EndStringArrayElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_STRINGARRAY))	m_ElementStack.pop();
			if((!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY)))
			{
				if(m_pStringArray && m_pEntity)
				{
					m_pEntity->SetStringArray(m_index, m_pStringArray);
						delete m_pStringArray;
						m_pStringArray=NULL;
				}
			}
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_PROP)
			{
				//update the parameter
				if(m_pStringArray && (m_pCprop = (CIoParam *)m_ParamStack.top()) /* && (m_pCprop->GetType()==IO_PARAM_VEC)*/)
				{
						m_pCprop->SetParam(m_pStringArray);
						delete m_pStringArray;
						m_pStringArray=NULL;
				}
			}			
			else if(m_ElementStack.top()==IO_XMLP_STACK_ELEMENT_ARRAY)
			{
				//update the parameter
				if(m_pStringArray && (m_pCArray = (CIoParam *)m_ArrayStack.top()) /* && (m_pCArray->GetType()==IO_PARAM_ARRAY)*/)
				{
						m_pCprop->SetParam(m_pStringArray);
						delete m_pStringArray;
						m_pStringArray=NULL;
				}
			}			

}



void CIoConfigSAXHandler::EndVectorElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
			if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_VECTOR))	m_ElementStack.pop();
			if((!m_SimElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY)))
			{
				if(m_pEntity)
					m_pEntity->SetVec(m_index,m_pCvec);

				if(m_pCvec) delete m_pCvec;
				m_pCvec = NULL;

			}


}

void CIoConfigSAXHandler::EndVecElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
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
			
			if((!m_ElementStack.empty() && ((int)(m_SimElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY)))
			{
				;

			}
			else
			{
			if(m_pCvec) delete m_pCvec;
			m_pCvec = NULL;

			}



}

void CIoConfigSAXHandler::EndMatrixElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
		matrix *pmat;
		if((m_pCprop = (CIoParam *)m_ParamStack.top())  && (m_pCprop->GetType()==IO_PARAM_MAT))
		{
					//m_pCprop->SetParam(m_pCmat);
					pmat=m_pCprop->GetMatParam();
		}
		
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_MATRIX))	m_ElementStack.pop();
			if((!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY)))
			{
				if(m_pEntity)
					m_pEntity->SetMat(m_index, pmat);
			}

		//if(m_pCmat) delete m_pCmat;
		m_matcols = 0;
		m_matrows = 0;
		m_matcurrentrow = 0;
		//m_pCmat = NULL;
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
						m_pCArray->AddParam(m_pCmat);
		}
}

void CIoConfigSAXHandler::Endmmat3dElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
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
			mmat3d *pmat;
		if((m_pCprop = (CIoParam *)m_ParamStack.top())  && (m_pCprop->GetType()==IO_PARAM_MMAT3D))
		{
					//m_pCprop->SetParam(m_pCmat);
					pmat=m_pCprop->Getmmat3dParam();
		}
		
		if(!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_MMAT3D))	m_ElementStack.pop();
			if((!m_ElementStack.empty() && ((int)(m_ElementStack.top())==IO_XMLP_STACK_ELEMENT_ENTITY)))
			{
				if(m_pEntity)
					m_pEntity->Setmmat3d(m_index, pmat);
			}	
		
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


void CIoConfigSAXHandler::EndMetadatalistElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	
	
	
	
}


void CIoConfigSAXHandler::EndMetadataElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
	
	
	
}




