#include <Utility.h>
#include "OutletManager.h"
#include "BleManager.h"

#define RX_PIN                     10
#define TX_PIN                     11
#define BAUD_RATE                  9600
#define SERVICE_ID                 "0xB000"
#define NOTIFICATION_INFORMATION   "1"
#define DEFAULT_ADVERTISING_DATA   0b11110000


BleManager* bleManager;
int lightEnable[4];
int lightStatus[4];
char defaultAdvertisingData = 0b11110000;
  
void setup() {
  Serial.begin(9600);
  
  bleManager = new BleManager(RX_PIN, TX_PIN, BAUD_RATE);
  bleManager->setServiceId(SERVICE_ID);
  bleManager->setNotificationInformation(NOTIFICATION_INFORMATION);
  bleManager->setAdvertisingData(DEFAULT_ADVERTISING_DATA);
}

void loop() {
  char checkedResponse = bleManager->getResponse();
  
  int checkedBit = 128; // 1000 0000
  Serial.println(checkedResponse);
  for(int i=0; i < 4; i++) {    
    if(checkedResponse & checkedBit) {
      lightEnable[i] = 1;
    } else {
      lightEnable[i] = 0;
    }
    
    int checkedLight = checkedBit >> 4;
    if(checkedResponse & checkedLight) {
      lightStatus[i] = 1;
    } else {
      lightStatus[i] = 0;
    }
    
    checkedBit >>= 1;
  }
  
  bleManager->disconnectRemotedDevices();
  bleManager->setAdvertisingData(checkedResponse);
  
  Serial.println("Raw data: ");
  Serial.println(checkedResponse, BIN);
  Serial.println("Light Status: ");
  printLightStatus();
  Serial.println();
  
  
  delay(5000);
}

void printLightStatus() {
  for(int i=0; i < 4; i++) {
    Serial.print("- Light ");
    Serial.print(i + 1);
    Serial.print(", Enable: ");
    Serial.print(lightEnable[i]);
    Serial.print(", Status: ");
    Serial.println(lightStatus[i]);
  }
}
