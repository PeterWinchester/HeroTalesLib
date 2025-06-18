lib/libherotales.a : src/htsys.o src/htframe.o src/htcards_basic.o src/htplayer.o src/htgame.o src/htcards_init.o *.o
	ar crv lib/libherotales.a src/htsys.o src/htframe.o src/htcards_basic.o src/htplayer.o src/htgame.o src/htcards_init.o *.o

src/htcards_init.o : src/htcards_init.cpp
	g++ -c src/htcards_init.cpp -I include -o src/htcards_init.o

src/htgame.o : src/htgame.cpp
	g++ -c src/htgame.cpp -I include -o src/htgame.o

*.o : src/cards/*.cpp
	g++ -c src/cards/*.cpp -I include

src/htplayer.o : src/htplayer.cpp
	g++ -c src/htplayer.cpp -I include -o src/htplayer.o

src/htcards_basic.o : src/htcards_basic.cpp
	g++ -c src/htcards_basic.cpp -I include -o src/htcards_basic.o

src/htframe.o : src/htframe.cpp
	g++ -c src/htframe.cpp -I include -o src/htframe.o

src/htsys.o : src/htsys.cpp
	g++ -c src/htsys.cpp -I include -o src/htsys.o

clean :
	rm -f src/*.o *.o
