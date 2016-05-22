<?php

require_once "vendor/autoload.php";
require_once __DIR__ . "/../../src/server/server.php";


class myAPI extends staffAuth\server
{
	protected function getAllKeys()
	{
		return array(
			array("id" => 1, "key" => "ssh-rsa AAA...")
		);
	}
}


?>
