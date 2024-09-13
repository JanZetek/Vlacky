#ifndef ABC_h
#define ABC_h

// #include <Arduino.h>

class ABC
{
  private:
    int RELE_PIN;
    int LED_PIN;
    bool able_off = false;
    bool* p_able_off = &able_off;

    // LED se rozsvítí, pokud je systém ABC zapnut

  public:
    bool stav;
    bool* p_stav = &stav;

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
      *p_stav = true;

      // Zapne systém ABC
      digitalWrite(RELE_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
    }

    void off()
    {
      if (*p_able_off == true)
      {
        *p_stav = false;

        // Vypne systém ABC
        digitalWrite(RELE_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
      }

    }

    void change()
    {
      change_2();
    }

    void change_2()
    {
      *p_stav = !*p_stav;

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

    void disable_switch()
    {
      *p_able_off = false;
    }

    void enable_switch()
    {
      *p_able_off = true;
    }
};

#endif