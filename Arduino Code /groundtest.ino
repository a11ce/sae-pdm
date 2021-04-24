void setup() {
  // Basically same as high power test but with some different pins?
  // 48-49 to be grounded?
 
  pinMode(48,OUTPUT); 
  pinMode(49,OUTPUT); 
pinMode(31,OUTPUT); //just to on and off?

pinMode(14,OUTPUT); //LED
pinMode(19,OUTPUT); //LED

digitalWrite(48, LOW);
digitalWrite(49, LOW);
digitalWrite(19, HIGH);//LED on when code runs
}


void loop() {

for(;;){
digitalWrite(31, HIGH);
digitalWrite(14, LOW); 
delay(10000);
digitalWrite(31, LOW);
digitalWrite(14, HIGH);
delay(10000);
}

}
