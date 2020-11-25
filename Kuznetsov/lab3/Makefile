test: resgen compile Source/test.py
	python Source/test.py
	for i in 1 2 3 4 5 6 7 8 9 10; do \
	if [ -f Tests/testres$$i.txt ]; then rm Tests/testres$$i.txt; fi; \
	done

resgen: compile
	for i in 1 2 3 4 5 6 7 8 9 10 ; do \
	./main.exe < Tests/test$$i.txt > Tests/testres$$i.txt ; \
	done

compile: Source/main.cpp
	g++ Source/main.cpp -o main

clean: 
	if [ -f main ]; then rm main; fi ; \
	for i in 1 2 3 4 5 6 7 8 9 10; do \
	if [ -f Tests/testres$$i.txt ]; then rm Tests/testres$$i.txt; fi; \
	done
