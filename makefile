all: demo

demo: demo.cpp sudoku_simple_solver.o sudoku_complex_solver.o Sudoku.o
	g++ -O3 -std=c++14 demo.cpp sudoku_simple_solver.o sudoku_complex_solver.o Sudoku.o -o demo

Sudoku.o: Sudoku.cpp Sudoku.hpp
	g++ -O3 -std=c++14 -c Sudoku.cpp

sudoku_complex_solver.o: sudoku_complex_solver.cpp sudoku_complex_solver.hpp
	g++ -O3 -std=c++14 -c sudoku_complex_solver.cpp

sudoku_simple_solver.o: sudoku_simple_solver.cpp sudoku_simple_solver.hpp
	g++ -O3 -std=c++14 -c sudoku_simple_solver.cpp
