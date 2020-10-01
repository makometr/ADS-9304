
all: lab1 test

lab1: main.o Source/Recursion.o Source/Data.o
	g++ main.o Source/Recursion.o Source/Data.o -o lab1
	rm -rf *.o
main.o: Source/main.cpp Source/Data.h
	g++ -c Source/main.cpp
Recursion.o: Source/Recursion.cpp Source/Recursion.h
	g++ -c Source/Recursion.cpp
Data.o: Source/Data.cpp Source/Data.h
	g++ -c Source/Data.cpp

test: main1.o Tests/Test.o
	g++ main1.o Tests/Test.o -o test
	rm -rf *.o
main1.o: Tests/main1.cpp Tests/Test.h
	g++ -c Tests/main1.cpp
Test.o: Tests/Test.cpp Tests/Test.h
	g++ -c Tests/Test.cpp

clear:
	rm -rf *.o lab1 test
	rm -rf ./Source/*.o
	rm -rf ./Tests/*.o

