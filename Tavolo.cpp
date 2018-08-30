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
		cout << giocatori[i].giocatore->getType() << endl;
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
      pot += DEALERMONEY;
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
   for (int i = 0; i < 3; i++) 
   {
      daiCarta(giocatoreIndex);
   }
   return;
}

void Tavolo::setBriscola()
{
   Carta* cp = mucchio.back();
   if (briscola == NULL)
   {
      briscola = cp;
      mucchio.pop_back();
   }
   else
   {
      cout << "ERRORE: c'è già una briscola" << endl;
   }
   return;
}

int Tavolo::chiGioca(bool debug, int chiComincia)
{
   unsigned index;
   vector <unsigned> indicesPlayersAnswered;
   int primo = -1;
   if ( (chiComincia < 0) && (chiComincia >= NUMGIOCATORI) )
      index = next(dealer);
   else
      index = chiComincia;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (giocatori[index].giocatore->getType() == "umano")
      {
         for (unsigned j = 0; j < indicesPlayersAnswered.size(); j++)
         {
            printPlayerInPlay(indicesPlayersAnswered[j]);
         }
         // giocatori che non hanno ancora risposto
         unsigned tmpIndex;
         if (indicesPlayersAnswered.size() > 0) // qualcuno ha risposto
         {
            tmpIndex = indicesPlayersAnswered[indicesPlayersAnswered.size()-1];
            tmpIndex = next(tmpIndex);
         }
         else // nessuno ha rispoto, quindi comincio con l'index normale
         {
            tmpIndex = index;
         }
         for (unsigned j = 0; j < NUMGIOCATORI - indicesPlayersAnswered.size(); j++)
         {
            printPlayerName(tmpIndex);
            cout << ": ???" << endl;
            tmpIndex = next(tmpIndex);
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
      // add index to indices of players that have answered
      indicesPlayersAnswered.push_back(index);
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
   if (giocatori[giocatoreIndex].giocatore->getType() == "umano")
   {
      stampaCarteGiocate(diMano);
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
         }
      }
   }
}

void Tavolo::resetPlayersStatus()
{
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      giocatori[i].numPrese = 0; //RESET
      giocatori[i].inGioco = 0; //RESET
   }
}

void Tavolo::resetBriscola()
{
   briscola = NULL;
   return;
}

/*** PRIVATE ***/
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

void Tavolo::setNumPrese(unsigned i, unsigned prese) 
{ 
   giocatori[i].numPrese = prese; 
   return; 
} 

void Tavolo::setInGioco(unsigned i)
{ 
   giocatori[i].inGioco = true;
   return; 
}

void Tavolo::daiCarta(unsigned posto)
{
   Carta* cp = mucchio.back();
   bool messaCarta = (giocatori[posto].giocatore)->riceviCarta(cp);
   if (messaCarta)
      mucchio.pop_back();
   else
      cout << "ERRORE: troppe carte" << endl;
   return;
}
/***************/


/***** GET & PRINT *****/
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

void Tavolo::printPlayerName(unsigned giocatoreIndex)
{
   cout << giocatoreIndex + 1 << ") " << giocatori[giocatoreIndex].giocatore->getName();
}

void Tavolo::printPlayerStatus(unsigned giocatoreIndex)
{
   cout << "Bestia: " << giocatori[giocatoreIndex].inBestia << "; ";
   cout << "In gioco: " << giocatori[giocatoreIndex].inGioco << "; ";
   cout << "Prese: " << giocatori[giocatoreIndex].numPrese;
   return;
}

void Tavolo::printPlayerInPlay(unsigned giocatoreIndex)
{
   printPlayerName(giocatoreIndex);
   cout << ": ";
   if (giocatori[giocatoreIndex].inGioco)
   {
      cout << "gioca" << endl;
   }
   else
   {
      cout << "non gioca" << endl;
   }
}

void Tavolo::printPlayersInPlay()
{
   // print players in play
   cout << "CHI GIOCA: " << endl;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      printPlayerInPlay(i);
   }
}

void Tavolo::printPresePlayersInPlay(unsigned index)
{
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (giocatori[index].inGioco)
      {
         printPlayerName(index);
         cout << ": Prese: " << giocatori[index].numPrese << endl;
      }
      index = next(index);
   }  
}

void Tavolo::printPlayersInPlayPreseBestia()
{
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (giocatori[i].inGioco)
      {
         printPlayerName(i);
         cout << ": Prese: " << giocatori[i].numPrese;
         cout << "; Bestia: " << giocatori[i].inBestia << endl;
      }
   }  
}

void Tavolo::stampaCarteGiocate()
{
   cout << "CARTE GIOCATE:" << endl;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (carteGiocate[i] != NULL)
         cout << "\t" << i+1 << ") " << *(carteGiocate[i]) << endl;
      else
         cout << "\t" << i+1 << ") VUOTO" << endl;
   }
   return;
}

void Tavolo::stampaCarteGiocate(int index)
{
   cout << "CARTE GIOCATE:" << endl;
   for (unsigned i = 0; i < NUMGIOCATORI; i++)
   {
      if (giocatori[index].inGioco)
      {
         if (carteGiocate[index] != NULL)
            cout << "\t" << index+1 << ") " << *(carteGiocate[index]) << endl;
         else
            cout << "\t" << index+1 << ") VUOTO" << endl;
      }
      index = next(index);
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

/*** for testing ***/
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
/*******************/

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
