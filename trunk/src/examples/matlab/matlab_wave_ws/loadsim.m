function [consts,domain,source,metadata]=loadsim(simfile,elist)
%add initial wave height as new param
%loads a simulation file and sets the consts and domains
%elist=list();  parameter used by iome to contain port and server address
readsimulation(simfile,elist)


params1.wavetype=getparamint('wavetype',elist); %travelling
params1.nsteps=getparamint('nsteps',elist);
params1.maxamplitude=getparamint('maxamplitude',elist);
params1.wavenumber=getparamvec('wavenumber',2,elist);   %vec(2)
params1.wavefreq=getparamdouble('wavefreq',elist);
params1.delta=getparamvec('delta',2,elist);               %vec(2)
params1.nmax=getparamvec('nmax',2,elist);                 %vec(2)
params1.deltat=getparamdouble('deltat',elist);

params2.steeringenabled=getparamint('steeringenabled',elist);
params2.finishsteering=getparamint('finishsteering',elist);


%params2
params2.tstep=getparamdouble('tstep',elist);
params2.jobname=getparamstring('jobname',elist);


metadata.directory=getmetadata('directory',elist);
metadata.author=getmetadata('author',elist);
metadata.sdate=getmetadata('date',elist);
metadata.platform=getmetadata('platform',elist);
metadata.desc=getmetadata('description',elist);
metadata.name=getmetadata('name',elist);


%endfunction

