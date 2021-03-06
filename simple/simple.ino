// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            13

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1054

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ400);

int delayval = 500; // delay for half a second

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
for(int n=0;n<3;n++){
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(1055-i, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.setPixelColor(1054-i, pixels.Color(0,0,255)); // Moderately bright green color.
    pixels.setPixelColor(1020-i, pixels.Color(0,0,0)); // Moderately bright green color.
  pixels.setPixelColor(1015-i, pixels.Color(0,0,255)); // Moderately bright green color.
    pixels.setPixelColor(800+i, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.setPixelColor(805+i, pixels.Color(200,0,0)); // Moderately bright green color.
    pixels.setPixelColor(847+i, pixels.Color(0,0,0)); // Moderately bright green color.
  pixels.setPixelColor(848+i, pixels.Color(200,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(200); // Delay for a period of time (in milliseconds).

  }
}
}
