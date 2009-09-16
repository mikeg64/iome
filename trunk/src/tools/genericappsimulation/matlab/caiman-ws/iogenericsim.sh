#!/bin/sh
echo "starting scilab"

IOME_SIMNAME="mysim"
#iogs initiome $IOME_SIMNAME null  &

IOME_WSPORT=`cat ${IOME_SIMNAME}_port.txt`
#rm ${IOME_SIMNAME}_port.txt
echo port is $IOME_WSPORT

#scilab -nb -nw -f ../scilabsaasexample.sce

#submits job to this compute node
ioapp genericappmat.sh ../caimansaasexample.sce mysim null
#iogs simulationstatus 0 $IOME_WSPORT localhost

#submits job to sge and waits for it to finish
#qsub -sync y iogenericsim_sge.sh

echo finished
exit 0
