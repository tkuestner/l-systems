CC = g++
CFLAGS = -g -Wall -O3 -std=c++14
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

OBJECTS = main.o rulesystem.o turtle.o window.o

all: l-systems

l-systems: $(OBJECTS)
	g++ -o $@ $^ $(SDL_LDFLAGS) -lSDL2pp

.cpp.o:
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

.PHONE clean:
	rm $(OBJECTS) l-systems

