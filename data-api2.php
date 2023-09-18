<?php 
require "koneksi.php";
require "aeslibrary.php";

date_default_timezone_set('Asia/Jakarta');
        //http://localhost/aes/data-api.php?suhu=35&&kelembaban=78
        $inputKey_temp		= "tuqZQhKP48e8Piuc";
        $ivx_temp		= "zxtZQhMzx8e8Piuc";
        $dataencript            = $_GET["data"];
        $encriptfinish          = str_replace(" ", "+", $dataencript);

        //ENKRIPSI
        $data           = json_encode(['suhu'=>$suhu,'kelembapan'=>$kelembaban,'waktu'=>$waktu]);
        //echo $data;
        $inputKey       = $inputKey_temp;
        $iv             = $ivx_temp;
        $blockSize      = 128;
        $aes            = new AESEncryption($data, $inputKey, $iv, $blockSize);
        $enc            = $aes->encrypt();
        $aes->setData($encriptfinish);
        $dec=$aes->decrypt();
        echo "[" ; echo $encriptfinish ; echo "] , " ;
        echo "[" ; echo $dec; echo "]" ;
        
        
        
        // Parsing string data untuk mendapatkan nilai suhu dan kelembaban
        $suhu_start = strpos($dec, "suhu=") + 5; // mencari posisi awal nilai suhu
        $suhu_end = strpos($dec, ",", $suhu_start); // mencari posisi akhir nilai suhu
        $suhu = substr($dec, $suhu_start, $suhu_end - $suhu_start); // mengambil nilai suhu dari string data

        $kelembaban_start = strpos($dec, "kelembaban=") + 11; // mencari posisi awal nilai kelembaban
        $kelembaban = substr($dec, $kelembaban_start); // mengambil nilai kelembaban dari string data

        $waktu                  = date("Y-m-d G:i:s");

        //UPDATE DATA REALTIME PADA TABEL tb_update
        $sql = "UPDATE tb_update SET 
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