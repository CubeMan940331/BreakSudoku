#ifndef CubeMan_Timer
#define CubeMan_Timer
#include<chrono>
namespace cubeman{
class Timer{
private:
    std::chrono::time_point<std::chrono::steady_clock> t1,t2;
public:
    void start(){t1=std::chrono::steady_clock::now();}
    long long elapsed_us(){
        t2=std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    }
};
}
#endif
