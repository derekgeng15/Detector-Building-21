#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RGB_LED.h"
#include "LM35.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define rPin 8
#define gPin 9
#define bPin 10
#define tempPin A0
#define VREF 2.23

#define blueThreshStart 0
#define blueThreshEnd 20
#define greenThreshStart 20
#define greenThreshEnd 35
#define redThreshStart 35
#define redThreshEnd 100
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

RGB_LED rgbLED(rPin, gPin, bPin);
LM35 tempSensor(tempPin, VREF);
void setup() {
  // put your setup code here, to run once:
  analogReference(AR_INTERNAL);
  analogReadResolution(11);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display Failed!");
    while (1);
  }
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  tempSensor.burn();
}
void oledReset() {
  oled.clearDisplay();
  oled.setCursor(0, 0);
}
void oledPrintTemp(double temp, double voltage, bool inRange) {
  //celcius
  oled.setTextSize(2);
  oled.print(temp);
  oled.setTextSize(1);
  oled.print(" o");
  oled.setTextSize(2);
  oled.println("C");
  oled.print(voltage);
  oled.setTextSize(2);
  oled.println(" mV");
  oled.println();
  oled.display();
}

double temp;
double roundD(double n, int p) {
  return (double)(round(n * p * 10) / ((float)p * 10.0));
}
void loop() {
  // put your main code here, to run repeatedly:
  oledReset();
  temp = roundD(tempSensor.getTemp(), 1);
  //LED CODE
  if (temp > blueThreshStart && temp <= blueThreshEnd)
    rgbLED.setColor(RGB_LED::COLOR::BLUE);
  if (temp > greenThreshStart && temp <= greenThreshEnd)
    rgbLED.setColor(RGB_LED::COLOR::GREEN);
  if (temp >= redThreshStart && temp <= redThreshEnd)
    rgbLED.setColor(RGB_LED::COLOR::RED);

  oledPrintTemp(temp, round(tempSensor.voltage), tempSensor.inRange(1.5));
}
