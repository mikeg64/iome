#Makefile for IoSimulation

##### User configurable options #####
include make_felix_i686
### End User configurable options ###

OBJ = IoSimHandler.o \
	IoSimulant.o \
	IoEntity.o \
	IoEntityType.o \
	IoEntityTypeSet.o \
	IoEntitySet.o \
	IoEntityArray1d.o \
	IoEntityArray3d.o \
	IoEntityList.o \
	IoModel.o \
	IoSimulator.o \
	IoSimulation.o \
	IoInitialiser.o \
	IoConfigDOMBuilder.o \
	IoConfigDOMPrintFilter.o \
	IoConfigSAXHandler.o \
	IoConfigReader.o \
	IoSimDOMBuilder.o \
	IoSimDOMPrintFilter.o \
	IoSimulationSAXHandler.o \
	IoSimulationReader.o \
	IoXMLSimulation.o \
	IoAgentModel.o\
	IoAgentXMLSimulation.o\
	IoAgent.o\
	IoAgentType.o\
	IoAgentTypeSet.o\
	IoAgentArray.o\
	CIoWFModel.o \
	CIoWFSimulator.o \
	CIoSimulantLink.o \
	CIoSimulantPort.o \
	IoProc.o \
	IoWFExecutable.o \
	soapC.o \
	soapClient.o \
	stdsoap2.o \
	IoWFSimulation.o \
	IoGenericSteerSimulation.o \
	IoGenericSteer.o \
	IoMetadata.o 
	 
iows: IoSteerWS.h
	soapcpp2 IoSteerWS.h	

#Compile
libIoSimulation.a : $(OBJ)
	ar -rv $(@) $(OBJ) $(MYLIBS)

	
.cpp.o:
	$(CC) $(INCLUDES) $(FLAGS)  -c $<

.c.o:
	$(CC) $(INCLUDES) $(FLAGS) -c $<

all:iows libIoSimulation.a
	cp libIoSimulation.a ../lib/libIoSimulation.a
	
cleanall :
	rm libIoSimulation.a $(OBJ)
	
clean :
	rm $(OBJ)	


