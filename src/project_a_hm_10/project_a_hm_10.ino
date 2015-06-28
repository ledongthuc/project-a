#include <Utility.h>
#include "OutletStatusManager.h"
#include "BleManager.h"
#include "RelayManager.h"
#include "Def.h" // Define configuration

BleManager* bleManager;
OutletStatusManager* outletStatusManager;
RelayManager* relayManager;

unsigned char mobileRequestDatas;
bool hasDisconnectSignal = false;
  
void setup() {
  Serial.begin(9600);
   
  // BLE setup default value
  bleManager = new BleManager(RX_PIN, TX_PIN, BAUD_RATE);
  bleManager->setServiceId(SERVICE_ID);
  bleManager->setNotificationInformation(NOTIFICATION_INFORMATION);
  bleManager->setAdvertisingData(DEFAULT_ADVERTISING_DATA);
  
  // BLE setup default value
  outletStatusManager = new OutletStatusManager(4);
  outletStatusManager->parseRequestFromMobile(DEFAULT_ADVERTISING_DATA);
  Outlet** outlets = outletStatusManager->getOutlets();
  
  // Relay setup default value
  relayManager = new RelayManager();
  relayManager->updateRelaySignal(outlets);
  
  Serial.println("---------end setup--------");
}

unsigned char advData = 0;

void loop() {  
  if(DEBUG) {
    mobileRequestDatas = 0b11110100;
  } else {
    mobileRequestDatas = bleManager->getResponse(&hasDisconnectSignal);
  }
  
  outletStatusManager->parseRequestFromMobile(mobileRequestDatas);
  unsigned char outletSignal = outletStatusManager->getOutletSignal();
  bleManager->sendData(outletSignal);
  
  Outlet** outlets = outletStatusManager->getOutlets();
  relayManager->updateRelaySignal(outlets);
  
  Serial.print("Is has disconnect signal: ");
  Serial.print(hasDisconnectSignal, BIN);
  if(hasDisconnectSignal) {
    bleManager->disconnectRemotedDevices();
    bleManager->setAdvertisingData(outletSignal);
  }
  
  Serial.println("---------^-^--------");
  
  delay(5000);
}

