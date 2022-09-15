void setup() {
  // put your setup code here, to run once:

  pinMode(12, OUTPUT); //buzzer
  pinMode(2, OUTPUT); //yellow led

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
  
//  digitalWrite(9, LOW);
//  digitalWrite(10, LOW);
//  digitalWrite(11, LOW);
  
  if(analogRead(A0) >= 60){
    digitalWrite(12, LOW); //buzzer off
    digitalWrite(2, HIGH); //led on
    
    }
    else{
      digitalWrite(2, LOW); //led off
      digitalWrite(12, HIGH); //buzzer on
    }
    
}
