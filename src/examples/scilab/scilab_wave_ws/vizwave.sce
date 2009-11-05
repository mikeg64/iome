//Executed from scilab using format and system boxes 
//with the command:
//  /usr/bin/scilex -nw -nb -f run_wave2d_dx.sce

//tdp=getenv('SCILAB_HOME')+'/share/scilab/contrib/iome_toolbox/loader.sce';
//tdp='/usr/share/scilab/contrib/iome_toolbox/loader.sce';
tdp=getenv('SCILAB_HOME')+'/contrib/iome_toolbox/loader.sce';
exec(tdp);

exec("wave2d.sce");
exec("savevtk_xym.sci");
exec("waveparams.sce");




//Wave packet
npackets=5;
pwavfreq=2;
pwavnum=7;
//chdir( jobname);



outfile='.out';
formfile='.form';
outfile='out/'+jobname+'.out';
formfile=jobname+'.form';
simfile=jobname+'.xml';
sdir='out';

//clf;
x=1:1:nmax(1);
y=1:1:nmax(2);


curFig             = scf(100001);
clf(curFig,"reset");
//demo_viewCode("anim5.sce");

drawlater();

xselect(); //raise the graphic window


// set a new colormap
//-------------------
cmap= curFig.color_map; //preserve old setting
curFig.color_map = jetcolormap(64);



disp(nsteps);
  mval=zeros(nmax(1),nmax(2));




//Creates and set graphical entities which represent the surface
//--------------------------------------------------------------
plot3d1(x,y,z,35,45,' ');
s=gce(); //the handle on the surface
s.color_flag=1 ; //assign facet color according to Z value
title("evolution of a 3d surface","fontsize",3)

I=20:-1:1;
realtimeinit(0.1);;//set time step (0.1 seconds)  and date reference


drawnow();

//for i=1:max(size(I))
//end





for i=tstep:tstep+nsteps


  realtime(i); //wait till date 0.1*i seconds




  fd=mopen(outfile, 'r');
  i=mfscanf(fd, '%f');
  n1=nmax(1);
  n2=nmax(2);
  nmax(1)=mfscanf(fd, '%f');
  nmax(2)=mfscanf(fd, '%f');

  printf('Reading matrix %d %d \n',nmax(1) ,nmax(2));
	
	for i=1:n1
	  for j=1:n2
	    		   fval=mfscanf(fd, '%f');    
	 		   mval(i,j)=fval;			   
	  end
	end
	
	mclose(fd);
	printf('finished reading %s\n', outfile);
	z1=mval;
     s.data.z = z1;





steeringenabled=getparamint('steeringenabled',elist);
finishsteering=getparamint('finishsteering',elist);
if finishsteering=1 
 break;  
end

setparamdouble('step',i,elist);
if steeringenabled=1
  maxamplitude=getparamint('maxamplitude',elist);
  wavenumber=getparamvec('wavenumber',2,elist);   //vec(2)
  wavefreq=getparamdouble('wavefreq',elist);
end

//zzm = min(z); zzM = max(z);
//[xf,yf,zf]=genfac3d(x,y,z);
//zcol = dsearch(z, linspace(zzm, zzM, 65));
//plot3d(x, y, list(z, zcol), flag = [-2 6 4])

//plot3d(x,y,z);
end //end of cycling over steps




//plot3d(x,y,z);
//exit;

