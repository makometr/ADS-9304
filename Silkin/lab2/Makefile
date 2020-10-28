all: lab2

lab2: main.o list.o
	g++ -std=c++17 main.o list.o -o list

main.o: ./Source/main.cpp
	g++ -std=c++17 ./Source/main.cpp -c

list.o: ./Source/list.cpp ./Source/list.h
	g++ -std=c++17 ./Source/list.cpp -c

testing: lab2
	./test_script