all: bubbleSort

bubbleSort: bubbleSort.o
	g++ -Wall bubbleSort.o -o bubbleSort -lSDL2

bubbleSort.o:
	g++ -c bubbleSort.cpp

clean:
	rm *.o bubbleSort
