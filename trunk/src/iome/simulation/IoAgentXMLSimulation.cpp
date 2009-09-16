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


#include <iome/simulation/IoAgentXMLSimulation.h>

CIoAgentXMLSimulation::CIoAgentXMLSimulation(void)
{
	SetSimName("AgentSim");
	SetSimClass("AgentXMLSimulation");
	SetSimulantClass("AgentModel");
	//strcpy(m_sSimName, "AgentSim");
	//strcpy(m_sSimClass, "AgentXMLSimulation");
	m_iNumSteps  = 2;
}

CIoAgentXMLSimulation::~CIoAgentXMLSimulation(void)
{
}

void CIoAgentXMLSimulation::CreatePropNames()
{
	AddPropName("defaultint");
}

void CIoAgentXMLSimulation::CreatePropArrayNames()
{
	AddArrayName("AgentSimProps");


}

void CIoAgentXMLSimulation::CreatePropFlags()
{
	int iflag = 1;//sim only


	AddPropFlag(iflag);

}

void CIoAgentXMLSimulation::CreatePropArrayFlags()
{
	int iflag = 5; //State, sim
	AddArrayFlag(iflag);

}

void CIoAgentXMLSimulation::CreateDefaultParams()
{
int i1;
i1 = 10;

	if(m_pProperties)
		delete m_pProperties;

    m_pProperties  = new CIoParam;

	AddInt(i1);
 
}

int CIoAgentXMLSimulation::CheckParamFormat(CIoParam *pSimData)
{
	int status=0;
	CIoParam *pParam=NULL;

	if((pSimData && (pSimData->GetType()==IO_PARAM_ARRAY)))
		if((pParam=pSimData->GetParam(0)) && (pParam->GetType()==IO_PARAM_INTEGER))status=1;

	return status;
}

CIoModel *CIoAgentXMLSimulation::newModel(char *sModelClass)
{
	CIoAgentModel *pAgentModel= new CIoAgentModel(this,NULL,NULL);

	/*! Unnecsssary the create method does this*/
	//pAgentModel->CreateDefaultParams();

	return pAgentModel;
}

CIoSimulator *CIoAgentXMLSimulation::newSimulator(char *sSimulatorClass)
{
	CIoAgentSimulator *pAgentSimulator= new CIoAgentSimulator;
	pAgentSimulator->CreateDefaultParams();

	return pAgentSimulator;
}


int CIoAgentXMLSimulation::ReadConfig(char *sConfigFilename, int format)
{
	int status=0;

   //CIoSimulator *pSimulator=NULL;
	CIoModel *pModel=NULL;
	//CIoAgentSimulator *pAgentSimulator;
	CIoAgentModel *pAgentModel;
	CIoSimulant *pSimulant = m_pSimulant;

std::cout << sConfigFilename << std::endl;
		status = CIoXMLSimulation::ReadConfig(sConfigFilename, format);
		
		//status = CIoXMLSimulation::ReadConfig("startestcfg1.xml", format);
        if((status==0) && (pAgentModel=(CIoAgentModel *)pSimulant))
        	pAgentModel->setglobal();
	//For reading a configuration
	//first read all of the config data in XML
	//we then convert it into the life model configuration format
	//Check any of the models in the simulators
	//if they are life models make sure that 
	//configuration matrices are set correctly
	//ReadConfigSimulatorIterator(pSimulant, sConfigFilename, format);
	return status;


} 

int  CIoAgentXMLSimulation::WriteConfig(char *sConfigFilename, int format, char *sXSLFilename, int iStepNum)
{
	int status=0;
	int i=0;
	
	int nx,ny,nz;
	int i1,i2,i3;
	int ir,ic;
	mmat3d *mm3d=NULL;
	mmat3d *mm3dv=NULL;
   // CIoSimulator *pSimulator=NULL;
	CIoModel *pModel=NULL;
	//CIoAgentSimulator *pAgentSimulator;
	CIoAgentModel *pAgentModel;
	CIoSimulant *pSimulant = m_pSimulant;

	//Check any of the models in the simulators
	//if they are life models make sure that 
	//configuration matrices are set correctly
	//WriteConfigSimulatorIterator(pSimulant, sConfigFilename, format);

	printf("here 1  format 2 %s \n",sConfigFilename);
 
    if(pSimulant && (format==2 || format==3 ))
    {
		 
		char sconfigname [100];
		std::ofstream ocfg;
		pAgentModel=(CIoAgentModel *)(m_pSimulant);
		if(m_sConfigFileName && (strlen(m_sConfigFileName)>0))
		{
			//printf("here 2  format 2 %s\n",sconfigname);
			//remeber to check print flags for each field (i.e. determine which properties
			//and entity properties to write
			
			i=0;
			
			if(format==2 )
			{
				while((i <99) && (m_sConfigFileName[i] !='.') && (m_sConfigFileName[i]!='\0'))
					sconfigname[i++]=m_sConfigFileName[i];
				sconfigname[i]='\0';
				sprintf(sconfigname, "%s.out",sconfigname);
			}
			else if(format==3 )
			{
				while((i <99) && (m_sConfigFileName[i] !='.') && (m_sConfigFileName[i]!='\0'))
					sconfigname[i++]=m_sConfigFileName[i];
				sconfigname[i]='\0';
				sprintf(sconfigname, "%s_%d.out",sconfigname,GetCurrentStep());
			}

			
			printf("writing config for dx %s",sconfigname);
			if(format==2 )
				ocfg.open(sconfigname, std::ofstream::out | std::ofstream::app);
			else if(format==3 )
				ocfg.open(sconfigname, std::ofstream::out | std::ofstream::trunc);
			//Each time series separated by a list of global scalar and global vector properties
			ocfg << iStepNum << std::endl;
			ocfg << pAgentModel->GetNumScaProps()<< " "<< pAgentModel->GetNumVecProps()<<" " << pAgentModel->GetNumScaFieldProps()<< " "<< pAgentModel->GetNumVecFieldProps()<< std::endl;
			ocfg << *(pAgentModel->GetVec(IO_AGENTMODEL_FLOATPROPS_VEC)) << " " <<*(pAgentModel->GetMat(IO_AGENTMODEL_VECPROPS_MAT))<< std::endl;
            //write some config info here
		     vec *vbox=pAgentModel->GetVec(IO_AGENTMODEL_MODELSIZE_VEC);
		     
		     if(vbox)
		     {
		     	nx=vbox->get(0);
		     	ny=vbox->get(1);	
		     	nz=vbox->get(2);	     		
		     }
		     mm3d=pAgentModel->Getmmat3d(IO_AGENTMODEL_SCALARFIELDS_MMAT3D); 
		     mm3dv = pAgentModel->Getmmat3d(IO_AGENTMODEL_VECFIELDS_MMAT3D);
			 if((mm3d != NULL) || (mm3dv != NULL))	
			 {
			     for(i1=0;i1<nx;i1++)
			    	 for(i2=0;i2<ny;i2++)
			    		 for(i3=0;i3<nz;i3++)
			    		 {
			    			 ocfg << i1 << " " << i2 << " " << i3;
			    			 
			    			 if(mm3d != NULL)
			    			 for(ir=0; ir<mm3d->mrows() ; ir++)
			    				 for(ic=0; ic<mm3d->mcols() ; ic++)
			    				 {
			    					 ocfg << " " << mm3d->getval(i1,i2,i3,ir,ic);
			    					 std::cout << mm3d->getval(i1,i2,i3,ir,ic) << " ";
			    				 }
			    			 if(mm3dv != NULL)
			    			 for(ir=0; ir<mm3dv->mrows() ; ir++)
			    				 for(ic=0; ic<mm3dv->mcols() ; ic++)
			    					 ocfg << " " << mm3dv->getval(i1,i2,i3,ir,ic);			    			 
			    			 
			    			 ocfg << std::endl;
			    			 
			    		 }
			     		std::cout << std::endl;
			 }

			ocfg.close();
			
			//separate file containing agent information
			
			
			
		}
		


    	
    }
    else
		status = CIoXMLSimulation::WriteConfig(sConfigFilename, format);
    
    

	//We have stored all cell positions and energies
	//not always necessary so delete them again????
	return status;
}

/*CIoSimulant *CIoAgentXMLSimulation::WriteConfigSimulatorIterator(CIoSimulant *pSimulant, char *sConfigFilename, char *format, char *sXSLFilename)
{
  CIoSimulant *ptSimulant=pSimulant;
  CIoAgentModel *pAgentModel=NULL;
  CIoModel *pModel = NULL;
   // pSimulant = pSimulant->GetNextSimulant();
	while(pSimulant)
	{
		if(pSimulant && pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR)
			WriteConfigSimulatorIterator(pSimulant, sConfigFilename, format, sXSLFilename);
		else
		{
			pModel = (CIoModel *)pSimulant;
			if(!strcmp(pModel->GetModelClass(), "AgentModel"))
			{
				pAgentModel = (CIoAgentModel *)pModel;
                pAgentModel->WriteConfig(sConfigFilename, format);
			}
		}
		pSimulant = pSimulant->GetNextSimulant();
	}
  return ptSimulant;
}*/

/*CIoSimulant *CIoAgentXMLSimulation::ReadConfigSimulatorIterator(CIoSimulant *pSimulant, char *sConfigFilename, char *format)
{
    CIoAgentModel *pAgentModel=NULL;
    CIoModel *pModel = NULL;
	CIoSimulant *ptSimulant=pSimulant;
    pSimulant = pSimulant->GetNextSimulant();
	while(pSimulant)
	{
		if(pSimulant && pSimulant->GetSimulantType()==IO_SIMULANT_TYPE_SIMULATOR)
			WriteConfigSimulatorIterator(pSimulant, sConfigFilename, format);
		else
		{
			pModel = (CIoModel *)pSimulant;
			if(!strcmp(pModel->GetModelClass(), "AgentModel"))
			{
				pAgentModel = (CIoAgentModel *)pModel;
                pAgentModel->ReadConfig(sConfigFilename, format);
			}
		}
		pSimulant = pSimulant->GetNextSimulant();
	}
  return ptSimulant;
}*/

int CIoAgentXMLSimulation::ReadSimulation(char *sSimFilename)
{
	int status;

	status=CIoXMLSimulation::ReadSimulation(sSimFilename);
	if(m_pSimulant)
	{
	  ((CIoAgentModel *)(m_pSimulant))->ClearFunctionHandlers();
	  ((CIoAgentModel *)(m_pSimulant))->CreateFunctionHandlers();
	}

	//specialised methods here
    /*if(m_iCreateMethod == 1)
	{
		if(m_pSimulant && (m_pSimulant))
			m_pSimulant->CreateConfig();
	}*/
	return status;

}





