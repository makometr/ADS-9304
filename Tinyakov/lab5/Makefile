LAB = lab5

.PHONY: all clean

all: run_tests

$(LAB): Source/$(LAB).cpp
	g++ $< -g -std=c++17 -o $@

run_tests: $(LAB)
	python3 test.py

clean:
	rm -rf $(LAB)
