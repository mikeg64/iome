#!/bin/sh

dxfile=$1
lusername=$2
cusername=$3
lserver=$4
clientaddress=$5
port="8080"
idclient="0"

ssh -f -Y -R"$port":"$clientaddress":"$port" $cusername"@"$clientaddress bin/dxwebclient2 $dxfile $lusername $lserver $idclient $port
