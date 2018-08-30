#include "GiocatoriDerivati.hpp"

GiocatoreUmano::GiocatoreUmano(string name, bool assoPrima, bool briscolaSeconda)
   :Giocatore(name),assoDiPrima(assoPrima),secondaBriscola(briscolaSeconda)
{
   type = "umano";
}

GiocatoreUmano::~GiocatoreUmano()
{
   // non elimino le carte perchè devono rimanere nel mazzo
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

bool GiocatoreUmano::bussareOno() 
{
   char a;
   cout << nome << ": bussare? (y/n) " << endl;
   cin >> a; 
   return ( (a == 'y') || (a == 'Y') ); 
}
   
bool GiocatoreUmano::vadoAlBuio() 
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
         cout << nome << ": Quale carta giocare? (briscola: " << *briscola << " )" << endl;
         for (unsigned i = 0; i < 3; i++)
         {
            if (carte[i] != NULL)
            {
               cout << i << ") " << *(carte[i]) << endl;
            }
         }
         unsigned a;
         cin >> a;
         while (a != hoAssoBriscola)
         {
            cout << "Devi giocare l'asso!" << endl;
            cin >> a;
         }
         Carta* c = carte[a];
         carte[a] = NULL;
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
            cout << nome << ": Quale carta giocare? Briscola: " << *briscola << endl;
            for (unsigned i = 0; i < 3; i++)
            {
               if (carte[i] != NULL)
               {
                  cout << i << ") " << *(carte[i]) << endl;
               }
            }
            unsigned a;
            cin >> a;
            bool briscolaGiocata = false;
            if (a >= 0 && a < 3)
            {
               if (carte[a] != NULL)
                  briscolaGiocata = (carte[a]->getSeme() == briscola->getSeme());
            }
            while (!briscolaGiocata)
            {
               cout << "Di seconda devi giocare briscola!" << endl;
               cin >> a;
               if (a >= 0 && a < 3)
               {
                  if (carte[a] != NULL)
                     briscolaGiocata = (carte[a]->getSeme() == briscola->getSeme());
               }
            }
            Carta* c = carte[a];
            carte[a] = NULL;
            return c;
         }
      }
      //NON E' UN ELSE PERCHE' ELSE IF potrebbe non eseguire in quanto non ha ancora controllato di essere di seconda
      ///cout << "sono di mano, gioco come voglio" << endl;
      //significa che sono io di mano
      // gioco come voglio
      cout << nome << ": Quale carta giocare? Briscola: " << *briscola << endl;
      for (unsigned i = 0; i < 3; i++)
      {
         if (carte[i] != NULL)
         {
            cout << i << ") " << *(carte[i]) << endl;
         }
      }
      unsigned a;
      cin >> a;
      while (!(a == 0 || a == 1 || a == 2) || carte[a] == NULL )
      {
         cout << "Valore non valido. Riscegliere la carta: ";
         cin >> a;
      }
      Carta* c = carte[a];
      carte[a] = NULL;
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
         cout << nome << ": Quale carta giocare? Briscola: " << *briscola << endl;
         for (unsigned i = 0; i < 3; i++)
         {
            if (carte[i] != NULL)
            {
               cout << i << ") " << *(carte[i]) << endl;
            }
         }
         unsigned a;
         cin >> a;
         bool briscolaGiocata = false;
         if (a >= 0 && a < 3)
         {
            if (carte[a] != NULL)
               briscolaGiocata = (carte[a]->getSeme() == briscola->getSeme());
         }
         ///cout << "briscola giocata: " << briscolaGiocata << endl;
         while (!briscolaGiocata)
         {
            cout << "Devi giocare briscola!" << endl;
            cin >> a;
            if (a >= 0 && a < 3)
            {
               if (carte[a] != NULL)
                  briscolaGiocata = (carte[a]->getSeme() == briscola->getSeme());
            }
         }
         Carta* c = carte[a];
         carte[a] = NULL;
         return c;
      }
      else
      {
         ///cout << "non ho ne briscola ne palo => gioco come voglio" << endl;
         //non ho ne briscola ne palo => gioco come voglio
         cout << nome << ": Quale carta giocare? Briscola: " << *briscola << endl;
         for (unsigned i = 0; i < 3; i++)
         {
            if (carte[i] != NULL)
            {
               cout << i << ") " << *(carte[i]) << endl;
            }
         }
         unsigned a;
         cin >> a;
         while (!(a == 0 || a == 1 || a == 2) || carte[a] == NULL )
         {
            cout << "Valore non valido. Riscegliere la carta: ";
            cin >> a;
         }
         Carta* c = carte[a];
         carte[a] = NULL;
         return c;
      }
   }
   else
   {
      // ho palo
      // gioco palo
      ///cout << "ho palo" << endl;
      cout << nome << ": Quale carta giocare? Briscola: " << *briscola << endl;
      for (unsigned i = 0; i < 3; i++)
      {
         if (carte[i] != NULL)
         {
            cout << i << ") " << *(carte[i]) << endl;
         }
      }
      unsigned a;
      cin >> a;
      bool paloGiocato = false;
      if (a >= 0 && a < 3)
      {
         if (carte[a] != NULL)
            paloGiocato = (carte[a]->getSeme() == palo);
      }
      while (!paloGiocato)
      {
         cout << "Devi seguire il seme!" << endl;
         cin >> a;
         if (a >= 0 && a < 3)
         {
            if (carte[a] != NULL)
               paloGiocato = (carte[a]->getSeme() == palo);
         }
      }
      Carta* c = carte[a];
      carte[a] = NULL;
      return c;
   }
   ///cout << "NIENTE" << endl;
   cout << nome << ": Quale carta giocare? Briscola: " << *briscola << endl;
   for (unsigned i = 0; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         cout << i << ") " << *(carte[i]) << endl;
      }
   }
   unsigned a;
   cin >> a;
   while (!(a == 0 || a == 1 || a == 2) || carte[a] == NULL )
   {
      cout << "Valore non valido. Riscegliere la carta: "; 
      cin >> a;
   }
   Carta* c = carte[a];
   carte[a] = NULL;
   return c;
}


/**** 
 * 
 *    AI
 * 
 ****/

// DA CONTROLLARE

AI::AI(string name, bool assoPrima, bool briscolaSeconda)
   :Giocatore(name),assoDiPrima(assoPrima),secondaBriscola(briscolaSeconda)
{
   type = "AI";
}

AI::~AI()
{
   // non elimino le carte perchè devono rimanere nel mazzo
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

Carta* AI::giocaCarta(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate, bool ultimo, unsigned posto, bool debug)
{
   if (debug)
      stampaCarte();
/***
 * se DiMano && Secondo Giro && Due Briscole   gioca la più piccola
 * se DiMano carta più alta non briscola
 * se DiMano && 3 briscole gioca la più alta
 * se nessuno ha giocato briscola taglieggio con la più bassa
 ***/
   Carta* cp;
   unsigned cpIndex;
   unsigned numCarte = 0;
   for (unsigned i = 0; i < 3; i++)
   {
      if (carte[i] != NULL)
         numCarte++;
   }
   if (numCarte == 1)
   {
      // se ho una sola carta
      for (unsigned i = 0; i < 3; i++)
      {
         if (carte[i] != NULL)
         {
            cp = carte[i];
            carte[i] = NULL;
            return cp;
         }
      }
   }
   else
   {
      if (diMano == posto)
      {  // se sono di mano
         if (debug)
            cout << "di mano" << endl;
         if (numCarte == 3)
         { //primo giro
            if (debug)
               cout << "primo giro" << endl;
            int cartaIndex;
            if (briscola->getValore() == 'A')
            {   // cioè come briscola c'è l'asso, devo giocare il 3
               if (debug)
                  cout << "briscola asso" << endl;
               cartaIndex = cercaCarta('3',briscola->getSeme());
               if (cartaIndex != -1)
               {
                  cp = carte[cartaIndex];
                  carte[cartaIndex] = NULL;
                  return cp;
               }
               else
               {
                  cpIndex = cartaPiuAltaNonBriscola(briscola->getSeme());
                  cp = carte[cpIndex];
                  carte[cpIndex] = NULL;
                  return cp;
               }
            }
            else
            {
               //devo giocare l'asso se ce l'ho, se non ho asso la più alta non briscola
               cartaIndex = cercaCarta('A',briscola->getSeme());
               if (cartaIndex != -1)
               {
                  cpIndex = cartaIndex;
                  cp = carte[cpIndex];
                  carte[cpIndex] = NULL;
                  return cp;
               }
               else
               {
                  cpIndex = cartaPiuAltaNonBriscola(briscola->getSeme());
                  if (cpIndex == -1)
                  {  //se tutte briscola
                     cpIndex = cartaPiuAlta(briscola->getSeme());
                  }
                  cp = carte[cpIndex];
                  carte[cpIndex] = NULL;
                  return cp;
               }
            }
         }
         else
         {
            // due carte
            if (debug)
               cout << "due carte" << endl;
            //secondo giro, se ho, gioco la briscola più piccola
            if (numCarteSeme(briscola->getSeme()) != 0)
            {
               cpIndex = cartaPiuBassa(briscola->getSeme());
               cp = carte[cpIndex];
               carte[cpIndex] = NULL;
               return cp;
            }
            else
            {
               if (debug)
                  cout << "non briscola" << endl;
               cpIndex = cartaPiuAltaNonBriscola(briscola->getSeme());
               cp = carte[cpIndex];
               carte[cpIndex] = NULL;
               return cp;
            }
         }
      }
      else
      {
         // se non sono di mano        
         char paloSeme = palo(diMano,carteGiocate);
         unsigned numCartePalo = numCarteSeme(paloSeme);
         if (numCartePalo != 0)
         {
         // ho palo
            if (debug)
               cout << "seguo palo" << endl;
            if (numCartePalo == 1)
            {
               //butto quella
               cpIndex = cartaPiuAlta(paloSeme); // visto che ne ho una sola gioco "la più alta"
               cp = carte[cpIndex];
               carte[cpIndex] = NULL;
               return cp;
            }
            else
            { // due o tre carte del palo
               if (ultimo)
               {
               //la più piccola che prende
                  //se è stata giocata briscola e palo!=briscola
                  if (briscolaGiocata(briscola,carteGiocate) && paloSeme != briscola->getSeme())
                  {
                     //butto la più bassa di quel seme, che tanto non prendo
                     cpIndex = cartaPiuBassa(paloSeme);
                     cp = carte[cpIndex];
                     carte[cpIndex] = NULL;
                     return cp;
                  }
                  else
                  {
                  //ELSE: o non è stata giocata briscola, oppure briscola==palo
                     //butto la più bassa che prende
                        /* Se ho 2 carte
                         *    prendo la più bassa e me la salvo
                         *    se batte 
                         *       butto questa
                         *    ELSE
                         *       prendo la più alta
                         *       se batte
                         *          butto questa
                         *       ELSE
                         *          butto la più bassa
                         * se ho 3 carte
                         *    prendo la più bassa e me la salvo
                         *    se batte 
                         *       butto questa
                         *    ELSE
                         *       prendo ne più alta nè più bassa //FUNZIONE
                         *       se batte
                         *          butto questa
                         *       ELSE
                         *          prendo la più alta
                         *          se batte
                         *             butto questa
                         *          ELSE
                         *             butto la più bassa
                         * CONTROLLARE BRISCOLA
                         */
                     if (numCartePalo == 2)
                     {
                        unsigned piuBassa = cartaPiuBassa(paloSeme);
                        char valVincente = valoreVincente(diMano,briscola,carteGiocate);
                        if ( aMAGGIOREb( carte[piuBassa]->getValore() , valVincente) )
                        {
                           cpIndex = piuBassa;
                           cp = carte[cpIndex];
                           carte[cpIndex] = NULL;
                           return cp;
                        }
                        else
                        {
                           unsigned piuAlta = cartaPiuAlta(paloSeme);
                           if ( aMAGGIOREb( carte[piuAlta]->getValore() , valVincente ) )
                           { 
                              cpIndex = piuAlta;
                              cp = carte[cpIndex];
                              carte[cpIndex] = NULL;
                              return cp;
                           }
                           else
                           {
                              cpIndex = piuBassa;
                              cp = carte[cpIndex];
                              carte[cpIndex] = NULL;
                              return cp;
                           }
                        }
                     }
                     else
                     { // 3 carte
                        unsigned piuBassa = cartaPiuBassa(paloSeme);
                        char valVincente = valoreVincente(diMano,briscola,carteGiocate);
                        if ( aMAGGIOREb(carte[piuBassa]->getValore() , valVincente) )
                        {
                           // la batte quindi gioco questa
                           cpIndex = piuBassa;
                           cp = carte[cpIndex];
                           carte[cpIndex] = NULL;
                           return cp;
                        }
                        else
                        {  // prendo ne piu alta ne piu bassa
                           unsigned piuAlta = cartaPiuAlta(paloSeme);
                           unsigned nePiuAltaNePiuBassa = ilTerzoNumero(piuBassa,piuAlta);
                           if ( aMAGGIOREb( carte[nePiuAltaNePiuBassa]->getValore() , valVincente) )
                           {
                              cpIndex = nePiuAltaNePiuBassa;
                              cp = carte[cpIndex];
                              carte[cpIndex] = NULL;
                              return cp;
                           }
                           else
                           {
                              if ( aMAGGIOREb( carte[piuAlta]->getValore() , valVincente ) )
                              {
                                 cpIndex = piuAlta;
                                 cp = carte[cpIndex];
                                 carte[cpIndex] = NULL;
                                 return cp;
                              }
                              else
                              {
                                 cpIndex = piuBassa;
                                 cp = carte[cpIndex];
                                 carte[cpIndex] = NULL;
                                 return cp;
                              }
                           }
                        }
                     }
                  }
               }
               else
               { //DUE O TRE CARTE DEL PALO
                  //siccome non sono ultimo, la più alta che ho se non c'è briscola
                  //se è stata giocata briscola e palo!=briscola
                  if (briscolaGiocata(briscola,carteGiocate) && paloSeme != briscola->getSeme())
                  {
                     //butto la più bassa di quel seme, che tanto non prendo
                     cpIndex = cartaPiuBassa(paloSeme);
                     cp = carte[cpIndex];
                     carte[cpIndex] = NULL;
                     return cp;
                  }
                  else
                  {  // o non è stata giocata briscola quindi il palo vale, oppure il palo è briscola (quindi anche qui il palo vale)
                     unsigned piuAlta = cartaPiuAlta(paloSeme);
                     char valVincente = valoreVincente(diMano,briscola,carteGiocate);
                     if ( aMAGGIOREb(carte[piuAlta]->getValore() , valVincente) )
                     {
                        // la batte quindi gioco questa
                        cpIndex = piuAlta;
                        cp = carte[cpIndex];
                        carte[cpIndex] = NULL;
                        return cp;
                     }
                     else
                     {
                        // la mia carta più alta non prende quindi butto la più bassa
                        cpIndex = cartaPiuBassa(paloSeme);
                        cp = carte[cpIndex];
                        carte[cpIndex] = NULL;
                        return cp;
                     }
                  }
               }
            }
         }
         else
         {
         // non ho palo
            if (debug)
               cout << "non ho palo" << endl;
            unsigned numCarteBriscola = numCarteSeme(briscola->getSeme());
            if (numCarteBriscola != 0)
            {    // ho briscola
               if (numCarteBriscola == 1)
               {  //butto quella che ho
                  cpIndex = cartaPiuAlta(briscola->getSeme());
                  cp = carte[cpIndex];
                  carte[cpIndex] = NULL;
                  return cp;
               }
               else if (!briscolaGiocata(briscola,carteGiocate))
               {  // se nessuno ha giocato briscola butto la piu piccola
                  cpIndex = cartaPiuBassa(briscola->getSeme());
                  cp = carte[cpIndex];
                  carte[cpIndex] = NULL;
                  return cp;
               }
               else
               {  // è stata giocata briscola, quindi valore vincente sicuramente briscola
                  if (numCarteBriscola == 2)
                  {
                     unsigned piuBassa = cartaPiuBassa(briscola->getSeme());
                     char valVincente = valoreVincente(diMano,briscola,carteGiocate);
                     if ( aMAGGIOREb( carte[piuBassa]->getValore() , valVincente) )
                     {
                        cpIndex = piuBassa;
                        cp = carte[cpIndex];
                        carte[cpIndex] = NULL;
                        return cp;
                     }
                     else
                     {
                        unsigned piuAlta = cartaPiuAlta(briscola->getSeme());
                        if ( aMAGGIOREb( carte[piuAlta]->getValore() , valVincente ) )
                        { 
                           cpIndex = piuAlta;
                           cp = carte[cpIndex];
                           carte[cpIndex] = NULL;
                           return cp;
                        }
                        else
                        {
                           cpIndex = piuBassa;
                           cp = carte[cpIndex];
                           carte[cpIndex] = NULL;
                           return cp;
                        }
                     }
                  }
                  else
                  { // 3 carte
                     unsigned piuBassa = cartaPiuBassa(briscola->getSeme());
                     char valVincente = valoreVincente(diMano,briscola,carteGiocate);
                     if ( aMAGGIOREb(carte[piuBassa]->getValore() , valVincente) )
                     {
                        // la batte quindi gioco questa
                        cpIndex = piuBassa;
                        cp = carte[cpIndex];
                        carte[cpIndex] = NULL;
                        return cp;
                     }
                     else
                     {  // prendo ne piu alta ne piu bassa
                        unsigned piuAlta = cartaPiuAlta(briscola->getSeme());
                        unsigned nePiuAltaNePiuBassa = ilTerzoNumero(piuBassa,piuAlta);
                        if ( aMAGGIOREb( carte[nePiuAltaNePiuBassa]->getValore() , valVincente) )
                        {
                           cpIndex = nePiuAltaNePiuBassa;
                           cp = carte[cpIndex];
                           carte[cpIndex] = NULL;
                           return cp;
                        }
                        else
                        {
                           if ( aMAGGIOREb( carte[piuAlta]->getValore() , valVincente ) )
                           {
                              cpIndex = piuAlta;
                              cp = carte[cpIndex];
                              carte[cpIndex] = NULL;
                              return cp;
                           }
                           else
                           {
                              cpIndex = piuBassa;
                              cp = carte[cpIndex];
                              carte[cpIndex] = NULL;
                              return cp;
                           }
                        }
                     }
                  }
               }            
            }
            else
            {     // non ho briscola
               if (debug)
                  cout << "non ho palo non ho briscola" << endl;
               cpIndex = cartaDaButtarVia();
               cp = carte[cpIndex];
               carte[cpIndex] = NULL;
               return cp;
            }         
         }
      }
   }
   // non dovrebbe arrivare qui
   return nullptr;
}

int AI::cercaCarta(char v, char s) //ritorna l'indice se c'è o -1 se non c'è
{
   for (unsigned i=0; i<3; i++)
   {
      if (carte[i]->getSeme() == s && carte[i]->getValore() == v)
         return i;
   }
   return -1;
}


int AI::cartaPiuAltaNonBriscola(char briscolaSeme) //non briscola, ritorna -1 se tutto briscola
{
   /*unsigned max = 0;
   bool flag = false; // trovata un carta non di briscola
   while (!flag && max < 3)
   {
      if (carte[max] != NULL)
      {
         if (carte[max]->getSeme() == briscolaSeme)
            max++;
         else
            flag = true;
      }
   }
   if (max == 3) // tutto briscola
      return -1;
   else if (max == 2) // ho solo la terza carta non briscola
      return max;
   for (unsigned i = max + 1; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         if ( aMAGGIOREb(carte[i]->getValore(),carte[max]->getValore()) ) //guardo il valore perchè potrebbero non avere lo stesso seme
            max = i;
      }
   }
   return max;*/
   // metto in un vector gli indici delle carte non briscola
   // trovo la carta maggiore tra quegli indici
   vector <unsigned> indiciNonBriscola;
   for (unsigned i = 0; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() != briscolaSeme) // se non è briscola aggiungo al vettore
            indiciNonBriscola.push_back(i);
      }
   }
   unsigned length = indiciNonBriscola.size();
   if (length == 0)
      return -1; // tutte briscola
   unsigned max = indiciNonBriscola[0];
   for (unsigned i = 1; i < indiciNonBriscola.size(); i++)
   {
      if ( aMAGGIOREb(carte[indiciNonBriscola[i]]->getValore(),carte[max]->getValore()) )
         max = indiciNonBriscola[i];
   }
   return max;
}

int AI::cartaPiuAlta(char s)
{
   vector <unsigned> indiciCarteSeme;
   for (unsigned i = 0; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() == s)
            indiciCarteSeme.push_back(i);
      }
   }
   unsigned length = indiciCarteSeme.size();
   if (length == 0)
      return -1;
   else if (length == 1)
      return indiciCarteSeme[0];
   else if (length == 2)
   {
      if (*carte[indiciCarteSeme[0]] > *carte[indiciCarteSeme[1]]) // comparo le carte perchè stesso seme
         return indiciCarteSeme[0];
      else
         return indiciCarteSeme[1];
   }
   else // length == 3, quindi tutte le carte di quel seme quindi non mi serve il vettore degli indici, inoltre significa che ha 3 carte quindi nessun puntatore NULL
   {
      unsigned max = 0;
      for (unsigned i = 1; i < 3; i++)
      {
         if (*carte[i] > *carte[max])
            max = i;
      }
      return max;
   }
}

unsigned AI::cartaPiuAlta()
{
   unsigned max = 0;
   for (unsigned i = max + 1; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         if ( aMAGGIOREb(carte[i]->getValore(),carte[max]->getValore()) ) //devo controllare valore perchè non stesso seme
            max = i;
      }
   }
   return max;
}

unsigned AI::cartaPiuBassa()
{
   unsigned min = 0;
   for (unsigned i = min + 1; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         if ( aMINOREb(carte[i]->getValore(),carte[min]->getValore()) ) //devo controllare valore perchè non stesso seme
            min = i;
      }
   }
   return min;
}

int AI::cartaPiuBassa(char s)
{
   vector <unsigned> indiciCarteSeme;
   for (unsigned i = 0; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() == s)
            indiciCarteSeme.push_back(i);
      }
   }
   unsigned length = indiciCarteSeme.size();
   if (length == 0)
      return -1;
   else if (length == 1)
      return indiciCarteSeme[0];
   else if (length == 2)
   {
      if (*carte[indiciCarteSeme[0]] < *carte[indiciCarteSeme[1]]) //confronto carte perchè stesso seme
         return indiciCarteSeme[0];
      else
         return indiciCarteSeme[1];
   }
   else // length == 3, quindi tutte le carte di quel seme quindi non mi serve il vettore degli indici, inoltre significa che ha 3 carte quindi nessun puntatore NULL
   {
      return cartaPiuBassa();
   }
}
//
char AI::palo(unsigned diMano, const vector <Carta*> carteGiocate) //non controlla che sia stata giocata la carta del giocatore di mano
{
   return carteGiocate[diMano]->getSeme();
}

char AI::valoreVincente(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate)
{
   char seme;
   if (briscolaGiocata(briscola,carteGiocate))
      seme = briscola->getSeme();
   else
      seme = palo(diMano,carteGiocate);
   unsigned length = carteGiocate.size();
   int max = -1;
   for (unsigned i = 0; i < length; i++)
   {
      if (carteGiocate[i] != NULL)
      {
         if (carteGiocate[i]->getSeme() == seme)
         {
            if (max == -1) // la prima carta di quel seme che trovo
               max = i;
            else
            {
               if (*carteGiocate[i] > *carteGiocate[max])
                  max = i;
            }
         }
      }
   }
   return carteGiocate[max]->getValore();
}

bool AI::briscolaGiocata(const Carta* briscola, const vector <Carta*> carteGiocate)
{
   unsigned length = carteGiocate.size();
   for (unsigned i = 0; i < length; i++)
   {
      if (carteGiocate[i] != NULL)
      {
         if (carteGiocate[i]->getSeme() == briscola->getSeme())
            return true;
      }
   }
   return false;
}


unsigned AI::numCarteSeme(char s) //numero carte di un seme
{
   unsigned num = 0;
   for (unsigned i = 0; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         if (carte[i]->getSeme() == s)
            num++;
      }
   }
   return num;
}

unsigned AI::cartaDaButtarVia() //la più bassa del seme in cui ho più carte
{
   char semi[4] = {'B','C','D','S'};
   unsigned carteSeme[4] = {0,0,0,0};
   char a;
   // contare le carte di ogni seme
   for (unsigned i = 0; i < 3; i++)
   {
      if (carte[i] != NULL)
      {
         a = carte[i]->getSeme();
         switch (a)
         {
            case 'B':
               carteSeme[0]++;
               break;
            case 'C':
               carteSeme[1]++;
               break;
            case 'D':
               carteSeme[2]++;
               break;
            case 'S':
               carteSeme[3]++;
               break;
         }
      }
   }
   // massimo vettore
   unsigned max = 0;
   for (unsigned i = 1; i < 4; i++)
   {
      if (carteSeme[i] >= carteSeme[max]) // metto = perchè NON LO SO 
         max = i;
   }
   if (carteSeme[max] == 1) //se ho tre semi diversi
      return cartaPiuBassa();
   else
      return cartaPiuBassa(semi[max]); //se c'è un seme con più carte butto via di la più bassa di quel seme
}

/*** BRUNO ***/
Bruno::Bruno(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,assoPrima,briscolaSeconda)
{
   type = "Bruno";
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
   //cout << "bruno" << endl;
   //char a;
   //cout << nome << ": bussare? (y/n) " << endl;
   //cin >> a; 
   //return ( (a == 'y') || (a == 'Y') );
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

/*************/

/*** TIGHT ***/
Tight::Tight(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,assoPrima,briscolaSeconda)
{
   type = "Tight";
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

/*************/

/*** BLIND ***/
Blind::Blind(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,assoPrima,briscolaSeconda)
{
   type = "Blind";
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

/*************/

/*** LOOSE ***/
Loose::Loose(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,assoPrima,briscolaSeconda)
{
   type = "Loose";
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

/*************/

/*** ROBIN ***/
Robin::Robin(string name, bool assoPrima, bool briscolaSeconda)
   :AI(name,assoPrima,briscolaSeconda)
{
   type = "Robin";
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

/*************/



/**** SPOSTATO IN CARTA.HPP
bool AI::aMAGGIOREb(char a, char b) //valore della carta
{
   switch (b) // valore di operando destra,  a > b, b
   {
      case 'A': // se b è un asso a non potrà essere più grande
         cout << "A" << endl;
         return false;
         break;
      case '3':
         cout << "3" << endl;
         return a == 'A';
         break;
      case 'R':
         cout << "R" << endl;
         return (a == 'A') || (a == '3');
         break;
      case 'C':
         cout << "C" << endl;
         return (a == 'A') || (a == '3') || (a == 'R');
         break;
      case 'F':
         cout << "F" << endl;
         return (a == 'A') || (a == '3') || (a == 'R') || (a == 'C');
         break;
      default: // 7,6,5,4,2
         if ((a == 'A') || (a == '3') || (a == 'R') || (a == 'C') || (a == 'F'))
            return true;
         return (a - '0') > (b - '0');
         break;
      
   }
}

bool AI::aMINOREb(char a, char b) //valore della carta
{
   return b > a;
}

static unsigned ilTerzoNumero(unsigned a, unsigned b)
{
   if (a == 0)
   {
      if (b == 1)
         return 2;
      else
         return 1;
   }
   if (a == 1)
   {
      if (b == 0)
         return 2;
      else
         return 0;
   }
   if (a == 2)
   {
      if (b == 0)
         return 1;
      else
         return 0;
   }
   return 4; //ERRORE
}
**********/