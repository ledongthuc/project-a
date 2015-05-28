#include <Hm10.h>
#include <Utility.h>

Hm10* hm10;
  
void setup() {
  Serial.begin(9600);
  hm10 = new Hm10(10, 11);
  
  Serial.print("TestCommand, Receive: ");
  char* result = hm10->setServiceId("0x9999");
  Serial.print(result);
  Serial.print("\n\n");
}

void loop() {

  
  delay(2000);
}

