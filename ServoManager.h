#ifndef ServoManager_h
#define ServoManager_h

#include <Servo.h>
#include <Arduino.h>

class ServoManager 
{
  private:
    Servo servo;   // Instance objektu Servo
    int servoPin;  // Pin, na kterém je servo připojeno

  public:
    // Konstruktor
    ServoManager(int pin)
      : servoPin(pin) {}

    // Inicializace spojení s servomotorem
    void begin() {
      servo.attach(servoPin);  // Připojení serva k pinu
    }

    // Deinicializace spojení s servomotorem
    ~ServoManager() {
      servo.detach();  // Odpojení serva
    }

    // Ovládání servomotoru na zadaný úhel
    void setAngle(int angle) {
      servo.write(angle);
    }
};

#endif