#include "Arduino.h"
#ifndef Light_h
#define Light_h

class Light
{
  private:
    int LED_A_PIN; //analog
    unsigned long after = 0; // po jakém čase se má obnovit
    unsigned long time = 0; // čas od posledního resetu

  public:

    // konstuktor
    Light(int led_a_pin) : LED_A_PIN(led_a_pin) {}

    void begin()
    {
      pinMode(LED_A_PIN, OUTPUT);
    }

    void update()
    {
      if (time == after)
      {
        after = random(50, 150);
        time = 0;
        time = millis();

        analogWrite(LED_A_PIN, random(300, 900) * 0.255);
      }
    }
};

#endif