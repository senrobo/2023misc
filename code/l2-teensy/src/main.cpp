#include <Arduino.h>

int incomingByte = 0; // for incoming serial data

void setup()
{
  // put your setup code here, to run once:
  Serial3.begin(115200);
  pinMode(13, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(2000);            // wait for a second
  digitalWrite(13, LOW);  // turn the LED off by making the voltage LOW
  delay(2000);            // wait for a second
  int goalX = 0;
  while (Serial3.available() < 1)
    ;
  goalX = Serial3.read();
  Serial.print(goalX);
  Serial.print(" ");
  Serial.println();
}