On the linux platform the soap calls are generated using the following calls
note the -DWITH_NONAMSPACES call has been removed 
soapcpp2 -c IoSteerWS.h

The make file contains the following line
.c.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)    -o $@ -c $<

For the linux installation the directory must also include the following files
	stdsoap2.c
	soapC.c
	soapClient.c
	soapServer.c
