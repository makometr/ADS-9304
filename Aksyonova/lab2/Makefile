all: lab2.o node.o list.o
	g++ -std=c++17 lab2.o node.o list.o -o lab2
 
lab2.o: Source/lab2.cpp Source/list.h
	g++ -std=c++17 -c Source/lab2.cpp
 
node.o: Source/node.cpp Source/node.h
	g++ -std=c++17 -c Source/node.cpp
 
list.o: Source/list.cpp Source/list.h Source/node.h
	g++ -std=c++17 -c Source/list.cpp
 
clean:
	rm -rf *.o
run_tests: lab2
	./tests_script
