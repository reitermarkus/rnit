<?php
	$name = $_POST["username"];
	$password = $_POST["password"];

	$con = new mysqli("localhost", "root", "");

	if ($con->connect_error) {
		die('Could not connect: ' . connect_error());
	}

	$con->select_db("spydatabase");

	$sql = "SELECT spyname FROM spytable WHERE spyname = '$name' and password = '$password'";
	$result = $con->query($sql);

	if(mysqli_num_rows($result) == 1) {
		$query = $con->query("SELECT spyname FROM spytable");
		$spys = "";
		while($row = $query->fetch_array(MYSQLI_ASSOC)) {
			$spys .= "<p>" . $row["spyname"] . "</p>";
		}

		$ip = getenv('HTTP_CLIENT_IP')?:getenv('HTTP_X_FORWARDED_FOR')?:getenv('HTTP_X_FORWARDED')?:
				getenv('HTTP_FORWARDED_FOR')?:getenv('HTTP_FORWARDED')?:getenv('REMOTE_ADDR');

		$obj = (object) [
			"spy" => $name,
			"ip" => $ip,
			"timestamp" => date('Y-m-d H:i:s'),
			"spys" => $spys,
		];

		echo json_encode($obj);

	} else {
		$obj = (object) [
			"error" => "<p class='error'> Benutzer und Passwort stimmen nicht überein. </p>"
		];

		echo json_encode($obj);
	}
?>