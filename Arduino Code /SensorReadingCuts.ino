//cuts are made based on temperature readings

float SPEED_S ; //wheel speed
float BRKTEMP_S; //brake temp
float POT_S; //shock pot
float BRKP_S; //brake pressure
//steering angle?  gona skip this
//Throttle posn  MAYBE IMPLEMENT LATER
float OILP_S; //oil press
float OILTMP_S; //oil temp
float CTMP_S; //coolant temp
float INTP_S; //intake press
float INTT_S; //intake temp
float L_S; //lambda
float PTUB_S; // pilot tube
float SGAUGE_S; //Strain Gauges
float ; //accelerometer
float GSCOPE_S; //gyroscope
void setup() {


}
bool SAFE(){
//read the sensor value //IDK HOW TO DO THIS 
//return true if everything is good. Kill main if not

//NEED TO ADD THE BAD OR GOOD VALUES
if(SPEED_S){
  return false;
}
if(BRKTMP_S){
  return false;
}
if(POT_S){
  return false;
}
if(BRKP_S){
  return false;
}
if(BRKTMP_S){
  return false;
}
if(BRKTMP_S){ //THROTTLE?
  return false;
}
if(OILP_S){
  return false;
}
if(OILTMP_S){
  return false;
}
if(CTMP_S){
  return false;
}
if(INTP_S){
  return false;
}
if(INTT_S){
  return false;
}
if(L_S){
  return false;
}
if(PTUB_S){
  return false;
}
if(SGAUGE_S){
  return false;
}
if(GSCOPE_S){
  return false;
}

}

void loop() {
if (!SAFE()){
//activate kill switch?

}
}
