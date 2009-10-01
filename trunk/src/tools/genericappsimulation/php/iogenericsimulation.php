<?php

class iogenericsimulation {
 
        var $name;
	private $params = array();
	private $metadata = array();
 
	public function __construct() {
	}
 
	public function addmetadata($prop, $name) {
                $metad=new iometadata($prop, $name)
		array_push($this->params, $metad);
	}

	public function setmetadata($prop, $name) {
		foreach ($metadata as $value)
		  {
		  if( ($value->name) == $name) $value->property=$prop;
		  } 
	} 

	public function getmetadata($name) {
                foreach ($metadata as $value)
		  {
		  if( ($value->name) == $name) return $value->property;
		  } 
  
		return;
	}        

	public function readsimulation($filename) {

		$parser=new iosimreader();
                $status=$parser->readsimulation($filename, $this);
		return $status;
	}

	public function writesimulation($filename) {

		$writer=new iosimwriter($this);
                $status=$writer->writesimulation($filename);
		return $status;
	}
 
}




?>
