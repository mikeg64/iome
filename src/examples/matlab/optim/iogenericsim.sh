#!/bin/sh
echo "starting IOGA job at `date`"

#submits job to sge and waits for it to finish
cp ../iogenericsim_sge.sh .
cp ../GAbatchIOWS.m .
cp ../rastrigin.m .
qsub -P eemicroscopy -sync y iogenericsim_sge.sh

#echo `cat imfile.log`
#../iogenericsim_sge.sh
echo "finished at `date`"
exit 0
