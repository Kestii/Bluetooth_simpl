#include <bluetooth_leevi.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLECharacteristic.h>
#include <BLEAdvertising.h>

#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer* pServer = nullptr;  
BLECharacteristic *pCharacteristic = nullptr;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;
bool mainontaa = true; // meinaa sitä että true == mainonta voidaan aloittaa


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      mainontaa = false;
      Serial.println("Yhdistetty BLE-laitteeseen");

    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      mainontaa = true;
    }
};

void LeeviBLE :: aloita_mainonta (const String& device_name){
    if(!mainontaa) return;
    Serial.println("Starting BLE work!");
    BLEDevice::init(device_name.c_str());
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
                                           CHARACTERISTIC_UUID,
                                           BLECharacteristic::PROPERTY_READ |
                                           BLECharacteristic::PROPERTY_WRITE
                                         );
  
    
    pService->start();
    // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("Characteristic defined! Now you can read it in your phone!");
    mainontaa = false;
  

}


bool LeeviBLE :: is_connected(){
    Serial.println("tarkistetaan yhdistetty tila");
    return deviceConnected;
    
}

bool LeeviBLE :: is_mainonta(){
    return mainontaa;
}

















void LeeviBLE :: lopeta_mainonta(const String& device_name){
    BLEDevice :: stopAdvertising();

}

void LeeviBLE :: send_info_BLE(){
    pCharacteristic->setValue("Hello World says Neil");
}