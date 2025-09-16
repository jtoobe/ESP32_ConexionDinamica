#ifndef MOTORDC_H
#define MOTORDC_H

class MotorDC {
  private:
    int pinIN1;
    int pinIN2;
    int pinENA;

  public:
    MotorDC(int in1, int in2, int ena);
    void adelante(int velocidad);
    void atras(int velocidad);
    void parar();
};

#endif
