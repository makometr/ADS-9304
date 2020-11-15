LAB = lab4

.PHONY: all clean

all: run_tests

$(LAB): Source/$(LAB).cpp
	g++ $< -g -std=c++17 -o $@

check: Source/check_sort.cpp
	g++ $< -g -std=c++17 -o $@

run_tests: $(LAB) check
	python3 test.py

clean:
	rm -rf $(LAB) check
