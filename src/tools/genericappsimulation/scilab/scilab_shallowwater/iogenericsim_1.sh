#!/bin/sh
echo "starting scilab"

#IOME_SIMNAME="intsaas1"
#iogs initiome $IOME_SIMNAME null  &



scilab -nb -nw -f ../scilabsaasexample.sce

#submits job to sge and waits for it to finish
#qsub -sync y iogenericsim_sge.sh
