#include <Arduino.h>

#define IR_LOOP_NUM 20
#define IR_NUM_MULTIPLIER 15
#define BEST_IR_NUM 3

unsigned short ballAngle, realBallStrength, realBallAngle, lastAngle;
float ballStrength, ballDistance;
int IRCounter, tempValues;

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
  for (int i = 0; i < IR_LOOP_NUM; i++)
  {
    tempValues[0] = digitalReadFast(PA5) ^ 1;
    tempValues[1] = digitalReadFast(PA4) ^ 1;
    tempValues[2] = digitalReadFast(PA1) ^ 1;
    tempValues[3] = digitalReadFast(PA0) ^ 1;
    tempValues[4] = digitalReadFast(PC15) ^ 1;
    tempValues[5] = digitalReadFast(PC14) ^ 1;
    tempValues[6] = digitalReadFast(PB9) ^ 1;
    tempValues[7] = digitalReadFast(PB8) ^ 1;
    tempValues[8] = digitalReadFast(PB7) ^ 1;
    tempValues[9] = digitalReadFast(PB6) ^ 1;
    tempValues[10] = digitalReadFast(PB5) ^ 1;
    tempValues[11] = digitalReadFast(PB4) ^ 1;
    tempValues[12] = digitalReadFast(PB3) ^ 1;
    tempValues[13] = digitalReadFast(PA15) ^ 1;
    tempValues[14] = digitalReadFast(PB14) ^ 1;
    tempValues[15] = digitalReadFast(PB13) ^ 1;
    tempValues[16] = digitalReadFast(PB12) ^ 1;
    tempValues[17] = digitalReadFast(PB11) ^ 1;
    tempValues[18] = digitalReadFast(PB10) ^ 1;
    tempValues[19] = digitalReadFast(PB2) ^ 1;
    tempValues[20] = digitalReadFast(PB1) ^ 1;
    tempValues[21] = digitalReadFast(PB0) ^ 1;
    tempValues[22] = digitalReadFast(PA7) ^ 1;
    tempValues[23] = digitalReadFast(PA6) ^ 1;
  }
}

void processIR()
{
  // Complete a reading of the sensors after a certain amount of individual readings, sensor values are now stored in the values array until the next complete read
  for (int i =0, i < IR_NUM, i++)
  {
    values[i] = 100 * (double)tempValues[i] / (double)IR_LOOP_NUM; // multiply each value in the array by 100 then divide it by number of times it read the sensors
    tempValues[i] = 0;                                             // reset values here
    sortedValues[i] = 0;
    indexes[i] = 0;
  }
  IRCounter = 0;
  IRsortvalues();
  IRcalculateanglestrength(BEST_IR_NUMBER);
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



void setup()
{
  // put your setup code here, to run once:
  Serial2.begin(115200); // Initialize Serial2 (USART2) for IR
}

void loop()
{
  // put your main code here, to run repeatedly:

  Serial2.write(1);
}