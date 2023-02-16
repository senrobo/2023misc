#include <Arduino.h>

#define IR_NUM 24      // number of IR sensors
#define IR_LOOP_NUM 20 // number of times to read the sensors in a loop
#define BEST_IR_NUM 3  // number of sensors to use to calculate the angle and strength of the ball

// essentially sorting indexes in an array from largest to lowest //
#define ARRAYLENGTH(array) (sizeof(array) / sizeof(array[0]))
#define ARRAYSHIFTDOWN(a, lower, upper)          \
  {                                              \
    if (upper == (sizeof(a) / sizeof(a[0])) - 1) \
    {                                            \
      for (int q = upper - 1; q >= lower; q--)   \
      {                                          \
        *(a + q + 1) = *(a + q);                 \
      }                                          \
    }                                            \
    else                                         \
    {                                            \
      for (int q = upper; q >= lower; q--)       \
      {                                          \
        *(a + q + 1) = *(a + q);                 \
      }                                          \
    }                                            \
  }

unsigned short ballAngle, realBallStrength, realBallAngle, lastangle, angle, tempValues[24];
float ballStrength, ballDistance, strength;
float angle_kp[3];
int IRCounter, noValsCounter, loopcounter;
uint16_t values[IR_NUM] = {0};       // Sensor values as percentages
uint16_t sortedValues[IR_NUM] = {0}; // Sorted values (highest to lowest)
uint8_t indexes[IR_NUM] = {0};       // Indexes of sensor numbers in sorted list

void initIR()
{
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
}

void readIR()
{
  // loops through the sensors once
  tempValues[0] = digitalRead(PIN_A5) ^ 1;
  tempValues[1] = digitalRead(PA4) ^ 1;
  tempValues[2] = digitalRead(PA1) ^ 1;
  tempValues[3] = digitalRead(PA0) ^ 1;
  tempValues[4] = digitalRead(PC15) ^ 1;
  tempValues[5] = digitalRead(PC14) ^ 1;
  tempValues[6] = digitalRead(PB9) ^ 1;
  tempValues[7] = digitalRead(PB8) ^ 1;
  tempValues[8] = digitalRead(PB7) ^ 1;
  tempValues[9] = digitalRead(PB6) ^ 1;
  tempValues[10] = digitalRead(PB5) ^ 1;
  tempValues[11] = digitalRead(PB4) ^ 1;
  tempValues[12] = digitalRead(PB3) ^ 1;
  tempValues[13] = digitalRead(PA15) ^ 1;
  tempValues[14] = digitalRead(PB14) ^ 1;
  tempValues[15] = digitalRead(PB13) ^ 1;
  tempValues[16] = digitalRead(PB12) ^ 1;
  tempValues[17] = digitalRead(PB11) ^ 1;
  tempValues[18] = digitalRead(PB10) ^ 1;
  tempValues[19] = digitalRead(PB2) ^ 1;
  tempValues[20] = digitalRead(PB1) ^ 1;
  tempValues[21] = digitalRead(PB0) ^ 1;
  tempValues[22] = digitalRead(PA7) ^ 1;
  tempValues[23] = digitalRead(PA6) ^ 1;
}

void IRsortvalues()
{
  // Sort the TSOP values from greatest to least in sortedFilteredValues
  // and sort the TSOP indexes from greatest to least strength in indexes (array positions)

  for (uint8_t i = 0; i < IR_NUM; i++)
  {
    for (uint8_t j = 0; j < IR_NUM; j++)
    {
      if (values[i] > sortedValues[j])
      {
        // We've found our place!
        // Shift elements from index j down
        if (j <= i)
        {
          // Make sure we only shift what is needed
          ARRAYSHIFTDOWN(sortedValues, j, i); // sort strength from weakest to strongest in the array
          ARRAYSHIFTDOWN(indexes, j, i);      // sort the indexes
        }

        sortedValues[j] = values[i];
        indexes[j] = i;
        break;
      }
    }
  }
}

void IRcalculateanglestrength(int n)
{
  // Cartesian addition of best n TSOPs
  float s = 0;
  float t = 0;
  noValsCounter = 0;

  for (int i = 0; i < 16; i++)
  {
    s += sortedValues[i]; // addition of all values in the array and sum up as 's'
  }
  for (int i = 0; i < n; i++)
  {
    t += sortedValues[i];
  }
  for (int i = 0; i < 16; i++)
  {
    if (sortedValues[i] == 0)
      noValsCounter++;
  }
  strength = t / s; // calculate strength as a proportion number, between 0 and 1 ***check reliability, didnt end up using it anyways lmao
  if (loopcounter < 1)
  {
    if (s == 0)
    {
      angle = lastangle;
      // Serial.println("is there ball??");
      loopcounter++;
    }
    else
    {
      if (indexes[0] == 0 || indexes[1] == 0 || indexes[2] == 0)
      {
        if (sortedValues[0] > 60)
        {
          angle = 0;
          // Serial.println("front");
        }
        else
        {
          angle = indexes[0] * 22.5;
          lastangle = angle;
          // Serial.println("haha");
        }
      }

      else
      {
        for (int i = 0; i < 3; i++)
        {
          angle_kp[i] = indexes[i] * sortedValues[i] * 22.5 / (sortedValues[0] + sortedValues[1] + sortedValues[2]);
        }
        angle = angle_kp[0] + angle_kp[1] + angle_kp[2];
        lastangle = angle;
        // Serial.println("ree");
      } // end of else statement for normal angle calculation
      loopcounter = 0;
    } // end of if statement if first 3 IRs = 0

  } // end of loopcounter <1

  else if (loopcounter >= 1)
  {
    if (sortedValues[0] > 0)
    {
      angle = 0;
      loopcounter = 0;
    }
    else
    {
      angle = 400; // no ball detected
      lastangle = angle;
      // Serial.println("no ball");
    }
    loopcounter = 0;
  }
  else
    ;

  // Serial.println(loopcounter); //HELP ME
}

uint16_t IRgetAngle()
{
  return angle;
}

float IRgetStrength()
{
  // return strength;
  return strength;
}

void processIR()
{
  // Complete a reading of the sensors after a certain amount of individual readings, sensor values are now stored in the values array until the next complete read
  for (int i = 0; i < IR_LOOP_NUM; i++)
  {
    values[i] = 100 * (double)tempValues[i] / (double)IR_LOOP_NUM; // multiply each value in the array by 100 then divide it by number of times it read the sensors
    tempValues[i] = 0;                                             // reset values here
    sortedValues[i] = 0;
    indexes[i] = 0;
  }
  IRCounter = 0;
  IRsortvalues();
  IRcalculateanglestrength(BEST_IR_NUM);
}

void setup()
{
  // put your setup code here, to run once:
  Serial2.begin(115200); // Initialize Serial2 (USART2) for IR
  pinMode(PB15, OUTPUT); // Initialize LED pin as output
  initIR();
}

void loop()
{
  // put your main code here, to run repeatedly:
  processIR();
  Serial2.write(angle);
  // Serial2.write(12);
  digitalWrite(PB15, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(PB15, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);
}