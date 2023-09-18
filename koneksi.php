
<?php 	

//Simpan dengan nama file koneksidb.php
error_reporting(0);
$server       = ini_get("mysql.default_host"); //Kalau X sama dalam 1 
$user         = "root";
$password     = "";
$database     = "aes"; //Nama Database di phpMyAdmin

$dbconnect      = mysqli_connect($server, $user, $password, $database);

function query($query) {
    global $dbconnect;
    $result = mysqli_query($dbconnect, $query );
    $box = [];
    while( $sql = mysqli_fetch_assoc($result) ){
    $box[] = $sql;
    }
    return $box;
} 

 ?>