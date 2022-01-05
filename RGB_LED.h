#include <Arduino.h>
class RGB_LED{

  private:
    const uint8_t rPin;//red pin
    const uint8_t gPin;//green pin
    const uint8_t bPin;//blue pin
    void setLow();//sets all colors low
  public:
    enum COLOR{//enum for colors
      RED,
      GREEN,
      BLUE
    };
    RGB_LED(uint8_t r, uint8_t g, uint8_t b);//constructor
    void setColor(COLOR color);//sets color
};
