#ifndef LOOSE_HPP
#define LOOSE_HPP

using namespace std;

#include "../AI.hpp"
#include "../random.hpp"

class Loose: public AI
{
   public:
      Loose(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Loose();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
};

#endif
