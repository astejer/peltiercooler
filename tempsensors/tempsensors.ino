//Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 4 on the Arduino
#define ONE_WIRE_BUS 4
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

int oldntc1 = A0;
int newntc2 = A1;
int newptc3 = A2;
int lm35cz4 = A3;
int ds18b20_5 = 4;
int val;

float V1, V2, V3, V4, V5;
float Vin = 5.;
float R0 = 10000.;
float logR1, R1, logR2, R2, R3, RT;
float T[5];
float c1 = 298.15, b1 = 3070., b2 = 3380.;

unsigned long time;

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  time = millis(); 
  
  V1 = (Vin / 1023.0) * analogRead(oldntc1);
  R1 = R0 * (Vin / V1 - 1.0);
  logR1 = log(R1 / R0);
  T[0] = (1.0 / (1 / c1 + ((1 / b1) * logR1))) - 273.15;

  V2 = (Vin / 1023.0) * analogRead(newntc2);
  R2 = R0 * (Vin / V2 - 1.0);
  logR2 = log(R2 / R0);
  T[1] = (1.0 / (1 / c1 + ((1 / b2) * logR2))) - 273.15;

  V3 = (5. / 1023.0) * analogRead(newptc3);
  RT = R0 * (Vin / V3 - 1.0);
  R3 = RT/5000.;
  T[2] = 28.54*(pow(R3,3))-158.5*(pow(R3,2))+474.8*(R3)-319.85;

  T[3] = (5.0 * analogRead(lm35cz4) * 100.0) / 1024;

  // Send the command to get temperatures
  sensors.requestTemperatures();
  T[4] = sensors.getTempCByIndex(0);

  for(int i=0; i<5; i++){
    Serial.print(T[i]);
    Serial.print("     ");
  }
    Serial.print(time);
    Serial.println();
  delay(1000);
}

