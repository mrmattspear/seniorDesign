#include <Arduino.h>

enum State {
  idle,
  sampleTemp,
  samplePow,
  errorCheck,
  calcTemp,
  calcPow,
  sendData,
  storeData,
  sleep
  };

void setup() {
    // put your setup code here, to run once:
State state = idle;
int tempData[0:4] = {0,0,0,0,0};
int currData = 0;
int voltData = 0;
int errorCode = 0b0000000000;
}

void loop() {
  // put your main code here, to run repeatedly:
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
state = calcPower;
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
