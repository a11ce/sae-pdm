void setup() {
  
for(int i=41;i<=49;i++){ //all of th pins tested
  pinMode(i,OUTPUT); 
}
const int LED = 14;
pinMode(LED,OUTPUT); //LED
pinMode(19,OUTPUT); //LED
pinMode(20,OUTPUT); //LED to try and turn off (by default is on (bug with board)
pinMode(21,OUTPUT); //LED to try and turn off (by default is on (bug with board)

pinMode(48,OUTPUT); //to set low always
pinMode(49,OUTPUT); 
digitalWrite(48, LOW);
digitalWrite(49, LOW);
digitalWrite(19, HIGH);//LED on when code runs
digitalWrite(20, LOW);
digitalWrite(21, LOW);
}


void loop() {
  /*
for(int i=41;i<47;i++){
digitalWrite(i, HIGH);
delay(500);
digitalWrite(i, LOW);
delay(500);
}
*/ 
//just checking voltage reading instead 
const int LED = 14;
for (;;){
for(int i=41;i<=47;i++){
digitalWrite(i, HIGH);
digitalWrite(LED, LOW);
  }
   delay(10000);
for(int i=41;i<=47;i++){
digitalWrite(i, LOW);
digitalWrite(LED, HIGH);
}
delay(10000);
}

}
