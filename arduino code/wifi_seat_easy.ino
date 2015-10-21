/*
 * 
 * This code is meant to be uploaded to an Arduino UNO board
 * 
 * This code sends a "getdata" request to an ESP8266 module connected via serial and expects to get back a positive integer number,
 * representing the power in dBm of the best WiFi network around.
 * 
 * Also, two photoresistors collects informations about the light level around the seat.
 *  
 * Then, it uses these values to control the color and the brightness of RGB LEDs.
 * 
 * The LEDs gets brighter when someone approaches, sensed by 5 PIR sensors.
 * 
 * Created in October 2015 - Andrea Fasolo Rao for 2MONOCHANNELS
 * raoandrea@gmail.com - giorgos@2monochannels.com
 * 
 */


/*
 *  Pins used to connect sensors and LEDs - ESP8266 must be connected to 0 and 1
 */

int ledPin = 13;  //using integrated LED for debug

int pirPins[] = {3,4,5,6,7};  //PIR (passive infrared sensors) pins

int redPin = 9;     //RGB LEDs pins
int greenPin = 10;
int bluePin = 11;

float redVal = 255; //values to control LEDs
float grnVal = 255;
float bluVal = 255;

int lightPin1 = A0; //photoresistors pins
int lightPin2 = A1;

float lightValue;   //mean value from the light sensors
int maxValue = 75;

int calibrationTimeSec = 20;  //time required to calibrate PIRs

long unsigned int lowIn;      //the time when the sensor outputs a low impulse

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 500;  

boolean lockLow = true;   //helping variable for PIRs 
boolean takeLowTime;      //time required to read "low" from the PIRs

boolean PirStatus = false;  //current global status of the PIRs
boolean PirStatuses[] = {false, false, false, false, false}; //array with the statuses for every single PIR
int PirCount = 0;           //number of PIRs reporting movement


float maxBrightness = 100;  //max brightness of the LEDs
float minBrightness = 15;   //min brightness of the LEDs
float brightness = 50;      //brightness of the LEDs

boolean stringComplete = false;     //checks if the string from the serial port is complete
String inputString="";              //string incoming from the serial port
unsigned long lastUpdate = millis();  
unsigned long waitTime = 10000;     //time between requests to the WiFi module
String data = "";                   //data from the serial port

float ledcolor = 0;                 //"one variable to rule them all" - from this number will be calculated R G and B values
float input = 100;


int pirCounter = 3;


unsigned long lightWaitTime = 250;    //time betweend photoresistors readings
unsigned long lightLastUpdate = millis();

unsigned long PirWaitTime = 500;      //time between PIRs readings
unsigned long PirLastUpdate = millis();

unsigned long wifiWaitTime = 20000;   //time between wifi power requests
unsigned long wifiLastUpdate = millis();


void setup() {              //this code runs once
  
  Serial.begin(115200);     //start serial communication. Speed depends on the revision of the module
  
  pinMode(ledPin, OUTPUT);  //setting the used pins to INPUT or OUTPUT
  digitalWrite(ledPin, LOW);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(lightPin1, INPUT);
  pinMode(lightPin2, INPUT);


  pinMode(pirPins[0], INPUT);
  pinMode(pirPins[1], INPUT);
  pinMode(pirPins[2], INPUT);
  pinMode(pirPins[3], INPUT);
  pinMode(pirPins[4], INPUT);
  
  
  lightValue = maxValue;

  analogWrite(redPin, 255);   //routine to check that the LEDs are working fine
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);

  delay(1000);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  delay(1000);

  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);

  delay(1000);

  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  delay(1000);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);

  delay(1000);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);

  delay(1000);

  analogWrite(redPin, 50);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 50);
  
  // PIR SENSOR CALIBRATION
  delay(calibrationTimeSec*1000);

  float lightValue1 = analogRead(lightPin1);    //reads photoresistors values
  float lightValue2 = analogRead(lightPin2);
  lightValue = (lightValue1 + lightValue2) / 2;
  lightValue = lightValue/4;                    //read values are 0-1024, output msut be 0-255, so we adapt that

  PirStatus = false;                            //Setting the PIRs readings to false before making a new read
  PirCount = 0;
    for (int i = 3; i < 8; i++){                //reading all the PIRs
      PirStatuses[i] = digitalRead(pirPins[i]);
      if (PirStatuses[i]){                      //everytime a PIR reports movement...
        PirCount++;                             //increase the count
      }
    }

    if (PirCount >= 3){                         //if at least three PIRs are positive, report movement globally
      PirStatus = true;
    }
    else {
      PirStatus = false;
    }

  Serial.println("getdata");  //first request for data
  delay(2000);

  wifiLastUpdate = millis() - 19000;            //first wifi request will be in one second instead of twenty

}

void loop() {       //this code keeps repeating

  while ((millis() - lightLastUpdate) > lightWaitTime){ //if lightWaitTime is passed, read new light values
    
    float lightValue1 = analogRead(lightPin1);
    float lightValue2 = analogRead(lightPin2);
    lightValue = (lightValue1 + lightValue2) / 2;
    lightValue = int(lightValue/4);                     //scaling from 0-1024 to 0-255
    
    lightLastUpdate = millis();
  }

  while ((millis() - PirLastUpdate) > PirWaitTime){     //if PirWaitTime is passed, read new PIRs values
    
    PirStatus = false;
    PirCount = 0;
    
    for (int i = 3; i < 8; i++){      //reading all the PIRs
      PirStatuses[i] =  digitalRead(pirPins[i]);
      if (PirStatuses[i]){            //everytime a PIR reports movement...
        PirCount++;                   //increase the count
      }
    }

    if (PirCount >= 3){               //if at least three PIRs are positive, report movement globally
      PirStatus = true;
    }
    else {
      PirStatus = false;
    }

      PirLastUpdate = millis();
  }

    maxBrightness = lightValue;     //the maximum brightness of the LEDs depends on the light received by the light sensor

  if (!PirStatus){                  //creates a smooth transition when dimming or brightening the LEDs
    if (brightness > minBrightness){
      brightness--;
      delay(2);
    }
  }
  if (PirStatus){
    if (brightness < maxBrightness){
      brightness++;
      delay(2);
    }
  }

  float aredVal = (redVal/255) * brightness;  //the R G B values are scaled with the current brightness value
  float agrnVal = (grnVal/255) * brightness;
  float abluVal = (bluVal/255) * brightness;


  analogWrite(redPin, aredVal);             //writes values to the LEDs
  analogWrite(greenPin, agrnVal);
  analogWrite(bluePin, abluVal);

  // READING SENSORS!

  while (millis() - wifiLastUpdate > wifiWaitTime){ //if wifiWaitTime is passed, sends a new request for the wifi power

    digitalWrite(ledPin,HIGH);  // debug pin dance for feedback
    delay(100);
    digitalWrite(ledPin,LOW);
    delay(50);
    digitalWrite(ledPin,HIGH);
    delay(100);
    digitalWrite(ledPin,LOW);
    delay(50);
    digitalWrite(ledPin,HIGH);
    delay(100);
    digitalWrite(ledPin,LOW);
    
    Serial.println("getdata");  // requesting data to ESP
    unsigned long now = millis();

    while (!stringComplete) {   //waits 5 seconds for a valid response from the ESP
          serialEvent();        //checks serial port for incoming data
          if (millis() > now + 5000) {
            blinknok();         //debug pin dance to report a problem 
            break;
          }
    }

    if (stringComplete==true)  {                                        //when the string from the serial port is complete..
            String bb=inputString.substring(0, inputString.length()-1); //...takes the input string, cutting off the last character
            Serial.println(bb);
            data=bb;
            blinkok();            //debug pin dance for feedback
            lastUpdate=millis();
        }

        inputString = "";         //the String with the incoming characters is cleared
        stringComplete = false;   //and the conditions set to false

        String aa="";

        for (int i=0; i<data.length(); i++)  {              //checks the incoming string for a ";" character, wich marks the end of the string
          aa+=data.substring(i,i+1);
          if (data.substring(i,i+1)==";") {
              input=aa.substring(0,aa.length()-1).toInt();  //takes only the dBm value without the ";" and converts it to integer
              aa="";                                        //string cleared
          }
        }

        if (input != 0){          //if the value received is not zero...

          ledcolor = input * 2,55;  // converts it from dBm to a number and then a color

          redVal = ledcolor;
          grnVal = 255 - ledcolor;
          bluVal = 0;
        }
        
    wifiLastUpdate = millis();
  }
  

}


void serialEvent() {
      while (Serial.available()) {            //when the serial port is free...
          
          char inChar = (char)Serial.read();  //get the new byte
          inputString += inChar;              //add it to the inputString:
          if (inChar == '\n') {               // if the incoming character is a newline, set the string as complete
                stringComplete = true;
          }
      }
}

void blinkok(){       // debug function "Blink OK"
  delay(1000);
  digitalWrite(13,HIGH);
  delay(200);
  digitalWrite(13,LOW);
  delay(100);
  digitalWrite(13,HIGH);
  delay(200);
  digitalWrite(13,LOW);
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  delay(200);
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
}




void blinknok(){      // debug function "Blink no OK"
  delay(1000);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(300);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);

}

void blinkbadnum(){    // debug function "Blink bad number"
   delay(1000);
  digitalWrite(13,HIGH);
  delay(2000);
  digitalWrite(13,LOW);
  delay(300);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(300);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
}
