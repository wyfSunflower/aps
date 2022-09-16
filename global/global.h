#ifndef GLOBAL_H
#define GLOBAL_H
#include <vector>
#include <memory>
#include <any>
#include "../protos/global.pb.h"
#define NOT_CALCULATED 0
#define WRONG 1
#define CORRECT 2

namespace pipeline{
    class engine;
}

struct udf{
    int failtimes;
    int verdict;
    udf():failtimes(0), verdict(NOT_CALCULATED){}
    virtual std::any operator()(std::vector<std::any*>& pre, global::globalstate& gs, int idx) = 0;
    virtual bool retry(pipeline::engine* caller, int idx, int call_layer) = 0;
};

#endif