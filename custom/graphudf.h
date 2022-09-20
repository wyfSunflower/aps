#ifndef GRAPHUDF_H
#define GRAPHUDF_H

#include "../global/global.h"

struct graphudf:public udf{
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
        nlohmann::json j = std::move(std::any_cast<nlohmann::json>(*pre[0]));
        pipeline::G gr;
        if(!j.contains("nodes")){
            //这个udf专门提取nodes
            gr.set_valid(false);
            return g;
        }
        gr.readG(j["nodes"]);
        return std::any(std::move(gr));
    }

    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        return false;
    }
};

struct graphudf2:public udf{
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
        nlohmann::json j = std::move(std::any_cast<nlohmann::json>(*pre[0]));
        pipeline::G gr;
        std::any a;
        if(!j.contains("nodes")){
            //这个udf专门提取nodes
            gr.set_valid(false);
            /*
            因为a.has_value()==false, 因此会触发
            if(!storage[idx].has_value()){
                return false;
            }
            导致engine() 返回false
            */
            return a; 
        }
        gr.readG(j["nodes"]);
        return std::any(std::move(gr));
    }

    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        return false;
    }
};

struct graphudf3:public udf{
    std::any operator()(std::vector<std::any*>& pre, global::global& g, size_t idx, size_t call_layer, pipeline::engine* caller){
        nlohmann::json j = std::move(std::any_cast<nlohmann::json>(*pre[0]));
        pipeline::G gr;
        std::any a;
        if(!j.contains("nodes")){
            //这个udf专门提取nodes
            gr.set_valid(false);
            /*
            因为a.has_value()==false, 因此会触发
            if(!storage[idx].has_value()){
                return false;
            }
            导致engine() 返回false
            */
            return a; 
        }
        gr.readG(j["nodes"]);
        return gr.get_valid() ? std::any(std::move(gr)): std::any();
    }

    bool retry(pipeline::engine* caller, size_t idx, size_t call_layer){
        return true;
    }
};

#endif