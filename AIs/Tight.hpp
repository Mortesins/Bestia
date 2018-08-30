#ifndef TIGHT_HPP
#define TIGHT_HPP

using namespace std;

#include "../AI.hpp"
#include "../random.hpp"

class Tight: public AI
{
   public:
      Tight(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Tight();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
};

#endif
