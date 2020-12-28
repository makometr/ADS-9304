CC = g++
CCFLAGS = -std=c++2a -Wall
DIR = ./Source/

.PHONY: all clean

all: cw

cw: $(DIR)main.cpp $(DIR)WeakHeap.cpp $(DIR)customQsort.cpp
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm *.o lab* 