#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  pinMode(PA8, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(PA8, HIGH);
  delay(250);
  digitalWrite(PA8, LOW);
  delay(250);
}