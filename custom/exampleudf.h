#ifndef EXAMPLEUDF_H
#define EXAMPLEUDF_H

#include "../global/global.h"

struct exampleudf:public udf{
    int x;
    std::any operator()(std::vector<std::any*>& pre, global::globalstate& gs, int idx){
        x = 0;
        for(std::any* a: pre){
            x += std::any_cast<int>(*a);
        }
        return x;
    }
    bool retry(pipeline::engine* caller, int idx, int call_layer){
        return false;
    }
};

#endif