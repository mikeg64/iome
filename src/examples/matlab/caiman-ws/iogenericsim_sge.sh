#!/bin/sh
#$ -q short.q

IOME_SIMNAME="mysim"
echo $HOSTNAME
iogs initiome null $IOME_SIMNAME null  &

cp ../caimansaasexample.m .
cp ../cpanellogin.sh .

#sleep for 10 sec allow server to start properly
sleep 10
IOME_WSPORT=`cat ${IOME_SIMNAME}0_port.txt`
echo port is $IOME_WSPORT



iogs readsimulation simfile.xml 0 $IOME_WSPORT localhost
IMFILE=`iogs getparam string imagefile 0 $IOME_WSPORT localhost`
echo "s/%imagefile%/$IMFILE/" > sed.in
sed -f sed.in cpanellogin.sh > tmp && mv tmp cpanellogin.sh

ftp -i cpaneldev.shef.ac.uk < cpanellogin.sh

#ioapp genericappmat.sh ../caimansaasexample.m mysim null
matlab -nosplash -nodisplay -r caimansaasexample
