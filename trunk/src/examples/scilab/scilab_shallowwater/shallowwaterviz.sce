function shallowwaterviz()
 
    //Executed from scilab using format and system boxes 
//with the command:
//  /usr/bin/scilex -nw -nb -f run_wave2d_dx.sce

//tdp=getenv('SCILAB_HOME')+'/share/scilab/contrib/iome_toolbox/loader.sce';
//tdp='/usr/share/scilab/contrib/iome_toolbox/loader.sce';
tdp=getenv('SCILAB_HOME')+'/contrib/iome_toolbox/loader.sce';
exec(tdp);


exec("savevtk_xym.sci");
exec('ioshallowwater.sce');
exec('paramssteeringtest1.sce');
stacksize('max');




started=0;
//Domain definition
// Define the x domain
//ni = 151; 
ni=domain.ni;
xmax = domain.xmax;                      
dx = xmax/(ni-1);
x  = [0:dx:xmax];

// Define the y domain
//nj = 151;  
nj=domain.nj;
ymax = domain.ymax;                      
dy = ymax/(nj-1);
y  = [0:dy:ymax];

tmax = domain.tmax;

// Define the wavespeed
wavespeed = u0 + sqrt(g*(h0 - b));

// Define time-domain
dt = 0.68*dx/wavespeed;

//t = [0:dt:tdomain];
t=[1:dt:tmax];
domain.nt=length(t);
courant = wavespeed*dt/dx;
mval=5000*ones(ni,nj)/10;
//clf;
 
name=metadata.name;
//disp(name);
  


curFig             = scf(100001);
clf(curFig,"reset");
//demo_viewCode("anim5.sce");

drawlater();

xselect(); //raise the graphic window


// set a new colormap
//-------------------
cmap= curFig.color_map; //preserve old setting
curFig.color_map = jetcolormap(64);



disp(domain.nt);
  




//Creates and set graphical entities which represent the surface
//--------------------------------------------------------------
plot3d1(1:ni,1:nj,mval,55,10,' ');
s=gce(); //the handle on the surface
s.color_flag=1 ; //assign facet color according to Z value
title("Shallow Water Wave","fontsize",3)

I=20:-1:1;
realtimeinit(0.1);;//set time step (0.1 seconds)  and date reference


drawnow();

//for i=1:max(size(I))
//end

  n1=domain.ni;
  n2=domain.nj;
  //nmax(1)=mfscanf(fd, '%f');
  //nmax(2)=mfscanf(fd, '%f');

 guiw1=300; guih1=410; guih2=100;
 close(1);f=figure(1,"position",[0,0,guiw1,guih1+20],"figure_name","Shallow Water Wave Model"); 

  
              
b1 = uicontrol(f, "Position"  , [80 45 70 20],...
		 "Style"     , "pushbutton",...
		 "String"    , "plot",...
		 "callback"  , "plotdata(metadata,mval,domain.nt,s)" );

b2 = uicontrol(f, "Position"  , [140 45 70 20],...
		 "Style"     , "pushbutton",...
		 "String"    , "start",...
		 "callback"  , "started=start(started,elist)" );

b3 = uicontrol(f, "Position"  , [210 45 70 20],...
		 "Style"     , "pushbutton",...
		 "String"    , "Quit",...
		 "FontWeight", "bold",...
		 "BackgroundColor",[0 0.7 1],...
		 "callback"  , "fin=quitio(started,elist)");

uicontrol(1,"style","text","string","sx","position",[15,270,70,20],...
              "horizontalalignment","left");
              
uicontrol(1,"style","text","string","sy","position",[15,220,70,20],...
              "horizontalalignment","left");   


uicontrol(1,"style","text","string","amplitude","position",[15,170,70,20],...
              "horizontalalignment","left");
              
uicontrol(1,"style","text","string","frequency","position",[15,120,70,20],...
              "horizontalalignment","left");            


// kx
hsx=uicontrol("style","slider","Min",0,"Max",100,"value",50.0,..
                     "position",[80 270 200 20]);

// ky (only for untriggered)
hsy=uicontrol("style","slider","Min",0,"Max",100,"value",50.0,..
                     "position",[80 220 200 20]);

// frequency
hfrequency=uicontrol("style","slider","Min",1,"Max",100,"value",5,..
                     "position",[80 120 200 20]);

// amplitude
hamplitude=uicontrol("style","slider","Min",0.1,"Max",100,"value",30,..
                     "position",[80 170 200 20]);                     
                     
  
b4 = uicontrol(f, "Position"  , [80 80 70 20],...
		 "Style"     , "pushbutton",...
		 "String"    , "update",...
		 "callback"  , "update(hsx,hsy,hamplitude,hfrequency,started,elist)" );
  
  
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


function plotdata(metadata, mval,nsteps,s)

  for i=1:nsteps
   realtime(1.0); //wait till date 0.1*i seconds
   sleep(250);
  
  //scommand=sprintf("cp %s tempr\n",outfile);
  configfile=sprintf('out/%ss%d.mat',metadata.name,i);
  //disp(configfile);
    try
       loadmatfile(configfile);
       mval=z/10;
       s.data.z = mval;
       //clear(z);
    catch
     disp('h matrix read error!')
    end


  end //end of cycling over steps

  
endfunction

function [newstarted]=start(started,elist)

 if started==0
  unix_g('start steerdemoserver.bat');
  setparamint('steeringenabled',1,elist);
  //unix_g('iogs initiome null mysim null 8080');
  exec('steeringtest1.sce');
  
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

function update(hsx,hsy,hamplitude,hfrequency,started,elist)
   //if started==1
      sx=get(hsx,"value");
      sy=get(hsy,"value");
      frequency=get(hfrequency,"value");
      amplitude=get(hamplitude,"value");      
      //disp(wavenumber);
      setparamdouble('sx',sx/100,elist);
      setparamdouble('sy',sy/100,elist);
      setparamdouble('amplitude',amplitude,elist);
      setparamdouble('frequency',frequency/100,elist);
      
      disp(getparamdouble('sx',elist));
      disp(getparamdouble('sy',elist)); 
      disp(getparamdouble('amplitude',elist));
      disp(getparamdouble('frequency',elist));      
   //end
  
endfunction


