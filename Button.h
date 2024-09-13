#include "Print.h"
#include "HardwareSerial.h"
#include "Arduino.h"

#ifndef Button_h
#define Button_h

#include "kontrola.h"
#include "Vyhybka.h"
#include "Semafor.h"
#include "kontrola.h"

typedef void (*OperationFunc)();

class Button 
{
  protected:
    int PIN_BUTTON;
    OperationFunc fce;

  public:
    // Konstruktor
    Button(int pin_button, OperationFunc fce) : PIN_BUTTON(pin_button), fce(fce)
    {
      pinMode(PIN_BUTTON, INPUT);
    }

    void look()
    {
      if (digitalRead(PIN_BUTTON) == HIGH)
      {
        while (digitalRead(PIN_BUTTON) == HIGH) {} // Nedělá nic

        fce();
      }
    }

    void look_semafor(Vyhybka** array_vyhybka, bool* right_way, int len)
    {
      if (digitalRead(PIN_BUTTON) == HIGH)
      {
        while (digitalRead(PIN_BUTTON) == HIGH) {}

        if (ableSemafor(right_way, array_vyhybka, len) == true)
        {
          fce();
        }
      }
    }
};

#endif