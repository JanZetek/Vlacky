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

    int P_LED_GREEN_PIN;
    int P_LED_RED_PIN;
    int P_LED_YELLOW_PIN;

    ABC U;

  public:
    int semafor_stav;
    int type = 0; // 0 -> GR; 1 -> GYR; 2 -> BW

    // Konstruktor
    Semafor(int led_green_pin, int led_red_pin, int p_led_green_pin, int p_led_red_pin, ABC u) : LED_GREEN_PIN(led_green_pin), LED_RED_PIN(led_red_pin), P_LED_GREEN_PIN(p_led_green_pin), P_LED_RED_PIN(p_led_red_pin), U(u) {}

    // led_green_pin & led_red_pin jsou u typu BW pužívány jako blue a white

    void begin()
    {
      // Inicializace
      pinMode(LED_GREEN_PIN, OUTPUT);
      pinMode(LED_RED_PIN, OUTPUT);
      pinMode(P_LED_GREEN_PIN, OUTPUT);
      pinMode(P_LED_RED_PIN, OUTPUT);

      semafor_stav = 0;
    }

    void GYR(int led_yellow_pin, int p_led_yellow_pin)
    {
      LED_YELLOW_PIN = led_yellow_pin;
      P_LED_YELLOW_PIN = p_led_yellow_pin;

      type = 1;

      pinMode(LED_YELLOW_PIN, OUTPUT);
    }

    void BW()
    {
      type = 2;

      // led_green_pin & led_red_pin jsou u typu BW pužívány jako blue a white
    }

    void disable() 
    {
      // Zapne červenou diodu, vypne zelenou a zapne relé
      digitalWrite(LED_GREEN_PIN, LOW); 
      digitalWrite(LED_RED_PIN, HIGH);

      digitalWrite(P_LED_GREEN_PIN, LOW);
      digitalWrite(P_LED_RED_PIN, HIGH);

      if (type == 1)
        digitalWrite(LED_YELLOW_PIN, LOW);

      semafor_stav = 0;

      U.on();
    }

    void enable()
    {
      // Zapne zelou, vypne červenou a relé
      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_RED_PIN, LOW);

      digitalWrite(P_LED_GREEN_PIN, HIGH);
      digitalWrite(P_LED_RED_PIN, LOW);

      if (type == 1)
        digitalWrite(LED_YELLOW_PIN, LOW);

      semafor_stav = 1;
    }

    void next()
    {
      semafor_stav = 2;

      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_YELLOW_PIN, HIGH);
    }

};

#endif