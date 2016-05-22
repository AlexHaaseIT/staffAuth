<?php

/* This file is part of staffAuth.
 *
 * staffAuth is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see
 *
 *  http://www.gnu.org/licenses/
 *
 *
 * Copyright (C)
 *  2015-2016 Alexander Haase IT Services <support@alexhaase.de>
 */


namespace staffAuth;

use Silex;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;


abstract class server
{
	private $app;


	/* The following functions are defined as abstract functions and will be
	 * implemented by the API classes to get the API data from a local database
	 * or with a similar method. */
	abstract protected function getAllKeys();


	/** \brief Constructor.
	 *
	 * \details Initializes the Silex routing for the API.
	 */
	public function __construct()
	{
		$this->app = new Silex\Application();

		$this->silex_setup_error_handler();
		$this->silex_setup_routing();
	}


	/** \brief Setup Silex error handler.
	 *
	 * \details Setup the Silex error handler to output a valid JSON object
	 *  instead of HTML.
	 */
	private function silex_setup_error_handler()
	{
		/* This solution is based on the Stack Overflow anser
		 *  http://stackoverflow.com/a/28090703 */
		$this->app->error(function (\Exception $e, Request $request, $code) {
			switch ($code) {
				case 404:
					$message = "Unknown endpoint";
					break;

				default:
					$message = "Unknown error";
			}

			return new JsonResponse(array(
				"status" => "error",
				"code" => $code,
				"message" => $message
			));
		});
	}


	/** \brief Setup the Silex routing for \ref $this->app.
	 *
	 * \details This function will setup all API endpoints and the logic for
	 *  calling the right function for the equivalent API call.
	 */
	private function silex_setup_routing()
	{
		/* Cache $this->app thus it will be needed many times in the following
		 * lines and the use() statement does not allow $this->app. */
		$app = $this->app;


		/* The /keys endpoint will return a full list of all known public keys.
		 * A call to this endpoint will never fail. */
		$app->get("/keys", function () use ($app) {
			return $app->json($this->getAllKeys(), 200);
		});
	}


	/** \brief Run the API server.
	 */
	public function run()
	{
		$this->app->run();
	}
}

?>
