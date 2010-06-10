#!/bin/sh 


simulationparams="simulationparams.sh"
simulationfile=$simulationname".xml"
rundate=`date`

modelname="mymodel"
modelnotes="my model notes"

vaciniparfile="inipar/vacini.par"
vacparfile="par/vac.par"

#distributed ini file configured for 10 processor iceberg
	#the distributed infile must be of the form
        #filename_npFFLL.ini
        #FF and LL are integeres
        #FF is the first processor
        #LL is the last processor
        #example
        #filename_np0110.ini
inifile="data/vacinifile.ini"
distribinifile="data/vacinifile_np0110.ini"

#vacpar parameters
#file must contain the line starting #vacparlist enclosed by %%
#     this line contains a space separated list of the variables
#     the first character of this variable name is its type 
#     d=double, i=integer, v=vector, s=string
#%vacparlist% dpar1 dpar2 dpar3
par[0]=""
par[0]=""
par[0]=""

#vacinipar parameters
#file must contain the line starting #vaciniparlist enclosed by %%
#     this line contains a space separated list of the variables
#     the first character of this variable name is its type 
#     d=double, i=integer, v=vector, s=string
#%vaciniparlist% dpar1 dpar2 dpar3
ipar1=""
ipar2=""
ipar3=""
