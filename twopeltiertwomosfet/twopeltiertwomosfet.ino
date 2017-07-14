/*
 Lawrence Berkeley National Lab 2017
 Adrien Stejer

 This code was written to control two Peltier devices (thermo-electric coolers, TECs) by using two N-channel 
 MOSFETs connected to two external power supplies, Arduino PWM outputs, and two peltier elements. Peltier1 was 
 mounted in between two aluminum pieces which was then fit into a plastic piece made specifically for the project, 
 peltier2 was placed between the CPU cooler and one of the aluminum plates. On each side of the aluminum pieces 
 an NTC Thermistor(Negative Temperature Coefficient) was mounted and placed in a voltage divider mounted on a 
 ProtoShield on the Arduino Mega 2560, another NTC was also placed on the CPU cooler on the hot side of Peltier2. 
 These are read out by three analog ports on the arduino, converted to voltage,and then using the voltage divider
 equation the resistance and then current temperature (based on the beta coefficient of the NTC) is found. 
 After the current temperature is found, the PID controller function computes the output to the gate of the MOSFET 
 through the PWM port based on how far the current temperature is from the setpoint and the PID coefficients.
 And this cycle continues, Arduino gets temperature, that information is put into the PID function, it computes
 the new PWM output based on how far the temperature is from the setpoint and the PID coefficients, the MOSFET then 
 changes the power to the Peltier which should change the temperature, and then the cycle starts over again. 

 The only thing that should be changed about this code is the PID coefficients, which depend on the system at hand, I 
 personally used the Ziegler-Nichols Method to determine the coefficients but there are other ways to determine the 
 coeffiecients including just blind guessing. From reading online it seems that for temperature control, as a general guideline
 the proportional coefficient(kp) should be high on the order of 100 and the integral and differential coefficients 
 should be small on the order of 10 or 1.

 Apart from that the pin locations can be changed as you please but if you decide to add more NTCs or peltiers remember
 that they need to have sequential or different numbering. But for the most part you can copy and paste the code and just
 change the numbers and this should work for any numbe of peltiers and NTCs.

 Enjoy!
 
 */
#include <PID_v1.h>       // This includes the PID Library which is necessary to control the power driving the peltier based on how far away the current temperature is from the setpoint 

int peltier1 = 5, peltier2 = 6;     // declares the peltier pin addresses for the pwm mosfet control  
double Output1, Output2;            // declares the output parameter necessary for the PID function, in this case it's an integer from 0 to 255
double Celsius1, Celsius2;          // declares the input for the PID algorithm and what we are trying to control
double Setpoint1, Setpoint2;        // declares the setpoint for each of the PID functions, 1 for the cold side and 2 for the shared side of the peltiers
unsigned long time;

//below are variables for NTC temp sensor
int ThermistorPin1 = A2, ThermistorPin2 = A1, ThermistorPin3 = A0;       // declares the analog pin addresses for the thermistors 
float V1, V2, V3;                                                        // declares the voltages that will be computed from the analog output in the voltage dividers
float Vin = 5;                                                           // voltage applied to the voltage divider, used in analog conversion
float R0 = 10000.;                                                       // the other resistor value in the voltage divider, also the R value of the NTC at 25C
float logR1, R1, logR2, R2, logR3, R3, T1, T2, T3;                       // declares variables for the current temperature calculation
float c1 = 298.15, b=3070.;                                              // c1 is 25C in Kelvin and b is the Beta value of the thermistor, we had to calibrate this as it was not the nominal value
int counter=9;                                                           // counter used to slow down the serial window when it prints out the temperature

/*
 * @param Celsius -- the variable to control
 * @param Output -- the value of the pwm to be calculated by the PID.compute() method
 * @param Setpoint -- the value of Celsius that the algorithm tries to attain.
 * @param kp -- (tentative: 100) maybe 150
 * @param ki -- (tentative: 10) maybe 12.5
 * @param kd -- (tentative: 1) maybe 3.125
 * @param Direction -- (tentative REVERSE)
 */
 
PID tempController1(&Celsius1, &Output1, &Setpoint1, 100, 3, .75, REVERSE);     // creates a PID controller linked to the peltier1 element, description of arguements/parameters given above
PID tempController2(&Celsius1, &Output2, &Setpoint2, 100, 3, .75, REVERSE);     // same for peltier2 elemenet


void setup() {
  Serial.begin(9600);                       // sets the baud for serial data transmission, make sure this matches with baud in serial monitor/plotter or you won't see the data printing out
  pinMode(peltier1, OUTPUT);                // configures pin going to MOSFET driving peltier 1 as an output of pwm
  pinMode(peltier2, OUTPUT);                // same as above for peltier two
  Celsius1 = T1, Celsius2 = T2;             // sets the first and second thermistor temps as the inputs for the PID controllers
  Setpoint1 = -40;                          // desired temperature(in C) for cold side of peltier1, ideally, -30 or -40
  Setpoint2 = Setpoint1;                           // desired temperature(in C) for cold side of peltier2, should be lower than setpoint for peltier1, maybe 10
  tempController1.SetSampleTime(1000);       // changed from 1000 to 200, let's see how this goes
  tempController1.SetOutputLimits(0, 255);  // ensures the output is from 0 to 255 otherwise pwm won't work
  tempController1.SetMode(AUTOMATIC);       // specifies that the PID should be ON
  
  tempController2.SetSampleTime(1000);       // same as above
  tempController2.SetOutputLimits(0, 255);
  tempController2.SetMode(AUTOMATIC);
}

void loop() {
  time = millis();
  counter +=1;                  // adds one to counter used to slow down the serial window when it prints out the temperature

  if (counter == 10){           // ensures that the serial window prints every second rather than constantly
    Serial.print(T1);
    Serial.print("     ");
    Serial.print(T2);
    Serial.print("     ");
    Serial.print(T3);
    Serial.print("     ");
    Serial.print(time);
    Serial.println();
    counter=0;                  // sets counter back to 0 so it can print again after another second
  }
  
  /*Begin temperature monitoring */
  
  /*NTC Temp sensor */
  V1=(5/1023.0)*analogRead(ThermistorPin1);         // converts analog readout to voltage
  R1 = R0 * (Vin/V1 - 1.0);                         // voltage divider equation to find current resistance of thermistor
  logR1 = log(R1/R0);                               
  T1 = (1.0 / (1/c1 + ((1/b)*logR1)))-273.15;       // beta equation gives the current temperature, could also use steinhart-hart eqn for more accuracy
  
  V2=(5/1023.0)*analogRead(ThermistorPin2);         // same as above
  R2 = R0 * (Vin/V2 - 1.0);
  logR2 = log(R2/R0);
  T2 = (1.0 / (1/c1 + ((1/b)*logR2)))-273.15;

  V3=(5/1023.0)*analogRead(ThermistorPin3);         // same as above
  R3 = R0 * (Vin/V3 - 1.0);
  logR3 = log(R3/R0);
  T3 = (1.0 / (1/c1 + ((1/b)*logR3)))-273.15;

  Celsius1 = T1;
  boolean s1 = tempController1.Compute();           // recomputes(at frequency specified by SetSampleTime) the output value going to the MOSFET through the pwm, it technically gives a boolean value (did it recompute output or not) but after it recomputes, the PID output changes
  analogWrite(peltier1, Output1);                   // the new output has been calculated and this send the new value to the analog port
  
  Celsius2 = T2;
  boolean s2 = tempController2.Compute();           // same as above
  analogWrite(peltier2, Output2); 

  delay(100);
  
}
