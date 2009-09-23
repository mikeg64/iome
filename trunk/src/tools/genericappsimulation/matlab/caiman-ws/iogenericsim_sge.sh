#!/bin/sh
#$ -q short.q

IOME_SIMNAME="mysim"
#iogs initiome $IOME_SIMNAME null  &
iogs initiome $IOME_SIMNAME null  &
#ioapp genericappmat.sh ../caimansaasexample.m mysim nullmatlab -nosplash -nodisplay -r ../caimansaasexample.m
