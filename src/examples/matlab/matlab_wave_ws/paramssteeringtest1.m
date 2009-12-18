
% Constants
g  = 9.81;
u0 = 0;                               
v0 = 0;
b  = 0;                               
h0 = 5030; 
consts=struct('g',g,'u0',u0,'v0',v0,'b',b,'h0',h0);

%Domain definition
% Define the x domain
ni = 51; 
%ni=41;
xmax = 100000;                      
dx = xmax/(ni-1);
x  = [0:dx:xmax];

% Define the y domain
nj = 51;  
%nj=41;
ymax = 100000;                      
dy = ymax/(nj-1);
y  = [0:dy:ymax];

nt=10;
step=0;
tmax = 200;
steeringenabled=1;
finishsteering=0;

domain=struct('ni',ni,'xmax',xmax,'nj',nj,'ymax',ymax,'nt',nt,'tmax',tmax,'step',step,'steeringenabled',steeringenabled,'finishsteering',finishsteering);


sf=0.05;%source frequency
sa=30;%source amplitude
sx=0.5;%source x location
sy=0.5;%source y location
source=struct('sf',sf,'sa',sa,'sx',sx,'sy',sy);

metadata.directory='out';
metadata.author='MikeG';
metadata.sdate=date();
metadata.platform='felix';
metadata.desc='A simple test of SAAS';
metadata.name='tsteer1';
elist=iome('localhost',8080,0);



