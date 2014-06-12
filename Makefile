CC=clang++
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

all:main

clean:
	rm -f *.o
