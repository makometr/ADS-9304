
all: lab

lab: main.o
	g++ main.o -std=c++17 -o lab

main.o: Source/main.cpp Source/BinTree.h Source/Node.h
	g++ -c Source/main.cpp -std=c++17

clean:
	rm -rf *.o lab

run_tests:
	python test.py
