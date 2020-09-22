void setup()
{
  Serial.begin(9600);
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

 // size(320, 410);
 
   // Birds = new ArrayList();
  // for (int i=0; i<birdNum; i++) {
  //  Birdy = new BirdObject(random(0, 310), 0, random(5,8)+0.2);
   // Birds.add(Birdy);
 // }
 
  for (int i=0; i<birdDisplay; i++) {
     Birdy[i] = new BirdObject();
     Birdy[i]->Begin(random(0, 310), 0, 200, 0, int(random(255)), random(4)+0.2);
  }
 for(int i = 0; i < maxLEDs; i++){ // Initiate all leds as off
   brightness[i] = 0;
 }
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

// butt stuff
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}


// int birdNum = 1;

void loop()
{

 buttonRelease();

 if(LEDstate == 1){
   if(millis() > 500*birdDisplay+tenFlowTimer && birdDisplay < birdNum){ // Never go above birdNum, otherwise out of bounds
    Birdy[birdDisplay] = new BirdObject(); // Create a new bird
    Birdy[birdDisplay]->Begin(random(0, 310), 0, int(random(255)), int(random(255)), int(random(255)), random(8)+0.2); // Give it values
    birdDisplay ++; // Make sure it fits in the for loops
}
 }
if(LEDstate!=3){
  for (int i=0; i<birdDisplay; i++) {
     Birdy[i]->Move(); // Update the birds position
     initiateShine(Birdy[i]->posX, Birdy[i]->posY, Birdy[i]->r, Birdy[i]->g, Birdy[i]->b); //Set the colour for the pixel 
 if(LEDstate==2){
  strip.setPixelColor(LEDNum, Birdy[i]->r, Birdy[i]->g, Birdy[i]->b);
 }
}

  //////////// This updates the LEDs ////////////
 for (int i=0; i< maxLEDs; i++) {
  if(brightness[i] != 0){
  // Serial.println("Again the Number is " + i);
   ShineOn(i, Birdy[0]->speeds); //Get the right ID, brightness and speed to update LED
    }
  }
}
else if (LEDstate==3){
   keyPressed();
     Move();
}
  strip.show();
}
