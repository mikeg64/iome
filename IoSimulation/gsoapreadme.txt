To build the server side tools
Use gsoap toolkit for windows used gsoap_win32_2.7.9I.zip
Starting from the webservice header file
IoSteerWS.h

The serever side files may be generated from the following gsoap
instruction

gsoap -S IoSteerWS.h


Copy the generated files into IoSimulation

we also need the follwoing files which are copied from the gsoap
distribution folder


stdsoap2.cpp
stdsoap2.h


The iome appplication is then built