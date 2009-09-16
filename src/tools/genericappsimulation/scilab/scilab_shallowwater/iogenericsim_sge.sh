#!/bin/sh


IOME_SIMNAME="intsaas1"
iogs initiome $IOME_SIMNAME null  &

scilab -nb -nw -f scilabsaasexample.sce
