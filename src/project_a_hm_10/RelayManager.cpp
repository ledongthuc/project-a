#include "RelayManager.h"
#include "Outlet.h"
#include "Arduino.h"


RelayManager::RelayManager() {
  this->relayPins[0] = RELAY_PIN_1;
  this->relayPins[1] = RELAY_PIN_2;
  this->relayPins[2] = RELAY_PIN_3;
  this->relayPins[3] = RELAY_PIN_4;
}

void RelayManager::updateRelaySignal(Outlet* outlets[]) {
  this->relaySignals = relaySignals;
  
  for(int index = 0; index < 4; index++) {
    int digialRelayPin = this->relayPins[index];
    OutletStatus outletStatus = outlets[index]->getStatus();
    int relaySignal = outletStatus.isExist & outletStatus.isOn;
    
    Serial.print("Digital relay pin: ");
    Serial.println(digialRelayPin);
    Serial.print("Relay signal: ");
    Serial.println(relaySignal);
    
    pinMode(digialRelayPin, OUTPUT);
    digitalWrite(digialRelayPin, relaySignal);
  }
}
