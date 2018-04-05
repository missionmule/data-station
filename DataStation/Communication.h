#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <SoftwareSerial.h>
#include "Arduino.h"

class Communication : public SoftwareSerial{

public:

  char station_id[2];

  // constructor
  Communication(int rx, int tx, int baudrate, char station_id[2]): SoftwareSerial(rx, tx){
    (this->station_id)[0] = station_id[0];
    (this->station_id)[1] = station_id[1];
  }

  // check to see if there are available commands
  int getDroneCommand();

  // empty the incomming serial buffer
  void flushIncommingBuffer();

  // get the new ID that the GCS wants to assign this station
  bool getNewId();

  // return the first part of a new ID
  char getId_1();

  // return the second part of a new ID
  char getId_2();

  // check for a matching preamble
  bool checkForPreamble();
  
};

#endif
