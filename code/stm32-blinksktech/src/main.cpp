#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  pinMode(PB15, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly: 
  digitalWrite(PB15, HIGH);
  delay(250);
  digitalWrite(PB15, LOW);
  delay(250);
}