#!/bin/sh
echo "starting caiman job at `date`"

#submits job to sge and waits for it to finish
cp ../iogenericsim_sge.sh .
cp ../caimansaasexample.m .
qsub -sync y iogenericsim_sge.sh

echo "`cat imfile.log`"


#bash ./iogenericsim_sge.sh
echo "finished at `date`"
exit 0
