void readIMU()  {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); //obtain euler vector
  cmpangle = euler.x();
  if(Wire.getError()>0) digitalWrite(LED_BUILTIN,LOW);
}

void processIMU() {
  if (cmpangle<cmpoffset) {
    cmpangle+=360;
  }
  cmpangle -= cmpoffset; //cmpangle = cmpangle - cmpoffset
  if (cmpangle > 180) angleError = cmpangle-360; //convert angle to degrees from north
  else angleError = cmpangle;
}
