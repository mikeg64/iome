<?php



class ioservice {

    var $server, $port, $id, $method;

     //$method=0 default using system call
     //$method=1 using zend developed client plugin
     //$method=2 using nusoap    

}


function addparamdouble( $name, $val , $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "addparam double ".$name." ".$val." 7 ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;				
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "ioclient addparam double ".$name." ".$val." 7 ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}


function setparamdouble( $name, $val , $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "setparam double ".$name." ".$val." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;	          	
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "ioclient setparam double ".$name." ".$val." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;
				
                $result=system($request);
	}
      return $result;
}

function getparamdouble( $name , $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "getparam double ".$name." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "ioclient getparam double ".$name." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}


?>
