#include <Arduino.h>
int tempVal[24] = {0},
    count = 0, maxVal = -1, maxIndex = -1, totalVal = 0;
unsigned long lastUp;
float ballAngle;

void setup()
{
  Serial1.begin(115200); // Debug
  Serial2.begin(115200); // Teensy
  pinMode(PA5, INPUT);
  pinMode(PA4, INPUT);
  pinMode(PA1, INPUT);
  pinMode(PA0, INPUT);
  pinMode(PC15, INPUT);
  pinMode(PC14, INPUT);
  pinMode(PB9, INPUT);
  pinMode(PB8, INPUT);
  pinMode(PB7, INPUT);
  pinMode(PB6, INPUT);
  pinMode(PB5, INPUT);
  pinMode(PB4, INPUT);
  pinMode(PB3, INPUT);
  pinMode(PA15, INPUT);
  pinMode(PB14, INPUT);
  pinMode(PB13, INPUT);
  pinMode(PB12, INPUT);
  pinMode(PB11, INPUT);
  pinMode(PB10, INPUT);
  pinMode(PB2, INPUT);
  pinMode(PB1, INPUT);
  pinMode(PB0, INPUT);
  pinMode(PA7, INPUT);
  pinMode(PA6, INPUT);

  lastUp = micros();
}

float mod(float x, float y)
{
  x = fmod(x, y);
  return x < 0 ? x + y : x;
}

void loop()
{
  // read IR
  tempVal[0] = digitalRead(PA5) ^ 1;
  tempVal[1] = digitalRead(PA4) ^ 1;
  tempVal[2] = digitalRead(PA1) ^ 1;
  tempVal[3] = digitalRead(PA0) ^ 1;
  tempVal[4] = digitalRead(PC15) ^ 1;
  tempVal[5] = digitalRead(PC14) ^ 1;
  tempVal[6] = digitalRead(PB9) ^ 1;
  tempVal[7] = digitalRead(PB8) ^ 1;
  tempVal[8] = digitalRead(PB7) ^ 1;
  tempVal[9] = digitalRead(PB6) ^ 1;
  tempVal[10] = digitalRead(PB5) ^ 1;
  tempVal[11] = digitalRead(PB4) ^ 1;
  tempVal[12] = digitalRead(PB3) ^ 1;
  tempVal[13] = digitalRead(PA15) ^ 1;
  tempVal[14] = digitalRead(PB14) ^ 1;
  tempVal[15] = digitalRead(PB13) ^ 1;
  tempVal[16] = digitalRead(PB12) ^ 1;
  tempVal[17] = digitalRead(PB11) ^ 1;
  tempVal[18] = digitalRead(PB10) ^ 1;
  tempVal[19] = digitalRead(PB2) ^ 1;
  tempVal[20] = digitalRead(PB1) ^ 1;
  tempVal[21] = digitalRead(PB0) ^ 1;
  tempVal[22] = digitalRead(PA7) ^ 1;
  tempVal[23] = digitalRead(PA6) ^ 1;

  if ((micros() - lastUp) > 3333)
  {
    for (int i = 0; i < 24; i++)
    {
      // Serial.print(tempVal[i]);
      // Serial.print(" ");
      if (tempVal[i] > maxVal)
      {
        maxVal = tempVal[i];
        maxIndex = i;
      }
      totalVal += tempVal[i];
    }

    if (maxIndex == 0)
    {
      ballAngle = 330.0 * ((float)tempVal[22] / (float)(tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1] + tempVal[2])) + 345.0 * ((float)tempVal[23] / (float)(tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1] + tempVal[2])) + 360.0 * ((float)tempVal[0] / (float)(tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1] + tempVal[2])) + 375.0 * ((float)tempVal[1] / (float)(tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1] + tempVal[2])) + 390.0 * ((float)tempVal[2] / (float)(tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1] + tempVal[2]));
    }
    else if (maxIndex == 23)
    {
      ballAngle = 315.0 * ((float)tempVal[21] / (float)(tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1])) + 330.0 * ((float)tempVal[22] / (float)(tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1])) + 345.0 * ((float)tempVal[23] / (float)(tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1])) + 360.0 * ((float)tempVal[0] / (float)(tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1])) + 375.0 * ((float)tempVal[1] / (float)(tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0] + tempVal[1]));
    }
    else if (maxIndex == 22)
    {
      ballAngle = 300.0 * ((float)tempVal[20] / (float)(tempVal[20] + tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0])) + 315.0 * ((float)tempVal[21] / (float)(tempVal[20] + tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0])) + 330.0 * ((float)tempVal[22] / (float)(tempVal[20] + tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0])) + 345.0 * ((float)tempVal[23] / (float)(tempVal[20] + tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0])) + 360.0 * ((float)tempVal[0] / (float)(tempVal[20] + tempVal[21] + tempVal[22] + tempVal[23] + tempVal[0]));
    }
    else if (maxIndex == 1)
    {
      ballAngle = -15.0 * ((float)tempVal[23] / (float)(tempVal[23] + tempVal[0] + tempVal[1] + tempVal[2] + tempVal[3]))
                  //+00.0*((float)tempVal[0]/(float)(tempVal[23]+tempVal[0]+tempVal[1]+tempVal[2]+tempVal[3]))
                  + 15.0 * ((float)tempVal[1] / (float)(tempVal[23] + tempVal[0] + tempVal[1] + tempVal[2] + tempVal[3])) + 30.0 * ((float)tempVal[2] / (float)(tempVal[23] + tempVal[0] + tempVal[1] + tempVal[2] + tempVal[3])) + 45.0 * ((float)tempVal[3] / (float)(tempVal[23] + tempVal[0] + tempVal[1] + tempVal[2] + tempVal[3]));
    }
    else if (maxIndex == 2)
    {
      ballAngle = // 00.0*((float)tempVal[0]/(float)(tempVal[0]+tempVal[1]+tempVal[2]+tempVal[3]+tempVal[4]))
          +15.0 * ((float)tempVal[1] / (float)(tempVal[0] + tempVal[1] + tempVal[2] + tempVal[3] + tempVal[4])) + 30.0 * ((float)tempVal[2] / (float)(tempVal[0] + tempVal[1] + tempVal[2] + tempVal[3] + tempVal[4])) + 45.0 * ((float)tempVal[3] / (float)(tempVal[0] + tempVal[1] + tempVal[2] + tempVal[3] + tempVal[4])) + 60.0 * ((float)tempVal[4] / (float)(tempVal[0] + tempVal[1] + tempVal[2] + tempVal[3] + tempVal[4]));
    }
    else
    {
      ballAngle = (float)(maxIndex - 2) * 15.0 * ((float)tempVal[maxIndex - 2] / (float)(tempVal[maxIndex - 2] + tempVal[maxIndex - 1] + tempVal[maxIndex] + tempVal[maxIndex + 1] + tempVal[maxIndex + 2])) + (float)(maxIndex - 1) * 15.0 * ((float)tempVal[maxIndex - 1] / (float)(tempVal[maxIndex - 2] + tempVal[maxIndex - 1] + tempVal[maxIndex] + tempVal[maxIndex + 1] + tempVal[maxIndex + 2])) + (float)(maxIndex)*15.0 * ((float)tempVal[maxIndex] / (float)(tempVal[maxIndex - 2] + tempVal[maxIndex - 1] + tempVal[maxIndex] + tempVal[maxIndex + 1] + tempVal[maxIndex + 2])) + (float)(maxIndex + 1) * 15.0 * ((float)tempVal[maxIndex + 1] / (float)(tempVal[maxIndex - 2] + tempVal[maxIndex - 1] + tempVal[maxIndex] + tempVal[maxIndex + 1] + tempVal[maxIndex + 2])) + (float)(maxIndex + 2) * 15.0 * ((float)tempVal[maxIndex + 2] / (float)(tempVal[maxIndex - 2] + tempVal[maxIndex - 1] + tempVal[maxIndex] + tempVal[maxIndex + 1] + tempVal[maxIndex + 2]));
    }
    ballAngle = mod(ballAngle, 360);

    /*if(Serial1.available()) {
      char info = Serial1.read();
      Serial1.print(ballAngle);
      Serial1.print(",");
      Serial1.print(totalVal);
      Serial1.print("|");
    }*/
    Serial1.print('I');
    Serial1.print(ballAngle);
    Serial1.print(',');
    Serial1.print(totalVal);
    Serial1.print('|');

    Serial2.write(ballAngle);

    memset(tempVal, 0, sizeof(tempVal));
    maxVal = -1;
    maxIndex = -1;
    totalVal = 0;
    // Serial.print(ballAngle); Serial.print(" ");
    // Serial.print(maxVal); Serial.print(" ");
    // Serial.print(totalVal);
    // Serial.println();

    lastUp = micros();
  }
}