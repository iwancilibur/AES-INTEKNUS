<?php
require "aeslibrary.php";
        $waktu          =date('d F Y, h:i:s A');
        $data           = json_encode(['suhu'=>'32','kelembapan'=>'70','TIme'=>$waktu]);
        $inputKey       = "tuqZQhKP48e8Piuc";
        $iv             = "zxtZQhMzx8e8Piuc";
        $blockSize      = 128;
        $aes            = new AESEncryption($data, $inputKey, $iv, $blockSize);
        $enc            = $aes->encrypt();
        $aes->setData($enc);
        $dec=$aes->decrypt();
        echo "After encryption: ".$enc."<br/>";
        echo "After decryption: ".$dec."<br/>";

?>