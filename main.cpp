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
    test("test1.txt", "", test_engine);
    test("test1.txt", "", test_pipeline1);
}