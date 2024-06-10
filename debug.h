#ifndef debug_h
#define debug_h

#include "Vyhybka.h"

void vypis(Vyhybka V)
{
  Serial.println(V.stav);
}

#endif