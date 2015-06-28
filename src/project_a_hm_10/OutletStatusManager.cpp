#include "OutletStatusManager.h"
#include "OutletStatus.h"
#include "Arduino.h"

OutletStatusManager::OutletStatusManager(int numberOfOutlet) {
  this->numberOfOutlet = numberOfOutlet;
  this->signalParser = new OutletSignalParser();
  
  for(int index=0; index < 4; index++) {
    this->outlets[index] = new Outlet();
  }
  
  this->signal = 0b00000000;
}

void OutletStatusManager::parseRequestFromMobile(unsigned char updatedOutletSignal) {
  this->signal = this->signalParser->parseCurrentSignalByUpdatedSignal(this->signal, updatedOutletSignal);
  
  OutletStatus status[4];
  this->signalParser->parseOutletSignal(this->signal, status);
  
  for(int index=0; index < 4; index++) {
    this->outlets[index]->setStatus(status[index]);
  }
}

unsigned char OutletStatusManager::getOutletSignal() {
 return this->signal; 
}

Outlet** OutletStatusManager::getOutlets() {
  return this->outlets;
}
