#include "Arduino.h"
#ifndef Light_h
#define Light_h

class Light
{
  private:
    int LED_A_PIN; //analog
    unsigned long after; // po jakém čase se má obnovit
    unsigned long time = millis(); // pointer na čas z main

  public:

    // konstuktor
    Light(int led_a_pin) : LED_A_PIN(led_a_pin) {}

    void begin()
    {
      pinMode(LED_A_PIN, OUTPUT);
    }

    void update()
    {
      if (time >= after)
      {
        after = time + random(50, 150);

        Serial.println(millis());

        analogWrite(LED_A_PIN, random(64, 255));
      }

      time = millis();
    }
};

#endif