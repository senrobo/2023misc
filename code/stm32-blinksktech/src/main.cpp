#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  pinMode(PA15, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(PA15, HIGH);
  delay(250);
  digitalWrite(PA15, LOW);
  delay(250);
}