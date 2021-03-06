#ifndef GIOCATORE_HPP
#define GIOCATORE_HPP

using namespace std;

#include "Carta.hpp"

#include <string>
#include <vector> //controlla se serve
#include <iostream>

class Giocatore
{
   friend ostream& operator<<(ostream& os,const Giocatore& g);
  protected:
   const string nome;
   const string type;
   unsigned soldi;
   Carta* carte[3];
  public:
   Giocatore(string name);
   Giocatore(string name, string type);
   virtual ~Giocatore();
      
   string getName() const { return nome; };
   string getType() const { return type; };
   int getSoldi() const { return soldi; };
   Carta* getCartaPointer(unsigned i) const { return carte[i]; };
   
   void versaSoldi(unsigned soldi);
   void riceviSoldi(unsigned soldi);
   Carta* giocaCarta(unsigned i); // for testing
   void scartaTutto();
   bool riceviCarta(Carta* cp);
   
   virtual bool bussareOno(const Carta* briscola) = 0; // = 0 for pure
   virtual bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) = 0; // = 0 for pure
   virtual Carta* giocaCarta(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate, bool ultimo, unsigned posto, bool debug) = 0; // = 0 for pure // OK
   
   void stampaCarte() const;
};
#endif
