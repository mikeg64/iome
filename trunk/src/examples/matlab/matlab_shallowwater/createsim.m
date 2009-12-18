function []=createsim(consts, domain,source,metadata,simfile,elist)

%elist=list();  parameter used by iome to contain port and server address
%elist=list();

addmetadata('author',metadata.author,elist);
addmetadata('directory',metadata.directory,elist);
addmetadata('date',metadata.sdate,elist);
addmetadata('platform',metadata.platform,elist);
addmetadata('description',metadata.desc,elist);
addmetadata('name',metadata.name,elist);

addparamdouble('frequency',source.sf,elist);
addparamdouble('amplitude',source.sa,elist);
addparamdouble('sx',source.sx,elist);
addparamdouble('sy',source.sy,elist);

% Constants
addparamdouble('g',consts.g,elist);
addparamdouble('u0',consts.u0,elist);
addparamdouble('v0',consts.v0,elist);
addparamdouble('b',consts.b,elist);
addparamdouble('h0',consts.h0,elist);

%Domain definition
% Define the x domain
%ni = 151; 
ni=domain.ni;
xmax = domain.xmax;                      
dx = xmax/(ni-1);
x  = [0:dx:xmax];

% Define the y domain
%nj = 151;  
nj=domain.nj;
ymax = domain.ymax;                      
dy = ymax/(nj-1);
y  = [0:dy:ymax];

tmax = domain.tmax;

% Define the wavespeed
wavespeed = consts.u0 + sqrt(consts.g*(consts.h0 - consts.b));

% Define time-domain
dt = 0.68*dx/wavespeed;

%t = [0:dt:tdomain];
t=[1:dt:tmax];
domain.nt=length(t);
%courant = wavespeed*dt/dx;

addparamdouble('ni',domain.ni,elist);
addparamdouble('nj',domain.ni,elist);
addparamdouble('xmax',domain.xmax,elist);
addparamdouble('ymax',domain.ymax,elist);
addparamdouble('tmax',domain.tmax,elist);
addparamint('nt',domain.nt,elist);
addparamint('steeringenabled',domain.steeringenabled,elist);
addparamint('finishsteering',domain.finishsteering,elist);
addparamint('step',domain.step,elist);


%simfile=sprintf('%s.xml',simname)

