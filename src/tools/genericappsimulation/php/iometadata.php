<?php

class iometadata {

   var $name, $property;

	public function __construct($iname, $iprop) {
		$this->name=$iname;
		$this->property=$iprop;
	}

	public function setname($inname)
	{
		$this->name=$inname;
	}

	public function setproperty($inprop)
	{
		$this->property=$inprop;
	}

	public function getproperty()
	{
		return $this->property;
	}

	public function getname()
	{
		return $this->name;
	}

}


?>
