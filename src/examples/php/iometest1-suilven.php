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

$ios = new ioservice; 
$ios->server = "suilven.shef.ac.uk";
$ios->port = 60000;
$ios->id = 0;
$ios->method = 2;
$client = $ios->client();

print(getparamdouble("d1", $ios)."\n");






if(!empty($_POST['iodoaction'])){


		if(!empty($_POST['name'])){
        			$name = $_POST['name'];
		}

 
		if(!empty($_POST['server'])  ){
		   $theserver = $_POST['server'];
		}
		else {
		   $theserver = 'localhost';
		}

		if(!empty($_POST['port'])  ){
		   $theport = $_POST['port'];
		}
		else {
		   $theport = 8080;
		}
		$themethod = 2;
		$theid = 0;
           
	        $myioservice = new ioservice;
		$myioservice->server = $theserver;
		$myioservice->port = $theport;
		$myioservice->id = $theid;
		$myioservice->method = $themethod;
		$ioaction = $_POST['ioaction'];
                echo "server is, {$theserver}, and port is {$theport}.";
		echo '<br>';
                echo "action is {$ioaction}";
		echo '<br>';	
		
 		if( strcmp($ioaction , 'setparam') == 0 ){

		$result=(string)setparamstring($name,(string)$_POST['floatval'],$myioservice);
	        
		}
		elseif( strcmp($ioaction , 'getparam') == 0 ){
                  
		$result=(string)getparamstring($name,$myioservice);
	        echo "get result is $result ";
		echo '<br>';

		}
		elseif( strcmp($ioaction , 'addparam') == 0 ){
			$result=(string)addparamstring($name,(string)$_POST['floatval'],$myioservice);
		        

		}        
	}  
?>



<form action="<?php echo $PHP_SELF; ?>" method="post">
Enter server: <input type="text" name="server" />
Enter port: <input type="text" name="port" />
<br>
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





 </body>
</html>
