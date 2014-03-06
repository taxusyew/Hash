<?php
	$arrayNum = "0123456789";
	// $arrayChar = "abcdefghigklmnopqrstuvwxyz";
	$arrayChar = "0123456789abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSYUVWXYZ";

	$img = imagecreate(100, 50);
	$blue = imagecolorallocate($img, 0, 0, 0);
	$green = imagecolorallocate($img, 255, 255, 255);

	$textSize = 25;
	$roate = 0;
	$X = 0;
	$Y = $textSize + 5;

	for ($i=0; $i < 4; $i++) { 
		$X = $i * $textSize;
		$text = $arrayChar[rand(0, strlen($arrayChar)-1)];
		imagettftext($img, $textSize, $roate, $X, $Y, $green, "arial.ttf", $text);
	}

	header('Content-type: image/png');
	imagepng($img);
	imagedestroy($img);
?>
