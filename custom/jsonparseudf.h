#ifndef JSONPARSEUDF_H
#define JSONPARSEUDF_H

#include "../global/global.h"

struct jsonparseudf:public udf{
    std::any operator()(std::vector<std::any*>& pre, global::globalstate& gs, int idx){
        nlohmann::json j;
        try{
            j = nlohmann::json::parse(std::any_cast<std::string>(*pre[0]));
        }catch(nlohmann::json::parse_error& ex){
            return std::any();
        }
        return std::any(std::move(j));
    }

    void retry(pipeline::engine* caller, int idx, int call_layer){

    }
};

#endif