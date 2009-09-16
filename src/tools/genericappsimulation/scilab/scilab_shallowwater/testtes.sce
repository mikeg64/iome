AddMetadata('author',metadata.author,elist);
//AddMetadata('author',metadata.author,elist);
AddMetadata('date',metadata.sdate,elist);
AddMetadata('platform',metadata.platform,elist);
AddMetadata('name',metadata.name,elist);
AddMetadata('description',metadata.desc,elist);


AddFloatParam('frequency',source.sf,7,elist);
AddFloatParam('amplitude',source.sf,7,elist);
AddFloatParam('sx',source.sf,7,elist);
AddFloatParam('sy',source.sf,7,elist);

// Constants
AddFloatParam('g',consts.g,7,elist);
AddFloatParam('u0',consts.u0,7,elist);
AddFloatParam('v0',consts.v0,7,elist);
AddFloatParam('b',consts.b,7,elist);
AddFloatParam('h0',consts.h0,7,elist);

//Domain definition
// Define the x domain
//ni = 151; 
ni=domain.ni;
xmax = domain.xmax;                      
dx = xmax/(ni-1);
x  = [0:dx:xmax];

// Define the y domain
//nj = 151;  
nj=domain.nj;
ymax = domain.ymax;                      
dy = ymax/(nj-1);
y  = [0:dy:ymax];

tmax = domain.tmax;

// Define the wavespeed
wavespeed = u0 + sqrt(g*(h0 - b));

// Define time-domain
dt = 0.68*dx/wavespeed;

//t = [0:dt:tdomain];
t=[1:dt:tmax];
courant = wavespeed*dt/dx;

AddFloatParam('ni',domain.ni,7,elist);
AddFloatParam('nj',domain.ni,7,elist);
AddFloatParam('xmax',domain.xmax,7,elist);
AddFloatParam('ymax',domain.ymax,7,elist);
AddFloatParam('tmax',domain.tmax,7,elist);

statsu=zeros(length(t),3);
statsv=zeros(length(t),3);
statsh=zeros(length(t),3);

AddMatParam('statsu',statsu,length(t),3,7,elist);
AddMatParam('statsv',statsv,length(t),3,7,elist);
AddMatParam('statsh',statsh,length(t),3,7,elist);

AddStringParam('resultsfile','results.zip',7,elist);
