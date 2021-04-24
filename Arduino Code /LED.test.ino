void setup() {
for(int i = 14; i<=21; i++){
  pinMode(i,OUTPUT); }

}

void loop() {
//test LEDs (pins 14-21)
for(int i=0; i<=3; i++){
digitalWrite(14, HIGH);
digitalWrite(15, HIGH);
digitalWrite(16, HIGH);
digitalWrite(17, HIGH);
digitalWrite(18, HIGH);
digitalWrite(19, HIGH);
digitalWrite(20, HIGH);
digitalWrite(21, HIGH);
delay(2000);
digitalWrite(14, LOW);
digitalWrite(15, LOW);
digitalWrite(16, LOW);
digitalWrite(17, LOW);
digitalWrite(18, LOW);
digitalWrite(19, LOW);
digitalWrite(20, LOW);
digitalWrite(21, LOW);
delay(500);
}
exit(0);
}
