#Makefile for StarSimulation IoSimTestSimple

##### User configurable options #####
include make_suilven
#include make_iceberg_mpi64
### End User configurable options ###



SRCS	=\

BASICEXOBJS	=\
	$(oDir)/IoGenericSimulationLib.o\
	../IoSimulation/IoGenericSteerSimulation.o\
	../IoSimulation/stdsoap2.o\
	../IoSimulation/soapC.o\
	../IoSimulation/soapClient.o
	


	
#include make_suilven
LIBOBJS	=\
	$(oDir)/IoGenericSimulationLib.o\
	../IoSimulation/stdsoap2.o\
	../IoSimulation/soapC.o\
	../IoSimulation/soapClient.o



	
ALLOBJS	=	$(EXOBJS)
ALLBIN	=	$(Bin)/iogensim

#MYLIBS	=	libAgentSimulation2.a

#@# Targets follow ---------------------------------

##all:	IoSimTestSimple


objs:	$(DXEXOBJS)

cleanobjs:
	rm -f $(BASICEXOBJS)

cleanbin:
	rm -f $(ALLBIN)

lib: libIoGenericSimulation.a
	cp libIoGenericSimulation.a ../lib/libIoGenericSimulation.a

clean:	cleanobjs cleanbin

cleanall:	cleanobjs cleanbin

all: lib






#all:IoSimTestSimple
	
#clean:
#	-rm $(OBJ) $(Bin)/IoSimTestSimple

#@# Dependency rules follow -----------------------------


iogensim:$(BASICEXOBJS) IoGenericSimulationLib.o
	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/iopymod $(BASICEXOBJS) $(MYLIBS)

#simulationtest:$(BASEEXOBJS) IoSimulationTest.o
#	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/simulationtest $(BASEEXOBJS) IoSimulationTest.o  $(MYLIBS)

#simulationbasictest:$(BASICEXOBJS) IoSimulationBasicTest.o
#	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/simulationbasictest -DWITH_NONAMESPACES $(BASICEXOBJS) $(MYLIBS)



#dxagentsteerclient:$(DXEXOBJS)
#	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/dxagentsteerclient -DWITH_NONAMESPACES $(DXEXOBJS) $(BASE)/lib_linux/libDXL.a $(MYLIBS)


#agentsteerclient:$(ALLOBJS)
#	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/agentsteerclient -DWITH_NONAMESPACES $(ALLOBJS) $(MYLIBS)

libIoGenericSimulation.a : $(LIBOBJS)
	ar -rv $(@) $(LIBOBJS) $(MYLIBS)


#.c.o:
#	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS) -DWITH_NONAMESPACES -o $@ -c $<


#.cpp.o:
#	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS) -DWITH_NONAMESPACES -o $@ -c $<

.cpp.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)    -o $@ -c $<

.c.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)  -o $@ -c $<

