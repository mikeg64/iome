#!/bin/sh
#$ -q short.q


#IOME_SIMNAME="intsaas1"
#iogs initiome $IOME_SIMNAME null  &

ioapp genericappmat.sh ../caimansaasexample.sce mysim null
