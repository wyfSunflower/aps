#ifndef ENGINE_H
#define ENGINE_H
#include <map>
#include <set>
#include <memory>
#include <string>
#include <future>
#include <queue>
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
    std::map<size_t, std::any> storage;
    std::map<std::string, std::function<std::shared_ptr<udf>(void)>> custom_invoke;
    engine& operator=(const engine&);
    void clear(){retryresult.clear(); id2fname.clear(); id2f.clear(); id2layer.clear(); layer2ids.clear(); ch.clear(); pr.clear(); storage.clear();}
    void initialize_priority_queue(const std::vector<size_t>& startnodes, std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>>& pq, \
        std::set<size_t>& inpq, size_t call_layer, bool run_already_calculated); //初始化优先队列
    bool run_s_internal(const std::vector<size_t>& startnodes, bool runninglog, size_t call_layer, bool run_already_calculated); //串行计算
    bool run_p_internal(const std::vector<size_t>& startnodes, bool runninglog, size_t call_layer, bool run_already_calculated); //模块间并行
    std::function<void(std::vector<std::any*>&, size_t)> tf = [this](std::vector<std::any*>& va, size_t idx){
        std::vector<size_t>& pre = pr[idx];
        std::transform(pre.begin(), pre.end(), std::back_inserter(va), [&](size_t x)->std::any*{
            return &storage[x];
        });
    };
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
        return storage[idx];
    }
    template<typename T> engine& operator=(T& initial){
        storage[root] = initial;
        return *this;
    }
    template<typename T> engine& operator=(T&& initial){
        storage[root] = std::move(initial);
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
        return run_s_internal(startnodes, runninglog, call_layer, true);
    }
    template<typename... Args> bool retry_p(bool runninglog, size_t call_layer, Args... args){
        std::vector<size_t> startnodes; vaargs(startnodes, args...);
        return run_p_internal(startnodes, runninglog, call_layer, true);
    }
    bool operator()();
    template<typename T> bool operator()(T& initial){
        storage.clear();
        storage[root] = initial;
        return this -> operator()();
    }
    template<typename T> bool operator()(T&& initial){
        storage.clear();
        storage[root] = std::move(initial);
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