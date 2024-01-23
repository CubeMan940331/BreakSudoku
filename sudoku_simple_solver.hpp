#ifndef CubeMan_sudoku_simple_solver
#define CubeMan_sudoku_simple_solver
#include "Sudoku.hpp"
namespace cubeman{
class sudoku_simple_solver{
private:
    bool const is_in_x(char &,char &);
    bool const is_in_y(char &,char &);
    bool const is_in_chunk(char &,char &,char &);
    bool const can_place(char &,char &,char &);
    Sudoku *sudoku;
    bool dfs();
public:
    bool solve(Sudoku &);
};
}
#endif
