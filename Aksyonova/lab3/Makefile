all: main.o node.o tree.o
	g++ main.o node.o tree.o -o lab3
main.o: Source/main.cpp Source/tree.h
	g++ -c ./Source/main.cpp
tree.o: Source/tree.cpp Source/tree.h Source/node.h
	g++ -c Source/tree.cpp
node.o: Source/node.cpp Source/node.h
	g++ -c Source/node.cpp
