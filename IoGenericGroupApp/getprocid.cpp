#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <cstdio>
#include <cstdlib>



using namespace std;

int main(int argc, char* argv[])
{

	int icount=0;
	int i;
	int procid=0;

    string shostname;
	string sinline,sserver,sq,sjunk;
	int iserver;

	if(argc>2)
	{
	ifstream infile;
	
	infile.open(argv[1], ofstream::in);
	while(!infile.eof())
	{
			infile>>sserver>>icount;

			#ifndef IO_MSVC
				shostname=getenv("HOSTNAME");
			#else
				shostname=getenv("HOSTNAME");
			#endif

			//for(i=0; i<iserver; i++)
		
			if(strcmp(sserver.c_str(),shostname.c_str())==0)
				procid=icount;
			else
				icount++;

			sinline.clear();
			sserver.clear();		
	}
  			infile.close();

	}


 
	
   printf("%d\n",procid);
   return 0;
}
