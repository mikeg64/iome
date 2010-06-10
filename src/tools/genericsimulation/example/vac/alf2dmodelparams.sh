#!/bin/sh 


simulationparams="alf2dsimparams.sh"
simulationfile=$simulationname".xml"
rundate=`date`

modelname="alfven2d"
modelnotes="test alfven2d"

vaciniparfile="alf2dvacini.par"
vacparfile="alf2dvac.par"

#distributed ini file configured for 10 processor iceberg
	#the distributed infile must be of the form
        #filename_npFFLL.ini
        #FF and LL are integeres
        #FF is the first processor
        #LL is the last processor
        #example
        #filename_np0110.ini
inifile="data/shearalfven2d.ini"
distribinifile="data/vacinifile_np0110.ini"

#vacpar parameters
#file must contain the line starting #vacparlist enclosed by %%
#     this line contains a space separated list of the variables
#     the first character of this variable name is its type 
#     d=double, i=integer, v=vector, s=string
#%vacparlist% suplogfile supoutfile
par[0]="shearalfven2df.log"
par[1]="shearalfven2df.out"

#vacinipar parameters
#file must contain the line starting #vaciniparlist enclosed by %%
#     this line contains a space separated list of the variables
#     the first character of this variable name is its type 
#     d=double, i=integer, v=vector, s=string
#%vaciniparlist%
ipar1=""
ipar2=""
ipar3=""
