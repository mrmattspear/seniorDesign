#include <Arduino.h>

typedef enum State {
  idle,
  sampleTemp,
  samplePow,
  errorCheck,
  calcTemp,
  calcPow,
  sendData,
  storeData,
  sleep
}State;

void setup() {
    // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  State state = idle;
  float tempData[5] = {0.0,0.0,0.0,0.0,0.0};
  float currData = 0.0;
  float voltData = 0.0;
  float errorCode = 0b0000000000;

switch(state){

case idle:
//delay every 60s
state = sampleTemp;
break;

case sampleTemp:
//function for sampling temp sensors 0:6
state = samplePow;
break;

case samplePow:
//function for sampling pow sensor
state = errorCheck;
break;

case errorCheck:
// iterate through sampled data
state = calcTemp;
break;

case calcTemp:
//calculate average temp, function should check relevant portion of errorCode
state = calcPow;
break;

case calcPow:
//calc power,  function should check relevant portion of errorCode
state = sendData;
break;

case sendData:
//pass data and error codes to comm function
if(){//check for server ack
//reset ack
state = idle;
}
else{//dataSend timeout
state = storeData;
}
break;

case storeData:
//start storing data if data send fail
break;

case sleep:
//sleep mode sample every 30m
break;
}
}
