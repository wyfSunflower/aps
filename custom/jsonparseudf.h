#ifndef JSONPARSEUDF_H
#define JSONPARSEUDF_H

#include "../global/global.h"

struct jsonparseudf:public udf{
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer){
        nlohmann::json j;
        try{
            j = nlohmann::json::parse(std::any_cast<std::string>(*pre[0]));
        }catch(nlohmann::json::parse_error& ex){
            return std::any();
        }
        return std::any(std::move(j));
    }

    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        return false;
    }
};

#endif