void processUltra()  { //basicUltraCheck
  ultracheck = 0;
  int j = 0;
  for(int i=0; i<3; i++) {
    if(ultraVals[i] > ultraThreshMin[i] && ultraVals[i] < ultraThreshMax[i]) { //if ultra is between min and max, then add 1 to ultracheck
      ultracheck ++;
      ultraOut[j] = i; //add i to array "ultraOut" if its in between to determine which side it detects out first
      j++; //add 1 to increase position of the index in array "ultraOut" to determine which ultras are detecting out
    }
  }
}

//const int ultraThreshMin[4] = {0,0,0,0};
//const int ultraThreshMax[4] = {40,40,40,40};
//note that the field to line is 30cm, if <40 detected, then means robot is out

void returnBase() {
  float x, y;
  int diff0 = ultraVals[0] - ultraFieldCentre[0];  //left ultra diff
  int diff1 = ultraFieldCentre[1] - ultraVals[1];  //right ultra diff
  int diff2 = ultraFieldCentre[2] - ultraVals[2];  //bot ultra diff
  if(diff0 < 0 &&  diff2 < 0) {
    x = abs(diff0);
    y = abs(diff2);
    robotAngle =  (180 - atan(x/y) * 180 / 3.141592654);
    //Serial.print("a");
  }
  else if(diff0 < 0 && diff2 > 0) {
    x = abs(diff0);
    y = abs(diff2);
    robotAngle = (atan(x/y) * 180 / 3.141592654);
    //Serial.print("b");
  }
  else if(diff0 > 0 && diff2 > 0)  {
    x = diff0;
    y = diff2;
    robotAngle = (360 - atan(x/y) * 180 / 3.141592654);
    //Serial.print("c");
  }
  else if(diff0 > 0 && diff2 < 0) {
    x = diff0;
    y = abs(diff2);
    robotAngle = (180 + atan(x/y) * 180 / 3.141592654);
    //Serial.print("d");
  }
  else {
    robotAngle = 0;
  }
  if((abs(diff0) < 5 || abs(diff1) < 5) && abs(diff2) < 5)  {
    runningSpeed = 0;
    Serial.println("YOU BETTER STOP");
  }
  else  runningSpeed = 55;
  /*if (returned>3) {
    runningSpeed = 0;
    returned = 0;
  }*/
  angular_drive(runningSpeed,robotAngle,0);
  angle_correct();
  /*Serial.print(diff0);
  Serial.print(" | ");
  Serial.print(diff1);
  Serial.print(" | ");
  Serial.print(diff2);
  Serial.print(" | ");
  Serial.println(robotAngle);*/
}
