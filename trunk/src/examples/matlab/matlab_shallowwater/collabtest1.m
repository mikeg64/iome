
portfile=metadata.name+'0_port.txt';
fd=mopen(portfile,'r');
portid=mfscanf(fd,'%d')
mclose(fd);
elist(2)=portid;
%elist(2)=portid;

simfile=metadata.name+'.xml';
%NewSimulation(metadata.name,'null',elist);
createcollabsim(cam,settings,metadata,simfile,elist);

%[cam,settings,metadata]=loadcollabsim('test1_16_02_09.xml',elist);



%WriteSimulation(simfile,elist);
%chdir('..');
%exit();
