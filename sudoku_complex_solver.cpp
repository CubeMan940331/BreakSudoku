#include "sudoku_complex_solver.hpp"
#include<random>
#include<algorithm>
//state functions
cubeman::sudoku_complex_solver::state::state(){
    //set every note 1
    //set every pos_count 9
    for(char i=0;i<9;++i){
        for(char j=0;j<9;++j){
            pos_count[i][j]=9;
            for(char n=0;n<=9;++n){
                this->note[i][j][n]=true;
            }
        }
    }
}
inline bool cubeman::sudoku_complex_solver::state::set_note(char x,char y,char n,bool p){
    bool isc=(p!=this->note[x][y][n]);//is change
    if(p){
        if(!this->note[x][y][n]) ++this->pos_count[x][y];
    }
    else{
        if(this->note[x][y][n]&&this->pos_count[x][y]) --this->pos_count[x][y];
    }
    this->note[x][y][n]=p;
    return isc;
}
bool cubeman::sudoku_complex_solver::state::update_note(){
    bool isc=false;//is change anything
    char sx,sy,ex,ey;
    char x,y,count;
    for(char c=0;c<9;++c){//chunk 0~8
        sx=(c%3)*3;sy=(c/3)*3;
        ex=sx+2;ey=sy+2;
        for(char n=1;n<=9;++n){//number 1~9
            bool ise;
            count=0;
            for(char i=sx;i<=ex;++i){//check if all note in the same x
                ise=false;
                for(char j=sy;j<=ey;++j){
                    if(this->note[i][j][n]){x=i;ise=true;break;}
                }
                count+=ise;
            }
            if(count==1){
                for(char j=0;j<9;++j){
                    if(j>=sy&&j<=ey) continue;//skip this chunk
                    if(this->set_note(x,j,n,false)) isc=true;
                }
            }
            ////////
            count=0;
            for(char j=sy;j<=ey;++j){//check if all note in the same y
                ise=false;
                for(char i=sx;i<=ex;++i){
                    if(this->note[i][j][n]){y=j;ise=true;break;}
                }
                count+=ise;
            }
            if(count==1){
                for(char i=0;i<9;++i){
                    if(i>=sx&&i<=ex) continue;//skip this chunk
                    if(this->set_note(i,y,n,false)) isc=true;
                }
            }
        }
    }
    ////////
    for(char n=1;n<=9;++n){//n 1~9
        for(char t=0;t<9;++t){//0~8
            //y
            count=0;
            for(char c=0;c<3;++c){//3 chunks
                sy=c*3;ey=sy+2;
                for(char j=sy;j<=ey;++j){
                    if(this->note[t][j][n]){++count;y=j;break;}
                }
            }
            if(count==1){
                char chunk=(t/3)+(y/3)*3;
                sx=(chunk%3)*3;sy=(chunk/3)*3;
                ex=sx+2;ey=sy+2;
                for(char i=sx;i<=ex;++i){
                    for(char j=sy;j<=ey;++j){
                        if(i==t) continue;
                        if(set_note(i,j,n,false)) isc=true;
                    }
                }
            }
            //x
            count=0;
            for(char c=0;c<3;++c){//3 chunks
                sx=c*3;ex=sx+2;
                for(char i=sx;i<=ex;++i){
                    if(this->note[i][t][n]){++count;x=i;break;}
                }
            }
            if(count==1){
                char chunk=(x/3)+(t/3)*3;
                sx=(chunk%3)*3;sy=(chunk/3)*3;
                ex=sx+2;ey=sy+2;
                for(char i=sx;i<=ex;++i){
                    for(char j=sy;j<=ey;++j){
                        if(j==t) continue;
                        if(set_note(i,j,n,false)) isc=true;
                    }
                }
            }
        }
    }
    return isc;
}
inline void cubeman::sudoku_complex_solver::state::set_n(char x,char y,char n){
    if(!n) return;
    if(this->puzzle[x][y]) return;
    this->puzzle[x][y]=n;
    for(char i=0;i<9;++i){
        set_note(x,y,i+1,false);
        set_note(x,i,n,false);
        set_note(i,y,n,false);
    }
    char chunk=(x/3)+(y/3)*3;
    char sx=x-x%3,sy=y-y%3;
    for(char i=0;i<3;++i){
        for(char j=0;j<3;++j){
            set_note(i+sx,j+sy,n,false);
        }
    }
    this->n_is_in_chunk[n][chunk]=true;
    this->n_is_in_x[n][x]=true;
    this->n_is_in_y[n][y]=true;
    ++this->complete_state;
}
bool cubeman::sudoku_complex_solver::state::update_n(){
    bool isc=false;
    char sx,ex,sy,ey,count,x,y;
    for(char n=1;n<=9;++n){
        //serach for pos_count==1
        for(char i=0;i<9;++i){
            for(char j=0;j<9;++j){
                if((this->pos_count[i][j]==1)&&this->note[i][j][n]){
                    set_n(i,j,n);
                    isc=true;
                }
            }
        }
        //search for only noted n in chunk
        for(char c=0;c<9;++c){
            if(this->n_is_in_chunk[n][c]) continue;
            sx=(c%3)*3;sy=(c/3)*3;
            ex=sx+2;ey=sy+2;
            count=0;
            for(char i=sx;i<=ex;++i){
                for(char j=sy;j<=ey;++j) if(this->note[i][j][n]){++count;x=i;y=j;}
            }
            if(count==1){set_n(x,y,n);isc=true;}
        }
        ////////////////
        for(char t=0;t<9;++t){
            //search for only noted n in same x
            if(!this->n_is_in_x[n][t]){
                count=0;
                for(char j=0;j<9;++j) if(this->note[t][j][n]){++count;y=j;};
                if(count==1){set_n(t,y,n);isc=true;}
            }
            //search for only noted n in same y
            if(!this->n_is_in_y[n][t]){
                count=0;
                for(char i=0;i<9;++i) if(this->note[i][t][n]){++count;x=i;};
                if(count==1){set_n(x,t,n);isc=true;}
            }
        }
    }
    return isc;
}
inline bool cubeman::sudoku_complex_solver::state::is_done(){
    //if 81 blocks are filled with number
    return this->complete_state==81;
}
inline bool cubeman::sudoku_complex_solver::state::is_legal(){
    for(char i=0;i<9;++i){
        for(char j=0;j<9;++j){
            //if pos_count of the block is zero but it is still blank
            if((!this->pos_count[i][j])&&(!this->puzzle[i][j])) return false;
        }
    }
    return true;
}
void cubeman::sudoku_complex_solver::state::inference(){
    bool flag=true;
    while(flag){
        flag=false;
        if(this->update_n()) flag=true;
        if(this->update_note()) flag=true;
    }
}
//solver functions
char cubeman::sudoku_complex_solver::guess_list[9]{1,2,3,4,5,6,7,8,9};
cubeman::sudoku_complex_solver::sudoku_complex_solver(bool random){
    this->if_random=random;
}
bool cubeman::sudoku_complex_solver::dfs(state node){
    node.inference();
    if(node.is_done()){
        ++(this->solution_count);
        if(!this->flag){
            //copy this node to sudoku
            for(char i=0;i<9;++i){
                for(char j=0;j<9;++j){
                    (*(this->sudoku))[i][j]=node.puzzle[i][j];
                }
            }
        }
        return this->solution_count==this->flag+1;
    }
    if(!node.is_legal()) return false;

    for(char i=0;i<9;++i){
        for(char j=0;j<9;++j){
            if(node.puzzle[i][j]) continue;//if this block is filled
            for(char n,idx=0;idx<9;++idx){
                n=guess_list[idx];
                if(node.note[i][j][n]){
                    state next=node;
                    next.set_n(i,j,n);
                    if(dfs(next)) return true;
                }
            }
            return false;    
        }
    }
    return false;
}
void cubeman::sudoku_complex_solver::solve_(){
    //init
    if(this->if_random){
        std::random_device rd;
        std::mt19937 rng(rd());
        std::shuffle(guess_list,guess_list+9,rng);
    }
    this->solution_count=0;
    state node;
    for(char i=0;i<9;++i){
        for(char j=0;j<9;++j){
            if(!node.note[i][j][(*(this->sudoku))[i][j]]) return;
            node.set_n(i,j,this->sudoku->puzzle[i][j]);
        }
    }
    if(!node.is_legal()) return;
    dfs(node);
}
bool cubeman::sudoku_complex_solver::solve(Sudoku &item){
    //init
    this->sudoku=&item;
    this->flag=false;
    this->solve_();
    return this->solution_count;
}
bool cubeman::sudoku_complex_solver::singal_solution(Sudoku &item){
    //init
    this->sudoku=&item;
    this->flag=true;
    this->solve_();
    return this->solution_count==1;
}
