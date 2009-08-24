


//Read input

wavetype=1; //travelling
nsteps=4;
maxamplitude=20;
wavenumber(1)=10;
wavenumber(2)=5;
wavefreq=8;
delta(1)=0.01;
delta(2)=0.01;
nmax(1)=100;
nmax(2)=100;
deltat=0.05;

steeringenabled=0;
finishsteering=0;


//params2
tstep=1;
//Wave packet
npackets=5;
pwavfreq=2;
pwavnum=7;

jobname='job1';
//chdir( jobname);
outfile='.out';
formfile='.form';

params1=struct('wavetype',wavetype,'nsteps',nsteps,'maxamplitude',maxamplitude,'wavenumber',wavenumber,'wavefreq',wavefreq,'delta',delta,'nmax',nmax,);
params2=struct('tstep',tstep,'npackets',npackets,'pwavfreq',pwavfreq,'pwavnum',pwavnum,'jobname',jobname,'steeringenabled',steeringenabled,'finishsteering',finishsteering);



metadata.directory='out';
metadata.author='MikeG';
metadata.sdate=date();
metadata.platform='felix';
metadata.desc='A simple test of SAAS';
metadata.name='intsaas1';

elist=list(2);
elist(1)='localhost';
elist(2)=8080;
elist(3)=0;


