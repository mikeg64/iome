<?php



class ioservice {

    var $server, $port, $id, $method;

     //$method=0 default using system call
     //$method=1 using zend developed client plugin
     //$method=2 using nusoap    

}





function setparamdouble( $name, $val , $ioservice)
{

	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';



      if ($ioservice->method == 1){
                $request = "setparam double ".$name." ".$val." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
		//$result=system('iogs getparam double d1');
		//$result=system('ls');
                $result = `echo iophp($request)`;
		//echo "$request set param and result is $result";
	}
        elseif ($ioservice->method == 0)
	{
                $request = "ioclient setparam double ".$name." ".$val." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
		//$result=system('iogs getparam double d1');
		//$result=system('ls');
                $result=system($request);
		echo "$request set param";
	}
      return $result;

}




?>
