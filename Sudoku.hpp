#ifndef CubeMan_BreakSudoku_Sudoku
#define CubeMan_BreakSudoku_Sudoku
#include<iostream>
#include<string>
namespace cubeman{
//Sudoku class
class Sudoku{
public:
    char puzzle[9][9];
    std::string const to_str(bool number_only=false);
    bool read(std::istream &in=std::cin);
    void operator=(Sudoku const &);
    Sudoku();
    Sudoku(std::istream &);
    char* operator[](int);
};
}
#endif
