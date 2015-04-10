#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
const int PIN_LIGHT = 3;
const char TURN_ON_SIGNAL = '1';
const char TURN_OFF_SIGNAL = '0';

char signalHistory[2];

void setup()  
{
  pinMode(PIN_LIGHT, OUTPUT);
  
  Serial.begin(4800);
  mySerial.begin(9600);
}

void loop() // run over and over
{
  if(!mySerial.available()) {
    return;
  }
  
  byte rawData = mySerial.read();
  Serial.print("Get message: ");
  Serial.println(rawData, DEC);
  
  char* signalHistory = pushToSignalHistory(rawData);
  char parsedData = composeCharFrom2Bytes(signalHistory[0], signalHistory[1]);
  
  switch(parsedData) {
    case TURN_ON_SIGNAL:
      turnOnLight();
      break;
    case TURN_OFF_SIGNAL:
      turnOffLight();
      break;
  }
}

void turnOnLight() {
  Serial.println("Turnon light");  
  digitalWrite(PIN_LIGHT, HIGH);
}

void turnOffLight() {
  Serial.println("Turnon off");  
  digitalWrite(PIN_LIGHT, LOW);
}

/*
 * Input 2 bytes, convert them to 1 byte.
 * byte1: 52  |=>  ASCII: 4   |=>  ASCII: 48    |=>    byte: 48  |=>  ASCII: 0  
 * byte2: 56  |        ASCII: 8   |                             |                          |
 *
 *
 * byte1: 52  |=>  ASCII: 4   |=>  ASCII: 49    |=>    byte: 49  |=>  ASCII: 1  
 * byte2: 57  |        ASCII: 9   |                             |                          |
 */
char composeCharFrom2Bytes(byte first, byte two) {
  char chars[] = { (char)first, (char)two, '\0'};
  byte resultAsByte = atoi(chars);
  return (char)resultAsByte;
}

char* pushToSignalHistory(byte pushedData) {
  signalHistory[0] = signalHistory[1];
  signalHistory[1] = pushedData;
  return signalHistory;
}
