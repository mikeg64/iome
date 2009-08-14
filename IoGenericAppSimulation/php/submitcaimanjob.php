<?php
require_once('iome/iome.php');

$myioservice = new ioservice;
$myioservice->server = 'localhost';
$myioservice->port = '8080';
$myioservice->id = 0;
$myioservice->method = 1;

//need correct write permission on target path
$target_path="/var/www/html/uploads/";
//echo $target_path ;
echo getcwd();
$target_path = $target_path.basename( $_FILES['userfile']['name']); 
//echo $target_path ;
if(move_uploaded_file($_FILES['userfile']['tmp_name'], $target_path)) {
    echo "The file ".  basename( $_FILES['userfile']['name']). 
    " has been uploaded";

	$imagefile = basename( $_FILES['userfile']['name']);
 	if(!empty($_POST['useremail'])){
        $useremail = $_POST['useremail'];

        }
	   /*The following lines read the job template xml file*/
	   /*The %items%  in the jobfile content are replaced with
	   the variable parameters*/
	   /*we use the str_replace function to acheive this*/
	   /*str_replace — Replace all occurrences of the search string with the replacement string*/

	$jobfile = file_get_contents  ( "iocaimanphp.xml");
        $imagecontents = file_get_contents  ( $target_path);
        $tempjobfile = str_replace("%imagefile%", $imagefile, $jobfile);
        $jobfile = str_replace("%useremail%", $useremail, $tempjobfile);

        //submit the job to the server
        //when the job runs it will pull the binary image file from the ftp server
         //echo $jobfile ;
	//$result=(string)setparamdouble($name,(float)$_POST['floatval'],$myioservice);


} else{
    echo "There was an error uploading the file, please try again!";
}
?>
