#include "GiocatoreUmano.hpp"

GiocatoreUmano::GiocatoreUmano(string name, bool assoPrima, bool briscolaSeconda)
   :Giocatore(name,"umano"),assoDiPrima(assoPrima),secondaBriscola(briscolaSeconda)
{
}

GiocatoreUmano::~GiocatoreUmano()
{
   // non elimino le carte perchè devono rimanere nel mazzo
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

bool GiocatoreUmano::bussareOno(const Carta* briscola) 
{
   char a;
   cout << nome << ": bussare? (y/n) " << endl;
   cin >> a; 
   return ( (a == 'y') || (a == 'Y') ); 
}
   
bool GiocatoreUmano::vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) 
{
   char a;
   cout << nome << ": Andare al buio? (y/n) " << endl;
   cin >> a; 
   return ( (a == 'y') || (a == 'Y') ); 
}

Carta* GiocatoreUmano::giocaCarta(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate, bool ultimo, unsigned posto, bool debug) //CATCH NON NUMBERS
{ 
   /*** COSA HO? ***/
      // asso di briscola
   int hoAssoBriscola = -1; // tengo l'indice
      // quante briscole 
   unsigned briscole = 0;
   
   for (unsigned i = 0; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         // briscola
            // TRUE: briscole++ e asso?
         if (carte[i]->getSeme() == briscola->getSeme())
         {
            briscole++;
            if (carte[i]->getValore() == 'A') 
               hoAssoBriscola = i;
         }
      }
   }
   /*** ***/
   /*** COSA FARE ***/
   ///cout << "asso briscola: " << hoAssoBriscola << " briscole: " << briscole << endl;
   unsigned a;
   bool sonoDiPrimaMano = true;
   //controllare di essere di prima
   for (unsigned i = 0; i < carteGiocate.size(); i++)
   {
      sonoDiPrimaMano = sonoDiPrimaMano && (carteGiocate[i] == NULL); //se sono tutte NULL allora sono di prima
   }
   if (sonoDiPrimaMano)
   {
      ///cout << "SONO di Prima" << endl;
      if (assoDiPrima && (hoAssoBriscola != -1)) // c'è la regola e ho l'asso
      {
         ///cout << "sono di mano e ho l'asso" << endl;
         a = scegliCartaDaGiocare(briscola);
         while (a-1 != hoAssoBriscola)
         {
            cout << "Devi giocare l'asso! Riscegliere la carta: ";
            cin >> a;
         }
         Carta* c = carte[a-1];
         carte[a-1] = NULL;
         return c;
      }
      else if (secondaBriscola && briscole != 0) // c'è la regola ed ho briscola
      {
         ///cout << "elseIF" << endl;
         //controllare che sia il secondo giro
            //devo avere 2 carte
         unsigned carteVuote = 0;
         for (unsigned i = 0; i < 3; i++)
         {
            if (carte[i] == NULL)
               carteVuote++;
         }
         if (carteVuote == 1) // sono di seconda
         {
            ///cout << "Sono di prima, ho briscola ed è secondo giro" << endl;
            a = scegliCartaDaGiocare(briscola);
            bool briscolaGiocata = (carte[a-1]->getSeme() == briscola->getSeme());
            while (!briscolaGiocata)
            {
               cout << "Di seconda devi giocare briscola! Riscegliere la carta: ";
               cin >> a;
               a = loopPerValoreValido(a);
               briscolaGiocata = (carte[a-1]->getSeme() == briscola->getSeme());
            }
            Carta* c = carte[a-1];
            carte[a-1] = NULL;
            return c;
         }
      }
      //NON E' UN ELSE PERCHE' ELSE IF potrebbe non eseguire in quanto non ha ancora controllato di essere di seconda
      ///cout << "sono di mano, gioco come voglio" << endl;
      //significa che sono io di mano
      // gioco come voglio
      a = scegliCartaDaGiocare(briscola);
      Carta* c = carte[a-1];
      carte[a-1] = NULL;
      return c;
   }
   /*** ***/
   ///cout << "non sono di prima" << endl;
   // CONTROLLARE PALO
   char palo = carteGiocate[diMano]->getSeme();
   bool hoPalo = false;
   unsigned i = 0;
   while (!hoPalo && i < 3)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() == palo)
            hoPalo = true;
      }
      i++;
   }
   if (!hoPalo)
   {
      ///cout << "non ho palo" << endl;
      bool hoBriscola = false;
      unsigned i = 0;
      while (!hoBriscola && i < 3)
      {
         if (carte[i] != NULL)
         {
            if (carte[i]->getSeme() == briscola->getSeme())
               hoBriscola = true;
         }
         i++;
      }
      if (hoBriscola)
      {
         // gioco briscola
         ///cout << "ho briscola" << endl;
         a = scegliCartaDaGiocare(briscola);
         bool briscolaGiocata = (carte[a-1]->getSeme() == briscola->getSeme());
         ///cout << "briscola giocata: " << briscolaGiocata << endl;
         while (!briscolaGiocata)
         {
            cout << "Devi giocare briscola! Riscegliere la carta: ";
            cin >> a;
            a = loopPerValoreValido(a);
            briscolaGiocata = (carte[a-1]->getSeme() == briscola->getSeme());
         }
         Carta* c = carte[a-1];
         carte[a-1] = NULL;
         return c;
      }
      else
      {
         ///cout << "non ho ne briscola ne palo => gioco come voglio" << endl;
         //non ho ne briscola ne palo => gioco come voglio
         a = scegliCartaDaGiocare(briscola);
         Carta* c = carte[a-1];
         carte[a-1] = NULL;
         return c;
      }
   }
   else
   {
      // ho palo
      // gioco palo
      ///cout << "ho palo" << endl;
      a = scegliCartaDaGiocare(briscola);
      bool paloGiocato = (carte[a-1]->getSeme() == palo);
      while (!paloGiocato)
      {
         cout << "Devi seguire il seme! Riscegliere la carta: ";
         cin >> a;
         a = loopPerValoreValido(a);
         paloGiocato = (carte[a-1]->getSeme() == palo);
      }
      Carta* c = carte[a-1];
      carte[a-1] = NULL;
      return c;
   }
   ///cout << "NIENTE" << endl;
   a = scegliCartaDaGiocare(briscola);
   Carta* c = carte[a-1];
   carte[a-1] = NULL;
   return c;
}

unsigned GiocatoreUmano::scegliCartaDaGiocare(const Carta* briscola)
{
   cout << nome << ": Quale carta giocare? Briscola: " << *briscola << endl;
   for (unsigned i = 1; i <= 3; i++)
   {
      if (carte[i-1] != NULL)
      {
         cout << i << ") " << *(carte[i-1]) << endl;
      }
   }
   unsigned a;
   cin >> a;
   return loopPerValoreValido(a);
}

unsigned GiocatoreUmano::loopPerValoreValido(unsigned a)
{
   while (!(a == 1 || a == 2 || a == 3) || carte[a-1] == NULL)
   {
      cout << "Valore non valido. Riscegliere la carta: "; 
      cin >> a;
   }
   return a;   
}
