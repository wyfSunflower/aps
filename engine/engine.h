#ifndef ENGINE_H
#define ENGINE_H
#include <map>
#include <set>
#include <memory>
#include <string>
#include "../protos/global.pb.h"
#include "../global/global.h"
#include "../util/util.h"
#include "nlohmann/json.hpp"

#define REGISTER(classname) custom_invoke[#classname] = std::make_unique<classname>();
#define PARSE_OK 0
#define JSON_PARSE_ERROR 1
#define CUSTOM_INVOKE_FUNCTION_NOT_FOUND 2
#define DEADLOCK_ERROR 3
#define ROOT_0_HAS_PRE 4
#define NOT_CONNECTED 5
#define TOPOLOGICAL_SORTING_FAILED 6

namespace pipeline{
class engine{
private:
    bool initial;
    size_t root;
    std::map<size_t, std::shared_ptr<udf>> id2f;
    std::map<size_t, size_t> id2layer;
    std::map<size_t, std::set<size_t>> layer2ids;
    std::map<size_t, std::set<size_t>> ch; //children
    std::map<size_t, std::set<size_t>> pr; //previous
    global::globalstate gs;
    std::map<size_t, std::any> storage;
    std::map<std::string, std::shared_ptr<udf>> custom_invoke;
public:
    engine(): initial(true), root(0){reg();}
    void clear(){id2f.clear(); id2layer.clear(); layer2ids.clear(); ch.clear(); pr.clear(); storage.clear();}
    void reg();
    int parse(nlohmann::json& graph);
    int parse(std::string& s);
    int parse(std::string&& s);
};
}

#endif