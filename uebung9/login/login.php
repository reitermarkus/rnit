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
		while($row = $query->fetch_array(MYSQLI_ASSOC)) {
			echo "<p>" . $row["spyname"] . "</p>";
		}
	} else {
		echo "<p class='error'> Benutzer und Passwort stimmen nicht überein. </p>";
	}
?>