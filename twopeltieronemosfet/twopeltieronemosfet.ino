/*
 Lawrence Berkeley National Lab 2017
 Adrien Stejer

 This code was written to control two Peltier devices (thermo-electric coolers, TECs) by using one N-channel 
 MOSFET connected to an external power supply, Arduino PWM output, and two peltier elements. Peltier1 was 
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
 the proportional coefficient(kp) should be high, on the order of 100, and the integral and differential coefficients 
 should be small, on the order of 10 or 1.

 Apart from that the pin locations can be changed as you please but if you decide to add more NTCs or peltiers driven by 
 separate mosfets remember that they need to have sequential or different numbering. But for the most part you can copy 
 and paste the code and just change the numbers and this should work for any numbe of peltiers, NTCs, and MOSFETs.

 Enjoy!
 
 */
 
#include <PID_v1.h>       // This includes the PID Library which is necessary to control the power driving the peltier based on how far away the current temperature is from the setpoint 

int peltier = 9;          // declares the peltier pin address for the pwm mosfet control  
double Output;            // declares the output parameter necessary for the PID function, in this case it's an integer from 0 to 255
double Celsius;           // declares the input for the PID algorithm and what we are trying to control, in our case it is temperature in degrees celsius
double Setpoint;          // declares the setpoint for the PID function, in our case this is the temperature of the cold side of the peltier
unsigned long time;       // establishes the varaible time so we can graph data later

/*below are variables for NTC temp sensor*/
int ThermistorPin[3] = {A0,A1,A2};       // declares the analog pin addresses for the thermistors 
float V1;                                                        // declares the voltages that will be computed from the analog output in the voltage dividers
float Vin = 5;                                                           // voltage applied to the voltage divider, used in analog conversion
float R0 = 10000.;                                                       // the other resistor value in the voltage divider, also the R value of the NTC at 25C
float logR1, R1;
float T[3];                       // declares variables for the current temperature calculation
float c1 = 298.15, b=3070.;                                              // c1 is 25C in Kelvin and b is the Beta value of the thermistor, we had to claibrate this as it was not the nominal value
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
 
PID tempController(&Celsius, &Output, &Setpoint, 100, 20.5, 5.125, REVERSE);       // creates a PID controller linked to the peltier1 element, description of arguements/parameters given above


void setup() {
  Serial.begin(9600);                         // sets the baud for serial data transmission, make sure this matches with baud in serial monitor/plotter or you won't see the data printing out
  pinMode(peltier, OUTPUT);                   // configures pin going to MOSFET driving the peltier as an output of pwm
  Celsius = T[0];                               // sets the first thermistor temp as the inputs for the PID controllers
  Setpoint = -40;                             // desired temperature(in C) for cold side of peltier1, ideally, -30 or -40 is lowest
  tempController.SetSampleTime(1000);         // changed from 1000 to 200, let's see how this goes
  tempController.SetOutputLimits(0, 255);     // ensures the output is from 0 to 255 otherwise pwm won't work
  tempController.SetMode(AUTOMATIC);          // specifies that the PID should be ON
}

void loop() {
  time = millis();
  counter +=1;                  // adds one to counter used to slow down the serial window when it prints out the temperature
  
  /*Begin temperature monitoring */
  /*NTC Temp sensor */
  for(int i=0; i<3; i++){
    V1=(5./1023.0)*analogRead(ThermistorPin[i]);         // converts analog readout to voltage
    R1 = R0 * (Vin/V1 - 1.0);                         // voltage divider equation to find current resistance of thermistor
    logR1 = log(R1/R0);
    T[i] = (1.0 / (1/c1 + ((1/b)*logR1)))-273.15;       // beta equation gives the current temperature, could also use steinhart-hart eqn for more accuracy
  }
 
  if (counter == 10){           // ensures that the serial window prints every second rather than constantly
    for(int i=0; i<3; i++){
      Serial.print(T[i]);
      Serial.print("     ");
    }
    Serial.print(time);
    Serial.println();
    counter=0;                  // sets counter back to 0 so it can print again after another second
  }

  Celsius = T[0];
  
  if(T[2]>60.){
    analogWrite(peltier,0);
  }
  else{ 
    boolean s = tempController.Compute();             // recomputes(at frequency specified by SetSampleTime) the output value going to the MOSFET through the pwm, it technically gives a boolean value (did it recompute output or not) but after it recomputes, the PID output changes
    analogWrite(peltier, Output);                     // the new output has been calculated and this send the new value to the analog port
  }
  
  delay(100);
  
}
