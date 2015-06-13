#include <Utility.h>
#include "OutletManager.h"
#include "BleManager.h"
#include "RelayManager.h"

#define RX_PIN                     10
#define TX_PIN                     11
#define BAUD_RATE                  9600
#define SERVICE_ID                 "0xB000"
#define NOTIFICATION_INFORMATION   "1"
#define DEFAULT_ADVERTISING_DATA   0b11110000


BleManager* bleManager;
OutletManager* outletManager;
RelayManager* relayManager;
int lightEnable[4];
int lightStatus[4];
  
void setup() {
  Serial.begin(9600);
  
  bleManager = new BleManager(RX_PIN, TX_PIN, BAUD_RATE);
  bleManager->setServiceId(SERVICE_ID);
  bleManager->setNotificationInformation(NOTIFICATION_INFORMATION);
  bleManager->setAdvertisingData(DEFAULT_ADVERTISING_DATA);
  
  outletManager = new OutletManager(4);
  Outlet** outlets = outletManager->getOutlets();
  
  relayManager = new RelayManager();
  relayManager->updateRelaySignal(outlets);
}

void loop() {
  char rawResponse = bleManager->getResponse();
  
  Serial.print("RawResponse: ");
  Serial.print(rawResponse);
  Serial.println();
  
  outletManager->updateOutletStatus(rawResponse);
  bleManager->disconnectRemotedDevices();
  bleManager->setAdvertisingData(rawResponse);
  
  Outlet** outlets = outletManager->getOutlets();
  relayManager->updateRelaySignal(outlets);
  
  Serial.println("---------^-^--------");
  
  delay(5000);
}

