#ifndef ENGINE_H
#define ENGINE_H
#include <map>
#include <set>
#include <memory>
#include <string>
#include <future>
#include <queue>
#include <concepts>
#include <any>
#include "../protos/global.pb.h"
#include "../protos/graph.pb.h"
#include "../global/global.h"
#include "../util/util.h"
#include "nlohmann/json.hpp"

#define REGISTER(classname) custom_invoke[#classname] = [](void)->std::shared_ptr<udf>{ return std::make_shared<classname>(); };
#define PARSE_OK 0
#define JSON_PARSE_ERROR 1
#define CUSTOM_INVOKE_FUNCTION_NOT_FOUND 2
#define DEADLOCK_ERROR 3
#define ROOT_0_HAS_PRE 4
#define NOT_CONNECTED 5
#define TOPOLOGICAL_SORTING_FAILED 6
#define ID_NOT_FOUND 7

#define PARALLEL 1

#define STRAIGHT 0
#define BEZIER 1

#define S_IDX "idx"
#define S_ID "id"
#define S_NID "nid"
#define S_LAYERID "layerId"
#define S_X "x"
#define S_Y "y"
#define S_Z "z"
#define S_TYPE "type"
#define S_OUTEDGES "outEdges"
#define S_CURVE "curvePoints"
#define WITHLOG true

template<typename T>
concept getable = requires(T a) { requires std::convertible_to<decltype(a.get()), std::any>; };


namespace pipeline{

class engine{
private:
    bool initial, parsed, parallel;
    size_t root, failtimes;
    std::string log; //运行日志
    std::map<std::pair<size_t, size_t>, bool> retryresult;
    std::map<size_t, std::string> id2fname;
    std::map<size_t, std::shared_ptr<udf>> id2f;
    std::map<size_t, size_t> id2layer;
    std::map<size_t, std::set<size_t>> layer2ids;
    std::map<size_t, std::vector<size_t>> ch; //children
    std::map<size_t, std::vector<size_t>> pr; //previous
    global::global g;
    std::map<size_t, std::pair<std::any, size_t>> storage;
    std::map<std::string, std::function<std::shared_ptr<udf>(void)>> custom_invoke;
    engine& operator=(const engine&);
    std::function<void(std::vector<std::any*>&, size_t)> tf = [this](std::vector<std::any*>& va, size_t idx){
        std::vector<size_t>& pre = pr[idx];
        std::transform(pre.begin(), pre.end(), std::back_inserter(va), [&](size_t x)->std::any*{
            return &(storage[x].first);
        });
    };
    std::function<serial_inner_helper(size_t, size_t)> serial_fn = [this](size_t call_layer, size_t idx)->serial_inner_helper{
        std::vector<std::any*> va;
        tf(va, idx);
        id2f[idx]->verdict[call_layer] = CORRECT;
        return serial_inner_helper(id2f[idx] -> operator()(va, g, idx, call_layer, this));
    };
    std::function<std::future<std::any>(size_t, size_t)> parallel_fn = [this](size_t call_layer, size_t idx)->std::future<std::any>{
        auto async_parallel = [this, call_layer](size_t idx)->std::any{
            std::vector<std::any*> va;
            tf(va, idx);
            id2f[idx]->verdict[call_layer] = CORRECT;
            return id2f[idx]->operator()(va, g, idx, call_layer, this);
        };
        return std::async(async_parallel, idx);
    };
    void clear(){retryresult.clear(); id2fname.clear(); id2f.clear(); id2layer.clear(); layer2ids.clear(); ch.clear(); pr.clear(); storage.clear();}
    void initialize_priority_queue(const std::vector<size_t>& startnodes, std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>>& pq, \
        std::set<size_t>& inpq, size_t call_layer, bool run_already_calculated); //初始化优先队列 
    bool prepare_for_initial_run(bool isparallel){
        if(!parsed) return false;
        for(auto it = id2f.begin(); it != id2f.end(); ++it){
            it->second->isparallel = isparallel;
            it->second->verdict[0] = NOT_CALCULATED;
        }
        failtimes = 0;
        log = "";
        return true;
    }
    template<getable G> bool run_internal(const std::vector<size_t>& startnodes, bool runninglog, size_t call_layer, bool run_already_calculated, const std::string& hintstring, std::function<G(size_t, size_t)> fn){
        /*
        startnodes: 运算开始的节点
        runninglog: true-记录日志 false-不记录日志
        call_layer: 调用层级, 初始为0
        */
        std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> pq;
        std::set<size_t> inpq;
        if(runninglog){
            log += "[" + timeStr() + " run_p_internal]: startnodes==" + stlout(startnodes) + ", call_layer==" + std::to_string(call_layer) + ".\n";
        }
        initialize_priority_queue(startnodes, pq, inpq, call_layer, run_already_calculated);
        while(!pq.empty()){
            std::vector<std::pair<size_t, size_t>> samelayer;
            auto t = pq.top();
            if(runninglog) log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: samelayer.push_back(" + stlout(t) + "), pq.size()==" + std::to_string(pq.size()) + "\n";
            pq.pop();
            //在同一层的一起出队列, 入samelayer
            samelayer.push_back(t);
            while(!pq.empty() && pq.top().first == t.first){
                samelayer.push_back(pq.top());
                if(runninglog) log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: samelayer.push_back(" + stlout(pq.top()) + "), pq.size()==" + std::to_string(pq.size()) + "\n";
                pq.pop();
            }
            //samelayer上的并行计算
            std::map<size_t, G> idx2f;
            for(auto layer_idx_pair: samelayer){
                size_t idx = layer_idx_pair.second;
                if(idx != root){
                    if(runninglog) log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: launch(" + std::to_string(idx) + ").\n";
                    for(size_t x: pr[idx]){
                        if(!storage[x].first.has_value()){
                            if(runninglog) log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: launch(" + std::to_string(idx) + ") failed because storage[" + std::to_string(x) + "] does not hold a value!\n";
                            return false; 
                        }
                    }
                    idx2f[idx] = fn(call_layer, idx);
                }
            }
            for(auto layer_idx_pair: samelayer){
                size_t idx = layer_idx_pair.second;
                if(idx != root){
                    std::any&& tmp = idx2f[idx].get();
                    if(!tmp.has_value()){
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} failed because result (type any).has_value() == false!\n";
                        return false;
                    }else if(id2f[idx]->verdict[call_layer] == WRONG){
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} failed because verdict==WRONG! Call " + std::to_string(idx) + " (" + id2fname[idx] + ") verdict==WRONG!\n";
                        ++id2f[idx]->failtimes;
                        ++failtimes;
                        bool res = id2f[idx]->retry(this, idx, call_layer);
                        retryresult[{call_layer, idx}] = res;
                    }else if(id2f[idx]->verdict[call_layer] == NOT_CALCULATED){
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} failed because verdict==NOT_CALCULATED! Call " + std::to_string(idx) + " (" + id2fname[idx] + ") verdict==NOT_CALCULATED! Now return false!\n";
                        return false;
                    }
                    if(id2f[idx]->verdict[call_layer] == CORRECT && (storage.find(idx) == storage.end() || call_layer > storage[idx].second)) {
                        storage[idx] = {tmp, call_layer};
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} successful. Verdict==" + std::to_string(id2f[idx]->verdict[call_layer]) + "[Stored]\n";
                    }else{
                        if(runninglog && id2f[idx]->verdict[call_layer] != CORRECT) 
                            log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + \
                                " (idx), " + std::to_string(call_layer) + " (call_layer)} unsuccessful (verdict==" + std::to_string(id2f[idx]->verdict[call_layer]) + ").\n";
                        if(runninglog && !(storage.find(idx) == storage.end() || call_layer > storage[idx].second)) log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: The result of {" + std::to_string(layer_idx_pair.first) + \
                             " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} is not stored because result of layer" + std::to_string(storage[idx].second) + " has already been stored.\n";
                    }
                }
                for(size_t c: ch[idx]){
                    if(inpq.find(c) == inpq.end() && ((run_already_calculated && id2f[c]->verdict[0] != NOT_CALCULATED) || (!run_already_calculated && id2f[c]->verdict[0] == NOT_CALCULATED))){
                        pq.push({id2layer[c], c});
                        inpq.insert(c);//避免重复加入队列
                        log += DBGSTR + "[" + timeStr() + " " + hintstring + "]: Push" + stlout(std::pair<size_t, size_t>(id2layer[c], c)) + ".\n";
                    }
                }
            }
        }
        return true;
    }
public:
    engine(): initial(true), parsed(false), parallel(true), root(0), failtimes(0){reg();}
    engine(engine&)=delete;
    engine(engine&&)=delete;
    void reset(){
        if(!parsed) return;
        for(auto it = id2f.begin(); it != id2f.end(); ++it){
            if(it -> first != root){
                if(it -> second) (it -> second).reset();
                it -> second = (custom_invoke[id2fname[it -> first]])();
            }
        }
    }
    std::any& operator[](size_t idx){
        return storage[idx].first;
    }
    template<typename T> engine& operator=(T& initial){
        storage[root] = {initial, 0};
        return *this;
    }
    template<typename T> engine& operator=(T&& initial){
        storage[root] = {std::move(initial), 0};
        return *this;
    }
    void reg();
    int parse(nlohmann::json& graph);
    int parse(std::string& s);
    int parse(std::string&& s);
    std::string debug();
    void copy(size_t src, size_t dst, bool use_move_semantics);
    bool run_s(); //串行计算
    bool run_p(); //模块间并行
    template<typename... Args> bool retry_s(bool runninglog, size_t call_layer, Args... args){
        std::vector<size_t> startnodes; vaargs(startnodes, args...);
        return run_internal<serial_inner_helper>(startnodes, WITHLOG, call_layer, true, "run_s_internal", serial_fn);
    }
    template<typename... Args> bool retry_p(bool runninglog, size_t call_layer, Args... args){
        std::vector<size_t> startnodes; vaargs(startnodes, args...);
        return run_internal<std::future<std::any>>(startnodes, WITHLOG, call_layer, true, "run_p_internal", parallel_fn);
    }
    bool operator()();
    template<typename T> bool operator()(T& initial){
        storage.clear();
        storage[root].first = initial;
        storage[root].second = 0;
        return this -> operator()();
    }
    template<typename T> bool operator()(T&& initial){
        storage.clear();
        storage[root].first = std::move(initial);
        storage[root].second = 0;
        return this -> operator()();
    }
    bool is_parallel(){
        return parallel;
    }
    bool is_parsed(){
        return parsed;
    }
    std::string getlog(){
        return log;
    }
    std::shared_ptr<udf> getpointer(size_t id){
        if(id2f.find(id) != id2f.end()){
            return id2f[id];
        }
        return nullptr;
    }
    void appendlog(const std::string& s){
        log += s;
    }
};

class G{
private:
    bool initial, valid;
    std::map<size_t, graph::vertex> V;
    std::map<size_t, std::map<int, std::set<size_t>>> thetahash;
    //thetahash说明:
    //每个点有个角度map, 即点的id (size_t类型)到角度map(std::map<int, std::set<size_t>>类型)的映射
    //角度map的key是角度(theta1), value是边的id集合(std::set<size_t>>类型)。同一个角度可能对应多个不同边, 所以用set。
public:
    G():initial(true), valid(true){}
    int readG(nlohmann::json& j); 
    int readG(std::string& s);
    int readG(std::string&& s);
    std::string debug();
    void set_valid(bool valid){this -> valid = valid;}
    bool get_valid(){return valid;}
};
}

#endif