paramssteeringtest1
portfile=[metadata.name '0_port.txt'];
%fd=mopen(portfile,'r');
%portid=mfscanf(fd,'%d')
%mclose(fd);
%elist(2)=portid;


simfile=[metadata.name '.xml'];
%NewSimulation(metadata.name,'test1.xsl',elist);
createsim(consts,domain,source,metadata,simfile,elist);

%[consts,domain,source]=loadsim(simfile,elist);
%chdir(metadata.directory);

runsim(consts,domain,source,metadata,simfile,elist);
%writesimulation(simfile,elist);
%chdir('..');
%exit();
