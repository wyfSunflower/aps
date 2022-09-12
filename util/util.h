#ifndef UTIL_H
#define UTIL_H
#include <sstream>
#include <string>
#include "nlohmann/json.hpp"
#define DBG printf("__FILE__==%s, __LINE__==%d\n", __FILE__, __LINE__);
#define WARNING(TYPE) printf("FILE==%s, LINE==%d, TYPE==%s (%d)", __FILE__, __LINE__, #TYPE, TYPE); return TYPE;

template<typename T>
bool stoT(std::string s, T& t){
    std::stringstream ss(s);
    ss >> t;
    return !ss.fail();
}

size_t getNonNegativeInteger(std::string s, bool& ok);

#define TYPE(j) \
( \
    j.type() == nlohmann::json::value_t::null ? "null": \
    j.type() == nlohmann::json::value_t::boolean ? "bool": \
    j.type() == nlohmann::json::value_t::number_unsigned ? "unsigned": \
    j.type() == nlohmann::json::value_t::number_integer ? "int": \
    j.type() == nlohmann::json::value_t::number_float ? "float": \
    j.type() == nlohmann::json::value_t::object ? "object": \
    j.type() == nlohmann::json::value_t::array ? "array": \
    j.type() == nlohmann::json::value_t::string? "string":"unknown" \
)

#define CHECK_TYPE(x, y) (std::string(TYPE(x)) == std::string(y))

template<typename KeyType>
bool contains(nlohmann::json& j, KeyType&& k){
    return j.contains(k);
}

template<typename KeyType, typename... Args>
bool contains(nlohmann::json& j, KeyType&& k, Args... args){
    if(!j.contains<KeyType>(k)) return false;
    return contains(j, args...);
}


#endif