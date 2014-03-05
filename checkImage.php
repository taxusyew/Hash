<?php
	$arrayNum = "0123456789";
	$arrayChar = "abcdefghigklmnopqrstuvwxyz";


	$img = imagecreate(100, 50);
	$blue = imagecolorallocate($img, 100, 100, 100);
	$green = imagecolorallocate($img, 0, 255, 0);

	// for ($i=0; $i < 3; $i++) { 
	// 	$offset = $i * 10;
		imagettftext($img, 10, 0, 20, 0, $green, "ARIAL.TTF", "a");
	// }
	// imagerectangle($img, 0, 0, 20, 20, $blue);
	imagefill($img, 0, 0, $blue);

	header('Content_type: image/png');
	imagepng($img);
	
	imagedestroy($img);
?>