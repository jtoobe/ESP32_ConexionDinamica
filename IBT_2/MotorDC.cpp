#include "MotorDC.h"
#include <Arduino.h>

MotorDC::MotorDC(int rpwm, int lpwm, int ren, int len) {
  pinRPWM = rpwm;
  pinLPWM = lpwm;
  pinREN = ren;
  pinLEN = len;

  pinMode(pinRPWM, OUTPUT);
  pinMode(pinLPWM, OUTPUT);
  pinMode(pinREN, OUTPUT);
  pinMode(pinLEN, OUTPUT);

  // Habilitar el driver
  digitalWrite(pinREN, HIGH);
  digitalWrite(pinLEN, HIGH);
}

void MotorDC::adelante(int velocidad) {
  analogWrite(pinRPWM, constrain(velocidad, 0, 255));
  analogWrite(pinLPWM, 0);
}

void MotorDC::atras(int velocidad) {
  analogWrite(pinRPWM, 0);
  analogWrite(pinLPWM, constrain(velocidad, 0, 255));
}

void MotorDC::parar() {
  analogWrite(pinRPWM, 0);
  analogWrite(pinLPWM, 0);
}
