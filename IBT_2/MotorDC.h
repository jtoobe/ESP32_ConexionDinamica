#ifndef MOTORDC_H
#define MOTORDC_H

class MotorDC {
  private:
    int pinRPWM;
    int pinLPWM;
    int pinREN;
    int pinLEN;

  public:
    MotorDC(int rpwm, int lpwm, int ren, int len);
    void adelante(int velocidad);
    void atras(int velocidad);
    void parar();
};

#endif
