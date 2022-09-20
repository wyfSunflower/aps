#ifndef GLOBAL_H
#define GLOBAL_H
#include <vector>
#include <memory>
#include <any>
#include <chrono>
#include "../protos/global.pb.h"
#define NOT_CALCULATED 0
#define WRONG 1
#define CORRECT 2
#define TIMEGUARD timeguard tg(this);
#define RETRY(...) if(isparallel){ caller->retry_p(WITHLOG, call_layer+1, __VA_ARGS__);} else { caller->retry_s(WITHLOG, call_layer+1, __VA_ARGS__);}
//RETRY宏的逻辑:
//首先在run_s和run_p的入口, engine会记录udf中的isparallel字段。程序会根据isparallel的内容判断调用retry_p(isparallel为true调用)还是retry_s(isparallel为false调用)
//以retry_p为例, 第一个参数WITHLOG决定是否打印runnignlog, 第二个参数call_layer+1表示递归调用层数+1, __VA_ARGS__是将startnodes打包成可变参数。例如2号节点触发0, 1节点重算, 则__VA_ARGS__传入0, 1

template<typename T, typename Duration_Type=std::chrono::nanoseconds>
struct timeguard{
    timeguard()=delete;
    T* p;
    timeguard(T* p):p(p){
        p -> start = std::chrono::steady_clock::now();
    }
    ~timeguard(){
        p -> end = std::chrono::steady_clock::now();
        p -> duration += (size_t)std::chrono::duration_cast<Duration_Type>(p -> end - p -> start).count();
    }
};

namespace pipeline{
    class engine;
}

namespace global{
    class global{
    public:
        std::chrono::time_point<std::chrono::steady_clock> start;
        std::chrono::time_point<std::chrono::steady_clock> end;
        size_t duration;
        globalstate gs;
        global(): duration(0){}
    };
}

struct udf{
    bool isparallel;
    int failtimes;
    std::map<size_t, int> verdict;
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
    size_t duration;
    udf():isparallel(true), failtimes(0), duration(0){}
    virtual std::any operator()(std::vector<std::any*>& pre, global::global& gs, size_t idx, size_t call_layer, pipeline::engine* caller) = 0;
    virtual bool retry(pipeline::engine* caller, size_t idx, size_t call_layer) = 0;
};

#endif