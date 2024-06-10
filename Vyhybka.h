#ifndef Vyhybka_h
#define Vyhybka_h

#include <Arduino.h>
#include "ServoManager.h"

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
    int left_angle;
    int right_angle;
  
  public:
    bool stav = false; // false -> vlevo; true -> vpravo
    bool* p_stav = &stav;
    char* LABEL;

    // konstruktor
    Vyhybka(int led_1_pin, int led_2_pin, int servo_pin, Semafor s1, Semafor s2, char* label, int left_angle, int right_angle) : Servo(servo_pin, left_angle, right_angle), LED_1_PIN(led_1_pin), LED_2_PIN(led_2_pin), SERVO_PIN(servo_pin), S1(s1), S2(s2), LABEL(label), left_angle(left_angle), right_angle(right_angle) {}

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

    bool print_stav()
    {
      Serial.println(stav);
      return stav;
    }

    void change()
    {
      switch (*p_stav) 
      {
        case false:
          *p_stav = true;
          break;
        
        case true:
          *p_stav = false;
          break;
      }

      Servo.begin(); // Vůbvec nevím, proč to tady je, ale bez toho to nefunguje
      Servo.setAngle(*p_stav ? true : false); // přepne servo na základě orientace do požadovaného úhlu

      digitalWrite(LED_1_PIN, *p_stav ? HIGH : LOW);
      digitalWrite(LED_2_PIN, *p_stav ? LOW : HIGH);

      // Pokud je kolej srdcová, přepne se relé
      if (srdcova == true)
        digitalWrite(RELE_PIN, *p_stav ? LOW : HIGH);

      // Nastaví na obou dvou semaforech červenou
      S1.disable(); 
      S2.disable();

      print_stav();
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