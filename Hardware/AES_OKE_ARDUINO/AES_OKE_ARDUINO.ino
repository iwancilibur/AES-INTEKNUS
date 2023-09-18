#include <AESLib.h>


AESLib aesLib;

int loopcount = 0;

char cleartext1[256] = {0};
char ciphertext1[512];


byte aes_key[] = { 0x74, 0x75, 0x71, 0x5a, 0x51, 0x68, 0x4b, 0x50, 0x34, 0x38, 0x65, 0x38, 0x50, 0x69, 0x75, 0x63 };
// AES Encryption Key



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
}

void loop() {
    int suhu =random(25,35);
    int kelembaban =random(50,75);
    
    sprintf(cleartext1, "suhu=%i,kelembaban=%i",suhu, kelembaban);
    aesLib.set_paddingmode(paddingMode::CMS);

    // Encrypt Data
    byte enc_iv1[N_BLOCK] = { 0x7a, 0x78, 0x74, 0x5a, 0x51, 0x68, 0x4d, 0x7a, 0x78, 0x38, 0x65, 0x38, 0x50, 0x69, 0x75, 0x63 }; // iv_block gets written to, provide own fresh copy...
    String encrypted1 = encrypt_impl(cleartext1, enc_iv1);
    sprintf(ciphertext1, "%s", encrypted1.c_str());
    
    Serial.println();
    Serial.println("Base64 encoded: ");
    Serial.print("ENCRIP: ");Serial.println(encrypted1);
    //Serial.print("IV    : ");Serial.println(enc_iv1);
    //Serial.print("Key   : ");Serial.println(aes_key);
  
    // Decrypt Data
    byte dec_iv1[N_BLOCK] = { 0x7a, 0x78, 0x74, 0x5a, 0x51, 0x68, 0x4d, 0x7a, 0x78, 0x38, 0x65, 0x38, 0x50, 0x69, 0x75, 0x63 }; // iv_block gets written to, provide own fresh copy...
    String decrypted1 = decrypt_impl(ciphertext1, dec_iv1);
    Serial.println("Base64-decoded Cleartext: ");
    Serial.print("DECRIP 1: ");Serial.println(decrypted1);  //Serial.print("DECRIP 2: ");Serial.println(decrypted2);
  
    // send HTTP header
//    HTTPClient http;  
//    http.begin("http://" + String(HOST_NAME) + String(PATH_NAME) + 
//                           "?data="    + String(encrypted1)); 
//    int httpCode = http.GET();
//
//    if (httpCode > 0) {
//        //AMBIL DATA JSON
//        String payload = http.getString();
//        payload.trim();
//        Serial.println(payload);
//      }
//      http.end();
    delay(5000);
}
