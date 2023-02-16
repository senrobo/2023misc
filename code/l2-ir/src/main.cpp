#include <Arduino.h>
#include <IR.h>
#include <IR.cpp>

void setup()
{
  // put your setup code here, to run once:
  Serial2.begin(115200); // Initialize Serial2 (USART2) for IR
  initIR();
}

void loop()
{
  // put your main code here, to run repeatedly:
  readIR(IR_NUM);
  Serial2.write(IR_NUM);
}