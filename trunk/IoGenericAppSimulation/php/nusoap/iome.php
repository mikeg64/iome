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

    var $server, $port, $id, $method;

    //$method=0 default using system call
    //$method=1 using nusoap
    //$method=2 using zend developed client plugin
    

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

      if ($ioservice->method == 1){
      $client = new nusoap_client($server);
      
	echo "from setparam server is: {$ioservice->server} and port is {$ioservice->port}.";
	echo "request is: {$name} val is {$val}";
      
      $id=$ioservice->id;
	// Call the SOAP method
      $params = array(  'id' => (int)$id,
			'name' => $name,
                        'value' => (float)$val
                      );
	$result = $client->call('setparamdouble', $params);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "iogs setparam double ".$name." ".$val." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
		//$result=system('iogs getparam double d1');
		$result=system($request);
		echo "$request set param";
	}
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
