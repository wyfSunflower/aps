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
    pipeline::engine e;
    std::string tstr;
    if(!std::getline(CIN, tstr)){
        return 0;
    }
    bool _ok = false;
    t = getNonNegativeInteger(tstr, _ok);
    if(!_ok){
        return (int)_ok;
    }
    int ok = 1;
    //{"1": {"pre": [0], "fid": "exampleudf"}, "2": {"pre": [0], "fid": "exampleudf"}, "3": {"pre": [1, 2], "fid": "exampleudf"}}
    while(t--){
        std::string j;
        if(!std::getline(CIN, j)){
            COUT << "GETLINE ERROR!\n";
            return 0;
        }
        COUT << "j==" << j << "\n";
        int tmpok = !e.parse(j);
        if(!tmpok){
            COUT << "PARSE ERROR: j==" << j << "\n\n";
        }else{
            COUT << e.debug() << "PARSE OK.\n\n";
        }
        ok = ok && tmpok;
    }
    return ok;
}