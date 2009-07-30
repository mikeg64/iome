#!/bin/sh
echo "starting scilab"

IOME_SIMNAME="mysim"
#iogs initiome $IOME_SIMNAME null  &

IOME_WSPORT=`cat ${IOME_SIMNAME}_port.txt`
#rm ${IOME_SIMNAME}_port.txt
echo port is $IOME_WSPORT

#scilab -nb -nw -f ../scilabsaasexample.sce

ioapp genericappsci.sh ../scilabsaasexample.sce mysim null
#iogs simulationstatus 0 $IOME_WSPORT localhost

echo finished
exit 0
#submits job to sge and waits for it to finish
#qsub -sync y iogenericsim_sge.sh
