//this code is based on the battery voltage, other one is based on sensors
int sensorValue; // = analogRead(A6);
const int VOLT_DIVIDER = 4;
float voltage; // = sensorValue * (5.0 / 1023.0);
//voltage = voltage * VOLT_DIVIDER;
const int POT_K = 31;
const int SPEED_K = 33;
const int TEMP_K = 35;
const int BRKP_K = 37;
const int BRKL_K = 39;
const int FAN_K = 41;
const int H20_K = 43;
//TEMPORARY VALUES
const float POT_V = 11; //add a value
const float TEMP_V = 10;
const float SPEED_V = 9;
const float FAN_V = 8;
const int DELAY = 1000; //delay time before reading value again

void setup() {
  for (int i = 14; i <= 49; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600); //this is default?
}
float readVolt() { //reads the voltage 
  sensorValue = analogRead(A6);
  voltage = sensorValue * (5.0 / 1023.0);
  voltage = voltage * VOLT_DIVIDER;
  return voltage;
}

void loop() {
  while (true) { //maybe change this later??
    voltage = readVolt();

    if (voltage < POT_V) {
      delay(DELAY); //make sure the voltage fluctuation isn't just a fluke
      voltage = readVolt();
      if (voltage < POT_V) {
        digitalWrite(POT_K, LOW);
        if (voltage < TEMP_V) {
          delay(DELAY);
          voltage = readVolt();
          if (voltage < TEMP_V) {
            digitalWrite(TEMP_K, LOW);
            if (voltage < SPEED_V) {
              delay(DELAY);
              voltage = readVolt();
              if (voltage < SPEED_V) {
                digitalWrite(SPEED_K, LOW);
                if (voltage < FAN_V) {
                  delay(DELAY);
                  voltage = readVolt();
                  if (voltage < FAN_V) {
                    digitalWrite(FAN_K, LOW);
                  }
                }
              }
            }
          }
        }
      }
    }
  }

if (voltage > POT_V) {
      delay(DELAY); //make sure the voltage fluctuation isn't just a fluke
      voltage = readVolt();
      if (voltage > FAN_K) {
        digitalWrite(FAN_K, HIGH);
        if (voltage > SPEED_V) {
          delay(DELAY);
          voltage = readVolt();
          if (voltage > SPEED_V) {
            digitalWrite(SPEED_V, HIGH);
            if (voltage > TEMP_V) {
              delay(DELAY);
              voltage = readVolt();
              if (voltage > TEMP_V) {
                digitalWrite(TEMP_V, HIGH);
                if (voltage > POT_V) {
                  delay(DELAY);
                  voltage = readVolt();
                  if (voltage > POT_V) {
                    digitalWrite(POT_V, HIGH);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
