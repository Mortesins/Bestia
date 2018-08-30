#ifndef GIOCATORIDERIVATI_HPP
#define GIOCATORIDERIVATI_HPP

using namespace std;

#include "Giocatore.hpp"
#include "random.hpp"

class GiocatoreUmano: public Giocatore
{
  private:
   const bool assoDiPrima;
   const bool secondaBriscola;
  public:
   GiocatoreUmano(string name, bool assoPrima=true, bool briscolaSeconda=true);
   ~GiocatoreUmano();

/* FOR TESTING */
   bool bussareOno(); // OK
   bool vadoAlBuio(); // OK
/*-------------*/
   bool bussareOno(const Carta* briscola) { return bussareOno(); };
   bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) { return vadoAlBuio(); };
   Carta* giocaCarta(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate, bool ultimo, unsigned posto, bool debug=false); //FATTO MA NON SE SE FUNZIONA
      // debug non serve
   unsigned cartaPiuAlta();

};

class AI: public Giocatore
{
  protected:
   const bool assoDiPrima;
   const bool secondaBriscola;
   // PRIVATE
   int cartaPiuAltaNonBriscola(char briscolaSeme); //la più alta non briscola, -1 se tutto briscola
   int cartaPiuAlta(char s); // -1 se non c'è
   unsigned cartaPiuAlta();
   int cartaPiuBassa(char s);
   unsigned cartaPiuBassa();
   unsigned numCarteSeme(char s); //numero carte di un seme
   unsigned cartaDaButtarVia(); //la più bassa del seme in cui ho più carte
   
   int cercaCarta(char v, char s);
   // PRIVATE

  public:
   AI(string name, bool assoPrima=true, bool briscolaSeconda=true);
   ~AI();
   
   //virtual bool bussareOno(const Carta* briscola) = 0; //=0 for pure
   //virtual bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
   Carta* giocaCarta(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate, bool ultimo, unsigned posto, bool debug); 
   
   char palo(unsigned diMano, const vector <Carta*> carteGiocate); //non controlla che sia stata giocata la carta del giocatore di mano
   char valoreVincente(unsigned diMano, const Carta* briscola, const vector <Carta*> carteGiocate);
   bool briscolaGiocata(const Carta* briscola, const vector <Carta*> carteGiocate);

/*** SPOSTATO IN CARTA
   static bool aMINOREb(char a, char b);
   static bool aMAGGIOREb(char a, char b);
   
   static unsigned ilTerzoNumero(unsigned a, unsigned b); 
   * **/
};

class Bruno: public AI
{
   public:
      Bruno(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Bruno();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
};

class Tight: public AI
{
   public:
      Tight(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Tight();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
};

class Blind: public AI
{
   public:
      Blind(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Blind();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto);
};

class Loose: public AI
{
   public:
      Loose(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Loose();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) ;
};

class Robin: public AI
{
   public:
      Robin(string name, bool assoPrima=true, bool briscolaSeconda=true);
      ~Robin();
   
      bool bussareOno(const Carta* briscola);
      bool vadoAlBuio(unsigned pot, bool nessunoAndato, bool ultimo, unsigned posto) ;
};

#endif
