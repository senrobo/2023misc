void readlight1()  { 
//top
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  lightVals[0]=analogRead(SIG_1);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  lightVals[1]=analogRead(SIG_1);
  digitalWrite(s0, LOW);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  lightVals[2]=analogRead(SIG_1);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  lightVals[3]=analogRead(SIG_1);
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  lightVals[4]=analogRead(SIG_1);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  lightVals[5]=analogRead(SIG_1);
  digitalWrite(s0, LOW);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  lightVals[6]=analogRead(SIG_1);
//bot  
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  lightVals[7]=analogRead(SIG_1);
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  lightVals[8]=analogRead(SIG_1);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  lightVals[9]=analogRead(SIG_1);
  digitalWrite(s0, LOW);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  lightVals[10]=analogRead(SIG_1);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  lightVals[11]=analogRead(SIG_1);
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  lightVals[12]=analogRead(SIG_1);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  lightVals[13]=analogRead(SIG_1);

}
void readlight2() { //right then left
  /*for (int i=0; i<14; i++) {
    digitalWrite(s4, muxVals[i][0]);//since muxVals is an array where [ (channel no.)(control pins i.e. a4-s3) ]
    digitalWrite(s5, muxVals[i][1]);//basically the forloop cycles thru the number of channels you want to read (14) thru digitalWrite the 4 signal channels
    digitalWrite(s6, muxVals[i][2]);
    digitalWrite(s7, muxVals[1][3]);
    delayMicroseconds(1);
    lightVals[i+14]=analogRead(SIG_2);//analogRead the signalchannel pin; then write into the array one by one */
//right
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
  lightVals[14]=analogRead(SIG_2);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
  lightVals[15]=analogRead(SIG_2);
  digitalWrite(s4, LOW);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
  lightVals[16]=analogRead(SIG_2);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
  lightVals[17]=analogRead(SIG_2);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, LOW);
  lightVals[18]=analogRead(SIG_2);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, LOW);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, LOW);
  lightVals[19]=analogRead(SIG_2);
  digitalWrite(s4, LOW);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, LOW);
  lightVals[20]=analogRead(SIG_2);
//left
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, LOW);
  lightVals[21]=analogRead(SIG_2);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, HIGH);
  lightVals[22]=analogRead(SIG_2);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, HIGH);
  lightVals[23]=analogRead(SIG_2);
  digitalWrite(s4, LOW);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, LOW);
  digitalWrite(s7, HIGH);
  lightVals[24]=analogRead(SIG_2);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, LOW);
  digitalWrite(s7, HIGH);
  lightVals[25]=analogRead(SIG_2);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);
  lightVals[26]=analogRead(SIG_2);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, LOW);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);
  lightVals[27]=analogRead(SIG_2);
}

void printlight() {
  for(int i=0; i<28; i++)  {    //20 (last one on the right) has low diff, 7 and 14 is usually low but diff is ok
    Serial.print(lightVals[i]);
    Serial.print(" ");
  }
  Serial.println();
}
int processlight() { //0=in, 8=bot, 15=right, 1=top, 22=left; returns the first sensor it detects out
  for(int i=0; i<7;i++) {
    if(lightVals[i]>lightThresh[i]) {
    topOut++; 
    }
  }
  for(int i=0;i<28;i++) {
    if(lightVals[i]>lightThresh[i]) {
      return i+1;
    }
  }
  return 0;

    /*for(int i=7;i<14;i++) {
      if(lightVals[i]>lightThresh[i]) botOut++;
  }
    for(int i=21; i<28;i++) {
      if(lightVals[i]>lightThresh[i]) leftOut++;
  }
    for(int i=14; i<21;i++) {
      if(lightVals[i]>lightThresh[i]) rightOut++;
    }*/
}

void caughtball() {
  lightgateVal = analogRead(A9);
  if(lightgateVal<52)  ballcatch = 1;
  else ballcatch = 0;
  Serial.println(ballcatch);
}


void resetlight() {
  topOut=0;
}


void calibrate_light(){
  int diff;
  int vals[28];
  //Serial.print("max: ");
  for (int i=0;i<28;i++){
    if (lightVals[i]>maxVals[i]) maxVals[i]=lightVals[i];

    if (lightVals[i]<minVals[i]) minVals[i]=lightVals[i];
   // diff=maxVals[i]-minVals[i];
  }
  for (int i=0;i<28;i++){
    vals[i]=round(((maxVals[i]+minVals[i])/2));
    Serial.print(vals[i]);
    Serial.print(',');
  }
  Serial.println();
}
