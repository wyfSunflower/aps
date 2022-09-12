#include "test.h"
int test(std::string&& infile, std::string&& outfile, std::function<int(std::istream*, std::ostream*)> fn){
    std::istream* in = &std::cin;
    std::ostream* out = &std::cout;
    std::ifstream inf;
    std::ofstream outf;
    bool openin = false, openout = false;
    if(!infile.empty()){
       openin = true;
       inf.open(infile, std::ios::in);
       in = &inf;
    }
    if(!outfile.empty()){
       openout = true;
       outf.open(outfile.c_str(), std::ios::trunc);
       out = &outf;
    }
    if(in -> fail() || out -> fail()){
        WARNING(IO_FAIL);
    }
    int res = fn(in, out);
    if(openin) inf.close();
    if(openout) outf.close();
    return res;
}

int test_engine(std::istream* in, std::ostream* out){
    int t = 0;
    while(t--){
        
    }
    return 0;
}