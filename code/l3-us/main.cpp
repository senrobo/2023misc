#include <NewPing.h>

#define US_NUM 4
#define MAX_DIST 400cm

NewPing sonar[US_NUM] = {
    NewPing(11, 10, MAX_DIST); // Front US1
NewPing(27, 28, MAX_DIST);     // Back US3
NewPing(25, 26, MAX_DIST);     // Left US4
NewPing(45, 46, MAX_DIST);     // Right US2
}

char sonarDist[1] = 0;
int usDist[4] = [ 0, 0, 0, 0 ];

void setup()
{
  // put your setup code here, to run once:
  Serial1.begin(115200); // For communication with the programmer
  Serial2.begin(115200); // For commuciation with the Teensy
}

void loop()
{
  // put your main code here, to run repeatedly:
  for (uint8_t i = 0; i < US_NUM; i++)
  {
    delay(29);
    // Serial.print(i);
    // Serial.print("=");
    // Serial.print(sonar[i].ping_cm());
    // Serial.print("cm ");
    usDist[i] = sonar[i].ping_cm();
  };
  for (int i = 0; i < 4; i++)
  {
    Serial2.write(sonarDist, 1);
  }
}
