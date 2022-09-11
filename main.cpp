#include "protos/graph.pb.h"
#include "nlohmann/json.hpp"
#include "custom/exampleudf.h"
#include "global/global.h"
#include "engine/engine.h"
#include "util/util.h"
#include <bits/stdc++.h>
using namespace std;

int main(void){
    pipeline::engine e;
    cout << e.parse("{\"1\":{\"fid\": \"exampleudf\", \"pre\": [1, 5]}}") << "\n";
}