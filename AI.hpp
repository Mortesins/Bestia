#ifndef AI_HPP
#define AI_HPP

using namespace std;

#include "Giocatore.hpp"
#include "random.hpp"

class AI: public Giocatore
{
  protected:
   const bool assoDiPrima;
   const bool secondaBriscola;
   // PRIVATE
   int cartaPiuAltaNonBriscola(char briscolaSeme); //la più alta non briscola, -1 se tutto briscola
   int cartaPiuAlta(char s); // -1 se non c'è
   unsigned cartaPiuAlta();
   int cartaPiuBassa(char s);
   unsigned cartaPiuBassa();
   unsigned numCarteSeme(char s); //numero carte di un seme
   unsigned cartaDaButtarVia(); //la più bassa del seme in cui ho più carte
   
   int cercaCarta(char v, char s);

  public:
   AI(string name, string type="AI", bool assoPrima=true, bool briscolaSeconda=true);
   ~AI();
   
   Carta* giocaCarta(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate, bool ultimo, unsigned posto, bool debug); 
   
   char palo(unsigned diMano, const vector <Carta*> carteGiocate); //non controlla che sia stata giocata la carta del giocatore di mano
   char valoreVincente(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate);
   bool briscolaGiocata(const Carta* briscola, const vector <Carta*> carteGiocate);
};

#endif
