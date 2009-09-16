#!/bin/sh 

projectname="defaultproject"
simulationname="defaultvacsim"
simulationnotes="general notes about the simulation"

author=`default`
vacversion=`vac4.02`
creationdate=`date`
computeresource=`echo $HOSTNAME`

dpar="22"
phipar="0"
zpar="0"
gpar="1976,44"
gparvacini="1976,400"
ppar="mhd"
upar="sim1"
onpar="cd,rk,mpi"
onparvacini="cd,rk,mpi"
offpar="mc,fct,tvdlf,tvd,impl,poisson,ct,gencoord,resist"
offparvacini="mc,fct,tvdlf,tvd,impl,poisson,ct,gencoord,resist,mpi"
vacinimakefile="Makefile"
vacmakefile="Makefile"
mpion="1"
runmake="1"
runvacini="1"
runvac="1"
templatevaciniparfile="inipar/templatevacini.par"
templatevacparfile="par/templatevac.par"
#simulationparams="simulationparams.sh"
modelparams="modelparams.sh"
