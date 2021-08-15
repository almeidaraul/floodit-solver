CFLAGS = -std=gnu++17 -Wall -O3 

all: main

main:
	g++ $(CFLAGS) -o aquarela main.cpp state.cpp
