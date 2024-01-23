#ifndef CubeMan_sudoku_complex_solver
#define CubeMan_sudoku_complex_solver
#include "Sudoku.hpp"
namespace cubeman{
class sudoku_complex_solver{
private:
    struct state{
        char puzzle[9][9]{};
        bool note[9][9][10];
        char pos_count[9][9];
        char complete_state=0;
        bool n_is_in_x[10][9]{};
        bool n_is_in_y[10][9]{};
        bool n_is_in_chunk[10][9]{};
        state();
        bool set_note(char,char,char,bool);//return is change
        bool update_note();//return is change
        void set_n(char,char,char);
        bool update_n();//return is change
        bool is_done();
        bool is_legal();
        void inference();
    };
    
    static char guess_list[9];

    Sudoku *sudoku;
    bool dfs(state);
    char solution_count;
    bool if_random;
    bool flag;//false for solve, true for check mutiple sulotion
    void solve_();
public:
    sudoku_complex_solver(bool random=false);
    bool solve(Sudoku &);
    bool singal_solution(Sudoku &);
};
}
#endif
