#Makefile for ioutils

##### User configurable options #####
include make_iceberg
### End User configurable options ###

OBJ = vec.o \
		vecpair.o \
		mat.o \
		ivec.o \
		IoString.o \
		IoStringArray.o \
		IoParams.o \
		IoPropertyManager.o \
		IoFileUtils.o \
		IoParamFilter.o \
		IoParamSetStats.o \
		fmat3d.o \
		mmat3d.o \
		fparser.o \
		fpoptimizer.o \
		mersenne.o \
		mother.o \
		rancombi.o

#Compile
libIoUtils.a : $(OBJ)
	ar -rv $(@) $(OBJ)

	
.cpp.o:
	$(CC) $(FLAGS) $(LINKFLAGS) -c $<

all:libIoUtils.a
	cp libIoUtils.a ../lib/libIoUtils.a
	
cleanall :
	rm libIoUtils.a $(OBJ)
	
clean :
	rm $(OBJ)	


