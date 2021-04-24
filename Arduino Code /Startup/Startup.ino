const int RAD_FAN_OUT  = 41;
const int COOLANT_PUMP_OUT = 43;
const int BRAKELIGHT_OUT = 39;
const int BRAKE_PRESSURE_OUT = 37;

const int SPEED_SENSE_OUT = 33;
const int TEMP_SENSE_OUT = 35;
const int POT_SENSE_OUT = 31;

#define BATTERY_IN A6
#define VOLT_MULT 4;

int allOuts[] = {RAD_FAN_OUT, COOLANT_PUMP_OUT, 
                 BRAKELIGHT_OUT,SPEED_SENSE_OUT,
                 TEMP_SENSE_OUT, POT_SENSE_OUT,
                 BRAKE_PRESSURE_OUT};

int sensorOuts[] = {SPEED_SENSE_OUT, TEMP_SENSE_OUT,
                    POT_SENSE_OUT};
                    
#define ALLOUTS_LEN sizeof(allOuts) / sizeof(int)
#define SENSOROUTS_LEN sizeof(sensorOuts) / sizeof(int)

#define SENSOR_MINIMAL 11

#define ALLOUTS_MINIMAL 10




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

void writeAllOuts(int val)
{
  for (int i = 0; i < ALLOUTS_LEN; i++)
  {
    digitalWrite(allOuts[i], val);
  }
}

void writeSensorOuts(int val)
{
  for (int i = 0; i < SENSOROUTS_LEN; i++)
  {
    digitalWrite(sensorOuts[i], val);
  }
}


void loop() {

  float battery = batteryVoltage();
   
  if(battery < ALLOUTS_MINIMAL)
  {
    writeAllOuts(LOW);
  }
  else if (battery < SENSOR_MINIMAL)
  {
    writeSensorOuts(LOW);
  } 
  else
  {
    writeAllOuts(HIGH);
  }

}
