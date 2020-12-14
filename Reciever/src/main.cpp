#include <Arduino.h>
#include <Phy.h>

void setup() {
  // put your setup code here, to run once:
   // initialize LED digital pin as an output.
  pinMode(12, INPUT);
  Serial.begin(9600);
  Serial.println("Detecting signal now");
}

void loop() {
  char message[MAX_DATA_LEN];
  int len = recv(message);
  message[len] = '\0';
  Serial.println(message);
}