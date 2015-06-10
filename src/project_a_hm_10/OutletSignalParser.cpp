#include "OutletSignalParser.h"
#include "Arduino.h"
#include "OutletStatus.h"

void OutletSignalParser::parseOutletSignal(char signal, OutletStatus outletStatus[]) {
  int checkedBit = 0b10000000;
  int checkedLight = 0b00001000;
  Serial.print("Signal: ");
  Serial.println(signal);
  for(int index = 0; index < 4; index++) {    
    if(signal & checkedBit) {
      outletStatus[index].isExist = true;
    } else {
      outletStatus[index].isExist = false;
    }
    
    if(signal & checkedLight) {
      outletStatus[index].isOn = true;
    } else {
      outletStatus[index].isOn = false;
    }
    
    checkedBit >>= 1;
    checkedLight >>= 1;
  }
}
