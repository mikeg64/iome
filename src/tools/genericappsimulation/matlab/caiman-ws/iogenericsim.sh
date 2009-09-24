#!/bin/sh
echo "starting scilab"

#submits job to sge and waits for it to finish
#qsub -sync y iogenericsim_sge.sh
../iogenericsim_sge.sh
echo finished
exit 0
