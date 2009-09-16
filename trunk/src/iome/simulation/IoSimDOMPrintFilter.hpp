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

/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 2001, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Id: IoSimDOMPrintFilter.hpp,v 1.1.1.1 2005/10/24 21:36:36 mike Exp $
 * $Log: IoSimDOMPrintFilter.hpp,v $
 * Revision 1.1.1.1  2005/10/24 21:36:36  mike
 * no message
 *
 * Revision 1.1.1.1  2005/09/22 19:35:30  mike
 * no message
 *
 * Revision 1.1.1.1  2004/04/19 19:32:00  Mike
 * no message
 *
 * Revision 1.3  2002/06/04 14:22:51  peiyongz
 * Implement setter/getter from DOMWriterFilter
 *
 * Revision 1.2  2002/06/03 22:40:07  peiyongz
 * *** empty log message ***
 *
 * Revision 1.1  2002/05/29 13:33:32  peiyongz
 * DOM3 Save Interface: DOMWriter/DOMWriterFilter
 *
 */

//////////////////////////////////////////////////////////////////////
// DOMPrintFilter.hpp: a sample implementation of DOMWriterFilter.
//
//////////////////////////////////////////////////////////////////////

#ifndef SimDOMPrintFilter_HEADER_GUARD_
#define SimDOMPrintFilter_HEADER_GUARD_

#include <xercesc/dom/DOMWriterFilter.hpp>

#ifndef IO_MSVC
    XERCES_CPP_NAMESPACE_USE
#endif

using namespace xercesc;

class CIoSimDOMPrintFilter : public DOMWriterFilter {
public:

    /** @name Constructors */
	CIoSimDOMPrintFilter(unsigned long whatToShow = DOMNodeFilter::SHOW_ALL);
    //@{

    /** @name Destructors */
	~CIoSimDOMPrintFilter(){};
    //@{

	/** @ interface from DOMWriterFilter */
	virtual short acceptNode(const DOMNode*) const;
    //@{

	virtual unsigned long getWhatToShow() const {return fWhatToShow;};

	virtual void          setWhatToShow(unsigned long toShow) {fWhatToShow = toShow;};

private:
	// unimplemented copy ctor and assignement operator
	CIoSimDOMPrintFilter(const CIoSimDOMPrintFilter &);
	CIoSimDOMPrintFilter & operator = (const CIoSimDOMPrintFilter &);

	unsigned long fWhatToShow;   

};

#endif
