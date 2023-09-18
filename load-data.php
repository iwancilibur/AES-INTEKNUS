<?php
  require 'koneksi.php';
  require "aeslibrary.php";
  
  $data 		= query("SELECT * FROM tb_update")[0];
  $inputKey_temp= $data["keyaes"]; //Key untuk Encripsi
  $ivx_temp		= $data["ivaes"]; //IV untuk Encripsi
  $suhu 		= $data["suhu"];
  $kelembaban 	= $data["kelembaban"];
  $waktu 		= $data["waktu"];
  //ENKRIPSI
  $data           = json_encode(['suhu'=>$suhu,'kelembapan'=>$kelembaban,'waktu'=>$waktu]);
  $inputKey       = $inputKey_temp;
  $iv             = $ivx_temp;
  $blockSize      = 128;
  $aes            = new AESEncryption($data, $inputKey, $iv, $blockSize);
  $enc            = $aes->encrypt();
  $aes->setData($enc);
  $dec=$aes->decrypt();
?> 

<!DOCTYPE html>
<html>
<head>
 <title></title>
</head>
<body >

		<table border=5 width=100% align="center">
		<tr >
		<td  colspan="5" align="center"><img src="img/logo.jpg" width=50%></td>
		</tr>

		<tr >
		<td  colspan="5" align="center"><h1>Data Terenkripsi</h1></td>
		</tr>	

        <tr >
		<td  colspan="5" align="center">
		<?php
		// Echo session variables that were set on previous page
		echo $enc;
		?>
		</td>
		</tr>		
		</table>

		<table border=5 width=100% align="center">
        
		
		<tr bgcolor=yellow>
			<td><h1 >TEMP</h1></td>
			<td><h1 >HUM</h1></td>
			<td><h1 >TIME</h1></td>
		</tr>
		<tr>
			<td><h1 class="mb-1"><?=$suhu?> C</h1></td>
			<td><h1 class="mb-1"><?=$kelembaban?> %</h1></td>
			<td><h1 class="mb-1"><?=$waktu?></h1></td>
		</tr>
		
		
		</table>


</body>
</html>


