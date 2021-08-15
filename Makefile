CFLAGS = -std=c++17 -Wall -O3 
TDIR=entradas
TESTE=$(TDIR)/teste.in
TESTE2=$(TDIR)/in1.txt
TESTE3=$(TDIR)/100x100-20c.txt

all: main
main: main.o state.o
	g++ $(CFLAGS) -o aquarela main.cpp state.cpp
exec: main
	time ./aquarela < $(TESTE)
	time ./aquarela < $(TESTE2)
	time ./aquarela < $(TESTE3)
pequeno: main
	python3 gen.py pequeno > temp.txt
	time ./aquarela area < temp.txt
	time ./aquarela perimeter < temp.txt
	time ./aquarela switch < temp.txt
	time ./aquarela half < temp.txt
	time ./aquarela most < temp.txt
	time ./aquarela random < temp.txt
medio: main
	python3 gen.py medio > temp.txt
	time ./aquarela area < temp.txt
	time ./aquarela perimeter < temp.txt
	time ./aquarela switch < temp.txt
	time ./aquarela half < temp.txt
	time ./aquarela most < temp.txt
	time ./aquarela random < temp.txt
grande: main
	python3 gen.py grande > temp.txt
	time ./aquarela area < temp.txt
	time ./aquarela perimeter < temp.txt
	time ./aquarela switch < temp.txt
	time ./aquarela half < temp.txt
	time ./aquarela most < temp.txt
	time ./aquarela random < temp.txt
test: main
	time ./aquarela < $(TESTE2)
	./aquarela < $(TESTE2) > entradas/saida.txt
big: main
	time ./aquarela < $(TESTE3)
