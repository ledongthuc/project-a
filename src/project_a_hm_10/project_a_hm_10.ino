#include <Hm10.h>
#include <Utility.h>

#define SERVICE_ID "0xB000"

Hm10* hm10;
int lightEnable[4];
int lightStatus[4];
char defaultAdvertisingData = 0b11110000;
  
void setup() {
  Serial.begin(9600);
  hm10 = new Hm10(10, 11);
  
  Serial.print("Set Service ID, Receive: ");
  char* result = hm10->setServiceId(SERVICE_ID);
  Serial.print(result);
  Serial.print("\n\n");
  
  Serial.print("Set Notification Information, Receive: ");
  char* result2 = hm10->setNotificationInformation("1");
  Serial.print(result2);
  Serial.print("\n\n");

  setAdvertisingData(defaultAdvertisingData);
}

void loop() {
  char* response = hm10->getResponse();
  // OK+CONN
  if(response[7] == 0) {
    delay(5000);
    return;
  }
  char checkedResponse = (char)response[7]; 
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
  
  //OK+LOST
  hm10->sendTestCommand();
  
  setAdvertisingData(checkedResponse);
  
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

void setAdvertisingData(char updatedData) {
  Serial.print("Set Advertising Data, Receive: ");
  char* result = hm10->setAdvertisingDataFlag(updatedData);
  Serial.print(result);
  Serial.print("\n\n");
}
