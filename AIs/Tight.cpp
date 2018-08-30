#include "Tight.hpp"

Tight::Tight(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,"Tight",assoPrima,briscolaSeconda)
{
}

Tight::~Tight()
{
   // non elimino le carte perchè devono rimanere nel mazzo
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

bool Tight::vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) 
{
   /*** ultimo posto && nessuno è andato && 2xPOT ***/
   if (ultimo && nessunoAndato && (soldi >= pot*2))
   {
      cout << nome << " va al buio" << endl;
      return true;
   }
   if (soldi >= pot*2)
   {
      unsigned randomNumber = randomInterval(0,9,pot/posto); // pot/posto è un extraseed per rendere ancora più casuale
      if (randomNumber < 5) // 0,1,2,3,4
      {
         cout << nome << " va al buio" << endl;
         return true;
      }
   }
   cout << nome << " non va al buio" << endl;
   return false;
}

bool Tight::bussareOno(const Carta* briscola) 
{
   char semeBriscola = briscola->getSeme(); 
   /*** se una briscola maggiore o uguale Cavallo ***/
   for (unsigned i=0; i<3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() == semeBriscola && aMAGGIOREb(carte[i]->getValore(),'F'))
            return true;
      }
   }
   /*************************************************/
   /*** se tutte le carte A o 3 ***/
      // se la carta più bassa è un 3 o A
   char valore = (carte[cartaPiuBassa()])->getValore();
   if (valore == '3' || valore == 'A')
      return true;
   /*******************************/
   /*** se 11 punti briscola ***/
   unsigned puntiBriscola = 0;
   for (unsigned i=0; i<3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() == semeBriscola)
         {
            char valore = carte[i]->getValore();
            switch (valore)
            {
               case 'A': 
                  puntiBriscola += 12;
                  break;
               case '3':
                  puntiBriscola += 11;
                  break;
               case 'R':
                  puntiBriscola += 10;
                  break;
               case 'C':
                  puntiBriscola += 9;
                  break;
               case 'F':
                  puntiBriscola += 8;
                  break;
               default: // 7,6,5,4,2
                  puntiBriscola += (valore - '0');
                  break;
            }
         }
      }
   }
   if (puntiBriscola >= 11)
      return true;
   /****************************/
   /*** se due Assi o 3 e una briscola ***/
      // se avessi asso o 3 di briscola il primo controllo mi restituisce true
      // QUINDI al massimo ho il fante di briscola
      // quindi la carta più bassa che ho deve essere di briscola
      // in più devo controllare che le altre due carte siano 3 o A
   unsigned cartaBassa = cartaPiuBassa();
   if ( (carte[cartaBassa])->getSeme() == semeBriscola )
   {
      unsigned valoreCartaAlta = (carte[cartaPiuAlta()])->getValore();
      unsigned valoreCartaMedia = (carte[ilTerzoNumero(cartaBassa,cartaPiuAlta())])->getValore();
      if ( aMAGGIOREb(valoreCartaAlta,'R') && aMAGGIOREb(valoreCartaMedia,'R') )
         return true;
   }
   /**************************************/
   return false;
}
