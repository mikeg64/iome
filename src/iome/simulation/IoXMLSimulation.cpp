/*
IOME LICENSE
IOME Version 2.2.1

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

// IoSimulation.cpp: implementation of the CIoXMLSimulation class.
//
//////////////////////////////////////////////////////////////////////


#include <iome/simulation/IoXMLSimulation.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoXMLSimulation::CIoXMLSimulation()
{

	m_sConfigXSLFileName = new char [100];
	m_sSimXSLFileName = new char [100];
	m_sStateXSLFileName = new char [100];
	m_sConfigXSLFilePrefix = new char [100];
	m_sStateXSLFilePrefix = new char [100];

	m_sSimXSLFileName [0] = '\0';
	m_sConfigXSLFileName [0] = '\0';
	m_sStateXSLFileName [0] = '\0';
	m_sConfigXSLFilePrefix [0]= '\0';
	m_sStateXSLFilePrefix[0] = '\0';
	m_isimwritemethod=1;
	m_isimreadmethod=1;
	m_istatewritemethod=1;
	m_istatereadmethod=1;
	m_iconfigwritemethod=1;
	m_iconfigreadmethod=1;
//	m_pDOMState=NULL;

	

}

CIoXMLSimulation::~CIoXMLSimulation()
{
	delete [] m_sSimXSLFileName;
	delete [] m_sConfigXSLFileName;
	delete [] m_sStateXSLFileName;
	delete [] m_sConfigXSLFilePrefix;
	delete [] m_sStateXSLFilePrefix;


	//XalanTransformer::terminate();
	//XMLPlatformUtils::Terminate();
	//XalanTransformer::ICUCleanUp();
}





void CIoXMLSimulation::CreatePropNames()
{
	AddPropName("TestInt1");
}

void CIoXMLSimulation::CreatePropArrayNames()
{
	AddArrayName("XMLSimtestProps");

}



void CIoXMLSimulation::SetStateXSLFileName(const char *name)
{
	if(m_sStateXSLFileName) 
		strcpy(m_sStateXSLFileName, name);

}

void CIoXMLSimulation::SetConfigXSLFileName(const char *name)
{
	if(m_sConfigXSLFileName) 
		strcpy(m_sConfigXSLFileName, name);
	
}/*{for(int i=0; i<strlen(name), i<100; i++)m_sConfigFileName [i]=name [i];}*/

void CIoXMLSimulation::SetSimXSLFileName(const char *name)
{
	if(m_sSimXSLFileName) 
		strcpy(m_sSimXSLFileName, name);
	
}/*{for(int i=0; i<strlen(name), i<100; i++)m_sConfigFileName [i]=name [i];}*/


void CIoXMLSimulation::SetStateXSLFilePrefix(const char *name)
{
	if(m_sStateXSLFilePrefix) 
		strcpy(m_sStateXSLFilePrefix, name );

}

void CIoXMLSimulation::SetConfigXSLFilePrefix(const char *name)
{
	if(m_sConfigXSLFilePrefix) 
		strcpy(m_sConfigXSLFilePrefix, name);
	
}/*{for(int i=0; i<strlen(name), i<100; i++)m_sConfigFileName [i]=name [i];}*/





int CIoXMLSimulation::ReadSimulation(char *sSimFilename)
{
	int status = 1;
				try
			{
		if(m_isimreadmethod==1)
		{
			CIoSimulationReader SimReader;
			status = SimReader.ParseSimulationFile(sSimFilename, this);
		
		}
		else
		{
			CIoSimulation::ReadSimulation(sSimFilename);
		}
		


			}
			catch(int j)
			{
				status=1;
				printf("XMLSimulation Reading %s failed\n",sSimFilename);
				
				
			}

	//This will uually be called by a CreateSimulation Command
	//call create CIoXMLSimulation::CreateSimulation
    //if(status && (m_iCreateMethod == 0) )
	//	status=this->ReadConfig(m_sConfigFileName, m_ireadmethod);  //Has virtual override pickup the correct method
	
	//if simulant is model if creator type is !=0 then create model


	//if simulant is simulator then check each model of the simulator
	//in turn for its creation method

	return status;
}


int CIoXMLSimulation::WriteSimulation(char *sSimFilename, char *sXSLFilename)
{
	int status=1;
	char sxml[] = ".xml";
	char sTempFilename[]="simulationfile.xml";
	#ifdef USEMPI
				if(m_irank==0)//only the root processor writes the simulation
				{
	#endif

	if(sSimFilename == NULL)
	{
		//sTempFilename = (char *)new char [4+strlen(m_sSimName)];
		sprintf(sTempFilename, "%s%s",m_sSimName,sxml); 
		//sSimFilename = strcat(m_sSimName,sxml);
		sSimFilename = sTempFilename;
	}
	CIoSimDOMBuilder DOMSimulation;

	DOMSimulation.CreateSimDOM(sSimFilename, this);
	DOMSimulation.WriteSimDOM(sSimFilename);
	
	#ifdef USEMPI
				}//end of testing irank
	#endif


	//if(sTempFilename) delete [] sTempFilename;
	return status;

}


int CIoXMLSimulation::XSLTransform(char *sxmlin, char *sxslin, char *sxmlout)
{
	int status=0;


	XalanTransformer theXalanTransformer;
	status =
				theXalanTransformer.transform(sxmlin,sxslin,sxmlout);
	


	return status;
}

int CIoXMLSimulation::SimTrans2AscFormat(char *ssimfile, char *ssimoutfile, int method)
{
	int status=0;
	ReadSimulation(ssimfile);
	int iOldWriteMethod=GetSimWriteMethod();
	SetSimWriteMethod(method);
	CIoSimulation::WriteSimulation(ssimoutfile);
	SetSimWriteMethod(iOldWriteMethod);

	return status;
}

int CIoXMLSimulation::SimTransAscFormat2XML(char *ssimfile, char *ssimoutfile)
{
	int status=0;
	
	int iOldReadMethod=GetSimReadMethod();
	int iOldWriteMethod=GetSimWriteMethod();
	SetSimReadMethod(0);

	CIoSimulation::ReadSimulation(ssimfile);
	SetSimWriteMethod(1);
	WriteSimulation(ssimoutfile);
	SetSimWriteMethod(iOldWriteMethod);

	return status;
}


XalanCompiledStylesheet *CIoXMLSimulation::CreateCompiledStyleSheet()
{
	XalanCompiledStylesheet *pcstylsheet=NULL;

	return pcstylsheet;
}

void CIoXMLSimulation::DeleteCompiledStyleSheet()
{


}














