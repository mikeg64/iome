#!/bin/bash

#Run vac iome model script
#version 1.1
#Michael Griffiths 12th November 2008

#The script performs the following functions
#Following input files are used
# default mainsimulation parameters simulationparams.sh
#        
# default model parameters  model params.sh only one of these files (default)
#       all model params are contained in the iome xml files
# vacpar template file with parameter replacements
# vacinipar template file with parameter replacements
# optional mainsimulationiome.xml file containing simulation description
#     i.e. how it is built and the vac switches
#
# optional modeliome.xml file containing the actual model description

#Set the parameters for compiling vac and vacini
#user provides a string containing the switches for vac
#switches are as follows

#./setvac -on=mpi
#./setvac -g=1976,44

#Setting for demo is
#./setvac -d=22 -phi=0 -z=0 -g=1976,44 -p=mhd -u=sim1 -on=cd,rk,mpi -off=mc,fct,tvdlf,tvd,impl,poisson,ct,gencoord,resist

#use a format to specify input string
# ascript processes input parameters and names
#generates the script for reading and writing sim file


#determine use case
#newsimnewmod creates sim and mod form default par file
#newsim       creates new sim using default simfile mod read from iomodel.xml file
#newmod	      creates new mod using default modfile sim read from iosim.xml file this is the case that is used most often
if [ $# -gt "1" ]
then
	usecase=0
	case $1 in
	"newsimnewmod")
         usecase="2"
         shift
	;;
	"newsim")
         usecase="3"
         shift
	;;
	"newmod")
         usecase="1"
         shift
	;;
	esac

	
else
	exit 1
fi

simulationparams="simulationparams.sh"
if [ $usecase -eq "2"  || $usecase -eq "3" ]
then
	if [ $# -gt "1" ]
	then
		simulationparams=$1
		shift
	fi
fi

#load the default simulation params
source $simulationparams












#start the iome server (as a background job)
iogs initiome $simulationname

if [ $usecase -eq "1"  || $usecase -eq "0" ]
then
 testusecase=0
else
 testusecase=1
fi


#if the user provided an input file
if [ $# -gt "1"  &&  $testusecase -eq "0" ]
then
 #read the simulation file
 iogs readsimulation $1
 shift

dpar=`iogs getparam double dpar`
phipar=`iogs getparam double phipar`
zpar=`iogs getparam double zpar`
gpar=`iogs getparam vec gpar`
gparvacini=`iogs getparam vec gparvacini`
ppar=`iogs getparam string ppar`
upar=`iogs getparam string upar`
onpar=`iogs getparam string onpar`
onparvacini=`iogs getparam string onparvacini`
offpar=`iogs getparam string offpar`
offparvacini=`iogs getparam string offparvacini`

mpion=`iogs getparam int mpion`
runmake=`iogs getparam int runmake`
runvacini=`iogs getparam int runvacini`
runvac=`iogs getparam int runvac`

 vacinimakefile=`iogs getmetadata vacinimakefile`
 vacmakefile=`iogs getmetadata vacmakefile`
 vaciniparfile=`iogs getmetadata vaciniparfile`
 vacparfile=`iogs getmetadata vacparfile`
 templatevaciniparfile=`iogs getmetadata templatevaciniparfile`
 templatevacparfile=`iogs getmetadata templatevacparfile`
 modelparams=`iogs getmetadata modelparams`
 simulationname=`iogs getmetadata simulationname`
 simulationnotes=`iogs getmetadata simulationnotes`
 author=`iogs getmetadata author`
 vacversion=`iogs getmetadata vacversion`
 creationdate=`iogs getmetadata creationdate`
 computeresource=`iogs getmetadata computeresource`



else

#addparam
iogs addparam double dpar $dpar 7
iogs addparam double phipar $phipar 7
iogs addparam double zpar $zpar 7
iogs addparam vec gpar $gpar 7
iogs addparam vec gparvacini $gparvacini 7
iogs addparam string ppar $ppar 7
iogs addparam string upar $upar 7
iogs addparam string onpar $onpar 7
iogs addparam string onparvacini $onparvacini 7
iogs addparam string offpar $offpar 7
iogs addparam string offparvacini $offparvacini 7

iogs addparam int mpion $mpion 7
iogs addparam int runmake $runmake 7
iogs addparam int runvacini $runvacini 7
iogs addparam int runvac $runvac 7









#addmetadata
#stored as metadata
iogs addmetadata vacinimakefile $vacinimakefile
iogs addmetadata vacmakefile $vacmakefile
iogs addmetadata vaciniparfile $vaciniparfile
iogs addmetadata vacparfile $vacparfile
iogs addmetadata templatevaciniparfile $templatevaciniparfile
iogs addmetadata templatevacparfile $templatevacparfile
iogs addmetadata modelparams $modelparams
iogs addmetadata simulationname $simulationname
iogs addmetadata simulationnotes $simulationnotes

iogs addmetadata author $author
iogs addmetadata vacversion $vacversion
iogs addmetadata creationdate $creationdate
iogs addmetadata computeresource $computeresource


simfile=$simulationname".xml"
iogs writesimulation $simfile
fi




#load the default model params
modelparams="modelparams.sh"
if [ $usecase -eq "2"  || $usecase -eq "1" ]
then
	if [ $# -gt "1" ]
	then
		modelparams=$1
		shift
	fi
fi

#load the default simulation params
source $modelparams

iogs newsimulation $modelname


#  parameter names must start with d, i or s
#  double, integer, string

#get array of vacpar names
sizvacpararray=0
res=`grep %vacparlist% $modelparams`
nres=${res:14}
index=0
for vacparname in $nres
do
  vacpararray[index]= $vacparname
  index=$[$index + 1]
done
sizevacpararray = $index

#get array of vaciniparnames
sizvacpariniarray=0
res=`grep %vaciniparlist% $modelparams`
nres=${res:17}
vacpariniarray[index]
index=0
for vaciniparname in $nres
do
  vacinipararray[index]= $vaciniparname
  index=$[$index + 1]
done
sizevacinipararray = $index



#create a new simulation and read the parameters for the model

#if the user provided an input file
if [ $# -gt "1" ]
then
#read the model file
 modelfile=$1
iogs readsimulation $1


#vacpar parameters
#par1=`iogs getparam double par1`
#par2=`iogs getparam double par2`
#par3=`iogs getparam double par3`
i="0"
while [ $i -lt  $sizvacpararray ]
do 
        parname=${vacpararray[i]}
        #get the first character from the name which is the type
        partype=${parname:0:1}
	apartype="double"
	aparname=${parname:1}
	case $partype in
	d)
         apartype="double"
	;;
	i)
         apartype="int"
	;;
	v)
         apartype="vec"
	aparname=${parname:1}+ " 3"
	;;
	s)
         apartype="string"
	;;
	esac
	par[i]=`iogs getparam $apartype $aparname`
	i=$[$i+1]
done

#vacinipar parameters
#ipar1=`iogs getparam double ipar1`
#ipar2=`iogs getparam double ipar2`
#ipar3=`iogs getparam double ipar3`
while [ $i -lt  $sizvacpararray ]
do 
        iparname=vacinipararray[i]
        #get the first character from the name which is the type
        ipartype=${iparname:0:1}
	aipartype="double"
	aiparname=${iparname:1}
	case $ipartype in
	d)
         aipartype="double"
	;;
	i)
         aipartype="int"
	;;
	v)
         aipartype="vec"
	aiparname=${iparname:1}+ " 3"
	;;
	s)
         aipartype="string"
	;;
	esac
	ipar[i]=`iogs getparam $aipartype $aiparname`
	i=$[$i+1]
done


simulationparams=`iogs getmetadata simulationparams`
simulationfile=`iogs getmetadata simulationfile`
rundate=`iogs getmetadata rundate`

modelname=`iogs getmetadata modelname`
modelnotes=`iogs getmetadata modelnotes`
vaciniparfile=`iogs getmetadata vacparinifile`
vacparfile=`iogs getmetadata vacparfile`




#distributed ini file configured for 10 processor
 inifile=`iogs getmetadata inifile`
 distribinifile=`iogs getmetadata distribinifile`
else

	iogs addmetadata simulationparams $simulationparams
	iogs addmetadata simulationfile $simulationfile
        iogs addmetadata rundate $rundate

	iogs addmetadata modelname $modelname
	iogs addmetadata modelnotes $modelnotes
	iogs addmetadata vacparinifile $vacparinifile
	iogs addmetadata vacparfile $vacparfile

	#distributed ini file configured for 10 processor
	iogs addmetadata inifile $inifile
	iogs addmetadata distribinifile $distribinifile
	#vacpar parameters
	#iogs addparam double par1 $par1 7
	#iogs addparam double par2 $par2 7
	#iogs addparam double par3 $par3 7
i="0"
while [ $i -lt  $sizvacpararray ]
do 
        parname=${vacpararray[i]}
        #get the first character from the name which is the type
        partype=${parname:0:1}
	apartype="double"
	aparname=${parname:1}
	case $partype in
	d)
         apartype="double"
	;;
	i)
         apartype="int"
	;;
	v)
         apartype="vec"
	aparname=${parname:1}+ " 3"
	;;
	s)
         apartype="string"
	;;
	esac
	iogs addparam $apartype $aparname ${par[i]} 7
	i=$[$i+1]
done





#vacinipar parameters
#iogs addparam double ipar1 $ipar1 7
#iogs addparam double ipar2 $ipar2 7
#iogs addparam double ipar3 $ipar3 7
while [ $i -lt  $sizvacpararray ]
do 
        iparname=vacinipararray[i]
        #get the first character from the name which is the type
        ipartype=${iparname:0:1}
	aipartype="double"
	aiparname=${iparname:1}
	case $ipartype in
	d)
         aipartype="double"
	;;
	i)
         aipartype="int"
	;;
	v)
         aipartype="vec"
	aiparname=${iparname:1}+ " 3"
	;;
	s)
         aipartype="string"
	;;
	esac
	iogs addparam $aipartype $aiparname ipar[i] 7
	i=$[$i+1]
done


	modelfile=$modelname".xml"
	iogs writesimulation $modelfile


fi






#replace parameters in template inipar
#sed -e "s/%ipar1%/"$ipar1"/g" $templatevaciniparfile > tmp.txt
#sed -e "s/%ipar2%/"$ipar1"/g" tmp.txt > tmp1.txt
#sed -e "s/%ipar3%/"$ipar1"/g" tmp1.txt > tmp.txt
#mv tmp.txt > $vaciniparfile
#rm tmp1.txt

cp $templatevaciniparfile > tmp1.txt
while [ $i -lt  $sizvacinipararray ]
do 
        iparname=vacinipararray[i]
        #get the first character from the name which is the type
	aiparname=${iparname:1}
        val=${ipar[i]}
	sed -e "s/%$aiparname%/"$val"/g" tmp1.txt > tmp2.txt
        mv tmp2.txt tmp1.txt
	i=$[$i+1]
done
mv tmp1.txt $vaciniparfile




#replace parameters in template par
#sed -e "s/%par1%/"$par1"/g" $templatevacparfile > tmp.txt
#sed -e "s/%par2%/"$par1"/g" tmp.txt > tmp1.txt
#sed -e "s/%par3%/"$par1"/g" tmp1.txt > tmp.txt
#mv tmp.txt > $vacparfile
#rm tmp1.txt

cp $templatevacparfile > tmp1.txt
while [ $i -lt  $sizvacpararray ]
do 
        parname=vacpararray[i]
        #get the first character from the name which is the type
	aparname=${parname:1}
        val=${par[i]}
	sed -e "s/%$aparname%/"$val"/g" tmp1.txt > tmp2.txt
        mv tmp2.txt tmp1.txt
	i=$[$i+1]
done
mv tmp1.txt $vacparfile









#search for mpi in $onpar
#using bash string replacement
testvar=${onpar/mpi/xyzxxx}


if [ $testvar == $onpar ]
then
  #off  -  mpi not found in $testvar
  mpion="0"


else
  #on  -  mpi not found in $testvar
  mpion="1"

fi

if [ $runmake == "1" ]
then




	cd src

	#show the current settings
	echo "current settings"
	./setvac -s


	./setvac -d=$dpar -g=$gpar -phi=$phipar -z=$zpar -p=$ppar -u=$upar -on=$onpar -f=$offpar -s

	#show the current settings
	echo "new settings for making vac"
	./setvac -s

	make clean

	make vac -f $vacmakefile

	./setvac -d=$dpar -g=$gparvacini -phi=$phipar -z=$zpar -p=$ppar -u=$upar -on=$onparvacini -f=$offparvacini -s

	#show the current settings
	echo "new settings for making vacini"
	./setvac -s
	
	make vacini -f $vacinimakefile

	cp vac ../vac
	cp vacini ../vacini

	cd ..

fi
#end of the make vac loop

if [ $runvacini == "1" ]
then
	#./vacini < vacini/vacini.par
	./vacini < $vaciniparfile
fi

#if we are parallel 
#distribute the model 
# execute /data/distribution to get help
if [ $mpion == "1" ]
then
	#the distributed infile must be of the form
        #filename_npFFLL.ini
        #FF and LL are integeres
        #FF is the first processor
        #LL is the last processor
        #example
        #filename_np0110.ini
   
	data/distribution -D -s=0 $inifile $distribinifile

fi

if [ $runvac == "1" ]
then
	#./vacini < vacini/vacini.par
	./vac < $vacparfile
fi




