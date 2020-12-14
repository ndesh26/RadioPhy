#include <Arduino.h>
#include <Phy.h>

void setup() {
  // put your setup code here, to run once:
   // initialize LED digital pin as an output.
  pinMode(12, OUTPUT);
}

void loop() {
  char message[] = "Hello World!!";
  send(message, strlen(message));
  delay(10000);
}