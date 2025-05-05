#ifndef BLUETOOTH_LEEVI
#define BLUETOOTH_LEEVI

#include <Arduino.h>

class LeeviBLE {
    public:
    void aloita_mainonta(const String& device_name);
    void lopeta_mainonta(const String& device_name);
    static void send_info_BLE();
    static bool is_connected();
    static bool is_mainonta();
};

#endif 


