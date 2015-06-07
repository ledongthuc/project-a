#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

class BleManager {
  public:
    void Setup(int rxPin, int txPin, int baudRate);
    char GetResponse();
};

#endif
