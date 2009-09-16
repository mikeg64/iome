Distributed Data Explorer
start server on local machine
./dxwebservice2  dxnetfile.net port numberofclients

start client on remote machine
.dxwebclient2 dxnetfile.net username serveraddress clientnumber[0] port[8080]

ssh -Y -Rport:clientaddress:port clientuser@clientaddress
/home1/cs/cs1mkg/bin/dxwebclient2
/home1/cs/cs1mkg/proj/visual/dev/dxwebclient2/clientdxnetfile.net username
serveraddress clientnumber[0] port[8080]




ssh -Y cs1mkg@suilven.shef.ac.uk 'cd proj/workingdirectory , ./dxapp'
Develop execution driver using java cog 4 toolkit

1. ddx file  format

most probably same client file for each client

<ddxfile>
	<server address="ip or identifier" port="portnumber"/>

	<clients>
		<dxnet id="0" file="file0.net" node="suilven.shef.ac.uk" directory="">
			<inputs>  </inputs>
			<outputs> </outputs>
		</dxnet>		
		<dxnet id="1" file="file1.net" node="iceberg.shef.ac.uk" directory="">
			<inputs>  </inputs>
			<outputs> </outputs>
		</dxnet>
		....
		....
		....
	</clients>
</ddxfile>


2. scp, gsiscp scripts to nodes
start client on each node using gsissh, ssh

Invoke clients from the server host

Start server on localhost 

     dxserver myjobserver.net inoutfile &

specify server address for
 
 ssh -Y -R port:serveraddress:port cs1mkg@iceberg.shef.ac.uk `cd proj/data ; dxclient myjob.net inoutfile`
 




