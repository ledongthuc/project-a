#include "BleManager.h"
#include <Hm10.h>
#include <Arduino.h>

BleManager::BleManager(int rxPin, int txPin, int baudRate) {
  this->hm10Controller = new Hm10(rxPin, txPin);
}

void BleManager::setServiceId(char* serviceId) {
  Serial.print("Set Service ID, Receive: ");
  char* result = this->hm10Controller->setServiceId(serviceId);
  Serial.print(result);
  Serial.print("\n\n");
}

void BleManager::setNotificationInformation(char* notificationInformation) {
  Serial.print("Set Notification Information, Receive: ");
  char* result = this->hm10Controller->setNotificationInformation(notificationInformation);
  Serial.print(result);
  Serial.print("\n\n");
}

void BleManager::setAdvertisingData(char advertisingData) {
  Serial.print("Set Advertising Data, Receive: ");
  char* result = this->hm10Controller->setAdvertisingDataFlag(advertisingData);
  Serial.print(result);
  Serial.print("\n\n");
}

void BleManager::disconnectRemotedDevices() {
  Serial.print("Disconnect to remoted devices, Receive: ");
  char* result = this->hm10Controller->sendTestCommand();
  Serial.print(result);
  Serial.print("\n\n");
}

char BleManager::getResponse() {
  char* responses;
  char response = 0;
  do {
    response = 0;
    responses = this->hm10Controller->getResponse();

    if(this->isConnectStatusString(responses) &&
       responses[7] != 0) {
      response = responses[7];
    }

    if(!this->isConnectStatusString(responses))
    {
      response = responses[0];
    }



    delay(1000);
  } while(response == 0);

  return response;
}

bool BleManager::isConnectStatusString(char* response) {
  if(strncmp(response, "OK+CONN", 7) == 0 ||
     strncmp(response, "OK+LOST", 7) == 0) {
     return true;
   }
  return false;
}
