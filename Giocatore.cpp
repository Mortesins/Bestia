#include "Giocatore.hpp"

Giocatore::Giocatore(string name)
   :nome(name)
{
   soldi = 0;
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
   
void Giocatore::giocaCarta(unsigned i)
{
   //giocarla
   carte[i] = NULL;
   return;
}

void Giocatore::scartaTutto()
{
   carte[0] = NULL;
   carte[1] = NULL;
   carte[2] = NULL;
   return;
}
   
void Giocatore::riceviCarta(Carta* cp)
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
   return;
}

ostream& operator<<(ostream& os, const Giocatore& g)
{
   os << "Nome: " << g.nome << endl;
   os << "Soldi: " << g.soldi << endl;
   os << "Carte: " << endl;
   for (unsigned i = 0; i < 3; i++)
   {
      if (g.carte[i] != NULL)
         os << "\t" << i << ") " << *(g.carte[i]) << endl;
      else
         os << "\t" << i << ") VUOTO" << endl;
   }
   return os;   
}
