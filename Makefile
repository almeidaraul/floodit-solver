CFLAGS = -Wall -O3

all: main
main: main.o state.o
	g++ main.cpp state.cpp $(CFLAGS)
exec: main
	time ./a.out < teste.in
	time ./a.out < gigante.in
clean:
	@rm -f *.o
