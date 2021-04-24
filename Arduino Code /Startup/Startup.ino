#define TEST_MODE

#ifdef TEST_MODE
  // TESTING LED VALUES - COMMENT OUT IN REAL USE
  // CUT 1
  const int SPEED_SENSE_OUT = 14;
  const int TEMP_SENSE_OUT = 15;
  const int POT_SENSE_OUT = 16;
  const int BRAKE_PRESSURE_OUT = 17;
  // CUT 2
  const int RAD_FAN_OUT  = 18;
  const int BRAKELIGHT_OUT = 19;
  // FINAL CUT
  const int COOLANT_PUMP_OUT = 20;
#else
  // REAL PORTS
  // CUT 1
  const int SPEED_SENSE_OUT = 33;
  const int TEMP_SENSE_OUT = 35;
  const int POT_SENSE_OUT = 31;
  const int BRAKE_PRESSURE_OUT = 37;
  // CUT 2
  const int RAD_FAN_OUT  = 41;
  const int BRAKELIGHT_OUT = 39;
  // FINAL CUT
  const int COOLANT_PUMP_OUT = 43;
#endif





#define BATTERY_IN A6
#define VOLT_MULT 4;




#define CUT1_MIN 11
int cut1Outs[] = {SPEED_SENSE_OUT, TEMP_SENSE_OUT,
                    POT_SENSE_OUT, BRAKE_PRESSURE_OUT};
int cut1Outs_INV[] = {RAD_FAN_OUT, COOLANT_PUMP_OUT, 
                      BRAKELIGHT_OUT};

#define CUT2_MIN 10.5
int cut2Outs[] = {RAD_FAN_OUT, BRAKELIGHT_OUT};
int cut2Outs_INV[] = {COOLANT_PUMP_OUT};

#define ALLOUTS_MIN 10
int allOuts[] = {RAD_FAN_OUT, COOLANT_PUMP_OUT, 
                 BRAKELIGHT_OUT,SPEED_SENSE_OUT,
                 TEMP_SENSE_OUT, POT_SENSE_OUT,
                 BRAKE_PRESSURE_OUT};

#define ALLOUTS_LEN sizeof(allOuts) / sizeof(int)
#define CUT1OUTS_LEN sizeof(cut1Outs) / sizeof(int)
#define CUT2OUTS_LEN sizeof(cut1Outs) / sizeof(int)

#define CUT1OUTS_INV_LEN sizeof(cut1Outs_INV) / sizeof(int)
#define CUT2OUTS_INV_LEN sizeof(cut1Outs_INV) / sizeof(int)






float batteryVoltage() { 
  float sensorValue = analogRead(BATTERY_IN);
  float voltage = sensorValue * (5.0 / 1023.0);
  voltage *= VOLT_MULT;
  return voltage;
}

void setup() {
  
  for (int i = 0; i < ALLOUTS_LEN; i++)
  {
    pinMode(allOuts[i], OUTPUT);
  }
}

void writeArrOuts(int val, int arr[], int len)
{
  for (int i = 0; i < len; i++)
  {
    digitalWrite(arr[i], val);
  }
  
}


void loop() {

  float battery = batteryVoltage();
   
  if(battery < ALLOUTS_MIN)
  {
    writeArrOuts(LOW, allOuts, ALLOUTS_LEN);
  }
  else if (battery < CUT2_MIN)
  {
    // cut everything
    writeArrOuts(LOW, allOuts, ALLOUTS_LEN);
    // except coolant pump
    digitalWrite(COOLANT_PUMP_OUT, HIGH);
  }
  else if (battery < CUT1_MIN)
  {
    writeArrOuts(LOW, cut1Outs, CUT1OUTS_LEN);
    writeArrOuts(HIGH, cut1Outs_INV, CUT1OUTS_INV_LEN);
  }
  else
  {
    writeArrOuts(HIGH, allOuts, ALLOUTS_LEN);
  }

}
