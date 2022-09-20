#include "protos/graph.pb.h"
#include "nlohmann/json.hpp"
#include "custom/exampleudf.h"
#include "global/global.h"
#include "engine/engine.h"
#include "util/util.h"
#include "tests/test.h"
#include <iostream>
using namespace std;

int main(void){
    //输入输出都在build文件夹
    test("test1.txt", "out1.txt", test_engine);
    test("test1.txt", "out2.txt", test_pipeline1);
    test("test1.txt", "out3.txt", test_pipeline2_withtimeguard);
    test("test1.txt", "out4.txt", test_pipeline3_withtimeguard);
    test("test2.txt", "out5.txt", test_G);
    test("test3.txt", "out6.txt", test_pipeline_graph);
    test("test3.txt", "out7.txt", test_copy);
    printf("test_retry1\n");
    test("", "out8.txt", test_retry1);
    printf("test_retry2\n");
    test("", "out9.txt", test_retry2);
    printf("test_retry3\n");
    test("", "out10.txt", test_retry3);
    printf("test_retrybug\n");
    test("", "out11.txt", test_retrybug);//测试之前串行版本重试存在的bug
    printf("test_retrynotwork\n");
    test("", "", test_retrynotwork);//测试一种不太合理的情况, 看程序是否会崩溃: 前驱节点A计算失败后, 重试A的后继节点。这种情况在业务中绝对不应该出现, 应该只能重试A的前驱节点, 重试A的后继节点根本没意义, 因为A的后继节点根本没算过!
    printf("test_anyhelper\n");
    test("", "", test_anyhelper);
    return 0;
}