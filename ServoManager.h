#ifndef ServoManager_h
#define ServoManager_h

#include <Servo.h>
#include <Arduino.h>

class ServoManager 
{
  private:
    Servo servo;   // Instance objektu Servo
    int servoPin;  // Pin, na kterém je servo připojeno
    int angle_now; // Aktuální pozice
    int right_angle;
    int left_angle;

  public:
    // Konstruktor
    ServoManager(int pin, int left_angle, int right_angle) : servoPin(pin), left_angle(left_angle), right_angle(right_angle) {}

    // Inicializace spojení s servomotorem
    void begin() {
      servo.attach(servoPin);  // Připojení serva k pinu
    }

    // Deinicializace spojení s servomotorem
    ~ServoManager() {
      servo.detach();  // Odpojení serva
    }

    // Ovládání servomotoru na zadaný úhel
    void setAngle(bool orient) {
      // switch (orient)
      // {
      //   case true:
      //     for (int i = right_angle; i <= left_angle; i--)
      //     {
      //       servo.write(i);
      //     }
      //     break;

      //   case false:
      //     for (int i = left_angle; i <= right_angle; i++)
      //     {
      //       servo.write(i);
      //     }
      //     break;
      // }
      servo.write(orient ? left_angle : right_angle);
    }
};

#endif