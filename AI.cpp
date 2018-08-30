#include "AI.hpp"

// DA CONTROLLARE

AI::AI(string name, string type, bool assoPrima, bool briscolaSeconda)
   :Giocatore(name,type),assoDiPrima(assoPrima),secondaBriscola(briscolaSeconda)
{
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
   int cpIndex;
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
            // se ho asso di briscola devo giocarlo
            // se ho 3 di briscola con A sul tavolo, allora devo giocare il 3
            if (debug)
               cout << "primo giro" << endl;
            // se briscola e' Asso, cerco se ho il 3
            // se no cerco l'Asso
            if (briscola->getValore() == 'A')
            {   // cioè come briscola c'è l'asso, devo giocare il 3
               if (debug)
                  cout << "briscola asso" << endl;
               cpIndex = cercaCarta('3',briscola->getSeme());
            }
            else
            {
               cpIndex = cercaCarta('A',briscola->getSeme());
            } 
            // se ho l'asso di briscola o il 3 (quando asso sul tavolo) -> lo gioco
            if (cpIndex != -1)
            {
               cp = carte[cpIndex];
               carte[cpIndex] = NULL;
               return cp;
            }
            else // se non ho asso di briscola o 3, gioco la carta piu' alta non briscola
            {     // se tutte briscole, la briscola piu' alta
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
               // non avendo briscola sicuro "cartaPiuAltaNonBriscola" non mi restituisce -1
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
                  // "cartaPiuAlta" non restituisce -1 perche' ho gia controllato che il seme c'e'
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
                        // "cartaPiuAlta" non restituisce -1 perche' ho gia controllato che il seme c'e'
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
                        // "cartaPiuBassa" non restituisce -1 perche' ho gia controllato che il seme c'e'
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
                           // "cartaPiuBassa" non restituisce -1 perche' ho gia controllato che il seme c'e'
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
                     // "cartaPiuAlta" non restituisce -1 perche' ho gia controllato che il seme c'e'
                  cpIndex = cartaPiuAlta(briscola->getSeme());
                  cp = carte[cpIndex];
                  carte[cpIndex] = NULL;
                  return cp;
               }
               else if (!briscolaGiocata(briscola,carteGiocate))
               {  // se nessuno ha giocato briscola butto la piu piccola
                     // "cartaPiuBassa" non restituisce -1 perche' ho gia controllato che il seme c'e'
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
