#ifndef ABC_h
#define ABC_h

#include <Arduino.h>

class ABC
{
  private:
    int RELE_PIN;
    int LED_PIN;

    // LED se rozsvítí, pokud je systém ABC zapnut

  public:
    bool stav;

    // Konstruktor
    ABC(int rele_pin, int led_pin) : RELE_PIN(rele_pin), LED_PIN(led_pin) {}

    void begin()
    {
      // Inicializuje pin
      pinMode(RELE_PIN, OUTPUT);
      pinMode(LED_PIN, OUTPUT);
    }

    void on()
    {
      stav = true;

      // Zapne systém ABC
      digitalWrite(RELE_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
    }

    void off()
    {
      stav = false;

      // Vypne systém ABC
      digitalWrite(RELE_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    }

    void change()
    {
      stav = !stav;

      switch(stav)
      {
        case false:
          off();
          break;
        case true:
          on();
          break;
      }
    }
};

#endif