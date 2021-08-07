CC = g++
CFLAGS = -Wall -O2
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
	time ./main < fabiano/in1.txt
	./main < fabiano/in1.txt > saida.txt

clean:
	@rm -f *.o

purge: clean
	@rm main
