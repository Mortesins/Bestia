all: Bestia.o Tavolo.o GiocatoriDerivati.o Giocatore.o Mazzo.o Carta.o random.o random.hpp Carta.hpp Bestia.hpp Tavolo.hpp Giocatore.hpp GiocatoriDerivati.hpp Mazzo.hpp
	g++ -Wall -o Bestia Bestia.o Tavolo.o GiocatoriDerivati.o Giocatore.o Mazzo.o Carta.o random.o
Bestia.o: Bestia.cpp Bestia.hpp Tavolo.o GiocatoriDerivati.o Mazzo.o Carta.o
	g++ -Wall -c Bestia.cpp
Tavolo.o: Tavolo.cpp Tavolo.hpp GiocatoriDerivati.o Carta.o Mazzo.o random.o
	g++ -Wall -c Tavolo.cpp
GiocatoriDerivati.o: GiocatoriDerivati.cpp GiocatoriDerivati.hpp Giocatore.o
	g++ -Wall -c GiocatoriDerivati.cpp
Giocatore.o: Giocatore.cpp Giocatore.hpp Carta.o
	g++ -Wall -c Giocatore.cpp
Mazzo.o: Mazzo.cpp Mazzo.hpp Carta.o
	g++ -Wall -c Mazzo.cpp
Carta.o: Carta.cpp Carta.hpp
	g++ -Wall -c Carta.cpp
random.o: random.cpp random.hpp
	g++ -Wall -c random.cpp

clean:
	rm *.o
