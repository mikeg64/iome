<?php
require_once('iome/iome.php');

$myioservice = new ioservice;
$myioservice->server = 'suilven.shef.ac.uk';
$myioservice->port = '60001';
$myioservice->id = 0;
$myioservice->method = 2;

//need correct write permission on target path
$currenttime = time();
//$target_path="/var/www/html/uploads/";
$target_path="/webusers/cs6grid/public_html/iogatest/results/$currenttime";
//echo $target_path ;
echo getcwd();

//$target_path = $target_path.basename( $_FILES['userfile']['name']); 
//echo $target_path ;
	   /*The following lines read the job template xml file*/
	   /*The %items%  in the jobfile content are replaced with
	   the variable parameters*/
	   /*we use the str_replace function to acheive this*/
	   /*str_replace — Replace all occurrences of the search string with the replacement string*/

        $useremail=""
	$jobfile = file_get_contents  ( "iogaphp.xml");
        $jobref=$currenttime
        $populationnumber="30"
        $generationnumber="50"
        $crossoverprobability="0.9"
        $mutationprobability="0.6"
        $equation="y=n+sum(x.^2-cos(2*pi*x));"
        $parameternumber="2"

 	if(!empty($_POST['useremail'])){
        $useremail = $_POST['useremail'];
        
 	if(!empty($_POST['populationnumber'])){
        $populationnumber = $_POST['populationnumber'];
        }

 	if(!empty($_POST['crossoverprobability'])){
        $crossoverprobability = $_POST['crossoverprobability'];
        }

 	if(!empty($_POST['mutationprobability'])){
        $mutationprobability = $_POST['mutationprobability'];
        }

 	if(!empty($_POST['equation'])){
        $equation = $_POST['equation'];
        }

 	if(!empty($_POST['parameternumber'])){
        $parameternumber = $_POST['parameternumber'];
        }
        
        $tempjobfile = str_replace("%useremail%", $useremail, $jobfile);
        $temptjobfile = str_replace("%populationnumber%", $populationnumber, $tempjobfile);
        $tempjobfile = str_replace("%generationnumber%", $generationnumber, $temptjobfile);
        $temptjobfile = str_replace("%crossoverprobability%", $crossoverprobability, $tempjobfile);
        $tempjobfile = str_replace("%mutationprobability%", $mutationprobability, $temptjobfile);
        $temptjobfile = str_replace("%equation%", $equation, $tempjobfile);
        $tempjobfile = str_replace("%jobref%", $jobref, $temptjobfile);

        $jobfile = str_replace("%parameternumber%", $parameternumber, $tempjobfile);

        //submit the job to the server
        //when the job runs it will pull the binary image file from the ftp server
        echo "populationnumber: ".$populationnumber
        echo "generationnumber: ".$generationnumber
        echo "crossoverprobability: ".$crossoverprobability
        echo "mutationprobability: ".$mutationprobability
        echo "equation: ".$equation
        echo "parameternumber: ".$parameternumber
        
        mkdir($target_path,0777,true);
	//$result=(string)setparamdouble($name,(float)$_POST['floatval'],$myioservice);
        submitsimulation($jobfile,$myioservice);
        //during testing we use the request to set up the job
        //this will not delete the directory when the job has completed
		//$result = requestsimulation($jobfile,$myioservice);
            //echo $result;
        $resultlink="http://wrgrid.group.shef.ac.uk/iogatest/results/".$currenttime
        echo "Result will be available at:"
        echo $resultlink
            //$myioservice -> id = $result;
		//runrequestedsimulation($myioservice);


?>
