/* Example taking test values from node.js server as input as well... */
#include <WiFi.h> //2.7.4
#include <HTTPClient.h>
#include <ArduinoJson.h> //6.17.3
#include <AESLib.h>


char* ssid            = "www.interactiverobotics.club"; //isi dengan SSID WIFI
char* pass            = "cilibur2019"; //isi dengan PASSWORD WIFI
String HOST_NAME      = "192.168.1.3"; // change to your PC's IP address
String PATH_NAME      = "/aes/data-api.php";

AESLib aesLib;

const char* plaintext = "Looks like key but it's not me.";
int loopcount = 0;

char cleartext[256] = {0};
char ciphertext[512];

byte aes_key[] = { 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30 };
// AES Encryption Key

// General initialization vector (you must use your own IV's in production for full security!!!)
byte aes_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void print_key_iv() {
  Serial.print("AES IV: ");
  for (unsigned int i = 0; i < sizeof(aes_iv); i++) {
    Serial.print(aes_iv[i], DEC);
    if ((i + 1) < sizeof(aes_iv)) {
      Serial.print(",");
    }
  }

  Serial.println("");
}

String encrypt_impl(char * msg, byte iv[]) {
  int msgLen = strlen(msg);
  char encrypted[2 * msgLen] = {0};
  aesLib.encrypt64((const byte*)msg, msgLen, encrypted, aes_key, sizeof(aes_key), iv);
  return String(encrypted);
}

String decrypt_impl(char * msg, byte iv[]) {
  int msgLen = strlen(msg);
  char decrypted[msgLen] = {0}; // half may be enough
  aesLib.decrypt64(msg, msgLen, (byte*)decrypted, aes_key, sizeof(aes_key), iv);
  return String(decrypted);
}


void setup() {
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting..");
    delay(100);
  }

  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connected!!!");
    delay(1000);
  }
  else{
    Serial.println("Connected Failed!!!");
  }
  Serial.println("Terhubung ke jaringan!");
}

void loop() {
 
  sprintf(cleartext, "START; %i", 30);
  //sprintf(cleartext, "Looks like key but it's not me.");

  aesLib.set_paddingmode(paddingMode::CMS);

  // Encrypt Data
  byte enc_iv[N_BLOCK] = { 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30 }; // iv_block gets written to, provide own fresh copy...
  String encrypted = encrypt_impl(cleartext, enc_iv);
  sprintf(ciphertext, "%s", encrypted.c_str());
  Serial.print("Base64 encoded Ciphertext: ");
  Serial.println(encrypted);

  // Decrypt Data
  byte dec_iv[N_BLOCK] = { 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30 }; // iv_block gets written to, provide own fresh copy...
  String decrypted = decrypt_impl(ciphertext, dec_iv);
  Serial.print("Base64-decoded Cleartext: ");
  Serial.println(decrypted);

  delay(5000);

}
