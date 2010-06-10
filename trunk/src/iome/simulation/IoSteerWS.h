//gsoap ns service name:	IoSteerWS
//gsoap ns service style:	rpc
//gsoap ns service encoding:	encoded
//gsoap ns service namespace:	http://mikeg.staff.shef.ac.uk/xml/IOSteerWS.wsdl
//gsoap ns service location:	http://mikeg.staff.shef.ac.uk/IOSteerWS.cgi

//gsoap ns schema namespace: urn:IoSteerWS

struct fdata 
{
public :
	double *__ptr;
	int __size;
};
int ns__add(double a, double b, double *result);

//int ns__getstep(int id, int *step);
//int ns__setstep(int id, int newstep, int *step);

//int ns__getnsteps(int id, int *nsstep);
//int ns__setnsteps(int id, int newnsteps, int *nsteps);




//int ns__getprocid(int id, int *procid);
//int ns__getnumprocs(int id, int *numprocs);

//int ns__runsimulationstep( int id, int istepnum, int *status);
// if sim file content is null just runs the simulation using current state
int ns__runsimulation( int id, char *simfilecontent, char **result);

int ns__requestsimulation(char *simfilecontent, int *isimid);
int ns__runrequestedsimulation(int isimid, int *istatus);

int ns__submitsimulation(char *simfilecontent, int *isimid);
int ns__simulationstatus(int isimid, int *status);
int ns__setsimulationstatus(int newstatus, int isimid, int *status);
int ns__getsimulationresults(int isimid, char **result);
int ns__deletesimulation(int isimid, int *status);

//Generic simulation operations only
int ns__newsimulation( int id, char *simname, char *xslname, int *status);
int ns__createsimulation( int id, char *filename, int *status);

int ns__writelocalsimulation( int id, char *filename, char **filecontent);
int ns__readlocalsimulation( int id, char *filename, int *status);
int ns__writesimulation( int id, char *filename, char **filecontent);
int ns__readsimulation( int id, char *filename, int *status);
//int ns__writestate( int id, char *filename, char **filecontent);
//int ns__writeconfig( int id, char *filename, char **filecontent);
int ns__exitiome(int id, int *status);

int ns__addparamdouble( int id, char *name, double value, int iflag, int *status );
int ns__addparamint(  int id, char *name, int value, int iflag, int *status );
int ns__addparamvec(  int id, char *name, struct fdata value, int n, int iflag, int *status );
int ns__addparammat(  int id, char *name, struct fdata value, int nr, int nc, int iflag, int *status );
int ns__addparamstring(  int id, char *name, char *value, int iflag, int *status );
int ns__addparammmat3d(  int id, char *name, struct fdata value, int n, int p, int q, int nr, int nc,int iflag, int *status );


int ns__addmetadata( int id, char *name, char *property, int *status);

int ns__getparamdouble( int id, char *name, double *value );
int ns__getparamint(  int id, char *name, int *value );
int ns__getparamvec(  int id, char *name, int n, struct fdata **dval );
int ns__getparammat(  int id, char *name, int nr, int nc, struct fdata **dval );
int ns__getparamstring(  int id, char *name, char **value );
int ns__getparammmat3d(  int id, char *name, int n, int p, int q, int nr, int nc, struct fdata **mmat3d );

int ns__getmetadata(int id, char *name, char **property);



int ns__setparamdouble( int id, char *name, double value, int *status );
int ns__setparamint(  int id, char *name, int value, int *status  );
int ns__setparamvec(  int id, char *name, struct fdata value, int n, int *status  );
int ns__setparammat(  int id, char *name, struct fdata value, int nr, int nc, int *status  );
int ns__setparamstring(  int id, char *name, char *value, int *status  );
int ns__setparammmat3d(  int id, char *name, struct fdata value, int n, int p, int q, int nr, int nc, int *status  );

int ns__setmetadata(int id, char *name, char *property, int *status);
int ns__listmetadata(int id, char **list);
int ns__deletemetadata(int id, char *name, int *status);

int ns__deleteparam(char *name, int id, int *status );


int ns__listparam(char *type, int id, char  **list );


int ns__getnumobj(int id, int *numobj);
int ns__getobjnum(int id, int *objnum);

/*int ns__setgroupparamdouble(int id, char *name, double value, int *status );
int ns__setgroupparamint( int id, char *name, int value, int *status  );
int ns__setgroupparamvec( int id, char *name, struct fdata value, int n, int *status  );
int ns__setgroupparammat( int id, char *name, struct fdata value, int nr, int nc, int *status  );
int ns__setgroupparamstring( int id, char *name, char *value, int *status  );
int ns__setgroupparammmat3d( int id, char *name, struct fdata value, int n, int p, int q, int nr, int nc, int *status  );

int ns__getgroupparamdouble(int id, char *name, double *value );
int ns__getgroupparamint( int id, char *name, int *value );
int ns__getgroupparamvec( int id, char *name, int n, struct fdata **dval );
int ns__getgroupparammat( int id, char *name, int nr, int nc, struct fdata **dval );
int ns__getgroupparamstring( int id, char *name, char **value );
int ns__getgroupparammmat3d( int id, char *name, int n, int p, int q, int nr, int nc, struct fdata **mmat3d );*/

/*int ns__testgroupbarrier(int id, int *state);
int ns__setgroupbarrier(int id, int state, int *newstate);*/