#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <SoftwareSerial.h>
#include "Arduino.h"

class Communication : public SoftwareSerial{

public:

  char station_id[3];
  long baudrate = 57600;

  // constructor
  Communication(int rx, int tx, int baudrate, char station_id[3]): SoftwareSerial(rx, tx){
    (this->station_id)[0] = station_id[0];
    (this->station_id)[1] = station_id[1];
    (this->station_id)[2] = station_id[2];
  }

  // begin function  
  void begin(){ SoftwareSerial::begin(baudrate); }

  // check to see if there are available commands
  int getDroneCommand();

  // empty the incomming serial buffer
  void flushIncommingBuffer();

  // get the new ID that the GCS wants to assign this station
  bool getNewId();

  // return the first part of a new ID
  char getId(int place);

  // check for a matching preamble
  bool checkForPreamble();

  // write a string
  void writeString(String string);
  
};

#endif
