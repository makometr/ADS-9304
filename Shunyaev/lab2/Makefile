
all: lab2 test

lab2: main.o HierarchicalList.o Algorithm.o
	g++ -std=c++17 main.o HierarchicalList.o Algorithm.o -o lab2
	rm -rf *.o

HierarchicalList.o: Source/HierarchicalList.cpp Source/HierarchicalList.h
	g++ -c -std=c++17 Source/HierarchicalList.cpp

main.o: Source/main.cpp Source/Algorithm.h Source/HierarchicalList.h
	g++ -c -std=c++17 Source/main.cpp

Algorithm.o: Source/Algorithm.cpp Source/Algorithm.h Source/HierarchicalList.h
	g++ -c -std=c++17 Source/Algorithm.cpp

test: main1.o Test.o
	g++ -std=c++17 main1.o Test.o -o test
	rm -rf *.o
main1.o: Tests/main1.cpp Tests/Test.h
	g++ -c -std=c++17 Tests/main1.cpp
Test.o: Tests/Test.cpp Tests/Test.h
	g++ -c -std=c++17 Tests/Test.cpp

clear:
	rm -rf *.o lab2 test
	rm -rf ./Source/*.o
	rm -rf ./Tests/*.o

