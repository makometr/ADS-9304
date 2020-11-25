
all: lab

lab: main.o
	g++ main.o -o lab

main.o: Source/main.cpp
	g++ Source/main.cpp -c
	
clean:
	rm -rf *.o lab

run_tests: lab
	python test.py
