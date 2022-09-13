#include "engine.h"
#include <iostream>
#include <queue>
#include "../custom/exampleudf.h"
#include "../util/util.h"

namespace pipeline{
    void engine::reg(){
        REGISTER(exampleudf);
    }

    std::any engine::operator[](size_t idx){
        return storage[idx];
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
            }
            if(k == 0){
                WARNING(ROOT_0_HAS_PRE);
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
                id2f[k] = custom_invoke[fids];
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
        }//for

        std::map<size_t, size_t> idg;//入度
        idg[root] = 0;
        id2layer[root] = 0;
        layer2ids[0] = {root};
        for(auto it = pr.begin(); it != pr.end(); ++it){
            std::set<size_t>& tmp = it -> second;
            for(auto tmppre: tmp){
                if(tmppre != 0 && pr[tmppre].size() == 0){
                    printf("pr[%zu].size()==%zu\n", tmppre, pr[tmppre].size());
                    WARNING(NOT_CONNECTED);
                }
            }
            idg[it->first] = it -> second.size();
        }

        //拓扑排序
        std::queue<std::pair<size_t, size_t>> q;
        q.push({root, 0});
        size_t num = 0;
        while(!q.empty()){
            auto [u, layerid] = q.front();
            q.pop();
            id2layer[u] = layerid;
            layer2ids[layerid].insert(u);
            for(int v: ch[u]){
                --idg[v]; //降低后继节点的入度
                if(idg[v] == 0){//如果后继节点的入度为0, 入队
                    q.push({v, layerid+1});
                }
            }
            ++num; //统计加入拓扑排序的节点数
        }
        if(num != pr.size() + 1){
            //从拓扑排序中出队列的节点数目(num)应该等于总的节点数目
            //上面已经校验过, 凡是pr右侧出现的节点都在pr左侧出现过
            //因此总节点数为pr.size() + 1
            WARNING(TOPOLOGICAL_SORTING_FAILED);
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

    std::string engine::debug(){
        std::string res;
        res += "root==" + std::to_string(root) + ", layer(" + std::to_string(root) + ")==" + std::to_string(id2layer[root]) + "\n";
        for(auto it = pr.begin(); it != pr.end(); ++it){
            res += "id==" + std::to_string(it->first) + ", layer(" + std::to_string(it->first) + ")==" + std::to_string(id2layer[it->first]) + ", pre==" + stlout(pr[it->first]) + "\n";
        }
        res += "Debug layers:\n";
        res += stlout(layer2ids) + "\n";
        return res;
    }

    void engine::run_s(){
        for(auto it = layer2ids.begin(); it != layer2ids.end(); ++it){
            if(it -> first == 0) continue;
            for(int idx: it->second){
                std::set<size_t>& pre = pr[idx];
                std::vector<std::any*> va;
                std::transform(pre.begin(), pre.end(), std::back_inserter(va), [&](size_t x)->std::any*{
                    return &storage[x];
                });
                storage[idx] = std::move(id2f[idx]->operator()(va, gs));
            }
        }
    }

    void engine::run_p(){
        //using std::async
        //TODO
    }

    void engine::operator()(){
        if(PARALLEL){
            run_p();
        }else{
            run_s();
        }
    }
}