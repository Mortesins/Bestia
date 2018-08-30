#include "Blind.hpp"

Blind::Blind(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,"Blind",assoPrima,briscolaSeconda)
{
}

Blind::~Blind()
{
   // non elimino le carte perchè devono rimanere nel mazzo
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

bool Blind::vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) 
{
   /*** 2xPOT ***/
   if (soldi >= pot*2)
   {
      cout << nome << " va al buio" << endl;
      return true;
   }
   cout << nome << " non va al buio" << endl;
   return false;
}

bool Blind::bussareOno(const Carta* briscola) 
{
   char semeBriscola = briscola->getSeme(); 
   /*** se una briscola maggiore o uguale 5 ***/
   for (unsigned i=0; i<3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() == semeBriscola && aMAGGIOREb(carte[i]->getValore(),'4'))
            return true;
      }
   }
   /*************************************************/
   /*** 3 figure 3 semi ***/
   char semeTmp = '0'; //così il primo seme che controllo è diverso da '0' e quindi non ho trovato due semi uguali
   bool treFigureTreSemi = true;
   unsigned i=0; 
   while (treFigureTreSemi && i<3) //così appena trovo una non figura o due semi uguali termina
   {
      if (carte[i] != NULL)
      {
         if ( aMINOREb(carte[i]->getValore(),'F') )
         {  // 2,4,5,6,7
            treFigureTreSemi = false;
         }
         else
         { // è una figura o più ma devo controllare che abbia seme diverso
            char semeCarta = carte[i]->getSeme();
            if (semeCarta != semeTmp)
            {  // seme diverso, quindi salvo questo seme per controllare il prossimo
               semeTmp = semeCarta;
            }
            else
            {  //due semi uguali quindi...
               treFigureTreSemi = false;
            }
         }
      }
      i++;
   }
   if (treFigureTreSemi)
      return true;
   /***********************/
   
   /*** A/3 + 2 figure 2 semi ***/
   bool assoOtre = false;
   for (unsigned i=0; i<3; i++)
   {
      if (carte[i] != NULL)
      {
         char valore = carte[i]->getValore();
         if (valore == 'A' || valore == '3')
         {
            assoOtre = true;
            break;
         }
      }
   }
   if (assoOtre)
   {
      // tutte maggiore di 7
      // due semi
      bool tutteFigure = true;
      bool dueSemi = false;
      char s;
      if (carte[0] != NULL)
      {
         if ( aMAGGIOREb(carte[0]->getValore(),'7') )
         {
            s = carte[0]->getSeme();
         }
         else
         {
            tutteFigure = false;
         }
      }
      unsigned i=1;
      while (i<3 && tutteFigure)
      {
         if (carte[i] != NULL)
         {
            if ( aMAGGIOREb(carte[i]->getValore(),'7') )
            {
               if (s != carte[i]->getSeme())
                  dueSemi = true;
            }
            else
            { 
               tutteFigure = false;
            }
         }
         i++;
      }
      if (tutteFigure && dueSemi)
         return true;
   }
   /*****************************/
   
   /*** 2 A ***/
   unsigned numAssi = 0;
   for (unsigned i=0; i<3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getValore() == 'A')
            numAssi++;
      }
   }
   if (numAssi >= 2)
      return true;
   /***********/
   
   return false;
}
