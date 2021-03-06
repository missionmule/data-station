#include "Communication.h"
#include "PowerManager.h"
#include "SensorComm.h"

int shutdownStart = 1;

char STATION_ID[3] = {'1', '0', '1'};

volatile int f_wdt=1;
volatile int count = 0;

Communication * comms = new Communication(10, 11, 57600, STATION_ID); // RX, TX, Baudrate
PowerManager * powerManager = new PowerManager(comms, &f_wdt);
SensorComm * sensorComm = new SensorComm();

char droneCommand;

unsigned long timerStart;
unsigned long timeElapsed;
const unsigned long TIMEOUT = 6000000;

void executeCommand(char command) {
  char startDelimiter = '~';
  String packetOut;

  comms->write(startDelimiter);

  comms->write(STATION_ID[0]);
  comms->write(STATION_ID[1]);
  comms->write(STATION_ID[2]);

  comms->write(command);

  // flush outgoing and incoming buffer, respectively
  comms->flush();
  //comms->flushIncommingBuffer();

  // execute the requested command
  switch (command) {
    case '1':
      Serial.println("Received Command: POWER_ON");
      shutdownStart = 0;
      powerManager->powerUpSystem();
      break;

    case '2':
      Serial.println("Received Command: POWER_OFF");
      shutdownStart = 1;
      break;

    case '3':
      Serial.println("Received Command: EXTEND_TIME");
      timerStart = millis();
      break;

    case '4':
      Serial.println("Received Command: RESET_ID");
      if (comms->getNewId()){
        STATION_ID[0] = comms->getId(0);
        STATION_ID[1] = comms->getId(1);
        STATION_ID[2] = comms->getId(2);
        Serial.print("New ID set: ");
        Serial.print(STATION_ID[0]);
        Serial.print(STATION_ID[1]);
        Serial.println(STATION_ID[2]);
      }
      break;

    case '5':
      Serial.println("Received Command: REQUEST_GPS");
      sensorComm->begin();
      sensorComm->listen();
      packetOut = sensorComm->getGpsData();
      comms->listen();
      // send prelimitor, GPS Data, then postlimitor
      comms->write('<');
      comms->writeString(packetOut);
      comms->write('>');
      break;

    case '6':
      Serial.println("Received Command: DEPLOYMENT_SYS_TEST");
      comms->write('<');
      comms->writeString("245233230,544344570");
      comms->write('>');
      break;

    default:
      Serial.println("ERROR: Command not recognized");
      break;
  }

}

// TODO: Add support for UBlox GPS Module, comm with I2C

void setup(){
  Serial.begin(57600);
  sensorComm->begin();
  comms->begin();
  comms->listen();

  // Initialize Watchdog Timer
  powerManager->setupWatchDogTimer();

  Serial.println("Initialized");
}

// Watchdog Interrupt Service. This is executed when watchdog timed out.
ISR(WDT_vect) {
  if(f_wdt == 0) {
    if (count >= 4){
      count = 0;
      f_wdt=1;
    }
    else{
      count++;
    }
  }
}

void loop(){
  // Wait until the watchdog has triggered a wake up.
  if(f_wdt != 1) {
    powerManager->enterSleep();
    return;
  }

  Serial.println("Awake!");

  droneCommand = comms->getDroneCommand();

  if (droneCommand){
    timerStart = millis();
    Serial.println("Drone in vicinity...");
    executeCommand(droneCommand);

    while (!shutdownStart){
      timeElapsed = millis()-timerStart;
      Serial.print("Time remaining (seconds): ");
      Serial.println((TIMEOUT-timeElapsed)/1000);

      if (timeElapsed > TIMEOUT){
        Serial.println("Timeout event...");
        break;
      }

      droneCommand = comms->getDroneCommand();

      if (droneCommand)
        executeCommand(droneCommand);

      delay(200);

    }
  }
  else{
      Serial.println("No messages received");
  }

  Serial.println("Going to slepp...ZZzzz");
  powerManager->shutDownSystem();

 }
