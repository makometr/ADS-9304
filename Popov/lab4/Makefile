OBJ = main.o
CC = g++
CFLAG = -std=c++17 -Wall
DIR = ./Source/

lab4: $(OBJ)
	$(CC) $(CFLAG) $^ -o $@

%.o: $(DIR)%.cpp
	$(CC) $(CFLAG) -c $<

.PHONY: clean
	rm *.o lab4
