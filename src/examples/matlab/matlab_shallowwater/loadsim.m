function [consts,domain,source,metadata]=loadsim(simfile,elist)
%add initial wave height as new param
%loads a simulation file and sets the consts and domains
%elist=list();  parameter used by iome to contain port and server address
readsimulation(simfile,elist)
source.sf=getparamdouble('frequency',elist);%source frequency
source.sa=getparamdouble('amplitude',elist);%source amplitude
source.sx=getparamdouble('sx',elist);%source x location
source.sy=getparamdouble('sy',elist);%source y location
  
  % Constants
consts.g  =getparamdouble('g',elist);
consts.u0 =getparamdouble('u0',elist);                               
consts.v0 =getparamdouble('v0',elist);
consts.b  =getparamdouble('b',elist);                               
consts.h0 =getparamdouble('h0',elist); 

%Domain definition
% Define the x domain
%ni = 151; 
domain.ni=getparamdouble('ni',elist);
domain.xmax=getparamdouble('xmax',elist);                      
dx = domain.xmax/(domain.ni-1);
x  = [0:dx:domain.xmax];

% Define the y domain
%nj = 151;  
domain.nj=getparamdouble('nj',elist);
domain.ymax=getparamdouble('ymax',elist);                      
dy = ymax/(domain.nj-1);
y  = [0:dy:domain.ymax];
domain.nt=getparamint('nt',elist);
domain.tmax=getparamdouble('tmax',elist);
domain.step=getparamint('step',elist);
domain.steeringenabled=getparamint('steeringenabled',elist);
domain.finishsteering=getparamint('finishsteering',elist);

metadata.directory=getmetadata('directory',elist);
metadata.author=getmetadata('author',elist);
metadata.sdate=getmetadata('date',elist);
metadata.platform=getmetadata('platform',elist);
metadata.desc=getmetadata('description',elist);
metadata.name=getmetadata('name',elist);

%endfunction

