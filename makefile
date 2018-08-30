all: Bestia.o Tavolo.o AIs.o GiocatoreUmano.o Mazzo.o Carta.o random.o random.hpp Carta.hpp Bestia.hpp Tavolo.hpp Giocatore.hpp Mazzo.hpp
	g++ -Wall -o Bestia Bestia.o Tavolo.o Giocatore.o GiocatoreUmano.o AIs.o Mazzo.o Carta.o random.o
Bestia.o: Bestia.cpp Bestia.hpp Tavolo.o AIs.o GiocatoreUmano.o Mazzo.o Carta.o
	g++ -Wall -c Bestia.cpp
Tavolo.o: Tavolo.cpp Tavolo.hpp Giocatore.o Carta.o Mazzo.o random.o
	g++ -Wall -c Tavolo.cpp
Mazzo.o: Mazzo.cpp Mazzo.hpp Carta.o
	g++ -Wall -c Mazzo.cpp
Carta.o: Carta.cpp Carta.hpp
	g++ -Wall -c Carta.cpp
random.o: random.cpp random.hpp
	g++ -Wall -c random.cpp
GiocatoreUmano.o: GiocatoreUmano.cpp GiocatoreUmano.hpp Giocatore.o
	g++ -Wall -c GiocatoreUmano.cpp
AI.o: AI.cpp AI.hpp Giocatore.o
	g++ -Wall -c AI.cpp
Giocatore.o: Giocatore.cpp Giocatore.hpp Carta.o
	g++ -Wall -c Giocatore.cpp
Blind.o: AIs/Blind.cpp AIs/Blind.hpp AI.o
	g++ -Wall -o AIs/Blind.o -c AIs/Blind.cpp
Bruno.o: AIs/Bruno.cpp AIs/Bruno.hpp AI.o
	g++ -Wall -o AIs/Bruno.o -c AIs/Bruno.cpp
Loose.o: AIs/Loose.cpp AIs/Loose.hpp AI.o
	g++ -Wall -o AIs/Loose.o -c AIs/Loose.cpp
Robin.o: AIs/Robin.cpp AIs/Robin.hpp AI.o
	g++ -Wall -o AIs/Robin.o -c AIs/Robin.cpp
Tight.o: AIs/Tight.cpp AIs/Tight.hpp AI.o
	g++ -Wall -o AIs/Tight.o -c AIs/Tight.cpp 
AIs.o: AI.o Blind.o Bruno.o Loose.o Robin.o Tight.o
	ld -r -o AIs.o AI.o AIs/Blind.o AIs/Bruno.o AIs/Loose.o AIs/Robin.o AIs/Tight.o

clean:
	rm *.o AIs/*.o
