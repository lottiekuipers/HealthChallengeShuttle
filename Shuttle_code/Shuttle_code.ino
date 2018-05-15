
#include <Adafruit_NeoPixel.h>
#include<Wire.h>
#define PIN 6

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp, oAcX, oAcY, oAcZ;

int x = 150; //Tijdelijk!
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

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
  
  Serial.begin(9600);
}

void loop() 
{
  rAc();
  checkA();
  
  while((AcX/2 > oAcX) || (AcY/2 > oAcY) || (AcZ/2 > oAcZ))
  {
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
    rAc();
    Serial.println(AcX);
    Serial.println(oAcX);
    Serial.println(AcY);
    Serial.println(oAcY);
    Serial.println(AcZ);
    Serial.println(oAcZ);
    setColor(0, 0, 0);  // red
   colorWipe(strip.Color(0, 0, 0), 100);
   delay(5000);
   }
   
   setColor(0, 0, 0);  // red
   colorWipe(strip.Color(0, 0, 0), 100);
   delay(5000);
}

void rAc()
{
  oAcX = AcX;
  oAcY = AcY;
  oAcZ = AcZ;
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,8,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.println(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet  
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

void checkA()
{
  if((AcX/2 > oAcX) || (AcY/2 > oAcY) || (AcY/2 > oAcY))
  {
    //LEDS 
  }
}

