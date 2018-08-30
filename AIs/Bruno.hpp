#ifndef BRUNO_HPP
#define BRUNO_HPP

using namespace std;

#include "../AI.hpp"
#include "../random.hpp"

class Bruno: public AI
{
   public:
      Bruno(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Bruno();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
};

#endif
