#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <string.h>
#include <Arduino.h>
#include "Semafor.h"
#include "ABC.h"
#include "ServoManager.h"
#include "Display.h"
#include "Vyhybka.h"

using namespace std;

bool ableToGreen(bool* right_way, Vyhybka* array, Semafor S) 
{

  for (int i = 0; i < (sizeof(right_way) / sizeof(right_way[0])); i++) {
    // porovná vždy hodnoty výhybky a správné cesty na stejné pozici v poli
    if (array[i].stav != right_way[i]) {
      return false;
    }
  }

  return true;

};

bool ableOffABC(Semafor S)
{
  if (S.semafor_stav == 1)
  {
    return true;
  }
  return false;
}

ABC U1(25, 50);
ABC U2(23, 51);

Semafor S1(19, 26, 13, 12, U1);
Semafor S2(24, 15, 36, 14, U2);

Vyhybka V1(30, 29, 52, S1, S2);

void setup() {

  Serial.begin(9600);

  V1.begin();
  S1.begin();
  S2.begin();

  U1.begin();
  U2.begin();

  pinMode(46, INPUT);
  pinMode(44, INPUT);
  pinMode(42, INPUT);
  pinMode(40, INPUT);
  pinMode(38, INPUT);
}

void loop() {

  if (digitalRead(46) == HIGH)
  {
    while (digitalRead(46) == HIGH) {} // Nedělá nic

    V1.change();
  }

  else if (digitalRead(42) == HIGH)
  {
    while (digitalRead(42) == HIGH) {} // Nedělá nic

    bool pole_1[] = {false};
    Vyhybka pole_2[] = {V1};

    if (S1.semafor_stav == 0 && ableToGreen(pole_1, pole_2, S1) == true)
    {
      S1.enable();
    } 
    else if (S1.semafor_stav == 0 && ableToGreen(pole_1, pole_2, S1) == false)
    {
      V1.blick();
    }
    else
    {
      S1.disable();
    }
  }

  else if (digitalRead(44) == HIGH)
  {
    while (digitalRead(44) == HIGH) {}

    bool pole_3[] = {true};
    Vyhybka pole_4[] = {V1};

    if (S2.semafor_stav == 0 && ableToGreen(pole_3, pole_4, S2) == true)
    {
      S2.enable();
    }
    else if (S2.semafor_stav == 0 && ableToGreen(pole_3, pole_4, S2) == false)
    {
      V1.blick();
    }
    else
    {
      S2.disable();
    }
  }

  else if (digitalRead(40) == HIGH)
  {
    if (ableOffABC(S1) == true && U1.stav == true)
    {
      U1.off();
    }
    else if (U1.stav == false)
    {
      U1.on();
    }
    else
    {
      Serial.println("Nelze změnit");
    }
  }

  else if (digitalRead(38) == HIGH)
  {
    if (ableOffABC(S2) == true && U2.stav == true)
    {
      U2.off();
    }
    else if (U2.stav == false)
    {
      U2.on();
    }
    else
    {
      Serial.println("Nelze změnit");
    }
  }
}