#include "test.h"
//CIN: (*in)
//COUT: (*out)
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

int test_pipeline1(std::istream* in, std::ostream* out){
    pipeline::engine e;
    e.parse("{\"1\": {\"pre\": [0], \"fid\": \"exampleudf\"}, \"2\": {\"pre\": [0], \"fid\": \"exampleudf\"}, \"3\": {\"pre\": [1, 2], \"fid\": \"exampleudf\"}}");
    e = 1;
    e();
    COUT << std::any_cast<int>(e[3]) << "\n";
    return 0;
}

int test_G(std::istream* in, std::ostream* out){
    pipeline::G g;
    std::string j;
    if(!std::getline(CIN, j)){
        COUT << "GETLINE ERROR!\n";
        return 1;
    }
    g.readG(j);
    std::string debug = std::move(g.debug());
    COUT << debug;
    return 0;
}

int test_pipeline_graph(std::istream* in, std::ostream* out){
    pipeline::engine e;
    std::string j1, j2, j3;
    if(!std::getline(CIN, j1)){//j1把"nodes"写成了"node"
        COUT << "GETLINE ERROR!\n";
        return 1;
    }
    if(!std::getline(CIN, j2)){//j2把某个"nid"写成了"nidbug"(故意的)
        COUT << "GETLINE ERROR!\n";
        return 1;
    }
    if(!std::getline(CIN, j3)){//j3是一个完全正常的json
        COUT << "GETLINE ERROR!\n";
        return 1;
    }
    //注意jsonparseudf都是相同的, 都是没有问题的。
    //注意由于没有使用std::boolalpha, 输出0代表false, 输出1代表true.
    e.parse("{\"parallel\": true, \"1\": {\"pre\": [0], \"fid\": \"jsonparseudf\"}, \"2\": {\"pre\": [1], \"fid\": \"graphudf\"}}");
    COUT << "[Using graphudf]run result of j1: " << e(j1) << "\n";
    /*
    e(j1) == 1
    程序进入到这里的if中:
    if(!j.contains("nodes")){
        //这个udf专门提取nodes
        g.set_valid(false);
        return g;
    }
    虽然g.valid == false, 但对应的std::any时有值的, 不会触发
    if(!storage[idx].has_value()){
        return false;
    }
    导致返回false
    */
    COUT << "[Using graphudf]run result of j2: " << e(j2) << "\n"; //1
    COUT << "[Using graphudf]run result of j3: " << e(j3) << "\n";//1, j3完全正常, 无论如何都返回1 (true)
    COUT << "e.parallel (should be 1)==" << e.is_parallel() << "\n";

    e.parse("{\"parallel\": false, \"1\": {\"pre\": [0], \"fid\": \"jsonparseudf\"}, \"2\": {\"pre\": [1], \"fid\": \"graphudf\"}}");
    COUT << "[Using graphudf]run result of j1: " << e(j1) << "\n";
    COUT << "[Using graphudf]run result of j2: " << e(j2) << "\n"; //1
    COUT << "[Using graphudf]run result of j3: " << e(j3) << "\n";//1, j3完全正常, 无论如何都返回1 (true)
    COUT << "e.parallel (should be 0)==" << e.is_parallel() << "\n";

    e.parse("{\"parallel\": true, \"1\": {\"pre\": [0], \"fid\": \"jsonparseudf\"}, \"2\": {\"pre\": [1], \"fid\": \"graphudf2\"}}");
    COUT << "[Using graphudf2]run result of j1: " << e(j1) << "\n";//0
    /*
    程序进入到这里的if中:
    std::any a;
    if(!j.contains("nodes")){
        //这个udf专门提取nodes
        g.set_valid(false);
        return a;
    }
    返回了一个空的any, 导致
    storage[idx] = std::move(id2f[idx]->operator()(va, gs));
    中storage[idx].has_value() == false
    从而进入以下if
    if(!storage[idx].has_value()){
        return false;
    }
    返回0.
    */
    COUT << "[Using graphudf2]run result of j2: " << e(j2) << "\n";//1
    COUT << "[Using graphudf2]run result of j3: " << e(j3) << "\n";//1, j3完全正常, 无论如何都返回1
    COUT << "e.parallel (should be 1)==" << e.is_parallel() << "\n";

    e.parse("{\"parallel\": false, \"1\": {\"pre\": [0], \"fid\": \"jsonparseudf\"}, \"2\": {\"pre\": [1], \"fid\": \"graphudf2\"}}");
    COUT << "[Using graphudf2]run result of j1: " << e(j1) << "\n";//0
    COUT << "[Using graphudf2]run result of j2: " << e(j2) << "\n";//1
    COUT << "[Using graphudf2]run result of j3: " << e(j3) << "\n";//1, j3完全正常, 无论如何都返回1
    COUT << "e.parallel (should be 0)==" << e.is_parallel() << "\n";

    e.parse("{\"1\": {\"pre\": [0], \"fid\": \"jsonparseudf\"}, \"2\": {\"pre\": [1], \"fid\": \"graphudf3\"}}");
    COUT << "[Using graphudf3]run result of j1: " << e(j1) << "\n";//0
    COUT << "[Using graphudf3]run result of j2: " << e(j2) << "\n";//0
    /*
    在graphudf3中:
    这里由于把"nid"写成了"nidbug", g.readG(j["nodes"]);会导致g.valid == false, 因为:
    if(!contains(tmpe, S_NID)){//S_NID就是"nid", 找不到"nid"(只有"nidbug")会导致这里valid为false
        valid = false;
        WARNING(JSON_PARSE_ERROR);
    }
    在仿函数的return语句中:
    return g.get_valid() ? std::any(std::move(g)): std::any();
    绝对会返回一个空的std::any(), 因为g.get_valid()变成了false。这样又触发了
    if(!storage[idx].has_value()){
        return false;
    }
    返回0.
    目前engine的提示还做得不好。
    */
    COUT << "[Using graphudf3]run result of j3: " << e(j3) << "\n";//1
    COUT << "e.parallel (should be 1)==" << e.is_parallel() << "\n";//1

    e.parse("{\"parallel\": false, \"1\": {\"pre\": [0], \"fid\": \"jsonparseudf\"}, \"2\": {\"pre\": [1], \"fid\": \"graphudf3\"}}");
    COUT << "[Using graphudf3]run result of j1: " << e(j1) << "\n";//0
    COUT << "[Using graphudf3]run result of j2: " << e(j2) << "\n";//0
    COUT << "[Using graphudf3]run result of j3: " << e(j3) << "\n";//1
    COUT << "e.parallel (should be 0)==" << e.is_parallel() << "\n";//0
    return 0;
}