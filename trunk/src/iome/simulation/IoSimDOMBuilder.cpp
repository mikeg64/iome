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


#include <iome/simulation/IoSimDOMBuilder.h>

#define X(str) XStr(str).unicodeForm()


CIoSimDOMBuilder::CIoSimDOMBuilder(void)
{
	ResetDepthArray();
	m_pCurrentModel=NULL;
	m_pCurrentSimulator=NULL;
	m_pCurrentParamArray=NULL;
	m_pCurrentEntitySet=NULL;
	m_pCurrentEntityTypeSet=NULL;
	m_pCurrentEntityType=NULL;
	m_SimElementStack.push(0);
	m_SimulantStack.push(NULL);
	
	m_iCurrentIndex = 0;
	// Initialize the XML4C2 system.
    //try
    //{
    //    XMLPlatformUtils::Initialize();
    //}

    //catch(const XMLException& toCatch)
    //{
     //   char *pMsg = XMLString::transcode(toCatch.getMessage());
        /*cerr << "Error during Xerces-c Initialization.\n"
             << "  Exception message:"
             << pMsg;*/
       // delete [] pMsg;
    //}
	m_pDOMImpl =  DOMImplementationRegistry::getDOMImplementation(X("Core"));
	m_pDOMDoc=NULL;

	/*!test flag to determine which type of
	   read/write we're testing for
	   1=simulation, 2=config, 4=state
					 */
	m_iflagtype=1;
}

CIoSimDOMBuilder::~CIoSimDOMBuilder(void)
{
    if(m_sArrayMap) delete [] m_sArrayMap; 
	if(m_pDOMDoc)
		m_pDOMDoc->release();
	//XMLPlatformUtils::Terminate();
}

int CIoSimDOMBuilder::CreateSimDOM(char *m_pDOMDocname, CIoXMLSimulation *pSimulation)
{
	int status = 1;
	char sver[100]= "crap";
	//sver[100] = "crap";
	char http [100] = "http//";
	char www [100]= "www.w3.org/2001/XMLSchema-instance";
	
	char xmlns [20] = "xmlns:xsi";
	strcat(http, www);
	int index = 0;
	char sSimulantType [100];
	char sCreateMethod [100];
	char sCycles [100];
	char snprocs [100];
	char sdistributemethod [100];
	int iCreateMethod = 0;
	int iCycles;
	int iNumParams = 0;
	CIoParam *pParam = NULL;
	DOMElement *pPropsElem; 
	DOMElement *pPropElem;
	index = 0;

	if(pSimulation)
	   {
		   m_pSimulation = pSimulation;
        //  Nest entire test in an inner block.
        //  The tree we create below is the same that the XercesDOMParser would
        //  have created, except that no whitespace text nodes would be created.

        // <company>
        //     <product>Xerces-C</product>
        //     <category idea='great'>XML Parsing Tools</category>
        //     <developedBy>Apache Software Foundation</developedBy>
        // </company>

        
        m_pDOMDoc = m_pDOMImpl->createDocument(
                    0,                    // root element namespace URI.
                    X("iosim"),         // root element name
                    0);                   // m_pDOMDocument type object (DTD).




        DOMElement* rootElem = m_pDOMDoc->getDocumentElement();
		//rootElem->lookupNamespaceURI(
		//rootElem->setAttributeNS(X("http//www.w3.org/2001/XMLSchema-instance"),X("xmlns:xsi"),X("http//www.w3.org/2001/XMLSchema-instance"));
		//rootElem->setAttributeNS(X("http//www.w3.org/2001/XMLSchema-instance"),X("xmlns:xsi"), 0);

		//rootElem->setAttributeNS(X("http//www.w3.org/2001/XMLSchema-instance"),X("xmlns:xsi"),X("http//www.w3.org/2001/XMLSchema-instance"));

		//rootElem->setAttribute(X(xmlns), X(http));
		//rootElem->setAttribute(X("xsi:noNamespaceSchemaLocation"), X("C:\\Documents and Settings\\Michael\\My Documents\\MKGSoft\\iome\\iome5\\Design\\XMLSimulation\\SimConfig3.xsd"));
		//sprintf(sver,"%f",  pSimulation->GetVersion());
		//rootElem->setAttribute(X("version"), X(sver));
		rootElem->setAttribute(X("filename"), X(m_pDOMDocname));

		iCreateMethod = pSimulation->GetCreateMethod();
		sprintf(sCreateMethod, "%d", iCreateMethod);
		sprintf(sSimulantType, "%d", pSimulation->GetSimulantType());




        DOMElement*  SimulationElem = m_pDOMDoc->createElement(X("simulation"));
        rootElem->appendChild(SimulationElem);
        SimulationElem->setAttribute(X("name"), X(pSimulation->GetSimName()));
        SimulationElem->setAttribute(X("class"), X(pSimulation->GetSimClass()));
		SimulationElem->setAttribute(X("simulanttype"), X(sSimulantType));
        SimulationElem->setAttribute(X("simulantclass"), X(pSimulation->GetSimulantClass()));
         //SimulationElem->setAttribute(X("configfilename"), X(pSimulation->GetConfigFileName()));
		//if((strlen(pSimulation->GetConfigXSLFileName()))>0)
		//	SimulationElem->setAttribute(X("configxslfile"), X(pSimulation->GetStateXSLFileName()));

        SimulationElem->setAttribute(X("createmethod"), X(sCreateMethod));
		//if((strlen(pSimulation->GetStateFileName()))>0)
		//	SimulationElem->setAttribute(X("statefilename"), X(pSimulation->GetStateFileName()));
		//if((strlen(pSimulation->GetStateXSLFileName()))>0)
		//	SimulationElem->setAttribute(X("statexslfile"), X(pSimulation->GetStateXSLFileName()));

        
        if((pSimulation->GetNumProcs())>0)
        {
        	sprintf(snprocs,"%d",pSimulation->GetNumProcs());
        	SimulationElem->setAttribute(X("nprocs"), X(snprocs));
        }
        
        if((pSimulation->GetDistributeMethod())>0)
         {
        	sprintf(sdistributemethod,"%d",pSimulation->GetDistributeMethod());
	        SimulationElem->setAttribute(X("distributemethod"), X(sdistributemethod));
        }


		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_SIMULATION);
		if((pParam = pSimulation->GetSimProperties()))
			{
				iNumParams = pParam->GetNumParams();
				if(iNumParams>0)
				{
					//pSimulation->CreatePropArrayNames();
					//pSimulation->CreatePropNames();
					//pSimulation->CreatePropArrayFlags();
					//pSimulation->CreatePropFlags();
					pPropsElem = CreatePropsElement(pSimulation->GetArrayName(0), pSimulation->GetArrayFlag(0),iNumParams, SimulationElem);
					pParam = pSimulation->GetProperty(0);
					while(pParam)
					{
						ResetDepthArray();
						m_iCurrentIndex = index;
						pPropElem = CreatePropElement(pParam, pPropsElem);
						if(pPropElem && pPropsElem /*&& (GetPropFlag()==0)*/)
							pPropsElem->appendChild(pPropElem);

						pParam = pParam->GetNextParam();
						index ++;					
					}
					if(pPropsElem)
						SimulationElem->appendChild(pPropsElem);
				}

			}



        DOMElement *StepsElem = CreateStepsElement(m_pSimulation, SimulationElem);
		DOMElement *filepropsElem = CreatefilepropsElement(m_pSimulation, SimulationElem);
		DOMElement *metadataElem = CreateMetadatalistElement(m_pSimulation, SimulationElem);

		SimulationElem->appendChild(StepsElem);
		SimulationElem->appendChild(filepropsElem);
		if(metadataElem != NULL)
			SimulationElem->appendChild(metadataElem);
        DOMElement * SimulantElem = CreateSimulantElement(pSimulation, SimulationElem);
		if(SimulantElem)
		{
			SimulationElem->appendChild(SimulantElem);
		//	status = 1;
		}
		//else
		//	status = 0;
		if((strlen(pSimulation->GetSimXSLFileName())>0) && (strcmp(pSimulation->GetSimXSLFileName(),"null")!=0)&& (strcmp(pSimulation->GetSimXSLFileName(),"NULL")!=0))
		{
			char sxsl[200];
			//sxsl = "href='fichier.xsl' type='text/xsl'";
			sprintf(sxsl," type=\"text/xsl\" href=\"%s\"",pSimulation->m_sSimXSLFileName);
			DOMProcessingInstruction*  procElem=m_pDOMDoc->createProcessingInstruction  ( X("xml-stylesheet"),  X(sxsl)   ); 
			m_pDOMDoc->insertBefore(procElem,rootElem);

		}
			if(!m_SimElementStack.empty()) m_SimElementStack.pop();
		status = 1;

   }
	else
		status = 0;

   


	return status;
}

DOMElement *CIoSimDOMBuilder::CreateStepsElement(CIoXMLSimulation *pSimulation, DOMElement *ParentSim)
{
	DOMElement *pStepsElem = NULL;
    int i, iSteps, iCycles;

	char sCycles[300];
	char sTempCycles[300];
	sCycles [0] = '\0';
	sTempCycles [0] = '\0';

	int ifreq;
	char sifreq [10];

	if(pSimulation)
	{
		/*iSteps = pSimulation->GetNumCycles();
		for(i=0; i<iSteps; i++)
		{
			strcpy(sTempCycles, sCycles);
			sprintf(sCycles, "%s %d", sTempCycles, pSimulation->GetNumSteps());
		}*/
		//strcpy(sTempCycles, sCycles);
		sprintf(sCycles, "%d", pSimulation->GetNumSteps());

		pStepsElem = m_pDOMDoc->createElement(X("steps"));
		
		/*ifreq = pSimulation->GetConfigCycleFreq();
		if(ifreq>=0)
		{
			sprintf(sifreq, "%d", ifreq);
			pStepsElem->setAttribute(X("configcyclefreq"), X(sifreq));
		}
		ifreq = pSimulation->GetStateCycleFreq();
		if(ifreq>=0)
		{
			sprintf(sifreq, "%d", ifreq);
			pStepsElem->setAttribute(X("statecyclefreq"), X(sifreq));
		}*/
		ifreq = pSimulation->GetConfigStepFreq();
		if(ifreq>=0)
		{
			sprintf(sifreq, "%d", ifreq);
			pStepsElem->setAttribute(X("configstepfreq"), X(sifreq));
		}
		ifreq = pSimulation->GetStateStepFreq();
		if(ifreq>=0)
		{
			sprintf(sifreq, "%d", ifreq);
			pStepsElem->setAttribute(X("statestepfreq"), X(sifreq));
		}
		DOMText*    StepsVal = m_pDOMDoc->createTextNode(X(sCycles));
			pStepsElem->appendChild(StepsVal);
 
	}

    return pStepsElem;
}


DOMElement *CIoSimDOMBuilder::CreateMetadatalistElement(CIoXMLSimulation *psim, DOMElement *parentsim)
{

	DOMElement *pmlElem = NULL;
	DOMElement *pmElem = NULL;
	CIoMetadata *pmeta=NULL;
    int i;
	char sname [1000];
	char scontent [1000];

	if(m_pDOMDoc && psim )
	{
		int lsize=((psim->m_lMetadataList).size());
		if(lsize>0)
		{
			pmlElem = m_pDOMDoc->createElement(X("metadatalist"));
			for(i=0; i<lsize; i++)
			{
				pmeta=psim->GetMetadata(i);
				sprintf(sname,"%s",(pmeta->m_sname).c_str());
				sprintf(scontent,"%s",(pmeta->m_scontent).c_str());
				pmElem = m_pDOMDoc->createElement(X("metadata"));
				pmElem->setAttribute(X("name"), X(sname));
				pmElem->setAttribute(X("content"), X(scontent));
				pmlElem->appendChild(pmElem);
			}

		}

	}


	return pmlElem;

}

DOMElement *CIoSimDOMBuilder::CreateLinksElement(CIoSimulator *psim, DOMElement *parentsim)
{

	DOMElement *plinksElem = NULL;
	DOMElement *plinkElem = NULL;
	DOMElement *pfromElem = NULL;
	DOMElement *ptoElem = NULL;
	CIoSimulantLink *plink=NULL;
    int i;

	if(m_pDOMDoc && psim )
	{
		int lsize=((psim->m_pLinks).size());
		if(lsize>0)
		{
			plinksElem = m_pDOMDoc->createElement(X("links"));
			for(i=0; i<lsize; i++)
			{
				plink=psim->GetLink(i);
				
				
				plinkElem = m_pDOMDoc->createElement(X("link"));
				pfromElem=CreateFromElement(plink->GetFromPort(),plinkElem);
				ptoElem=CreateToElement(plink->GetToPort(),plinkElem);
				plinkElem->appendChild(pfromElem);
				plinkElem->appendChild(ptoElem);
				
				plinksElem->appendChild(plinkElem);
			}

		}

	}


	return plinksElem;

}

DOMElement *CIoSimDOMBuilder::CreateFromElement(CIoSimulantPort *pport, DOMElement *linkelem)
{
		DOMElement *pfromelement = NULL;
		DOMElement *ptoelement = NULL;

	    int i;

		char sientitysetid[1000];
		char siparamid[1000];
		char sisimulantid[1000];

		string sparammap;
		string ssimulantmap;
		int iparamid;
		int isimulantid;
		int ientitysetid;
			
		if(pport !=NULL)
		{
		    sparammap=pport->GetParammap();
		    ssimulantmap=pport->GetSimulantmap();
		    iparamid=pport->GetParamID();
		    isimulantid=pport->GetSimulantID();
		    ientitysetid=pport->GetEntitySetID();
		
			pfromelement = m_pDOMDoc->createElement(X("from"));
			
			if(sparammap.length() >0)
				pfromelement->setAttribute(X("parammap"), X(sparammap.c_str()));
			   
			if(ssimulantmap.length()>0)
				pfromelement->setAttribute(X("simulantmap"), X(ssimulantmap.c_str()));
			  
			sprintf(siparamid,"%d",iparamid);
			sprintf(sisimulantid,"%d",isimulantid);			   
			sprintf(sientitysetid,"%d",ientitysetid);			   
						   
			if(iparamid>=0)
						   pfromelement->setAttribute(X("paramid"), X(siparamid));
			if(isimulantid>=0)
						   pfromelement->setAttribute(X("simulantid"), X(sisimulantid));
			if(ientitysetid>=0)
						   pfromelement->setAttribute(X("entitysetid"), X(sientitysetid));
			
			
		}
	    return pfromelement;
}

DOMElement *CIoSimDOMBuilder::CreateToElement(CIoSimulantPort *pport, DOMElement *linkelem)
{
		DOMElement *ptoelement = NULL;
	    int i;
		string sparammap;
		string ssimulantmap;
		int iparamid;
		int isimulantid;
		int ientitysetid;
		char siparamid [1000];
		char sisimulantid [1000];
		char sientitysetid [1000];
		
		if(pport !=NULL)
		{
		    sparammap=pport->GetParammap();
		    ssimulantmap=pport->GetSimulantmap();
		    iparamid=pport->GetParamID();
		    isimulantid=pport->GetSimulantID();
		    ientitysetid=pport->GetEntitySetID();
		
			ptoelement = m_pDOMDoc->createElement(X("to"));
			
			if(sparammap.length()>0)
				ptoelement->setAttribute(X("parammap"), X(sparammap.c_str()));
			   
			if(ssimulantmap.length()>0)
			   ptoelement->setAttribute(X("simulantmap"), X(ssimulantmap.c_str()));
			  
			sprintf(siparamid,"%d",iparamid);
			sprintf(sisimulantid,"%d",isimulantid);			   
			sprintf(sientitysetid,"%d",ientitysetid);			   
						   
			if(iparamid>=0)
						   ptoelement->setAttribute(X("paramid"), X(siparamid));
			if(isimulantid>=0)
						   ptoelement->setAttribute(X("simulantid"), X(sisimulantid));
			if(ientitysetid>=0)
						   ptoelement->setAttribute(X("entitysetid"), X(sientitysetid));
			
			
		}
	    return ptoelement;
}


DOMElement *CIoSimDOMBuilder::CreatefilepropsElement(CIoXMLSimulation *pSimulation, DOMElement *ParentSim)
{
	DOMElement *pfilepropsElem = NULL;
    int i;
	char sreadMethod [100];
	char swriteMethod [100];
	
	int ireadMethod = 1;
	int iwriteMethod = 1;


	int ifreq;
	char sifreq [10];

	if(pSimulation)
	{


		pfilepropsElem = m_pDOMDoc->createElement(X("fileprops"));


		iwriteMethod = pSimulation->GetSimWriteMethod();
		
			sprintf(swriteMethod, "%d", iwriteMethod);
			pfilepropsElem->setAttribute(X("simwritemethod"), X(swriteMethod));

		ireadMethod = pSimulation->GetSimReadMethod();
		
			sprintf(sreadMethod, "%d", ireadMethod);
			pfilepropsElem->setAttribute(X("simreadmethod"), X(sreadMethod));

		iwriteMethod = pSimulation->GetStateWriteMethod();
		
			sprintf(swriteMethod, "%d", iwriteMethod);
			pfilepropsElem->setAttribute(X("statewritemethod"), X(swriteMethod));

		ireadMethod = pSimulation->GetStateReadMethod();
		
			sprintf(sreadMethod, "%d", ireadMethod);
			pfilepropsElem->setAttribute(X("statereadmethod"), X(sreadMethod));

		iwriteMethod = pSimulation->GetConfigWriteMethod();
		
			sprintf(swriteMethod, "%d", iwriteMethod);
			pfilepropsElem->setAttribute(X("configwritemethod"), X(swriteMethod));

		ireadMethod = pSimulation->GetConfigReadMethod();
		
			sprintf(sreadMethod, "%d", ireadMethod);
			pfilepropsElem->setAttribute(X("configreadmethod"), X(sreadMethod));





		if(strlen(pSimulation->GetConfigFileName())>0)
			pfilepropsElem->setAttribute(X("configfilename"), X(pSimulation->GetConfigFileName()));
		if((strlen(pSimulation->GetConfigXSLFileName()))>0)
			pfilepropsElem->setAttribute(X("configxslfile"), X(pSimulation->GetConfigXSLFileName()));
		if((strlen(pSimulation->GetConfigXSLFilePrefix()))>0)
			pfilepropsElem->setAttribute(X("configxslfileprefix"), X(pSimulation->GetConfigXSLFilePrefix()));

 		if((strlen(pSimulation->GetStateFileName()))>0)
			pfilepropsElem->setAttribute(X("statefilename"), X(pSimulation->GetStateFileName()));
		if((strlen(pSimulation->GetStateXSLFileName()))>0)
			pfilepropsElem->setAttribute(X("statexslfile"), X(pSimulation->GetStateXSLFileName()));
		if((strlen(pSimulation->GetStateXSLFilePrefix()))>0)
			pfilepropsElem->setAttribute(X("statexslfileprefix"), X(pSimulation->GetStateXSLFilePrefix()));


 
	}

    return pfilepropsElem;
}


void CIoSimDOMBuilder::ResetDepthArray()
{
	m_iArrayDepth = 0;
	m_iCurrentProp = -1;
	m_sArrayMap=NULL;

	for(int i=0; i<IO_MAXDEPTH; i++)m_iMapArray [i]=0;


}

DOMElement *CIoSimDOMBuilder::CreateSimulantElement(CIoXMLSimulation *pSimulation, DOMElement *SimulationElem)
{

	DOMElement *pSimulantElem = NULL;
	CIoSimulant *pSimulant = NULL;
	DOMElement *pSimulatorElem = NULL;
	DOMElement *pModelElem = NULL;
	if(m_pDOMDoc && pSimulation && (pSimulant = pSimulation->GetSimulant()))
	{
		/*if(pSimulantElem = m_pDOMDoc->createElement(X("Simulant")))
		{*/
			if(pSimulant->GetSimulantType()== IO_SIMULANT_TYPE_SIMULATOR)
			{
			pSimulatorElem = CreateSimulatorElement(pSimulant, pSimulantElem);
			if(pSimulatorElem)
				/*pSimulantElem->appendChild(pSimulatorElem);*/
				pSimulantElem = pSimulatorElem;
			}
			else if(pSimulant->GetSimulantType()== IO_SIMULANT_TYPE_MODEL)
			{
			pModelElem = CreateModelElement(pSimulant, pSimulantElem);
			if(pModelElem)
				pSimulantElem = pModelElem;
				/*pSimulantElem->appendChild(pModelElem);*/
			}
		/*}*/



	}


	return pSimulantElem;


}

DOMElement *CIoSimDOMBuilder::CreateSimulatorChildElement(CIoSimulant *pSimulant, DOMElement *SimulatorElem, int iIndex)
{

	DOMElement *pChildSimulantElem = NULL;

	CIoSimulant *pChildSimulant = NULL;
	DOMElement *pChildSimulatorElem = NULL;
	DOMElement *pChildModelElem = NULL;
	if(m_pDOMDoc && pSimulant && SimulatorElem)
	{

		//if(pChildSimulantElem)
		//{
			if(pSimulant->GetSimulantType()== IO_SIMULANT_TYPE_SIMULATOR)
			{
			pChildSimulantElem = CreateSimulatorElement(pSimulant, pChildSimulantElem);
			//if(pChildSimulatorElem)
			//	pChildSimulantElem->appendChild(pChildSimulatorElem);
			}
			else if(pSimulant->GetSimulantType()== IO_SIMULANT_TYPE_MODEL)
			{
			pChildSimulantElem = CreateModelElement(pSimulant, pChildSimulantElem);
			//if(pChildModelElem)
			//	pChildSimulantElem->appendChild(pChildModelElem);
			}
		//}



	}


	return pChildSimulantElem;


}



DOMElement *CIoSimDOMBuilder::CreateSimulatorElement(CIoSimulant *pSimulant, DOMElement *SimulantElem, int iIndex)
{
	char sNumProps [10];
	char sIndex [10];
	char sprocid [10];
	int index = 0;
	char sCreateMethod[10];

	int iCurrentIndex;
	sprintf(sIndex, "%d", iIndex);
	int iNumParams=0;

	DOMElement *pEntitySetElem;
	DOMElement *pSimulatorElem = NULL;
	DOMElement *pLinksElem = NULL;
	DOMElement *pModelElem = NULL;
	DOMElement *pPropsElem = NULL;
	DOMElement *pPropElem = NULL;
	DOMElement *pChildSimulantElem = NULL;

	CIoSimulator *pSimulator = (CIoSimulator *)pSimulant;
	CIoSimulant *pCurrentSimulant = NULL;
	CIoEntitySet *pEntitySet=NULL;
	CIoParam *pParam = NULL;
	sprintf(sIndex, "%d", iIndex);

	if(m_pDOMDoc && pSimulator)
	{
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_SIMULATOR);
		m_SimulantStack.push(pSimulator);
		if(pSimulatorElem = m_pDOMDoc->createElement(X("simulator")))
		{
			sprintf(sCreateMethod, "%d", pSimulator->GetCreateMethod());

			//Set the simulator attributes
			pSimulatorElem->setAttribute(X("name"), X(pSimulator->GetSimulatorName()));
			pSimulatorElem->setAttribute(X("class"), X(pSimulator->GetSimulatorClass()));
			pSimulatorElem->setAttribute(X("index"), X(sIndex));
			
			if((pSimulator->GetProcID())>=0)
			{
				sprintf(sprocid, "%d", pSimulator->GetProcID());
				pSimulatorElem->setAttribute(X("procid"), X(sprocid));
			}


			pSimulatorElem->setAttribute(X("createmethod"), X(sCreateMethod));

			if(pParam = pSimulator->GetParams())
			{
				m_pCurrentSimulator = pSimulator;
				iNumParams = pParam->GetNumParams();
				//pSimulator->CreatePropArrayNames();
				//pSimulator->CreatePropNames();
				//pSimulator->CreatePropArrayFlags();
				//pSimulator->CreatePropFlags();
				if(iNumParams>0)
				{
					pPropsElem = CreatePropsElement(pSimulator->GetName(),pSimulator->GetArrayFlag(0), iNumParams, pSimulatorElem);
					pParam = pSimulator->GetProperty(0);
					while(pParam)
					{
						ResetDepthArray();
						m_iCurrentIndex = index;
						pPropElem = CreatePropElement(pParam, pPropsElem);
						if(pPropElem && pPropsElem)
							pPropsElem->appendChild(pPropElem);

						pParam = pParam->GetNextParam();
						index ++;					
					}
					if(pPropsElem)
						pSimulatorElem->appendChild(pPropsElem);
				}

/*								m_pCurrentEntitySet=pSimulator->GetEntitySet();
				if(m_pCurrentEntitySet)
				{
					pEntitySetElem = CreateEntitySetElement(m_pCurrentEntitySet, pModelElem);

					if(pEntitySetElem)
							pSimulatorElem->appendChild(pEntitySetElem);
					CIoEntitySet *pNextEntitySet=NULL;
					while((pNextEntitySet = m_pCurrentEntitySet->GetNextEntitySet())!=NULL)
					{

						//pNextEntitySet=(pEntitySet->m_pNextEntitySet);
						m_pCurrentEntitySet = pNextEntitySet;
						//if(m_pCurrentEntitySet=pModel->GetEntitySet())
							pEntitySetElem = CreateEntitySetElement(m_pCurrentEntitySet, pModelElem);

					if(pEntitySetElem)
							pSimulatorElem->appendChild(pEntitySetElem);

					}
				}*/

			}

			//Now go through each simulant of this simulator
			//and create each simulant
			iCurrentIndex = 0;
			pCurrentSimulant = pSimulator->GetSimulant();
			while(pCurrentSimulant)
			{
				pChildSimulantElem = CreateSimulatorChildElement(pCurrentSimulant, pSimulatorElem, iCurrentIndex);
				if(pChildSimulantElem)
					pSimulatorElem->appendChild(pChildSimulantElem);

				iCurrentIndex ++;
				pCurrentSimulant = pCurrentSimulant->GetNextSimulant();

			}
			
			//add the links element
			if(pSimulator->GetNumLinks())
			{
			   	if(pLinksElem=CreateLinksElement(pSimulator,pSimulatorElem))
			   	    pSimulatorElem->appendChild(pLinksElem);
			}
		}
		m_SimElementStack.pop();
		m_SimulantStack.pop();
	}
	return pSimulatorElem;
}

DOMElement *CIoSimDOMBuilder::CreateModelElement(CIoSimulant *pSimulant, DOMElement *SimulantEleme, int iIndex)
{
	DOMElement *pModelElem = NULL;
	char sCreateMethod[10];
	char sIndex [10];

	/*v11 23/07/2003*/
	int iNumParams = 0;
	char sNumProps [10];
	char sprocid [10];
	//CIoParam *pParam = NULL;
	int index = 0;
	DOMElement *pPropElem = NULL;
	/*v11 23/07/2003*/

	sprintf(sIndex, "%d", iIndex);
	DOMElement *pPropsElem = NULL;
	DOMElement *pModelPropsElem = NULL;
	DOMElement *pEntitySetElem = NULL;

	CIoEntitySet *pEntitySet = NULL;
	CIoModel *pModel = (CIoModel *)pSimulant;
	ResetDepthArray();
	CIoParam *pParam = NULL;
	if(m_pDOMDoc && pModel)
	{
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_MODEL);
		m_SimulantStack.push(pModel);

		if(pModelElem = m_pDOMDoc->createElement(X("model")))
		{
			//Set the model attributes
			pModelElem->setAttribute(X("name"), X(pModel->GetModelName()));
			pModelElem->setAttribute(X("class"), X(pModel->GetModelClass()));
			pModelElem->setAttribute(X("index"), X(sIndex));

			sprintf(sCreateMethod, "%d", pModel->GetCreateMethod());
			pModelElem->setAttribute(X("createmethod"), X(sCreateMethod));

			if((pModel->GetProcID())>=0)
			{
				sprintf(sprocid, "%d", pModel->GetProcID());
				pModelElem->setAttribute(X("procid"), X(sprocid));
			}


			if(pParam = pModel->m_pProperties)
			{
			m_pCurrentModel = pModel;
			//pModelPropsElem = CreateModelCreatorElement(pModel, pModelElem);
			//if(pModelPropsElem)
			//	pModelElem->appendChild(pModelPropsElem);

			/*v11 23/07/2003 Removal of model creator element*/
			/*CreateModelCreatorElement*/
			//Set the model attributes
			//if(pParam = pModel->m_pProperties)
				iNumParams = pParam->GetNumParams();

			if(iNumParams>0)
			{

				//pModel->CreatePropArrayNames();
				//pModel->CreatePropNames();
				//pModel->CreatePropArrayFlags();
				//pModel->CreatePropFlags();
				pPropsElem = CreatePropsElement(pModel->GetArrayName(0), pModel->GetArrayFlag(0),iNumParams, pModelElem);
				pParam = pModel->GetProperty(0);

				while(pParam)
				{
					ResetDepthArray();
					m_iCurrentIndex = index;
					pPropElem = CreatePropElement(pParam, pPropsElem);
					if(pPropElem && pPropsElem /*&& GetPropFlag()==0*/)
						pPropsElem->appendChild(pPropElem);

					pParam = pParam->GetNextParam();
					index ++;					
				}
				if(pPropsElem)
					pModelElem->appendChild(pPropsElem);

				m_pCurrentEntitySet=pModel->GetEntitySet();
				if(m_pCurrentEntitySet)
				{
					pEntitySetElem = CreateEntitySetElement(m_pCurrentEntitySet, pModelElem);

					if(pEntitySetElem)
							pModelElem->appendChild(pEntitySetElem);
					CIoEntitySet *pNextEntitySet=NULL;
					while((pNextEntitySet = m_pCurrentEntitySet->GetNextEntitySet())!=NULL)
					{

						//pNextEntitySet=(pEntitySet->m_pNextEntitySet);
						m_pCurrentEntitySet = pNextEntitySet;
						//if(m_pCurrentEntitySet=pModel->GetEntitySet())
							pEntitySetElem = CreateEntitySetElement(m_pCurrentEntitySet, pModelElem);

					if(pEntitySetElem)
							pModelElem->appendChild(pEntitySetElem);

					}
				}
			}




			}
		}
		m_SimElementStack.pop();
		m_SimulantStack.pop();

	}



	return pModelElem;



}

DOMElement *CIoSimDOMBuilder::CreateEntitySetElement(CIoEntitySet *pEntitySet, DOMElement *ModelElem)
{

	DOMElement *pEntitySetElem = NULL;
	char snEntities [10];
	int nEntities=0;

	CIoEntityTypeSet *pEntityTypeSet = NULL;
	int iNumParams = 0;
	int iNumEParams = 0;
	char sNumProps [10];
	//CIoParam *pParam = NULL;
	int index = 0;
	DOMElement *pPropElem = NULL;
	if(pEntitySet) nEntities=pEntitySet->GetNum();
	sprintf(snEntities, "%d", nEntities);
	DOMElement *pPropsElem = NULL;
	DOMElement *pEPropsElem = NULL;
	DOMElement *pESPropsElem = NULL;
	DOMElement *pEntityTypeSetElem = NULL;

	ResetDepthArray();
	CIoParam *pParam = NULL;
	CIoParam *pEParam = NULL;
	if(m_pDOMDoc && pEntitySet)
	{
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYSET);

		if(pEntitySetElem = m_pDOMDoc->createElement(X("entityset")))
		{
			//Set the model attributes
			pEntitySetElem->setAttribute(X("name"), X(pEntitySet->GetEntitySetName()));
			pEntitySetElem->setAttribute(X("class"), X(pEntitySet->GetEntitySetClass()));
			pEntitySetElem->setAttribute(X("numentities"), X(snEntities));


			if(pParam = pEntitySet->m_pProperties)
			{
			m_pCurrentEntitySet = pEntitySet;
			//pModelPropsElem = CreateModelCreatorElement(pModel, pModelElem);
			//if(pModelPropsElem)
			//	pModelElem->appendChild(pModelPropsElem);

			/*v11 23/07/2003 Removal of model creator element*/
			/*CreateModelCreatorElement*/
			//Set the model attributes
			//if(pParam = pModel->m_pProperties)
				iNumParams = pParam->GetNumParams();
	
			if(iNumParams>0)
			{

				//pEntitySet->CreatePropArrayNames();
				//pEntitySet->CreatePropNames();
				//pEntitySet->CreatePropArrayFlags();
				//pEntitySet->CreatePropFlags();

				pPropsElem = CreatePropsElement(pEntitySet->GetEntitySetName(),pEntitySet->GetArrayFlag(0), iNumParams, pEntitySetElem);
				pParam = pEntitySet->GetProperty(0);

				while(pParam)
				{
					ResetDepthArray();
					m_iCurrentIndex = index;
					pPropElem = CreatePropElement(pParam, pPropsElem);
					if(pPropElem && pPropsElem /*&& GetPropFlag()==0*/)
						pPropsElem->appendChild(pPropElem);

					pParam = pParam->GetNextParam();
					index ++;					
				}
				
				if(pPropsElem)
					pEntitySetElem->appendChild(pPropsElem);

				if(pEntityTypeSet=pEntitySet->GetEntityTypeSet())
					if(pEntityTypeSetElem = CreateEntityTypeSetElement(pEntityTypeSet, pEntitySetElem))
						pEntitySetElem->appendChild(pEntityTypeSetElem);


				//pEntitySet->DeleteNames();
				//pEntitySet->DeleteFlags();
			}




			}

			//entity params
			
			if(pEParam = pEntitySet->GetEDefaultParams())
			{
				iNumEParams = pEParam->GetNumParams();
			int index=0;
			if(iNumEParams>0)
			{

				//pEntitySet->CreatePropArrayNames();
				//pEntitySet->CreatePropNames();
				//pEntitySet->CreatePropArrayFlags();
				//pEntitySet->CreatePropFlags();
				m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE);
				pEPropsElem = CreateEntityPropsElement(pEntitySet->GetEArrayName(0),pEntitySet->GetEArrayFlag(0), iNumEParams, pEntitySetElem);
				pEParam = pEParam->GetParam(0);

				while(pEParam)
				{
					ResetDepthArray();
					m_iCurrentIndex = index;
					pPropElem = CreatePropElement(pEParam, pPropsElem);
					if(pPropElem && pEPropsElem /*&& GetPropFlag()==0*/)
						pEPropsElem->appendChild(pPropElem);

					pEParam = pEParam->GetNextParam();
					index ++;					
				}
				
				if(pEPropsElem)
					pEntitySetElem->appendChild(pEPropsElem);

				m_SimElementStack.pop();
			}
			
			}//End of entity params

		}//end of create entity set element check
		m_SimElementStack.pop();

		}



	return pEntitySetElem;


}

DOMElement *CIoSimDOMBuilder::CreateEntityTypeSetElement(CIoEntityTypeSet *pEntityTypeSet, DOMElement *pEntitySetElem)
{

	DOMElement *pEntityTypeSetElem = NULL;
	DOMElement *pEntityTypeElem = NULL;

	char snEntityTypes [10];
	int nEntityTypes=0;
	CIoEntityType *pEntityType=NULL;
	
	int iNumParams = 0;
	char sNumProps [10];
	//CIoParam *pParam = NULL;
	int i, index = 0;
	DOMElement *pPropElem = NULL;
	if(pEntityTypeSet) nEntityTypes=pEntityTypeSet->GetNumEntityTypes();
	sprintf(snEntityTypes, "%d", nEntityTypes);
	DOMElement *pPropsElem = NULL;
	DOMElement *pESPropsElem = NULL;

	ResetDepthArray();
	CIoParam *pParam = NULL;
	if(m_pDOMDoc && pEntityTypeSet)
	{
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYTYPESET);

		if(pEntityTypeSetElem = m_pDOMDoc->createElement(X("entitytypeset")))
		{
			//Set the model attributes
			if( (pEntityTypeSet->GetEntityTypeSetName()) && (strlen(pEntityTypeSet->GetEntityTypeSetName())>0))
				pEntityTypeSetElem->setAttribute(X("name"), X(pEntityTypeSet->GetEntityTypeSetName()));
			pEntityTypeSetElem->setAttribute(X("class"), X(pEntityTypeSet->GetEntityTypeSetClass()));
			pEntityTypeSetElem->setAttribute(X("numentitytypes"), X(snEntityTypes));


			if((pParam = pEntityTypeSet->m_pProperties) )
			{
			m_pCurrentEntityTypeSet = pEntityTypeSet;
			//pModelPropsElem = CreateModelCreatorElement(pModel, pModelElem);
			//if(pModelPropsElem)
			//	pModelElem->appendChild(pModelPropsElem);

			/*v11 23/07/2003 Removal of model creator element*/
			/*CreateModelCreatorElement*/
			//Set the model attributes
			//if(pParam = pModel->m_pProperties)
				iNumParams = pParam->GetNumParams();
	
			if(iNumParams>0)
			{

				//pEntityTypeSet->CreatePropArrayNames();
				//pEntityTypeSet->CreatePropNames();
				//pEntityTypeSet->CreatePropArrayFlags();
				//pEntityTypeSet->CreatePropFlags();
				pPropsElem = CreatePropsElement(pEntityTypeSet->GetEntityTypeSetName(), pEntityTypeSet->GetArrayFlag(0), iNumParams, pEntityTypeSetElem);
				pParam = pEntityTypeSet->GetProperty(0);

				while(pParam)
				{
					ResetDepthArray();
					m_iCurrentIndex = index;
					pPropElem = CreatePropElement(pParam, pPropsElem);
					if(pPropElem && pPropsElem /*&& GetPropFlag()==0*/)
						pPropsElem->appendChild(pPropElem);

					pParam = pParam->GetNextParam();
					index ++;					
				}
				if(pPropsElem)
					pEntityTypeSetElem->appendChild(pPropsElem);




			}

		

			}
				nEntityTypes=pEntityTypeSet->GetNumEntityTypes();
				for(i=0; i<nEntityTypes; i++)
					if(pEntityType = pEntityTypeSet->GetEntityType(i))
						if(pEntityTypeElem=CreateEntityTypeElement(pEntityType, pEntityTypeSetElem))
												pEntityTypeSetElem->appendChild(pEntityTypeElem);

		}
		m_SimElementStack.pop();
		

	}



	return pEntityTypeSetElem;




}

DOMElement *CIoSimDOMBuilder::CreateEntityTypeElement(CIoEntityType *pEntityType, DOMElement *pEntityTypeSetElem)
{
	char snetindex[10];
	int netindex;

	DOMElement *pEntityTypeElem = NULL;
	
	char snEntityTypeProps [10];
	int nEntityTypeProps=0;
//	CIoEntityType *pEntityType=NULL;
	int iNumParams = 0;
	char sNumProps [10];
	//CIoParam *pParam = NULL;
	int i, index = 0;
	DOMElement *pPropElem = NULL;
	DOMElement *pPropsElem = NULL;
	DOMElement *pESPropsElem = NULL;

	if(pEntityType) netindex=pEntityType->GetID();
	sprintf(snetindex, "%d", netindex);

	ResetDepthArray();
	CIoParam *pParam = NULL;
	if(m_pDOMDoc && pEntityType)
	{
		m_SimElementStack.push(IO_XMLP_STACK_ELEMENT_ENTITYTYPE);

		if(pEntityTypeElem = m_pDOMDoc->createElement(X("entitytype")))
		{
			//Set the model attributes
			if( (pEntityType->GetEntityTypeName()) && (strlen(pEntityType->GetEntityTypeName())>0))
				pEntityTypeElem->setAttribute(X("name"), X(pEntityType->GetEntityTypeName()));
			pEntityTypeElem->setAttribute(X("class"), X(pEntityType->GetEntityTypeClass()));
			pEntityTypeElem->setAttribute(X("index"), X(snetindex));


			if((pParam = pEntityType->m_pProperties) )
			{
			m_pCurrentEntityType = pEntityType;
			//pModelPropsElem = CreateModelCreatorElement(pModel, pModelElem);
			//if(pModelPropsElem)
			//	pModelElem->appendChild(pModelPropsElem);

			/*v11 23/07/2003 Removal of model creator element*/
			/*CreateModelCreatorElement*/
			//Set the model attributes
			//if(pParam = pModel->m_pProperties)
				iNumParams = pParam->GetNumParams();
	
			if(iNumParams>0)
			{

				//pEntityType->CreatePropArrayNames();
				//pEntityType->CreatePropNames();
				//pEntityType->CreatePropArrayFlags();
				//pEntityType->CreatePropFlags();
				pPropsElem = CreatePropsElement(pEntityType->GetEntityTypeName(), pEntityType->GetArrayFlag(0), iNumParams, pEntityTypeElem);
				pParam = pEntityType->GetProperty(0);

				while(pParam)
				{
					ResetDepthArray();
					m_iCurrentIndex = index;
					pPropElem = CreatePropElement(pParam, pPropsElem);
					if(pPropElem && pPropsElem /*&& GetPropFlag()==0*/)
						pPropsElem->appendChild(pPropElem);

					pParam = pParam->GetNextParam();
					index ++;					
				}
				if(pPropsElem)
					pEntityTypeElem->appendChild(pPropsElem);



			}




			}
		}
		m_SimElementStack.pop();
		


	}
		return pEntityTypeElem;
}


DOMElement *CIoSimDOMBuilder::CreateModelCreatorElement(CIoModel *pModel, DOMElement *ModelElem)
{
	/*v11 23/07/2003*/
	/*Function no longer used*/
	DOMElement *pModelParamsElem=NULL;
	DOMElement *pPropsElem = NULL;
	DOMElement *pPropElem = NULL;
	int iNumParams = 0;
	char sNumProps [10];
	CIoParam *pParam = NULL;
	int index = 0;

	if(m_pDOMDoc && pModel)
	{
		if(pModelParamsElem = m_pDOMDoc->createElement(X("modelcreator")))
		{
			//Set the model attributes
			if(pParam = pModel->m_pProperties)
				iNumParams = pParam->GetNumParams();
	
			if(iNumParams>0)
			{

				pModel->CreatePropArrayNames();
				pModel->CreatePropNames();
				pPropsElem = CreatePropsElement(pModel->GetName(), pModel->GetArrayFlag(0), iNumParams, pModelParamsElem);
				pParam = pModel->GetProperty(0);

				while(pParam)
				{
					ResetDepthArray();
					m_iCurrentIndex = index;
					pPropElem = CreatePropElement(pParam, pPropsElem);
					if(pPropElem && pPropsElem)
						pPropsElem->appendChild(pPropElem);

					pParam = pParam->GetNextParam();
					index ++;					
				}
				if(pPropsElem)
					pModelParamsElem->appendChild(pPropsElem);
			}
		}
	}
	return pModelParamsElem;
}

DOMElement *CIoSimDOMBuilder::CreatePropsElement(string sName, int iFlag, int iNumProps, DOMElement *ParentEleme)//parent could be simulant, modelparams or prop
{
	char sNumProps [10];
	char sFlag [10];

	DOMElement *pPropsElement=NULL;
 	sprintf(sNumProps, "%d", iNumProps);
	sprintf(sFlag, "%d", iFlag);

		if(m_pDOMDoc && (pPropsElement = m_pDOMDoc->createElement(X("props"))))
		{
			//Set the model attributes
			pPropsElement->setAttribute(X("name"), X(sName.c_str()));
			pPropsElement->setAttribute(X("numprops"), X(sNumProps));
			pPropsElement->setAttribute(X("flag"), X(sFlag));
		}
	return pPropsElement;
}


DOMElement *CIoSimDOMBuilder::CreateArrayElement(CIoParam *pParams, DOMElement *ParentProps)//parent could be simulant, modelparams or prop
{
	char sNumProps [10];
	CIoParam *pParam;
	DOMElement *pChildValueElement;
	int i;

	DOMElement *pArrayElement=NULL;

		if(m_pDOMDoc && (pArrayElement = m_pDOMDoc->createElement(X("array"))))
		{
			sprintf(sNumProps, "%d", pParams->GetNumParams());
			pArrayElement->setAttribute(X("n"), X(sNumProps));
			
			for(i=0; i<pParams->GetNumParams(); i++)
			{
				if(pParam=pParams->GetParam(i))
				{
					switch(pParam->GetType())
					{
					case IO_PARAM_ARRAY :
						pChildValueElement = CreateArrayElement(pParam, pArrayElement);
						
						break;
			
					case IO_PARAM_INTEGER :
							pChildValueElement = CreateIntElement(pParam, pArrayElement);
						break;
					case IO_PARAM_FLOAT :
							pChildValueElement = CreateFloatElement(pParam, pArrayElement);
						break;
					case IO_PARAM_VEC :
							//pChildValueElement = CreateVectorElement(pParams, pPropElement);
							pChildValueElement = CreateVecElement(pParam, pArrayElement);
						break;
					case IO_PARAM_MAT :
							pChildValueElement = CreateMatElement(pParam, pArrayElement);
						break;
					case IO_PARAM_MMAT3D :
							pChildValueElement = Createmmat3dElement(pParam, pArrayElement);
						break;

					case IO_PARAM_STRING :
							pChildValueElement = CreateStringElement(pParam, pArrayElement);
						break;

					case IO_PARAM_STRINGARRAY :
							pChildValueElement = CreateStringArrayElement(pParam, pArrayElement);
						break;

			
			
					}//end switch
				}//end check param not null
			}//end loop over params
			
			if(ParentProps && pArrayElement)
				ParentProps->appendChild(pArrayElement);
			
			
			
			
		}
	return pArrayElement;
}


DOMElement *CIoSimDOMBuilder::CreateEntityPropsElement(string sName, int iFlag, int iNumProps, DOMElement *ParentEleme)//parent could be simulant, modelparams or prop
{
	char sNumProps [10];
	char sFlag [10];
	DOMElement *pPropsElement=NULL;
 	sprintf(sNumProps, "%d", iNumProps);
	sprintf(sFlag, "%d", iFlag);
		if(m_pDOMDoc && (pPropsElement = m_pDOMDoc->createElement(X("entityprops"))))
		{

			//Set the model attributes
			pPropsElement->setAttribute(X("name"), X(sName.c_str()));
			pPropsElement->setAttribute(X("numprops"), X(sNumProps));
			pPropsElement->setAttribute(X("flag"), X(sFlag));
		}
	return pPropsElement;
}


DOMElement *CIoSimDOMBuilder::CreatePropElement(CIoParam *pParams, DOMElement *ParentProps)
{
	DOMElement *pPropElement=NULL;
	DOMElement *pChildPropsElement=NULL;
	DOMElement *pChildPropElement=NULL;
	DOMElement *pChildValueElement=NULL;

	int iNumParams = 0;
	char sIndex [20];
	char sFlag [20];
    string sPropName;
	string sPropArrayName ;
	char *sPropsName = NULL; //name of current array
	//Get Prop Name
    //check if write flag set for this parameter
	//using stack of simulants, and simulant type;
	//Different cases 
	//pPropElement->

	//m_iCurrentIndex is index of this property
	sprintf(sIndex, "%d", m_iCurrentIndex);
	sprintf(sFlag, "%d", GetPropFlag());
	sPropName = GetPropName();  //Function to get name of property
	if(pParams && TestPropFlag())  //Function to check if write flag set for this property
	{
		if(m_pDOMDoc && (pPropElement = m_pDOMDoc->createElement(X("prop"))))
		{
			//Set the model attributes
			pPropElement->setAttribute(X("name"), X(sPropName.c_str()));
			pPropElement->setAttribute(X("index"), X(sIndex));
			pPropElement->setAttribute(X("flag"), X(sFlag));

			string sinfilename=GetPropInfilename();
			if(sinfilename.length()>0)
							pPropElement->setAttribute(X("infile"), X(sinfilename.c_str()));

		}
		switch(pParams->GetType())
		{
		case IO_PARAM_ARRAY :
			pChildValueElement = CreateArrayElement(pParams, pPropElement);
			
			break;

		case IO_PARAM_INTEGER :
				pChildValueElement = CreateIntElement(pParams, pPropElement);
			break;
		case IO_PARAM_FLOAT :
				pChildValueElement = CreateFloatElement(pParams, pPropElement);
			break;
		case IO_PARAM_VEC :
				//pChildValueElement = CreateVectorElement(pParams, pPropElement);
				pChildValueElement = CreateVecElement(pParams, pPropElement);
			break;
		case IO_PARAM_MAT :
				pChildValueElement = CreateMatElement(pParams, pPropElement);
			break;
		case IO_PARAM_MMAT3D :
				pChildValueElement = Createmmat3dElement(pParams, pPropElement);
			break;


		case IO_PARAM_STRING :
				pChildValueElement = CreateStringElement(pParams, pPropElement);
			break;


	case IO_PARAM_STRINGARRAY :
				pChildValueElement = CreateStringArrayElement(pParams, pPropElement);
			break;


		}
	}


	return pPropElement;
}

DOMElement *CIoSimDOMBuilder::CreateIntElement(CIoParam *pParams, DOMElement *ParentProps)
{
	DOMElement *pIntElement=NULL;
	char sInt [20];
	int iInt = 0;

    if(m_pDOMDoc && (pIntElement = m_pDOMDoc->createElement(X("int"))))
	{
		if(pParams)
			iInt = pParams->GetIntParam();

		sprintf(sInt, "%d", iInt);
		DOMText*    IntVal = m_pDOMDoc->createTextNode(X(sInt));
        pIntElement->appendChild(IntVal);

		if(ParentProps && pIntElement)
			ParentProps->appendChild(pIntElement);
	}

	return pIntElement;
}

DOMElement *CIoSimDOMBuilder::CreateFloatElement(CIoParam *pParams, DOMElement *ParentProps)
{
	DOMElement *pFloatElement=NULL;

	char sFloat [40];
	float fFloat = 0;

    if(m_pDOMDoc && (pFloatElement = m_pDOMDoc->createElement(X("float"))))
	{
		if(pParams)
			fFloat = pParams->GetFloatParam();

		sprintf(sFloat, "%f", fFloat);
		DOMText*    FloatVal = m_pDOMDoc->createTextNode(X(sFloat));
        pFloatElement->appendChild(FloatVal);

	
		if(ParentProps && pFloatElement)
			ParentProps->appendChild(pFloatElement);
	}


	return pFloatElement;
}

DOMElement *CIoSimDOMBuilder::CreateVectorElement(CIoParam *pParams, DOMElement *ParentProps)
{
	DOMElement *pVectorElement=NULL;
	int iVecSize = 0;
	char sVecSize [20];

	vec *pVec = NULL;
	if(pParams)
	{
		if((pVec = pParams->GetVecParam()) && m_pDOMDoc && (pVectorElement = m_pDOMDoc->createElement(X("vector"))))
		{
			iVecSize = pVec->length();
			sprintf(sVecSize, "%d", iVecSize);
		    pVectorElement->setAttribute(X("size"), X(sVecSize));

			CreateVecElement(pParams,pVectorElement);
		
			if(ParentProps && pVectorElement)
				ParentProps->appendChild(pVectorElement);
		}
	}



	return pVectorElement;
}

DOMElement *CIoSimDOMBuilder::CreateMatElement(CIoParam *pParams, DOMElement *ParentProps)
{
	DOMElement *pMatElement=NULL;
	//CIoParam *pVecParam = new CIoParam;
	std::ostringstream matstring;

	//char *sMat, *sTempMat;
	char sMatrSize [20];
	char sMatcSize [20];
	
	float fMat;

	matrix *pMatrix = NULL;
	int j;
	int imatr=0;
	int imatc=0;
	//vec *pVec = NULL;
	if(pParams)
	{
		if((pMatrix = pParams->GetMatParam()) && m_pDOMDoc && (pMatElement = m_pDOMDoc->createElement(X("mat"))))
		{
			imatr = pMatrix->depth();
			sprintf(sMatrSize, "%d", imatr);
		    pMatElement->setAttribute(X("rows"), X(sMatrSize));

			imatc = pMatrix->width();
			sprintf(sMatcSize, "%d", imatc);
	        pMatElement->setAttribute(X("cols"), X(sMatcSize));

			string sinfilename=GetPropInfilename();
			if(sinfilename.length()>0)
			{
				//open the file and save the strings
				ofstream outfile;
				outfile.open((const char *)(sinfilename.c_str()));
				// >> i/o operations here <<
				outfile << *pMatrix;
				outfile.close();
			}
			else
			{

				const int ism=imatr*imatc*10;
				const int istm=imatr*imatc*10;
				char *sMat = new char[ism]; 
				char *sTempMat = new char[istm]; 

				//char sMat[ism];
				//char sTempMat[istm];
				sMat[0]='\0';
				sTempMat[0]='\0';
				for(int i=0; i<imatr; i++)
				{
					for(j=0; j<imatc; j++)
					{
						//pVec->set(j, pMatrix->getval(i,j));
						//strcpy(sTempMat, sMat);
						fMat = pMatrix->getval(i,j);
						//if(j<=20)
						//	sprintf(sMat, "%s%f ", sTempMat,fMat);
						//else
						//	sprintf(sMat, "%s%f \n", sTempMat,fMat);
						if(j<20)	
							matstring << fMat << " ";
						else
							matstring << fMat << " " << "\n";	
							
						//printf("smat is %s \n",sMat);
						
					}

					//pVecParam->SetParam(pVec);
					//CreateVecElement(pVecParam,pMatElement);
								
				}
				
				//DOMText*    MatVal = m_pDOMDoc->createTextNode(X(sMat));
				DOMText*    MatVal = m_pDOMDoc->createTextNode(X(matstring.str().c_str()));
				pMatElement->appendChild(MatVal);	

			}
			//if(pVec) delete pVec;
			if(ParentProps && pMatElement)
				ParentProps->appendChild(pMatElement);
			//delete [] sMat;
			//delete [] sTempMat;
			
		
		}
	}



	//delete pVecParam;
	return pMatElement;
}

DOMElement *CIoSimDOMBuilder::Createmmat3dElement(CIoParam *pParams, DOMElement *ParentProps)
{
	DOMElement *pMatElement=NULL;
	//CIoParam *pVecParam = new CIoParam;
	std::ostringstream matstring;

	//char *sMat, *sTempMat;
	char sMatrSize [20];
	char sMatcSize [20];
	char sMatdSize [20];

	char smMatrSize [20];
	char smMatcSize [20];
	
	float fMat;

	mmat3d *pMatrix = NULL;
	int j,k,l,m;
	int imatr=0;
	int imatc=0;
	int imatd=0;
	int immatc=0;
	int immatr=0;
	//vec *pVec = NULL;
	if(pParams)
	{
		if((pMatrix = pParams->Getmmat3dParam()) && m_pDOMDoc && (pMatElement = m_pDOMDoc->createElement(X("mmat3d"))))
		{
			imatr = pMatrix->rows();
			sprintf(sMatrSize, "%d", imatr);
		    pMatElement->setAttribute(X("rows"), X(sMatrSize));

			imatc = pMatrix->cols();
			sprintf(sMatcSize, "%d", imatc);
	        pMatElement->setAttribute(X("cols"), X(sMatcSize));

			imatd = pMatrix->depth();
			sprintf(sMatdSize, "%d", imatd);
	        pMatElement->setAttribute(X("depth"), X(sMatdSize));

			immatr = pMatrix->mrows();
			sprintf(smMatrSize, "%d", immatr);
		    pMatElement->setAttribute(X("mrow"), X(smMatrSize));

			immatc = pMatrix->mcols();
			sprintf(smMatcSize, "%d", immatc);
	        pMatElement->setAttribute(X("mcol"), X(smMatcSize));

			string sinfilename=GetPropInfilename();
			if(sinfilename.length()>0)
			{
				//open the file and save the strings
				ofstream outfile;
				outfile.open((const char *)(sinfilename.c_str()));
				// >> i/o operations here <<
				outfile << *pMatrix;
				outfile.close();
			}
			else
			{

				//const int ism=imatr*imatc*10;
				//const int istm=imatr*imatc*10;
				//char *sMat = new char[ism]; 
				//char *sTempMat = new char[istm]; 

				//char sMat[ism];
				//char sTempMat[istm];
				//sMat[0]='\0';
				//sTempMat[0]='\0';
				for(int i=0; i<imatr; i++)
				{
					for(j=0; j<imatc; j++)
					{
						for(int k=0; k<imatd; k++)
						{
							for(int l=0; l<immatr; l++)
							{
								for(m=0; m<immatc; m++)
								{


									//pVec->set(j, pMatrix->getval(i,j));
									//strcpy(sTempMat, sMat);
									fMat = pMatrix->getval(i,j,k,l,m);
									//if(j<=20)
									//	sprintf(sMat, "%s%f ", sTempMat,fMat);
									//else
									//	sprintf(sMat, "%s%f \n", sTempMat,fMat);
									if(j<20)	
										matstring << fMat << " ";
									else
										matstring << fMat << " " << "\n";	
										
									//printf("smat is %s \n",sMat);
									
								}

								//pVecParam->SetParam(pVec);
								//CreateVecElement(pVecParam,pMatElement);
											
							}
						}
					}
				}
				
				//DOMText*    MatVal = m_pDOMDoc->createTextNode(X(sMat));
				DOMText*    MatVal = m_pDOMDoc->createTextNode(X(matstring.str().c_str()));
				pMatElement->appendChild(MatVal);	

			}
			//if(pVec) delete pVec;
			if(ParentProps && pMatElement)
				ParentProps->appendChild(pMatElement);
			//delete [] sMat;
			//delete [] sTempMat;
			
		}
	}



	//delete pVecParam;
	return pMatElement;
}



DOMElement *CIoSimDOMBuilder::CreateStringElement(CIoParam *pParams, DOMElement *ParentProps)
{
	DOMElement *pStringElement=NULL;

	char *sString=NULL;


    if(m_pDOMDoc && (pStringElement = m_pDOMDoc->createElement(X("string"))))
	{
		if(pParams)
			sString = pParams->GetStringParam();

			string sinfilename=GetPropInfilename();
			if(sinfilename.length()>0)
			{
				//open the file and save the strings
				ofstream outfile;
				outfile.open((const char *)(sinfilename.c_str()));
				// >> i/o operations here <<
				outfile << *sString;
				outfile.close();
			}
			else
			{
				if(sString)
				{
					DOMText*    StringVal = m_pDOMDoc->createTextNode(X(sString));
					pStringElement->appendChild(StringVal);
				}
				else
				{
					DOMText*    StringVal = m_pDOMDoc->createTextNode(X("NULL"));
					pStringElement->appendChild(StringVal);
				}
			}
		if(ParentProps && pStringElement)
			ParentProps->appendChild(pStringElement);
	}


	return pStringElement;
}


DOMElement *CIoSimDOMBuilder::CreateStringArrayElement(CIoParam *pParams, DOMElement *ParentProps)
{
	DOMElement *pStringArrayElement=NULL;

	char *sString=NULL;
    IoStringArray *pStringArray=NULL;

    if(m_pDOMDoc && (pStringArrayElement = m_pDOMDoc->createElement(X("stringarray"))))
	{
		if(pParams )
			pStringArray = pParams->GetStringArrayParam();

			string sinfilename=GetPropInfilename();
			if(sinfilename.length()>0)
			{
				//open the file and save the strings
				ofstream outfile;
				outfile.open((const char *)(sinfilename.c_str()));
				// >> i/o operations here <<
				outfile << *pStringArray;
				outfile.close();
			}
			else
			{
				if(pStringArray )
				{
					string tstr=pStringArray->GetAllStrings();
					sString=(char *)(tstr.c_str());
					DOMText*    StringVal = m_pDOMDoc->createTextNode(X(sString));
					pStringArrayElement->appendChild(StringVal);
				}
				else
				{
					DOMText*    StringVal = m_pDOMDoc->createTextNode(X("NULL"));
					pStringArrayElement->appendChild(StringVal);
				}
			}
			if(ParentProps && pStringArrayElement)
				ParentProps->appendChild(pStringArrayElement);
	}


	return pStringArrayElement;
}


DOMElement *CIoSimDOMBuilder::CreateVecElement(CIoParam *pParams, DOMElement *ParentProps)
{
	DOMElement *pVecElement=NULL;
	std::ostringstream vecstring;

	int iVecSize = 0;
	char sVec [300];
	char sTempVec [300];
	char sVecSize [20];
	
	float fVec=0;
	int i;
	sVec [0] ='\0';
	sTempVec [0] = '\0';
//	sTempVec = "";
	vec *pVec = NULL;
	if(pParams)
	{
		if((pVec = pParams->GetVecParam()) && m_pDOMDoc && (pVecElement = m_pDOMDoc->createElement(X("vec"))))
		{

			iVecSize = pVec->length();
			sprintf(sVecSize, "%d", iVecSize);
		    pVecElement->setAttribute(X("size"), X(sVecSize));			
						string sinfilename=GetPropInfilename();
			if(sinfilename.length()>0)
			{
				//open the file and save the strings
				ofstream outfile;
				outfile.open((const char *)(sinfilename.c_str()));
				// >> i/o operations here <<
				outfile << *pVec;
				outfile.close();
			}
			else
			{
				for(int i=0; i<iVecSize; i++)
				{
					//strcpy(sTempVec, sVec);
					fVec = pVec->get(i);
					//sprintf(sVec, "%s%f ", sTempVec,fVec);
					
					if(i<20)
						vecstring << fVec << " ";
					else
						vecstring << fVec << " " << "\n";				
					
				}
				//DOMText*    VecVal = m_pDOMDoc->createTextNode(X(sVec));
				DOMText*    VecVal = m_pDOMDoc->createTextNode(X(vecstring.str().c_str()));
				pVecElement->appendChild(VecVal);
	
			}
			if(ParentProps && pVecElement)
				ParentProps->appendChild(pVecElement);
		}
	}




	return pVecElement;
}



string CIoSimDOMBuilder::GetPropName()
{
	string sPropName;
	string strprop;
	CIoSimulant *pSimulant = (CIoSimulant *)m_SimulantStack.top();

	if(m_iArrayDepth>0)
	{
		//Using current array of array indices
		CreateArrayMap();
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			sPropName = pSimulant->GetChildPropertyName(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			sPropName = m_pSimulation->GetChildPropertyName(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			sPropName = m_pCurrentEntitySet->GetChildPropertyName(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			sPropName = m_pCurrentEntitySet->GetEArrayName(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			sPropName = m_pCurrentEntityTypeSet->GetChildPropertyName(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			sPropName = m_pCurrentEntityType->GetChildPropertyName(m_iCurrentIndex, m_sArrayMap);
			break;


		}
	}
	else
	{
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			strprop = pSimulant->GetPropertyName(m_iCurrentIndex);
			//strcpy(spropname,(char *)strprop.c_str();
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			strprop = m_pSimulation->GetPropertyName(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			strprop = m_pCurrentEntitySet->GetPropertyName(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			strprop = m_pCurrentEntitySet->GetEPropertyName(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			strprop = m_pCurrentEntityTypeSet->GetPropertyName(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			strprop = m_pCurrentEntityType->GetPropertyName(m_iCurrentIndex);
			break;


		}
	}

	//return sPropName;
	return strprop;
}

string CIoSimDOMBuilder::GetPropInfilename()
{
	string sPropInfilename;
	string strprop;
	CIoSimulant *pSimulant = (CIoSimulant *)m_SimulantStack.top();

	if(m_iArrayDepth>0)
	{
		//Using current array of array indices
		CreateArrayMap();
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			sPropInfilename = pSimulant->GetChildPropInfilename(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			sPropInfilename = m_pSimulation->GetChildPropInfilename(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			sPropInfilename = m_pCurrentEntitySet->GetChildPropInfilename(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			sPropInfilename = m_pCurrentEntitySet->GetEArrayInfilename(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			sPropInfilename = m_pCurrentEntityTypeSet->GetChildPropInfilename(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			sPropInfilename = m_pCurrentEntityType->GetChildPropInfilename(m_iCurrentIndex, m_sArrayMap);
			break;


		}
	}
	else
	{
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			strprop = pSimulant->GetPropInfilename(m_iCurrentIndex);
			//strcpy(spropname,(char *)strprop.c_str();
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			strprop = m_pSimulation->GetPropInfilename(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			strprop = m_pCurrentEntitySet->GetPropInfilename(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			strprop = m_pCurrentEntitySet->GetEPropertyName(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			strprop = m_pCurrentEntityTypeSet->GetPropInfilename(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			strprop = m_pCurrentEntityType->GetPropInfilename(m_iCurrentIndex);
			break;


		}
	}

	//return sPropInfilename;
	return strprop;
}

string CIoSimDOMBuilder::GetPropOutfilename()
{
	string sPropOutfilename;
	string strprop;
	CIoSimulant *pSimulant = (CIoSimulant *)m_SimulantStack.top();

	if(m_iArrayDepth>0)
	{
		//Using current array of array indices
		CreateArrayMap();
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			sPropOutfilename = pSimulant->GetChildPropOutfilename(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			sPropOutfilename = m_pSimulation->GetChildPropOutfilename(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			sPropOutfilename = m_pCurrentEntitySet->GetChildPropOutfilename(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			sPropOutfilename = m_pCurrentEntitySet->GetEArrayOutfilename(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			sPropOutfilename = m_pCurrentEntityTypeSet->GetChildPropOutfilename(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			sPropOutfilename = m_pCurrentEntityType->GetChildPropOutfilename(m_iCurrentIndex, m_sArrayMap);
			break;


		}
	}
	else
	{
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			strprop = pSimulant->GetPropOutfilename(m_iCurrentIndex);
			//strcpy(spropname,(char *)strprop.c_str();
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			strprop = m_pSimulation->GetPropOutfilename(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			strprop = m_pCurrentEntitySet->GetPropOutfilename(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			strprop = m_pCurrentEntitySet->GetEPropertyName(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			strprop = m_pCurrentEntityTypeSet->GetPropOutfilename(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			strprop = m_pCurrentEntityType->GetPropOutfilename(m_iCurrentIndex);
			break;


		}
	}

	//return sPropOutfilename;
	return strprop;
}



string CIoSimDOMBuilder::GetPropArrayName()
{
	string sPropArrayName;
	CIoSimulant *pSimulant = (CIoSimulant *)m_SimulantStack.top();

	if(m_iArrayDepth>0)
	{
		//Using current array of array indices
		CreateArrayMap();
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			sPropArrayName = pSimulant->GetChildArrayName(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			sPropArrayName = m_pSimulation->GetChildArrayName(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			sPropArrayName = m_pCurrentEntitySet->GetChildArrayName(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			//sPropArrayName = NULL;
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			sPropArrayName = m_pCurrentEntityTypeSet->GetChildArrayName(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			sPropArrayName = m_pCurrentEntityType->GetChildArrayName(m_iCurrentProp, m_sArrayMap);
			break;

		}
	}
	else
	{
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			sPropArrayName = pSimulant->GetArrayName(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			sPropArrayName = m_pSimulation->GetArrayName(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			sPropArrayName = m_pCurrentEntitySet->GetArrayName(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			sPropArrayName = m_pCurrentEntitySet->GetEArrayName(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			sPropArrayName = m_pCurrentEntityTypeSet->GetArrayName(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			sPropArrayName = m_pCurrentEntityType->GetArrayName(m_iCurrentProp);
			break;

		}
	}

	return sPropArrayName;
}

string CIoSimDOMBuilder::GetPropArrayInfilename()
{
	string sPropArrayInfilename;
	CIoSimulant *pSimulant = (CIoSimulant *)m_SimulantStack.top();

	if(m_iArrayDepth>0)
	{
		//Using current array of array indices
		CreateArrayMap();
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			sPropArrayInfilename = pSimulant->GetChildArrayInfilename(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			sPropArrayInfilename = m_pSimulation->GetChildArrayInfilename(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			sPropArrayInfilename = m_pCurrentEntitySet->GetChildArrayInfilename(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			//sPropArrayInfilename = NULL;
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			sPropArrayInfilename = m_pCurrentEntityTypeSet->GetChildArrayInfilename(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			sPropArrayInfilename = m_pCurrentEntityType->GetChildArrayInfilename(m_iCurrentProp, m_sArrayMap);
			break;

		}
	}
	else
	{
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			sPropArrayInfilename = pSimulant->GetArrayInfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			sPropArrayInfilename = m_pSimulation->GetArrayInfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			sPropArrayInfilename = m_pCurrentEntitySet->GetArrayInfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			sPropArrayInfilename = m_pCurrentEntitySet->GetEArrayInfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			sPropArrayInfilename = m_pCurrentEntityTypeSet->GetArrayInfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			sPropArrayInfilename = m_pCurrentEntityType->GetArrayInfilename(m_iCurrentProp);
			break;

		}
	}

	return sPropArrayInfilename;
}


string CIoSimDOMBuilder::GetPropArrayOutfilename()
{
	string sPropArrayOutfilename;
	CIoSimulant *pSimulant = (CIoSimulant *)m_SimulantStack.top();

	if(m_iArrayDepth>0)
	{
		//Using current array of array indices
		CreateArrayMap();
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			sPropArrayOutfilename = pSimulant->GetChildArrayOutfilename(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			sPropArrayOutfilename = m_pSimulation->GetChildArrayOutfilename(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			sPropArrayOutfilename = m_pCurrentEntitySet->GetChildArrayOutfilename(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			//sPropArrayOutfilename = NULL;
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			sPropArrayOutfilename = m_pCurrentEntityTypeSet->GetChildArrayOutfilename(m_iCurrentProp, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			sPropArrayOutfilename = m_pCurrentEntityType->GetChildArrayOutfilename(m_iCurrentProp, m_sArrayMap);
			break;

		}
	}
	else
	{
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			sPropArrayOutfilename = pSimulant->GetArrayOutfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			sPropArrayOutfilename = m_pSimulation->GetArrayOutfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			sPropArrayOutfilename = m_pCurrentEntitySet->GetArrayOutfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			sPropArrayOutfilename = m_pCurrentEntitySet->GetEArrayOutfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			sPropArrayOutfilename = m_pCurrentEntityTypeSet->GetArrayOutfilename(m_iCurrentProp);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			sPropArrayOutfilename = m_pCurrentEntityType->GetArrayOutfilename(m_iCurrentProp);
			break;

		}
	}

	return sPropArrayOutfilename;
}



int CIoSimDOMBuilder::GetPropFlag()
{

	int iPropFlag = 0;  //Default is write the property
 	CIoSimulant *pSimulant = (CIoSimulant *)m_SimulantStack.top();
    //Not implemennted by property manager yet
	if(m_iArrayDepth>0)
	{
		//Using current array of array indices
		CreateArrayMap();
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			iPropFlag = pSimulant->GetChildPropertyFlag(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			iPropFlag =m_pSimulation->GetChildPropertyFlag(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			iPropFlag =m_pCurrentEntitySet->GetChildPropertyFlag(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			iPropFlag =m_pCurrentEntitySet->GetEArrayFlag(m_iCurrentIndex);//?????
			break;


		}
	}
	else
	{
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			iPropFlag = pSimulant->GetPropertyFlag(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			iPropFlag =m_pSimulation->GetPropertyFlag(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			iPropFlag =m_pCurrentEntitySet->GetPropertyFlag(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			iPropFlag =m_pCurrentEntitySet->GetEPropertyFlag(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPESET :
			iPropFlag =m_pCurrentEntityTypeSet->GetPropertyFlag(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYTYPE :
			iPropFlag =m_pCurrentEntityType->GetPropertyFlag(m_iCurrentIndex);
			break;


		}
	}



	return iPropFlag;



}

int CIoSimDOMBuilder::TestPropFlag()
{

	int iPropFlag = GetPropFlag();  

	if(iPropFlag & m_iflagtype) 
			iPropFlag=1;
	else
		    iPropFlag=0;

	return iPropFlag;



}


int CIoSimDOMBuilder::TestPropsFlag()
{

	int iPropsFlag = GetPropsFlag();  

	if(iPropsFlag & m_iflagtype) 
			iPropsFlag=1;
	else
		    iPropsFlag=0;

	return iPropsFlag;



}

int CIoSimDOMBuilder::GetPropsFlag()
{

	int iPropsFlag = 0;  //Default is write the property
 	CIoSimulant *pSimulant = (CIoSimulant *)m_SimulantStack.top();
    //Not implemennted by property manager yet
	if(m_iArrayDepth>0)
	{
		//Using current array of array indices
		CreateArrayMap();
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			iPropsFlag = pSimulant->GetChildArrayFlag(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			iPropsFlag =m_pSimulation->GetChildArrayFlag(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			iPropsFlag =m_pCurrentEntitySet->GetChildArrayFlag(m_iCurrentIndex, m_sArrayMap);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			iPropsFlag =7;
			break;
		}
	}
	else
	{
		switch((int)m_SimElementStack.top())
		{
		case IO_XMLP_STACK_ELEMENT_SIMULATOR :
		case IO_XMLP_STACK_ELEMENT_MODEL :
			iPropsFlag = pSimulant->GetArrayFlag(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_SIMULATION :
			iPropsFlag =m_pSimulation->GetArrayFlag(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYSET :
			iPropsFlag =m_pCurrentEntitySet->GetArrayFlag(m_iCurrentIndex);
			break;
		case IO_XMLP_STACK_ELEMENT_ENTITYPROPSTYPE :
			iPropsFlag =m_pCurrentEntitySet->GetEArrayFlag(m_iCurrentIndex);
			break;
		}
	}



	return iPropsFlag;



}

void CIoSimDOMBuilder::CreateArrayMap()
{
	m_sArrayMap = new char [50];

	char sIndex [10];
	sprintf(sIndex, "%d", m_iArrayDepth);
	strcpy(m_sArrayMap, sIndex);

	for(int i=0; i<m_iArrayDepth, i<IO_MAXDEPTH; i++)
	{
		sprintf(sIndex, " %d", m_iMapArray [i]);			
		strcat(m_sArrayMap, sIndex);
	}
}

int CIoSimDOMBuilder::WriteSimDOM(char *docname)
{
	// ---------------------------------------------------------------------------
	//  Local data
	//
	//  gXmlFile
	//      The path to the file to parser. Set via command line.
	//
	//  gDoNamespaces
	//      Indicates whether namespace processing should be done.
	//
	//  gDoSchema
	//      Indicates whether schema processing should be done.
	//
	//  gSchemaFullChecking
	//      Indicates whether full schema constraint checking should be done.
	//
	//  gDoCreate
	//      Indicates whether entity reference nodes needs to be created or not
	//      Defaults to false
	//
	//  gOutputEncoding
	//      The encoding we are to output in. If not set on the command line,
	//      then it is defaults to the encoding of the input XML file.
	//
	//  gMyEOLSequence
	//      The end of line sequence we are to output.
	//
	//  gSplitCdataSections
	//      Indicates whether split-cdata-sections is to be enabled or not.
	//
	//  gDiscardDefaultContent
	//      Indicates whether default content is discarded or not.
	//
	//  gUseFilter
	//      Indicates if user wants to plug in the DOMPrintFilter.
	//
	//  gValScheme
	//      Indicates what validation scheme to use. It defaults to 'auto', but
	//      can be set via the -v= command.
	//
	// ---------------------------------------------------------------------------

	static bool                     gDoNamespaces          = false;
	static bool                     gDoSchema              = false;
	static bool                     gSchemaFullChecking    = false;
	static bool                     gDoCreate              = true;

	// options for DOMWriter's features
	static const XMLCh*             gOutputEncoding        = 0;
	static const XMLCh*             gMyEOLSequence         = 0;

	static bool                     gSplitCdataSections    = true;
	static bool                     gDiscardDefaultContent = true;
	static bool                     gUseFilter             = false;
	static bool                     gFormatPrettyPrint     = false;

	static XercesDOMParser::ValSchemes    gValScheme       = XercesDOMParser::Val_Auto;


	int status = 1;
	CIoSimDOMPrintFilter *myFilter;

        
			// get a serializer, an instance of DOMWriter
			XMLCh tempStr[100];
			XMLString::transcode("LS", tempStr, 99);
			DOMImplementation *impl          = DOMImplementationRegistry::getDOMImplementation(tempStr);
			DOMWriter         *theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

			// set user specified end of line sequence and output encoding
			theSerializer->setNewLine(gMyEOLSequence);
			theSerializer->setEncoding(gOutputEncoding);

			// plug in user's own filter
			if (gUseFilter)
			{
				// even we say to show attribute, but the DOMWriter
				// will not show attribute nodes to the filter as
				// the specs explicitly says that DOMWriter shall
				// NOT show attributes to DOMWriterFilter.
				//
				// so DOMNodeFilter::SHOW_ATTRIBUTE has no effect.
				// same DOMNodeFilter::SHOW_DOCUMENT_TYPE, no effect.
				//
				myFilter = new CIoSimDOMPrintFilter(DOMNodeFilter::SHOW_ELEMENT   |
                                              DOMNodeFilter::SHOW_ATTRIBUTE |
                                              DOMNodeFilter::SHOW_DOCUMENT_TYPE
											  );
				theSerializer->setFilter(myFilter);
			}

			// plug in user's own error handler
			//DOMErrorHandler *myErrorHandler = new DOMPrintErrorHandler();
			//theSerializer->setErrorHandler(myErrorHandler);

			// set feature if the serializer supports the feature/mode
			if (theSerializer->canSetFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections))
				theSerializer->setFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections);
			
			if (theSerializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent))
				theSerializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent);

			if (theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint))
				theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint);

            //
			// Plug in a format target to receive the resultant
			// XML stream from the serializer.
            //
			// StdOutFormatTarget prints the resultant XML stream
			// to stdout once it receives any thing from the serializer.
			//
			XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(X(docname));

			// get the DOM representation
			DOMNode *doc = m_pDOMDoc;
			
			//
			// do the serialization through DOMWriter::writeNode();
			//
			theSerializer->writeNode(myFormTarget, *doc);

			delete theSerializer;
			delete myFormTarget;
			if (gUseFilter) delete myFilter;




	return status;
}

char *CIoSimDOMBuilder::WriteMemSimDOM()
{
	// ---------------------------------------------------------------------------
	//  Local data
	//
	//  gXmlFile
	//      The path to the file to parser. Set via command line.
	//
	//  gDoNamespaces
	//      Indicates whether namespace processing should be done.
	//
	//  gDoSchema
	//      Indicates whether schema processing should be done.
	//
	//  gSchemaFullChecking
	//      Indicates whether full schema constraint checking should be done.
	//
	//  gDoCreate
	//      Indicates whether entity reference nodes needs to be created or not
	//      Defaults to false
	//
	//  gOutputEncoding
	//      The encoding we are to output in. If not set on the command line,
	//      then it is defaults to the encoding of the input XML file.
	//
	//  gMyEOLSequence
	//      The end of line sequence we are to output.
	//
	//  gSplitCdataSections
	//      Indicates whether split-cdata-sections is to be enabled or not.
	//
	//  gDiscardDefaultContent
	//      Indicates whether default content is discarded or not.
	//
	//  gUseFilter
	//      Indicates if user wants to plug in the DOMPrintFilter.
	//
	//  gValScheme
	//      Indicates what validation scheme to use. It defaults to 'auto', but
	//      can be set via the -v= command.
	//
	// ---------------------------------------------------------------------------

	static bool                     gDoNamespaces          = false;
	static bool                     gDoSchema              = false;
	static bool                     gSchemaFullChecking    = false;
	static bool                     gDoCreate              = true;

	// options for DOMWriter's features
	static const XMLCh*             gOutputEncoding        = 0;
	static const XMLCh*             gMyEOLSequence         = 0;

	static bool                     gSplitCdataSections    = true;
	static bool                     gDiscardDefaultContent = true;
	static bool                     gUseFilter             = false;
	static bool                     gFormatPrettyPrint     = false;

	static XercesDOMParser::ValSchemes    gValScheme       = XercesDOMParser::Val_Auto;


	int status = 1;
	CIoSimDOMPrintFilter *myFilter;

        
			// get a serializer, an instance of DOMWriter
			XMLCh tempStr[100];
			XMLString::transcode("LS", tempStr, 99);
			DOMImplementation *impl          = DOMImplementationRegistry::getDOMImplementation(tempStr);
			DOMWriter         *theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

			// set user specified end of line sequence and output encoding
			theSerializer->setNewLine(gMyEOLSequence);
			theSerializer->setEncoding(gOutputEncoding);

			// plug in user's own filter
			if (gUseFilter)
			{
				// even we say to show attribute, but the DOMWriter
				// will not show attribute nodes to the filter as
				// the specs explicitly says that DOMWriter shall
				// NOT show attributes to DOMWriterFilter.
				//
				// so DOMNodeFilter::SHOW_ATTRIBUTE has no effect.
				// same DOMNodeFilter::SHOW_DOCUMENT_TYPE, no effect.
				//
				myFilter = new CIoSimDOMPrintFilter(DOMNodeFilter::SHOW_ELEMENT   |
                                              DOMNodeFilter::SHOW_ATTRIBUTE |
                                              DOMNodeFilter::SHOW_DOCUMENT_TYPE
											  );
				theSerializer->setFilter(myFilter);
			}

			// plug in user's own error handler
			//DOMErrorHandler *myErrorHandler = new DOMPrintErrorHandler();
			//theSerializer->setErrorHandler(myErrorHandler);

			// set feature if the serializer supports the feature/mode
			if (theSerializer->canSetFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections))
				theSerializer->setFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections);
			
			if (theSerializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent))
				theSerializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent);

			if (theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint))
				theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint);

            //
			// Plug in a format target to receive the resultant
			// XML stream from the serializer.
            //
			// StdOutFormatTarget prints the resultant XML stream
			// to stdout once it receives any thing from the serializer.
			//
			//XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(X(docname));
			//XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(X(docname));
			// get the DOM representation
			DOMNode *doc = m_pDOMDoc;
			
			//
			// do the serialization through DOMWriter::writeNode();
			//
			//theSerializer->writeNode(myFormTarget, *doc);
			XMLCh *sOut=theSerializer->writeToString(*doc);
			delete theSerializer;
			//delete myFormTarget;
			if (gUseFilter) delete myFilter;




			return StrX(sOut).localForm();
}


