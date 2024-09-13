#ifndef kontrola_h
#define kontrola_h

#include "Vyhybka.h"

bool ableSemafor(bool* right_way, Vyhybka** now_way, int len)
{
  // int len = sizeof(right_way) / sizeof(right_way[0]); // velikost pole

  for (int i = 0; i < len; i++)
  {
    if ((*now_way[i]).stav != right_way[i])
    {
      Serial.print((*now_way[i]).stav);
      Serial.print(" != ");
      Serial.print(right_way[i]);
      Serial.print("\n");
      
      Serial.println("false");
      (*now_way[i]).blick();
      return false;
    }
  }
  Serial.println("true");
  return true; // pokud proběhne úspěšně celý cyklus, je možné provést přehození
}

bool ableOffABC(Semafor S)
{
  if (S.stav == 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

#endif