all: lab5

lab5: ./src/main.o ./src/hesh.o
	g++ src/main.o src/hesh.o -o lab5
	rm -rf *.o
main.o: ./src/main.cpp ./src/hesh.h
	g++ -std=c++17 ./src/main.cpp
hesh.o: ./src/hesh.cpp ./src/hesh.h
	g++ -std=c++17 ./src/hesh.cpp

clear:
	rm -rf *.o lab5
	rm -rf ./src/*.o
