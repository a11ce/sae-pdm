#define TEST_MODE

#ifdef TEST_MODE
  // TESTING LED VALUES 
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
#define CUT2_MIN 10.5
#define CUT3_MIN 10

// everything at or below the given index will be cut
// if the voltage drops below the threshold;
// read it as 'the first N in the array will stay on'
#define CUT1_IDX 3 // no sensors
#define CUT2_IDX 1 // just the coolant pump
#define CUT3_IDX 0 // everything off

int allOuts[] = {COOLANT_PUMP_OUT, 

                RAD_FAN_OUT, BRAKELIGHT_OUT,

                SPEED_SENSE_OUT, TEMP_SENSE_OUT,
                POT_SENSE_OUT, BRAKE_PRESSURE_OUT};


#define ALLOUTS_LEN sizeof(allOuts) / sizeof(int)


float batteryVoltage() { 
  float sensorValue = analogRead(BATTERY_IN);
  float voltage = sensorValue * (5.0 / 1023.0);
  voltage *= VOLT_MULT;
  return voltage;
}

void setCutoff(int cutoffIdx)
{
  for (int i = 0; i < ALLOUTS_LEN; i++)
  {
    digitalWrite(allOuts[i], i > cutoffIdx ? HIGH : LOW);
  }
  
}

void setup() {
  
  for (int i = 0; i < ALLOUTS_LEN; i++)
  {
    pinMode(allOuts[i], OUTPUT);
  }
  setCutoff(-1);
}


void loop() {

  float battery = batteryVoltage();
   
  if(battery < CUT3_MIN)
  {
    setCutoff(CUT3_IDX);
  }
  else if (battery < CUT2_MIN)
  {
    setCutoff(CUT2_IDX);
  }
    else if (battery < CUT1_MIN)
  {
    setCutoff(CUT1_IDX);
  }
  else
  {
    setCutoff(-1);
  }

}
