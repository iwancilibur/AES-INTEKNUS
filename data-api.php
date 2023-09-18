<?php 
require "koneksi.php";
require "aeslibrary.php";
//session_start();
        date_default_timezone_set('Asia/Jakarta');
        //http://localhost/aes/data-api.php?inputkey=tuqZQhKP48e8Piuc&&iv=zxtZQhMzx8e8Piuc&&suhu=35&&kelembaban=78
        $inputKey_temp		= $_GET["inputkey"];
        $ivx_temp		= $_GET["iv"];
        $suhu		 	= $_GET["suhu"];
        $kelembaban		= $_GET["kelembaban"];
        $waktu                  = date("Y-m-d G:i:s");
        
        //ENKRIPSI
        $data           = json_encode(['suhu'=>$suhu,'kelembapan'=>$kelembaban,'waktu'=>$waktu]);
        $inputKey       = $inputKey_temp;
        $iv             = $ivx_temp;
        $blockSize      = 128;
        $aes            = new AESEncryption($data, $inputKey, $iv, $blockSize);
        $enc            = $aes->encrypt();
        $aes->setData($enc);
        $dec=$aes->decrypt();
        echo $enc;
        //$_SESSION["enkripsi"] = $enc;
        echo "  ".$dec."";
       
        //UPDATE DATA REALTIME PADA TABEL tb_update
        $sql = "UPDATE tb_update SET 
                keyaes      = '$inputKey_temp',
                ivaes       = '$ivx_temp',
                suhu        = '$suhu',
                kelembaban  = '$kelembaban',
                waktu       = '$waktu'";
        $dbconnect->query($sql);
        
        //INSERT DATA REALTIME PADA TABEL tb_sensor 	
        $sqlsave = "INSERT INTO tb_sensor (suhu, kelembaban,waktu) VALUES ('" . $suhu . "', '" . $kelembaban . "', '" . $waktu . "')";
        $dbconnect->query($sqlsave);

        //MENJADIKAN JSON DATA
        // $response =  query("SELECT * FROM kategori_makanan WHERE kategori='$datanya'")[0];
        // $result = json_encode($response);
        // echo $result;
        
		
 ?>