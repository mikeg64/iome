#!/bin/bash

#Test file for submitting a job using iome
# the job start file starts iome in background
# it picks up the port adress of the iome server
#from the port file output by initiome
IOME_SIMNAME="mysim"
iogs initiome $IOME_SIMNAME null  &
sleep 3
echo "I'm running"

IOME_WSPORT=`cat ${IOME_SIMNAME}_port.txt`
rm ${IOME_SIMNAME}_port.txt
echo port is $IOME_WSPORT

iogs exitiome $IOME_WSPORT localhost
