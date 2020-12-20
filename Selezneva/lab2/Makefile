CC = g++
CFLAG = -std=c++17 -Wall

all: lab2

lab2: Lb2.o List_Hier.o
	$(CC) $(CFLAG) $^ -o $@
	rm *.o

Lb2.o: source/Lb2.cpp source/List_Hier.h
	$(CC) $(CFLAG) -c $< 

List_Hier.o: source/List_Hier.cpp source/List_Hier.h 
	$(CC) $(CFLAG) -c $<

clean:
	rm *.o
