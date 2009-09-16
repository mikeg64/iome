//exec('../../IoSetUpGenericScilabSimulation.sce');  //this should be executed by the iome start up application
exec('../../IoGenericScilabSimulation.sce');  //this should be executed by the iome start up application
exec('../ioshallowwater.sce');

//this application is started using the io  start scilab application
exec('../paramssaastest1.sce');
portid=8081;
jobid=2;
//open the file generated
portfile='ioserverinfo.txt';                            //add comment if  we are not running standalone
//portfile='intsaas1_port.txt';                      //remove comment if  we are not running standalone
//portfile=metadata.name+'_port.txt';
fd=mopen(portfile,'r');
res=mfscanf(fd,'%d %d %s')
mclose(fd);

elist(2)=res(1);  //port
//elist(3)=res(2);  //id
elist(3)=0;
elist(1)=res(3);  //hostname

//Add data to logfile
//simfile='mine.xml'
//createsim(consts,domain,source,metadata,simfile,elist);
//WriteSimulation(simfile,elist);

try
  [consts,domain,source]=loadsim('simfile.xml',elist);  //remove comment if we are not running standalone
catch
   disp('failed to load sim');
   exit();
end

mkdir(metadata.directory);
mkdir('dx');

try
  runsim(consts,domain,source,elist);
catch
   disp('failed to run sim');

  exit();
end

//ExitIOME(elist);                                       //remove comment if we are not running standalone

//exit();


