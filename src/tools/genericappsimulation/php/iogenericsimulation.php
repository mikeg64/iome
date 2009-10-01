<?php

class iogenericsimulation {
 
	private $params = array();
	private $metadata = array();
 
	public function __construct() {
	}
 
	public function push($data) {
		array_push($this->params, $data);
	}
 
	public function pop() {
		return array_pop($this->params);
	}

	public function readsimulation($filename) {

		$parser=new iosimreader();
                $status=$parser->readsimulation($filename, $this);
		return $status;
	}

	public function writesimulation($filename) {

		$writer=new iosimwriter();
                $status=$writer->writesimulation($filename, $this);
		return $status;
	}
 
}




?>
