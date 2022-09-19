#ifndef RETRYUDF_H
#define RETRYUDF_H

#include "../global/global.h"
#include <thread>
#include <ctime>
#include <random>
#include <chrono>
#include <thread>

struct retryudf:public udf{
    int x;
    int retrytimes, maxretries;
    retryudf(): x(0), retrytimes(0), maxretries(5){}
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer){
        for(std::any* a: pre){
            x += std::any_cast<int>(*a);
        }
        verdict[call_layer] = idx == 6 ? (retrytimes < maxretries ? WRONG : CORRECT) : CORRECT;
        return x;
    }
    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        if(retrytimes < maxretries && idx==6){
            ++retrytimes;
            RETRY(1, 2);
            return false;
        }
        return true;
    }
};

struct retryudf2:public udf{
    int x;
    int retrytimes, maxretries;
    retryudf2(): x(0), retrytimes(0), maxretries(1){}
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer){
        x = std::any_cast<int>(*(pre[0]));
        verdict[call_layer] = idx >= 2 ? (retrytimes < maxretries ? WRONG : CORRECT) : CORRECT;
        return x + retrytimes;
    }
    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        if(retrytimes < maxretries && idx >= 2){
            ++retrytimes;
            if(idx == 2) {
                RETRY(0);
            }else{
                RETRY(1);
            }
            return false;
        }
        return true;
    }
};

struct retryudf3:public udf{
    size_t x;
    int retrytimes, maxretries;
    retryudf3(): x(0), retrytimes(0), maxretries(100000000){}
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer){
        using namespace std::chrono_literals;
        if(idx==3) std::this_thread::sleep_for(41ns); 
        size_t seed = (size_t)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distributionInteger(0, 29);
        int r = distributionInteger(generator);
        for(std::any* a: pre){
            x += std::any_cast<size_t>(*a);
        }
        if(idx == 3 && r % 2 == 0){
            verdict[call_layer] = WRONG;
        }
        //if(idx == 3) printf("call_layer==%zu, x==%zu, r==%d\n", call_layer, x, r);
        return x;
    }
    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        if(retrytimes < maxretries && idx==3){
            ++retrytimes;
            RETRY(0);
            return false;
        }
        return true;
    }
};

#endif