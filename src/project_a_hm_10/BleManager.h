#include <Hm10.h>

#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

class BleManager {
  private:
    Hm10* hm10;
    bool isConnectionResponse(char* response);
  public:
    BleManager(int rxPin, int txPin, int baudRate);
    void setServiceId(char* serviceId);
    void setNotificationInformation(char* notificationInformation);
    void setAdvertisingData(char advertisingData);
    void disconnectRemotedDevices();
    char getResponse();
};

#endif
