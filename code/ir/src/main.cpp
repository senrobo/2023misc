#include <Arduino.h>
#include <SoftwareSerial.h>

#define IR_0 PA5   // IR1
#define IR_1 PA4   // IR2
#define IR_2 PA1   // IR3
#define IR_3 PA0   // IR4
#define IR_4 PC15  // IR5
#define IR_5 PC14  // IR6
#define IR_6 PB9   // IR7
#define IR_7 PB8   // IR8
#define IR_8 PB7   // IR9
#define IR_9 PB6   // IR10
#define IR_10 PB5  // IR11
#define IR_11 PB4  // IR12
#define IR_12 PB3  // IR13
#define IR_13 PA15 // IR14
#define IR_14 PB14 // IR15
#define IR_15 PB13 // IR16
#define IR_16 PB12 // IR17
#define IR_17 PB11 // IR18
#define IR_18 PB10 // IR19
#define IR_19 PB2  // IR20
#define IR_20 PB1  // IR21
#define IR_21 PB0  // IR22
#define IR_22 PA7  // IR23
#define IR_23 PA6  // IR24

#define IR_NUM 24                 // define number of sensors u are using
#define IR_NUM_MULTIPLIER 15      // (360 / IR_NUM)
#define BEST_IR_NUMBER 3          // Number of strongest sensors used to calculate angle and strength
#define IR_TIMER_PERIOD_NUMBER 38 // mininum number of periods (of 833us) needed for IR to chill and calculate the detected data

// Angle if there is no ball
#define IR_NO_BALL 400

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

// IR variables
int IRpins[24] = {IR_0, IR_1, IR_2, IR_3, IR_4, IR_5, IR_6, IR_7, IR_8, IR_9, IR_10, IR_11, IR_12, IR_13, IR_14, IR_15, IR_16, IR_17, IR_18, IR_19, IR_20, IR_21, IR_22, IR_23};
unsigned short ballAngle, realBallStrength, realBallAngle, lastAngle;
float ballStrength, ballDistance;
int noValsCounter, loopcounter, lastangle, ballstatus;
uint16_t angle = 0;
float strength = 0;
float angle_kp[3];

uint16_t values[IR_NUM] = {0};       // Sensor values as percentages
uint16_t sortedValues[IR_NUM] = {0}; // Sorted values (highest to lowest)
uint8_t indexes[IR_NUM] = {0};       // Indexes of sensor numbers in sorted list
uint16_t IRCounter = 0;              // Number of reads

float tempValues[IR_NUM] = {0}; // Raw sensor values after read

uint16_t IRgetAngle()
{
  return angle;
}

float IRgetStrength()
{
  // return strength;
  return strength;
}

void initIR()
{
  for (uint8_t i = 0; i < IR_NUM; i++)
  { // declare all as input for all the digitalpins
    pinMode(IRpins[i], INPUT);
  }
}

void readIR(int n)
{
  for (int j = 0; j < IR_NUM; j++)
  {
    tempValues[j] += digitalReadFast(PinName(IRpins[j])) ^ 1; // bitwise function: +1 to digitalread value everytime so it will be 1,2,3,4,5... btw i changed this to digitalreadfast(PinName(IRpins[j])) insted of digitalRead(IRpins[j]) because it is giving me an error havent tested it yet but yes
  }
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

  for (int i = 0; i < IR_NUM; i++)
  {
    s += sortedValues[i]; // addition of all values in the array and sum up as 's'
  }
  for (int i = 0; i < n; i++)
  {
    t += sortedValues[i];
  }
  for (int i = 0; i < IR_NUM; i++)
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
          angle = indexes[0] * 15;
          lastangle = angle;
          // Serial.println("haha");
        }
      }

      else
      {
        for (int i = 0; i < 3; i++)
        {
          angle_kp[i] = indexes[i] * sortedValues[i] * 15 / (sortedValues[0] + sortedValues[1] + sortedValues[2]);
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

void processballstrength()
{
  if (noValsCounter > 2)
  {

    ballstatus = 1; // if far away return 1
  }
  else
  {

    ballstatus = 0;
  }
}

void processIR()
{
  // Complete a reading of the sensors after a certain amount of individual readings, sensor values are now stored in the values array until the next complete read
  for (uint8_t i = 0; i < IR_NUM; i++)
  {
    //
    values[i] = 100 * (double)tempValues[i]; // multiply each value in the array by 100
    tempValues[i] = 0;                       // reset values here
    sortedValues[i] = 0;
    indexes[i] = 0;
  }
  IRsortvalues();
  IRcalculateanglestrength(BEST_IR_NUMBER);
}

void setup()
{
  Serial1.begin(9600);
  // initIR();
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, HIGH);
  delay(1000);
  digitalWrite(PC13, LOW);
  Serial1.println("Inshallah");
}

void loop()
{
  // readIR(24);
  Serial1.println("Inshallah");
  // processIR();
  // ballAngle = IRgetAngle();
  // ballStrength = IRgetStrength();
  // Serial1.println(ballAngle);
  // Serial1.println(ballStrength);
}