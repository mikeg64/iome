function [consts,domain,source,metadata]=loadsim(simfile,elist)
//add initial wave height as new param
//loads a simulation file and sets the consts and domains
//elist=list();  parameter used by iome to contain port and server address
//ReadSimulation(simfile,elist)
source.sf=GetDoubleParam('frequency',elist);//source frequency
source.sa=GetDoubleParam('amplitude',elist);//source amplitude
source.sx=GetDoubleParam('sx',elist);//source x location
source.sy=GetDoubleParam('sy',elist);//source y location
  
  // Constants
consts.g  =GetDoubleParam('g',elist);
consts.u0 =GetDoubleParam('u0',elist);                               
consts.v0 =GetDoubleParam('v0',elist);
consts.b  =GetDoubleParam('b',elist);                               
consts.h0 =GetDoubleParam('h0',elist); 

//Domain definition
// Define the x domain
//ni = 151; 
domain.ni=GetDoubleParam('ni',elist);
domain.xmax=GetDoubleParam('xmax',elist);                      
dx = domain.xmax/(domain.ni-1);
x  = [0:dx:domain.xmax];

// Define the y domain
//nj = 151;  
domain.nj=GetDoubleParam('nj',elist);
domain.ymax=GetDoubleParam('ymax',elist);                      
dy = ymax/(domain.nj-1);
y  = [0:dy:domain.ymax];
domain.nt=GetIntParam('nt',elist);
domain.tmax=GetDoubleParam('tmax',elist);
domain.step=GetIntParam('step',elist);
domain.steeringenabled=GetIntParam('steeringenabled',elist);
domain.finishsteering=GetIntParam('finishsteering',elist);

metadata.directory=GetMetadata('directory',elist);
metadata.author=GetMetadata('author',elist);
metadata.sdate=GetMetadata('date',elist);
metadata.platform=GetMetadata('platform',elist);
metadata.desc=GetMetadata('description',elist);
metadata.name=GetMetadata('name',elist);

endfunction

function []=createsim(consts, domain,source,metadata,simfile,elist)

//elist=list();  parameter used by iome to contain port and server address
//elist=list();

AddMetadata('author',metadata.author,elist);
AddMetadata('directory',metadata.directory,elist);
AddMetadata('date',metadata.sdate,elist);
AddMetadata('platform',metadata.platform,elist);
AddMetadata('description',metadata.desc,elist);
AddMetadata('name',metadata.name,elist);

AddDoubleParam('frequency',source.sf,7,elist);
AddDoubleParam('amplitude',source.sa,7,elist);
AddDoubleParam('sx',source.sx,7,elist);
AddDoubleParam('sy',source.sy,7,elist);

// Constants
AddDoubleParam('g',consts.g,7,elist);
AddDoubleParam('u0',consts.u0,7,elist);
AddDoubleParam('v0',consts.v0,7,elist);
AddDoubleParam('b',consts.b,7,elist);
AddDoubleParam('h0',consts.h0,7,elist);

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

AddDoubleParam('ni',domain.ni,7,elist);
AddDoubleParam('nj',domain.ni,7,elist);
AddDoubleParam('xmax',domain.xmax,7,elist);
AddDoubleParam('ymax',domain.ymax,7,elist);
AddDoubleParam('tmax',domain.tmax,7,elist);
AddIntParam('nt',domain.nt,7,elist);
AddIntParam('steeringenabled',domain.steeringenabled,7,elist);
AddIntParam('finishsteering',domain.finishsteering,7,elist);
AddIntParam('step',domain.step,7,elist);

statsu=zeros(domain.nt,3);
statsv=zeros(domain.nt,3);
statsh=zeros(domain.nt,3);

AddMatParam('statsu',statsu,7,elist);
AddMatParam('statsv',statsv,7,elist);
AddMatParam('statsh',statsh,7,elist);

AddStringParam('resultsfile','results.zip',7,elist);
//simfile=sprintf('%s.xml',simname)



endfunction

function []=runsim(consts, domain,source, metadata,simname,elist)

//elist=list();  parameter used by iome to contain port and server address
//elist=list(); 

sf=source.sf;//source frequency
sa=source.sa;//source amplitude
sx=source.sx;//source x location
sy=source.sy;//source y location

// Constants
g  = consts.g;
u0 = consts.u0;                               
v0 = consts.v0;
b  = consts.b;                               
h0 = consts.h0; 

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
steeringenabled=domain.steeringenabled;
finishsteering=domain.finishsteering;


// Define the wavespeed
wavespeed = u0 + sqrt(g*(h0 - b));

// Define time-domain
dt = 0.68*dx/wavespeed;

//t = [0:dt:tdomain];
t=[1:dt:tmax];
domain.nt=length(t);
nt=domain.nt;
courant = wavespeed*dt/dx;

// Build empty u, v, b matrices
u=zeros(length(x), length(y), 2);
v=zeros(length(x), length(y), 2);
b=zeros(length(x), length(y));

// Define h
h=zeros(length(x), length(y), 2); 
h(:,:,1) = 5000;                              
h((45000/100000*(length(x)-1)+1):floor(55000/100000*(length(x)-1)+1),(45000/100000*(length(y)-1)+1):floor(55000/100000*(length(y)-1)+1),1) = 5030;

//Define b
for i = 1:length(x)
    if x(i) > 20001
        b(:,i) = 0;
    elseif x(i) < 20000
        b(:,i) = 5000/20000*(20000-x(i));
    end
end

//For a steerable simulation generate and save a dxformfile that saves a single data step
//used for the steering dx module

//sdir=GetMetadata('directory',elist);
sdir=metadata.directory

name=metadata.name;
disp(sdir,name)
//name=GetMetadata('name',elist);
outfile=sprintf('%s/%s.out',sdir,name);
fd=mopen(outfile,'w');
if steeringenabled==1
  
  mkdir('tmp');
  gendxgen('tmp',name,1,ni,nj);
end

formfile=sdir+'/'+'form'+name+'.out';
fdform=mopen(formfile,'w');
  mfprintf(fdform, '%d %d %d\n',max(size(t))-1, ni, nj);
mclose(fdform);

statsu=zeros(nt,3);
statsv=zeros(nt,3);
statsh=zeros(nt,3);
// Employ Lax
//disp(length(t));


while finishsteering == 0
 h((45000/100000*(length(x)-1)+1):floor(55000/100000*(length(x)-1)+1),(45000/100000*(length(y)-1)+1):floor(55000/100000*(length(y)-1)+1),1) = 5030;
 
    if steeringenabled==0
      finishsteering=1;
    end
for n=1:(length(t)-1)
  //disp('step n');
  //disp(n);

   //disp('n');
   //disp(n);
   
    for i=2:(ni-1)
        for j=2:(nj-1)    
            u(i,j,2) = ((u(i+1,j,1) + u(i-1,j,1) + u(i,j+1,1) + u(i,j-1,1))/4)...
                - 0.5*(dt/dx)*((u(i+1,j,1)^2)/2 - (u(i-1,j,1)^2)/2)...
                - 0.5*(dt/dy)*(v(i,j,1))*(u(i,j+1,1) - u(i,j-1,1)) - 0.5*g*(dt/dx)*(h(i+1,j,1)-h(i-1,j,1));
            
            v(i,j,2) = ((v(i+1,j,1) + v(i-1,j,1) + v(i,j+1,1) + v(i,j-1,1))/4)...
                - 0.5*(dt/dy)*((v(i,j+1,1)^2)/2 - (v(i,j+1,1)^2)/2)...
                - 0.5*(dt/dx)*(u(i,j,1))*(v(i+1,j,1) - v(i-1,j,1)) - 0.5*g*(dt/dy)*(h(i,j+1,1)-h(i,j-1,1));
            
            if i==sx & j==sy then
                   h(i,j,2) = ((h(i+1,j,1) + h(i-1,j,1) + h(i,j+1,1) + h(i,j-1,1))/4)...
                  - 0.5*(dt/dx)*(u(i,j,1))*((h(i+1,j,1)-b(i+1,j)) - (h(i-1,j,1)-b(i-1,j)))...
                  - 0.5*(dt/dy)*(v(i,j,1))*((h(i,j+1,1)-b(i,j+1)) - (h(i,j-1,1)-b(i,j-1)))...
                  - 0.5*(dt/dx)*(h(i,j,1)-b(i,j))*(u(i+1,j,1)- u(i-1,j,1))...
                  - 0.5*(dt/dy)*(h(i,j,1)-b(i,j))*(v(i,j+1,1) - v(i,j-1,1));

            else
              h(i,j,2) = sa*sin(n*sf)+((h(i+1,j,1) + h(i-1,j,1) + h(i,j+1,1) + h(i,j-1,1))/4)...
                  - 0.5*(dt/dx)*(u(i,j,1))*((h(i+1,j,1)-b(i+1,j)) - (h(i-1,j,1)-b(i-1,j)))...
                  - 0.5*(dt/dy)*(v(i,j,1))*((h(i,j+1,1)-b(i,j+1)) - (h(i,j-1,1)-b(i,j-1)))...
                  - 0.5*(dt/dx)*(h(i,j,1)-b(i,j))*(u(i+1,j,1)- u(i-1,j,1))...
                  - 0.5*(dt/dy)*(h(i,j,1)-b(i,j))*(v(i,j+1,1) - v(i,j-1,1));
            end
                


        end
    end

    // Define Boundary Conditions
    u(1,:,2) = 2.5*u(2,:,2) - 2*u(3,:,2) + 0.5*u(4,:,2);
    u(length(x),:,2) = 2.5*u(ni-1,:,2) - 2*u(ni-2,:,2) + 0.5*u(ni-3,:,2);
    u(:,1,2) = 2.5*u(:,2,2) - 2*u(:,3,2) + 0.5*u(:,4,2);
    u(:,length(y),2) = 2.5*u(:,nj-1,2) - 2*u(:,nj-2,2) + 0.5*u(:,nj-3,2);

    v(1,:,2) = 2.5*v(2,:,2) - 2*v(3,:,2) + 0.5*v(4,:,2);
    v(length(x),:,2) = 2.5*v(ni-1,:,2) - 2*v(ni-2,:,2) + 0.5*v(ni-3,:,2);
    v(:,1,2) = 2.5*v(:,2,2) - 2*v(:,3,2) + 0.5*v(:,4,2);
    v(:,length(y),2) = 2.5*v(:,nj-1,2) - 2*v(:,nj-2,2) + 0.5*v(:,nj-3,2);

    h(1,:,2) = 2.5*h(2,:,2) - 2*h(3,:,2) + 0.5*h(4,:,2);
    h(length(x),:,2) = 2.5*h(ni-1,:,2) - 2*h(ni-2,:,2) + 0.5*h(ni-3,:,2);
    h(:,1,2) = 2.5*h(:,2,2) - 2*h(:,3,2) + 0.5*h(:,4,2);
    h(:,length(y),2) = 2.5*h(:,nj-1,2) - 2*h(:,nj-2,2) + 0.5*h(:,nj-3,2);
    
    h(:,:,1)=h(:,:,2);
    u(:,:,1)=u(:,:,2);
    v(:,:,1)=v(:,:,2);
    
    //calculate max
    statsu(n,1)=max(u(:,:,1));
    statsv(n,1)=max(v(:,:,1));
    statsh(n,1)=max(h(:,:,1));

    //calculate min
    statsu(n,2)=min(u(:,:,1));
    statsv(n,2)=min(v(:,:,1));
    statsh(n,2)=min(h(:,:,1));

    //calculate mean
    t1=mean(u(:,:,1),'r');
    statsu(n,3)=mean(t1,'c');
    t1=mean(v(:,:,1),'r');
    statsv(n,3)=mean(t1,'c');
    t1=mean(h(:,:,1),'r');
    statsh(n,3)=mean(t1,'c');
    
    //disp('computing stats');
    
    //set the params
    //SetMatParam('statsu',statsu,nt,3,elist)
    //SetMatParam('statsv',statsu,nt,3,elist)
    //SetMatParam('statsh',statsu,nt,3,elist)
    SetIntParam('step',n,elist);
    
    if steeringenabled==1
      //disp('getting updatea params');
      //for steering get the modified control params
      sf=GetDoubleParam('frequency',elist);//source frequency
      sa=GetDoubleParam('amplitude',elist);//source amplitude
      sx=GetDoubleParam('sx',elist);//source x location
      sy=GetDoubleParam('sy',elist);//source y location
      finishsteering=GetIntParam('finishsteering',elist);//source y location  
        // Constants
      g  =GetDoubleParam('g',elist);
    
    
      //save file containing current data
      configfile=sprintf('tmp/%ss%d.out',name,n);
      fdt=mopen(configfile,'w');
      mfprintf(fdt,'%f\n',n);
      for i1=1:ni
        for j1=1:ni
          mfprintf(fdt,'%f %f %f',u(i1,j1,1),v(i1,j1,1),h(i1,j1,1));
        end
        mfprintf(fdt,'\n')
      end
      mclose(fdt);
    
    
    end
  
    //disp('writing data');
    //if finishsteering==1
      mfprintf(fd,'%f\n',n);
      for i1=1:ni
        for j1=1:nj
          mfprintf(fd,'%f %f %f',u(i1,j1,1),v(i1,j1,1),h(i1,j1,1));
        end
        mfprintf(fd,'\n')
      end
    //end
    
    //disp('written data');
end

  // force the final ouput file to be over written
  if steeringenabled==1
    if finishsteering==0
      mclose(fd);
      fd=mopen(outfile,'w');
    end
  end
//disp('while finsish steering');
end //while finishsteering loop

disp('finalising');
SetMatParam('statsu',statsu,elist);
SetMatParam('statsv',statsu,elist);
SetMatParam('statsh',statsu,elist);
disp('finished');
//for the completed simulation
nsteps=length(t);
mclose(fd);


gendxgen(sdir,name,length(t),ni,nj);

//remove the files in the tmp directory
//the files that were used for steering
//rmdir('tmp','s')
//save simualtion state parameters summarising results from simulation


//use the iosetparam operations to set the results parameters

//generate a surface plot

//run the dx visualisation




  
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
    mfprintf(fdform, 'field = field0, field1 \n structure = 2-vector, scalar \n type = float, float  \n dependency = positions, positions  \n positions = regular,regular, 0, 1,0,1 \n end \n ');
  mclose(fdform);


 basedxgenfile='dx/base'+jobname+'.general';

  fdbform=mopen(basedxgenfile,'w');
   // mfprintf(fdbform, 'file=%s\n', directory+'/'+jobname+'.out');
    mfprintf(fdbform,'grid %d X %d\n',n1,n2);
    mfprintf(fdbform,'format = ascii \n interleaving = field \n majority = row \n header = lines 1 \n');
    mfprintf(fdbform, 'series =  1  , 1, 1, separator=lines 1\n');
    mfprintf(fdbform, 'field = field0, field1 \n structure = 2-vector, scalar \n type = float, float  \n dependency = positions, positions  \n positions = regular,regular, 0, 1,0,1 \n end \n ');
  mclose(fdbform);



endfunction

