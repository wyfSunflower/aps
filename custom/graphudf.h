#ifndef GRAPHUDF_H
#define GRAPHUDF_H

#include "../global/global.h"

struct graphudf:public udf{
    std::any operator()(std::vector<std::any*>& pre, global::globalstate& gs){
        nlohmann::json j = std::move(std::any_cast<nlohmann::json>(*pre[0]));
        pipeline::G g;
        if(!j.contains("nodes")){
            //这个udf专门提取nodes
            g.set_valid(false);
            return g;
        }
        g.readG(j["nodes"]);
        return std::any(std::move(g));
    }
};

struct graphudf2:public udf{
    std::any operator()(std::vector<std::any*>& pre, global::globalstate& gs){
        nlohmann::json j = std::move(std::any_cast<nlohmann::json>(*pre[0]));
        pipeline::G g;
        std::any a;
        if(!j.contains("nodes")){
            //这个udf专门提取nodes
            g.set_valid(false);
            /*
            因为a.has_value()==false, 因此会触发
            if(!storage[idx].has_value()){
                return false;
            }
            导致engine() 返回false
            */
            return a; 
        }
        g.readG(j["nodes"]);
        return std::any(std::move(g));
    }
};

struct graphudf3:public udf{
    std::any operator()(std::vector<std::any*>& pre, global::globalstate& gs){
        nlohmann::json j = std::move(std::any_cast<nlohmann::json>(*pre[0]));
        pipeline::G g;
        std::any a;
        if(!j.contains("nodes")){
            //这个udf专门提取nodes
            g.set_valid(false);
            /*
            因为a.has_value()==false, 因此会触发
            if(!storage[idx].has_value()){
                return false;
            }
            导致engine() 返回false
            */
            return a; 
        }
        g.readG(j["nodes"]);
        return g.get_valid() ? std::any(std::move(g)): std::any();
    }
};

#endif