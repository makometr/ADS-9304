CC = g++
CFLAGS = -std=c++17 -Wall
DIR = ./Source/

all: lab2

lab2: main.o List.o Node.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: $(DIR)main.cpp $(DIR)Node.h $(DIR)List.h
	$(CC) $(CFLAGS) -c $<

Node.o: $(DIR)Node.cpp $(DIR)Node.h
	$(CC) $(CFLAGS) -c $<

List.o: $(DIR)List.cpp $(DIR)List.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o