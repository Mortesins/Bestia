#ifndef TAVOLO_HPP
#define TAVOLO_HPP

using namespace std;

#include "Giocatore.hpp"
#include "Mazzo.hpp"
#include "Carta.hpp"
#include "random.hpp"
#include <vector>

const unsigned NUMGIOCATORI = 4;

//////
      class ContainerGiocatore
      {
        public:
         ContainerGiocatore() { giocatore = NULL; inBestia = false;}
         Giocatore* giocatore;
         bool inBestia;
      };
//////

class Tavolo
{
   friend ostream& operator<<(ostream& os, Tavolo t);
  private:
   ContainerGiocatore giocatori[NUMGIOCATORI];
   Carta* carteGiocate[NUMGIOCATORI];
   vector <Carta*> pozzo;
   vector <Carta*> mucchio; 
   const Mazzo mazzo;
   Carta* briscola;
   unsigned pot;
   int dealer;
  public:
   Tavolo();
   void posizionaGiocatore(Giocatore* g, int posto = -1); // OK // posto = -1 significa RANDOM
   void daiCarta(unsigned posto);
   void setDealer(); // OK
   void mettiSoldiDealer();
   void distribuisciCarte(unsigned giocatoreIndex);
   void setBriscola();
   void chiGioca();
   void prova();
   void chiVaAlBuio();
   void daiSoldiGiocatore(unsigned giocatoreIndex);
   void giocaCarta(unsigned giocatoreIndex);
   void chiHaVinto();
   void dividereSoldiEBestia();
   void mettiBestiaSoldi();
   void stampaMucchio();
   unsigned getDealer(); // OK
};
#endif
