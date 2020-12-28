cw: main.o BST.o IBST.o Research.o
	g++ -std=c++17 main.o BST.o Research.o -o cw

main.o: src/main.cpp src/Research.h
	g++ -Wall -std=c++17 -c src/main.cpp

BST.o: src/BST.cpp src/BST.h src/BinTreeNode.h
	g++ -Wall -std=c++17 -c src/BST.cpp

IBST.o: src/IBST.h src/BinTreeNode.h
	g++ -Wall -std=c++17 -c src/IBST.h

Research.o: src/Research.cpp src/BST.h src/IBST.h
	g++ -Wall -std=c++17 -c src/Research.cpp

plot_height_average:
	python3 plot.py results/res_ha.txt

plot_height_worst:
	python3 plot.py results/res_hw.txt

plot_time_average:
	python3 plot.py results/res_ta.txt

plot_time_worst:
	python3 plot.py results/res_tw.txt

clean:
	rm -rf *.o src/*.gch cw results/*.txt