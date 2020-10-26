CC=g++
CFLAGS=-std=c++17 -Wall
DIRECT=./Source/

all: lab2

lab2: main.o List.o Node.o
	$(CC) $^ -o $@
	rm *.o

main.o: $(DIRECT)main.cpp $(DIRECT)List.h $(DIRECT)Node.h
	$(CC) -c $(CFLAGS) $<

List.o: $(DIRECT)List.cpp $(DIRECT)List.h $(DIRECT)Node.h
	$(CC) -c $(CFLAGS) $<

Node.o: $(DIRECT)Node.cpp $(DIRECT)Node.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm *.o