<?php
require_once('iome/iome.php');

$myioservice = new ioservice;
$myioservice->server = 'suilven.shef.ac.uk';
$myioservice->port = '60000';
$myioservice->id = 0;
$myioservice->method = 2;

//need correct write permission on target path
//$target_path="/var/www/html/uploads/";
$target_path="/webusers/cs1mkg/public_html/iometest/uploads/";
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
        $jobtype=0;
 	if(!empty($_POST['jobtype'])){
        $jobtype = $_POST['jobtype'];

        }
	   /*The following lines read the job template xml file*/
	   /*The %items%  in the jobfile content are replaced with
	   the variable parameters*/
	   /*we use the str_replace function to acheive this*/
	   /*str_replace — Replace all occurrences of the search string with the replacement string*/

	$jobfile = file_get_contents  ( "iocaimanphp.xml");
        $imagecontents = file_get_contents  ( $target_path);
        $tempjobfile = str_replace("%imagefile%", $imagefile, $jobfile);
        $temptjobfile = str_replace("%useremail%", $useremail, $tempjobfile);
        $jobfile = str_replace("%jobtype%", $jobtype, $temptjobfile);

        //submit the job to the server
        //when the job runs it will pull the binary image file from the ftp server
        echo $imagefile ;
        echo $jobtype;
	//$result=(string)setparamdouble($name,(float)$_POST['floatval'],$myioservice);
        submitsimulation($jobfile,$myioservice);
        //during testing we use the request to set up the job
        //this will not delete the directory when the job has completed
		//requestsimulation($jobfile,$myioservice);

} else{
    echo "There was an error uploading the file, please try again!";
}
?>
