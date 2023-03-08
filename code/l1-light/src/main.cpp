#include "main.h"

void setup()
{
  // put your setup code here, to run once:
  Serial1.begin(115200); // Debugger
  Serial2.begin(115200); // Teensy
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);

  pinMode(mux1, INPUT);
  pinMode(mux2, INPUT);
  pinMode(m1s0, OUTPUT);
  pinMode(m1s1, OUTPUT);
  pinMode(m1s2, OUTPUT);
  pinMode(m1s3, OUTPUT);
  pinMode(m2s0, OUTPUT);
  pinMode(m2s1, OUTPUT);
  pinMode(m2s2, OUTPUT);
  pinMode(m2s3, OUTPUT);
  pinMode(sol, OUTPUT);

  digitalWriteFast(m1s0, LOW);
  digitalWriteFast(m1s1, LOW);
  digitalWriteFast(m1s2, LOW);
  digitalWriteFast(m1s3, LOW);
  digitalWriteFast(m2s0, LOW);
  digitalWriteFast(m2s1, LOW);
  digitalWriteFast(m2s2, LOW);
  digitalWriteFast(m2s3, LOW);
  digitalWriteFast(sol, LOW);
}

void readLightSensors()
{
  if (micros() - readTimer >= MUX_DELAY)
  {
    bool out = false;
    int idx = lightCnt;
    lightVals[idx] = analogRead(mux1);
    if (lightVals[idx] > lightThresh.vals[idx])
    {
      lineDetected[outSensors] = idx;
      outSensors++;
    }
    idx = lightCnt + 16;
    lightVals[idx] = analogRead(mux2);
    if (lightVals[idx] > lightThresh.vals[idx])
    {
      lineDetected[outSensors] = idx;
      outSensors++;
    }

    lightCnt++;
    lightCnt %= 16;
    digitalWriteFast(m1s0, muxChannel[lightCnt][0]);
    digitalWriteFast(m1s1, muxChannel[lightCnt][1]);
    digitalWriteFast(m1s2, muxChannel[lightCnt][2]);
    digitalWriteFast(m1s3, muxChannel[lightCnt][3]);
    digitalWriteFast(m2s0, muxChannel[lightCnt][0]);
    digitalWriteFast(m2s1, muxChannel[lightCnt][1]);
    digitalWriteFast(m2s2, muxChannel[lightCnt][2]);
    digitalWriteFast(m2s3, muxChannel[lightCnt][3]);
    readTimer = micros();
  }
}
void sendDataToTeensy() {}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial2.write(2);
}