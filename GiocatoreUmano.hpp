#ifndef GIOCATOREUMANO_HPP
#define GIOCATOREUMANO_HPP

using namespace std;

#include "Giocatore.hpp"
#include "random.hpp"

class GiocatoreUmano: public Giocatore
{
  private:
   const bool assoDiPrima;
   const bool secondaBriscola;
   unsigned scegliCartaDaGiocare(const Carta* briscola);
   unsigned loopPerValoreValido(unsigned a);
  public:
   GiocatoreUmano(string name, bool assoPrima=true, bool briscolaSeconda=true);
   ~GiocatoreUmano();

   bool bussareOno(const Carta* briscola);
   bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
   Carta* giocaCarta(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate, bool ultimo, unsigned posto, bool debug=false); //FATTO MA NON SE SE FUNZIONA
      // debug non serve
   unsigned cartaPiuAlta();
};

#endif
