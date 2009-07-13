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

#include "IoSimulationReader.h"

CIoSimulationReader::CIoSimulationReader(void)
{
	    // Initialize the XML4C2 system

        //XMLPlatformUtils::Initialize();



}

CIoSimulationReader::~CIoSimulationReader(void)
{
	//XMLPlatformUtils::Terminate();
}

int CIoSimulationReader::ParseSimulationFile(char *sSimFileName, CIoXMLSimulation *pSimulation)
{
	int status = 1;
    const char*                  xmlFile      = 0;
    SAX2XMLReader::ValSchemes    valScheme    = SAX2XMLReader::Val_Auto;
    bool                         doNamespaces = true;
    bool                         doSchema = true;
    bool                         schemaFullChecking = false;
    bool                         doList = false;
    bool                         errorOccurred = false;
    bool                         namespacePrefixes = false;
    
	    //
    //  Create a SAX parser object. Then, according to what we were told on
    //  the command line, set it to validate or not.
    //
    SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	
    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, doNamespaces);
    parser->setFeature(XMLUni::fgXercesSchema, doSchema);
    parser->setFeature(XMLUni::fgXercesSchemaFullChecking, schemaFullChecking);
    parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, namespacePrefixes);

    if (valScheme == SAX2XMLReader::Val_Auto)
    {
        parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(XMLUni::fgXercesDynamic, true);
    }
    if (valScheme == SAX2XMLReader::Val_Never)
    {
        parser->setFeature(XMLUni::fgSAX2CoreValidation, false);
    }
    if (valScheme == SAX2XMLReader::Val_Always)
    {
        parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(XMLUni::fgXercesDynamic, false);
    }

    //
    //  Create our SAX handler object and install it on the parser, as the
    //  document and error handler.
    //
    CIoSimulationSAXHandler handler;
	handler.m_pSimulation = pSimulation;
    parser->setContentHandler(&handler);
    parser->setErrorHandler(&handler);

    //
    //  Get the starting time and kick off the parse of the indicated
    //  file. Catch any exceptions that might propogate out of it.
    //
    unsigned long duration;


    //ifstream fin;
	xmlFile = sSimFileName;

       //reset error count first
        handler.resetErrors();

       // try
       // {
            const unsigned long startMillis = XMLPlatformUtils::getCurrentMillis();

            parser->parse(xmlFile);
            const unsigned long endMillis = XMLPlatformUtils::getCurrentMillis();
            duration = endMillis - startMillis;
       // }

      //  catch (const XMLException& e)
       // {
            /*cerr << "\nError during parsing: '" << xmlFile << "'\n"
                << "Exception message is:  \n"
                << StrX(e.getMessage()) << "\n" << endl;
            errorOccurred = true;*/
		//	status = 0;

       // }

       // catch (...)
        //{
            //cerr << "\nUnexpected exception during parsing: '" << xmlFile << "'\n";
            //errorOccurred = true;
		//	status = 0;

       // }


        // Print out the stats that we collected and time taken
        if (!handler.getSawErrors())
        {
			status = 0;
            /*cout << xmlFile << ": " << duration << " ms ("
                << handler.getElementCount() << " elems, "
                << handler.getAttrCount() << " attrs, "
                << handler.getSpaceCount() << " spaces, "
                << handler.getCharacterCount() << " chars)" << endl;*/
        }
        else
            status=1;
 

    //
    //  Delete the parser itself.  Must be done prior to calling Terminate, below.
    //
    delete parser;


	return status;
}
