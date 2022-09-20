#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <math.h>
#include "nlohmann/json.hpp"
#define DBG printf("__FILE__==%s, __LINE__==%d\n", __FILE__, __LINE__);
#define DBGSTR (std::string(__FILE__) + ", line" + std::to_string(__LINE__) + ":") 
#define SILENT 1
#define WARNING(TYPE) { if(!SILENT) { printf("FILE==%s, LINE==%d, TYPE==%s (%d)\n", __FILE__, __LINE__, #TYPE, TYPE); } return TYPE; }
#define PI 3.1415927
#define RAD 57.2957787

template<typename T>
bool stoT(std::string s, T& t){
    std::stringstream ss(s);
    ss >> t;
    return !ss.fail();
}

size_t getNonNegativeInteger(std::string s, bool& ok);

#define TYPE(j) \
( \
    (j).type() == nlohmann::json::value_t::null ? "null": \
    (j).type() == nlohmann::json::value_t::boolean ? "bool": \
    (j).type() == nlohmann::json::value_t::number_unsigned ? "unsigned": \
    (j).type() == nlohmann::json::value_t::number_integer ? "int": \
    (j).type() == nlohmann::json::value_t::number_float ? "float": \
    (j).type() == nlohmann::json::value_t::object ? "object": \
    (j).type() == nlohmann::json::value_t::array ? "array": \
    (j).type() == nlohmann::json::value_t::string? "string":"unknown" \
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

template<typename ValueType>
ValueType getd(nlohmann::json& j, const std::string& key, const ValueType& V){
    if(j.contains(key)) return j[key].get<ValueType>();
    return V;
}

template<typename T, T...>
struct myinteger_sequence { };

template<typename T, typename S1 = void, typename S2 = void>
struct helper{
    std::string operator()(const T& s){
        return std::string(s);
    }
}; 

template<typename T>
struct helper<T, decltype((void)std::to_string(std::declval<T>())), typename std::enable_if<!std::is_same<typename std::decay<T>::type, char>::value, void>::type>{
    std::string operator()(const T& s){
        return std::to_string(s);
    }
};

template<typename T>
struct helper<T, void, typename std::enable_if<std::is_same<typename std::decay<T>::type, char>::value, void>::type>{
    std::string operator()(const T& s){
        return std::string(1, s);
    }
};

template<typename T, typename S1 =void, typename S2 =void>
struct seqhelper{
    const static bool seq = false;
};

template<typename T>
struct seqhelper<T, decltype((void)(std::declval<T>().begin())), decltype((void)(std::declval<T>().end()))>{
    const static bool seq = !(std::is_same<typename std::decay<T>::type, std::string>::value);
};

template<std::size_t N, std::size_t... I>
struct gen_indices : gen_indices<(N - 1), (N - 1), I...> { };
template<std::size_t... I>
struct gen_indices<0, I...> : myinteger_sequence<std::size_t, I...> { };

template<typename T, typename REDUNDANT = void>
struct converter{
    template<typename H>
    std::string& to_string_impl(std::string& s, H&& h)
    {
        using std::to_string;
        s += converter<H>().convert(std::forward<H>(h));
        return s;    
    }

    template<typename H, typename... T1>
    std::string& to_string_impl(std::string& s, H&& h, T1&&... t)
    {
        using std::to_string;
        s += converter<H>().convert(std::forward<H>(h)) + ", ";
        return to_string_impl(s, std::forward<T1>(t)...);
    }

    template<typename... T1, std::size_t... I>
    std::string mystring(const std::tuple<T1...>& tup, myinteger_sequence<std::size_t, I...>)
    {
        std::string result;
        int ctx[] = { (to_string_impl(result, std::get<I>(tup)...), 0), 0 };
        (void)ctx;
        return result;
    }

    template<typename... S>
    std::string mystring(const std::tuple<S...>& tup)
    {
        return mystring(tup, gen_indices<sizeof...(S)>{});
    }

    template<typename S=T>
    std::string convert(const S& x){
        return helper<S>()(x);
    }

    template<typename... S>
    std::string convert(const std::tuple<S...>& tup){
        std::string res = std::move(mystring(tup));
        res = "{" + res + "}";
        return res;
    }

    template<typename S1, typename S2>
    std::string convert(const std::pair<S1, S2>& x){
        return "{" + converter<S1>().convert(x.first) + ", " + converter<S2>().convert(x.second) + "}";
    }
};

template<typename T>
struct converter<T, typename std::enable_if<seqhelper<T>::seq, void>::type>{
    template<typename S=T>
    std::string convert(const S& x){
        int len = 0;
        std::string ans = "{";
        for(auto it = x.begin(); it != x.end(); ++it){
            ans += move(converter<typename S::value_type>().convert(*it)) + ", ";
            ++len;
        }
        if(len == 0) return "{[EMPTY]}";
        ans.pop_back(), ans.pop_back();
        return ans + "}";
    }
};

template<typename T> //stl->std::string
std::string stlout(const T& x){
    return converter<T>().convert(x);
}

template<typename T>
T gettheta(T x, T y){
    double theta = atan2((double)y, (double)x);
    return (T)(::round(theta*RAD*1000));
}

std::string timeStr();

template<typename BaseType, typename T>
void vaargs(std::vector<BaseType>& container, T&& arg){
    container.push_back((BaseType)arg);
}

template<typename BaseType, typename T, typename... Args>
void vaargs(std::vector<BaseType>& container, T&& arg, Args&&... args){
    container.push_back((BaseType)arg);
    vaargs(container, std::forward<Args>(args)...);
}

struct serial_inner_helper{
    std::any A;
    std::any&& get(){
        return std::move(A);
    }
    serial_inner_helper& operator=(std::any&& anotherA){
        A = std::forward<std::any>(anotherA);
        return *this;
    }
	serial_inner_helper(std::any&& anotherA){
		A = std::forward<std::any>(anotherA);
	}
    serial_inner_helper& operator=(serial_inner_helper&& ih){
        A = std::move(ih.A);
        return *this;
    }
	serial_inner_helper(serial_inner_helper&& ih){
		A = std::move(ih.A);
	}
    serial_inner_helper()=default;
};


template<typename T>
struct anyhelper{
    bool hasvalue, valid;
    size_t Tid, anytypeid;
    std::string what;
    T value;
    anyhelper()=delete;
    anyhelper(const anyhelper&)=delete;
    anyhelper(const std::any& A, bool move=false):hasvalue(A.has_value()), valid(false), Tid(typeid(T).hash_code()), anytypeid(0){
        if(A.has_value()){
            anytypeid = A.type().hash_code();
            if(anytypeid == Tid){
                valid = true;
                what = "ok";
                try{
                    value = move ? std::move(std::any_cast<T>(A)) : std::move(std::any_cast<T>(A));
                }catch(const std::bad_any_cast& e){
                    what = e.what();
                    valid = false;
                }
            }else{
                what = "Tid==" + std::to_string(Tid) + ", anytypeid==" + std::to_string(anytypeid) + ", Ttype==" + std::string(typeid(T).name()) + ", anytype==" + std::string(A.type().name()) + ", not match!";
            }
        }else{
            what = "A.has_value() == false";
        }
    }
    anyhelper(const serial_inner_helper& ih, bool move=false):anyhelper(ih.A, move){}
};

#endif