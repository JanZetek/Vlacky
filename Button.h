#include "Print.h"
#include "HardwareSerial.h"
#include "Arduino.h"

#ifndef Button_h
#define Button_h

#include "kontrola.h"
#include "Vyhybka.h"
#include "Semafor.h"

class Button 
{
  protected:
    int PIN_BUTTON;

  public:
    // Konstruktor
    Button(int pin_button) : PIN_BUTTON(pin_button)
    {
      pinMode(PIN_BUTTON, INPUT);
    }
};

class Button_Vyhybka : Button
{
  private:
    Vyhybka V;
  
  public:
    // Konstruktor
    Button_Vyhybka(int pin, Vyhybka v) : Button(pin), V(v) {}

    void look()
    {
      // Serial.println("I'm working from Switch");
      if (digitalRead(PIN_BUTTON) == HIGH)
      {
        Serial.println("Výhybka");
        while (digitalRead(PIN_BUTTON) == HIGH) {} // Nedělá nic, dokud nepustím tlačítko

        change();
      }
    }

    void change()
    {
      V.change();
    }
};

class Button_Semafor : Button
{
  private:
    Semafor S;
    bool* right_way;
    int len;
  
  public:
    Vyhybka** vyhybky_array;
    // Konstruktor
    Button_Semafor(int pin, Semafor s, bool* right_way, Vyhybka* vyhybky_array[], int len) : Button(pin), S(s), right_way(right_way), vyhybky_array(vyhybky_array), len(len) {}

    void look()
    {

      if (digitalRead(PIN_BUTTON) == HIGH)
      {
        Serial.println("Semafor");
        Serial.println((*vyhybky_array[0]).stav);

        while(digitalRead(PIN_BUTTON) == HIGH) {} // Nedělá nic, dokud je tlačítko zmáčknuto

        change();
      }
      else {}
    }

    void change()
    {
      for (int i = 0; i < len; i++)
      {
        Serial.println(right_way[i]);

        if ((*vyhybky_array[i]).stav == right_way[i])
        {
          Serial.println("I can");
          S.change();
        }
        else 
        {
          Serial.println("I can't");
          Serial.print((*vyhybky_array[i]).stav);
          Serial.print(" != ");
          Serial.print(right_way[i]);
          Serial.print("\n");
          (*vyhybky_array[i]).blick();
        }
      }
    }
};

class Button_ABC : Button
{

  protected:
    ABC U;
  
  public:
    Semafor* S;
    Button_ABC(int pin, ABC u, Semafor* s) : Button(pin), U(u), S(s) {}

    void look()
    {
      if (digitalRead(PIN_BUTTON) == HIGH)
      {
        while (digitalRead(PIN_BUTTON) == HIGH) {} // Nedělá nic

        Serial.println("ABC");
        Serial.println(S->stav);

        change();
      }
    }

    void change()
    {
      Serial.println(S->stav);
      switch (S->stav)
      {
        case 0:
          Serial.println("false");
          break;

        case 1:
          Serial.println("true");
          U.change();
          break;
      }
    }

};

#endif