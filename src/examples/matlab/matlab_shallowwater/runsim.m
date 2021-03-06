
function []=runsim(consts, domain,source, metadata,simname,elist)

%elist=list();  parameter used by iome to contain port and server address
%elist=list(); 

sf=source.sf;%source frequency
sa=source.sa;%source amplitude
sx=source.sx;%source x location
sy=source.sy;%source y location

% Constants
g  = consts.g;
u0 = consts.u0;                               
v0 = consts.v0;
b  = consts.b;                               
h0 = consts.h0; 

%Domain definition
% Define the x domain
%ni = 151; 
ni=domain.ni;
xmax = domain.xmax;                      
dx = xmax/(ni-1);
x  = [0:dx:xmax];

% Define the y domain
%nj = 151;  
nj=domain.nj;
ymax = domain.ymax;                      
dy = ymax/(nj-1);
y  = [0:dy:ymax];


tmax = domain.tmax;
steeringenabled=domain.steeringenabled;
finishsteering=domain.finishsteering;


% Define the wavespeed
wavespeed = u0 + sqrt(g*(h0 - b));

% Define time-domain
dt = 0.68*dx/wavespeed;

%t = [0:dt:tdomain];
t=[1:dt:tmax];
domain.nt=length(t);
nt=domain.nt;
courant = wavespeed*dt/dx;

                             
%h((45000/100000*(length(x)-1)+1):floor(55000/100000*(length(x)-1)+1),(45000/100000*(length(y)-1)+1):floor(55000/100000*(length(y)-1)+1),1) = 5030;



%For a steerable simulation generate and save a dxformfile that saves a single data step
%used for the steering dx module

sdir=getmetadata('directory',elist);
%sdir=metadata.directory

%name=metadata.name;

name=getmetadata('name',elist);
%disp(sdir,name)

outfile=sprintf('%s/%s.out',sdir,name);
fd=fopen(outfile,'w');
if steeringenabled==1
  mkdir('tmp');
  gendxgen('tmp',name,1,ni,nj);
end

formfile=[sdir '/' 'form' name '.out'];
%formfile=sdir+'/'+'form'+name+'.out';
fdform=fopen(formfile,'w');
  fprintf(fdform, '%d %d %d\n',max(size(t))-1, ni, nj);
fclose(fdform);


% Employ Lax
%disp(length(t));

display(finishsteering);
while (finishsteering ~= 1)
    
% Build empty u, v, b matrices
u=zeros(length(x), length(y), 2);
v=zeros(length(x), length(y), 2);
b=zeros(length(x), length(y));

% Define h
h=zeros(length(x), length(y), 2); 
h(:,:,1) = 5000;     
%Define b
for i = 1:length(x)
    if x(i) > 20001
        b(:,i) = 0;
    elseif x(i) < 20000
        b(:,i) = 5000/20000*(20000-x(i));
    end
end    
    
 %h((45000/100000*(length(x)-1)+1):floor(55000/100000*(length(x)-1)+1),(45000/100000*(length(y)-1)+1):floor(55000/100000*(length(y)-1)+1),1) = 5030;
nli = int32((sx-sf)*(ni-1)+1);
 nui = int32((sx+sf)*(ni-1)+1);
 nlj = int32((sy-sf)*(nj-1)+1);
 nuj = int32((sy+sf)*(nj-1)+1);
 h(nli:nui,nlj:nuj,1) = 5000+sa; 
    
for n=1:(length(t)-1)
  %disp('step n');
  %disp(n);

   %disp('n');
   %disp(n);
   
    for i=2:(ni-1)
        for j=2:(nj-1)    
            u(i,j,2) = ((u(i+1,j,1) + u(i-1,j,1) + u(i,j+1,1) + u(i,j-1,1))/4)...
                - 0.5*(dt/dx)*((u(i+1,j,1)^2)/2 - (u(i-1,j,1)^2)/2)...
                - 0.5*(dt/dy)*(v(i,j,1))*(u(i,j+1,1) - u(i,j-1,1)) - 0.5*g*(dt/dx)*(h(i+1,j,1)-h(i-1,j,1));
            
            v(i,j,2) = ((v(i+1,j,1) + v(i-1,j,1) + v(i,j+1,1) + v(i,j-1,1))/4)...
                - 0.5*(dt/dy)*((v(i,j+1,1)^2)/2 - (v(i,j+1,1)^2)/2)...
                - 0.5*(dt/dx)*(u(i,j,1))*(v(i+1,j,1) - v(i-1,j,1)) - 0.5*g*(dt/dy)*(h(i,j+1,1)-h(i,j-1,1));
            
            
            h(i,j,2) = ((h(i+1,j,1) + h(i-1,j,1) + h(i,j+1,1) + h(i,j-1,1))/4)...
                  - 0.5*(dt/dx)*(u(i,j,1))*((h(i+1,j,1)-b(i+1,j)) - (h(i-1,j,1)-b(i-1,j)))...
                  - 0.5*(dt/dy)*(v(i,j,1))*((h(i,j+1,1)-b(i,j+1)) - (h(i,j-1,1)-b(i,j-1)))...
                  - 0.5*(dt/dx)*(h(i,j,1)-b(i,j))*(u(i+1,j,1)- u(i-1,j,1))...
                  - 0.5*(dt/dy)*(h(i,j,1)-b(i,j))*(v(i,j+1,1) - v(i,j-1,1));

            
                


        end
    end

    % Define Boundary Conditions
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
    
    
    
    %disp('computing stats');
    
    %set the params
    %setparammat('statsu',statsu,nt,3,elist)
    %setparammat('statsv',statsu,nt,3,elist)
    %setparammat('statsh',statsu,nt,3,elist)
    
    
    
      %save file containing current data
      configfile=['tmp\' name 's' num2str(n) '.out'];
      fdt=fopen('tempo','w');
      fprintf(fdt,'%f\n',n);
      for i1=1:ni
        for j1=1:ni
          fprintf(fdt,' %f %f %f ',u(i1,j1,1),v(i1,j1,1),h(i1,j1,1));
        end
        fprintf(fdt,'\n');
      end
      fclose(fdt);
      %scommand=sprintf('cp temp %s\n',configfile);
      scommand=['copy tempo ' configfile];
      system(scommand);
      setparamint('step',n,elist);
  
  
    %disp('writing data');
    if finishsteering > 0
      fprintf(fd,'%f\n',n);
      for i1=1:ni
        for j1=1:nj
          fprintf(fd,' %f %f %f ',u(i1,j1,1),v(i1,j1,1),h(i1,j1,1));
        end
        fprintf(fd,'\n');
      end
    end
    
    %disp('written data');
end

  % force the final ouput file to be over written
  


%disp('while finsish steering');
steeringenabled=getparamint('steeringenabled',elist)
if steeringenabled>0
      %disp('getting updatea params');
      %for steering get the modified control params
      sf=str2num(getparamdouble('frequency',elist));%source frequency
      sa=str2num(getparamdouble('amplitude',elist));%source amplitude
      sx=str2num(getparamdouble('sx',elist));%source x location
      sy=str2num(getparamdouble('sy',elist));%source y location        
end
finishsteering=getparamint('finishsteering',elist);



end %while finishsteering loop


disp('finished');
%for the completed simulation
nsteps=length(t);
fclose(fd);


gendxgen(sdir,name,length(t),ni,nj);

%remove the files in the tmp directory
%the files that were used for steering
%rmdir('tmp','s')
%save simualtion state parameters summarising results from simulation


%use the iosetparam operations to set the results parameters

%generate a surface plot

%run the dx visualisation




