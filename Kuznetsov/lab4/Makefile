.PHONY: test clean

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
	./test < curTest.txt > res.txt; \
	cat res.txt curTest.txt > forCheck.txt; \
	python3.8 Source/test.py < forCheck.txt; \
	done
	@rm forCheck.txt res.txt curTest.txt test 

clean:
	@rm main
