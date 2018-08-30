#include "Bestia.hpp"

Bestia::Bestia(bool d, bool assoPrima, bool briscolaSeconda, unsigned n, unsigned a)
   :assoDiPrima(assoPrima),secondaBriscola(briscolaSeconda),numGiocatori(n),ante(a),tavolo(n,a),debug(d)
{
   Giocatore* g = new GiocatoreUmano("Axel",assoDiPrima,secondaBriscola);
   tavolo.posizionaGiocatore(g,0);
   unsigned randomNumber = randomInterval(1,5);
   unsigned tmp = randomNumber;
   for (unsigned i = 1; i < 4; i++)
   {
      randomNumber = randomInterval(1,5,tmp*i);
      tmp = randomNumber;
      switch (randomNumber)
      {
	 case 1:
		 tavolo.posizionaGiocatore(new Bruno("Tizio"+to_string(i),assoDiPrima,secondaBriscola),i);
		 break;
	 case 2:
		 tavolo.posizionaGiocatore(new Blind("Tizio"+to_string(i),assoDiPrima,secondaBriscola),i);
		 break;
	 case 3:
		 tavolo.posizionaGiocatore(new Loose("Tizio"+to_string(i),assoDiPrima,secondaBriscola),i);
		 break;
	 case 4:
		 tavolo.posizionaGiocatore(new Robin("Tizio"+to_string(i),assoDiPrima,secondaBriscola),i);
		 break;
	 default:
		 tavolo.posizionaGiocatore(new Tight("Tizio"+to_string(i),assoDiPrima,secondaBriscola),i);
		 break;
      }
   }
   tavolo.daiSoldiGiocatore(0,150);
   tavolo.daiSoldiGiocatore(1,150);
   tavolo.daiSoldiGiocatore(2,150);
   tavolo.daiSoldiGiocatore(3,150);
}

void Bestia::run()
{
	if (debug)
		tavolo.printPlayersType();
   //selezionare Dealer
   //while
      //Dealer++
      //metterSoldi
      //distribuisciCarte
      //bussare 
      //andare al buio
      //for 3 giri
         //giro
      //dividere soldi
   int diMano = -1; // quello dopo il dealer
   unsigned diManoOld;
   while (true)
   {
      tavolo.resetMucchio();
      tavolo.setDealer(); //random se non c'è già, oppure dealer++
      // METTI SOLDI
      tavolo.mettiSoldiDealer();
      tavolo.mettiBestiaSoldi();
      //
      // DISTRIBUISCI CARTE
      // reset player status and briscola
      tavolo.resetPlayersStatus();
      tavolo.resetBriscola();
      for (unsigned i = 0; i < numGiocatori; i++)
         tavolo.distribuisciCarte(i);
      tavolo.setBriscola();
      // 
      cout << tavolo;
      // BUSSARE
      cout << "BUSSARE: " << endl;
      diMano = tavolo.chiGioca(debug);
      tavolo.printPlayersInPlay();
      //
      if (diMano != -1) // se diMano == -1 nessuno gioca
      {
         //ANDARE AL BUIO
         tavolo.chiVaAlBuio(diMano);
	 tavolo.printPlayersInPlay();
         // se un solo giocatore finisce lì
         if (tavolo.numGiocatoriInGioco() == 1)
         {
	    cout << "giocatori in gioco: " << tavolo.numGiocatoriInGioco() << endl;
	    tavolo.vincitoreIncontrastato();
	 }
	 else
	 {
	    // GIOCARE
	    for (unsigned i = 0; i < 3; i++) // 3 giri
	    {
	       //tavolo.stampaBriscola();
	       ///cout << "tavolo.giro(diMano);" << endl;
	       tavolo.giro(debug,diMano);

	       ///cout << "tavolo.stampaCarteGiocate;" << endl;
	       tavolo.stampaCarteGiocate(diMano);

	       ///cout << "tavolo.stampaPozzo;" << endl;
	       //tavolo.stampaPozzo();

	       ///cout << "tavolo.chiudiGiro;" << endl;
	       diManoOld = diMano;
	       diMano = tavolo.chiudiGiro(diMano);

	       // stampare prese
	       tavolo.printPresePlayersInPlay(diManoOld);
	       // fine stampare
	    }
	 }
         //
         // DIVIDERE SOLDI
         tavolo.dividereSoldiEBestia();
         //
	 cout << "*** RESULTS ***" << endl;
	 tavolo.printPlayersInPlayPreseBestia();
      }
      else
      {
	 // nessuno gioca
	 //togliere briscola
	 tavolo.resetBriscola();
      }
      cout << "***************************************************************" << endl;
   }
   return;
}

int main()
{
   Bestia bestia(false,true,true,4,15);
   try
   {
      bestia.run();
   }
   catch (string s)
   {
      cout << "Il giocatore: " << s << " ha finito i soldi" << endl;
      cout << "GAME OVER" << endl;
      return 0;
   }
   return 0;
}
