#include <Arduino.h>

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

int IRpins[24] = {PA5, PA4, PA1, PA0, PC15, PC14, PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PB14, PB13, PB12, PB11, PB10, PB2, PB1, PB0, PA7, PA6};

#define IR_NUM 24                 // define number of sensors u are using
#define IR_NUM_MULTIPLIER 15      // (360 / IR_NUM)
#define BEST_IR_NUMBER 3          // Number of strongest sensors used to calculate angle and strength
#define IR_TIMER_PERIOD_NUMBER 38 // mininum number of periods (of 833us) needed for IR to chill and calculate the detected data
#define LED_BLINK_TIME_SLAVE_SENSOR 800000

// Angle if there is no ball
#define IR_NO_BALL 400

// IR math stuff
#define MATH_E 2.7182818284590452353602874713527
#define TO_RADIANS 0.01745329251994329576923690768489
#define TO_DEGREES 57.295779513082320876798154814105

void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}