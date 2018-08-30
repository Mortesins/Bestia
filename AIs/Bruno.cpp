#include "Bruno.hpp"

Bruno::Bruno(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,"Bruno",assoPrima,briscolaSeconda)
{
}

Bruno::~Bruno()
{
   // non elimino le carte perchè devono rimanere nel mazzo
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

bool Bruno::vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) 
{
   /*** ultimo posto && nessuno è andato && 2xPOT ***/
   if (ultimo && nessunoAndato && (soldi >= pot*2))
   {
      cout << nome << " va al buio" << endl;
      return true;
   }
   if (soldi >= pot*4)
   {
      unsigned randomNumber = randomInterval(0,9,pot/posto); // pot/posto è un extraseed per rendere ancora più casuale
      if (randomNumber < 2) // 0,1
      {
         cout << nome << " va al buio" << endl;
         return true;
      }
   }
   cout << nome << " non va al buio" << endl;
   return false;
}

bool Bruno::bussareOno(const Carta* briscola) 
{
   char semeBriscola = briscola->getSeme(); 
   /*** se ho l'asso di briscola ***/
   if (cercaCarta('A',semeBriscola) != -1)
      return true;
   /********************************/
   /*** se la briscola è l'asso ***/
   if (briscola->getValore() == 'A')
   {
      /* e ho il 3 di briscola */
      if (cercaCarta('3',semeBriscola) != -1)
         return true;
      /*-----------------------*/
      /* re e altra briscola */
      if (cercaCarta('R',semeBriscola) != -1)
      {
         unsigned numBriscole = 0;
         for (unsigned i=0; i < 3; i++)
         {
            if (carte[i]->getSeme() == semeBriscola)
               numBriscole++;
         }
         if (numBriscole >= 2)
            return true;
      }
      /*---------------------*/
      /* cavallo e altre 2 briscole */
      if (cercaCarta('C',semeBriscola) != -1)
      {
         unsigned numBriscole = 0;
         for (unsigned i=0; i < 3; i++)
         {
            if (carte[i]->getSeme() == semeBriscola)
               numBriscole++;
         }
         if (numBriscole == 3)
            return true;
      }
      /*----------------------------*/      
   }
   /*****************************************************/
   /*** se la briscola è il 3 ***/
   if (briscola->getValore() == '3')
   {
      /* re e altra briscola */
      if (cercaCarta('R',semeBriscola) != -1)
      {
         unsigned numBriscole = 0;
         for (unsigned i=0; i < 3; i++)
         {
            if (carte[i]->getSeme() == semeBriscola)
               numBriscole++;
         }
         if (numBriscole >= 2)
            return true;
      }
      /*---------------------*/
      /* cavallo e altre 2 briscole */
      if (cercaCarta('C',semeBriscola) != -1)
      {
         unsigned numBriscole = 0;
         for (unsigned i=0; i < 3; i++)
         {
            if (carte[i]->getSeme() == semeBriscola)
               numBriscole++;
         }
         if (numBriscole == 3)
            return true;
      }
      /*----------------------------*/
   }
   /*****************************/
   /*** se la briscola è il Re ***/
   if (briscola->getValore() == 'R')
   {
      /* cavallo e altre 2 briscole */
      if (cercaCarta('C',semeBriscola) != -1)
      {
         unsigned numBriscole = 0;
         for (unsigned i=0; i < 3; i++)
         {
            if (carte[i]->getSeme() == semeBriscola)
               numBriscole++;
         }
         if (numBriscole == 3)
            return true;
      }
      /*----------------------------*/  
   }
   /******************************/
   /*** 3 di briscola e un'altra briscola ***/
   if (cercaCarta('3',semeBriscola) != -1)
   {
      unsigned numBriscole = 0;
      for (unsigned i=0; i < 3; i++)
      {
         if (carte[i]->getSeme() == semeBriscola)
            numBriscole++;
      }
      if (numBriscole >= 2)
         return true;      
   }
   /*****************************************/
   /*** Re di briscola e altre 2 briscole ***/
   if (cercaCarta('R',semeBriscola) != -1)
   {
      unsigned numBriscole = 0;
      for (unsigned i=0; i < 3; i++)
      {
         if (carte[i]->getSeme() == semeBriscola)
            numBriscole++;
      }
      if (numBriscole == 3)
         return true;      
   }
   /*****************************************/
   return false;
}
