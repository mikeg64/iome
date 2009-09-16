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
	


#include <iome/utils/IoStringArray.h>



IoStringArray::IoStringArray(char *cstring)
{
	//svs=NULL;
	if(cstring /*&& (strlen(cstring)>0)*/)
		AddString(cstring);
}

IoStringArray::IoStringArray(IoStringArray *sstring)
{
	//svs=NULL;
	if(sstring)
	{
		//SetString(0, sstring->GetString(0));
		
		for(int it=0;it <sstring->GetSize(); it++)
			AddString(sstring->GetsString(it));		  
	}
}

IoStringArray::IoStringArray(string sstring)
{
	//svs=NULL;
	SetString(0, sstring);
}

IoStringArray::~IoStringArray(void)
{
//	if(sv) delete [] sv;
//	sv = NULL;
	//if(svs)
	//	delete svs;
	svs.clear();

		//svs->erase();
	//svs=NULL;
	//svs.erase();
}

char *IoStringArray::SetString(int i, char *cstring)
{
	string svsc(cstring);
	if(cstring)
	{
		//if(svs)
		//	delete svs;
		
        if(svs.size() > i)
		 svs[i] = svsc;

	}
	return (char *)(svsc.c_str());
	
}

char *IoStringArray::SetString(int i, string sstring)
{

	if(svs.size() > i)
		 svs[i] = sstring;
	
	return (char *)(sstring.c_str());
	
}

/*char *IoStringArray::GetString(int i)
{
   //int i;
	// if(v && strlen(v)>n)
	//	for(i=n; i<strlen(v); i++) v[i] = ' ';
	string svsc("");
	if(svs.size() > i)
		 svsc = svs[i];
	
    return (char *)(svsc.c_str());
	//return sv;	
}*/

string IoStringArray::GetsString(int i)
{
   //int i;
	// if(v && strlen(v)>n)
	//	for(i=n; i<strlen(v); i++) v[i] = ' ';
	string svsc("");
	if(svs.size() > i)
		 svsc = svs[i];
	
    return svsc;
	//return sv;	
}

void IoStringArray::AddString(char *cstring)
{
	std::string svsc(cstring);
	//std::cout << svsc;
	if(cstring)
	{
		
		svs.push_back(svsc);
		//svs.
	}
	else
	  svs.push_back("");
		
	
}



void IoStringArray::RemoveString(int i)
{	
	VSTRING::iterator it=svs.begin()+i;
	if(i<svs.size())
	  svs.erase(it);	
}

ostream& operator<<(ostream& s, IoStringArray& s1)
//print a matrix
{
	VSTRING::iterator it=(s1.svs).begin();
	int n=(s1.svs).size();
	s<<n <<"\n";
	for(it=(s1.svs).begin(); it!=(s1.svs).end(); it++)
	{
		s << (string)(*it) << "\n";	
	}
	return s;
}

istream& operator>>(istream& s, IoStringArray& s1)
{
	int inum;
	
	s>>inum;
	string str;
	s1.clear();
	
    for(int i=0; i<inum; i++)
    {
    	 	s>>str;
    		s1.AddString(str);	
    }
       
	return s;
}

string IoStringArray::GetAllStrings(char *sep)
{
	string allstrings;

		for(int it=0;it <svs.size(); it++)
		{
			allstrings+=svs[it];
			allstrings+=sep;
			//strcat(allstrings, svs[it].c_str());
			//strcat(allstrings, sep);

	
				  
		
	}	
	return allstrings;
	
}

