.PHONY: test clean worst average best

compile:
	@echo "Compiling program..."
	@g++ Source/main.cpp -D _DEBUG -o main
	@echo "Compiled successfully"
	
test:
	@echo "Compiling test version of the program..."
	@g++ Source/main.cpp -D TEST -o test
	@echo "Compiled successfully"; echo ''
	@for file in ./Tests/*; do \
	echo Test $${file}; \
	cp $${file} curTest.txt; \
	./test < curTest.txt && \
	cat res.txt curTest.txt > forCheck.txt; \
	python3.8 Source/test.py < forCheck.txt; \
	done
	@rm forCheck.txt res.txt curTest.txt test 

graph:
	@echo "Compiling insert testing version of the program..."
	@g++ Source/main.cpp -D GRAPH -o graph
	
worst: graph
	@echo "Counting operations"
	@./graph worst
	@echo "Drawing worst case graph"
	@python Source/main.py insertWorst.txt
	
average: graph
	@echo "Counting operations"
	@./graph average
	@echo "Drawing average case graph"
	@python Source/main.py insertAverage.txt
	
best: graph
	@echo "Counting operations"
	@./graph best
	@echo "Drawing best case graph"
	@python Source/main.py insertBest.txt

clean:
	@rm main test graph res insertAverage.txt insertBest.txt insertWorst.txt 2> /dev/null