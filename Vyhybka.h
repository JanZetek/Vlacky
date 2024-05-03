#ifndef Vyhybka_h
#define Vyhybka_h

#include <Arduino.h>

class Vyhybka 
{
  private:
    int LED_1_PIN;
    int LED_2_PIN;
    int SERVO_PIN;
    int RELE_PIN;
    bool srdcova = false;
    ServoManager Servo;
    Semafor S1;
    Semafor S2;
  
  public:
    bool stav; // false -> vlevo; true -> vpravo

    // konstruktor
    Vyhybka(int led_1_pin, int led_2_pin, int servo_pin, Semafor s1, Semafor s2) : Servo(servo_pin), LED_1_PIN(led_1_pin), LED_2_PIN(led_2_pin), SERVO_PIN(servo_pin), S1(s1), S2(s2) {}


    void begin() 
    {
      // Nastavení LED jakou OUTPUT
      pinMode(LED_1_PIN, OUTPUT);
      pinMode(LED_2_PIN, OUTPUT);

      // Inicialzizace serva
      Servo.begin();

      // Semafory nastaví na červenou
      S1.disable();
      S2.disable();

      change();

    }

    void set_srdcova(int rele_pin) 
    {
      srdcova = true;

      RELE_PIN = rele_pin;

      pinMode(RELE_PIN, OUTPUT);
    }

    void change()
    {
      if (stav == false) {
        stav = true; // přepna orientaci výhybky vpravo
      } else {
        stav = false;
      }

      Servo.begin(); // Vůbvec nevím, proč to tady je, ale bez toho to nefunguje
      Servo.setAngle(stav ? 0 : 180); // přepne servo na základě orientace do požadovaného úhlu

      digitalWrite(LED_1_PIN, stav ? HIGH : LOW);
      digitalWrite(LED_2_PIN, stav ? LOW : HIGH);

      // Pokud je kolej srdcová, přepne se relé
      if (srdcova == true)
        digitalWrite(RELE_PIN, stav ? LOW : HIGH);

      // Nastaví na obou dvou semaforech červenou
      S1.disable(); 
      S2.disable();
    }

    void blick()
    {
      Serial.println("Zablikam");

      switch (stav)
      {
        case false:
          digitalWrite(LED_1_PIN, HIGH);
          delay(250);
          digitalWrite(LED_1_PIN, LOW);
          break;
        case true:
          digitalWrite(LED_2_PIN, HIGH);
          delay(250);
          digitalWrite(LED_2_PIN, LOW);
          break;
      }
    }

};

#endif