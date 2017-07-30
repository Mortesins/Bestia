#ifndef MAZZO_HPP
#define MAZZO_HPP

using namespace std;

#include "Carta.hpp"

#include <vector>

class Mazzo
{
   friend ostream& operator<<(ostream& os, const Mazzo& m);
  private:
   Carta* mazzo[40];//vector
  public:
   Mazzo();
   Carta* getCartaPointer(char s, char v) const;
   Carta* getCartaPointer(unsigned i) const;
};
#endif
