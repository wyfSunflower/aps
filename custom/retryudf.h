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
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
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
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
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
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
        using namespace std::chrono_literals;
        if(idx==3) std::this_thread::sleep_for(1us); 
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

struct retryudfrunsbug:public udf{
    size_t x;
    int retrytimes, maxretries;
    retryudfrunsbug(): x(0), retrytimes(0), maxretries(1){}
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
        if(idx == 1 && retrytimes == 0){
            verdict[call_layer] = WRONG;
            (*caller)[0] = (size_t)1;
        }
        return *pre[0];
    }
    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        if(retrytimes < maxretries && idx==1){
            ++retrytimes;
            RETRY(0);
            return false;
        }
        return true;
    }
};

struct retryudfnotwork:public udf{
    int retrytimes, maxretries;
    retryudfnotwork(): retrytimes(0), maxretries(1){}
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
        if(idx == 1 && retrytimes == 0){
            verdict[call_layer] = WRONG;
        }
        return *pre[0];
    }
    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        if(retrytimes < maxretries){
            ++retrytimes;
            RETRY(3);//retry idx的后继节点, 因此不会进行任何运算, 因为retry的时候只会retry已经算过的节点。所以这个udf本身没有什么意义!只是测试下如果RETRY没算过的点程序会不会崩掉!
            return false;
        }
        return true;
    }
};

#endif