/*
HIH9130.h - Library for reading the HIH9130 Temp/Hum Sensor
Franz Stoiber 2019

History -----------------------------------------------------
2019-10-05 V1
           check if device is present now in function checkPresence
           new function logInfo can be activated in function begin
2020-01-26 V2
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
    const uint8_t Version = 2;
    const float NoVal = -99.;
    uint8_t State;
    float Temp = NoVal;
    float Hum = NoVal;
    
    void begin(uint8_t I2CAdr, bool Log = false);
    bool checkPresence();
    void readTempHum();
               
  private:
    uint8_t DeviceAdr;
    bool SerialLog;
    
    void logInfo(const char *Item);
};

#endif