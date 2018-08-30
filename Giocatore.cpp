#include "Giocatore.hpp"

Giocatore::Giocatore(string name)
   :nome(name)
{
   soldi = 0;
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

Giocatore::~Giocatore()
{
   // non elimino le carte perchè devono rimanere nel mazzo
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
}

void Giocatore::stampaCarte() const
{
   if (carte[0] != NULL)
      cout << *(carte[0]) << " ; ";
   else
      cout << "VUOTO ; ";
   if (carte[1] != NULL)
      cout << *(carte[1]) << " ; ";
   else
      cout << "VUOTO ; ";
   if (carte[2] != NULL)   
      cout << *(carte[2]) << endl;
   else
      cout << "VUOTO" << endl;
   return;
}

void Giocatore::versaSoldi(unsigned s)
{
   soldi -= s;
   //versare a chi?
   return;
}

void Giocatore::riceviSoldi(unsigned s)
{
   soldi += s;
   return;
}
   
//Carta* Giocatore::giocaCarta(unsigned i)
//{
//   //giocarla
//   Carta* c = carte[i];
//   carte[i] = NULL;
 //  return c;
//}

//Carta* Giocatore::giocaCarta(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate, bool ultimo, unsigned posto) //CATCH NON NUMBERS
//{ 
   //cout << nome << ": Quale carta giocare? Di Mano: "<< diMano << " Briscola: " << *briscola << endl;
   //for (unsigned i = 0; i < 3; i++)
   //{
      //if (carte[i] != NULL)
      //{
         //cout << i << ") " << *(carte[i]) << endl;
      //}
   //}
   //unsigned a;
   //cin >> a;
      ///* FOR TESTING
      //if (a == 11)
         //throw "I QUIT";
      //*/
   //if ( a == 0 || a == 1 || a == 2)
   //{
      //Carta* c = carte[a];
      //carte[a] = NULL;
      //return c;
   //}
   //else
      //return NULL;
//}


void Giocatore::scartaTutto()
{
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
   return;
}
   
bool Giocatore::riceviCarta(Carta* cp) //buon fine
{
   unsigned i = 0; 
   bool messa = false;
   while (i < 3 && !messa)
   {
      if (carte[i] == NULL)
      {
         carte[i] = cp;
         messa = true;
      }
      i++;
   }
   return messa;
}

//bool Giocatore::bussareOno() 
//{
   //char a;
   //cout << nome << ": bussare? (y/n) " << endl;
   //cin >> a; 
   //return ( (a == 'y') || (a == 'Y') ); 
//}
   
//bool Giocatore::vadoAlBuio() 
//{
   //char a;
   //cout << nome << ": Andare al buio? (y/n) " << endl;
   //cin >> a; 
   //return ( (a == 'y') || (a == 'Y') ); 
//}

ostream& operator<<(ostream& os, const Giocatore& g)
{
   os << "Nome: " << g.nome << endl;
   os << "Soldi: " << g.soldi << endl;
   if (g.type == "umano")
   {
	   os << "Carte: " << endl;
	   for (unsigned i = 0; i < 3; i++)
	   {
		  if (g.carte[i] != NULL)
			 os << "\t" << i << ") " << *(g.carte[i]) << endl;
		  else
			 os << "\t" << i << ") VUOTO" << endl;
	   }
   }
   return os;   
}
