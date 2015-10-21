/* 
 *  
 *  This code is meant to be upload to a ESP8266 01 wifi module
 *  
 *  Refer to this guide to connect the ESP to Arduino UNO or MEGA:
 *  http://www.instructables.com/id/noobs-guide-to-ESP8266-with-Arduino-Mega-2560-or-U/
 *  
 *  The ESP8266WiFi library is required:
 *  https://github.com/esp8266/Arduino
 *  
 *  This code, upon receiving a "getdata" request from the serial port, scans the wifi networks nearby,
 *  and gives back via serial port, as absolut number, the power in dBm of the most powerful network.
 *  
 *  Created in October 2015 - Andrea Fasolo Rao for 2MONOCHANNELS
 *  raoandrea@gmail.com - giorgos@2monochannels.com
 *  
 */


#include <ESP8266WiFi.h> // ESP8266 Library

unsigned long waittime = 5000;      //wait time between networks scans
unsigned long lastscan = millis();

int bestNetworkID = 99;     //ID of the most powerful network 
int bestNetworkPower = 99;  //power in dBm of the most powerful network
int worstNetworkID = 99;    //ID of the less powerful network, unused
String bestNetworkSSID;     //SSID of the most powerful network

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {               //this code runs once
  
  Serial.begin(115200);     //start serial communication. Speed depends on the revision of the module
  delay(10);
  
}

void loop() {               //this code keeps repeating

  serialEvent();            //check if data comming from serial port

    if (stringComplete) {                     //if the received String is complete...
      String bb=inputString.substring(0, 7);  //takes its first 7 characterss
      if (bb=="getdata"){                     //if the incoming String is "getdata"
         Serial.println(getdata());           //prints the result of the getdata() method, see line 56
         Serial.println();
      }
      inputString = "";                       //the String with the incoming characters is cleared
      stringComplete = false;                 //and the conditions set to false
    }

}

String getdata(){

    bestNetworkID = 99;
    worstNetworkID = 99;
    
    listNetworks();     //runs listNetwork() method, see line 78

    String message1 = String(bestNetworkPower);
    String message = String(message1+";");      //attaching a ";" character to the power of the best network
    return message;                             //this the value that will be sent via serial to the Arduino UNO
}

void serialEvent() {
      while (Serial.available()) {            //when the serial port is free...
          char inChar = (char)Serial.read();  //get the new byte from the serial port
          inputString += inChar;              //add it to the inputString
          if (inChar == '\n') {               //if the incoming character is a newline, set the string as complete
                stringComplete = true;
          }
      }
}

void listNetworks() {
  int numSsid = WiFi.scanNetworks();                  // scan for nearby networks:
  if (numSsid == -1) {                                //if there are no networks...
    Serial.println("Couldn't get a wifi connection"); //...prints an error
    bestNetworkPower = -99;                           //...and sets an invalid value
    while (true);                                     //wait to get networks SSIDs
    
  }

  //get the best connection:
  bestNetworkID = 0;
  for (int i = 1; i < numSsid; i++){      //this cycle finds the most powerful network, ignoring the one from the seat itself
    if ((WiFi.RSSI(i) > WiFi.RSSI(bestNetworkID)) && (String(WiFi.SSID(i)) != "Wifi-seat")){
      bestNetworkID = i;
    }
  }

  worstNetworkID = 0;
  for (int i = 1; i < numSsid; i++){    //this cycle finds the less powerful network
    if (WiFi.RSSI(i) < WiFi.RSSI(worstNetworkID)){
      worstNetworkID = i;
    }
  }

  bestNetworkPower = (WiFi.RSSI(bestNetworkID)*-1);   //dBm values are negative, this turns it to positive for convenience
  bestNetworkSSID = WiFi.SSID(bestNetworkID);

}
