#include <ESP8266WiFi.h>


//ESP8266WiFiMulti wifiMulti;
//WiFiClient client;

unsigned long waittime = 5000; //waiting time between scans
unsigned long lastscan = millis();

//int IDs[20];
//String SSIDs[20];
//int power[40];

int bestNetworkID = 99;
int bestNetworkPower = 99;
int worstNetworkID = 99;
String bestNetworkSSID;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  
  Serial.begin(115200);
  delay(10);

  for (int i = 0; i<40; i++){
    //IDs[i] = 99;
    //SSIDs[i] = "";
    //power[i] = 0;
  }

}

void loop() {

  serialEvent(); //check if data comming from serial port
    if (stringComplete) {
     // Serial.println("ok");
      String bb=inputString.substring(0, 7);
     // Serial.println(bb);
      //Serial.println(bb.length());
      if (bb=="getdata"){  //if cmd "getdata"
         Serial.println(getdata());
         Serial.println();
      }
      inputString = "";
      stringComplete = false;
    }

/*
  while ( (millis()-lastscan > waittime)){
    listNetworks();
    lastscan = millis();
    Serial.println();
    
  }

  */
  /*
  while ( (millis()-lastscan > waittime)){
    bestNetworkID = 99;
    worstNetworkID = 99;
      for (int i = 0; i<40; i++){
    }
    
    Serial.println("Scanning networks");
    listNetworks();
    lastscan = millis();
    Serial.println();
  }

  */

}

String getdata(){

    bestNetworkID = 99;
    worstNetworkID = 99;
    //  for (int i = 0; i<40; i++){
    //}
    
    //Serial.println("Scanning networks");
    listNetworks();

    String message1 = String(bestNetworkPower);
    String message = String(message1+";");
    return message;
}

void serialEvent() {
      while (Serial.available()) {
          // get the new byte:
          char inChar = (char)Serial.read();
          // add it to the inputString:
          inputString += inChar;
         // Serial.println(inChar);
          // if the incoming character is a newline, set a flag
          if (inChar == '\n') {
                stringComplete = true;
          }
      }
}

void listNetworks() {
  // scan for nearby networks:
  //Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    bestNetworkPower = -99;
    while (true);
    
  }

  // print the list of networks seen:
  //Serial.print("number of available networks:");
  //Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) { //gets data into the arrays
    //SSIDs[thisNet] = WiFi.SSID(thisNet);
    //power[thisNet] = WiFi.RSSI(thisNet);
        
    //Serial.print(thisNet);
    //Serial.print(") ");
    //Serial.print(WiFi.SSID(thisNet));
    //Serial.print("\tSignal: ");
    //Serial.print(WiFi.RSSI(thisNet));
    //Serial.println(" dBm");
    //Serial.print("\tEncryption: ");
    //printEncryptionType(WiFi.encryptionType(thisNet));
  }

  // GET THE BEST CONNECTION
  bestNetworkID = 0;
  for (int i = 1; i < numSsid; i++){
    if ((WiFi.RSSI(i) > WiFi.RSSI(bestNetworkID)) && (String(WiFi.SSID(i)) != "Wifi-seat")){
      bestNetworkID = i;
    }
  }

  worstNetworkID = 0;
  for (int i = 1; i < numSsid; i++){
    if (WiFi.RSSI(i) < WiFi.RSSI(worstNetworkID)){
      worstNetworkID = i;
    }
  }

  bestNetworkPower = (WiFi.RSSI(bestNetworkID)*-1);
  bestNetworkSSID = WiFi.SSID(bestNetworkID);

  //Serial.println(bestNetworkID);
  /*
  Serial.print("best connection is... ");
  Serial.print(bestNetworkID);
  Serial.print(": ");
  Serial.print(WiFi.SSID(bestNetworkID));
  Serial.print(", Power: ");
  Serial.println(WiFi.RSSI(bestNetworkID));
  
  Serial.print("worst connection is... ");
  Serial.print(worstNetworkID);
  Serial.print(": ");
  Serial.print(WiFi.SSID(worstNetworkID));
  Serial.print(", Power: ");
  Serial.println(WiFi.RSSI(worstNetworkID));
  Serial.println();
  */
}
/*
void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
  }
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];

  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}
*/created by 2monochannels from andrea fasolo rao
