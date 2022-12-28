#include "NewPing.h"

#define frontECHO = 10
#define frontTRIG = 11
#define backECHO = 28
#define backTRIG = 27
#define rightECHO = 46
#define rightTRIG = 45
#define leftECHO = 26
#define leftTRIG = 25
#define externalLED = 2
#define maxDist = 400

float frontDist, backDist, rightDist, leftDist;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  NewPing sonar1(frontTRIG, frontECHO, maxDist);
  NewPing sonar2(backTRIG, backECHO, maxDist);
  NewPing sonar3(leftTRIG, leftECHO, maxDist);
  NewPing sonar4(rightTRIG, rightECHO, maxDist);
  pinMODE(externalLED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  frontDist = sonar.ping_cm();
  backDist = sonar2.ping_cm();
  leftDist = sonar3.ping_cm();
  rightDist = sonar4.ping_cm();
  Serial.write(frontDist);
}

