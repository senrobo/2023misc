// declare libraries here //

#include <i2c_t3.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055_t3.h>
#include <utility/imumaths.h>
#include <NewPing.h>
#include <math.h>


//declare light variables here //
  // light ring pins, MUX control pins (s0 to s3 for top and bot clusters, MUX signature pin 1 //
const int s0 = 6;
const int s1 = 7;
const int s2 = 8;
const int s3 = 11;
const int SIG_1 = A21;

  // s4 to s7 for left and right clusters, MUX signature pin 2 //
const int s4 = 12;
const int s5 = 28;
const int s6 = 29;
const int s7 = 30;
const int SIG_2 = A22;
  // MUX binary address to access each port //
const int muxVals[16][4]={{0,0,0,0},{1,0,0,0},{0,1,0,0},{1,1,0,0},{0,0,1,0},{1,0,1,0},{0,1,1,0},
{1,1,1,0},{0,0,0,1},{1,0,0,1},{0,1,0,1},{1,1,0,1},{0,0,1,1},{1,0,1,1},{0,1,1,1},{1,1,1,1}}; //can just dont include since im doing manual
int lightVals[28],lineOut=0;
int topOut; //account for lack of front ultra
const int lightgate = A9; //proximity sensor
int lightgateVal;

//ultra variables
int testVal, ultraVals[3], ultraOut[3], ultracheck;

//motors
const int FL_DIR = 24; const int FL_PWM = 2;
const int FR_DIR = 25; const int FR_PWM = 3;
const int BL_DIR = 26; const int BL_PWM = 4;
const int BR_DIR = 27; const int BR_PWM = 5; 

//movement variables
float fl, fr, bl, br; //float this, nvr declare these variables as integers as they will round up
int FLout, FRout, BLout, BRout;
int angVel, angleError;

//compass variables
float cmpangle, cmpoffset=0;
Adafruit_BNO055 bno = Adafruit_BNO055(WIRE_BUS, -1, BNO055_ADDRESS_A, I2C_MASTER, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_100, I2C_OP_MODE_ISR);

//IR variables
unsigned short  ballAngle, realBallStrength, realBallAngle, lastAngle;
float ballStrength, ballDistance;
  //define IR digital pins
#define IR_0 14
#define IR_1 15
#define IR_2 16
#define IR_3 17
#define IR_4 20
#define IR_5 21
#define IR_6 22
#define IR_7 31
#define IR_8 32
#define IR_9 33
#define IR_10 34
#define IR_11 35
#define IR_12 36
#define IR_13 37
#define IR_14 38
#define IR_15 39

int IRpins [16] = {14,15,16,17,20,21,22,31,32,33,34,35,36,37,38,39};
#define IR_NUM 16 //define number of sensors u are using
#define IR_NUM_MULTIPLIER 22.5 // (360 / IR_NUM)
#define BEST_IR_NUMBER 3 // Number of strongest sensors used to calculate angle and strength
#define IR_TIMER_PERIOD_NUMBER 38 //mininum number of periods (of 833us) needed for IR to chill and calculate the detected data
#define LED_BLINK_TIME_SLAVE_SENSOR 800000

  //Angle if there is no ball
#define IR_NO_BALL 400


  //IR math stuff
#define MATH_E 2.7182818284590452353602874713527
#define TO_RADIANS 0.01745329251994329576923690768489
#define TO_DEGREES 57.295779513082320876798154814105

  // these functions may or may not be useful //
int mod(int x, int m) {
  int r = x % m; //calculate remainder when 1 integer is divided by another
  return r < 0 ? r + m : r;
}

double doubleMod(double x, double m) {
  double r = fmod(x, m);
  return r < 0 ? r + m : r;
}

double degreesToRadians(double degrees) {
  return degrees * TO_RADIANS;
}

double radiansToDegrees(double radians) {
  return radians * TO_DEGREES;
}

  // essentially sorting indexes in an array from largest to lowest //
#define ARRAYLENGTH(array) (sizeof(array) / sizeof(array[0]))
#define ARRAYSHIFTDOWN(a, lower, upper){          \
    if (upper == (sizeof(a)/sizeof(a[0])) - 1){   \
        for (int q = upper - 1; q >= lower; q--){ \
            *(a + q + 1) = *(a + q); }            \
    } else{                                       \
        for (int q = upper; q >= lower; q--){     \
            *(a + q + 1) = *(a + q); }}}

int mod(int x, int m);
double doubleMod(double x, double max);

double degreesToRadians(double degrees);
double radiansToDegrees(double radians);

// modified IR library functions //
  uint16_t getAngle();
  float getStrength();

  uint16_t values[IR_NUM] = { 0 }; // Sensor values as percentages
  uint16_t sortedValues[IR_NUM] = { 0 }; // Sorted values (highest to lowest)
  uint8_t indexes[IR_NUM] = { 0 }; // Indexes of sensor numbers in sorted list
  uint16_t IRCounter = 0; // Number of reads

  float tempValues[IR_NUM] = { 0 }; // Raw sensor values after read

  uint16_t angle = 0;
  float strength = 0;

  // Scaled sin and cos tables
  double scaledSin[IR_NUM] = { 0 };
  double scaledCos[IR_NUM] = { 0 };



 // Timer class/library, check if a certain time has elapsed //
class Timer {
public:
    Timer(unsigned long duration);
    void update();
    bool timeHasPassed();
    bool timeHasPassedNoUpdate();

    void resetTime();
    unsigned long lastUpdate;

private:
    unsigned long timerDuration;
};


// Update IR sensors for a certain amount of time before computing ball data
Timer IRTimer(833 * IR_TIMER_PERIOD_NUMBER); //initialise the class
Timer ledTimer(LED_BLINK_TIME_SLAVE_SENSOR);
bool ledOn;


//random variables
float outBallAngle, outBallStrength,absBallAngle,absBallStrength,angularVel,robotAngle,lastangle;
unsigned long startTime, lastDetectTime, lastOutTime=0, lastInTime=0;
bool lineStop=false, goalfound=false, ballfound, ballcatch;
int ballstatus,lastRunningSpeed;
double balldistance;
int tempangle, indexpos,loopcounter,noValsCounter;
float angle_kp[3];
float lastRobotAngle;
int go_in,returned;

//control constants; figure these out
const float angular_kp = 0.7; //speed=50;kp=1.0; speed=80;kp=0.7; tune this if u want apply angular vel to robot
const float angle_correct_kp = 0.7;
const float baseRad = 0.10;
const float chaseball_kp = 1.75;
const int maxSpeed = 90;
const int minSpeed = 65;
const int speed = 82;
int runningSpeed = speed;

//variables to set pre-match
const int lightThresh[28] = {330,400,400,465,370,350,280,300,400,354,290,320,370,305,348,332,326,332,336,415,300,375,453,400,460,440,1023,1023};
int maxVals[28] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
int minVals[28] = {1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023};

//ultrasonic variables
const int ultraThreshMin[3] = {0,0,0};
const int ultraThreshMax[3] = {45,45,45};
const int ultraFieldCentre[3] = {60,106,55}; //to measure relative to position where u want robot to return to base
