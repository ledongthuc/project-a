#include "OutletManager.h"
#include "OutletStatus.h"
#include "Arduino.h"

OutletManager::OutletManager(int numberOfOutlet) {
  this->numberOfOutlet = numberOfOutlet;
  this->signalParser = new OutletSignalParser();
  
  for(int index=0; index < 4; index++) {
    this->outlets[index] = new Outlet();
  }
  
  this->signal = 0b00000000;
}

void OutletManager::updateOutletStatus(unsigned char updatedOutletSignal) {
  this->signal = this->signalParser->parseCurrentSignalByUpdatedSignal(this->signal, updatedOutletSignal);
  
  OutletStatus status[4];
  this->signalParser->parseOutletSignal(this->signal, status);
  
  for(int index=0; index < 4; index++) {
    this->outlets[index]->setStatus(status[index]);
  }
}

unsigned char OutletManager::getOutletSignal() {
 return this->signal; 
}

Outlet** OutletManager::getOutlets() {
  return this->outlets;
}
