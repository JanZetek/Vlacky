#ifndef Semafor_h
#define Semafor_h

#include <Arduino.h>
#include "ABC.h"

class Semafor
{
  private:
    int LED_GREEN_PIN;
    int LED_RED_PIN;
    int LED_YELLOW_PIN;

    ABC U;

  public:
    int stav; // 0 -> red (blue), 1 -> green (white), 2 -> yellow
    int* p_stav = &stav;
    int type = 0; // 0 -> GR; 1 -> GYR; 2 -> BW
    int* p_type = &type;

    // Konstruktor
    Semafor(int led_green_pin, int led_red_pin, ABC u) : LED_GREEN_PIN(led_green_pin), LED_RED_PIN(led_red_pin), U(u) {}

    // led_green_pin & led_red_pin jsou u typu BW pužívány jako blue a white

    void begin()
    {
      // Inicializace
      pinMode(LED_GREEN_PIN, OUTPUT);
      pinMode(LED_RED_PIN, OUTPUT);

      *p_stav = 0;
    }

    void GYR(int led_yellow_pin)
    {
      LED_YELLOW_PIN = led_yellow_pin;
      *p_type = 1;

      pinMode(LED_YELLOW_PIN, OUTPUT);
    }

    void BW()
    {
      *p_type = 2;

      // led_green_pin & led_red_pin jsou u typu BW pužívány jako blue a white
    }

    void disable() 
    {
      // Zapne červenou diodu, vypne zelenou a zapne relé
      digitalWrite(LED_GREEN_PIN, LOW); 
      digitalWrite(LED_RED_PIN, HIGH);

      if (*p_type == 1)
        digitalWrite(LED_YELLOW_PIN, LOW);

      *p_stav = 0;

      U.on();
      U.disable_switch();
    }

    void enable()
    {
      // Zapne zelou, vypne červenou a relé
      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_RED_PIN, LOW);

      if (*p_type == 1)
        digitalWrite(LED_YELLOW_PIN, LOW);

      *p_stav = 1;

      U.enable_switch();
    }

    void next()
    {
      *p_stav = 2;

      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_YELLOW_PIN, HIGH);
    }

    void change()
    {
      change_2();
    }

    void change_2()
    {

      Serial.println("Semafor byl vyvolán");
      if ((*p_type == 0) || (*p_type == 2))
      {
        switch(*p_stav)
        {
          case 0:
            enable();
            break;
          case 1:
            disable();
            break;
        }
      } else if (*p_type == 1)
      {
        switch (*p_stav)
        {
        case 0:
          enable();
          break;
        case 1:
          next();
          break;
        case 2:
          disable();
          break;
        }
      }
    }

};

#endif