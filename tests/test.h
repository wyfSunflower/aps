#ifndef TEST_H
#define TEST_H
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
int test(const std::string& infile, const std::string& outfile, std::function<int(std::istream*, std::ostream*)> fn);
int test_engine(std::istream* in, std::ostream* out);
int test_pipeline1(std::istream* in, std::ostream* out); //相加求和
int test_pipeline2_withtimeguard(std::istream* in, std::ostream* out);
int test_pipeline3_withtimeguard(std::istream* in, std::ostream* out);
int test_G(std::istream* in, std::ostream* out);
int test_pipeline_graph(std::istream* in, std::ostream* out); //解析json并建图
int test_copy(std::istream* in, std::ostream* out);
int test_retry1(std::istream* in, std::ostream* out);
int test_retry2(std::istream* in, std::ostream* out);
int test_retry3(std::istream* in, std::ostream* out);
int test_retrybug(std::istream* in, std::ostream* out);
int test_retrynotwork(std::istream* in, std::ostream* out);
int test_anyhelper(std::istream* in, std::ostream* out);
#endif