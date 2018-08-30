#ifndef ROBIN_HPP
#define ROBIN_HPP

using namespace std;

#include "../AI.hpp"
#include "../random.hpp"

class Robin: public AI
{
   public:
      Robin(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Robin();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
};

#endif
