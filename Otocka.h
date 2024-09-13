#include "Arduino.h"
#include "ABC.h"
#include "Semafor.h"
#include "Vyhybka.h"

#ifndef Otocka_h
#define Otocka_h

class Otocka
{
  private:
    ABC U1;
    ABC U2;
    int pinL, pinK, pinU;
    Vyhybka V1;
    int stav = 3;
    int* p_stav = &stav;

  public:
    Otocka(ABC U1, ABC U2, int pinL, int pinK, int pinU, Vyhybka V1) : U1(U1), U2(U2), pinL(pinL), pinK(pinK), pinU(pinU), V1(V1) {}

    // U1 před otočkou
    // U2 v otočce
    // pinU je zdroj elektriky

    void begin()
    {
      pinMode(pinK, OUTPUT);
      pinMode(pinL, OUTPUT);
      pinMode(pinU, OUTPUT);

      digitalWrite(pinK, LOW);
      digitalWrite(pinL, HIGH);
      digitalWrite(pinU, HIGH);
      }

    void change()
    {
      switch(*p_stav)
      {
        case 1:
          *p_stav = 2;
          stav_2();
          break;
        case 2:
          *p_stav = 3;
          stav_3();
          break;
        case 3:
          *p_stav = 1;
          stav_1();
          
      }
    }

    void stav_1()
    {
      // Vlak najíždí na otočku

      V1.to_false();
      U2.on();
      U1.off();
    }

    void stav_2()
    {
      // Vlak je již v otočce
      // Výměna K a L

      U1.on();
      V1.to_true();

      digitalWrite(pinU, LOW);
      delay(100);

      digitalWrite(pinK, HIGH);
      digitalWrite(pinL, LOW);
      delay(100);

      digitalWrite(pinU, HIGH);

      U1.off();
      U2.off();
      
    }

    void stav_3()
    {
      // Vlak vyjel z otočky

      U2.on();
      U1.on();
    }

};

#endif