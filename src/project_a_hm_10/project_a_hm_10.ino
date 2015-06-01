#include <Hm10.h>
#include <Utility.h>

#define SERVICE_ID "0xB000"

Hm10* hm10;
int lightEnable[4];
int lightStatus[4];
char defaultAdvertisingData = 0b11110100;
unsigned char updated = 0b00000000;
  
void setup() {
  Serial.begin(9600);
  hm10 = new Hm10(10, 11);
  
  Serial.print("Set Service ID, Receive: ");
  char* result = hm10->setServiceId(SERVICE_ID);
  Serial.print(result);
  Serial.print("\n\n");
  
  setAdvertisingData(defaultAdvertisingData);
}

void loop() {
  char* response = hm10->getResponse();
  //char response = defaultAdvertisingData;
  
  if(response[0] == 0) {
    delay(5000);
    return;
  }

  Serial.print("Test: ");  
  Serial.println(response[0]);
  
  int checkedBit = 128; // 1000 0000
  char checkedResponse = (char)response[0];
  
  for(int i=0; i < 4; i++) {    
    if(checkedResponse & checkedBit) {
      lightEnable[i] = 1;
      updated |= checkedBit;
    } else {
      lightEnable[i] = 0;
    }
    
    int checkedLight = checkedBit >> 4;
    if(checkedResponse & checkedLight) {
      lightStatus[i] = 1;
      updated |= checkedLight;      
    } else {
      lightStatus[i] = 0;
    }
    
    checkedBit >>= 1;
  }
  
  updated = 0b00000000;
  updated = updated | defaultAdvertisingData;
  Serial.println(updated, BIN);
  setAdvertisingData(updated);
 
  
  Serial.println("Raw data: ");
  Serial.println(updated, BIN);
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

void setAdvertisingData(char updatedData) {
  Serial.print("Set Advertising Data, Receive: ");
  char* result = hm10->setAdvertisingDataFlag(updatedData);
  Serial.print(result);
  Serial.print("\n\n");
}
