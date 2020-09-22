// Script by Matt, June 2015
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 13
const int maxLEDs = 1054;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxLEDs, PIN, NEO_GRB + NEO_KHZ800);

int brightness[maxLEDs];
int LEDsArray[] = {23,25,26,27,38,40,40,40,40,37,36,35,35,34,34,34,34,34,35,35,35,37,40,40,40,40,38,27,26,25,24};
// int Rgb[1056][3];

int stripNum; // This is which strip the LED is on
int rowNum; //This is how far up the LED is
int LEDNum; // This is the LED ID
const int birdNum = 10; // Total nUmber of Birds flying
int birdDisplay = 2; // Birds on display  
bool flyMyPretties = false;
int tenFlowTimer = 0;

//  Butt stuff
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int LEDstate = 0;

///SNAAAAAAAAAAAAAAAAAAAAAAKKKKKKKKEEEEEEEEEEEEE
int angle=0;
int snakesize=5;
int aTime=0;
int headx[100];
int heady[100];
int  applex=(round(random(31))+1)*10;
int  appley=(round(random(40))+1)*10;
boolean redo=true;
boolean stopgame=false;
char val; // Data received from the serial port
float snakeSpeed = 3.0;


class BirdObject {
  public:
  float posX;
  float posY;
  float speeds;
  int r,g,b;
  void Move();
  BirdObject();
 void Begin(float inX, float inY, int _r, int _g, int _b, float inSPEED);
  private:
  float dirAngle=0;            // direction of birds
  float randomSpeedChange=random(1)-0.5;       // magnitude of random speed changes
  int unrest=10;                                // % chance of random changes
  
    float minSpeed=3;                            // lower speed limit
  float maxSpeed=8;                            // upper speed limit
  int timer;
  float endTime = 1000;
  float moveStepX = 0;
  float moveStepY = 1;
  float dir = 0;
  float ranWave;  // This is the speed it spirals at left to right, lower is slower
  float ranWaveWidth = random(5, 25); // This is the width between each spiral side, larger is wider
};

BirdObject::BirdObject(){
} 
 
void BirdObject::Begin(float inX, float inY, int _r, int _b, int _g, float inSPEED){
    posX = inX;
    posY = inY; 
    r = _r;
    g = _g;
    b = _b;
    speeds = inSPEED;
    timer = millis();
    if(LEDstate==0){
      ranWave = random(1, 7);
    }
    else if (LEDstate == 1){
     ranWave = random(1, 10);
    }
     else if (LEDstate == 2){
        minSpeed=1;                 
        maxSpeed=4;  
        ranWave = random(1, 7);
     }
      else if (LEDstate == 4){
        minSpeed=3;                 
        maxSpeed=10;  
        ranWave = random(20, 30);
        ranWaveWidth = random(5, 20);
     }
  }

void BirdObject::Move() {
  if(LEDstate!=4){
    if (endTime <=  millis() - timer) {
       if(LEDstate==0 || LEDstate == 2){
        dir = cos(radians(random(-100, 100)));
       }
        else {
           dir = cos(degrees(random(20, 160))); // To get an even portion from left to right, go between 0, 180 or 0 to PI
        }
        timer = millis();
      endTime = random(500, 3000);
      ranWave = random(1, 80);; // This is the speed it spirals at left to right, lower is slower
      ranWaveWidth = random(5, 25); // This is the width between each spiral side, larger is wider
    } 
  }
   // if(posX< 160){
     // dir += 0.1;}
     // else if(posX>160){
     // dir -=0.1; }
     float wave;
      if(LEDstate==0 || LEDstate==2){
     wave = sin(radians(millis()/ranWave));
     moveStepX = dir + wave;
     moveStepX = moveStepX * speeds;
      }
      else if(LEDstate == 1 || LEDstate == 4){
         wave = sin(radians(millis()*(ranWave*0.1)));
         moveStepX = dir + wave * ranWaveWidth;
       }
    
    moveStepY = 1;
  //  moveStepX = moveStepX * speeds;
    moveStepY = moveStepY * speeds;
    posX += moveStepX;
    posY += moveStepY;
    // check border condition
    if (posX<0) posX+=320;
    if (posX>=320) posX-=320;
    if (posY<0) posY+=410;
    if (posY>=410) {
      posY-=410;
      if(LEDstate == 4){
        speeds = random(6,10);
        posX = random(0,310); 
      }
    }
    // RandomChange the movement speed
    if(LEDstate !=4){
    if (random(10)<unrest) {          
      speeds += randomSpeedChange;
      randomSpeedChange += 0.05-random(0.01, 0.5);
      randomSpeedChange = constrain(randomSpeedChange, -0.3, 0.3);
      speeds = constrain(speeds, minSpeed, maxSpeed);
    }
    }
     else {
      ranWave = random(20, 30);
    ranWaveWidth = random(5, 20);
    dir = cos(degrees(random(20, 120)));
   
    
    speeds += 0.15;
     }
  }

BirdObject *Birdy[birdNum];




void ShineOn(int ID, int thisSpeed){

 // thisSpeed = (red*0.17) + (green*0.12) + (blue*0.07);
  brightness[ID] -= 1*thisSpeed;
   
  if(brightness[ID] <= 0){
    brightness[ID] = 0;
  }

   ///// For really cool effect just use this //////
    // int bee = 255*brightness[ID];
    if(LEDstate == 2){
      uint32_t color = strip.getPixelColor(ID);
        color = color*brightness[ID]/255;
      strip.setPixelColor(ID, color);
    }
    else{
  int red = strip.getRedColor(ID); // Had to mess with the library but was able to gather rgb, sets it to the old one
  int blue = strip.getGreenColor(ID);
  int green = strip.getBlueColor(ID);
  
   int arr = red*brightness[ID]/255;
   int gee = blue*brightness[ID]/255;
   int bee = green*brightness[ID]/255;
  strip.setPixelColor(ID, arr, gee, bee);
    }
  }
  
 
void initiateShine(float pX, float pY, int red, int green, int blue){
     stripNum = (int)(map(pX, 0, 320, 0, 31));
     rowNum = (int)(map(pY, 0, 410, 0, 40));
     LEDNum = 0;
 for(int n = 0; n < stripNum; n++){
    LEDNum += LEDsArray[n];
  }
    LEDNum += rowNum;
   if(rowNum < LEDsArray[stripNum]){
    brightness[LEDNum] = 255;
  if(LEDstate!=2){
    strip.setPixelColor(LEDNum, red, green, blue); /// I set the initial value here, so it can be taken by the led.
    LEDNum = 0;
  }
   }

}

void buttonRelease(){
    // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;


  // turns on the LED every four button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
    LEDstate ++;

    if(LEDstate > 4)
    {
      LEDstate = 0;
    }
    //Green and Gold
    if(LEDstate == 0){
      birdDisplay = 2;
      Birdy[0]->Begin(random(0, 310), 0, 0, 38, 158, random(8)+0.2); // Give it values
       Birdy[1]->Begin(random(0, 310), 0, 200, 0, 109, random(8)+0.2); // Give it values
    }
    // 10Flow
    else if(LEDstate == 1){
      birdDisplay = 1;
      tenFlowTimer = millis();
       for (int i=0; i<birdDisplay; i++) {
     Birdy[i] = new BirdObject();
     Birdy[i]->Begin(random(0, 310), 0, 200, 0, int(random(255)), random(4)+0.2);
  }
    }
  else if(LEDstate == 2){
     birdDisplay = 2;
     Birdy[0]->Begin(random(0, 310), 0, int(random(255)), int(random(255)), int(random(255)), random(4)+0.2); // This is for the sending the signal away
     Birdy[1]->Begin(random(0, 310), 0, 200, 0, int(random(255)), random(4)+0.2); // This is for the sending the signal away

  }
     else if(LEDstate == 4){
     birdDisplay = 2;
  Birdy[0]->Begin(190, 0, 20, 200, 60, random(4, 8)+0.2); // Give it values  
Birdy[1]->Begin(160, 0, 0, 105, 168, random(4, 8)+0.2); // Give it values  
Birdy[2]->Begin(190, 0, 255, 0, 50, random(4, 8)+0.2); // Give it values  
Birdy[3]->Begin(220, 0, 105, 50, 180, random(4, 8)+0.2); // Give it values  
Birdy[4]->Begin(250, 0, 63, 0, 255, random(4, 8)+0.2); // Give it values  
  }
    Serial.println("LEDstate: ");
     Serial.println(LEDstate);
       buttonPushCounter++;
   
   // Resets it all
   for(int i = 0; i < maxLEDs; i++){ // Initiate all leds as off
   brightness[i] = 0;
  ShineOn(i, Birdy[0]->speeds); //Get the right ID, brightness and speed to update LED
    } 
  } 
  else {
    digitalWrite(ledPin, LOW);
  //  LEDstate = 1;
  }
 
  
}


