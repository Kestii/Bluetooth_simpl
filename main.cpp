#include <Arduino.h>
#include <bluetooth_leevi.h>

LeeviBLE ble;
bool yhdistetty = false;
String bluetooth_nimi = "moi";
bool mainonta = false;
void setup() {
  Serial.begin(115200);
  delay(200);

  
  ble.aloita_mainonta(bluetooth_nimi);
  Serial.println("mainonta aloitettu");
}

void loop() {

  yhdistetty = LeeviBLE :: is_connected();
  mainonta = LeeviBLE :: is_mainonta();
  if(yhdistetty == false && mainonta == true){ // kun mainonta on true niin se voidaan aloittaa
    ble.aloita_mainonta(bluetooth_nimi);
    Serial.println("ei yhdistetty");

  }
  if(yhdistetty == true){
    Serial.println("yhdistetty laitteeseen");
  }
  delay(5000);
  ble.send_info_BLE("123456789101234567890leeeviii");
}

