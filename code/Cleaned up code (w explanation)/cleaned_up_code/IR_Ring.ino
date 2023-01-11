void initIR() {
  for (uint8_t i = 0; i < IR_NUM; i++) { //declare all as input for all the digitalpins
    pinMode(IRpins[i], INPUT);
  }
}

void readIR (int n) {
  for (int i = 0; i < n; i++)  {
    for (int j=0; j<16; j++) {
      tempValues[j] += digitalReadFast(IRpins[j]) ^ 1; //bitwise function: +1 to digitalread value everytime so it will be 1,2,3,4,5...
      delayMicroseconds(1); //may not be neccessary, can just delete if the data is ok
    }
    IRCounter++;
  }
}

void processIR() {
  // Complete a reading of the sensors after a certain amount of individual readings, sensor values are now stored in the values array until the next complete read
  for (uint8_t i = 0; i < IR_NUM; i++) {
    //
    values[i] = 100 * (double)tempValues[i] / (double)IRCounter; //multiply each value in the array by 100 then divide it by number of times it read the sensors
    tempValues[i] = 0; //reset values here
    sortedValues[i] = 0;
    indexes[i] = 0;
  }

  IRCounter = 0;

  IRsortvalues();
  IRcalculateanglestrength(BEST_IR_NUMBER);
}
void IRsortvalues() {
  // Sort the TSOP values from greatest to least in sortedFilteredValues
  // and sort the TSOP indexes from greatest to least strength in indexes (array positions)

  for ( uint8_t i = 0; i < IR_NUM; i++) {
    for ( uint8_t j = 0; j < IR_NUM; j++) {
      if (values[i] > sortedValues[j]) {
        // We've found our place!
        // Shift elements from index j down
        if (j <= i) {
          // Make sure we only shift what is needed
          ARRAYSHIFTDOWN(sortedValues, j, i); //sort strength from weakest to strongest in the array
          ARRAYSHIFTDOWN(indexes, j, i); //sort the indexes
        }

        sortedValues[j] = values[i];
        indexes[j] = i;
        break;
      }
    }
  }
}

void IRcalculateanglestrength(int n) {
  // Cartesian addition of best n TSOPs
  float s = 0;
  float t = 0;
  noValsCounter = 0;
  
  for (int i = 0; i < 16; i++)  {
    s += sortedValues[i]; //addition of all values in the array and sum up as 's'
  }
  for (int i = 0; i < n; i++)  {
    t += sortedValues[i];
  }
  for (int i = 0; i < 16; i++)  {
    if(sortedValues[i] == 0) noValsCounter++;
  }
  strength = t / s;  //calculate strength as a proportion number, between 0 and 1 ***check reliability, didnt end up using it anyways lmao
  if (loopcounter < 1) {
    if (s == 0)  {
      angle = lastangle;
      //Serial.println("is there ball??");
      loopcounter++;
    }
    else  { 
      if (indexes[0] == 0 || indexes[1] == 0 || indexes[2] == 0) {
        if (sortedValues[0] > 60)  {
          angle = 0;
          //Serial.println("front");
        }
        else {
          angle = indexes[0] * 22.5;
          lastangle = angle;
          //Serial.println("haha");
        }
      }
      
      else  {
        for (int i = 0; i < 3; i++) {
          angle_kp[i] = indexes[i] * sortedValues[i] * 22.5 / (sortedValues[0] + sortedValues[1] + sortedValues[2]);
          }
        angle = angle_kp[0] + angle_kp[1] + angle_kp[2];
        lastangle = angle;
        //Serial.println("ree");
      } //end of else statement for normal angle calculation
       loopcounter=0; 
    }  //end of if statement if first 3 IRs = 0
   
  }  //end of loopcounter <1

  
  else if (loopcounter >= 1)  {
    if (sortedValues[0] > 0)  {
      angle = 0;
      loopcounter = 0;
    }
    else  {
      angle = 400;  //no ball detected
      lastangle = angle;
      //Serial.println("no ball");
    }
    loopcounter = 0;
  }
  else;

  //Serial.println(loopcounter); //HELP ME
}

uint16_t IRgetAngle() {
  return angle;
}

float IRgetStrength() {
  //return strength;
  return strength;
}

//IR timer stuff
Timer::Timer(unsigned long duration) {
  timerDuration = duration;
}

void Timer::update() {
  lastUpdate = micros();
}

bool Timer::timeHasPassed() {
  if (micros() - lastUpdate > timerDuration) {
    lastUpdate = micros();
    return true;
  }

  return false;
}

bool Timer::timeHasPassedNoUpdate() {
  return micros() - lastUpdate > timerDuration;
}

void Timer::resetTime() {
  lastUpdate = micros();
}

void processballstrength()  {
  if (noValsCounter > 2) ballstatus = 1; //if far away return 1
  else ballstatus = 0;
}
