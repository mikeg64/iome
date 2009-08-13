<?php


include_once('nusoap.php');


class ioservice {

    var $server, $port, $id, $method;

    //$method=0 default using system call
    //$method=1 using nusoap
    //$method=2 using zend developed client plugin
    

}





function setparamdouble( $name, $val , $ioservice)
{

	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      //$client = new nusoap_client($server);

	
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
		//$result=system('ls');
                $result=system($request);
		echo "$request set param";
	}
      return $result;

}




?>
