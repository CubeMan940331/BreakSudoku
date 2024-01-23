#include "sudoku_simple_solver.hpp"
bool const cubeman::sudoku_simple_solver::is_in_x(char &n,char &x){
    for(char j=0;j<9;++j){
        if((*(this->sudoku))[x][j]==n) return true;
    }
    return false;
}
bool const cubeman::sudoku_simple_solver::is_in_y(char &n,char &y){
    for(char i=0;i<9;++i){
        if((*(this->sudoku))[i][y]==n) return true;
    }
    return false;
}
bool const cubeman::sudoku_simple_solver::is_in_chunk(char &n,char &x,char &y){
    char sx=x-x%3,sy=y-y%3;
    for(char i=0;i<3;++i){
        for(char j=0;j<3;++j){
            if((*(this->sudoku))[sx+i][sy+j]==n) return true;
        }
    }
    return false;
}
bool const cubeman::sudoku_simple_solver::can_place(char &n,char &x,char &y){
    return (!is_in_x(n,x))&&(!is_in_y(n,y))&&(!is_in_chunk(n,x,y));
}
bool cubeman::sudoku_simple_solver::dfs(){
    for(char i=0;i<9;++i){
        for(char j=0;j<9;++j){
            if((*(this->sudoku))[i][j]) continue;
            for(char n=1;n<=9;++n){
                if(can_place(n,i,j)){
                    (*(this->sudoku))[i][j]=n;
                    if(dfs()) return true;
                    (*(this->sudoku))[i][j]=0;
                }
            }
            return false;
        }
    }
    return true;
}
bool cubeman::sudoku_simple_solver::solve(Sudoku &item){
    this->sudoku=&item;
    return dfs();
}
