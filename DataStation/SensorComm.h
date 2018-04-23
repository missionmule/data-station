#ifndef SENSORCOMM_H
#define SENSORCOMM_H

#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include "Arduino.h"

class SensorComm {
private:
  SoftwareSerial commPort; //RX, TX
  Adafruit_GPS gpsModule;
  unsigned long timeout = 180000; // 3 minutes
  int totalSamples = 10;

public:
  // constructor
  SensorComm() : commPort(6,7), gpsModule(&commPort) {}

  // start communication with sensors
  void begin(){ 
    gpsModule.begin(9600); 
    // Set the update rate, 1 Hz
    gpsModule.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    // Request updates on antenna status
    gpsModule.sendCommand(PGCMD_ANTENNA);
  }

  // stop communication with sensonrs
  void stop(){ commPort.end(); }

  // get actualy GPS data (returns in 1/100,000 of a degree)
  String getGpsData();

  // start listening on the SoftwareSerial port
  void listen() {commPort.listen(); }
  
};

#endif
