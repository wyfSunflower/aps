#ifndef TEST_ENGINE_H
#define TEST_ENGINE_H
#include <string>
#include <functional>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "../util/util.h"
#define IO_FAIL -1
int test(std::string&& infile, std::string&& outfile, std::function<int(std::istream*, std::ostream*)> fn);
int test_engine(std::istream* in, std::ostream* out);
#endif