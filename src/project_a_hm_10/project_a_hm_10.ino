#include <Hm10.h>
#include <Utility.h>

Hm10* hm10;
  
void setup() {
  Serial.begin(9600);
  hm10 = new Hm10(10, 11);
}

void loop() {
  Serial.print("TestCommand, Receive: ");
  char* result = hm10->setServiceId("0x9999");
  Serial.print(result);
  Serial.print("\n\n");
  
  delay(2000);
}

