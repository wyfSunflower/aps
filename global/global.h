#ifndef GLOBAL_H
#define GLOBAL_H
#include <vector>
#include <memory>
#include <any>
#include "../protos/global.pb.h"

struct udf{
    virtual std::any operator()(std::vector<std::any*>& pre, global::globalstate& gs) = 0;
};

#endif