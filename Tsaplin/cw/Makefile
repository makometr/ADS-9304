cw: cw.o
	g++ cw.o -o cw -lsfml-graphics -lsfml-window -lsfml-system
cw.o: Source/cw.cpp
	g++ -c -std=c++17 Source/cw.cpp -o cw.o
run_tests: cw
	./tests_script

