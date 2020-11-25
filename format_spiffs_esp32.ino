/* Format the spiffs memory
 * if 'd' is received on serial
 * 2020 Ghetto Buidler
 */


#include "SPIFFS.h"
 
 
void setup() { 
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("\n\n----Listing files");
  listAllFiles();
}
 
void loop() {
  if ( Serial.available()) {
    char ch = Serial.read();
    Serial.print(" First received character :");
    Serial.println(ch);
    Serial.flush();
    bool formatted;
    if (ch =='d') {
      Serial.println (" Format should take a few seconds, please wait....");
      bool formatted = SPIFFS.format();
      if(formatted){
        Serial.println("\n\nSuccess formatting");
      }else{
        Serial.println("\n\nError formatting");
      }
      Serial.println("\n\n----Listing files after format----");
      listAllFiles();
    }
  }
}

void listAllFiles(){
  int i = 0;
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while(file){
      i++;
      Serial.print("FILE: ");
      Serial.println(file.name());
      file = root.openNextFile();
  }
  if (i==0) {
    Serial.println("THe Spliff is empty");
  }
}
