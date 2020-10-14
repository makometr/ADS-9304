lab2: main.o h_list.o
	g++ -std=c++17 main.o h_list.o -o lab2

main.o: source/main.cpp source/H_List.h
	g++ -Wall -std=c++17 -c source/main.cpp

h_list.o: source/H_List.cpp source/H_List.h source/Node.h
	g++ -Wall -std=c++17 -c source/H_List.cpp

run_tests:
	./myscript

clean:
	rm -rf *.o