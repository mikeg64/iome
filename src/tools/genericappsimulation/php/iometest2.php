<html>
 <head>
  <title>IOME PHP Test</title>
 </head>
 <body>


 <?php echo '<p>This is the IOME test.</p>'; ?> 
<?php

phpinfo();
require_once('iome/iome.php');
?>


<?php 
   
   $myioservice = new ioservice;
   $myioservice->server = 'suilven.shef.ac.uk';
   $myioservice->port = '60000';
   $myioservice->id = 0;
   $myioservice->method = 2;
	

 	if(!empty($_POST['floatval'])){
 	echo "Float val, {$_POST['floatval']}";
        
 	setparamdouble('d1',(float)$_POST['floatval'],$myioservice);
        echo "result is $result";
	}  

   if((!empty($_POST['server'])) and (!empty($_POST['port'])) ){
   $myioservice->server = $_POST['server'];
   $myioservice->port = $_POST['port'];

   echo "server is, {$myioservice->server}, and port is {$myioservice->port}.";
  
}
?>



<form action="<?php echo $PHP_SELF; ?>" method="post">
Enter float value: <input type="text" name="floatval" />
<input type="submit">
</form>


<form action="<?php echo $PHP_SELF; ?>" method="post">
Enter server: <input type="text" name="server" />
Enter port: <input type="text" name="port" />
<input type="submit">
</form>
 </body>
</html>
