#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

int x = 150; //Tijdelijk!

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  strip.begin();
  strip.show();
}

void loop() {
  while(/*speedwaarde=actief/hoog ofzo?*/ 1){
    setColor(150, 0, 0);  // red
    colorWipe(strip.Color(150, 0, 0), 100);
    delay(x);
    setColor(80, 80, 0);  // green
    colorWipe(strip.Color(80, 80, 0), 100);
    delay(x);
    setColor(0, 80, 80);  // blue
    colorWipe(strip.Color(0, 80, 80), 100);
    delay(x);
    setColor(80, 0, 80);  // yellow
    colorWipe(strip.Color(80, 0, 80), 100);
    delay(x);
    setColor(0, 150, 0);  // purple
    colorWipe(strip.Color(0, 150, 0), 100);
    delay(x);
  }
}


void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
