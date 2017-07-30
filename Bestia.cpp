#include "Bestia.hpp"

Bestia::Bestia(bool assoPrima, bool briscolaSeconda, bool briscolaAlta, unsigned n, unsigned a)
   :assoDiPrima(assoPrima),secondaBriscola(briscolaSeconda),briscolaPiuAlta(briscolaAlta),numGiocatori(n),ante(a)
{
}

void Bestia::run()
{
   //selezionare Dealer
   //while
      //Dealer++
      //metterSoldi
      //distribuisciCarte
      //bussare 
      //andare al buio
      //for numGiocatori
         //giro
      //dividere soldi
   return;
}

void Bestia::mettereSoldi()
{
   //tavolo.getDealer()->versaSoldi(ante);
   //for (unsigned i = 0; i < numGiocatori; i++)
   //{
      //if (tavolo.getGiocatore(i)->inBestia())
         //tavolo.getGiocatore(i)->versaSoldi(tavolo.getBestiaValue());
   //}
   return;
}

void Bestia::distribuisciCarte()
{
   for (unsigned i = 0; i < 3; i++)
   {
      for (unsigned j = 0; j < numGiocatori; j++)
      {
         tavolo.daiCarta(i);
      }
   }
   return;
}


int main()
{
   Mazzo mazzo;
   Carta* c = mazzo.getCartaPointer('S','R');
   Giocatore g("Gigi");
   Giocatore g2("Tizio");
   Giocatore g3("Caio");
   Giocatore g4("Sempronio");
   g.riceviCarta(c);
   Tavolo tavolo;
   tavolo.prova();
   tavolo.posizionaGiocatore(&g);
   tavolo.posizionaGiocatore(&g2);
   tavolo.posizionaGiocatore(&g3);
   tavolo.posizionaGiocatore(&g4);
   tavolo.setDealer();
   cout << tavolo;

   return 0;
}
