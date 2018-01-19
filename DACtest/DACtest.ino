#include <SPI.h>         // Remember this line!
#include <DAC_MCP49xx.h>

DAC_MCP49xx dac(DAC_MCP49xx::MCP4911, 53, -1); // DAC model, SS pin, LDAC pin

void setup() { } // No setup code is necessary

void loop() {
  dac.output(180);
  delay(100);
  dac.output(0);
  delay(100);
}
