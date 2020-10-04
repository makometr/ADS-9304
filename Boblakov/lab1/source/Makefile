all: main.o recSearch.o
	g++ main.o recSearch.o

main.o: main.cpp recSearch.h
	g++ -c main.cpp

recSearch.o: recSearch.cpp recSearch.h
	g++ -c recSearch.cpp recSearch.h

clean:
	rm *.o
