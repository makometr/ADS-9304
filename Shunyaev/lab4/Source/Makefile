
all: lab4

lab4: main.o Data.o HeapSort.o
	g++ -std=c++17 main.o HeapSort.o Data.o -o lab4

HeapSort.o: Source/HeapSort.cpp Source/HeapSort.h Source/Data.h
	g++ -c -std=c++17 Source/HeapSort.cpp

main.o: Source/main.cpp Source/HeapSort.h Source/Data.h
	g++ -c -std=c++17 Source/main.cpp

Data.o: Source/Data.cpp Source/Data.h
	g++ -c -std=c++17 Source/Data.cpp


clear:
	rm -rf *.o lab4
	rm -rf ./Source/*.o

