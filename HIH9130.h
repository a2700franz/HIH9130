/*
HIH9130.h - Library for reading the HIH9130 Temp/Hum Sensor
Franz Stoiber 2019

History -----------------------------------------------------
2019-10-05 V1
-------------------------------------------------------------
*/

#ifndef HIH9130_h
#define HIH9130_h

#include "Arduino.h"

#define HIH9130_DEFAULT_ADDRESS     0x27
#define HIH9130_CONVERSIONDELAY_MS    40
#define MaxNrAvgVals                 150

class HIH9130 {
  public:
    const uint8_t Version = 1;
    const float NoVal = -99.;
    uint8_t State;
    float Temp = NoVal;
    float Hum = NoVal; 
    bool begin(uint8_t I2CAdr);
    void readTempHum();
               
  private:
    uint8_t DeviceAdr;
};

#endif