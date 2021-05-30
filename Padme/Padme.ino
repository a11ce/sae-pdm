//#include <can.h>

//#define TEST_MODE

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
#define VOLT_MULT 4
const float HYSTER = 0.2;

#define NUM_CUTS 3

const float cutVoltages[NUM_CUTS] = {10.0, 10.5, 11.0};
// everything at or below the given index will be cut
// if the voltage drops below the threshold;
// read it as 'the first N in the array will stay on'
// 3 no sensors
// 1 just the coolant pump
// 0 everything off
const int cutIndexes[NUM_CUTS] = {0, 1, 3};


int allOuts[] = {COOLANT_PUMP_OUT, 

                BRAKELIGHT_OUT, RAD_FAN_OUT,

                BRAKE_PRESSURE_OUT, POT_SENSE_OUT,
                TEMP_SENSE_OUT, SPEED_SENSE_OUT};
                


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
      digitalWrite(allOuts[i], (i < cutoffIdx) ? HIGH : LOW);
 
  }
}

void setup() {
  
  for (int i = 0; i < ALLOUTS_LEN; i++)
  {
    pinMode(allOuts[i], OUTPUT);
  }
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);
  pinMode(47, OUTPUT);
  digitalWrite(47, HIGH);
  setCutoff(ALLOUTS_LEN);
  //Serial.begin(9600);
}


void loop() {

  float currentVoltage = batteryVoltage();
  
 
  // boolean canSaysCarFucked = can_read(ADDR_CAR_STATUS_BIT);
  //if(canSaysCarFucked)
  //{
  //   while(true)
  //   {
  //     // kill everything until reset
  //     // 31-47
  //     for(int idx = 31; idx < 49; idx += 2)
  //     {
  //       digitalWrite(idx, LOW);
  //     }
  //   }
  //}
   
  int currentCuts = false;
  
  for(int idx = 0; idx < NUM_CUTS; idx++)
  {

    if(currentVoltage < (cutVoltages[idx] + HYSTER))
    {
      currentCuts = true;
      if (currentVoltage < (cutVoltages[idx] - HYSTER))
      {
        setCutoff(cutIndexes[idx]);
        break;
      }

    } 
  }
  
  if(!currentCuts)
  {
     setCutoff(ALLOUTS_LEN);

  }
  //setCutoff(0);
}
