#!/bin/sh 

projectname="alfven2d"
simulationname="defaultvacsim"
simulationnotes="general notes about the simulation alfven2d"

author="mikeg"
vacversion="vac4.52"
creationdate=`date`
computeresource=`echo $HOSTNAME`

dpar="22"
phipar="0"
zpar="0"
gpar="260,260"
gparvacini="260,260"
ppar="mhd"
upar="gravity"
onpar="cd,tvdlf,tvd,poisson,resist"
onparvacini="cd,tvdlf,tvd,poisson,resist"
offpar="mc,fct,impl,ct,gencoord,rk,mpi"
offparvacini="mc,fct,impl,ct,gencoord,rk,mpi"
vacinimakefile="Makefile"
vacmakefile="Makefile"
mpion="0"
runmake="0"
runvacini="1"
runvac="0"
templatevaciniparfile="tempalf2dvacini.par"
templatevacparfile="tempalf2dvac.par"
simulationparams="alf2dsimparams.sh"
modelparams="alf2dmodelparams.sh"
