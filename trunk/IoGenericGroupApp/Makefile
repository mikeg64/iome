#Makefile for StarSimulation IoSimTestSimple

##### User configurable options #####
include make_suilven
#include make_iceberg_mpi64
### End User configurable options ###



SRCS	=\

BASICEXOBJS	=\
	$(oDir)/IoStartGenericGroupApp.o\
	../IoSimulation/IoGenericSteerSimulation.o\
	../IoSimulation/stdsoap2.o\
	../IoSimulation/soapC.o\
	../IoSimulation/soapClient.o\
	../IoSimulation/soapServer.o
	

EXOBJS	=\
	$(oDir)/agentsteerclient.o\
	$(oDir)/IoTestAgentSimulation.o\
	../IoSimulation/IoAgentModel.o\
	../IoSimulation/IoAgentXMLSimulation.o\
	../IoSimulation/IoAgent.o\
	../IoSimulation/IoAgentType.o\
	../IoSimulation/IoAgentTypeSet.o\
	../IoSimulation/IoAgentArray.o\
	../IoSimulation/stdsoap2.o\
	../IoSimulation/soapC.o\
	../IoSimulation/soapClient.o
	
#include make_suilven
LIBOBJS	=\
	$(oDir)/IoTestAgentSimulation.o\
	../IoSimulation/IoAgentModel.o\
	../IoSimulation/IoAgentXMLSimulation.o\
	../IoSimulation/IoAgent.o\
	../IoSimulation/IoAgentType.o\
	../IoSimulation/IoAgentTypeSet.o\
	../IoSimulation/IoAgentArray.o\
	../IoSimulation/stdsoap2.o\
	../IoSimulation/soapC.o\
	../IoSimulation/soapClient.o\
	../IoSimulation/soapServer.o

	
DXEXOBJS	=\
	$(oDir)/dxagentsteerclient.o\
	$(oDir)/IoTestAgentSimulation.o\
	../IoSimulation/IoAgentModel.o\
	../IoSimulation/IoAgentXMLSimulation.o\
	../IoSimulation/IoAgent.o\
	../IoSimulation/IoAgentType.o\
	../IoSimulation/IoAgentTypeSet.o\
	../IoSimulation/IoAgentArray.o\
	../IoSimulation/stdsoap2.o\
	../IoSimulation/soapC.o\
	../IoSimulation/soapClient.o
	
BASEEXOBJS	=\
	$(oDir)/IoTestAgentSimulation.o\
	../IoSimulation/IoAgentModel.o\
	../IoSimulation/IoAgentXMLSimulation.o\
	../IoSimulation/IoAgent.o\
	../IoSimulation/IoAgentType.o\
	../IoSimulation/IoAgentTypeSet.o\
	../IoSimulation/IoAgentArray.o\
	../IoSimulation/stdsoap2.o\
	../IoSimulation/soapC.o\
	../IoSimulation/soapClient.o\
	../IoSimulation/soapServer.o
	
ALLOBJS	=	$(EXOBJS)
ALLBIN	=	$(Bin)/iogroupapp
ALLTGT	=	$(Bin)/IoSimTestSimple

#MYLIBS	=	libAgentSimulation2.a

#@# Targets follow ---------------------------------

##all:	IoSimTestSimple


objs:	$(DXEXOBJS)

cleanobjs:
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

lib: libIoAgentSimulation.a
	cp libIoAgentSimulation.a ../lib/libIoAgentSimulation.a

clean:	cleanobjs cleanbin

cleanall:	cleanobjs cleanbin

all: iogroupapp getprocid readmachinefile






#all:IoSimTestSimple
	
#clean:
#	-rm $(OBJ) $(Bin)/IoSimTestSimple

#@# Dependency rules follow -----------------------------


iogroupapp:$(BASICEXOBJS) IoStartGenericGroupApp.o
	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/iogroupapp $(BASICEXOBJS) $(MYLIBS)

readmachinefile:readmachinefile.o
	$(LD)  -o $(Bin)/readmachinefile readmachinefile.cpp

getprocid:getprocid.o
	$(LD)  -o $(Bin)/getprocid getprocid.cpp


#simulationtest:$(BASEEXOBJS) IoSimulationTest.o
#	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/simulationtest $(BASEEXOBJS) IoSimulationTest.o  $(MYLIBS)

#simulationbasictest:$(BASICEXOBJS) IoSimulationBasicTest.o
#	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/simulationbasictest -DWITH_NONAMESPACES $(BASICEXOBJS) $(MYLIBS)



#dxagentsteerclient:$(DXEXOBJS)
#	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/dxagentsteerclient -DWITH_NONAMESPACES $(DXEXOBJS) $(BASE)/lib_linux/libDXL.a $(MYLIBS)


#agentsteerclient:$(ALLOBJS)
#	$(LD) -g $(LIBS)  $(incDirs) -o $(Bin)/agentsteerclient -DWITH_NONAMESPACES $(ALLOBJS) $(MYLIBS)

#libIoAgentSimulation.a : $(LIBOBJS)
#	ar -rv $(@) $(LIBOBJS) ../lib/libIoUtils.a  ../lib/libIoSimulation.a


#.c.o:
#	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS) -DWITH_NONAMESPACES -o $@ -c $<


#.cpp.o:
#	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS) -DWITH_NONAMESPACES -o $@ -c $<

.cpp.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS) -o $@ -c $<

.c.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)  -o $@ -c $<

