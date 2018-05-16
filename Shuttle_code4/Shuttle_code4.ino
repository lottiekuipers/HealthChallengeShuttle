//Muziek pin = 8

//MPU-6050
//A4 - SDA
//A5 - SCL
//2 - INT



#include <Adafruit_NeoPixel.h>
#include<Wire.h>
#define PIN 6
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
#include "pitch.h"
#define melodyPin 8

float noteDurations[] = {
  2, 4, 0, 2, 4, 0, 0.7, 0.5
};

int melody[] = {
  NOTE_A5, NOTE_E5, 0, NOTE_F5, NOTE_C5, 0, NOTE_D5, NOTE_B4
};

// notes in the melody:
int melodyf[] = {
  NOTE_E5, NOTE_F5, NOTE_G5, NOTE_C6, NOTE_D5, NOTE_E5, NOTE_F5, 0, 0, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_F6, 0,
  NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_C6, 0, NOTE_D6, NOTE_E6, NOTE_F6,
  NOTE_G5,NOTE_G5, NOTE_E6, NOTE_D6, NOTE_G5, NOTE_E6, NOTE_D6, NOTE_G5, NOTE_F6, NOTE_E6, NOTE_D6, NOTE_C6
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
float noteDurationsf[] = {
  4, 8, 8, 1, 4, 8, 1, 0, 0, 4, 8, 8, 1, 0, 4, 8, 2, 2, 2, 4, 8, 8, 1, 0, 4, 8, 0.7, 4, 8, 2.5, 4, 8, 2.5, 4,
  8, 2.5, 4, 8, 2
};

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az, oax, oay, oaz;

const int MPU_addr = 0x68; // I2C address of the MPU-6050
uint16_t AcX, AcY, AcZ, oAcX, oAcY, oAcZ;
int16_t Tmp;

int x = 150; //Tijdelijk!
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int state = 0;
int notes = 0;

#define LED_PIN 13
bool blinkState = false;
int nrsongs = 1;
int nrsongsp = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  strip.begin();
  strip.show();

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize serial communication
  Serial.begin(38400);
  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


  pinMode(LED_PIN, OUTPUT);

  rAc2();
  rAc2();
}

void rAc2()
{
  accelgyro.getAcceleration(&ax, &ay, &az);

  oax = ax;
  oay = ay;
  oaz = az;

  // display tab-separated accel x/y/z values
  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.println("\t");

  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

void loop()
{
  rAc2();

  setColor(150, 0, 150);
  colorWipe(strip.Color(150, 0, 150), 100);
  
  if (abs(ax) > 8000 || abs(ay) > 8000 || abs(az) > 18000 || abs(az) < 15000)
  {
    Serial.println("If");
    state = 1;
      setColor(150, 150, 0);
      colorWipe(strip.Color(150, 150, 0), 100);

      nrsongs = random(1,5);
      Serial.print("Nr. Songs: ");
      Serial.println(nrsongs);

      while(nrsongs != nrsongsp)
      {
        for (int thisNote = 0; thisNote < 39; thisNote++) {
          // to calculate the note duration, take one second divided by the note type.
          int noteDuration = 600 / noteDurationsf[thisNote];
          tone(melodyPin, melodyf[thisNote]);
          delay(noteDuration);
    
          // to distinguish the notes, set a minimum time between them.
          //pauseBetweenNotes
          delay(120);
          noTone(8);
          
          //setColor(150, 0, 150);
          //colorWipe(strip.Color(150, 0, 150), 100);
        }
        nrsongsp++;
      }
  }
  if (state == 1)
  {
    setColor(150, 0, 0);
    colorWipe(strip.Color(150, 0, 0), 100);
      
     for (int thisNote = 0; thisNote < 8; thisNote++) {
  
      // to calculate the note duration, take one second divided by the note type.
      int noteDuration = 200 / noteDurations[thisNote];
      tone(melodyPin, melody[thisNote]);
      delay(noteDuration);
  
      // to distinguish the notes, set a minimum time between them.
      //pauseBetweenNotes
      delay(120);
      noTone(8);
    }
    state = 0;
    nrsongsp = 0;
  }


  setColor(0, 0, 0);  // red
  colorWipe(strip.Color(0, 0, 0), 100);
}

void rAc()
{
  oAcX = AcX;
  oAcY = AcY;
  oAcZ = AcZ;

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 8, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.println(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
}

void colorWipe(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
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
