<html>
 <head>
  <title>IOGA PHP Test</title>
 </head>
 <body>


<?php echo '<p>This is the IOGA test.</p>';  


//phpinfo();

echo $_SERVER['HTTP_USER_AGENT'];
?>

<?php
if (strpos($_SERVER['HTTP_USER_AGENT'], 'Mozilla') !== FALSE) {
    echo 'You are using Mozilla.<br />';
}
?>

<form enctype="multipart/form-data"
      action="submitiogajob.php"
      method="post">
      <p><b>Email: <b> <br />
      <input name="useremail" type="text"></p>
      <p><b>Population Number: <b> <br />
      <input name="populationnumber" type="text" value="30"></p>
      <p><b>Generation Number: <b> <br />
      <input name="generationnumber" type="text" value="50"></p>
      <p><b>Crossover Probability: <b> <br />
      <input name="crossoverprobability" type="text" value="0.9"></p>
      <p><b>Mutation Probability: <b> <br />
      <input name="mutationprobability" type="text" value="0.6"></p>
      <p><b>Equation: <b> <br />
      <input name="equation" type="text" value="y=n+sum(x.^2-cos(2*pi*x));"></p>
      <p><b>Parameter Number: <b> <br />
      <input name="parameternumber" type="text" value="2"></p>


	<br>
 
      <input value="Submit Job" type="submit"></p>
</form>


 </body>
</html>
