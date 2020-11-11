
all: lab3 test

lab3: main.o TreeElement.o InputData.o
	g++ -std=c++17 main.o TreeElement.o InputData.o -o lab3
	rm -rf *.o

TreeElement.o: Source/TreeElement.cpp Source/TreeElement.h
	g++ -c -std=c++17 Source/TreeElement.cpp

main.o: Source/main.cpp Source/TreeElement.h Source/InputData.h
	g++ -c -std=c++17 Source/main.cpp

InputData.o: Source/InputData.cpp Source/InputData.h
	g++ -c -std=c++17 Source/InputData.cpp

test: main1.o Test.o
	g++ -std=c++17 main1.o Test.o -o test
	rm -rf *.o
main1.o: Tests/main1.cpp Tests/Test.h
	g++ -c -std=c++17 Tests/main1.cpp
Test.o: Tests/Test.cpp Tests/Test.h
	g++ -c -std=c++17 Tests/Test.cpp

clear:
	rm -rf *.o lab3 test
	rm -rf ./Source/*.o
	rm -rf ./Tests/*.o

