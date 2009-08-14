<html>
 <head>
  <title>IOME PHP Test</title>
 </head>
 <body>


<?php echo '<p>This is the IOME test.</p>';  


//phpinfo();
require_once('iome/iome.php');


echo $_SERVER['HTTP_USER_AGENT'];
?>




<?php
if (strpos($_SERVER['HTTP_USER_AGENT'], 'Mozilla') !== FALSE) {
    echo 'You are using Mozilla.<br />';
}
?>






<?php 
   
   /*The following lines read the job template xml file*/
   /*The %items%  in the jobfile content are replaced with
   the variable parameters*/
   /*we use the str_replace function to acheive this*/
   /*str_replace — Replace all occurrences of the search string with the replacement string*/
   /*$jobfile = file_get_contents  ( "jobfile.xml");*/
   $myioservice = new ioservice;
   //$myioservice->server = 'localhost';
   //$myioservice->port = '8080';
   $myioservice->id = 0;
   $myioservice->method = 1;
   //$name = 'd1';
   //$ioaction = 'setparam';

   //$val = '27.0';

	if(!empty($_POST['name'])){
 	//echo "Name is, {$_POST['name']}.";
        $name = $_POST['name'];
	}

	if(!empty($_POST['iodoaction'])){
 	
		$ioaction = $_POST['ioaction'];
 		if( strcmp($ioaction , 'setparam') == 0 ){

		$result=(string)setparamdouble($name,(float)$_POST['floatval'],$myioservice);
	        
		}
		elseif( strcmp($ioaction , 'getparam') == 0 ){
		$result=(string)getparamdouble($name,$myioservice);
	        echo "get result is $result ";

		}
		elseif( strcmp($ioaction , 'addparam') == 0 ){
			$result=(string)addparamdouble($name,(float)$_POST['floatval'],$myioservice);
		        

		}        
	}

	if(!empty($_POST['ioaction'])){ 	
        $ioaction = $_POST['ioaction'];
	//echo "newioaction is, $ioaction .";
	}

 	if(!empty($_POST['floatval'])){
 	//echo "Float val, {$_POST['floatval']}";
        $val = $_POST['floatval'];
 	//$result=(string)setparamdouble($name,(float)$_POST['floatval'],$myioservice);
        //echo "val is $val";
	}  

   if((!empty($_POST['server'])) and (!empty($_POST['port'])) ){
   $myioservice->server = $_POST['server'];
   $myioservice->port = $_POST['port'];

   echo "server is, {$myioservice->server}, and port is {$myioservice->port}.";
  

}
?>



<form action="<?php echo $PHP_SELF; ?>" method="post">
Enter float value: <input type="text" name="floatval" />
Enter name: <input type="text" name="name" /><br>
Add Param: 
<input type="radio"
name="ioaction" value="addparam">
<br>
Set Param: 
<input type="radio" name="ioaction" value="setparam">
<br>
Get Param:
<input type="radio" name="ioaction" value="getparam">
<br>
Click checkbox to make the actual request:
<input type="checkbox" 
name="iodoaction" value="doaction">
<br>
<input type="submit">
</form>




<form action="<?php echo $PHP_SELF; ?>" method="post">
Enter server: <input type="text" name="server" />
Enter port: <input type="text" name="port" />
<input type="submit">
<br>



</form>
 </body>
</html>
