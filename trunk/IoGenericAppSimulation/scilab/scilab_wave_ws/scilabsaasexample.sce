//tdp=getenv('SCILAB_HOME')+'/share/scilab/contrib/iome_toolbox/loader.sce';
//tdp=getenv('SCILAB_HOME')+'/contrib/iome_toolbox/loader.sce';
tdp=getenv('SCI')+'/contrib/iome_toolbox/loader.sce';
exec(tdp);
//this application is started using the io  start scilab application
exec('../paramssaastest1.sce');
exec('../wave2d.sce');

//open the file generated
//portfile='ioserverinfo.txt';                            //add comment if  we are not running standalone
//portfile='ioserverinfo.txt';                      //remove comment if  we are not running standalone
portfile='mysim0_port.txt';
fd=mopen(portfile,'r');
//res=mfscanf(fd,'%d %d %s')
res=mfscanf(fd,'%d')
mclose(fd);

//port=res(1) id=res(2) hostname=res(3)
//elist=iome(res(3),res(1),res(2));
elist=iome('localhost',res(1),0);

try
  readsimulation('simfile.xml',elist);
  [params1,params2,metadata]=loadsim(elist);  //remove comment if we are not running standalone    
catch
   disp('failed to load sim');
end

mkdir(metadata.directory);
mkdir('dx');

try
  wavetype=params1.wavetype; //travelling
  nsteps=params1.nsteps;
  maxamplitude=params1.maxamplitude;
  wavenumber=params1.wavenumber;
  wavefreq=params1.wavefreq;
  delta=params1.delta;
  nmax=params1.nmax;
  deltat=params1.deltat;
  steeringenabled=params2.steeringenabled;
  finishsteering=params2.finishsteering;


  //params2
  tstep=params2.tstep;


  jobname=params2.jobname;;
  //chdir( jobname);
  //outfile='.out';
  //formfile='.form';
  
  outfile=jobname+'.out';
  formfile=jobname+'.form'; 
  //  x=1:1:nmax(1);
  //y=1:1:nmax(2);

  fdform=mopen(formfile,'w');
    mfprintf(fdform, '%d %d %d\n',nsteps, nmax(1), nmax(2));
  mclose(fdform);

  fd=mopen(outfile,'w');

  for i=tstep:tstep+nsteps
  z=wave2d(i*deltat, wavetype, maxamplitude, wavenumber, wavefreq, delta,nmax);
   
  //Write data to output

   mfprintf(fd, '%d %d %d\n',i, nmax(1), nmax(2));
   for j1=1:nmax(1)
    for j2=1:nmax(2)
        mfprintf(fd, '%f',z(j1,j2));
    end
    mfprintf(fd, '\n');
   end

  end //end of cycling over steps
  mclose(fd);
catch
   disp('failed to run sim');
end

exitiome(elist);
simulationstatus(elist);

//remove comment if we are not running standalone

exit();

