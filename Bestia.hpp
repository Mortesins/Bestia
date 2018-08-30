#ifndef BESTIA_HPP
#define BESTIA_HPP

using namespace std;

#include "Tavolo.hpp"

class Bestia
{
  private:
   const bool assoDiPrima;
   const bool secondaBriscola;
   const unsigned numGiocatori;
   const unsigned ante;
   Tavolo tavolo;
   const bool debug;
  public:
   Bestia(bool debug = false, bool assoPrima = true, bool briscolaSeconda = true, unsigned n = 4, unsigned a = 15);
      // d = debug, n = numero giocatori, a = ante
   void run();
};
#endif
