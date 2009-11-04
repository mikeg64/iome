
% Camera parameters
vfrom  = [25 25 21];
vto = [23 25 0];
vup = [0.2 0.8 0.6];
fcamwidth = 47;

istep = 1;

sname='testsim3';



cam=struct('camfrom',vfrom,'camto',vto,'camup',vup,'camwidth',fcamwidth);
settings=struct('step',istep,'name',sname);




metadata.author='MikeG';
metadata.sdate=date();
metadata.platform='felix';
metadata.desc='Collab viewer example';
metadata.name='collabtestsim3';

elist=list(2);
elist(1)='localhost';
%elist(1)='10.0.16.99';
elist(2)=8080;
elist(3)=0;


