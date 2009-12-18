function waveviz()
 
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

stacksize('max');


//Wave packet
npackets=5;
pwavfreq=2;
pwavnum=7;
//chdir( jobname);

started=0;
ext='out';
outfile='.out';
formfile='.form';
outfile='out/'+jobname+'.'+ext;
formfile=jobname+'.form';
simfile=jobname+'.xml';
sdir='out';
mval=zeros(nmax(1),nmax(2));
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
  




//Creates and set graphical entities which represent the surface
//--------------------------------------------------------------
plot3d1(x,y,mval,35,45,' ');
s=gce(); //the handle on the surface
s.color_flag=1 ; //assign facet color according to Z value
title("Simple Wave","fontsize",3)

I=20:-1:1;
realtimeinit(0.1);;//set time step (0.1 seconds)  and date reference


drawnow();

//for i=1:max(size(I))
//end

  n1=nmax(1);
  n2=nmax(2);
  //nmax(1)=mfscanf(fd, '%f');
  //nmax(2)=mfscanf(fd, '%f');

 guiw1=300; guih1=300; guih2=90;
 close(1);f=figure(1,"position",[0,0,guiw1,guih1+20],"figure_name","Wave Model"); 

uicontrol(1,"style","text","string","kx","position",[30,170,70,20],...
              "horizontalalignment","left");
              
uicontrol(1,"style","text","string","ky","position",[30,120,70,20],...
              "horizontalalignment","left");              
              
b1 = uicontrol(f, "Position"  , [50 45 70 20],...
		 "Style"     , "pushbutton",...
		 "String"    , "plot",...
		 "callback"  , "plotdata(outfile,mval,s)" );

b2 = uicontrol(f, "Position"  , [110 45 70 20],...
		 "Style"     , "pushbutton",...
		 "String"    , "start",...
		 "callback"  , "started=start(started,elist)" );

b3 = uicontrol(f, "Position"  , [170 45 70 20],...
		 "Style"     , "pushbutton",...
		 "String"    , "Quit",...
		 "FontWeight", "bold",...
		 "BackgroundColor",[0 0.7 1],...
		 "callback"  , "fin=quitio(started,elist)");

// kx
hkx=uicontrol("style","slider","Min",0.1,"Max",100,"value",10,..
                     "position",[50 170 200 20]);

// ky (only for untriggered)
hky=uicontrol("style","slider","Min",0.1,"Max",100,"value",10,..
                     "position",[50 120 200 20]);
                     
  
b4 = uicontrol(f, "Position"  , [50 80 70 20],...
		 "Style"     , "pushbutton",...
		 "String"    , "update",...
		 "callback"  , "update(hkx,hky,started,elist)" );
  
  
  fin=%f
  while ~fin
    sleep(1)
  end
  close(f)
  //if started==1
    exitiome(elist);
  //end
  return
endfunction


function plotdata(outfile, mval,s)

  //for i=tstep:tstep+nsteps
  //realtime(1.0); //wait till date 0.1*i seconds
  //sleep(1000);
  
  //scommand=sprintf("cp %s tempr\n",outfile);
  fd=mopen(outfile, 'r');
  
  try
  ii=mfscanf(fd, '%f');
  nmax(1)=mfscanf(fd, '%f');
  nmax(2)=mfscanf(fd, '%f');
	for i1=1:n1
	  for j1=1:n2
	    		   fval=mfscanf(fd, '%f');    
	 		   mval(i1,j1)=fval;			   
	  end
   end


	mclose(fd);
	z=mval;
     //loadmatfile(outfile,'z');
     s.data.z = z;
     //clear(z);
  catch
    mclose(fd);
  end


//steeringenabled=0;
//finishsteering=0;

//steeringenabled=getparamint('steeringenabled',elist);
//finishsteering=getparamint('finishsteering',elist);
if finishsteering==1 
 break;  
end

//setparamdouble('step',i,elist);
if steeringenabled==1
//  maxamplitude=getparamint('maxamplitude',elist);
//  wavenumber=getparamvec('wavenumber',2,elist);   //vec(2)
//  wavefreq=getparamdouble('wavefreq',elist);
end

//zzm = min(z); zzM = max(z);
//[xf,yf,zf]=genfac3d(x,y,z);
//zcol = dsearch(z, linspace(zzm, zzM, 65));
//plot3d(x, y, list(z, zcol), flag = [-2 6 4])

//plot3d(x,y,z);
//end //end of cycling over steps

  
endfunction

function [newstarted]=start(started,elist)

 if started==0
  unix_g('start steerdemoserver.bat');
  setparamint('steeringenabled',1,elist);
  //unix_g('iogs initiome null mysim null 8080');
  exec('steerwave.sce');
  
 end
 newstarted=1;
endfunction



function [newquit]=quitio(started,elist)

 //if started==1
  setparamint('finishsteering',1,elist);
  sleep(1000);
  exitiome(elist);
 //end
 newquit=%t;
endfunction

function update(hkx,hky,started,elist)
   //if started==1
      wavenumber(1)=get(hkx,"value");
      wavenumber(2)=get(hky,"value");
      //disp(wavenumber);
      setparamvec('wavenumber',wavenumber,elist);
   //end
  
endfunction


