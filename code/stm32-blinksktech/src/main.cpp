#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  pinMode(PB12, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly: 
  digitalWrite(PB12, HIGH);
  delay(250);
  digitalWrite(PB12, LOW);
  delay(250);
}