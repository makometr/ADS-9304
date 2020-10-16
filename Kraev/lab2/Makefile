
all: lab

lab: Source/main.o Source/Node.o Source/List.o
	g++ Source/main.o Source/Node.o Source/List.o -std=c++17 -o lab

Source/main.o: Source/main.cpp
	g++ Source/main.cpp -c -std=c++17

Source/Node.o: Source/Node.cpp
	g++ Source/Node.cpp -c -std=c++17

Source/List.o: Source/List.cpp
	g++ Source/List.cpp -c -std=c++17

run_tests:
	python test.py

clean:
	rm -rf *.o lab
