.PHONY: all

all: run_tests

lab2: Source/lab2.cpp
	g++ Source/lab2.cpp -std=c++17 -o lab2

run_tests: lab2
	python3 test.py
