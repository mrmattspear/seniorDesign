#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_MAX31865.h"
#include "Adafruit_INA219.h"
#include "SoftwareSerial.h"
#include "SparkFunESP8266WiFi.h"


typedef enum State {
  idle,
  sampleTemp,
  samplePow,
  errorCheck,
  calcTemp,
  sendData
  //storeData,
//  sleep
}State;
State state = idle;
Adafruit_INA219 ina219;

#define REF_RESISTOR 430.0 // reference resistor value in ohms for RTD amp
#define CSPIN10 10 //define spi cs pins for ease of reading
#define CSPIN9 9
#define CSPIN8 8
#define CSPIN7 7
#define CSPIN6 6
#define MILLIWATT_TO_WATT_CONVERSION 0.001
#define POWER_SAMPLE_FAILURE 128 //2^7 binary value

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
   //*----------Debug Setup Begin------------------------------------
    Serial.begin(9600);
      while (!Serial) {
   // will pause until serial console opens
    delay(1);
    }
    //------------Debug Setup End--------------------------------------*/

   //----------Temperature Sensor Setup Begin-----------------------
    for (int i = 0; i < 4; i++){
    max[i].begin(MAX31865_4WIRE); //initialize 4 wire  for each temp sensor
  }//-----------Temperature Senor Setup End--------------------------
   //----------Power Sensor Setup Begin-----------------------------
    ina219.begin(); //initialize power sensor
   //----------Power Sensor Setup End-------------------------------


}

void loop() {
  // put your main code here, to run repeatedly:

  float tempData[5] = {0.0,0.0,0.0,0.0,0.0};//array of float to hold sampled data from temp sensor/ amplfier modules
  int errorCode = 0b0000000000;             //int variable used to hold error code, parsed as binary value
  float power = 0;                          //float to hold sampled datum from ina219 power sensor
  float busvoltage = 0.0;
  float shuntvoltage = 0.0;
  float loadvoltage = 0.0;
  float current_mA    = 0.0;

/*
  Serial.print("Current:   "); Serial.print(current_mA); Serial.println(" A"); //Display current in Amps
  Serial.print("Voltage: "); Serial.print(loadvoltage); Serial.println(" V");  //Display voltage in Volts
  Serial.print("Power:  "); Serial.print(power); Serial.println(" W");         //Display power in Watts
  delay(2000
  */

switch(state){

case idle:
//delay every 60s
Serial.println("Idle");
state = sampleTemp;
break;

case sampleTemp:
Serial.println("Temp");
//function for sampling temp sensors 0:4

for(int i = 0; i < 5; i++){
tempData[i] = max[i].temperature(100, REF_RESISTOR);
}
/*Debug Messages Power Sensor
for(int i = 0; i < 5; i++){
Serial.println("Temperature Sensor %d: %lf degree C", i, tempData[i]);
}
Serial.println("")
delay(2000);
*/
state = samplePow;
break;

case samplePow:
//function for sampling pow sensor
power = ina219.getPower_mW() * MILLIWATT_TO_WATT_CONVERSION; //sample power, convert to Watts
busvoltage = ina219.getBusVoltage_V();
shuntvoltage = ina219.getShuntVoltage_mV();
loadvoltage = ina219.getBusVoltage_V();
current_mA    = ina219.getCurrent_mA();
//* Debug Messages Power Sensor
Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
Serial.print("Power:         "); Serial.print(power); Serial.println(" mW");
Serial.println("");
delay(2000);
//*/

state = errorCheck;
break;

case errorCheck:
Serial.println("errorCheck");
// iterate through sampled data
for(int i = 0; i < 5; i++){
  if(max[i].readFault()){//iterate through temp sensors to check for faults
    errorCode += 2^(i + 1); //add bit corresponding to faulty sensor
  }
}

if (power <= 0){
  errorCode += POWER_SAMPLE_FAILURE;
}

state = calcTemp;
break;

case calcTemp:
//calculate average temp, function should check relevant portion of errorCode

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
state = idle;
break;

  }
}


/*
//----------------Connecting to wifi network------------------------------
//----------------For wifi shield-----------------------------------------
const char mySSID[] = "yourSSIDhere";
const char myPSK[] = "yourPWDhere";

ESP8266Server server = ESP8266Server(80);

const char destServer[] = "example.com";
const String htmlHeader = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Connection: close\r\n\r\n"
                          "<!DOCTYPE HTML>\r\n"
                          "<html>\r\n";

const String httpRequest = "GET / HTTP/1.1\n"
                           "Host: example.com\n"
                           "Connection: close\n\n";

 // errorLoop prints an error code, then loops forever.
 void errorLoop(int error)
 {
   Serial.print(F("Error: ")); Serial.println(error);
   Serial.println(F("Looping forever."));
   for (;;)
     ;
 }



  void initializeESP8266()
  {
   // esp8266.begin() verifies that the ESP8266 is operational
   // and sets it up for the rest of the sketch.
   // It returns either true or false -- indicating whether
   // communication was successul or not.
   // true
   int test = esp8266.begin();
   if (test != true)
   {
     Serial.println(F("Error talking to ESP8266."));
     errorLoop(test);
   }
   Serial.println(F("ESP8266 Shield Present"));
 }

 void connectESP8266()
 {
   // The ESP8266 can be set to one of three modes:
   //  1 - ESP8266_MODE_STA - Station only
   //  2 - ESP8266_MODE_AP - Access point only
   //  3 - ESP8266_MODE_STAAP - Station/AP combo
   // Use esp8266.getMode() to check which mode it's in:
   int retVal = esp8266.getMode();
   if (retVal != ESP8266_MODE_STA)
   { // If it's not in station mode.
     // Use esp8266.setMode([mode]) to set it to a specified
     // mode.
     retVal = esp8266.setMode(ESP8266_MODE_STA);
     if (retVal < 0)
     {
       Serial.println(F("Error setting mode."));
       errorLoop(retVal);
     }
   }
   Serial.println(F("Mode set to station"));

   // esp8266.status() indicates the ESP8266's WiFi connect
   // status.
   // A return value of 1 indicates the device is already
   // connected. 0 indicates disconnected. (Negative values
   // equate to communication errors.)
   retVal = esp8266.status();
   if (retVal <= 0)
   {
     Serial.print(F("Connecting to "));
     Serial.println(mySSID);
     // esp8266.connect([ssid], [psk]) connects the ESP8266
     // to a network.
     // On success the connect function returns a value >0
     // On fail, the function will either return:
     //  -1: TIMEOUT - The library has a set 30s timeout
     //  -3: FAIL - Couldn't connect to network.
     retVal = esp8266.connect(mySSID, myPSK);
     if (retVal < 0)
     {
       Serial.println(F("Error connecting"));
       errorLoop(retVal);
     }
   }
 }

 void displayConnectInfo()
 {
   char connectedSSID[24];
   memset(connectedSSID, 0, 24);
   // esp8266.getAP() can be used to check which AP the
   // ESP8266 is connected to. It returns an error code.
   // The connected AP is returned by reference as a parameter.
   int retVal = esp8266.getAP(connectedSSID);
   if (retVal > 0)
   {
     Serial.print(F("Connected to: "));
     Serial.println(connectedSSID);
   }

   // esp8266.localIP returns an IPAddress variable with the
   // ESP8266's current local IP address.
   IPAddress myIP = esp8266.localIP();
   Serial.print(F("My IP: ")); Serial.println(myIP);
 }

 void clientDemo()
 {
   // To use the ESP8266 as a TCP client, use the
   // ESP8266Client class. First, create an object:
   ESP8266Client client;

   // ESP8266Client connect([server], [port]) is used to
   // connect to a server (const char * or IPAddress) on
   // a specified port.
   // Returns: 1 on success, 2 on already connected,
   // negative on fail (-1=TIMEOUT, -3=FAIL).
   int retVal = client.connect(destServer, 80);
   if (retVal <= 0)
   {
     Serial.println(F("Failed to connect to server."));
     return;
   }

   // print and write can be used to send data to a connected
   // client connection.
   client.print(httpRequest);

   // available() will return the number of characters
   // currently in the receive buffer.
   while (client.available())
     Serial.write(client.read()); // read() gets the FIFO char

   // connected() is a boolean return value - 1 if the
   // connection is active, 0 if it's closed.
   if (client.connected())
     client.stop(); // stop() closes a TCP connection.
 }

 void serverSetup()
 {
   // begin initializes a ESP8266Server object. It will
   // start a server on the port specified in the object's
   // constructor (in global area)
   server.begin();
   Serial.print(F("Server started! Go to "));
   Serial.println(esp8266.localIP());
   Serial.println();
 }

 void serverDemo()
 {
   // available() is an ESP8266Server function which will
   // return an ESP8266Client object for printing and reading.
   // available() has one parameter -- a timeout value. This
   // is the number of milliseconds the function waits,
   // checking for a connection.
   ESP8266Client client = server.available(500);

   if (client)
   {
     Serial.println(F("Client Connected!"));
     // an http request ends with a blank line
     boolean currentLineIsBlank = true;
     while (client.connected())
     {
       if (client.available())
       {
         char c = client.read();
         // if you've gotten to the end of the line (received a newline
         // character) and the line is blank, the http request has ended,
         // so you can send a reply
         if (c == '\n' && currentLineIsBlank)
         {
           Serial.println(F("Sending HTML page"));
           // send a standard http response header:
           client.print(htmlHeader);
           String htmlBody;
           // output the value of each analog input pin
           for (int a = 0; a < 6; a++)
           {
             htmlBody += "A";
             htmlBody += String(a);
             htmlBody += ": ";
             htmlBody += String(analogRead(a));
             htmlBody += "<br>\n";
           }
           htmlBody += "</html>\n";
           client.print(htmlBody);
           break;
         }
         if (c == '\n')
         {
           // you're starting a new line
           currentLineIsBlank = true;
         }
         else if (c != '\r')
         {
           // you've gotten a character on the current line
           currentLineIsBlank = false;
         }
       }
     }
     // give the web browser time to receive the data
     delay(1);

     // close the connection:
     client.stop();
     Serial.println(F("Client disconnected"));
   }

 }


 // serialTrigger prints a message, then waits for something
 // to come in from the serial port.
 void serialTrigger(String message)
 {
   Serial.println();
   Serial.println(message);
   Serial.println();
   while (!Serial.available())
     ;
   while (Serial.available())
     Serial.read();
 }


//------------------------------------------------------------------------


 void setup() {
   Serial.begin(9600);
   uint32_t currentFrequency;

//--------------wifi shield-----------------------------------------------
   serialTrigger(F("Press any key to begin."));

  // initializeESP8266() verifies communication with the WiFi
  // shield, and sets it up.
  initializeESP8266();

  // connectESP8266() connects to the defined WiFi network.
  connectESP8266();

  // displayConnectInfo prints the Shield's local IP
  // and the network it's connected to.
  displayConnectInfo();

  serialTrigger(F("Press any key to connect client."));
  clientDemo();

  serialTrigger(F("Press any key to test server."));
  serverSetup();
}





 void loop() {
   serverDemo(); //Wifi Shield

   int tempData[5] = {0,0,0,0,0};
   //-------------------------------------------------------------------
   int errorCode = 0b0000000000;
*/
