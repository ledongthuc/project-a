#include <Hm10.h>

#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

class BleManager {
  public:
    BleManager(int rxPin, int txPin, int baudRate);
    void setServiceId(char* serviceId);
    void setNotificationInformation(char* notificationInformation);
    void setAdvertisingData(char advertisingData);
    void sendData(unsigned char data);
    void setCharacteristic(char* characteristic);
    void setMode(char* mode);
    void disconnectRemotedDevices();
    char getResponse(bool *hasDisconnectSignal);
  private:
    Hm10* hm10Controller;
    bool isConnectStatusString(char* response);
    bool isDisconnectSignal(char* response);
};

#endif
