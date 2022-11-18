#include "NewPing.h"

frontECHO = 10 frontTRIG = 11 backECHO = 28 backTRIG = 27 rightECHO = 46 rightTRIG = 45 leftECHO = 26 leftTRIG = 25 externalLED = 2 maxDist = 400

float frontDist float backDist float rightDist float leftDist

void setup()
{
  // put your setup code here, to run once:
  NewPing sonar1(frontTRIG, frontECHO, maxDist);
  NewPing sonar2(backTRIG, backECHO, maxDist);
  NewPing sonar3(leftTRIG, leftECHO, maxDist);
  NewPing sonar4(rightTRIG, rightECHO, maxDist);
  pinMODE(externalLED, OUTPUT);
}

void getDistance()
{
  // put your main code here, to run repeatedly:
  frontDist = sonar.ping_cm();
  backDist = sonar2.ping_cm();
  leftDist = sonar3.ping_cm();
  rightDist = sonar4.ping_cm();
}

void stateLocation(){
    
}
