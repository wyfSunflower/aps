#ifndef TEST_ENGINE_H
#define TEST_ENGINE_H
#include <string>
#include <functional>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "../util/util.h"
#include "../engine/engine.h"
#define IO_FAIL -1
#define CIN (*in)
#define COUT (*out)
int test(std::string&& infile, std::string&& outfile, std::function<int(std::istream*, std::ostream*)> fn);
int test_engine(std::istream* in, std::ostream* out);
int test_pipeline1(std::istream* in, std::ostream* out); //相加求和
int test_G(std::istream* in, std::ostream* out);
int test_pipeline_graph(std::istream* in, std::ostream* out); //解析json并建图
int test_copy(std::istream* in, std::ostream* out);
#endif