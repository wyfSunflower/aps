#ifndef EXAMPLEUDF_H
#define EXAMPLEUDF_H

#include "../global/global.h"

struct exampleudf:public udf{
    int x;
    std::any operator()(std::vector<std::any*>& pre, global::globalstate& gs){
        x = 0;
        for(std::any* a: pre){
            x += std::any_cast<int>(*a);
        }
        return x;
    }
};

#endif