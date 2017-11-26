#include "SleepyPi2.h"
#include <Time.h>
#include <LowPower.h>
#include <PCF8523.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//Uses software serial from Github with extra functions
SoftwareSerial xBeeSerial(9, 10); // Serial for Xbee RX, TX
char byteIden;
char byteCommand;
char byteReceived[2];
bool droneInVicinity;
const int CAM_IDEN = 1;
const int TIMEOUT = 5;


class Timer {

private:
  float timeElapsed;
  unsigned long timeCurrent;
  unsigned long timeStart;

public:
  int getTimeElapsed(){
    // return time elapsed in minutes
    timeCurrent = millis();
    timeElapsed = (timeCurrent - timeStart)/(1000*60);
    return timeElapsed;
  }
  void reset(){
    timeStart = millis();
  }
}

void setup() {
  // Turn the Serial Protocol ON
  Serial.begin(9600); //Serial communication to RasPi
  while (!Serial) {
    ; // wait for serial port to connect. Just in case
  }
  Serial.print("start xbee fuck yes?");

  delay(50);

  xBeeSerial.begin(9600);
  Serial.print("start xbee fuck yes yes");

  resetInputs();

}

void resetVariables(){
  intIden = 0;
  intCommand = 0;
  intReceived = {0,0};
  droneInVicinity = false;
}

void loop() {

  if (xBeeSerial.available()) {
    droneInVicinity = true;
    timer Timer();
    timer.reset()
    Serial.println("Received a Message from Wadi Drone");
    // Save the received data into variables
    byteReceived[0]=xBeeSerial.read();
    byteReceived[1]=xBeeSerial.read();

    // Check to see if we received this command already and make sure
    // it is adressed to this camera trap;
    if (byteReceived[0] == CAM_IDEN && byteReceived[1] != byteCommand){
      // This is a new command; record it
      byteCommand = byteReceived[1]

      // Act on the command received from the Drone
      executeCommand()
    }

  }

  if (droneInVicinity){
    if (timer.getTimeElapsed() > TIMEOUT){
      droneInVicinity = false;
      enterLowPowerMode()
    }
  }
  else{
    enterLowPowerMode()
  }

}

void enterLowPowerMode(){
  resetVariables();
}

void executeCommand(){
  ;
}
