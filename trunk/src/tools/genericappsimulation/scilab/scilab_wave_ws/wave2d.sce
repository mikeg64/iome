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


params1.wavetype=getparamint('wavetype',elist); //travelling
params1.nsteps=getparamint('nsteps',elist);
params1.maxamplitude=getparamint('maxamplitude',elist);
params1.wavenumber=getparamvec('wavenumber',2,elist);   //vec(2)
params1.wavefreq=getparamdouble('wavefreq',elist);
params1.delta=getparamvec('delta',2,elist);               //vec(2)
params1.nmax=getparamvec('nmax',2,elist);                 //vec(2)
params1.deltat=getparamdouble('deltat',elist);

params2.steeringenabled=getparamint('steeringenabled',elist);
params2.finishsteering=getparamint('finishsteering',elist);


//params2
params2.tstep=getparamdouble('tstep',elist);
params2.jobname=getparamstring('jobname',elist);


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

addparamdouble('step',0,elist);
addparamint('wavetype',params1.wavetype,elist);
addparamint('nsteps',params1.nsteps,elist);
addparamdouble('maxamplitude',params1.maxamplitude,elist);
addparamvec('wavenumber',(params1.wavenumber)',elist);   //vec(2)
addparamdouble('wavefreq',params1.wavefreq,elist);
addparamvec('delta',(params1.delta)',elist);               //vec(2)
addparamvec('nmax',(params1.nmax)',elist);                 //vec(2)
addparamdouble('deltat',params1.deltat,elist);

addparamint('steeringenabled',params2.steeringenabled,elist);
addparamint('finishsteering',params2.finishsteering,elist);


//params2
addparamdouble('tstep',params2.tstep,elist);
addparamstring('jobname',params2.jobname,elist);

endfunction

//generate dx general file 
//describing magnetic fields
//particle locations
function gendxgen(directory,jobname,nsteps, n1,n2)



  //file=out/jobform.out
  //grid = 1
  //format = ascii
  //interleaving = record
  //majority = row
  //field = nsteps, nx, ny
  //structure = scalar, scalar, scalar
  //type = int, int, int
  //dependency = positions, positions, positions
  //positions = regular, 0, 1

  //end

  dxformgenfile='dx/'+jobname+'_form.general';
  fdform=mopen(dxformgenfile,'w');
    mfprintf(fdform, 'file=%s\n', directory+'/form'+jobname+'.out');
    mfprintf(fdform,'grid=1\n');
    mfprintf(fdform,'format = ascii \n interleaving = record \n majority = row \n');
    mfprintf(fdform, 'field = nsteps, nx, ny \n structure = scalar, scalar, scalar \n type = int, int, int  \n dependency = positions, positions,positions  \n positions = regular, 0, 1 \n end \n ');
  mclose(fdform);    
//generate dx general file for this data set
  //file=out/job.out
  //grid 51 x 51
  //format = ascii
  //interleaving = field
  //majority = row
  //header = lines 1

  //series =  24 , 1, 1, separator=lines 1
  //field = field0, field1
  //structure = 2-vector, scalar
  //type = float, float
  //dependency = positions, positions
  //positions = regular,regular, 0, 1,0,1

  //end
  dxgenfile='dx/'+jobname+'.general';

  fdform=mopen(dxgenfile,'w');
    mfprintf(fdform, 'file=%s\n', directory+'/'+jobname+'.out');
    mfprintf(fdform,'grid %d X %d\n',n1,n2);
    mfprintf(fdform,'format = ascii \n interleaving = field \n majority = row \n header = lines 1 \n');
    mfprintf(fdform, 'series =  %d  , 1, 1, separator=lines 1\n',nsteps-1);
    mfprintf(fdform, 'field = field0 \n structure = scalar \n type = float  \n dependency = positions  \n positions = regular,regular,0,1,0,1 \n end \n ');
  mclose(fdform);


 basedxgenfile='dx/base'+jobname+'.general';

  fdbform=mopen(basedxgenfile,'w');
   // mfprintf(fdbform, 'file=%s\n', directory+'/'+jobname+'.out');
    mfprintf(fdbform,'grid %d X %d\n',n1,n2);
    mfprintf(fdbform,'format = ascii \n interleaving = field \n majority = row \n header = lines 1 \n');
    mfprintf(fdbform, 'series =  1  , 1, 1, separator=lines 1\n');
    mfprintf(fdbform, 'field = field0\n structure = scalar \n type = float  \n dependency = positions  \n positions = regular,regular,0,1, 0,1 \n end \n ');
  mclose(fdbform);



endfunction





