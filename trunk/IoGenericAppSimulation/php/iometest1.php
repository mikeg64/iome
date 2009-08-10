<html>
 <head>
  <title>IOME PHP Test</title>
 </head>
 <body>
 <?php echo '<p>This is the IOME test.</p>'; ?> 
<?php
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

<form action="<?php echo $PHP_SELF; ?>" method="post">
Enter your name: <input type="text" name="name" />
<input type="submit">
</form>

 </body>
</html>
