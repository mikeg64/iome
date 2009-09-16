#!/bin/bash

#readmachinefile.sh

#copy the current hostfile to the current location
cp $PE_HOSTFILE pe_hostfile

readmachinefile pe_hostfile $1
