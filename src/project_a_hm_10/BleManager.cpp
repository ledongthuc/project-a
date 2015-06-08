#include "BleManager.h"
#include <Hm10.h>
#include <Arduino.h>

BleManager::BleManager(int rxPin, int txPin, int baudRate) {
  this->hm10 = new Hm10(rxPin, txPin);
}

void BleManager::setServiceId(char* serviceId) {
  Serial.print("Set Service ID, Receive: ");
  char* result = this->hm10->setServiceId(serviceId);
  Serial.print(result);
  Serial.print("\n\n");
}

void BleManager::setNotificationInformation(char* notificationInformation) {
  Serial.print("Set Notification Information, Receive: ");
  char* result = this->hm10->setNotificationInformation(notificationInformation);
  Serial.print(result);
  Serial.print("\n\n");
}

void BleManager::setAdvertisingData(char advertisingData) {
  Serial.print("Set Advertising Data, Receive: ");
  char* result = this->hm10->setAdvertisingDataFlag(advertisingData);
  Serial.print(result);
  Serial.print("\n\n");
}

void BleManager::disconnectRemotedDevices() {
  Serial.print("Disconnect to remoted devices, Receive: ");
  char* result = hm10->sendTestCommand();
  Serial.print(result);
  Serial.print("\n\n");
}

char BleManager::getResponse() {
  char* responses;
  char response = 0;
  do {
    responses = this->hm10->getResponse();
    
    response = responses[7];
  } while(response == 0);
  
  return response;
}
