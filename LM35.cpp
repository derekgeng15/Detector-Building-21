#include "LM35.h"

LM35::LM35(uint8_t p, float v): pin(p), vref(v){};
void LM35::burn(){
   for(int i = 0; i < 5; i++){
    prior = analogRead(pin) * vref * 1000 / bitres;
    delay(200);
  }
  post = prior;
  delay(500);
}

double LM35::getTemp(){
   //predict step
  prior = post + Q;//compute prior
  P = P + Q;//adjust belief  
  //update step
  rawVoltage = analogRead(pin) * vref * 1000 / bitres;//get sensor reading
  
  residual = rawVoltage - prior;//compute residual
  K = P / (P + R);//compute Kalman Gain
  post = prior + K * residual;//compute post
  P = (1 - K) * P;//adjust belief
  Serial.print(rawVoltage);
  voltage = post;
  Serial.print(" ");
  Serial.println(voltage);
  return A * voltage * voltage + B * voltage + C;//apply quadratic regression line
}
bool LM35::inRange(double r){
  return (abs(rawVoltage - voltage) <= r)?true:false;
}
