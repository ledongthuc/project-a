#include "OutletManager.h"
#include "OutletStatus.h"

OutletManager::OutletManager(int numberOfOutlet) {
  this->numberOfOutlet = numberOfOutlet;
  this->signalParser = new OutletSignalParser();
  
  for(int index=0; index < 4; index++) {
    this->outlets[index] = new Outlet();
  }
}

void OutletManager::updateOutletStatus(char signal) {
  this->signal = signal;
  
  OutletStatus status[4];
  this->signalParser->parseOutletSignal(signal, status);
  
  for(int index=0; index < 4; index++) {
    this->outlets[index]->setStatus(status[index]);
  }
}

char OutletManager::getOutletSignal() {
 return this->signal; 
}
