#include "engine.h"
#include <iostream>
#include <queue>
#include "../custom/exampleudf.h"
#include "../custom/graphudf.h"
#include "../custom/jsonparseudf.h"
#include "../custom/retryudf.h"
#include "../util/util.h"

namespace pipeline{
    void engine::reg(){
        REGISTER(exampleudf);
        REGISTER(exampleudf2);
        REGISTER(graphudf);
        REGISTER(graphudf2);
        REGISTER(graphudf3);
        REGISTER(jsonparseudf);
        REGISTER(retryudf);
        REGISTER(retryudf2);
        REGISTER(retryudf3);
    }

    int engine::parse(nlohmann::json& graph){
        //硬编码
        if(!initial) clear(); //如果不是最开始的状态, 清空
        parallel = true;
        initial = false;
        parsed = false; //不能保证parse成功, 先将parsed置为false, 成功再改为true.
        log = "";
        if(graph.contains("parallel") && CHECK_TYPE(graph["parallel"], "bool")){
            parallel = (graph["parallel"].get<bool>() != 0);
        }
        for(auto it = graph.begin(); it != graph.end(); ++it){
            std::string key = it.key();
            if(key == "parallel"){
                continue;
            }
            bool ok = true;
            size_t k = getNonNegativeInteger(key, ok);
            if(!ok){
                WARNING(JSON_PARSE_ERROR);
            }
            if(k == 0){
                WARNING(ROOT_0_HAS_PRE);
            }
            try{
                nlohmann::json& value = it.value();
                if(!contains(value, "fid", "pre")){
                    WARNING(JSON_PARSE_ERROR);
                }
                nlohmann::json& fidj = value["fid"];
                nlohmann::json& prea = value["pre"];
                if(fidj.is_null() || !CHECK_TYPE(fidj, "string")){
                    WARNING(JSON_PARSE_ERROR);
                }
                if(!prea.is_array()){
                    WARNING(JSON_PARSE_ERROR);
                }
                std::string fids = fidj.get<std::string>();
                if(custom_invoke.find(fids) == custom_invoke.end()){
                    WARNING(CUSTOM_INVOKE_FUNCTION_NOT_FOUND);
                }
                id2fname[k] = fids;
                id2f[k] = custom_invoke[fids]();
                int sz = prea.size();
                for(int i = 0; i < sz; ++i){
                    nlohmann::json& element = prea[i];
                    if(!CHECK_TYPE(element, "unsigned")){
                        WARNING(JSON_PARSE_ERROR);
                    }
                    size_t prei = element.get<size_t>();
                    if(k == prei){
                        printf("k==prei==%zu\n", k);
                        WARNING(DEADLOCK_ERROR);
                    }
                    ch[prei].push_back(k);
                    pr[k].push_back(prei);
                }
            }catch(nlohmann::json::parse_error& ex){
                WARNING(JSON_PARSE_ERROR);
            }
        }//for

        std::map<size_t, size_t> idg;//入度
        idg[root] = 0;
        id2layer[root] = 0;
        layer2ids[0] = {root};
        for(auto it = pr.begin(); it != pr.end(); ++it){
            std::vector<size_t>& tmp = it -> second;
            for(auto tmppre: tmp){
                if(tmppre != 0 && pr[tmppre].size() == 0){
                    printf("pr[%zu].size()==%zu\n", tmppre, pr[tmppre].size());
                    WARNING(NOT_CONNECTED);
                }
            }
            idg[it->first] = it -> second.size();
        }

        //拓扑排序
        std::queue<std::pair<size_t, size_t>> q;
        q.push({root, 0});
        size_t num = 0;
        while(!q.empty()){
            auto [u, layerid] = q.front();
            q.pop();
            id2layer[u] = layerid;
            layer2ids[layerid].insert(u);
            for(int v: ch[u]){
                --idg[v]; //降低后继节点的入度
                if(idg[v] == 0){//如果后继节点的入度为0, 入队
                    q.push({v, layerid+1});
                }
            }
            ++num; //统计加入拓扑排序的节点数
        }
        if(num != pr.size() + 1){
            //从拓扑排序中出队列的节点数目(num)应该等于总的节点数目
            //上面已经校验过, 凡是pr右侧出现的节点都在pr左侧出现过
            //因此总节点数为pr.size() + 1
            WARNING(TOPOLOGICAL_SORTING_FAILED);
        }
        parsed = true;
        return PARSE_OK;
    }

    int engine::parse(std::string& s){
        return parse(std::move(s));
    }

    int engine::parse(std::string&& s){
        nlohmann::json j;
        try{
            j = nlohmann::json::parse(s);
        }catch(nlohmann::json::parse_error& ex){
            WARNING(JSON_PARSE_ERROR);
            return JSON_PARSE_ERROR;
        }
        return parse(j);
    }

    std::string engine::debug(){
        std::string res;
        res += "root==" + std::to_string(root) + ", layer(" + std::to_string(root) + ")==" + std::to_string(id2layer[root]) + "\n";
        for(auto it = pr.begin(); it != pr.end(); ++it){
            res += "id==" + std::to_string(it->first) + ", layer(" + std::to_string(it->first) + ")==" + std::to_string(id2layer[it->first]) + ", pre==" + stlout(pr[it->first]) + "\n";
        }
        res += "Debug layers:\n";
        res += stlout(layer2ids) + "\n";
        return res;
    }

    void engine::copy(size_t src, size_t dst, bool use_move_semantics){
        if(storage.find(src) != storage.end()){
            if(!use_move_semantics) storage[dst] = storage[src];
            else storage[dst] = std::move(storage[src]);
        }
    }
    
    void engine::initialize_priority_queue(const std::vector<size_t>& startnodes, std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>>& pq, std::set<size_t>& inpq, size_t call_layer, bool run_already_calculated){
        //pair形如(layerid, nodeid)
        //先按拓扑排序的层排序, 再按顶点编号排序。其实顶点编号可以不用排序, 但层**一定**要排序, 所以干脆放到pair里面去
        
        for(size_t c: startnodes){
            if(inpq.find(c) == inpq.end() && (c == 0 || (run_already_calculated && id2f[c]->verdict[0] != NOT_CALCULATED) || (!run_already_calculated && id2f[c]->verdict[0] == NOT_CALCULATED))){
                pq.push({id2layer[c], c});
                inpq.insert(c); //防止重复加入队列
            }
        }
    }

    bool engine::run_s_internal(const std::vector<size_t>& startnodes, bool runninglog, size_t call_layer, bool run_already_calculated){
        /*
        startnodes: 运算开始的节点
        runninglog: true-记录日志 false-不记录日志
        call_layer: 调用层级, 初始为0
        terminate: 当terminate对应的节点计算完成后推出, 不必等所有节点计算完成。terminate==-1代表完整运行计算图
        */
        std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> pq;
        std::set<size_t> inpq;
        if(runninglog){
            log += DBGSTR + "[" + timeStr() + " run_s_internal]: startnodes==" + stlout(startnodes) + ", call_layer==" + std::to_string(call_layer) + ".\n";
        }
        initialize_priority_queue(startnodes, pq, inpq, call_layer, run_already_calculated);
        while(!pq.empty()){
            auto [layer, idx] = pq.top();
            pq.pop();
            if(runninglog) log += "[" + timeStr() + " run_s_internal]: Handle {" + std::to_string(layer) + " (layer), " + std::to_string(idx) + " (idx)}. pq.size()==" + std::to_string(pq.size()) + "\n";
            if(idx != root){
                for(size_t x: pr[idx]){
                    if(!storage[x].has_value()){
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: launch(" + std::to_string(idx) + ") failed because storage[" + std::to_string(x) + "] does not hold a value!\n";
                        return false; 
                    }
                }
                std::vector<std::any*> va;
                tf(va, idx);
                id2f[idx]->verdict[call_layer] = CORRECT;
                std::any&& tmp = id2f[idx]->operator()(va, g, idx, call_layer);
                if(!tmp.has_value()){
                    if(runninglog) log += DBGSTR + "[" + timeStr() + " run_s_internal]: Handle {" + std::to_string(layer) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} failed because result (type any).has_value() == false!\n";
                    return false;
                }else if(id2f[idx]->verdict[call_layer] == WRONG){
                    if(runninglog) log += DBGSTR + "[" + timeStr() + " run_s_internal]: Handle {" + std::to_string(layer) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} failed because verdict==WRONG! Call " + std::to_string(idx) + " (" + id2fname[idx] + ") verdict==WRONG!\n";
                    ++id2f[idx]->failtimes;
                    ++failtimes;
                    bool res = id2f[idx]->retry(this, idx, call_layer);
                    retryresult[{call_layer, idx}] = res;
                }else if(id2f[idx]->verdict[call_layer] == NOT_CALCULATED){
                    if(runninglog) log += DBGSTR + "[" + timeStr() + " run_s_internal]: Handle {" + std::to_string(layer) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} failed because verdict==NOT_CALCULATED! Call " + std::to_string(idx) + " (" + id2fname[idx] + ") verdict==NOT_CALCULATED! Now return false!\n";
                    return false;
                }
                log += DBGSTR +"[" + timeStr() + " run_s_internal]: Handle {" + std::to_string(layer) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} successful.\n";
                if(id2f[idx]->verdict[call_layer] == CORRECT) {
                    storage[idx] = tmp;
                    if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: Handle {" + std::to_string(layer) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} successful. Verdict==" + std::to_string(id2f[idx]->verdict[call_layer]) + "[Stored]\n";
                }else{
                    if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: Handle {" + std::to_string(layer) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} unsuccessful.\n";
                }
            }
            for(size_t c: ch[idx]){
                if(inpq.find(c) == inpq.end() && (idx == root || (run_already_calculated && id2f[c]->verdict[0] != NOT_CALCULATED) || (!run_already_calculated && id2f[c]->verdict[0] == NOT_CALCULATED))){
                    pq.push({id2layer[c], c});
                    inpq.insert(c);//避免重复加入队列
                }
            }
        }
        return true;
    }

    bool engine::run_p_internal(const std::vector<size_t>& startnodes, bool runninglog, size_t call_layer, bool run_already_calculated){
        /*
        startnodes: 运算开始的节点
        runninglog: true-记录日志 false-不记录日志
        call_layer: 调用层级, 初始为0
        */
        auto async_parallel = [this, call_layer](size_t idx)->std::any{
            std::vector<std::any*> va;
            tf(va, idx);
            id2f[idx]->verdict[call_layer] = CORRECT;
            return id2f[idx]->operator()(va, g, idx, call_layer);
        };

        std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> pq;
        std::set<size_t> inpq;
        if(runninglog){
            log += "[" + timeStr() + " run_p_internal]: startnodes==" + stlout(startnodes) + ", call_layer==" + std::to_string(call_layer) + ".\n";
        }
        initialize_priority_queue(startnodes, pq, inpq, call_layer, run_already_calculated);
        while(!pq.empty()){
            std::vector<std::pair<size_t, size_t>> samelayer;
            auto t = pq.top();
            if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: samelayer.push_back(" + stlout(t) + "), pq.size()==" + std::to_string(pq.size()) + "\n";
            pq.pop();
            //在同一层的一起出队列, 入samelayer
            samelayer.push_back(t);
            while(!pq.empty() && pq.top().first == t.first){
                samelayer.push_back(pq.top());
                if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: samelayer.push_back(" + stlout(pq.top()) + "), pq.size()==" + std::to_string(pq.size()) + "\n";
                pq.pop();
            }
            //samelayer上的并行计算
            std::map<size_t, std::future<std::any>> idx2f;
            for(auto layer_idx_pair: samelayer){
                size_t idx = layer_idx_pair.second;
                if(idx != root){
                    if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: launch(" + std::to_string(idx) + ").\n";
                    for(size_t x: pr[idx]){
                        if(!storage[x].has_value()){
                            if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: launch(" + std::to_string(idx) + ") failed because storage[" + std::to_string(x) + "] does not hold a value!\n";
                            return false; 
                        }
                    }
                    idx2f[idx] = std::async(async_parallel, idx);
                }
            }
            for(auto layer_idx_pair: samelayer){
                size_t idx = layer_idx_pair.second;
                if(idx != root){
                    std::any&& tmp = idx2f[idx].get();
                    if(!tmp.has_value()){
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} failed because result (type any).has_value() == false!\n";
                        return false;
                    }else if(id2f[idx]->verdict[call_layer] == WRONG){
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} failed because verdict==WRONG! Call " + std::to_string(idx) + " (" + id2fname[idx] + ") verdict==WRONG!\n";
                        ++id2f[idx]->failtimes;
                        ++failtimes;
                        bool res = id2f[idx]->retry(this, idx, call_layer);
                        retryresult[{call_layer, idx}] = res;
                    }else if(id2f[idx]->verdict[call_layer] == NOT_CALCULATED){
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} failed because verdict==NOT_CALCULATED! Call " + std::to_string(idx) + " (" + id2fname[idx] + ") verdict==NOT_CALCULATED! Now return false!\n";
                        return false;
                    }
                    if(id2f[idx]->verdict[call_layer] == CORRECT) {
                        storage[idx] = tmp;
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} successful. Verdict==" + std::to_string(id2f[idx]->verdict[call_layer]) + "[Stored]\n";
                    }else{
                        if(runninglog) log += DBGSTR + "[" + timeStr() + " run_p_internal]: Handle {" + std::to_string(layer_idx_pair.first) + " (layer), " + std::to_string(idx) + " (idx), " + std::to_string(call_layer) + " (call_layer)} unsuccessful.\n";
                    }
                }
                for(size_t c: ch[idx]){
                    if(inpq.find(c) == inpq.end() && ((run_already_calculated && id2f[c]->verdict[0] != NOT_CALCULATED) || (!run_already_calculated && id2f[c]->verdict[0] == NOT_CALCULATED))){
                        pq.push({id2layer[c], c});
                        inpq.insert(c);//避免重复加入队列
                        log += DBGSTR + "[" + timeStr() + " run_p_internal]: Push" + stlout(std::pair<size_t, size_t>(id2layer[c], c)) + ".\n";
                    }
                }
            }
        }
        return true;
    }

    bool engine::run_s(){
        if(!parsed) return false;
        for(auto it = id2f.begin(); it != id2f.end(); ++it){
            it->second->isparallel = false;
            it->second->verdict[0] = NOT_CALCULATED;
        }
        failtimes = 0;
        log = "";
        std::vector<size_t> startnodes = {root};
        return run_s_internal(startnodes, WITHLOG, 0, false);
    }

    bool engine::run_p(){
        if(!parsed) return false;
        for(auto it = id2f.begin(); it != id2f.end(); ++it){
            it->second->isparallel = true;
            it->second->verdict[0] = NOT_CALCULATED;
        }
        failtimes = 0;
        log = "";
        std::vector<size_t> startnodes = {root};
        return run_p_internal(startnodes, WITHLOG, 0, false);
    }

    bool engine::operator()(){
        if(!parsed){
            return false;
        }
        if(parallel){
            return run_p();
        }else{
            return run_s();
        }
        return false;
    }
    
    int G::readG(nlohmann::json& j){
        valid = true;
        if(!initial){
            V.clear();
        }
        if(!j.is_array()){
            valid = false;
            WARNING(JSON_PARSE_ERROR);
        }
        int sz = j.size();
        for(int i = 0; i < sz; ++i){
            //读点
            nlohmann::json& tmp = j[i];
            if(!contains(tmp, S_ID, S_X, S_Y)){
                valid = false;
                WARNING(JSON_PARSE_ERROR);
            }
            graph::vertex v;
            v.set_id(tmp[S_ID].get<unsigned>());
            v.set_x(tmp[S_X].get<int>());
            v.set_y(tmp[S_Y].get<int>());
            int z = getd(tmp, S_Z, 0);
            unsigned layerid = getd(tmp, S_LAYERID, 0u);
            unsigned type = getd(tmp, S_TYPE, 0u);
            v.set_z(z);
            v.set_layerid(layerid);
            v.set_type(type);
            V[v.id()] = std::move(v);
        }
        for(int i = 0; i < sz; ++i){
            //读边
            nlohmann::json& tmp = j[i];
            unsigned id = tmp[S_ID].get<unsigned>();
            std::map<int, std::set<size_t>>& thetahash_id = thetahash[id];
            if(!contains(tmp, S_OUTEDGES)) continue;
            nlohmann::json& outedges = tmp[S_OUTEDGES];
            if(!outedges.is_array()){
                valid = false;
                WARNING(JSON_PARSE_ERROR);
            }
            int sza = outedges.size();
            for(int ed = 0; ed < sza; ++ed){
                graph::edge* e = V[id].add_e();
                nlohmann::json& tmpe = outedges[ed];
                if(!contains(tmpe, S_NID)){
                    valid = false;
                    WARNING(JSON_PARSE_ERROR);
                }
                e -> set_edgeid(ed);
                e -> set_startid(id);
                unsigned nid = tmpe[S_NID].get<unsigned>();
                if(V.find(nid) == V.end()){
                    valid = false;
                    WARNING(ID_NOT_FOUND);
                }
                e -> set_endid(nid);
                e -> add_x(V[id].x());
                e -> add_y(V[id].y());
                e -> add_z(V[id].z());
                bool zsame = true;
                int prevz = e -> z(0);
                {
                    //业务逻辑
                    if(contains(tmpe, S_CURVE)){
                        e -> set_type(BEZIER);
                        nlohmann::json& curve_arr = tmpe[S_CURVE];
                        if(!curve_arr.is_array()){
                            valid = false;
                            WARNING(JSON_PARSE_ERROR);
                        }
                        int szc = curve_arr.size();
                        std::vector<nlohmann::json> cps; //control points
                        for(int i = 0; i < szc; ++i){
                            if(!contains(curve_arr[i], S_IDX, S_X, S_Y)){
                                valid = false;
                                WARNING(JSON_PARSE_ERROR);
                            }
                            cps.push_back(curve_arr[i]);
                        }
                        std::sort(cps.begin(), cps.end(), [](const nlohmann::json& x, const nlohmann::json& y){
                            return x[S_IDX].get<unsigned>() < y[S_IDX].get<unsigned>();
                        }); //按照控制点的IDX排序
                        for(int i = 0; i < szc; ++i){
                            nlohmann::json& curve_p = cps[i];
                            e -> add_x(curve_p[S_X].get<int>());
                            e -> add_y(curve_p[S_Y].get<int>());
                            int z = getd(curve_p, S_Z, prevz);
                            e -> add_z(z);
                            if(z != prevz) zsame = false;
                        }
                    }else{
                        e -> set_type(STRAIGHT);
                    }
                    e -> add_x(V[nid].x());
                    e -> add_y(V[nid].y());
                    e -> add_z(V[nid].z());
                    if(V[nid].z() != prevz) zsame = false;
                }

                int xsize = e -> x_size();
                //STRAIGHT EDGE: xsize == 2
                //BEZIER EDGE: xsize >= 2
                e -> set_zsame((int)zsame);
                if(zsame){
                    int diff1x = e -> x(1) - e -> x(0);
                    int diff1y = e -> y(1) - e -> y(0);
                    e -> set_theta1(gettheta(diff1x, diff1y));
                    int diff2x = e -> x(xsize-1) - e -> x(xsize-2);
                    int diff2y = e -> y(xsize-1) - e -> y(xsize-2);
                    e -> set_theta2(gettheta(diff2x, diff2y));
                    thetahash_id[e->theta1()].insert(e->edgeid());
                }
            }
        }
        return PARSE_OK;
    }

    int G::readG(std::string& s){
        return readG(std::move(s));
    }

    int G::readG(std::string&& s){
        nlohmann::json j;
        try{
            j = nlohmann::json::parse(s);
        }catch(nlohmann::json::parse_error& ex){
            WARNING(JSON_PARSE_ERROR);
            return JSON_PARSE_ERROR;
        }
        return readG(j);
    }

    std::string G::debug(){
        std::map<size_t, std::string> typemap;
        typemap[STRAIGHT] = "STRAIGHT";
        typemap[BEZIER] = "BEZIER";
        std::string res;
        res += std::to_string(V.size()) + " vertices in total.\n";
        for(auto it = V.begin(); it != V.end(); ++it){
            res += "======[id:" + std::to_string(it->first) + "]======\n";
            const graph::vertex& v = it->second;
            res += "coordinate: (" + std::to_string(v.x()) + ", " + std::to_string(v.y()) + ", " + std::to_string(v.z()) + ", " + std::to_string(v.layerid()) + ") [x, y, z, layerid]\n";
            res += "type: " + std::to_string(v.type()) + "\n";
            res += "Debugging edges, size==" + std::to_string(v.e_size()) + "\n\n";
            for(int i = 0; i < v.e_size(); ++i){
                const graph::edge& e = v.e(i);
                res += "(" + std::to_string(e.edgeid()) + ", " + std::to_string(e.startid()) + ", " + std::to_string(e.endid()) + ") [edgeid, startid, endid]\n";
                res += "[Edgeid: " + std::to_string(e.edgeid()) + "]: zsame==" + std::to_string(e.zsame()) + ", type==" + std::to_string(e.type()) + ", theta1==" + std::to_string(e.theta1()) + ", theta2==" + \
                    std::to_string(e.theta2()) + "\n";
                res += "Points through which this edge passes:\n";  
                for(int j = 0; j < e.x_size(); ++j){
                    res += "(" + std::to_string(e.x(j)) + ", " + std::to_string(e.y(j)) + ", " + std::to_string(e.z(j)) + ") [x, y, z]\n";
                }
                res += "\n";
            }
        }
        res += "DebugThetaHash:\n";
        for(auto it = thetahash.begin(); it != thetahash.end(); ++it){
            res += "======[id:" + std::to_string(it -> first) + "]======\n";
            const std::map<int, std::set<size_t>>& thetahash_id = it -> second;
            for(auto it2 = thetahash_id.begin(); it2 != thetahash_id.end(); ++it2){
                std::string edgestr;
                size_t sz = it2 -> second.size(), i = 0;
                for(size_t e: it2 -> second){
                    edgestr += "{\"edgeid\": \"" + std::to_string(e) + "\", \"endid\": \"" + std::to_string(V[it->first].e(e).endid())+ "\"}";
                    ++i;
                    if(i != sz){
                        edgestr += ", ";
                    }
                }
                res += "theta: " + std::to_string(it2->first) + ", edges==[" + edgestr + "]\n";
            }
        }
        res += "Finished.\n";
        return res;
    }
}