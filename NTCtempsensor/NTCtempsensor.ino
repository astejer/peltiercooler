int ThermistorPin1 = A1;
float V1;
int ThermistorPin2 = A2;
float V2;
float Vin = 5.;
float R0 = 10000.;
float logR1, R1, logR2, R2, T1, T2;
float c1 = 298.15, b=3070.;

void setup() {
Serial.begin(9600);
}

void loop() {

  V1=(5./1023.0)*analogRead(ThermistorPin1);
  R1 = R0 * (Vin/V1 - 1.0);
  logR1 = log(R1/R0);
  T1 = (1.0 / (1/c1 + ((1/b)*logR1)))-273.15;
  
  V2=(5./1023.0)*analogRead(ThermistorPin2);
  R2 = R0 * (Vin/V2 - 1.0);
  logR2 = log(R2/R0);
  T2 = (1.0 / (1/c1 + ((1/b)*logR2)))-273.15;
  
  Serial.print("Temperature: "); 
  Serial.print(T1);
  Serial.println(" C");   
  Serial.print(T2);
  Serial.println(" C");   
  
  delay(1000);
}

