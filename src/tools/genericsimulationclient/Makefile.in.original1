#Makefile for StarSimulation IoSimTestSimple

##### User configurable options #####
include make_suilven
### End User configurable options ###



SRCS	=\

BASICEXOBJS	=\
	$(oDir)/IoGenericSimulationClient.o\
	../IoSimulation/IoGenericSteerSimulation.o\
	../IoSimulation/stdsoap2.o\
	../IoSimulation/soapC.o\
	../IoSimulation/soapClient.o\
	../IoSimulation/soapServer.o
	

	
ALLOBJS	=	$(EXOBJS)
ALLBIN	=	$(Bin)/ioclient



cleanobjs:
	rm -f $(BASICEXOBJS)

cleanbin:
	rm -f $(ALLBIN)


clean:	cleanobjs cleanbin

cleanall:	cleanobjs cleanbin

all: ioclient




ioclient:$(BASICEXOBJS) IoGenericSimulationClient.o
	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/ioclient $(BASICEXOBJS) $(MYLIBS)


.cpp.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)  -o $@ -c $<

.c.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)    -o $@ -c $<


