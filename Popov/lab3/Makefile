CC=g++
CFLAGS=-std=c++17 -Wall
SOURCE=./Source/

all: lab3

lab3: main.o 
	$(CC) $(CFLAGS) $^ -o $@

main.o: $(SOURCE)main.cpp
	$(CC) $(CFLAGS) -c $<