CC=clang++
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: bin/tetris

bin/tetris: main.o blocks.o
	clang++ $(LDLIBS) main.o blocks.o -o bin/tetris

main.o: main.cpp blocks.hpp
	clang++ -c main.cpp

blocks.o: blocks.cpp blocks.hpp
	clang++ -c blocks.cpp

clean:
	rm -f *.o
