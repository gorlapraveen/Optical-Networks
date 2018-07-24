#include <EmonLib.h>

// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;// Create an instance

void setup()
{  
  Serial.begin(9600);
  
  emon1.voltage(2,5,0);  // Voltage: input pin, calibration, phase_shift
  emon2.voltage(3,5,0); 
  emon3.voltage(4,5,0); // Current: input pin, calibration.
}

void loop()
{
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.serialprint();          // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
                                                      //extract Power Factor into Variable
  float supplyVoltage1   = emon1.Vrms;
  float supplyVoltage2   = emon2.Vrms;
  float supplyVoltage3   = emon3.Vrms;  //extract Vrms into Variable
  Serial.println(supplyVoltage1) ;            //extract Irms into Variable
}
