#include "SensorComm.h"

String SensorComm::getGpsData(){
  // start timer
  unsigned long timeStart = millis();
  String retVal = "-1,-1";
  int32_t latAvg = 0; // in 1/100,000 of a degree
  int32_t lonAvg = 0; // in 1/100,000 of a degree
  
  while (true){
    char c = gpsModule.read();
    
    if ((gpsModule.newNMEAreceived()) && (gpsModule.parse(gpsModule.lastNMEA()))) {
      if (gpsModule.fix){
        retVal = String(gpsModule.latitude_fixed) + "," + String(gpsModule.longitude_fixed);
        return retVal;
      }
    }

    // return if this takes too long...
    if ((millis()-timeStart) > timeout){
      return retVal;
    }
  }
}

