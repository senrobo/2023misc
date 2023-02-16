#ifdef IR_H
#define IR_H

#include <Arduino.h>

#define IR_ONE PA5
#define IR_TWO PA4
#define IR_THREE PA1
#define IR_FOUR PA0
#define IR_FIVE PC15
#define IR_SIX PC14
#define IR_SEVEN PB9
#define IR_EIGHT PB8
#define IR_NINE PB7
#define IR_TEN PB6
#define IR_ELEVEN PB5
#define IR_TWELVE PB4
#define IR_THIRTEEN PB3
#define IR_FOURTEEN PA15
#define IR_FIFTEEN PB14
#define IR_SIXTEEN PB13
#define IR_SEVENTEEN PB12
#define IR_EIGHTEEN PB11
#define IR_NINETEEN PB10
#define IR_TWENTY PB2
#define IR_TWENTYONE PB1
#define IR_TWENTYTWO PB0
#define IR_TWENTYTHREE PA7
#define IR_TWENTYFOUR PA6

#define IR_NUM 24
#define IR_NUM_MULTIPLIER 15
#define BEST_IR_NUM 3

unsigned short ballAngle, realBallStrength, realBallAngle, lastAngle;
float ballStrength, ballDistance;

class IR
{
public:
    void initIR();
    void readIR(int n);
    void processIR();
    void sortIRValues();
    void calculateIRStrength();
}