CC = g++
CCFLAGS = -std=c++17 -Wall
DIR = ./Source/
TARGET = main.o

.PHONY: all clean

all: lab5

lab5: $(TARGET)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: $(DIR)%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm *.o lab* 