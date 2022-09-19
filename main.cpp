#include "protos/graph.pb.h"
#include "nlohmann/json.hpp"
#include "custom/exampleudf.h"
#include "global/global.h"
#include "engine/engine.h"
#include "util/util.h"
#include "tests/test.h"
#include <bits/stdc++.h>
using namespace std;

int main(void){
    //输入输出都在build文件夹
    test("test1.txt", "out1.txt", test_engine);
    test("test1.txt", "out2.txt", test_pipeline1);
    test("test1.txt", "out3.txt", test_pipeline2_withtimeguard);
    test("test2.txt", "out4.txt", test_G);
    test("test3.txt", "out5.txt", test_pipeline_graph);
    test("test3.txt", "out6.txt", test_copy);
    printf("test_retry1\n");
    test("", "", test_retry1);
    printf("test_retry2\n");
    test("", "", test_retry2);
    printf("test_retry3\n");
    test("", "", test_retry3);
}