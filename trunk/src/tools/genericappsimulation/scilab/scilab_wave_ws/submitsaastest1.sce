//this is the standalone version  for submitting work to a saas

tdp=getenv('SCILAB_HOME')+'/share/scilab/contrib/iome_toolbox/loader.sce';
exec(tdp);

//this application is started using the io  start scilab application
exec('paramssaastest1.sce');
//stacksize('max');
//stacksize(268435454);
elistremote=iome('localhost',8080,0);

simfile=metadata.name+'.xml';
simfileout=metadata.name+'_out.xml';
newsimulation(metadata.name,'test1.xsl',elist);
createsim(param1,params2,metadata,elist);

//[consts,domain,source]=loadsim('test1_16_02_09.xml',elist);
//chdir(metadata.directory);
writesimulation(simfile,elist);
//runsim(consts,domain,source,metadata,simfile,elist);

submitsimulation(simfile,elistremote);

//WriteSimulation(simfile,elist);
//chdir('..');
//exit();
