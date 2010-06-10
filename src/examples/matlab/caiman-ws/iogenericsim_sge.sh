#!/bin/sh
#$ -q short.q



IOME_SIMNAME="mysim"
iogs initiome null $IOME_SIMNAME null  &
sleep 10
IOME_WSPORT=`cat ${IOME_SIMNAME}0_port.txt`
echo port is $IOME_WSPORT
iogs readsimulation simfile.xml 0 $IOME_WSPORT localhost
IMFILE=`iogs getparam string imagefile 0 $IOME_WSPORT localhost`

#echo "s/%imagefile%/$IMFILE/" > sed.in
echo "Processing file $IMFILE at `date`" > imfile.log

#matlab -nosplash -nodisplay  < caimansaasexample.m 
matlab -nosplash -nodisplay  -r caimansaasexample 
