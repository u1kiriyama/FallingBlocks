tetris.out: tetris.o board.o parts.o common.hpp
	g++ -std=c++20 -Wall tetris.o board.o parts.o -o tetris.out
tetris.o: tetris.cpp
	g++ -std=c++20 -c -Wall tetris.cpp -o tetris.o
board.o: board.cpp board.hpp
	g++ -std=c++20 -c -Wall board.cpp -o board.o
parts.o: parts.cpp parts.hpp
	g++ -std=c++20 -c -Wall parts.cpp -o parts.o