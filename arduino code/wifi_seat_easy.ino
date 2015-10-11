
int ledPin = 13;

int pirPins[] = {3,4,5,6,7}; 

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

float redVal = 255;
float grnVal = 255;
float bluVal = 255;

int lightPin = A0;

//int lightPin1 = A0;
//int lightPin2 = A1;

int lightValue;
int maxValue = 75;

int calibrationTimeSec = 10;

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 500;  

boolean lockLow = true;
boolean takeLowTime;
boolean PirStatus = false;


float maxBrightness = 100;
float minBrightness = 5;
float brightness = 50;

boolean stringComplete = false;
String inputString="";
unsigned long lastUpdate = millis();
unsigned long waitTime = 10000;
String data = "";

float ledcolor = 0;
float input = 100;


unsigned long lightWaitTime = 500;
unsigned long lightLastUpdate = millis();

unsigned long PirWaitTime = 100;
unsigned long PirLastUpdate = millis();

unsigned long wifiWaitTime = 20000;
unsigned long wifiLastUpdate = millis();


void setup() {
  
  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(lightPin, INPUT);


  pinMode(pirPins[0], INPUT);
  pinMode(pirPins[1], INPUT);
  pinMode(pirPins[2], INPUT);
  pinMode(pirPins[3], INPUT);
  pinMode(pirPins[4], INPUT);
  
  
  lightValue = maxValue;

  analogWrite(redPin, 50);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 50);
  // PIR SENSOR CALIBRATION
  delay(calibrationTimeSec*1000);

  lightValue = analogRead(lightPin);

  PirStatus = false;;
    for (int i = 3; i < 8; i++){
      PirStatus = (PirStatus || digitalRead(pirPins[i]));
    }
  
//  if (digitalRead(pirPin) == HIGH){
//      PirStatus = true;
//    }
//  if (digitalRead(pirPin) == LOW){
//      PirStatus = false;
//  }

  Serial.println("getdata");  //first request for data
  delay(2000);

  wifiLastUpdate = millis() - 19000;

}

void loop() {

  while ((millis() - lightLastUpdate) > lightWaitTime){ 
    lightValue = analogRead(lightPin);
    //Serial.println(lightValue);
    lightLastUpdate = millis();
  }

  while ((millis() - PirLastUpdate) > PirWaitTime){
    
    PirStatus = false;
    for (int i = 3; i < 8; i++){
      PirStatus = (PirStatus || digitalRead(pirPins[i]));
      //Serial.println(PirStatus);
    }
//    
//    if (digitalRead(pirPin) == HIGH){
//      PirStatus = true;
//    }
//    if (digitalRead(pirPin) == LOW){
//      PirStatus = false;
//    }
      //Serial.println(PirStatus);
      PirLastUpdate = millis();
  }

    maxBrightness = 50 + lightValue; //RIVEDERE CALCOLO CON VALORI DECENTI

  if (!PirStatus){
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

  //Serial.println(brightness);

  float aredVal = (redVal/255) * brightness;
  float agrnVal = (grnVal/255) * brightness;
  float abluVal = (bluVal/255) * brightness;

  analogWrite(redPin, aredVal);
  analogWrite(greenPin, agrnVal);
  analogWrite(bluePin, abluVal);

  // READING SENSORS!

  while (millis() - wifiLastUpdate > wifiWaitTime){

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

    while (!stringComplete) {
          serialEvent();
          if (millis() > now + 5000) {
            blinknok();
            break;
          }
    }

    if (stringComplete==true)  {
  String bb=inputString.substring(0, inputString.length()-1);
            Serial.println(bb);
            data=bb;
            blinkok();  //do else
            lastUpdate=millis();
        }

        inputString = "";
        stringComplete = false;

        String aa="";

        for (int i=0; i<data.length(); i++)  {
          aa+=data.substring(i,i+1);
          if (data.substring(i,i+1)==";") {
              input=aa.substring(0,aa.length()-1).toInt();
              aa="";
          }
        }

        if (input != 0){

          ledcolor = input / 100;
          ledcolor = ledcolor * 255;// from dBm to a number and then a color

          redVal = ledcolor;
          grnVal = 255 - ledcolor;
          bluVal = 0;
        }
        
    //delay(10);
    wifiLastUpdate = millis();
  }
  

}

boolean getPirsStatus(){

}

void serialEvent() {
      while (Serial.available()) {
          // get the new byte:
          char inChar = (char)Serial.read();
          // add it to the inputString:
          inputString += inChar;
          // if the incoming character is a newline, set a flag
          if (inChar == '\n') {
                stringComplete = true;
          }
      }
}

void blinkok(){
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


/*********************************************
 * Function dedicated to generate Blink noOK *
 *********************************************/

void blinknok(){
  delay(1000);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(300);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);

}

void blinkbadnum(){
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
// created by 2monochannels from andrea fasolo rao
