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
  private:
   const string nome;
   unsigned soldi;
   Carta* carte[3]; //vector <Carta*> carte;
  public:
   Giocatore(string name);
   string getName() const { return nome; };
   unsigned getSoldi() const { return soldi; };
   Carta* getCartaPointer(unsigned i) const { return carte[i]; };
   
   void versaSoldi(unsigned soldi);
   void giocaCarta(unsigned i);
   void scartaTutto();
   void riceviCarta(Carta* cp);
   
   virtual void scegliCartaDaGiocare() { cout << "scegliCartaDaGiocare: virtual. Da fare" << endl; };
   
   
   void stampaCarte() const;
};
#endif
