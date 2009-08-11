<?php

// necessary classes
//require_once('class.soapclient.php');
//require_once('class.soap_val.php');
//require_once('class.soap_parser.php');
//require_once('class.soap_fault.php');

// transport classes
//require_once('class.soap_transport_http.php');

// optional add-on classes
//require_once('class.xmlschema.php');
//require_once('class.wsdl.php');
include_once('nusoap.php');

class ioservice {

    var $server, $port, $id;

    //function ioservice( $iserver, $iport, $iid )
	//{
	//	$this->$server=$iserver;
	//	$this->$port=$iport;
	//	$this->$id=$iid;
	//}

}

function submitjob( $simfile , $ioservice)
{
	//result is jobid
     // $server='http://'.$ioservice->server.':'.$ioservice->port.'/IoSteerWS.wsdl';
//$wsdl="http://www.xmethods.net/sd/2001/CurrencyExchangeService.wsdl";
	//$client=new soapclient($server, 'wsdl');

      //$client = new soapclient($server);
	// Call the SOAP method
      $params = array( 'simfilecontent' => $simfile );

	/*$params = array(
	'simfilecontent' => $simfile,
	'queryStr'=>'robotics',
	'startFrom'=>0
	);*/

	//$result = $client->call('submitsimulation', $params);
      return $result;
}


function setparamdouble( $name, $val , $ioservice)
{
	
//result is jobid
      $server='http://'.$ioservice->server.':'.$ioservice->port;
//$wsdl="http://www.xmethods.net/sd/2001/CurrencyExchangeService.wsdl";
	//$client=new soapClient('http://localhost:8080/IoSteerWS.wsdl');
      $wsdl= new wsdl('IoSteerWS.wsdl');
      //echo "wsdl $wsdl";
 
      $client = new nusoap_client($server);
      //$client->wsdl = $wsdl;
	echo "from setparam server is: {$ioservice->server} and port is {$ioservice->port}.";
	echo "request is: {$name} val is {$val}";
      //$client = new soapclient($server);
      //$client->$endpointType='soap';
	//$client->$forceEndpoint=$server;
      $id=$ioservice->id;
	// Call the SOAP method
      $params = array(  'id' => (int)$id,
			'name' => $name,
                        'value' => (float)$val
                      );



	$result = $client->call('setparamdouble', $params);
      return $result;
}

function getparamdouble( $name , $ioservice)
{
	//result is jobid
      $server='http://'.$ioservice.server.':'.$ioservice.port;
      //$client = new soapclient($server);
	// Call the SOAP method
      $params = array(  'id' => $ioservice.id,
				'name' => $name,
                      );

	/*$params = array(
	'simfilecontent' => $simfile,
	'queryStr'=>'robotics',
	'startFrom'=>0
	);*/

	//$result = $client->call('getparamdouble', $params);
      return $result;
}



?>
