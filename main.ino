#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "Arduino.h"
#include "Semafor.h"
#include "ABC.h"
#include "ServoManager.h"
#include "Display.h"
#include "Vyhybka.h"
#include "Button.h"
#include "Light.h"
#include "Otocka.h"
#include "kontrola.h"

ABC U1(20, 22);
ABC U2(9, 24);

Semafor S1(10, 11, U1);
Semafor S2(31, 25, U2);

Vyhybka V1(46, 47, 53, S1, S2, "Výhybka 1", 50, 110);

Button B_U1(13, []() {U1.change();});
Button B_U2(17, []() {U2.change();});

Button B_S1(23, []() {S1.change();});
Button B_S2(21, []() {S2.change();});

Button B_V1(19, []() {V1.change();});

Vyhybka* array_vyhybka[] = {&V1};

bool right_way_1_1[] = {false};
bool right_way_1_2[] = {true};

void setup() {

  Serial.begin(9600);

  V1.begin();

  S1.begin();
  S2.begin();

  U1.begin();
  U2.begin();
}

void loop() {
  B_U1.look();
  B_U2.look();

  B_S1.look_semafor(array_vyhybka, right_way_1_1, 1);
  B_S2.look_semafor(array_vyhybka, right_way_1_2, 1);

  B_V1.look();
}
