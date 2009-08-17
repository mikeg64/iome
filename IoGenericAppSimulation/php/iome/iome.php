<?php



class ioservice {

    var $server, $port, $id, $method;

     //$method=0 default using system call
     //$method=1 using zend developed client plugin
     //$method=2 using nusoap    

}


function stringtovec($stringvar, $vsize, $separator)
{
    $vec=split($separator, $stringvar);
    return $vec;
}

function vectostring($vec, $separator)
{
    for($i=0; $i < $vsize ; $i++)
    {
        if($i == $vsize-1)
        {        
		$vecstring = $temp.$vec[ $i ];
	        $temp=$vecstring;
	}
	else
        {
		$vecstring = $temp.$vec[ $i ].$separator;
	        $temp=$vecstring;
	}
    }   
    return $vecstring;

}

function newvec($vsize)
{   
    for($i=0; $i < $vsize ; $i++)
    {
	$vec[ $i ]=0;
    }   
    return $vec;
}

function newmat($nr,$nc)
{
    for($i=0; $i < $nr ; $i++)
    {
	for($j=0; $j < $nc ; $j++)
    	{
		$mat[$i][$j]=0;
	}
    }   
    return $mat;

}

function vec2mat($vec, $nr,$nc)
{
    $vsize=count($vec);
    $mat = newmat($nr, $nc);
    $vc=0;
    for($i=0; $i < $nr ; $i++)
    {
	for($j=0; $j < $nc ; $j++)
    	{
		$mat[$i][$j]=$vec[$vc];
                $vt=$vc+1;
                $vc=$vt;
                if($vc > $vsize)
                {
			return $mat;
                }
	}
    }   
    return $mat;
}

function mat2vec($mat)
{
    $r = count($mat,0);
    $c = (count($mat,1)/count($mat,0))-1;

    $vsize=$r*$c;
    $vc=0;
    for($i=0; $i < $r ; $i++)
    {
	    for($j=0; $j < $c ; $j++)
	    {
		$vec[ $vc ]=$mat[$i][$j];
                $temp = $vc + 1;
                $vc = $temp;
            }
    }   
    return $vec;
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

function addparamstring( $name, $val , $ioservice)
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


function setparamstring( $name, $val , $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "setparam string ".$name." ".$val." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;	          	
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "ioclient setparam string ".$name." ".$val." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;
				
                $result=system($request);
	}
      return $result;
}

function getparamstring( $name , $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "getparam string ".$name." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "ioclient getparam string ".$name." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}


function runsimulation( $simfile , $outfile, $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "runsimulation string ".$simfile." ".$outfile." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "iogs runsimulation string ".$simfile." ".$outfile." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}

function submitsimulation( $simfile , $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "submitsimulation string ".$simfile." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "iogs submitsimulation string ".$simfile." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}

function requestsimulation( $simfile , $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "requestsimulation string ".$simfile." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "iogs requestsimulation string ".$simfile." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}

function runrequestedsimulation( $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "runrequestedsimulation string ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "iogs requestedsimulation string ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}

function simulationstatus( $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "simulationstatus string ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "iogs simulationstatus string ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}

function setsimulationstatus( $newstatus, $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "setsimulationstatus string ".$newstatus." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "iogs setsimulationstatus string ".$newstatus." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}

function getsimulationresults( $outfile , $ioservice)
{	
      $server='http://'.$ioservice->server.':'.$ioservice->port.'/';

      if ($ioservice->method == 1){
                $request = "getsimulationresults string ".$outfile." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result = iophp($request);
	}
        elseif ($ioservice->method == 0)
	{
                $request = "iogs getsimulationresults string ".$outfile." ".$ioservice->id ." ".$ioservice->port ." ".$ioservice->server ;		
                $result=system($request);
	}
      return $result;
}

?>
