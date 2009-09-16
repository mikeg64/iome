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
	m_pDOMState=NULL;

	

}

CIoXMLSimulation::~CIoXMLSimulation()
{
	delete [] m_sConfigXSLFileName;
	delete [] m_sStateXSLFileName;
	delete [] m_sConfigXSLFilePrefix;
	delete [] m_sStateXSLFilePrefix;
	if(m_pDOMState)
	{
				//delete m_pDOMState;
				m_pDOMState=NULL;
	}

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
			if(m_pSimulant)
			{
		 		//m_pSimulant->CreateConfig();
		 		m_pSimulant->SetCreateMethod(m_iCreateMethod);
			}		
		}
		else
		{
			CIoSimulation::ReadSimulation(sSimFilename);
		}
		

	if(m_pSimulant)
	{
		 m_pSimulant->SetCreateMethod(m_iCreateMethod);
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

int CIoXMLSimulation::ReadConfig(char *sConfigFilename, int format)
{
	char sconfigname [100];
	int i;
	int status = 1;

try
{
	if(m_iconfigreadmethod==1)
	{
		i=0;
		while((i <99) && (m_sConfigFileName[i] !='.') && (m_sConfigFileName[i]!='\0'))
				sconfigname[i++]=m_sConfigFileName[i];
		sconfigname[i]='\0';

		#ifdef USEMPI
			sprintf(sconfigname, "%s_p%d.xml",sconfigname,m_irank);
		#else

			sprintf(sconfigname, "%s.xml",sconfigname);
		#endif

		CIoConfigReader ConfigReader;
		status = ConfigReader.ParseConfigFile(sConfigFilename, this);
	}
	else
		CIoSimulation::ReadConfig(sConfigFilename, format);
}
catch(int j)
{
	printf("IoXMLSimulation failed to read config\n");
	
}

	return status;
}

int CIoXMLSimulation::ReadState(char *sStateFilename, int format)
{
	int status=0;
	int i=0;
	int iNoEntities=1; //Tell config DOM writer 
	                   //not to output any entities to
	                   //the state file
	                   
	try
	{
	#ifdef USEMPI
		if(m_irank !=0)
		{
	#endif
	if(m_istatereadmethod==1)
	{
		CIoConfigReader ConfigReader;
		status = ConfigReader.ParseConfigFile(sStateFilename, this, iNoEntities);
	}
	else
		CIoSimulation::ReadState(sStateFilename, format);
	
	#ifdef USEMPI
		}//end read only if m_irank=0
	#endif
	}
	catch(int j)
	{
		printf("IoXMLSimulation failed to read state\n");
		
	}
	return status;
}

int CIoXMLSimulation::ReadStateInfo(char *sStateFilename, int format)
{
	int status=0;
	int i=0;
	int iNoEntities=1; //Tell config DOM writer 
	                   //not to output any entities to
	                   //the state file
    try
    {
	#ifdef USEMPI
		if(m_irank !=0)
		{
	#endif

	if(m_istatereadmethod==1)
	{
		CIoConfigReader ConfigReader;
		status = ConfigReader.ParseConfigFile(sStateFilename, this, iNoEntities);
	}
	else
		CIoSimulation::ReadStateInfo(sStateFilename, format);
	
	#ifdef USEMPI
		}
	#endif
    }
    catch(int j)
	{
		printf("XMLSimulation  failed to read state info.\n");
		
	}
	return status;
}


int CIoXMLSimulation::WriteConfig(char *sConfigFilename, int format, char *sXSLFilename, int iStepNum)
{
	int status=1;
	int i=0;
	char soutname [100];
	char slisname [100];

	char stxtoutname [100];
	char c;

	CIoConfigDOMBuilder DOMConfig;
	if(m_iconfigwritemethod==1)
	{


		DOMConfig.CreateConfigDOM(sConfigFilename, this, iStepNum);
		DOMConfig.WriteConfigDOM(sConfigFilename);

		//If the file was written OK then append its
		//name to the list of config files
		//i.e. the .lis file for this simulation
		strcpy(slisname, m_sSimName);
		strcat(slisname, "_cfg.lis");

		CIoFileUtils cCfgFileList(slisname, 'a');
		cCfgFileList.WriteLine(sConfigFilename);
		//CIoFileUtils cOutFileList(GetOutputFiles(), 'a');
		//cOutFileList.WriteLine(sConfigFilename);

		if(sXSLFilename)
		{
					while(((c=sConfigFilename[i])!='.') && (i < strlen(sConfigFilename)))
						soutname[i++]=c;

					if(i<100)
						soutname [i] = '\0';

						strcpy(stxtoutname, soutname);

					if(m_sConfigXSLFilePrefix)
					{
						strcat(soutname, ".");
						strcat( soutname,m_sConfigXSLFilePrefix);
					}
					else
						strcat( soutname,"_xslt.iotr");
					strcat(stxtoutname, "_xslt.dat");

					XSLTransform(sConfigFilename, sXSLFilename, soutname);
					CIoFileUtils fCfgUtil(soutname, 'r');
					fCfgUtil.SetFileName(soutname);
					fCfgUtil.ReplaceXMLBreakString(stxtoutname);

		
					//cOutFileList.WriteLine(soutname);
					//cOutFileList.WriteLine(stxtoutname);
		}
		//cOutFileList.CloseFile();
		//cCfgFileList.CloseFile();
	}
	else
		CIoSimulation::WriteConfig(sConfigFilename, format);




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

int CIoXMLSimulation::WriteState(char *sStateFilename, int format, char *sXSLFilename, int iStepNum)
{
	int status=1;
	int i=0;
	int iNoEntities=1; //Tell config DOM writer 
	                   //not to output any entities to
	                   //the state file
	int isteptest, icycletest;

	char soutname [100];
	char c;
	char stxtoutname [100];
	#ifdef USEMPI
				if(m_irank==0)//only the root processor writes the simulation
				{
	#endif

	CIoConfigDOMBuilder *DOMConfig;
	DOMConfig = m_pDOMState;


	if(m_istatewritemethod==1)
	{
	CIoFileUtils cOutFileList(GetOutputFiles(), 'a');
	cOutFileList.WriteLine(sStateFilename);
	if(DOMConfig)
	{
		
		DOMConfig->m_pRootElem->appendChild(DOMConfig->CreateSimulationElement(this, iStepNum, iNoEntities));
	}
	else
	{
		m_pDOMState=(CIoConfigDOMBuilder *)new CIoConfigDOMBuilder;
		DOMConfig = m_pDOMState;
		DOMConfig->CreateConfigDOM(sStateFilename, this, iStepNum, iNoEntities );
	}

	isteptest=(GetNumSteps()-iStepNum-1)/m_iStateStepFreq;
	

	if(isteptest==0 )
		DOMConfig->WriteConfigDOM(sStateFilename, iNoEntities);

	if((iStepNum>=(GetNumSteps()-1)))
		if(m_pDOMState)
		{


				while(((c=sStateFilename[i])!='.') && (i < strlen(sStateFilename)))
					soutname[i++]=c;

				if(i<100)
					soutname [i] = '\0';

				//strcpy(stxtoutname, soutname);
				/*if(m_sStateXSLFilePrefix)
					strcat( soutname,m_sStateXSLFilePrefix);
				else
					strcat( soutname,"_xslt.iotr");
				strcat(stxtoutname, "_xslt.dat");*/

				delete m_pDOMState;
				m_pDOMState=NULL;
				/*if(m_sStateXSLFileName)
				{
					XSLTransform(sStateFilename, m_sStateXSLFileName, soutname);
					CIoFileUtils fStateUtil(soutname);
					fStateUtil.ReplaceXMLBreakString(stxtoutname);
					cOutFileList.WriteLine(soutname);
					cOutFileList.WriteLine(stxtoutname);
				}*/


	
		}
		//cOutFileList.CloseFile();
	}
	else
		CIoSimulation::WriteState(sStateFilename,format,NULL);

	#ifdef USEMPI
				}//end only proc 0 writes state
	#endif
	return status;
}

int CIoXMLSimulation::WriteStateInfo(char *sStateFilename, int format, char *sXSLFilename, int iStepNum)
{
	int status=1;
	int i=0;
	int iNoEntities=1; //Tell config DOM writer 
	                   //not to output any entities to
	                   //the state file
	int isteptest, icycletest;

	char soutname [100];
	char c;
	char stxtoutname [100];

	#ifdef USEMPI
				if(m_irank==0)//only the root processor writes the simulation
				{
	#endif

	CIoSimulant *pSim, *pOldSim=GetSimulant();

	CIoConfigDOMBuilder *DOMConfig;
	DOMConfig = m_pDOMState;
	//int ioldcycle=GetCurrentCycle();
	int ioldstep=GetCurrentStep();


	if(m_istatewritemethod==1)
	{

		for(m_lSimStateIterator=m_lSimStateList.begin(); m_lSimStateIterator != m_lSimStateList.end();m_lSimStateIterator++)
		{
			if(pSim=(CIoSimulant *)(*m_lSimStateIterator))
			{
				SetSimulant(pSim);
				//SetCurrentCycle(pSim->GetCurrentCycle());
				SetCurrentStep(pSim->GetCurrentStep());
				if(DOMConfig)
				{
					
					DOMConfig->m_pRootElem->appendChild(DOMConfig->CreateSimulationElement(this, iStepNum, iNoEntities));
				}
				else
				{
					m_pDOMState=(CIoConfigDOMBuilder *)new CIoConfigDOMBuilder;
					DOMConfig = m_pDOMState;
					DOMConfig->CreateConfigDOM(sStateFilename, this, iStepNum, iNoEntities );
				}

				//if last simulant in list
				if(m_lSimStateIterator == m_lSimStateList.end())
					DOMConfig->WriteConfigDOM(sStateFilename, iNoEntities);
			}
		}
		SetSimulant(pOldSim);
		SetCurrentStep(ioldstep);
		//SetCurrentCycle(ioldcycle);
	}
	else
		CIoSimulation::WriteStateInfo(sStateFilename,format,NULL);

	#ifdef USEMPI
				}//end writing state info
	#endif

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

int CIoXMLSimulation::StateTrans2AscFormat(char *sstatefile, char *sstateoutfile, int method)
{
	int status=0;
	ReadStateInfo(sstatefile);
	int iOldWriteMethod=GetStateWriteMethod();
	SetStateWriteMethod(method);
	CIoSimulation::WriteStateInfo(sstateoutfile);
	SetStateWriteMethod(iOldWriteMethod);

	return status;
}

int CIoXMLSimulation::StateTransAscFormat2XML(char *sstatefile, char *sstateoutfile, int method)
{
	int status=0;
	int iOldReadMethod=GetStateReadMethod();
	int iOldWriteMethod=GetStateWriteMethod();
	SetStateReadMethod(0);

	CIoSimulation::ReadStateInfo(sstatefile);
	SetStateWriteMethod(1);
	WriteStateInfo(sstateoutfile);
	SetStateWriteMethod(iOldWriteMethod);
	return status;
}



int CIoXMLSimulation::CfgTrans2AscFormat(char *scfgfile, char *scfgoutfile, int method)
{
	int status=0;
	ReadConfig(scfgfile);
	int iOldWriteMethod=GetConfigWriteMethod();
	SetConfigWriteMethod(method);
	CIoSimulation::WriteConfig(scfgoutfile, method);
	SetConfigWriteMethod(iOldWriteMethod);
	return status;
}

int CIoXMLSimulation::CfgTransAscFormat2XML(char *scfgfile, char *scfgoutfile, int method)
{
	int status=0;
	int iOldReadMethod=GetConfigReadMethod();
	int iOldWriteMethod=GetConfigWriteMethod();
	
	if(GetConfigReadMethod()==1)
			SetConfigReadMethod(0);

	this->ReadConfig(scfgfile,method);
	SetConfigWriteMethod(1);
	this->WriteConfig(scfgoutfile);
	SetConfigWriteMethod(iOldWriteMethod);
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


int CIoXMLSimulation::CreateTransformedConfigDOM()
{
	int status=0;

	return status;

}


void CIoXMLSimulation::DeleteTransformedConfigDOM()
{


}

int CIoXMLSimulation::CreateConfig()
{
	int status=0;
	if(GetCreateMethod()>0)
		status=m_pSimulant->CreateConfig();
	else
		status=ReadConfig(GetConfigFileName(), GetConfigReadMethod());

	return status;
}

int CIoXMLSimulation::CreateConfigDOM()
{
	int status=0;

	return status;

}

void CIoXMLSimulation::DeleteConfigDOM()
{


}

















