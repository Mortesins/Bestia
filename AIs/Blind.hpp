#ifndef BLIND_HPP
#define BLIND_HPP

using namespace std;

#include "../AI.hpp"
#include "../random.hpp"

class Blind: public AI
{
   public:
      Blind(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Blind();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
};

#endif
