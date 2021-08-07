CC = g++
CFLAGS = -Wall -O3
OBJ = main.o state.o
DEPS = state.hpp
all: main

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

exec: main
	./main < teste.in

fabiano: main
	time ./main < entradas/in1.txt
	./main < entradas/in1.txt > entradas/saida.txt

clean:
	@rm -f *.o

purge: clean
	@rm main
