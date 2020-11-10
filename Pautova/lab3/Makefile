lab3: main.o BinTree.o
	g++ -std=c++17 main.o BinTree.o -o lab3

main.o: source/main.cpp source/BinTree.h
	g++ -Wall -std=c++17 -c source/main.cpp

BinTree.o: source/BinTree.cpp source/BinTree.h source/BinTreeNode.h
	g++ -Wall -std=c++17 -c source/BinTree.cpp

run_tests:
	./myscript

clean:
	rm -rf *.o