<?php

// necessary classes
require_once('class.soapclient.php');
require_once('class.soap_val.php');
require_once('class.soap_parser.php');
require_once('class.soap_fault.php');

// transport classes
require_once('class.soap_transport_http.php');

// optional add-on classes
require_once('class.xmlschema.php');
require_once('class.wsdl.php');
require_once('nusoap.php');

class ioservice{

    var $server, $port, $id;

}

function submitjob( $simfile , $ioservice)
{
	//result is jobid
      $server='http://'.$ioservice.server.':'.$ioservice.port;
      $client = new soapclient($server);
	// Call the SOAP method
      $params = array( 'simfilecontent' => $simfile );

	/*$params = array(
	'simfilecontent' => $simfile,
	'queryStr'=>'robotics',
	'startFrom'=>0
	);*/

	$result = $client->call('submitsimulation', $params));
      return $result;
}


function setparamdouble( $name, $val , $ioservice)
{
	//result is jobid
      $server='http://'.$ioservice.server.':'.$ioservice.port;
      $client = new soapclient($server);
	// Call the SOAP method
      $params = array(  'id' => $ioservice.id,
				'name' => $name,
                        'value' => $val
                      );

	/*$params = array(
	'simfilecontent' => $simfile,
	'queryStr'=>'robotics',
	'startFrom'=>0
	);*/

	$result = $client->call('setparamdouble', $params));
      return $result;
}

function getparamdouble( $name , $ioservice)
{
	//result is jobid
      $server='http://'.$ioservice.server.':'.$ioservice.port;
      $client = new soapclient($server);
	// Call the SOAP method
      $params = array(  'id' => $ioservice.id,
				'name' => $name,
                      );

	/*$params = array(
	'simfilecontent' => $simfile,
	'queryStr'=>'robotics',
	'startFrom'=>0
	);*/

	$result = $client->call('getparamdouble', $params));
      return $result;
}



?>
