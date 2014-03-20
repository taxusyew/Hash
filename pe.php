<?php
function pe($filename)
	{
		$path     = '/var';
		// 拼接文件路径
		$pathA=substr($filename, 0, 1);
		$pathB=substr($filename, 1, 1);
		$pathC=substr($filename, 2, 1);
		$pathD=substr($filename, 3, 1);
		$file_path = $path.$pathA.'/'.$pathB.'/'.$pathC.'/'.$pathD.'/'.$filename;

		$fp = fopen($file_path, "rb");
		$data = fread($fp, 400);
		fclose($fp);
		$finalflag = 0;

		// 输出MZ
		$fphead = substr($data, 0, 2);
		$fphead = unpack("C*",$fphead);
		if (($fphead[1] == 77) && ($fphead[2] == 90)) {
			// 找0x3c 的值
			$fp3c = substr($data, 60, 4);
			$fp3c = unpack("C*",$fp3c);

			$i3C = ($fp3c[4]<<24) +($fp3c[3]<<16) +($fp3c[2]<<8) + $fp3c[1];
			
			// 如果PE头偏移大于400，返回
			if ($i3C > 400) {
				break;
			}

			// 判断PE头
			$fpPE = substr($data, $i3C, 2);
			$iPE = unpack("C*",$fpPE);
			if (($iPE[1] == 80) && ($iPE[2] == 69))
			{
				$fpflag = substr($data, $i3C + 22, 2);
				$PEflag = unpack("C*",$fpflag);
				
				$flag = ($PEflag[2]<<8) + $PEflag[1];
				
				if( $flag & 8192)
				{
					$finalflag = 0;
				}
				else{
					$finalflag = 1;
				}
			}
		}
		$is_exe = array(
			'isexe' => $finalflag
		);
		// echo json_encode($is_exe);
		return $finalflag;
	}
?>
