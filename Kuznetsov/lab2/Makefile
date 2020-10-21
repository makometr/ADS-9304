test: resgen compile Source/tests.py
	cp Source/tests.py ./tests.py
	python Source/tests.py

resgen: compile
	for i in 1 2 3 4 5 6 7 8 9 10 ; do \
	./main.exe < Tests/test$$i.txt > Tests/testres$$i.txt ; \
	done 


compile: Source/main.cpp
	g++ Source/main.cpp -o main -std=c++17

clean: 
	rm main tests.py
	for i in 1 2 3 4 5 6 7 8 9 10; do \
	rm Tests/testres$$i.txt ; \
	done



