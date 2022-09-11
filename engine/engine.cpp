#include "engine.h"
#include <iostream>
#include "../custom/exampleudf.h"
#include "../util/util.h"

namespace pipeline{
    void engine::reg(){
        REGISTER(exampleudf);
    }

    int engine::parse(nlohmann::json& graph){
        //硬编码
        if(!initial) clear(); //如果不是最开始的状态, 清空
        initial = false;
        for(auto it = graph.begin(); it != graph.end(); ++it){
            std::string key = it.key();
            bool ok = true;
            size_t k = getNonNegativeInteger(key, ok);
            if(!ok){
                WARNING(JSON_PARSE_ERROR);
                return JSON_PARSE_ERROR;
            }
            try{
                nlohmann::json& value = it.value();
                if(!contains(value, "fid", "pre")){
                    WARNING(JSON_PARSE_ERROR);
                }
                nlohmann::json& fidj = value["fid"];
                nlohmann::json& prea = value["pre"];
                if(fidj.is_null() || !CHECK_TYPE(fidj, "string")){
                    WARNING(JSON_PARSE_ERROR);
                }
                if(!prea.is_array()){
                    WARNING(JSON_PARSE_ERROR);
                }
                std::string fids = fidj.get<std::string>();
                if(custom_invoke.find(fids) == custom_invoke.end()){
                    WARNING(CUSTOM_INVOKE_FUNCTION_NOT_FOUND);
                }
                int sz = prea.size();
                for(int i = 0; i < sz; ++i){
                    nlohmann::json& element = prea[i];
                    if(!CHECK_TYPE(element, "unsigned")){
                        WARNING(JSON_PARSE_ERROR);
                    }
                    size_t prei = element.get<size_t>();
                    if(k == prei){
                        printf("k==prei==%zu\n", k);
                        WARNING(DEADLOCK_ERROR);
                    }
                    ch[prei].insert(k);
                    pr[k].insert(prei);
                }
            }catch(nlohmann::json::parse_error& ex){
                WARNING(JSON_PARSE_ERROR);
            }
        }
        return PARSE_OK;
    }

    int engine::parse(std::string& s){
        return parse(std::move(s));
    }

    int engine::parse(std::string&& s){
        nlohmann::json j;
        try{
            j = nlohmann::json::parse(s);
        }catch(nlohmann::json::parse_error& ex){
            WARNING(JSON_PARSE_ERROR);
            return JSON_PARSE_ERROR;
        }
        return parse(j);
    }
}