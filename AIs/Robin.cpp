#include "Robin.hpp"

Robin::Robin(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,"Robin",assoPrima,briscolaSeconda)
{
}

Robin::~Robin()
{
   // non elimino le carte perchè devono rimanere nel mazzo
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

bool Robin::vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) 
{
   /*** ultimo posto && nessuno è andato && POT ***/
   if (ultimo && nessunoAndato && (soldi >= pot))
   {
      cout << nome << " va al buio" << endl;
      return true;
   }
   /***********************************************/
   /*** 12POT 5/10 ***/
   if (soldi >= pot*12)
   {
      unsigned randomNumber = randomInterval(0,9,pot/posto); // pot/posto è un extraseed per rendere ancora più casuale
      if (randomNumber < 5) // 0,1,2,3,4
      {
         cout << nome << " va al buio" << endl;
         return true;
      }
   }
   /******************/
   cout << nome << " non va al buio" << endl;
   return false;
}

bool Robin::bussareOno(const Carta* briscola) 
{
   char semeBriscola = briscola->getSeme(); 
   /*** se ho l'asso di briscola ***/
   if (cercaCarta('A',semeBriscola) != -1)
      return true;
   /********************************/
   // conto il numero di briscole
   unsigned numBriscole = 0;
   for (unsigned i=0; i<3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() == semeBriscola)
            numBriscole++;
      }
   }
   /*** se tre briscole ***/
   if (numBriscole == 3)
      return true;
   /***********************/
   /*** se due briscole... ***/
   if (numBriscole == 2)
   {
      /*** almeno 1 figura di briscola ***/
      for (unsigned i=0; i<3; i++)
      {
         if (carte[i] != NULL)
         {
            if (carte[i]->getSeme() == semeBriscola && aMAGGIOREb(carte[i]->getValore(),'7') )
               return true;
         }
      }
      /***********************************/
      /*** Somma briscole >= 11 ***/
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
      /*** 9 punti di Briscola e una figura non briscola ***/
         // siccome se ho una figura di briscola vado, se arrivo qui vuol dire che non ho una figura di briscola
         // QUINDI basta cercare una figura generica
      if (puntiBriscola >= 9)
      {
         for (unsigned i=0; i<3; i++)
         {
            if (carte[i] != NULL)
            {
               if (aMAGGIOREb(carte[i]->getValore(),'7') )
                  return true;
            }
         }
      }
      /*****************************************************/
   }
   /**************************/ 

   /*** se la briscola è l'asso ***/
   if (briscola->getValore() == 'A')
   {
      /* e ho il 3 di briscola */
      if (cercaCarta('3',semeBriscola) != -1)
         return true;
      /*-----------------------*/
      /* re e altra figura */
      if (cercaCarta('R',semeBriscola) != -1)
      {
         // controllo di avere due figure perchè una è il re stesso
         unsigned numFigure = 0;
         for (unsigned i=0; i < 3; i++)
         {
            if (aMAGGIOREb(carte[i]->getValore(),'7'))
               numFigure++;
         }
         if (numFigure >= 2)
            return true;
      }
      /*---------------------*/
      /* cavallo e altre 2 figure */
      if (cercaCarta('C',semeBriscola) != -1)
      {
         unsigned numFigure = 0;
         for (unsigned i=0; i < 3; i++)
         {
            if (aMAGGIOREb(carte[i]->getValore(),'7'))
               numFigure++;
         }
         if (numFigure == 3)
            return true;
      }
      /*----------------------------*/      
   }
   /*****************************************************/
   /*** se la briscola è il 3 ***/
   if (briscola->getValore() == '3')
   {
      /* re e altra figura */
      if (cercaCarta('R',semeBriscola) != -1)
      {
         unsigned numFigure = 0;
         for (unsigned i=0; i < 3; i++)
         {
            if (aMAGGIOREb(carte[i]->getValore(),'7'))
               numFigure++;
         }
         if (numFigure >= 2)
            return true;
      }
      /*---------------------*/
      /* cavallo e altre 2 figure */
      if (cercaCarta('C',semeBriscola) != -1)
      {
         unsigned numFigure = 0;
         for (unsigned i=0; i < 3; i++)
         {
            if (aMAGGIOREb(carte[i]->getValore(),'7'))
               numFigure++;
         }
         if (numFigure == 3)
            return true;
      }
      /*----------------------------*/
   }
   /*****************************/
   /*** se 3 di briscola e un'altra figura ***/
   if (cercaCarta('3',semeBriscola) != -1)
   {
      unsigned numFigure = 0;
      for (unsigned i=0; i < 3; i++)
      {
         if (aMAGGIOREb(carte[i]->getValore(),'7'))
            numFigure++;
      }
      if (numFigure >= 2)
         return true;
   }
   /******************************************/
   /*** se Re di briscola e altre due figure ***/
   if (cercaCarta('R',semeBriscola) != -1)
   {
      unsigned numFigure = 0;
      for (unsigned i=0; i < 3; i++)
      {
         if (aMAGGIOREb(carte[i]->getValore(),'7'))
            numFigure++;
      }
      if (numFigure == 3)
         return true;
   }
   /******************************************/
   /*** 2 A e un'altra figura ***/
   unsigned numAssi = 0;
   bool treFigure = true;
   unsigned i=0;
   while (treFigure && i<3)
   {
      if (carte[i] != NULL)
      {
         char valoreCarta = carte[i]->getValore();
         if (aMAGGIOREb(valoreCarta,'7'))
         {
            if (valoreCarta == 'A')
               numAssi++;
         }
         else
         {
            treFigure= false;
         }
      }
      i++;
   }
   if (treFigure && numAssi >= 2)
      return true;
   /***********/
   /*** se tutte le carte A o 3 ***/
      // se la carta più bassa è un 3 o A
   char valore = (carte[cartaPiuBassa()])->getValore();
   if (valore == '3' || valore == 'A')
      return true;
   /*******************************/

   return false;
}
