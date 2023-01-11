void readnano() {
  Serial1.write(2);
  //Serial.println("a"); //uncomment to debug if program gets stuck at requesting data phase, if so, unpluig and replug cable to reboot whole system
   while (Serial1.available() < 3); //less than 3 byte
      for (int i=0; i<3; i++) {
        ultraVals[i] = Serial1.read();
       // Serial.print(ultraVals[i]); //uncomment to debug ultra vals 
        //Serial.print(" ");
      }
    //SeM rial.print("no.of bytes avail:");
    //Serial.println(Serial1.available());
   //Serial.println();
}
