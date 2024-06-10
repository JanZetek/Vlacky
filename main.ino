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
#include "kontrola.h"
#include "debug.h"

ABC U1(20, 24);
ABC U2(9, 22);

Semafor S1(10, 11, U1);
Semafor S2(31, 25, U2);

Vyhybka V1(47, 46, 53, S1, S2, "Vyhybka", 50, 110);

Vyhybka* vyhybky[] = {&V1};

Button_Vyhybka Button1(19, V1);

bool right_way_2[] = {false};

Button_Semafor Button2(21, S1, right_way_2, vyhybky, 1);

bool right_way_3[] = {true};
Button_Semafor Button3(23, S2, right_way_3, vyhybky, 1);

Button_ABC Button4(17, U1, &S1);
Button_ABC Button5(13, U2, &S2);

void setup() {

  Serial.begin(9600);

  V1.begin();
  S1.begin();
  S2.begin();

  U1.begin();
  U2.begin();

  if (Button4.S == &S1)
  {
    Serial.println("Adresy se shodují");
  }
  else
  {
    Serial.println("Adresy se neshodují");
  }
}

void loop() {
  // Serial.println("start of loop");
  Button1.look();
  Button2.look();
  Button3.look();
  Button4.look();
  Button5.look();
  // Serial.println("end of loop");
}