#Makefile for StarSimulation IoSimTestSimple

##### User configurable options #####
include make_suilven
### End User configurable options ###





BASICEXOBJS	=\
	IoTestc.o\
	IoTest.o\
	../../IoGenericSimulationLib.o\
	../../../IoSimulation/IoGenericSteerSimulation.o\
	../../../IoSimulation/stdsoap2.o\
	../../../IoSimulation/soapC.o\
	../../../IoSimulation/soapClient.o

	
ALLOBJS	=	$(BASICEXOBJS)
ALLBIN	=	$(Bin)/iotestf


#MYLIBS	=	libAgentSimulation2.a

#@# Targets follow ---------------------------------

##all:	IoSimTestSimple




cleanobjs:
	rm -f $(BASICEXOBJS)

cleanbin:
	rm -f $(ALLBIN)


clean:	cleanobjs cleanbin

cleanall:	cleanobjs cleanbin

all: iotestf






#all:IoSimTestSimple
	
#clean:
#	-rm $(OBJ) $(Bin)/IoSimTestSimple

#@# Dependency rules follow -----------------------------


iotestf:$(BASICEXOBJS)
	$(FF) -g $(LIBS)  $(incDirs) -o $(Bin)/iotestf $(BASICEXOBJS) $(MYLIBS)

IoTest.o: IoTest.f90
	$(FF) -o $@ -c $<


.cpp.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)  -o $@ -c $<

.c.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)    -o $@ -c $<



