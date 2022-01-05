#include "RGB_LED.h"

RGB_LED::RGB_LED(uint8_t r, uint8_t g, uint8_t b):rPin(r), gPin(g), bPin(b){//inits pins and sets output pins
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}
void RGB_LED::setLow(){//sets all pins low
  digitalWrite(rPin, LOW);
  digitalWrite(gPin, LOW);
  digitalWrite(bPin, LOW);
}
void RGB_LED::setColor(COLOR color){//sets color based on user input
   setLow();
   switch(color){
      case RED:
        digitalWrite(rPin, HIGH);
        break;
      case GREEN:
        digitalWrite(gPin, HIGH);
        break;
      case BLUE:
        digitalWrite(bPin, HIGH);
        break;
   }
  
}
