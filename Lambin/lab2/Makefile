all: main.o node.o list.o
	g++ -std=c++17 main.o node.o list.o -o lab2

main.o: source/main.cpp source/list.h
	g++ -std=c++17 -c source/main.cpp

node.o: source/node.cpp source/node.h
	g++ -std=c++17 -c source/node.cpp

list.o: source/list.cpp source/list.h source/node.h
	g++ -std=c++17 -c source/list.cpp

clean:
	rm -rf *.o
