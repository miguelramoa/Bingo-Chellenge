#pragma once
#include <cstring>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
#include <time.h>
#include "../Commons/Commons.h"

const int ch_MAX = 26;
std::string RandomString(int ch);
std::string PrintGameCard(std::vector<int> gameCard);
const int str2int(const std::string &s);
char* make_copy(const char *s);