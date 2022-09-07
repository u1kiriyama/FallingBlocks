FallingBlocks.out: main.o board.o parts.o common.hpp
	g++ -std=c++20 -Wall main.o board.o parts.o -o FallingBlocks.out
main.o: main.cpp
	g++ -std=c++20 -c -Wall main.cpp -o main.o
board.o: board.cpp board.hpp
	g++ -std=c++20 -c -Wall board.cpp -o board.o
parts.o: parts.cpp parts.hpp
	g++ -std=c++20 -c -Wall parts.cpp -o parts.o