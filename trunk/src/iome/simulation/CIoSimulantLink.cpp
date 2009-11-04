#include <iome/simulation/CIoSimulantLink.h>

CIoSimulantLink::CIoSimulantLink(CIoSimulantPort *from, CIoSimulantPort *to)
{
		#ifdef USEMPI
			m_comm=MPI::COMM_WORLD;
			m_nprocs=m_comm.Get_size();
			m_irank=m_comm.Get_rank();
		#endif
		m_fromport=(CIoSimulantPort*)new CIoSimulantPort(from);
		m_toport=(CIoSimulantPort*)new CIoSimulantPort(to);

}

CIoSimulantLink::~CIoSimulantLink()
{
}

int CIoSimulantLink::movedata()
{
	int status=0;
	//CIoSimulation *psim=GetFromSimulant()->GetParentSimulation();

	//determine move type
	int movetype=0; //1=entity set, 2=entity
	//simulant param

	
	if(m_fromport.m_ientitysetid >=0 && m_toport.m_ientitysetid >=0)
	{
		if(m_fromport.m_ientityid >=0 && m_toport.m_ientityid >=0)
			movetype=2;//entity param
		else
			movetype=1;//entity set param
	}

	
	if(movetype==0)
	{
	if(GetFromSimulant()->m_idistributemethod==1)
		mpisimulantmovedata();
	else if(GetFromSimulant()->m_idistributemethod==0)
		localsimulantmovedata();
	}
	else if(movetype==1)
	{
		if(GetFromSimulant()->m_idistributemethod==1)
			mpiesmovedata();
		else if(GetFromSimulant()->m_idistributemethod==0)
			localesmovedata();
	}
	if(movetype==2)
	{
		if(GetFromSimulant()->m_idistributemethod==1)
			mpientitymovedata();
		else if(GetFromSimulant()->m_idistributemethod==0)
			localentitymovedata();
	}

	return status;
}


int CIoSimulantLink::mpisimulantmovedata()
{
	int status=0;
	CIoParam *fromparam, *toparam;

	#ifdef USEMPI
		//send param
	    //enum IoVarType {IO_PARAM_ARRAY, IO_PARAM_INTEGER, IO_PARAM_FLOAT, IO_PARAM_VEC, IO_PARAM_MAT, IO_PARAM_STRING, IO_PARAM_STRINGARRAY, IO_PARAM_IVEC, IO_PARAM_MMAT3D, IO_PARAM_NULL};

		if(GetFromSimulant()->m_iprocid==m_irank)
		{
			int sval;
			float sfval;
			if(fromparam=GetFromSimulant()->GetProperty(m_fromport.GetParamID()))
			{
				//void MPI::Comm::Send(const void* buf, int count, const MPI::Datatype& datatype, int dest, int tag) const
				switch(fromparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=fromparam->GetIntParam();
						m_comm.Send(&sval,1,MPI::INT,GetToSimulant()->m_iprocid,1);
					break;
				case IO_PARAM_FLOAT:
						sfval=fromparam->GetFloatParam();
						m_comm.Send(&sfval,1,MPI::FLOAT,GetToSimulant()->m_iprocid,1);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}
		}

		//recv param
		if(GetToSimulant()->m_iprocid==m_irank)
		{
			if(toparam=GetToSimulant()->GetProperty(m_toport.GetParamID()))
			{
				//void MPI::Comm::Recv(void* buf, int count, const MPI::Datatype& datatype, int source, int tag) const
				float rfval;
				int rval;
				switch(toparam->GetType())
				{
				case IO_PARAM_INTEGER:
					    
						m_comm.Recv(&rval, 1,MPI::INT,GetFromSimulant()->m_iprocid,1);
						toparam->SetParam(&rval);
					break;
				case IO_PARAM_FLOAT:
					    
						m_comm.Recv(&rfval, 1,MPI::FLOAT,GetFromSimulant()->m_iprocid,1);
						toparam->SetParam(&rfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}

		}
	#endif

	return status;

}

int CIoSimulantLink::localsimulantmovedata()
{
	int status=0;
	CIoParam *fromparam, *toparam;

	
		//send param
	    //enum IoVarType {IO_PARAM_ARRAY, IO_PARAM_INTEGER, IO_PARAM_FLOAT, IO_PARAM_VEC, IO_PARAM_MAT, IO_PARAM_STRING, IO_PARAM_STRINGARRAY, IO_PARAM_IVEC, IO_PARAM_MMAT3D, IO_PARAM_NULL};

		
			int sval;
			float sfval;
			float rfval;
			int rval;

			if(((fromparam=GetFromSimulant()->GetProperty(m_fromport.GetParamID()))) && (toparam=GetToSimulant()->GetProperty(m_toport.GetParamID())) && (fromparam->GetType()) == (toparam->GetType()))
			{
				
				switch(fromparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=fromparam->GetIntParam();
						toparam->SetParam(&sval);
					break;
				case IO_PARAM_FLOAT:
						sfval=fromparam->GetFloatParam();
						toparam->SetParam(&sfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}
		
		

	return status;

}


int CIoSimulantLink::mpientitymovedata()
{
	int status=0;
	CIoParam *fromparam, *toparam;

	#ifdef USEMPI
		//send param
	    //enum IoVarType {IO_PARAM_ARRAY, IO_PARAM_INTEGER, IO_PARAM_FLOAT, IO_PARAM_VEC, IO_PARAM_MAT, IO_PARAM_STRING, IO_PARAM_STRINGARRAY, IO_PARAM_IVEC, IO_PARAM_MMAT3D, IO_PARAM_NULL};

		if(GetFromSimulant()->m_iprocid==m_irank)
		{
			int sval;
			float sfval;
			if(fromparam=GetFromSimulant()->GetProperty(m_fromport.GetParamID()))
			{
				//void MPI::Comm::Send(const void* buf, int count, const MPI::Datatype& datatype, int dest, int tag) const
				switch(fromparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=fromparam->GetIntParam();
						m_comm.Send(&sval,1,MPI::INT,GetToSimulant()->m_iprocid,1);
					break;
				case IO_PARAM_FLOAT:
						sfval=fromparam->GetFloatParam();
						m_comm.Send(&sfval,1,MPI::FLOAT,GetToSimulant()->m_iprocid,1);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}
		}

		//recv param
		if(GetToSimulant()->m_iprocid==m_irank)
		{
			if(toparam=GetToSimulant()->GetProperty(m_toport.GetParamID()))
			{
				//void MPI::Comm::Recv(void* buf, int count, const MPI::Datatype& datatype, int source, int tag) const
				float rfval;
				int rval;
				switch(toparam->GetType())
				{
				case IO_PARAM_INTEGER:
					    
						m_comm.Recv(&rval, 1,MPI::INT,GetFromSimulant()->m_iprocid,1);
						toparam->SetParam(&rval);
					break;
				case IO_PARAM_FLOAT:
					    
						m_comm.Recv(&rfval, 1,MPI::FLOAT,GetFromSimulant()->m_iprocid,1);
						toparam->SetParam(&rfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}

		}
	#endif

	return status;

}

int CIoSimulantLink::localentitymovedata()
{
	int status=0;
	CIoParam *fromparam, *toparam;

	
		//send param
	    //enum IoVarType {IO_PARAM_ARRAY, IO_PARAM_INTEGER, IO_PARAM_FLOAT, IO_PARAM_VEC, IO_PARAM_MAT, IO_PARAM_STRING, IO_PARAM_STRINGARRAY, IO_PARAM_IVEC, IO_PARAM_MMAT3D, IO_PARAM_NULL};

		
			int sval;
			float sfval;
			float rfval;
			int rval;

			if(((fromparam=GetFromSimulant()->GetProperty(m_fromport.GetParamID()))) && (toparam=GetToSimulant()->GetProperty(m_toport.GetParamID())) && (fromparam->GetType()) == (toparam->GetType()))
			{
				
				switch(fromparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=fromparam->GetIntParam();
						toparam->SetParam(&sval);
					break;
				case IO_PARAM_FLOAT:
						sfval=fromparam->GetFloatParam();
						toparam->SetParam(&sfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}
		
		

	return status;
}

int CIoSimulantLink::mpiemovedata()
{
	int status=0;
	CIoParam *fromparam, *toparam;
	CIoEntitySet *fpes, *tpes;
	CIoEntity *fpe, *tpe;
	CIoSimulant *fs,*ts;

	#ifdef USEMPI
		//send param
	    //enum IoVarType {IO_PARAM_ARRAY, IO_PARAM_INTEGER, IO_PARAM_FLOAT, IO_PARAM_VEC, IO_PARAM_MAT, IO_PARAM_STRING, IO_PARAM_STRINGARRAY, IO_PARAM_IVEC, IO_PARAM_MMAT3D, IO_PARAM_NULL};

		if((fs=GetFromSimulant())->m_iprocid==m_irank)
		{
			//if(((fs->GetSimulantType)==IO_SIMULANT_TYPE_MODEL) &&
			//(((fpes=(CIoModel *)GetFromSimulant())->GetEntitySet(m_fromport.m_ientitysetid))!=NULL) &&
			//((fpe=fpes->GetEntity(m_fromport.m_ientityid))!=NULL))
			if(((fs->GetSimulantType())==IO_SIMULANT_TYPE_MODEL)   )
				if((fpes=((CIoModel *)fs)->GetEntitySet(m_fromport.m_ientitysetid))!=NULL)
					if(((fpe=fpes->GetEntity(m_fromport.m_ientityid))!=NULL))
			{
			int sval;
			float sfval;
			if(fromparam=GetFromSimulant()->GetProperty(m_fromport.GetParamID()))
			{
				//void MPI::Comm::Send(const void* buf, int count, const MPI::Datatype& datatype, int dest, int tag) const
				switch(fromparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=fromparam->GetIntParam();
						m_comm.Send(&sval,1,MPI::INT,GetToSimulant()->m_iprocid,1);
					break;
				case IO_PARAM_FLOAT:
						sfval=fromparam->GetFloatParam();
						m_comm.Send(&sfval,1,MPI::FLOAT,GetToSimulant()->m_iprocid,1);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}
			}
		}

		//recv param
		if(GetToSimulant()->m_iprocid==m_irank)
		{
			if(toparam=GetToSimulant()->GetProperty(m_toport.GetParamID()))
			{
				//void MPI::Comm::Recv(void* buf, int count, const MPI::Datatype& datatype, int source, int tag) const
				float rfval;
				int rval;
				switch(toparam->GetType())
				{
				case IO_PARAM_INTEGER:
					    
						m_comm.Recv(&rval, 1,MPI::INT,GetFromSimulant()->m_iprocid,1);
						toparam->SetParam(&rval);
					break;
				case IO_PARAM_FLOAT:
					    
						m_comm.Recv(&rfval, 1,MPI::FLOAT,GetFromSimulant()->m_iprocid,1);
						toparam->SetParam(&rfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}

		}
	#endif

	return status;
}

int CIoSimulantLink::localemovedata()
{
	int status=0;
	CIoParam *fromparam, *toparam;

	
		//send param
	    //enum IoVarType {IO_PARAM_ARRAY, IO_PARAM_INTEGER, IO_PARAM_FLOAT, IO_PARAM_VEC, IO_PARAM_MAT, IO_PARAM_STRING, IO_PARAM_STRINGARRAY, IO_PARAM_IVEC, IO_PARAM_MMAT3D, IO_PARAM_NULL};

		
			int sval;
			float sfval;
			float rfval;
			int rval;

			if(((fromparam=GetFromSimulant()->GetProperty(m_fromport.GetParamID()))) && (toparam=GetToSimulant()->GetProperty(m_toport.GetParamID())) && (fromparam->GetType()) == (toparam->GetType()))
			{
				
				switch(fromparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=fromparam->GetIntParam();
						toparam->SetParam(&sval);
					break;
				case IO_PARAM_FLOAT:
						sfval=fromparam->GetFloatParam();
						toparam->SetParam(&sfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}
		
		

	return status;
}

int CIoSimulantLink::mpiesmovedata()
{
	int status=0;
	CIoParam *fromparam, *toparam;
	CIoEntitySet *fpes, *tpes;
	CIoEntity *fpe, *tpe;
	CIoSimulant *fs,*ts;

	#ifdef USEMPI
		//send param
	    //enum IoVarType {IO_PARAM_ARRAY, IO_PARAM_INTEGER, IO_PARAM_FLOAT, IO_PARAM_VEC, IO_PARAM_MAT, IO_PARAM_STRING, IO_PARAM_STRINGARRAY, IO_PARAM_IVEC, IO_PARAM_MMAT3D, IO_PARAM_NULL};

		if((fs=GetFromSimulant())->m_iprocid==m_irank)
		{
			if(((fs->GetSimulantType())==IO_SIMULANT_TYPE_MODEL))
				if((fpes=((CIoModel *)fs)->GetEntitySet(m_fromport.m_ientitysetid))!=NULL)
					if(((fpe=fpes->GetEntity(m_fromport.m_ientityid))!=NULL))
			//if((fpes=(((CIoModel *)fs)->GetEntitySet(m_fromport.m_ientitysetid)))!=NULL)
			//if((fpe=(fpes->GetEntity(m_fromport.m_ientityid)))!=NULL)
			{
			int sval;
			float sfval;
			if(fromparam=GetFromSimulant()->GetProperty(m_fromport.GetParamID()))
			{
				//void MPI::Comm::Send(const void* buf, int count, const MPI::Datatype& datatype, int dest, int tag) const
				switch(fromparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=fromparam->GetIntParam();
						m_comm.Send(&sval,1,MPI::INT,GetToSimulant()->m_iprocid,1);
					break;
				case IO_PARAM_FLOAT:
						sfval=fromparam->GetFloatParam();
						m_comm.Send(&sfval,1,MPI::FLOAT,GetToSimulant()->m_iprocid,1);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}
			}
		}

		//recv param
		if(GetToSimulant()->m_iprocid==m_irank)
		{
			if(toparam=GetToSimulant()->GetProperty(m_toport.GetParamID()))
			{
				//void MPI::Comm::Recv(void* buf, int count, const MPI::Datatype& datatype, int source, int tag) const
				float rfval;
				int rval;
				switch(toparam->GetType())
				{
				case IO_PARAM_INTEGER:
					    
						m_comm.Recv(&rval, 1,MPI::INT,GetFromSimulant()->m_iprocid,1);
						toparam->SetParam(&rval);
					break;
				case IO_PARAM_FLOAT:
					    
						m_comm.Recv(&rfval, 1,MPI::FLOAT,GetFromSimulant()->m_iprocid,1);
						toparam->SetParam(&rfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}

		}
	#endif

	return status;
}

int CIoSimulantLink::localesmovedata()
{
	int status=0;
	CIoParam *fromparam, *toparam;

	
		//send param
	    //enum IoVarType {IO_PARAM_ARRAY, IO_PARAM_INTEGER, IO_PARAM_FLOAT, IO_PARAM_VEC, IO_PARAM_MAT, IO_PARAM_STRING, IO_PARAM_STRINGARRAY, IO_PARAM_IVEC, IO_PARAM_MMAT3D, IO_PARAM_NULL};

		
			int sval;
			float sfval;
			float rfval;
			int rval;

			if(((fromparam=GetFromSimulant()->GetProperty(m_fromport.GetParamID()))) && (toparam=GetToSimulant()->GetProperty(m_toport.GetParamID())) && (fromparam->GetType()) == (toparam->GetType()))
			{
				
				switch(fromparam->GetType())
				{
				case IO_PARAM_INTEGER:
						sval=fromparam->GetIntParam();
						toparam->SetParam(&sval);
					break;
				case IO_PARAM_FLOAT:
						sfval=fromparam->GetFloatParam();
						toparam->SetParam(&sfval);
					break;
				case IO_PARAM_VEC:

					break;
				case IO_PARAM_MAT:

					break;
				case IO_PARAM_STRING:

					break;
				case IO_PARAM_MMAT3D:

					break;


				}
			}
		
		

	return status;
}

