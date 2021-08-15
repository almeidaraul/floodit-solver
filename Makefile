CFLAGS = -Wall -O3 -std=c++17
TDIR=entradas
TESTE=$(TDIR)/teste.in
TESTE2=$(TDIR)/in1.txt
TESTE3=$(TDIR)/100x100-20c.txt

all: main
main: main.o state.o
	g++ $(CFLAGS) -o aquarela main.cpp state.cpp
exec: main
	time ./aquarela < $(TESTE)
test: main
	time ./aquarela < $(TESTE2)
	./aquarela < $(TESTE2) > entradas/saida.txt
big: main
	time ./aquarela < $(TESTE3)
