#include "Tavolo.hpp"

Tavolo::Tavolo(unsigned n, unsigned dm)
   :NUMGIOCATORI(n),DEALERMONEY(dm)
{
   briscola = NULL;
   dealer = -1;
   pot = 0;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      carteGiocate.push_back(NULL);
      giocatori.push_back(ContainerGiocatore());
   }
   // SET UP mucchio
   // vector 0 a 39
   vector <int> numeri;
   for (unsigned i = 0; i < 40; i++)
      numeri.push_back(i);
   unsigned randInt;
   for (unsigned i = 0; i < 39; i++) //l'ultima la gestisco fuori
   {     //ogni giro prendo un numero a caso, assegno quella carta al mucchio,
         //poi elimino quel numero
         //quindi il random ogni volta ha come limite massimo un numero in meno
      randInt = randomInterval(0,39-i,i);
      mucchio.push_back(mazzo.getCartaPointer(numeri[randInt])); //non inserisco randInt, ma il numero del vettore numeri alla posizione randInt ( cambia perchè ogni giro elimino il numero usato)
      numeri.erase(numeri.begin() + randInt);
   }
   mucchio.push_back(mazzo.getCartaPointer(numeri[0]));
}

Tavolo::~Tavolo()
{
   // tutte le carte sono cancellate dal mazzo
}

void Tavolo::printPlayersType()
{
   for (unsigned i = 0; i < 4; i++)
	{
		cout << giocatori[i].giocatore->type << endl;
   }
   return;
}

void Tavolo::resetMucchio()
{
   unsigned length = mucchio.size();
   for (unsigned i = 0; i < length; i++)
   {
      // vuota tutto
      mucchio.erase(mucchio.begin());
   }
   vector <int> numeri;
   for (unsigned i = 0; i < 40; i++)
      numeri.push_back(i);
   unsigned randInt;
   for (unsigned i = 0; i < 39; i++) //l'ultima la gestisco fuori
   {     //ogni giro prendo un numero a caso, assegno quella carta al mucchio,
         //poi elimino quel numero
         //quindi il random ogni volta ha come limite massimo un numero in meno
      randInt = randomInterval(0,39-i,i);
      mucchio.push_back(mazzo.getCartaPointer(numeri[randInt])); //non inserisco randInt, ma il numero del vettore numeri alla posizione randInt ( cambia perchè ogni giro elimino il numero usato)
      numeri.erase(numeri.begin() + randInt);
   }
   mucchio.push_back(mazzo.getCartaPointer(numeri[0]));
   // vuota pozzo
   length = pozzo.size();
   for (unsigned i = 0; i < length; i++)
      pozzo.erase(pozzo.begin());
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

bool Tavolo::mettiSoldiDealer()
{
   giocatori[dealer].giocatore->versaSoldi(DEALERMONEY);
   if (giocatori[dealer].giocatore->getSoldi() < 0)
   {
      //cout << "ERRORE: negative money" << endl;
      throw giocatori[dealer].giocatore->getName();
      return false;
   }
   else
   {
      pot += 15;
      return true;
   }
}

bool Tavolo::mettiBestiaSoldi()
{     //reset bestia soldi
   bool buonfine = true;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (giocatori[i].inBestia)
      {
         giocatori[i].giocatore->versaSoldi(bestiaMoney);
         if (giocatori[i].giocatore->getSoldi() < 0)
         {
            cout << "ERRORE: negative money" << endl;
            throw giocatori[i].giocatore->getName();
            buonfine = false;
         }
         else
         {
            pot += bestiaMoney;
            giocatori[i].inBestia = false;
         }
      }
   }
   return buonfine;
}

void Tavolo::distribuisciCarte(unsigned giocatoreIndex)
{
   daiCarta(giocatoreIndex,-1);
   daiCarta(giocatoreIndex,-2);
   daiCarta(giocatoreIndex,-3);
   return;
}

void Tavolo::setBriscola()
{
   int i = randomInterval(0,mucchio.size() - 1);
   Carta* cp = mucchio[i];
   if (briscola == NULL)
   {
      briscola = cp;
      mucchio.erase(mucchio.begin() + i);
   }
   else
      cout << "ERRORE: c'è già una briscola" << endl;
   return;
}

int Tavolo::chiGioca(bool debug, int chiComincia)
{
   unsigned index;
   int primo = -1;
   if ( (chiComincia < 0) && (chiComincia >= NUMGIOCATORI) )
      index = next(dealer);
   else
      index = chiComincia;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (giocatori[index].giocatore->type == "umano")
      {
         for (unsigned j = 0; j < NUMGIOCATORI; j++)
         {
            getPlayerName(j);
            cout << endl;
            getPlayerStatus(j);
            cout << endl;
         }
      }
      if (debug)
         giocatori[index].giocatore->stampaCarte();
      if (giocatori[index].giocatore->bussareOno(briscola))
      {
         setInGioco(index);
         if (primo == -1)
            primo = index;
      }
      else
      {
         giocatori[index].giocatore->scartaTutto();
      }
      index = next(index);
   }
   return primo;
}

void Tavolo::chiVaAlBuio(int primo)
{
   // if un altro è in gioco nessuno al buio
      // return
   unsigned numGiocatoriInGioco = 0; 
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (giocatori[i].inGioco)
      {
         numGiocatoriInGioco++;
      }
      if (numGiocatoriInGioco > 1) // se 2 giocatori in gioco allora nessuno al buio
         return;
   }
   
   bool ultimo = false; // parametro da passare al giocatore che dice se è ultimo o no
   bool nessunoAndato = true; // parametro per dire che nessuno è ancora andato al buio
   unsigned index;
   if ( (primo < 0) && (primo >= NUMGIOCATORI) )
      index = next(dealer);
   else
      index = next(primo); //perchè il primo è in gioco quindi non deve andare al buio
   for (unsigned i = 0; i < NUMGIOCATORI - 1; i++) // NUMGIOCATORI -1 perchè il giocatore in gioco non lo ciclo
   {
      if (giocatori[index].giocatore->type == "umano")
      {
         for (unsigned j = 0; j < NUMGIOCATORI; j++)
         {
            getPlayerName(j);
            cout << endl;
            getPlayerStatus(j);
            cout << endl;
         }
      }
      if (i == NUMGIOCATORI - 2) // l'ultimo giro il giocatore è ultimo, perchè ciclo NUMGIOCATORI-1 perchè quello che è in gioco non lo ciclo
         ultimo = true;
      if (!(giocatori[index].inGioco))
      {
         if (giocatori[index].giocatore->vadoAlBuio(pot,nessunoAndato,ultimo,index))
         {
            setInGioco(index);
            nessunoAndato = false;
            distribuisciCarte(index);
         }
      }
      else // se giocatori[index] è in gioco allora nessuno al buio
         return;
      index = next(index);
   }
}

void Tavolo::daiSoldiGiocatore(unsigned giocatoreIndex, unsigned soldi)
{
   giocatori[giocatoreIndex].giocatore->riceviSoldi(soldi);
   // è generica, i soldi li toglie qualcunaltro
   return;
}

void Tavolo::giocaCarta(unsigned giocatoreIndex, unsigned diMano, bool debug)
{
   bool ultimo = true;
   int i = next(giocatoreIndex); // parto dal giocatore giusto dopo
   while (i != diMano && ultimo) //fino a quando non arrivo al primo che gioca, e fintanto che sono ultimo (cioè non ho trovato nessuno dopo di me che gioca)
   {
      if (giocatori[i].inGioco)
         ultimo = false; // ho trovato qualcuno che gioca dopo di me, quindi non sono ultimo 
      i = next(i);
   } 
   // if giocatore umano stampa carte in gioco
   if (giocatori[giocatoreIndex].giocatore->type == "umano")
   {
      stampaCarteGiocate();
   }
   Carta* c = giocatori[giocatoreIndex].giocatore->giocaCarta(diMano,briscola,carteGiocate,ultimo,giocatoreIndex,debug);
   if (carteGiocate[giocatoreIndex] == NULL)
   {
      carteGiocate[giocatoreIndex] = c;
   }
   else
      cout << "ERRORE: carta già giocata" << endl;
   return;
}

unsigned Tavolo::chiudiGiro(int chiComincia)
{
   unsigned vincente; // la carta vincente è del primo che gioca (dopo il dealer)
   if ( (chiComincia < 0) && (chiComincia >= NUMGIOCATORI) )
   {
      vincente = next(dealer);
   }
   else
   {
      vincente = chiComincia;
   }
   unsigned index = next(vincente);
   bool briscolaGiocata = (carteGiocate[vincente]->getSeme() == briscola->getSeme()); // è già stata giocata briscola?
   //cout << "briscola giocata: " << briscolaGiocata << "; index " << index << "; vincente " << vincente << endl;
   // per 3 giri
      // la carta successiva è maggiore della vincente?
         //TRUE: cambiare vincente, continuare con la prossima carta
         //FALSE: briscola già giocata?
            // TRUE: se la briscola è già giocata e la carta non è maggiore, la carta o è di un altro seme oppure e minore => SKIP
            // FALSE: la carta è briscola
               //TRUE: cambiare vincente, briscolaGiocata = true
               //FALSE: skip
   for (unsigned i = 0; i < NUMGIOCATORI-1; i++) // su n carte devo fare n-1 controlli //(unsigned i = 1; i <= 3; i++) // i NON E' INDICE DEL GIOCATORE!!!
   {
      if (carteGiocate[index] != NULL) //così salto chi non gioca
      {
         // la carta successiva è maggiore della vincente?
         if (*(carteGiocate[index]) > *(carteGiocate[vincente]))
         {
            //cout << "index: " << index << " index > vincente = " << vincente << endl;
            //TRUE: cambiare vincente, continuare con la prossima carta
            vincente = index;
            //cout << "QUINDI: index: " << index << " vincente = " << vincente << endl;
         }
         else
         {
            //cout << "index: " << index << " index < vincente = " << vincente << endl;
            //FALSE: briscola non ancora giocata?
            if (!briscolaGiocata)
            {
               //cout << "briscola non giocata" << endl;
               // TRUE: la carta è briscola?
               if (carteGiocate[index]->getSeme() == briscola->getSeme())
               {
                  //cout << "index è briscola   ";
                  //TRUE: cambiare vincente, briscolaGiocata = true
                  vincente = index;
                  briscolaGiocata = true;
                  //cout << "briscola giocata: " << briscolaGiocata << "; index " << index << "; vincente " << vincente << endl;
               }          
                  //FALSE: skip
            }
         }
      }
      index = next(index);
   }
   // assegno una presa al vincente
   giocatori[vincente].numPrese++;
   // scarto le carte
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (carteGiocate[i] != NULL)
         pozzo.push_back(carteGiocate[i]);
      carteGiocate[i] = NULL;
   }
   return vincente;
}

void Tavolo::vincitoreIncontrastato()
{ 
   // SE HA BUSSATO UN SOLO GIOCATORE
   // scarta le carte
   // 3 prese
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {  // trovo l'unico giocatore che ha giocato
      if (giocatori[i].inGioco)
      {
         setNumPrese(i,3);
         giocatori[i].giocatore->scartaTutto();
         return;
      }
   }
   cout << "ERRORE: nessuno giocatore in gioco" << endl;
   return;
}

void Tavolo::giro(bool debug, int chiComincia)
{
   unsigned index;
   if ( (chiComincia < 0) && (chiComincia >= NUMGIOCATORI) )
      chiComincia = next(dealer);
   index = chiComincia;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (giocatori[index].inGioco)
         giocaCarta(index,chiComincia,debug);
      index = next(index);
   }
   return;
}

void Tavolo::dividereSoldiEBestia()  
{     // reset numPrese e InGioco
   unsigned share = pot / 3; //share per ogni presa
   bestiaMoney = pot;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      // SE HANNO GIOCATO
      if (giocatori[i].inGioco)
      {
         if (giocatori[i].numPrese == 0)
         {
            // in bestia
            giocatori[i].inBestia = true;
         }
         else
         {
            daiSoldiGiocatore(i,share*giocatori[i].numPrese);
            pot -= share*giocatori[i].numPrese;
            giocatori[i].numPrese = 0; //RESET
         }
         giocatori[i].inGioco = 0; //RESET
      }
   }
   // RESET BRISCOLA
   briscola = NULL;
}

void Tavolo::resetBriscola()
{
   briscola = NULL;
   return;
}

// PRIVATE
unsigned Tavolo::next(unsigned i)
{
   if (i + 1 == NUMGIOCATORI)
      return 0;
   else if (i + 1 > NUMGIOCATORI)
   {
      cout << "ERRORE: i out of bounds" << endl;
      return i;
   }
   else
      return i + 1;
}

// DIVENTERA' PRIVATE
void Tavolo::setNumPrese(unsigned i, unsigned prese) 
{ 
   giocatori[i].numPrese = prese; 
   return; 
} 

// DIVENTERA' PRIVATE
void Tavolo::setInGioco(unsigned i)
{ 
   giocatori[i].inGioco = true;
   return; 
}

// PRIVATE
void Tavolo::daiCarta(unsigned posto, int resetSeed) // if resetSeed < 0 do not reset
{
   int i = randomInterval(0,mucchio.size() - 1, posto*resetSeed + resetSeed); //posto per il seed, il + è per quando posto = 0
   Carta* cp = mucchio[i];
   bool messaCarta = (giocatori[posto].giocatore)->riceviCarta(cp);
   if (messaCarta)
      mucchio.erase(mucchio.begin() + i);
   else
      cout << "ERRORE: troppe carte" << endl;
   return;
}


/***** GET & PRINT *****/
void Tavolo::stampaMucchio()
{
   for (unsigned i = 0; i < mucchio.size(); i++)
   {
      if (mucchio[i] != NULL)
         cout << i+1 << ") " << *(mucchio[i]) << endl;
      else
         cout << "MANCANTE" << endl;
   }
   return;
}

void Tavolo::stampaPozzo()
{
   for (unsigned i = 0; i < pozzo.size(); i++)
   {
      if (pozzo[i] != NULL)
         cout << i+1 << ") " << *(pozzo[i]) << endl;
      else
          cout << "MANCANTE" << endl;
   }
   return;
}

unsigned Tavolo::getDealer()
{
   return dealer;
}

unsigned Tavolo::numGiocatoriInGioco()
{
   unsigned n = 0;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (giocatori[i].inGioco)
         n++;
   }
   return n;
}

void Tavolo::getPlayerName(unsigned giocatoreIndex)
{
   cout << giocatoreIndex + 1 << ") " << giocatori[giocatoreIndex].giocatore->getName();
}

void Tavolo::getPlayerStatus(unsigned giocatoreIndex)
{
   cout << "Bestia: " << giocatori[giocatoreIndex].inBestia << "; ";
   cout << "In gioco: " << giocatori[giocatoreIndex].inGioco << "; ";
   cout << "Prese: " << giocatori[giocatoreIndex].numPrese;
   return;
   
}

void Tavolo::stampaCarteGiocate(int giocatoreDiMano)
{
   cout << "CARTE GIOCATE:" << endl;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (carteGiocate[i] != NULL)
         if (i == giocatoreDiMano)
            cout << "\t" << i+1 << ") " << *(carteGiocate[i]) << " *" << endl;
         else
            cout << "\t" << i+1 << ") " << *(carteGiocate[i]) << endl;
      else
         cout << "\t" << i+1 << ") VUOTO" << endl;
   }
   return;
}

void Tavolo::stampaBriscola()
{
   if (briscola != NULL)
      cout << "BRISCOLA: " << *briscola << endl;
   else
      cout << "BRISCOLA: VUOTO" << endl;
   return;
}



ostream& operator<<(ostream& os,const Tavolo& t)
{
   // for testing purposes printing player, but it should only print the names
   os << "TAVOLO" << endl;
   os << "Briscola: ";
   if (t.briscola != NULL)
      os << *(t.briscola);
   os << endl;
   os << "Pot: " << t.pot << endl;
   os << "Giocatori: " << endl;
   for (unsigned i = 0; i < t.NUMGIOCATORI; i++)
   {
      os << i+1;
      if (t.dealer == i)
         os << "*";
      os << ") " ;//<< endl;
      if (t.giocatori[i].giocatore != NULL)
         os << *(t.giocatori[i].giocatore) << endl;
      else
         os << "VUOTO" << endl;
   }
   return os;
}
