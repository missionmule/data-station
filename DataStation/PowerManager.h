#ifndef POWERMANAGER_H
#define POWERMANAGER_H
#include "Communication.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include "Arduino.h"


class PowerManager{

private:
  Communication * comms;
  volatile int * f_wdt;
  const int PI_PWR_CTRL = 2;
  const int PI_PWR_STATUS = 3;
  const int PI_PWR_CMD = 4;
  const int SNSR_PWR_CTRL = 5;
  const unsigned long POWER_OFF_TIMEOUT = 300000; // 5 minutes

public:
  // constructor
  PowerManager(Communication * comms, volatile int * f_wdt){
    this->comms = comms;
    setupDigitalPins();
    this->f_wdt = f_wdt;
  }

  // configure digital pins
  void setupDigitalPins();

  // shut down data station
  void shutDownSystem();

  // power up data station
  void powerUpSystem();

  // configure watchdog timer
  void setupWatchDogTimer();

  // go into sleep mode
  void enterSleep();
};

#endif

