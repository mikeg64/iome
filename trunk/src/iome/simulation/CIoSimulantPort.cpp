#include <iome/simulation/CIoSimulantPort.h>

CIoSimulantPort::CIoSimulantPort(CIoSimulantPort *port)
{
	if(port !=NULL)
	{
		m_paramid=port->GetParamID();
		m_sparammap=port->GetParammap();

		m_ientitysetid=port->GetEntitySetID();
		
	
	    m_isimulantid=port->GetSimulantID();
	    m_ssimulantmap=port->GetSimulantmap();
	}
	else
	{
		m_ientitysetid=-1;
		m_ientityid=-1;
	}

}

CIoSimulantPort::~CIoSimulantPort()
{
	
	
}






void CIoSimulantPort::SetParammap(string sparammap)
{



	m_sparammap=sparammap;
		
	
}

void CIoSimulantPort::SetSimulantmap(string ssimulantmap)
{
		m_ssimulantmap=ssimulantmap;
			
	
}





