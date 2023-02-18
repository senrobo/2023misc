int tempVal[24] = {0}, count = 0, maxVal = -1, maxIndex = -1, totalVal = 0;
unsigned long lastUp;
float ballAngle;

void setup()
{
  Serial1.begin(115200);
  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH);

  pinMode(PC13, INPUT_PULLUP);
  pinMode(PC14, INPUT_PULLUP);
  pinMode(PC15, INPUT_PULLUP);
  pinMode(PA0, INPUT_PULLUP);
  pinMode(PA1, INPUT_PULLUP);
  pinMode(PA2, INPUT_PULLUP);
  pinMode(PA3, INPUT_PULLUP);
  pinMode(PA4, INPUT_PULLUP);
  pinMode(PA5, INPUT_PULLUP);
  pinMode(PA6, INPUT_PULLUP);
  pinMode(PA7, INPUT_PULLUP);
  pinMode(PB0, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);
  pinMode(PB14, INPUT_PULLUP);
  pinMode(PB15, INPUT_PULLUP);
  pinMode(PA8, INPUT_PULLUP);
  pinMode(PA11, INPUT_PULLUP);
  pinMode(PA12, INPUT_PULLUP);
  pinMode(PA15, INPUT_PULLUP);
  pinMode(PB3, INPUT_PULLUP);
  pinMode(PB4, INPUT_PULLUP);
  pinMode(PB5, INPUT_PULLUP);
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB7, INPUT_PULLUP);

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
  tempVal[0] += digitalReadFast(PC_13) ^ 1;
  tempVal[1] += digitalReadFast(PC_14) ^ 1;
  tempVal[2] += digitalReadFast(PC_15) ^ 1;
  tempVal[3] += digitalReadFast(PA_0) ^ 1;
  tempVal[4] += digitalReadFast(PA_1) ^ 1;
  tempVal[5] += digitalReadFast(PA_2) ^ 1;
  tempVal[6] += digitalReadFast(PA_3) ^ 1;
  tempVal[7] += digitalReadFast(PA_4) ^ 1;
  tempVal[8] += digitalReadFast(PA_5) ^ 1;
  tempVal[9] += digitalReadFast(PA_6) ^ 1;
  tempVal[10] += digitalReadFast(PA_7) ^ 1;
  tempVal[11] += digitalReadFast(PB_0) ^ 1;
  tempVal[12] += digitalReadFast(PB_2) ^ 1;
  tempVal[13] += digitalReadFast(PB_14) ^ 1;
  tempVal[14] += digitalReadFast(PB_15) ^ 1;
  tempVal[15] += digitalReadFast(PA_8) ^ 1;
  tempVal[16] += digitalReadFast(PA_11) ^ 1;
  tempVal[17] += digitalReadFast(PA_12) ^ 1;
  tempVal[18] += digitalReadFast(PA_15) ^ 1;
  tempVal[19] += digitalReadFast(PB_3) ^ 1;
  tempVal[20] += digitalReadFast(PB_4) ^ 1;
  tempVal[21] += digitalReadFast(PB_5) ^ 1;
  tempVal[22] += digitalReadFast(PB_6) ^ 1;
  tempVal[23] += digitalReadFast(PB_7) ^ 1;

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