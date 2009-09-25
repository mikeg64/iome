#!/bin/sh
echo "starting caiman job"

#submits job to sge and waits for it to finish
cp ../iogenericsim_sge.sh .
qsub -sync y iogenericsim_sge.sh
#../iogenericsim_sge.sh
echo finished
exit 0
