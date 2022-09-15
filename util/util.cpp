#include "util.h"

size_t getNonNegativeInteger(std::string s, bool& ok){
    size_t n = s.size();
    if(n == 0){
        ok = false;
        return 0;
    }
    if(n != 1 && s[0] == 0){
        //前导0
        ok = false;
        return 0;
    }
    size_t ans = 0;
    for(size_t i = 0; i < n; ++i){
        char c = s[i];
        if(c < '0' || c > '9'){
            ok = false;
            return 0;
        }
        ans = ans * 10 + c - '0';
    }
    ok = true;
    return ans;
}

std::string timeStr()
{
    const std::string &format = "%Y-%m-%d %X";
    const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();  
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), format.c_str());
    return ss.str();
}