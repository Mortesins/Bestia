#ifndef TAVOLO_HPP
#define TAVOLO_HPP

using namespace std;

#include "GiocatoriDerivati.hpp"
#include "Mazzo.hpp"
#include "Carta.hpp"
#include "random.hpp"
#include <vector>

//////
      class ContainerGiocatore
      {
        public:
         ContainerGiocatore() { giocatore=NULL; inBestia=false; inGioco=false; numPrese=0; }
         ~ContainerGiocatore() { delete giocatore; }
         Giocatore* giocatore;
         bool inBestia;
         bool inGioco;
         unsigned numPrese;
      };
//////

class Tavolo
{
   friend ostream& operator<<(ostream& os,const Tavolo& t);
  private:
   vector <ContainerGiocatore> giocatori;
   vector <Carta*> carteGiocate;
   vector <Carta*> mucchio; 
   vector <Carta*> pozzo; 
   const Mazzo mazzo;
   Carta* briscola;
   unsigned pot;
   unsigned bestiaMoney;
   int dealer;
   
   unsigned next(unsigned i);
   void daiCarta(unsigned posto, int resetSeed); 
  public:
   const unsigned NUMGIOCATORI; //PERCHE' PUBLIC????
   const unsigned DEALERMONEY; //PERCHE' PUBLIC????
   Tavolo(unsigned n, unsigned dm);
   ~Tavolo();
   
   void printPlayersType();
   void posizionaGiocatore(Giocatore* g, int posto = -1);  // posto = -1 significa RANDOM
   void setDealer(); 
   bool mettiSoldiDealer();  //andato a buon fine? BOOL
   bool mettiBestiaSoldi(); // andato a buon fine? BOOL
   void daiSoldiGiocatore(unsigned giocatoreIndex, unsigned soldi); 
   void distribuisciCarte(unsigned giocatoreIndex); 
   void setBriscola(); 
   
   int chiGioca(bool debug, int chiComincia = -1); //di default parte quello dopo il dealer // return -1 se nessuno gioca
   void chiVaAlBuio(int primo = -1); //di default parte quello dopo il dealer
   void giocaCarta(unsigned giocatoreIndex, unsigned diMano, bool debug); 
   
   unsigned chiudiGiro(int chiComincia = -1 );  //di default parte il dealer // ritorna chi ha vinto
   void vincitoreIncontrastato();
   void dividereSoldiEBestia(); 
   void resetBriscola();
   void resetPlayersStatus();
   void giro(bool debug, int chiComincia = -1);  //di default parte il dealer
   void resetMucchio();

   void setNumPrese(unsigned i, unsigned prese);// { giocatori[i].numPrese = prese; return; } //PRIVATE
   void setInGioco(unsigned i); //{ giocatori[i].inGioco = true; return; } // PRIVATE
   
   /***** GET & PRINT *****/
   void printPlayerStatus(unsigned giocatoreIndex); 
   void printPlayerName(unsigned giocatoreIndex); 
   void printPlayerInPlay(unsigned giocatoreIndex);
   void printPlayersInPlay();
   void printPresePlayersInPlay(unsigned index);
   void printPlayersInPlayPreseBestia();
   void stampaMucchio(); 
   void stampaPozzo(); 
   void stampaCarteGiocate();
   void stampaCarteGiocate(int index); 
   void stampaBriscola(); 
   unsigned getDealer(); 
   unsigned numGiocatoriInGioco();
   /***** \\GET & PRINT *****/
};
#endif
