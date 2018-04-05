#ifndef SENSORCOMM_H
#define SENSORCOMM_H

#include <SoftwareSerial.h>
#include "Arduino.h"

class SensorComm {
private:
  SoftwareSerial gpsModule; //RX, TX

public:
  // constructor
  SensorComm() : gpsModule(6,7){}

  // start communication with sensors
  void begin(){
    gpsModule.begin(9600);
  }

  // stop communication with sensonrs
  void stop(){
    gpsModule.end();
  }
  
};

#endif
