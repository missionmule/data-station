#include "PowerManager.h"

// configure digital pins
void PowerManager::setupDigitalPins(){
  // Setup Control Pins
  pinMode(PI_PWR_CTRL, OUTPUT);
  pinMode(SNSR_PWR_CTRL, OUTPUT);
  pinMode(PI_PWR_CMD, OUTPUT);
  pinMode(PI_PWR_STATUS, INPUT);


  // Initialize Control Pins
  digitalWrite(PI_PWR_CTRL, HIGH);
  digitalWrite(PI_PWR_CMD, LOW);
  digitalWrite(SNSR_PWR_CTRL, HIGH);
}

// shut down data station
void PowerManager::shutDownSystem(){
  // We need to power down the raspi... safely (or else Zane gets his pannies in a bunch!)
  // The Raspi should have daemon running that continuously monitors the state of GPIO pin
  // 22. When it receives a logic HIGH, it initiates a shutdown. :)
  digitalWrite(PI_PWR_CMD, LOW);
  unsigned long timerStart = millis();
  while (digitalRead(PI_PWR_STATUS) == HIGH){
    delay(1000);
    // can't wait forever... if 5 mins pass, break this loop and shutdown.
    if ((millis() - timerStart) > POWER_OFF_TIMEOUT){ 
      Serial.println("Timeout for Pi power off. Forcing shutdown.");
      break; 
    }
  }
  digitalWrite(PI_PWR_CTRL, LOW);

  delay(1000);
  enterSleep();
}

// power up data station
void PowerManager::powerUpSystem(){
  digitalWrite(PI_PWR_CMD, HIGH);
  digitalWrite(PI_PWR_CTRL, HIGH);
}

// configure watchdog timer
void PowerManager::setupWatchDogTimer(){
  // The MCU Status Register (MCUSR) is used to tell the cause of the last
  // reset, such as brown-out reset, watchdog reset, etc.
  // NOTE: for security reasons, there is a timed sequence for clearing the
  // WDE and changing the time-out configuration. If you don't use this
  // sequence properly, you'll get unexpected results.

  // Clear the reset flag on the MCUSR, the WDRF bit (bit 3).
  MCUSR &= ~(1<<WDRF);

  // Configure the Watchdog timer Control Register (WDTCSR)
  // The WDTCSR is used for configuring the time-out, mode of operation, etc

  // In order to change WDE or the pre-scaler, we need to set WDCE (This will
  // allow updates for 4 clock cycles).

  // Set the WDCE bit (bit 4) and the WDE bit (bit 3) of the WDTCSR. The WDCE
  // bit must be set in order to change WDE or the watchdog pre-scalers.
  // Setting the WDCE bit will allow updates to the pre-scalers and WDE for 4
  // clock cycles then it will be reset by hardware.
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  /**
   *  Setting the watchdog pre-scaler value with VCC = 5.0V and 16mHZ
   *  WDP3 WDP2 WDP1 WDP0 | Number of WDT | Typical Time-out at Oscillator Cycles
   *  0    0    0    0    |   2K cycles   | 16 ms
   *  0    0    0    1    |   4K cycles   | 32 ms
   *  0    0    1    0    |   8K cycles   | 64 ms
   *  0    0    1    1    |  16K cycles   | 0.125 s
   *  0    1    0    0    |  32K cycles   | 0.25 s
   *  0    1    0    1    |  64K cycles   | 0.5 s
   *  0    1    1    0    |  128K cycles  | 1.0 s
   *  0    1    1    1    |  256K cycles  | 2.0 s
   *  1    0    0    0    |  512K cycles  | 4.0 s
   *  1    0    0    1    | 1024K cycles  | 8.0 s
  */
  WDTCSR  = (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0);
  // Enable the WD interrupt (note: no reset).
  WDTCSR |= _BV(WDIE);  
}

// go into sleep mode
void PowerManager::enterSleep(){
  comms->flushIncommingBuffer();
  // clear the flag so we can run code again after the MCU wake up
  *f_wdt = 0;

  comms->end();
  digitalWrite(SNSR_PWR_CTRL, LOW);


  // SLEEP_MODE_PWR_DOWN - the highest power saving mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  // Now enter sleep mode.
  sleep_mode();

  // The program will continue from here after the WDT timeout

  // First thing to do is disable sleep.
  sleep_disable();

  // Re-enable the peripherals.
  power_all_enable();

  digitalWrite(SNSR_PWR_CTRL, HIGH);
  comms->begin(); 
  comms->listen();
}

