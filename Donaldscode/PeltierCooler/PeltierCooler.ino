/*
 SparkFun Electronics 2010
 Nathan Seidle
 
 This code is public domain.
 
 Peltier ran at 3.6A @ 11.0V = 39.6W!
 
 The thermo-electric cooler (or Peltier) works well well with a computer power supply for power, a computer 
 CPU heat sink for cooling and a N-Channel MOSFET to control the power. The Peltier is going to use a ton 
 of juice. In this case, I  measured 3.6 amps at 11 volts! I had to attach the hot side of the Peltier 
 to a large computer CPU heat sink but it worked so well that the cold side was so cold I could not keep 
 my finger on the device.
 
 Because I was so scared of pumping 40 watts into a device, I used this program to slowly ramp
 up the power flowing through the MOSFET. Press 'a' to increase power, 'z' to step down.
 
 */
#include <PID_v1.h>
#include <Wire.h>


int tmp102Address = 0x48;
//int power = 0; //Power level fro 0 to 99%
//int peltier_level = map(power, 0, 99, 0, 255); //This is a value from 0 to 255 that actually controls the MOSFET
int fan = 3;

int peltier = 4; 
double Output;
double Celsius; // This is the input for the PID algorithm and what we are trying to control.
double Setpoint; // let's see if this works
unsigned long time;

/**
 * @param Celsius -- the variable to control
 * @param Output -- the value of the pwm to be calculated by the PID.compute() method
 * @param Setpoint -- the value of Celsius that the algorithm tries to attain.
 * @param kp -- (tentative: 5) maybe 25
 * @param ki -- (tentative: 1) maybe 3.45
 * @param kd -- (tentative: 5.5) maybe .025
 * @param Direction -- (tentative REVERSE)
 */
PID tempController(&Celsius, &Output, &Setpoint, 100, 65, 50, REVERSE);


void setup() {
  Serial.begin(9600);
  pinMode(fan, OUTPUT);
  pinMode(peltier, OUTPUT);
  Wire.begin();
  Celsius = getTemperature();
  Setpoint = -20;
  tempController.SetSampleTime(1000);
  tempController.SetOutputLimits(0, 255);
  tempController.SetMode(AUTOMATIC);
}

void loop() {
  time = millis();
  
  /*Begin temperature monitoring */
  Celsius = getTemperature();
  boolean s = tempController.Compute();
  analogWrite(peltier, Output);
  
 
    Serial.print(Celsius);
    Serial.print(",");
    Serial.print(Output);
    Serial.print(",");
    Serial.print(time);
    Serial.println();
    
    delay(500); 
  
}

double getTemperature(){
  Wire.requestFrom(tmp102Address, 2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  return TemperatureSum*0.0625;
  
}

