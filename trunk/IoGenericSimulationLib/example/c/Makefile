#Makefile for StarSimulation IoSimTestSimple

##### User configurable options #####
include make_suilven
### End User configurable options ###





BASICEXOBJS	=\
	$(oDir)/IoTest.o\
	../../IoGenericSimulationLib.o\
	../../../IoSimulation/IoGenericSteerSimulation.o\
	../../../IoSimulation/stdsoap2.o\
	../../../IoSimulation/soapC.o\
	../../../IoSimulation/soapClient.o

	
ALLOBJS	=	$(BASICEXOBJS)
ALLBIN	=	$(Bin)/iotestc


#MYLIBS	=	libAgentSimulation2.a

#@# Targets follow ---------------------------------

##all:	IoSimTestSimple




cleanobjs:
	rm -f $(BASICEXOBJS)

cleanbin:
	rm -f $(ALLBIN)


clean:	cleanobjs cleanbin

cleanall:	cleanobjs cleanbin

all: iotestc






#all:IoSimTestSimple
	
#clean:
#	-rm $(OBJ) $(Bin)/IoSimTestSimple

#@# Dependency rules follow -----------------------------


iotestc:$(BASICEXOBJS) IoTest.o
	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/iotestc $(BASICEXOBJS) $(MYLIBS)



.cpp.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)  -o $@ -c $<

.c.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)    -o $@ -c $<


