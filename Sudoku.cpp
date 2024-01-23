#include "Sudoku.hpp"
std::string const cubeman::Sudoku::to_str(bool number_only){
    std::string str;
    for(char i=0;i<9;++i){
        for(char j=0;j<9;++j){
            if((!number_only)&&(j==3||j==6)) str+='|';
            else if(j) str+=' ';
            str+=(puzzle[i][j]+'0');
        }
        str+='\n';
        if((!number_only)&&(i==2||i==5)) str+="-----------------\n";
    }
    return str;
}
bool cubeman::Sudoku::read(std::istream &in){
    short tmp;
    for(char i=0;i<9;++i){
        for(char j=0;j<9;++j){
            if(in.eof()) return false;
            in>>tmp;
            puzzle[i][j]=tmp;
        }
    }
    return true;
}
void cubeman::Sudoku::operator=(Sudoku const &other){
    for(char i=0;i<9;++i){
        for(char j=0;j<9;++j){
            puzzle[i][j]=other.puzzle[i][j];
        }
    }
}
cubeman::Sudoku::Sudoku(){
    for(char i=0;i<9;++i){
        for(char j=0;j<9;++j) puzzle[i][j]=0;
    }
}
cubeman::Sudoku::Sudoku(std::istream &in){read(in);}
char *cubeman::Sudoku::operator[](int i){return this->puzzle[i];}
