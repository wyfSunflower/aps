#ifndef EXAMPLEUDF_H
#define EXAMPLEUDF_H

#include "../global/global.h"

struct exampleudf:public udf{
    int x;
    std::any operator()(std::vector<std::any*>& pre, global::globalstate& gs){
        x = 1;
        int y = std::any_cast<int>(*pre[0]);
        return x+y;
    }
};

#endif