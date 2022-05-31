#ifndef CALIPERS_UTIL_H
#define CALIPERS_UTIL_H

#include <vector>

#include "calipers_types.h"

using namespace std;

vector<string> split_string(string str, char c);
uint64_t unsigned_diff(uint64_t a, uint64_t b);
void print_instruction(Instruction& instr);

#endif // CALIPERS_UTIL_H
