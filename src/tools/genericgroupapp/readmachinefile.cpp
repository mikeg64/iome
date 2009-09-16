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


	string sinline,sserver,sq,sjunk;
	int iserver;

	if(argc>2)
	{
	ifstream infile;
	ofstream outfile;
	
	infile.open (argv[1], ofstream::in);
	outfile.open (argv[2], ofstream::out);
	while(!infile.eof())
	{
		infile>>sserver>>iserver>>sq>>sjunk;

		//for(i=0; i<iserver; i++)
		outfile<<sserver<<" "<<iserver<<endl;


		sinline.clear();
		sserver.clear();
	}



	outfile.close();
	infile.close();

	}

   return 0;
}