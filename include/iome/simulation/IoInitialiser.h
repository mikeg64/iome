#ifndef IO_SIMULATION_INITIALISER_H
#define IO_SIMULATION_INITIALISER_H
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
#ifdef USEMPI
	#include <mpi.h>
#endif



#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>



#ifndef IO_MSVC
   // XERCES_CPP_NAMESPACE_USE
#endif



XALAN_CPP_NAMESPACE_USE

XALAN_USING_XERCES(XMLPlatformUtils)
XALAN_USING_XALAN(XalanTransformer)


//The class will call a parser that 
//parses an XML config file and wrappers enabling object communication

//platform configuration
//environment variables for applcations and libraries
//on different nodes
//path names of different grid nodes

//user configuration
//e.g. user home directory for each grid node
//

class CIoInitialiser
{
public:
	CIoInitialiser(void);
	~CIoInitialiser(void);

	void Initialise(int argc=1, char *argv[]=NULL);
	void Terminate();

	#ifdef USEMPI
			MPI::Intracomm m_comm;
			int m_nprocs;
			int m_irank;
			
	#endif
	
};

#endif
