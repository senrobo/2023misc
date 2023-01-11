  void angular_drive(int spd, float angle, float angVel) {
  float radAng = (90+angle)*3.141592654/180; //convert angle to vector coordinates

  float x_co = sin(radAng);
  float y_co = cos(radAng); //zero
  fl = -(-0.707*x_co+0.707*y_co + baseRad*angVel);  //resolve wheel vectors
  fr = 0.707*x_co+0.707*y_co + baseRad*angVel;
  bl = -(-0.707*x_co-0.707*y_co + baseRad*angVel);
  br = 0.707*x_co-0.707*y_co + baseRad*angVel;

  float factor = spd / max(max(abs(fl), abs(fr)), max(abs(bl), abs(br))); //scale all to speed
  FLout = round(factor * fl);
  FRout = round(factor * fr);
  BLout = round(factor * bl);
  BRout = round(factor * br);
}

void move_OUT() {
  analogWrite(FL_PWM, abs(FLout));
  if (FLout > 0) digitalWrite(FL_DIR, HIGH);
  else digitalWrite(FL_DIR, LOW);

  analogWrite(FR_PWM, abs(FRout));
  if (FRout > 0) digitalWrite(FR_DIR, LOW);
  else digitalWrite(FR_DIR, HIGH);

  analogWrite(BL_PWM, abs(BLout));
  if (BLout > 0) digitalWrite(BL_DIR, LOW);
  else digitalWrite(BL_DIR, HIGH);

  analogWrite(BR_PWM, abs(BRout));
  if (BRout > 0) digitalWrite(BR_DIR, LOW);
  else digitalWrite(BR_DIR, HIGH);
}

void angle_correct() {
  FLout -= angleError * angle_correct_kp; //FLout = FLout - (angleError * angle_correct_kp)
  BLout -= angleError * angle_correct_kp;
  FRout += angleError * angle_correct_kp; //FLout = FLout + (angleError * angle_correct_kp)
  BRout += angleError * angle_correct_kp;
}

void out_correct() {
  
  if (ultracheck == 1) { //if only 1 ultra detects out
    if(topOut > 0)  angular_drive(speed, 180, 0);
    else if (ultraOut[0] == 0) angular_drive(speed, 90, 0); //if left ultra is out, move right
    else if (ultraOut[0] == 1) angular_drive(speed, 270, 0); //if right ultra is out, move left
    else if (ultraOut[0] == 2) angular_drive(speed, 0, 0); //if back ultra detects out, move forward back in (either stuck in goalpost or out beside goalpost)
  }
  else if (ultracheck == 2) { //if 2 ultra detects out
    if (topOut > 0) { angular_drive(speed, 180, 0);
      if (ultraOut[1] == 0) angular_drive(speed, 135, 0); //if front+left sense out (top left corner)
      else if (ultraOut[1] == 1) angular_drive(speed, 225, 0); //if front+right sense out (top right corner)
      else if (ultraOut[1] == 2) angular_drive(0, 0, 0); //back and front detected, stop on line????????? possible to remove this line
    }
    else if (ultraOut[0] == 1) {  //if left ultra detects out
      //if (ultraOut[1] == 2) angular_drive(speed, 180 - angleError, 0); check this
      if(ultraOut[1] == 3) angular_drive(speed, 45, 0); //sense 1 and 3, bot left corner
    }
    else angular_drive(speed, 315, 0); //sense 2 and 3, bot right; save time by not check right ultra in 'else if(ultraOut[0] ==1)'
  }
  
  else if (ultracheck == 3) { //3 detected, check this one
    if (ultraOut[0] == 0) {
      if (ultraOut[1] == 1) {
        if (ultraOut[2] == 2) angular_drive(speed, 180, 0); //0,1,2, assume 0, in between opponent bot on right side of field???
        else angular_drive(speed, 90, 0); //0,1,3, assume 1
      }
      else angular_drive(speed, 270, 0); //0,2,3 assume 2
    }
    else angular_drive(speed, 0, 0); //1,2,3 assume 3
  }
  else {
    angular_drive(0, 0, 0); //all 3 detected
  }
  //angle_correct(); //angle correct alr present in out_correct
  topOut = 0;
}


void chaseball()  {
      //processballstrength; ballstatus = 1 if far,  0 if close
    processballstrength();
    if(ballAngle >= 337 && ballAngle <= 22) {
        if(indexes[0] == 0) {  //if ball is infront (front 3 sensors are the strongest)
          robotAngle = 0;
          //Serial.println("front");
        }
        else if(indexes[0] == 1) {
          robotAngle = 30;
          //Serial.println("frontR");
        }
        else if(indexes[0] == 15) {
          robotAngle = 330;
          //Serial.println("frontL");
        }
      else  {
        robotAngle = ballAngle; 
        //Serial.println("fuck");
      }
      runningSpeed = maxSpeed;
      lastRobotAngle = robotAngle;
      lastRunningSpeed = runningSpeed;
    }
    else if(ballAngle > 22 && ballAngle < 160)  {
      if(ballstatus == 1)  robotAngle = ballAngle + 25;
      else  {
        if(ballAngle > 22 && ballAngle < 45)  robotAngle = ballAngle * 2.4;
        if(ballAngle >= 45 && ballAngle < 80) robotAngle = ballAngle * 1.7;
        if(ballAngle >=80 && ballAngle <120)  robotAngle = ballAngle * 1.4;
        if(ballAngle >=120 && ballAngle <160)  robotAngle = ballAngle * 1.25;
      }
      runningSpeed = speed;
      lastRobotAngle = robotAngle;
      lastRunningSpeed = runningSpeed;
      //Serial.println("ball is left side");
    }
    
    else if(ballAngle > 200 && ballAngle < 337)  {
      if(ballstatus == 1) robotAngle = ballAngle - 25;
      else  {
        if(ballAngle > 200 && ballAngle < 260)  {
          robotAngle = ballAngle * 0.80;
          }
        if(ballAngle >= 260 && ballAngle < 337)  {
          robotAngle = ballAngle * 0.68;
        }
      }
      runningSpeed = speed;
      lastRobotAngle = robotAngle;
      lastRunningSpeed = runningSpeed;
      //Serial.println("ball is right side");
    }
    
    else if(ballAngle >= 160 && ballAngle <= 200)  {
      if(ballstatus == 1) robotAngle = 180;
      else  {
      robotAngle = ballAngle * 1.35;
       }
      runningSpeed = maxSpeed;
      lastRobotAngle = robotAngle;
      lastRunningSpeed = runningSpeed;
      //Serial.println("ball is behind");
    }

    else if(ballAngle == 400) {
      runningSpeed = 0;
      robotAngle = 0;
      //Serial.println("noball");
    }
    
    else  {
      if(indexes[0] == 0) {  //if ball is infront (front 3 sensors are the strongest)
        robotAngle = 0;
        //Serial.println("front");
        runningSpeed = maxSpeed;
      }
      else if(indexes[0] == 1) {
        robotAngle = 30;
        //Serial.println("frontR");
        runningSpeed = maxSpeed;
      }
      else if(indexes[0] == 15) {
        robotAngle = 330;
        //Serial.println("frontL");
        runningSpeed = maxSpeed;
      }
      else  {
      robotAngle = lastRobotAngle;
      runningSpeed = lastRunningSpeed;
      //Serial.println("lastball"); 
      }
  }
    
    angular_drive(runningSpeed,robotAngle,0);
    angle_correct();
    resetlight();
    //Serial.println(robotAngle);
}

void REE()  { //smah the goal
  int LDiff = 100 - ultraVals[0];
  int RDiff = 100 - ultraVals[1];
  int BDiff = 160 - ultraVals[2];
  if(LDiff>RDiff) { //robot is on right side of field, charge left
    if(BDiff<70)  robotAngle = 350;
    else  robotAngle = 335;
  }
  else if(LDiff<RDiff)  { //robot is on left side of field, charge right
    if(BDiff<70)  robotAngle = 10;
    else  robotAngle = 25;
  }
  else  {  //assuming its equal on both sides???
    robotAngle = 0;
  }
  angular_drive(maxSpeed,robotAngle,0);
  angle_correct();
}


void circular_motion()  {
  for (int i=0;i<360;i++)  {
    readIMU();
    processIMU();
    angular_drive(65,i,0);
    angle_correct();
    delay(2);
    move_OUT();
  }
}

/*void trackball()  {
    if(ballAngle >= 337 && ballAngle <= 22) {
        if(indexes[0] == 0) {  //if ball is infront (front 3 sensors are the strongest)
          robotAngle = 0;
          Serial.println("front");
        }
        else if(indexes[0] == 1) {
          robotAngle = 90;
          Serial.println("frontR");
        }
        else if(indexes[0] == 15) {
          robotAngle = 270;
          Serial.println("frontL");
        }
      else;
      runningSpeed = speed;
      lastRobotAngle = robotAngle;
      lastRunningSpeed = runningSpeed;
    }
    else if(ballAngle > 22 && ballAngle < 160)  {
        if(ballAngle > 22 && ballAngle < 75)  {
          robotAngle = 90;
          runningSpeed = speed;
        }
        if(ballAngle >=75 && ballAngle <160)  {
          robotAngle = 90;
          runningSpeed = maxSpeed;
        }
      lastRobotAngle = robotAngle;
      lastRunningSpeed = runningSpeed;
      Serial.println("ball is left side");
    }
    
    else if(ballAngle > 200 && ballAngle < 337)  {
        if(ballAngle > 200 && ballAngle < 260)  {
          robotAngle = 270;
          runningSpeed = speed;
          }
        if(ballAngle >= 260 && ballAngle < 337)  {
          robotAngle = 270;
          runningSpeed = maxSpeed;
        }
      lastRobotAngle = robotAngle;
      lastRunningSpeed = runningSpeed;
      Serial.println("ball is right side");
    }
    
    else if(ballAngle >= 160 && ballAngle <= 200)  {
      robotAngle = ballAngle * 1.35;
      runningSpeed = 100;
      lastRobotAngle = robotAngle;
      lastRunningSpeed = runningSpeed;
      Serial.println("ball is behind");
    }

    else if(ballAngle == 400) {
      runningSpeed = 0;
      robotAngle = 0;
      Serial.println("noball");
    }
    
    else  {
      if(indexes[0] == 0) {  //if ball is infront (front 3 sensors are the strongest)
        robotAngle = 0;
        Serial.println("front");
      }
      else if(indexes[0] == 1) {
        robotAngle = 90;
        Serial.println("frontR");
      }
      else if(indexes[0] == 15) {
        robotAngle = 270;
        Serial.println("frontL");
      }
      else  {
      robotAngle = lastRobotAngle;
      runningSpeed = lastRunningSpeed;
      Serial.println("lastball"); 
      }
      runningSpeed = speed;
  }
    angular_drive(runningSpeed,robotAngle,0);
    angle_correct();
    resetlight();
    //Serial.println(robotAngle);
}*/
