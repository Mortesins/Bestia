#include "Tavolo.hpp"

Tavolo::Tavolo()
{
   briscola = NULL;
   dealer = -1;
   pot = 0;
   for (unsigned i; i < NUMGIOCATORI; i++)
   {
      carteGiocate[i] = NULL;
   }
   // SET UP mucchio
   // vector 0 a 39
   vector <int> numeri;
   for (unsigned i = 0; i < 40; i++)
      numeri.push_back(i);
   unsigned randInt;
   for (unsigned i = 0; i < 40; i++)
   {     //ogni giro prendo un numero a caso, assegno quella carta al mucchio,
         //poi elimino quel numero
         //quindi il random ogni volta ha come limite massimo un numero in meno
      randInt = randomInterval(0,39-i,i);
      mucchio.push_back(mazzo.getCartaPointer(numeri[randInt])); //non inserisco randInt, ma il numero del vettore numeri alla posizione randInt ( cambia perchè ogni giro elimino il numero usato)
      numeri.erase(numeri.begin() + randInt);
   }
}

void Tavolo::stampaMucchio()
{
   for (unsigned i = 0; i < 40; i++)
   {
      if (mucchio[i] != NULL)
         cout << *(mucchio[i]) << endl;
   }
   return;
}


void Tavolo::posizionaGiocatore(Giocatore* g, int posto)
{
   // se posto == -1 random
   if ( posto >= 0 && posto < NUMGIOCATORI )
   {     //posto valido  (posto != -1)
      if (giocatori[posto].giocatore == NULL)
      {
         // posto libero
         giocatori[posto].giocatore = g;
         return;
      }
   }
   else
   {     //random
      unsigned i = randomInterval(0, NUMGIOCATORI - 1);
      unsigned j = 0; //for seeding purposes
      while (true)
      {
         if (giocatori[i].giocatore == NULL)
         {
            giocatori[i].giocatore = g;
            return;
         }
         j++; //for seeding purposes
         i = randomInterval(0, NUMGIOCATORI - 1, j);      
      }
   }
}

unsigned Tavolo::getDealer()
{
   return dealer;
}

void Tavolo::daiCarta(unsigned posto)
{
   int i = randomInterval(0,mucchio.size() - 1);
   Carta* cp = mucchio[i];
   mucchio.erase(mucchio.begin() + i);
   giocatori[posto].giocatore->riceviCarta(cp);
   return;
}

void Tavolo::setDealer()
{
   if (dealer == -1)
      dealer = randomInterval(0,NUMGIOCATORI - 1);
   else
   {
      if (dealer == NUMGIOCATORI - 1)
         dealer = 0;
      else
         dealer++;
   }
}

void Tavolo::mettiSoldiDealer()
{

}

void Tavolo::distribuisciCarte(unsigned giocatoreIndex)
{

}

void Tavolo::setBriscola()
{

}

void Tavolo::chiGioca()
{
   
}

void Tavolo::prova()
{
   cout << "WTF" << endl;
   return;
}

void Tavolo::chiVaAlBuio()
{

}

void Tavolo::daiSoldiGiocatore(unsigned giocatoreIndex)
{

}

void Tavolo::giocaCarta(unsigned giocatoreIndex)
{

}

void Tavolo::chiHaVinto()
{

}

void Tavolo::dividereSoldiEBestia()
{

}

void Tavolo::mettiBestiaSoldi()
{

}

ostream& operator<<(ostream& os, Tavolo t)
{
   // for testing purposes printing player, but it should only print the names
   os << "TAVOLO" << endl;
   os << "Briscola: ";
   if (t.briscola != NULL)
      os << *(t.briscola);
   os << endl;
   os << "Pot: " << t.pot << endl;
   os << "Giocatori: " << endl;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      os << i+1;
      if (t.dealer == i)
         os << "*";
      os << ") " << endl;
      if (t.giocatori[i].giocatore != NULL)
         os << *(t.giocatori[i].giocatore) << endl;
      else
         os << "VUOTO" << endl;
   }
   return os;
}
