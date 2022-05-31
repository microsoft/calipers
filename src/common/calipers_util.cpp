#include <iostream>

#include <vector>

#include "calipers_util.h"
#include "calipers_types.h"

using namespace std;

vector<string> split_string(string str, char c)
{
    vector<string> v;
    size_t pos = 0;

    while (true)
    {
        size_t char_pos = str.find(c, pos);
        v.push_back(str.substr(pos, char_pos - pos));

        if (char_pos == string::npos)
        {
            break;
        }

        pos = char_pos + 1;
    }

    return v;
}

uint64_t unsigned_diff(uint64_t a, uint64_t b)
{
    if (a > b)
    {
        return a - b;
    }
    else
    {
        return b - a;
    }
}

void print_instruction(Instruction& instr)
{
}
