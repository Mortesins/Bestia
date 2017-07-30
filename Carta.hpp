#ifndef CARTA_HPP
#define CARTA_HPP

#include <iostream>

using namespace std;

class Carta
{
   friend ostream& operator<<(ostream& os, const Carta& c);
  private:
   const char seme;
   const char valore;
  public:
   Carta(char s, char v);
   char getValore() const { return valore; }
   char getSeme() const{ return seme; }
};
#endif
