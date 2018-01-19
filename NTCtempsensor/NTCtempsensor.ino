
int ThermistorPin[2] = {A1,A2};
float V1;
float Vin = 5.;
float R0 = 10000.;
float logR1, R1;
float T[2];
float c1 = 298.15, b=3070.;

void setup() {
Serial.begin(9600);
}

void loop() {

  for(int i=0; i<2; i++){
    V1=(5./1023.0)*analogRead(ThermistorPin[i]);
    R1 = R0 * (Vin/V1 - 1.0);
    logR1 = log(R1/R0);
    T[i] = (1.0 / (1/c1 + ((1/b)*logR1)))-273.15;
  }
  
  Serial.print("Temperature: "); 
  for (int i=0; i<2; i++){
    Serial.print(T[i]);
    Serial.print(" C"); 
    Serial.print("     ");
  }
  Serial.println();   
    
  delay(1000);
}

