#include "Communication.h"


// check to see if there are available commands
int Communication::getDroneCommand(){
  char incommingByte;
  bool idenMatch = false;
  bool preambleSuccess = false;
  int idenCount = 0;

  Serial.println("Checking for incomming messages...");
  for (int i = 0; i < 10; i++){
    preambleSuccess = checkForPreamble();
    
    while (available()){  
      incommingByte = read();
      
      if (idenMatch == true) {
        return incommingByte;
      }

      else if (preambleSuccess == true){
        if (incommingByte == station_id[idenCount]){
          idenCount++;
        }
        else {
          preambleSuccess = false;
        }
        idenMatch = (idenCount == 2);
      }
    }
    delay(500);
  }
  return 0;
}

// empty the incomming serial buffer
void Communication::flushIncommingBuffer(){
  char incommingByte;

  while (available()){
    incommingByte = read();
  }
  
}

// check to see if we succesfully received the preamble
bool Communication::checkForPreamble(){
  char incommingByte;
  char preamble[6] = {'s', 't', 'r', 'e', 'e', 't'};
  int preamblemCount = 0;

  while (available()){
    incommingByte = read();
    delay(10);
    
    if (incommingByte == preamble[preamblemCount]){
      preamblemCount++;
      if (preamblemCount == 6){
        Serial.println("Preamble received");
        return true;
      }
    }
  }
  return false;
}

bool Communication::getNewId(){
  int charCount = 0;
  char incommingByte;
  int count = 0;

  Serial.println("Getting new ID");
  for (int i = 0; i < 10; i++){
    delay(500);
    while (available()){
      incommingByte = read();
      Serial.println(incommingByte);
      if (incommingByte == '<')
        break;
    }
    delay(100);
    while ((available()) && (count < 2)){
      incommingByte = read();
      Serial.println(incommingByte);
      station_id[count] = incommingByte;
      count++;
    }
    delay(100);
    while (available()){
      incommingByte = read();
      Serial.println(incommingByte);
      if (incommingByte == '>')
        return true;;
    }
  }
    
  return false;

}

char Communication::getId_1(){
  return station_id[0];
}

char Communication::getId_2(){
  return station_id[1];
}


