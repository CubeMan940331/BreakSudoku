#include "BreakSudoku35.h"
#include"Timer.h"
#include<iostream>
using namespace std;
int main(){
    cubeman::Sudoku sudoku;
    cubeman::Timer timer;
    long long T;
    while(sudoku.read(cin)){
        timer.start();
        //cubeman::sudoku_complex_solver solver(sudoku);
        cubeman::sudoku_simple_solver solver(sudoku);
        if(solver.solve()){
            T=timer.elapsed_us();
            cout<<sudoku.to_str();
            cout<<T<<" us\n";
        }
        else cout<<"error input\n";
        cout<<'\n';
    }

    return 0;
}
