#ifndef BLUETOOTH_LEEVI
#define BLUETOOTH_LEEVI

#include <Arduino.h>

class LeeviBLE {
    public:
    void aloita_mainonta(const String& device_name);
    void lopeta_mainonta(const String& device_name);
    void send_info_BLE(const String& viesti);
    static bool is_connected();
    static bool is_mainonta();
    
};

#endif 


