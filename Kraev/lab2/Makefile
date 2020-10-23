
all: lab

lab: main.o Node.o List.o
	g++ main.o Node.o List.o -std=c++17 -o lab

main.o: Source/main.cpp
	g++ Source/main.cpp -c -std=c++17

Node.o: Source/Node.cpp
	g++ Source/Node.cpp -c -std=c++17

List.o: Source/List.cpp
	g++ Source/List.cpp -c -std=c++17

run_tests:
	python test.py

clean:
	rm -rf *.o lab
