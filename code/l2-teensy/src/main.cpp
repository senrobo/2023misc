#include <Arduino.h>

int incomingByte = 0; // for incoming serial data

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);  // Compass Serial
  Serial2.begin(115200); // IR Serial
  Serial3.begin(115200); // Camera Serial
  Serial4.begin(115200); // Layer 1 Serial
  Serial5.begin(115200); // Ultra Serial Serial
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);            // wait for a second
  digitalWrite(13, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);            // wait for a second
}

void readCamera()
{
  int goalX = 0;
  while (Serial3.available() < 1)
    ;
  goalX = Serial3.read();
  Serial.print(goalX);
  Serial.print(" ");
  Serial.println();
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100);             // wait for a second
  digitalWrite(13, LOW);  // turn the LED off by making the voltage LOW
  delay(100);             // wait for a second
}

void readIR()
{
  int irAngle = 0;
  while (Serial2.available() < 1)
    ;
  irAngle = Serial2.read();
  Serial.print(irAngle);
  Serial.print(" ");
  Serial.println();
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100);             // wait for a second
  digitalWrite(13, LOW);  // turn the LED off by making the voltage LOW
  delay(100);             // wait for a second
}

void loop()
{
  // put your main code here, to run repeatedly:
  // readCamera();
  readIR();
  Serial.println("Im not dead");
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);            // wait for a second
  digitalWrite(13, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);            // wait for a second
}