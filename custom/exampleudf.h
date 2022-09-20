#ifndef EXAMPLEUDF_H
#define EXAMPLEUDF_H

#include "../global/global.h"
#include <thread>

struct exampleudf:public udf{
    int x;
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
        x = 0;
        for(std::any* a: pre){
            x += std::any_cast<int>(*a);
        }
        return x;
    }
    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        return false;
    }
};

struct exampleudf2:public udf{
    int x;
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
        TIMEGUARD
        x = 0;
        for(std::any* a: pre){
            x += std::any_cast<int>(*a);
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(x));
        return x;
    }
    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        return false;
    }
};

struct exampleudf3:public udf{
    int x;
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
        TIMEGUARD
        if(idx == 3){
            x = 0;
            int i = 1;
            for(std::any* a: pre){
                x += i * std::any_cast<int>(*a);
                ++i;
            }
        }else{
            return (int)idx;
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(x));
        return x;
    }
    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        return false;
    }
};

#endif