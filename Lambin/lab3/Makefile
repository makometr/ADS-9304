all: main.o node.o tree.o
	g++ main.o node.o tree.o -o lab3

main.o: source/main.cpp source/tree.h
	g++ -c source/main.cpp

node.o: source/node.cpp source/node.h
	g++ -c source/node.cpp

tree.o: source/tree.cpp source/tree.h source/node.h
	g++ -c source/tree.cpp

clean:
	rm -rf *.o
