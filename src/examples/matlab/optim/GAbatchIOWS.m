%
%------------------------------------------------------
% real valued genetic algorithm 
% for the minimization of the rastrigin function 
% (with dynamic display for the case of 2 parameters)
%
%-----------------------------------------------------
% selection: proportionate with ranking method 
% crossover: blend 
% mutation: non uniform
% 1-elitism
%

%
%---------main program ---------------------
%
disp('real valued GA for minimizing the rastrigin function');
disp('(with dynamic display for 2 parameters)');
%

%--------------------------------------------------------------------------------------------------
%   1   set and open IOME settings
%--------------------------------------------------------------------------------------------------

try
   %tttt1=pwd;disp(tttt1)
   path(path,'../ga')
   %open the file generated
   %portfile = 'ioserverinfo.txt';                            %add comment if  we are not running standalone
   %portfile = 'ioserverinfo.txt';                      %remove comment if  we are not running standalone
   portfile                = 'mysim0_port.txt';
   fd                      = fopen(portfile);
   %res = mfscanf(fd,'%d %d %s')
   res                     = textscan(fd,'%d %s');
   fclose(fd);
   %port                   = res(1) id = res(2) hostname = res(3)
   %elist                  = iome(res(3),res(1),res(2));
   elist                   = iome('localhost',res{1},0);
   %readsimulation('simfile.xml',elist);

   setpref('Internet','SMTP_Server','mailhost.shef.ac.uk');
   setpref('Internet','E_mail','m.griffiths@sheffield.ac.uk');
   %setpref('Internet','E_mail','c.reyes@sheffield.ac.uk');
   outputCode                          = 'GA';
catch
    outputCode                          = 'E2a';
end

%--------------------------------------------------------------------------------------------------
%   2   get the parameters from the server
%--------------------------------------------------------------------------------------------------

try
    userEmail           = getparamstring('useremail',elist);
    equation           = getparamstring('equation',elist);
    
    n=getparamint('parameter_number',elist);%2;%evstr(x_dialog('parameter number of the rastrigin function','2')); 
    Npop=getparamint('population_number',elist);%30;%evstr(x_dialog('population number','30'));     
    Ngen=getparamint('generation_number',elist);%50;%evstr(x_dialog('generation number','50')); 
    pc=getparamdouble('crossover_probability',elist);%0.9;%evstr(x_dialog('crossover probability','0.9')); 
    pm=getparamdouble('mutation_probability',elist);%0.6;%evstr(x_dialog('mutation probability','0.6'));
    jobref=getparamstring('jobref',elist);
    
    
    outputCode          = 'GA';
    disp(userEmail);
    disp(imageFile);
catch
    outputCode                          = 'E2b';
    display('Failed to get parameters from local iome server');
    exitiome(elist);
    exitiome(elist);
    exit();       
end







xmin=-5.12;xmax=5.12;N=300;
x=xmin:((xmax-xmin)/(N-1)):xmax;
y=x;

%
%n=2;%evstr(x_dialog('parameter number of the rastrigin function','2')); 
%Npop=30;%evstr(x_dialog('population number','30'));     
%Ngen=50;%evstr(x_dialog('generation number','50')); 
%pc=0.9;%evstr(x_dialog('crossover probability','0.9')); 
%pm=0.6;%evstr(x_dialog('mutation probability','0.6')); 
%
xmin=-5.12*ones(1,n);
xmax=5.12*ones(1,n);
Xmin=ones(Npop,1)*xmin;
Xmax=ones(Npop,1)*xmax;
u=rand(Npop,n);
pop=Xmin+(Xmax-Xmin).*u;  % random initialisation of the population
Xpar=[pop,zeros(Npop,1)];  
Xoff=Xpar;Xoldpar=Xpar;fmin=[];mineval=0;newval=zeros(Npop,1);Traj=[];
%
z=zeros(N,N);
for i=1:N
for j=1:N
z(i,j)=rastrigin([x(i),y(j)],n);
end
end
 %
for gen=1:Ngen;
  Xpar=Xoff;
  [Xpar,bestpar,bestnewpop]=evalplus1elitism(Xpar,Xoldpar,Npop,gen,n);  % evaluation plus 1-elitism
  Xoldpar=Xpar;
  fmin=[fmin,bestpar(numel(bestnewpop))];
  %
  Xpar=rankselect(Xpar); % rank selection
  for i=1:2:(Npop-1)
    u1=1+int32((Npop-1)*rand());u2=1+int32((Npop-1)*rand());u3=int32(rand());
    xpar=[Xpar(u1,:);Xpar(u2,:)];
    Xoff(i:(i+1),:)=xpar;
    if (u3<pc)
     xoff=blcross(xpar);   %crossover
     Xoff(i:(i+1),:)=xoff;
    end
    for j=1:2
       u4=rand();
        if (u4<pm)
          xoffl=mutate(xoff(j,:),gen,Ngen,xmin,xmax);  % mutation
          Xoff(i+j-1,:)=xoffl;
        end
    end
   end
Traj=[Traj;bestpar(1),bestpar(2)];
%
end


h1=figure('Visible','off','IntegerHandle','Off');
hold on;
%Need to alter the camer position so
%hget the child property of the figure which are the axes
hax=get(h1,'Children');
%set(hax,'CameraPosition',[-24 -11 5]);
xlabel('x')
ylabel('y')
title('Contour plot of rastrigin function')
colorbar('visible')
contour(x,y,z);
%print the most recent figure to a file
print -djpeg 'gacontour.jpg'
hold off;



%plot(Xpar(:,1),Xpar(:,2));
%plot(Traj(:,1),Traj(:,2));

[Xpar,bestpar,bestnewpop]=evalplus1elitism(Xoff,Xoldpar,Npop,gen,n);  % evaluation plus 1-elitism
fmin=[fmin,bestpar(numel(bestnewpop))];

hax=get(h1,'Children');
plot(0:Npop:(Npop*Ngen),fmin);
xlabel('Generation')
ylabel('fmin')
title('Best Values for Each Generation')
%print the most recent figure to a file
print -djpeg 'gatraj.jpg'
hold off;
%plot(0:Npop:(Npop*Ngen),fmin);

%disp('minimum obtained:');disp(bestpar(1:n));
%disp('corresponding value by f:');disp(bestpar(numel(bestnewpop)));
%disp('evaluation number:');disp(Npop*Ngen);
extradata.resultslocation=['http://wrgrid.group.shef.ac.uk/iogatest/results/',jobref]
extradata.bestpar=bestpar(1:n);
extradata.numelbestnewpop=bestpar(numel(bestnewpop));
extradata.evaluationnumber=Npop*Ngen;

setparamvec('minimum_obtained',bestpar(1:n),length(bestpar(1:n)),elist);
setparamdouble('value_obtained',bestpar(numel(bestnewpop)),elist);
setparamint('evaluation_number',Npop*Ngen,elist);

pc=getparamdouble('crossover_probability',elist);%0.9;%evstr(x_dialog('crossover probability','0.9')); 
pm=getparamdouble('mutation_probability',elist);%0.6;%evstr(x_dialog('mutation probability','0.6'));

writelocalsimulation('simresults.xml',elist);
%email output to user
if(length(userEmail)>0)
 if ~strcmp(outputCode(1),'E')
             %prepare the results only if there were no errors on the way
            %if there is a dataOut, prepare the image to attach, otherwise just send the email
            
              outputMessage       = createOutputMessage(outputCode,extraData);           
              %--------------------------------------------------------------------------------------------------
              % 5 email results to the user
              %--------------------------------------------------------------------------------------------------
              try
                  sendmail(userEmail,'Results from IOGA',outputMessage,{'gatraj.jpg','gacontour.jpg','simresults.xml'});
              catch
                  %getpref('Internet')
                  outputCode                  = 'E1';
                  outputMessage               = createOutputMessage(outputCode);
                  sendmail(userEmail,'Results from IOGA',outputMessage);                
              end
 else
            outputMessage                   = createOutputMessage(outputCode);
            sendmail(userEmail,'Results from IOGA ',outputMessage);    
 end
end






try
   exitiome(elist);
catch
   display('Unable to close IOME'); 
end

try
    exitiome(elist);
catch
    display('iome server closed!');
end

exit();



