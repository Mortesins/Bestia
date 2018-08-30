#ifndef BESTIA_HPP
#define BESTIA_HPP

using namespace std;

#include "Tavolo.hpp"
#include "AI.hpp"
#include "GiocatoreUmano.hpp"
#include "AIs/Bruno.hpp"
#include "AIs/Blind.hpp"
#include "AIs/Loose.hpp"
#include "AIs/Robin.hpp"
#include "AIs/Tight.hpp"

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
