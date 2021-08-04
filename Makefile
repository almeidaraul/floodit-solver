CC = g++
CFLAGS = -Wall
OBJ = main.o state.o
DEPS = state.hpp
all: main

%.o: %.c $(DEPS) 
	$(CC) $(CFLAGS) -c -o $@ $<    

main: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

exec: main
	./a.out < teste.in

clean:
	@rm -f *.o 

purge: clean
	@rm main
