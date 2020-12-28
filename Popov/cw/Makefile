OBJ = main.o
CC = g++
CFLAG = -std=c++17 -Wall
DIR = ./Source/

cw: $(DIR)main.cpp $(DIR)Smootshort.cpp $(DIR)Node.cpp
	$(CC) $(CFLAG) $^ -o $@

.PHONY: clean

clean:
	rm cw timeSmootshort.txt timeRadix.txt