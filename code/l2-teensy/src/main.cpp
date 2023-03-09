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
  pinMode(3, OUTPUT);     // FL PWM
  pinMode(4, OUTPUT);     // FL DIR
  pinMode(5, OUTPUT);     // FR PWM
  pinMode(6, OUTPUT);     // FR DIR
  pinMode(9, OUTPUT);     // BR PWM
  pinMode(10, OUTPUT);    // BR DIR
  pinMode(11, OUTPUT);    // BL PWM
  pinMode(12, OUTPUT);    // BL DIR
}

void readLightData(){}
void processLightData(){}
void readCompassData(){}
void readUltraData(){}
void readCameraData(){}
void readIRData(){}



void loop()
{
  // put your main code here, to run repeatedly:
  
}
