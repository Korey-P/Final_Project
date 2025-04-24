all: main

main: main.cpp
	g++ -std=c++11 -o main main.cpp

run: main
	./main

clean:
	rm -f main
