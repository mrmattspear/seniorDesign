#include <Arduino.h>
#include <Adafruit_MAX31865.h>

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


#define REF_RESISTOR 430.0 // reference resistor value for RTD amp

#define CSPIN10 10 //define spi cs pins for ease of reading
#define CSPIN9 9
#define CSPIN8 8
#define CSPIN7 7
#define CSPIN6 6

/*configure array of temperature amplifier objects for SPI communication*/
Adafruit_MAX31865 max[5] = {
  Adafruit_MAX31865(CSPIN10),
  Adafruit_MAX31865(CSPIN9),
  Adafruit_MAX31865(CSPIN8),
  Adafruit_MAX31865(CSPIN7),
  Adafruit_MAX31865(CSPIN6),
};

void setup() {
    // put your setup code here, to run once:

    for (int i = 0; i < 4; i++){
    max[i].begin(MAX31865_4WIRE); //initialize 4 wire  for each temp sensor
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  State state = idle;

  float tempData[5] = {0.0,0.0,0.0,0.0,0.0};
  /*

  float currData = 0.0;
  float voltData = 0.0;
  float errorCode = 0b0000000000;
*/
switch(state){

case idle:
//delay every 60s
state = sampleTemp;
break;

case sampleTemp:
//function for sampling temp sensors 0:4
for(int i = 0; i < 5; i++){
tempData[i] = max[i].temperature(100, REF_RESISTOR);
}
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
/*
if(){//check for server ack
//reset ack
state = idle;
}
else{//dataSend timeout
state = storeData;
}
*/
break;

case storeData:
//start storing data if data send fail
break;

case sleep:
//sleep mode sample every 30m
break;
}
}
