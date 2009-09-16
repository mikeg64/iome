#ifndef CIoSimulantLink_H_
#define CIoSimulantLink_H_
//#define USEMPI
#ifdef USEMPI
	#include <mpi.h>
	
#endif

#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>



#include <iome/simulation/IoModel.h>



class CIoSimulantLink
{
public:
	CIoSimulantLink(CIoSimulantPort *from=NULL, CIoSimulantPort *to=NULL);
	virtual ~CIoSimulantLink();
	
	CIoSimulantPort m_fromport;
	CIoSimulantPort m_toport;

	#ifdef USEMPI
		MPI::Intracomm m_comm;
		int m_nprocs;
		int m_irank;
	#endif

	void SetFromPort(CIoSimulantPort *port){m_fromport=new CIoSimulantPort(port);}
	void SetToPort(CIoSimulantPort *port){m_toport=new CIoSimulantPort(port);}

	CIoSimulantPort *GetFromPort(){return &m_fromport;}
	CIoSimulantPort *GetToPort(){return &m_toport;}
	CIoSimulant *GetFromSimulant(){return m_fromport.m_simulant;}
	CIoSimulant *GetToSimulant(){return m_toport.m_simulant;}
	int movedata();
	int mpisimulantmovedata();
	int localsimulantmovedata();

	int mpientitymovedata();
	int localentitymovedata();

	int mpiemovedata();
	int localemovedata();

	int mpiesmovedata();
	int localesmovedata();

	
    

};

#endif /*CIOSIMULANTLINK_H_*/
