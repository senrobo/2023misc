 void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200); //with nano
  pinMode(s0, OUTPUT); pinMode(s1, OUTPUT); pinMode(s2, OUTPUT); pinMode(s3, OUTPUT); pinMode(SIG_1, INPUT);
  pinMode(s4, OUTPUT); pinMode(s5, OUTPUT); pinMode(s6, OUTPUT); pinMode(s7, OUTPUT); pinMode(SIG_2, INPUT);
  digitalWrite(s0, LOW); digitalWrite(s1, LOW); digitalWrite(s2, LOW); digitalWrite(s3, LOW);
  digitalWrite(s4, LOW); digitalWrite(s5, LOW); digitalWrite(s6, LOW); digitalWrite(s7, LOW);
  //IR ring (init)
  initIR();
  pinMode(FL_DIR, OUTPUT); pinMode(FL_PWM, OUTPUT);
  pinMode(FR_DIR, OUTPUT); pinMode(FR_PWM, OUTPUT);
  pinMode(BL_DIR, OUTPUT); pinMode(BL_PWM, OUTPUT);
  pinMode(BR_DIR, OUTPUT); pinMode(BR_PWM, OUTPUT);
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000); //compass default i2c pins 18/19
  bno.begin(); //begin the compass
  delay(2000);
  bno.setExtCrystalUse(false); //see example code + depends if crystal is big enough
   /*uint8_t system, gyro, accel, mag = 0; //to test if compass fucks up
    while(gyro!=3 && mag!=3) {
    bno.getCalibration(&system, &gyro, &accel, &mag);
    Serial.println("callibration");
    }*/
  IRTimer.update();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  readIR(15);
  readIMU();
  processIMU();
  startTime=micros();
  if(IRTimer.timeHasPassed())  { //process after set time
    processIR();
    ballAngle = IRgetAngle();
    ballStrength = IRgetStrength();
    IRTimer.resetTime();
    }
  if (ledTimer.timeHasPassed()) {
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }
  readnano();
  readlight1();
  readlight2();
  chaseball();
  
  //caughtball();
  /*if (ballcatch>0)  {
    REE(); //charge for goal
  }*/
  //Serial.println(processlight());  
  if(processlight()>0)  { //outdetected
    digitalWrite(LED_BUILTIN, LOW);
    lastOutTime = millis();
    outBallAngle = ballAngle;
    processUltra();
     if (ultracheck != 0)  {
        out_correct();
      }
  }
  else outBallAngle = 0;
  if(ballAngle == 400 || outBallAngle >0)  returnBase();
  //Serial.println(processlight());
  //calibrate_light();
  //readnano();
  //returnBase();
  //readlight1();
  //readlight2();
 // printlight();
  move_OUT();
}
