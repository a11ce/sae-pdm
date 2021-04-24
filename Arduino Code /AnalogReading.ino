void setup(){
Serial.begin(9600); //this is default?
delay(3000);
int sensorValue = analogRead(A6); //
  //receives a value 0-1023 which is the voltage??? On a   
//weird scale
  //can be A0-A14 on Mega we are focused on A6 and A7??

float voltage= sensorValue * (5.0 / 1023.0);
  // ’normalizes’ Voltage in terms of volts. Operating voltage of Mega is 5
//Voltage divider does something so that our value isn’t straight up 5??
voltage = voltage * 4; //since our v divider is approx /4, test 
Serial.println(voltage); //should output to IDE as txt file?
}

void loop(){




}
