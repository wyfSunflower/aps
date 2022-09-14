#ifndef ENGINE_H
#define ENGINE_H
#include <map>
#include <set>
#include <memory>
#include <string>
#include "../protos/global.pb.h"
#include "../protos/graph.pb.h"
#include "../global/global.h"
#include "../util/util.h"
#include "nlohmann/json.hpp"

#define REGISTER(classname) custom_invoke[#classname] = std::make_shared<classname>();
#define PARSE_OK 0
#define JSON_PARSE_ERROR 1
#define CUSTOM_INVOKE_FUNCTION_NOT_FOUND 2
#define DEADLOCK_ERROR 3
#define ROOT_0_HAS_PRE 4
#define NOT_CONNECTED 5
#define TOPOLOGICAL_SORTING_FAILED 6
#define ID_NOT_FOUND 7

#define PARALLEL 0

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


namespace pipeline{
class engine{
private:
    bool initial, parsed;
    size_t root;
    std::map<size_t, std::shared_ptr<udf>> id2f;
    std::map<size_t, size_t> id2layer;
    std::map<size_t, std::set<size_t>> layer2ids;
    std::map<size_t, std::set<size_t>> ch; //children
    std::map<size_t, std::set<size_t>> pr; //previous
    global::globalstate gs;
    std::map<size_t, std::any> storage;
    std::map<std::string, std::shared_ptr<udf>> custom_invoke;
    engine& operator=(const engine&);
public:
    engine(): initial(true), parsed(false), root(0){reg();}
    engine(engine&)=delete;
    engine(engine&&)=delete;
    std::any operator[](size_t idx);
    template<typename T> engine& operator=(T& initial){
        storage[root] = initial;
        return *this;
    }
    template<typename T> engine& operator=(T&& initial){
        storage[root] = std::move(initial);
        return *this;
    }
    void clear(){id2f.clear(); id2layer.clear(); layer2ids.clear(); ch.clear(); pr.clear(); storage.clear();}
    void reg();
    int parse(nlohmann::json& graph);
    int parse(std::string& s);
    int parse(std::string&& s);
    std::string debug();
    bool run_s(); //串行计算
    bool run_p(); //模块间并行
    bool operator()();
    template<typename T> bool operator()(T& initial){
        storage[root] = initial;
        return this -> operator()();
    }
    template<typename T> bool operator()(T&& initial){
        storage[root] = std::move(initial);
        return this -> operator()();
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