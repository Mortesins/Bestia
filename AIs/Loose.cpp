#include "Loose.hpp"

Loose::Loose(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,"Loose",assoPrima,briscolaSeconda)
{
}

Loose::~Loose()
{
   // non elimino le carte perchè devono rimanere nel mazzo
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

bool Loose::vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) 
{
   /*** ultimo posto && nessuno è andato ***/
   if (ultimo && nessunoAndato)
   {
      cout << nome << " va al buio" << endl;
      return true;
   }
   /****************************************/
   /*** POT 9/10 times ***/
   if (soldi >= pot)
   {
      unsigned randomNumber = randomInterval(0,9,pot/posto); // pot/posto è un extraseed per rendere ancora più casuale
      if (randomNumber < 9) // 0,1,2,3,4
      {
         cout << nome << " va al buio" << endl;
         return true;
      }
   }
   /**********************/
   cout << nome << " non va al buio" << endl;
   return false;
}

bool Loose::bussareOno(const Carta* briscola) 
{
   char semeBriscola = briscola->getSeme(); 
   /*** se una briscola ***/
   for (unsigned i=0; i<3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() == semeBriscola)
            return true;
      }
   }
   /***********************/
   
   /*** 3 figure 2 semi ***/
      // CONTROLLO PRIMA 3 FIGURE, POI CONTROLLO CHE NON SIANO TUTTI I SEMI UGUALI
   bool treFigure = true;
   
   unsigned i=0; 
   while (treFigure && i<3) //così appena trovo una non figura termina
   {
      if (carte[i] != NULL)
      {
         if ( aMINOREb(carte[i]->getValore(),'F') )
         {  // 2,4,5,6,7
            treFigure = false;
         }
      }
      i++;
   }
   bool dueSemi = !( 
                     (carte[0]->getSeme() == carte[1]->getSeme()) &&
                     (carte[0]->getSeme() == carte[2]->getSeme()) &&
                     (carte[1]->getSeme() == carte[2]->getSeme()) 
                   ); //NON tutti uguali
   if (treFigure && dueSemi)
      return true;
   /***********************/
   
   /*** 2 A/3 ***/
   unsigned numAssiOtre = 0;
   for (unsigned i=0; i<3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getValore() == 'A' || carte[i]->getValore() == '3')
            numAssiOtre++;
      }
   }
   if (numAssiOtre >= 2)
      return true;
   /***********/
   
   return false;
}
