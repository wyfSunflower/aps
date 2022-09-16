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