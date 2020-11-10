CC=g++
CCFLAGS=-std=c++17
DIRECT=./Source/
TARGET=main.o

all: lab3

lab3: $(TARGET)
	$(CC) $(CCFLAGS) $^ -o $@

main.o: $(DIRECT)main.cpp $(DIRECT)Tree.h $(DIRECT)Node.h
	$(CC) $(CCFLAGS) -c $<

clean:
	rm *.o
