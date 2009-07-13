
// Constants
g  = 9.81;
u0 = 0;                               
v0 = 0;
b  = 0;                               
h0 = 5030; 
consts=struct('g',g,'u0',u0,'v0',v0,'b',b,'h0',h0);

//Domain definition
// Define the x domain
ni = 51; 
//ni=41;
xmax = 100000;                      
dx = xmax/(ni-1);
x  = [0:dx:xmax];

// Define the y domain
nj = 51;  
//nj=41;
ymax = 100000;                      
dy = ymax/(nj-1);
y  = [0:dy:ymax];

nt=10;
step=0;
tmax = 100;
steeringenabled=0;
finishsteering=0;

domain=struct('ni',ni,'xmax',xmax,'nj',nj,'ymax',ymax,'nt',nt,'tmax',tmax,'step',step,'steeringenabled',steeringenabled,'finishsteering',finishsteering);


sf=10;//source frequency
sa=5;//source amplitude
sx=20;//source x location
sy=30;//source y location
source=struct('sf',sf,'sa',sa,'sx',sx,'sy',sy);

metadata.directory='out';
metadata.author='MikeG';
metadata.sdate=date();
metadata.platform='felix';
metadata.desc='A simple test of SAAS';
metadata.name='intsaas1';

elist=list(2);
elist(1)='localhost';
elist(2)=8080;


