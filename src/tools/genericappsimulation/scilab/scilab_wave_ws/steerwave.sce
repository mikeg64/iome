//Executed from scilab using format and system boxes 
//with the command:
//  /usr/bin/scilex -nw -nb -f run_wave2d_dx.sce


exec("wave2d.sce");
exec("savevtk_xym.sci");

jobname='steerjob1';

//Read input

wavetype=1; //travelling
nsteps=60;
maxamplitude=20;
wavenumber(1)=10;
wavenumber(2)=5;
wavefreq=8;
delta(1)=0.01;
delta(2)=0.01;
nmax(1)=100;
nmax(2)=100;
deltat=0.05;
tstep=1;


//Wave packet
npackets=5;
pwavfreq=2;
pwavnum=7;
//chdir( jobname);



outfile='.out';
formfile='.form';
outfile='out/'+jobname+'.out';
formfile=jobname+'.form';
sdir='out';



//clf;
x=1:1:nmax(1);
y=1:1:nmax(2);

fdform=mopen(formfile,'w');
  mfprintf(fdform, '%d %d %d\n',nsteps, nmax(1), nmax(2));
mclose(fdform);

//fd=mopen(outfile,'w');
//xset("colormap",jetcolormap(64));
gendxgen(sdir,jobname,2,nmax(1),nmax(2));
for i=tstep:tstep+nsteps
z=wave2d(i*deltat, wavetype, maxamplitude, wavenumber, wavefreq, delta,nmax);

sfilename=sprintf("z_%d",i);
//Write data to output
//savevtk_xym(x,y,z,"z",sfilename);
//write the data to a temporary file 
fd=mopen('temp','w');
mfprintf(fd, '%d %d %d\n',i, nmax(1), nmax(2));
 for j1=1:nmax(1)
  for j2=1:nmax(2)
      mfprintf(fd, '%f',z(j1,j2));
  end
  mfprintf(fd, '\n');
 end

mclose(fd);

//as soon as the file is written we can copy to the working directory
scommand=sprintf("cp temp %s\n",outfile);
unix_g(scommand);

//zzm = min(z); zzM = max(z);
//[xf,yf,zf]=genfac3d(x,y,z);
//zcol = dsearch(z, linspace(zzm, zzM, 65));
//plot3d(x, y, list(z, zcol), flag = [-2 6 4])

//plot3d(x,y,z);
end //end of cycling over steps




//plot3d(x,y,z);
//exit;

