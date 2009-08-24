//2d wave
//return a 2d matrix of wave amplitudes
function [wave2d]=wave2d(time, wavetype, maxamplitude, wavenumber, wavefreq, delta, n)

  nx=n(1);
  ny=n(2);

  wave2d=zeros(nx,ny);
  dx=delta(1);
  dy=delta(2);

  
  k1=wavenumber(1);
  k2=wavenumber(2);
  
  //stationary/standing wave 
  if wavetype == 0 then
  
      for i=1:nx
        for j=1:ny
          wave2d(i,j)=sin((k1*i*dx)+(k2*j*dy))*sin(wavefreq*time);
        end
      end
  
  
  //travelling/progressive wave
  elseif wavetype == 1 then
    for i=1:nx
      for j=1:ny
        wave2d(i,j)=sin(((k1*i*dx)+(k2*j*dy))-(wavefreq*time));
      end
    end
  
  end

endfunction


function [params1,params2,metadata]=loadsim(elist)


params1.wavetype=getintparam('wavetype',elist); //travelling
params1.nsteps=getintparam('nsteps',elist);
params1.maxamplitude=getintparam('nsteps',elist);
params1.wavenumber=getvecparam('wavenumber',2,elist);   //vec(2)
params1.wavefreq=getdoubleparam('wavefreq',elist);
params1.delta=getvecparam('delta',2,elist);               //vec(2)
params1.nmax=getvecparam('nmax',2,elist);                 //vec(2)
params1.deltat=getdoubleparam('deltat',elist);

params1.steeringenabled=getintparam('steeringenabled',elist);
params1.finishsteering=getintparam('finishsteering',elist);


//params2
params2.tstep=getdoubleparam('tstep',elist);
//Wave packet
params2.npackets=getintparam('npackets',elist);
params2.pwavfreq=getdoubleparam('pwavfreq',elist);
params2.pwavnum=getdoubleparam('pwavnum',elist);
params2.jobname=getstringparam('jobname',elist);
//chdir( jobname);
params2.outfile=getstringparam('outfile',elist);
params2.formfile=getstringparam('formfile',elist);

metadata.directory=getmetadata('directory',elist);
metadata.author=getmetadata('author',elist);
metadata.sdate=getmetadata('date',elist);
metadata.platform=getmetadata('platform',elist);
metadata.desc=getmetadata('description',elist);
metadata.name=getmetadata('name',elist);

endfunction

function []=createsim(params1,params2,metadata,simfile,elist)

//elist=list();  parameter used by iome to contain port and server address
//elist=list();

addmetadata('author',metadata.author,elist);
addmetadata('directory',metadata.directory,elist);
addmetadata('date',metadata.sdate,elist);
addmetadata('platform',metadata.platform,elist);
addmetadata('description',metadata.desc,elist);
addmetadata('name',metadata.name,elist);


addintparam('wavetype',params1.wavetype,7,elist);
addintparam('nsteps',params1.nsteps,7,elist);
adddoubleparam('maxamplitude',params1.maxamplitude,7,elist);
addvecparam('wavenumber',params1.wavenumber,2, 7,elist);   //vec(2)
adddoubleparam('wavefreq',params1.wavefreq,elist);
addvecparam('delta',params1.delta,2,elist);               //vec(2)
addvecparam('nmax',params1.nmax,2,elist);                 //vec(2)
adddoubleparam('deltat',params1.deltat,elist);

addintparam('steeringenabled',params1.steeringenabled,elist);
addintparam('finishsteering',params1.finishsteering,elist);


//params2
adddoubleparam('tstep',params2.tstep,7,elist);
//Wave packet
addintparam('npackets',params2.npackets,7,elist);
adddoubleparam('pwavfreq',params2.pwavfreq,7,elist);
adddoubleparam('pwavnum',params2.pwavnum,7,elist);
addstringparam('jobname',params2.jobname,7,elist);
//chdir( jobname);
addstringparam('outfile',params2.outfile,7,elist);
addstringparam('formfile',params2.formfile,7,elist);


endfunction




