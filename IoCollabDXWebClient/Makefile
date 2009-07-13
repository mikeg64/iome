#Makefile for StarSimulation IoSimTestSimple

##### User configurable options #####
#include make_iceberg
include make_suilven
### End User configurable options ###



SRCS	=\

BASICEXOBJS	=\
	$(oDir)/dxwebclient4.o\
	../IoSimulation/stdsoap2.o\
	../IoSimulation/soapC.o\
	../IoSimulation/soapClient.o


	
ALLOBJS	=	$(BASICEXOBJS)
ALLBIN	=	$(Bin)/iocollabdxwsc
ALLTGT	=	$(Bin)/iocollabdxwsc

#MYLIBS	=	libAgentSimulation2.a

#@# Targets follow ---------------------------------

##all:	IoSimTestSimple


objs:	$(BASICEXOBJS)

cleanobjs:
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)



clean:	cleanobjs cleanbin

cleanall:	cleanobjs cleanbin

all: iocollabdxwsc






#all:IoSimTestSimple
	
#clean:
#	-rm $(OBJ) $(Bin)/IoSimTestSimple

#@# Dependency rules follow -----------------------------


iocollabdxwsc:$(BASEEXOBJS) dxwebclient4.o
	$(LD) -g $(XLIBS) $(LIBS)  $(incDirs) -o $(Bin)/iocollabdxwsc $(BASEEXOBJS) dxwebclient4.o  $(BASE)/lib_linux/libDXL.a $(MYLIBS)







#.c.o:
#	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS) -DWITH_NONAMESPACES -o $@ -c $<


.cpp.o:
	$(CC) $(C_FLAGS) $(incDirs) $(LINKFLAGS)  -o $@ -c $<



