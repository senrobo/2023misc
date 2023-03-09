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

  // if want to use digitalWriteFast us pinMode(pinNametoDigitalPin(PINNAME), OUTPUT/INPUT))
  pinMode(m1s0, OUTPUT);
  pinMode(m1s1, OUTPUT);
  pinMode(m1s2, OUTPUT);
  pinMode(m1s3, OUTPUT);
  pinMode(m2s0, OUTPUT);
  pinMode(m2s1, OUTPUT);
  pinMode(m2s2, OUTPUT);
  pinMode(m2s3, OUTPUT);
  pinMode(sol, OUTPUT);

  digitalWrite(m1s0, LOW);
  digitalWrite(m1s1, LOW);
  digitalWrite(m1s2, LOW);
  digitalWrite(m1s3, LOW);
  digitalWrite(m2s0, LOW);
  digitalWrite(m2s1, LOW);
  digitalWrite(m2s2, LOW);
  digitalWrite(m2s3, LOW);

  // Deactivate Solenoid
  digitalWrite(sol, LOW);
}

void updateSensors()
{
  if (micros() - readTimer >= MUX_DELAY)
  {
    int idx = lightCnt;
    lightVals[idx] = analogRead(mux1);

    if (lightVals[idx] > fixedThreshFirstBot[idx])
    {
      lineDetected[outSensors] = idx;
      outSensors++;
    }

    idx = lightCnt + 16;

    lightVals[idx] = analogRead(mux2);
    if (lightVals[idx] > fixedThreshFirstBot[idx])
    {
      lineDetected[outSensors] = idx;
      outSensors++;
    }

    lightCnt++;
    lightCnt %= 16;

    // Ping via using nested lists [lightCnt] to access which mux "configuration" and [0-3] to access which pin to set [HIGH/LOW
    digitalWrite(m1s0, muxChannel[lightCnt][0]);
    digitalWrite(m1s1, muxChannel[lightCnt][1]);
    digitalWrite(m1s2, muxChannel[lightCnt][2]);
    digitalWrite(m1s3, muxChannel[lightCnt][3]);
    digitalWrite(m2s0, muxChannel[lightCnt][0]);
    digitalWrite(m2s1, muxChannel[lightCnt][1]);
    digitalWrite(m2s2, muxChannel[lightCnt][2]);
    digitalWrite(m2s3, muxChannel[lightCnt][3]);
    readTimer = micros();
  }
}
void sendDataToTeensy() {}

void loop()
{
  // put your main code here, to run repeatedly:
  updateSensors();
  // sendDataToTeensy();
}