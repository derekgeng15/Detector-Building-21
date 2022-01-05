#include <Arduino.h>

#define A -2.86e-6
#define B 0.105
#define C -2.29
#define bitres 2048

#define m 0.1027
#define b -1.98674
class LM35 {
  private:
    double prior;//prior estimate
    double post;//post estimate
    double R = 0.739615;//sensor variance
    double Q = 5.5e-4;//system variance
    double P = R;//estimate variance(equal to sensor variance since initial readings are direct measurements)
    double K;//kalman gain
    double residual;//measurment - predition
    double rawVoltage;//difference between raw voltage
    const uint8_t pin;//input analog pin
    const float vref;//reference voltage
  public:
    double voltage;//filtered voltage
    LM35(uint8_t p, float v);
    void burn();//burns first 5 readings
    double getTemp();//returns tempature
    bool inRange(double r);//verifies whether estimated voltage is within a range from raw voltage

};
