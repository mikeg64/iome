<html>
 <head>
  <title>IOME PHP Test</title>
 </head>
 <body>
 <?php echo '<p>This is the IOME test.</p>'; ?> 
<?php
require_once('iome.php');




echo $_SERVER['HTTP_USER_AGENT'];
?>

<?php
if (strpos($_SERVER['HTTP_USER_AGENT'], 'Mozilla') !== FALSE) {
    echo 'You are using Mozilla.<br />';
}
?>

<?php if(!empty($_POST['name'])){
 echo "Greetings, {$_POST['name']}, and welcome.";
}
?>


<?php if(!empty($_POST['floatval'])){
 echo "Float val, {$_POST['floatval']}.";
 setparamdouble('d1',$_POST['floatval'],$myioservice);
}
?>

<?php 
   
   $myioservice = new ioservice;
   $myioservice->server = 'localhost';
   $myioservice->port = '8080';
   $myioservice->id = '0';


   

   if((!empty($_POST['server'])) and (!empty($_POST['port'])) ){
   $myioservice->server = $_POST['server'];
   $myioservice->port = $_POST['port'];

   echo "server is, {$myioservice->server}, and port is {$myioservice->port}.";
   //echo "server is, {$_POST['server']}, and port is {$_POST['port']}.";
   // $myioservice=new ioservice('localhost','8080','0');

}
?>


<form action="<?php echo $PHP_SELF; ?>" method="post">
Enter float value: <input type="text" name="floatval" />
<input type="submit">
</form>


<form action="<?php echo $PHP_SELF; ?>" method="post">
Enter your name: <input type="text" name="name" />
<input type="submit">
</form>

<form action="<?php echo $PHP_SELF; ?>" method="post">
Enter server: <input type="text" name="server" />
Enter port: <input type="text" name="port" />
<input type="submit">
</form>
 </body>
</html>
