function []=createsim(params1,params2,metadata,simfile,elist)

%elist=list();  parameter used by iome to contain port and server address
%elist=list();

addmetadata('author',metadata.author,elist);
addmetadata('directory',metadata.directory,elist);
addmetadata('date',metadata.sdate,elist);
addmetadata('platform',metadata.platform,elist);
addmetadata('description',metadata.desc,elist);
addmetadata('name',metadata.name,elist);

addparamdouble('step',0,7,elist);
addparamint('wavetype',params1.wavetype,7,elist);
addparamint('nsteps',params1.nsteps,7,elist);
addparamdouble('maxamplitude',params1.maxamplitude,7,elist);
addparamvec('wavenumber',(params1.wavenumber)',7,elist);   %vec(2)
addparamdouble('wavefreq',params1.wavefreq,7,elist);
addparamvec('delta',(params1.delta)',7,elist);               %vec(2)
addparamvec('nmax',(params1.nmax)',7,elist);                 %vec(2)
addparamdouble('deltat',params1.deltat,7,elist);

addparamint('steeringenabled',params2.steeringenabled,7,elist);
addparamint('finishsteering',params2.finishsteering,7,elist);


%params2
addparamdouble('tstep',params2.tstep,7,elist);
addparamstring('jobname',params2.jobname,7,elist);