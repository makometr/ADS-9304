CC = g++
CFLAGS = -std=c++17 -Wall
DIR = ./Source/

all: lab4

lab4: main.o customQsort.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: $(DIR)main.cpp $(DIR)customQsort.h
	$(CC) $(CFLAGS) -c $<

customQsort.o: $(DIR)customQsort.cpp $(DIR)customQsort.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
	rm *.o lab4
