#include "OutletSignalParser.h"
#include "Arduino.h"
#include "OutletStatus.h"

void OutletSignalParser::parseOutletSignal(unsigned char signal, OutletStatus outletStatus[]) {
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

unsigned char OutletSignalParser::parseCurrentSignalByUpdatedSignal(unsigned char currentSignal, unsigned char updatedSignal) {  
  for(unsigned char existBit = 0b10000000; existBit > 0b00001000; existBit = existBit >> 1) {
    if(existBit & updatedSignal) {      
      if( (existBit & updatedSignal) && 
         !(existBit & currentSignal)) {
        currentSignal += existBit;
      } 
      
      if(!(existBit & updatedSignal) && 
          (existBit & currentSignal)) {
        currentSignal -= existBit;
      }

      unsigned char enableBit = existBit >> 4;
      
      if( (enableBit & updatedSignal) && 
         !(enableBit & currentSignal)) {
        currentSignal += enableBit;
      } 
      
      if(!(enableBit & updatedSignal) && 
          (enableBit & currentSignal)) {
        currentSignal -= enableBit;
      }
    }
  }

  return currentSignal;
}
