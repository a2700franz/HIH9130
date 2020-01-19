/*
HIH9130.cpp - Library for reading the HIH9130 Temp/Hum Sensor
Franz Stoiber 2019
*/

#include "HIH9130.h"
#include <Wire.h>

bool HIH9130::begin(uint8_t I2CAdr) {
  //I2CAdr ... one of the posible device addresses
  uint16_t i;
  DeviceAdr = I2CAdr; 
  Wire.beginTransmission(DeviceAdr);
  if (Wire.endTransmission() != 0) {
    Serial.println("HIH9130: device not found");
    return(false);
  }
  return(true);
}
 
void HIH9130::readTempHum() {
  //the readings are stored in the public variables Temp and Hum
  uint8_t HumHi, HumLo, TempHi, TempLo;
  uint16_t HumRaw, TempRaw;
  uint32_t TimeoutMillis;
  Wire.beginTransmission(DeviceAdr);
  Wire.endTransmission();
  delay(HIH9130_CONVERSIONDELAY_MS);
  TimeoutMillis = millis() + 10;
  Wire.requestFrom(DeviceAdr, 4);
  while (Wire.available() < 4) {
    if ((int32_t)(millis() - TimeoutMillis) > 0) return;
  }
  HumHi  = Wire.read();
  HumLo  = Wire.read();
  TempHi = Wire.read();
  TempLo = Wire.read();
  State = (HumHi & 0xC0) >> 6;
  HumRaw = ((HumHi & 0x3F) << 8) | HumLo;
  Hum = ((float)HumRaw * 100.) / 16382.;
  TempRaw = ((TempHi << 8) | (TempLo & 0xFC)) >> 2;
  Temp = ((float)TempRaw *165.) / 16382. - 40.;
}