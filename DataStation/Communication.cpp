#include "Communication.h"
#include <delay.h>

// check to see if there are available commands
int Communication::getDroneCommand(){
  char incommingByte;
  char preamble[6] = {'s', 't', 'r', 'e', 'e', 't'};
  bool idenMatch = false;
  bool preambleSuccess = false;
  int preamblemCount = 0;
  int idenCount = 0;

  for (int i = 0; i < 10; i++){
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
          preamblemCount = 0;
        }
        idenMatch = (idenCount == 2);
      }

      else if (incommingByte == preamble[preamblemCount]){
        preamblemCount++;
        preambleSuccess = (preamblemCount == 6);
      }

      else {
        preamblemCount = 0;
      }
    }
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

