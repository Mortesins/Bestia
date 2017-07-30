#ifndef BESTIA_HPP
#define BESTIA_HPP

using namespace std;

#include "Tavolo.hpp"

class Bestia
{
  private:
   Tavolo tavolo;
   const bool assoDiPrima;
   const bool secondaBriscola;
   const bool briscolaPiuAlta;
   const unsigned numGiocatori;
   const unsigned ante;
  public:
   Bestia(bool assoPrima, bool briscolaSeconda, bool briscolaAlta, unsigned n, unsigned a);
   void run();
   void mettereSoldi();
   void distribuisciCarte();
};
#endif
