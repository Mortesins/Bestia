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
   bool operator>(const Carta& c);
   bool operator<(const Carta& c);
};

bool aMAGGIOREb(char a, char b); //valore della carta senza contare il seme
bool aMINOREb(char a, char b); //valore della carta senza contare il seme
unsigned ilTerzoNumero(unsigned a, unsigned b);

#endif
