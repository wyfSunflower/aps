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