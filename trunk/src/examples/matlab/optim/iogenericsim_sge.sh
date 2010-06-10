#!/bin/sh
#$ -q short.q

IOME_SIMNAME="mysim"
iogs initiome null $IOME_SIMNAME null  &
sleep 10
IOME_WSPORT=`cat ${IOME_SIMNAME}0_port.txt`
echo port is $IOME_WSPORT
iogs readsimulation simfile.xml 0 $IOME_WSPORT localhost
EQUATION=`iogs getparam string equation 0 $IOME_WSPORT localhost`
JOBREF=`iogs getparam string jobref 0 $IOME_WSPORT localhost`
echo "s/%equation%/$EQUATION/" > sed.in
sed -f sed.in rastrigin.m rastrigin.m
echo "Processing file $EQUATION at `date`" > equationgafile.log


matlab -nosplash -nodisplay -r GAbatchIOWS

#may copy results back to ftp server using curl
#file would require unique id
curl -T gacontour.jpg ftp://wrgrid.group.shef.ac.uk/public_html/ioga/results/$JOBREF/gacontour.jpg --user username:password
curl -T gatraj.jpg ftp://wrgrid.group.shef.ac.uk/public_html/ioga/results/$JOBREF/gatraj.jpg --user username:password
curl -T simresults.xml ftp://wrgrid.group.shef.ac.uk/public_html/ioga/results/$JOBREF/simresults.jpg --user username:password