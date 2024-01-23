#include "sudoku_complex_solver.hpp"
#include "sudoku_simple_solver.hpp"
#include "Timer.hpp"
using namespace std;
signed main(){
    cubeman::Sudoku sudoku;
    cubeman::Timer timer;
    cubeman::sudoku_complex_solver solver;
    long long T;
    while(sudoku.read(cin)){
        timer.start();
        if(solver.solve(sudoku)){
            T=timer.elapsed_us();
            cout<<sudoku.to_str();
            cout<<T<<"us\n";
        }
        else cout<<"error input\n";
        cout<<'\n';
    }

    return 0;
}
