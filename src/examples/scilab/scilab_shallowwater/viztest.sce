  
  curFig             = scf(100001);
clf(curFig,"reset");
//demo_viewCode("anim5.sce");

drawlater();

xselect(); //raise the graphic window


// set a new colormap
//-------------------
cmap= curFig.color_map; //preserve old setting
curFig.color_map = jetcolormap(64);
ni=51;
nj=51;
mval=5000*ones(ni,nj)/10; 
 //Creates and set graphical entities which represent the surface
//--------------------------------------------------------------
plot3d1(1:ni,1:nj,mval,55,10,' ');
s=gce(); //the handle on the surface
s.color_flag=1 ; //assign facet color according to Z value
title("Shallow Water Wave","fontsize",3)

I=20:-1:1;
realtimeinit(0.1);;//set time step (0.1 seconds)  and date reference


drawnow(); 
  
  
  
  
  
  nsteps=32;
  name='tsteer1';
  
  
  for i=1:32
   realtime(1.0); //wait till date 0.1*i seconds
   //sleep(1000);
  
  //scommand=sprintf("cp %s tempr\n",outfile);
  configfile=sprintf('out/%ss%d.mat',name,i);
    try
       loadmatfile(configfile);
       mval=z;
       s.data.z = mval/10;
       //clear(z);
    catch
     disp('h matrix read error!')
    end


  end //end of cycling over steps
