#include "MotorDC.h"
#include <Arduino.h>

MotorDC::MotorDC(int in1, int in2, int ena) {
  pinIN1 = in1;
  pinIN2 = in2;
  pinENA = ena;

  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENA, OUTPUT);
}

void MotorDC::adelante(int velocidad) {
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  analogWrite(pinENA, constrain(velocidad, 0, 255));
}

void MotorDC::atras(int velocidad) {
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  analogWrite(pinENA, constrain(velocidad, 0, 255));
}

void MotorDC::parar() {
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  analogWrite(pinENA, 0);
}
