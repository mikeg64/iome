#ifndef IOGENERICSIMULATIONMETHODS_H_
#define IOGENERICSIMULATIONMETHODS_H_

//int initiome_(char *simname, char *simxslfile, char *simfilename, char *statefilename, char *configfilename, int port, int istandalone);
extern "C" int exitiome_(int *port, char *sserver);
extern "C" int newsimulation_( int *id, char *simname, int *port, char *sserver );


extern "C" int runsimulationstep_( int *id, int *istepnum, int *port, char *sserver);


extern "C" int newsimulation_( int *id, char *simname, int *port, char *sserver );
extern "C" int createsimulation_( int *id, char *simfile, char *simname, int *port, char *sserver );
extern "C" int runsimulation_( int *id, char *simfilecontent, int *port, char *sserver );

extern "C" int requestsimulation_(char *simfilecontent, int *isimid, int *port, char *sserver);
extern "C" int runrequestedsimulation_(int *isimid, char **status, int *port, char *sserver);

extern "C" int submitsimulation_(char *simfilecontent, int *isimid, int *port, char *sserver);
extern "C" int simulationstatus_(int *isimid, char **status, int *port, char *sserver);
extern "C" int getsimulationresults_(int *isimid, char **result, int *port, char *sserver);
extern "C" int deletesimulation_(int *isimid, int *status, int *port, char *sserver);


extern "C" int readsimulation_( int *id, char *simfile, int *port, char *sserver );
extern "C" int writesimulation_( int *id, char *simfile,  int *port, char *sserver);
extern "C" int readlocalsimulation_( int *id, char *simfile, int *port, char *sserver );
extern "C" int writelocalsimulation_( int *id, char *simfile,  int *port, char *sserver);

extern "C" int addintparam_( int *id, char *sname,int iv,int *iflag,  int *port, char *sserver );
extern "C" int adddoubleparam_( int *id, char *sname,double fv,int *iflag,  int *port, char *sserver);
extern "C" int addstringparam_( int *id, char *sname,char *sv,int *iflag,  int *port, char *sserver);
extern "C" int addmatparam_( int *id, char *sname,double *vv,int *nr, int *nc,int *iflag,   int *port, char *sserver);
extern "C" int addvecparam_( int *id, char *sname,double *vv,int *n,int *iflag,   int *port, char *sserver);
extern "C" int addmmat3dparam_( int *id,char *sname,double *vv ,int *ni, int *nj, int *nk, int *nr, int *nc,int *iflag,   int *port, char *sserver);

extern "C" int addmetadata_( int *id,char *sname, char *sproperty,  int *port, char *sserver);
extern "C" int setmetadata_( int *id,char *sname, char *sproperty,  int *port, char *sserver);
extern "C" int getmetadata_( int *id,char *sname, char *sproperty,  int *port, char *sserver);
extern "C" int deletemetadata_( int *id,char *sname,  int *port, char *sserver);
extern "C" int listmetadata_(int *id, char  **list ,  int *port, char *sserver);



int setintparam_( int id,char *sname,int iv,  int port, char *sserver );
int setdoubleparam_( int id,char *sname,double fv,  int port, char *sserver);
int setstringparam_( int id,char *sname,char *sv,  int port, char *sserver);
int setmatparam_( int id,char *sname,double *vv,int nr, int nc,   int port, char *sserver);
int setvecparam_( int id,char *sname,double *vv,int n,   int port, char *sserver);
int setmmat3dparam_( int id,char *sname,double *vv ,int ni, int nj, int nk, int nr, int nc,   int port, char *sserver);

extern "C" int getintparam_( int *id,char *sname,int *iv,  int *port, char *sserver );
int getdoubleparam_( int id,char *sname,double *fv,  int port, char *sserver);
int getstringparam_( int id,char *sname,char **sv,  int port, char *sserver);
int getmatparam_( int id,char *sname,double **vv,int nr, int nc,   int port, char *sserver);
int getvecparam_( int id,char *sname,double **vv,int n,   int port, char *sserver);
int getmmat3dparam_( int id,char *sname,double **vv ,int ni, int nj, int nk, int nr, int nc,   int port, char *sserver);

int deleteparam_( int id,char *name, int *status,  int port, char *sserver );


int listparam_(char *type, int id, char  **list ,  int port, char *sserver);



int getnumobj_(int *numobj, int id,  int port, char *sserver);
int getobjnum_(int *objnum, int id);


int testgroupbarrier_(int id, int *state,  int port, char *sserver);
int setgroupbarrier_(int id, int *state,  int port, char *sserver);



#endif /*IOGENERICSIMULATIONMETHODS_H_*/
