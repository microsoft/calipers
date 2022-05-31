#ifndef CALIPERS_DEFS_H
#define CALIPERS_DEFS_H

#include <iostream>
#include <chrono>

using namespace std;

#define CALIPERS_INFO(msg) \
    cerr << "CALIPERS_INFO | " << msg << endl;

#define CALIPERS_WARNING(warn_msg) \
    cerr << "CALIPERS_WARNING | " << warn_msg << endl;

#define CALIPERS_ERROR(error_msg) \
    {cerr << "CALIPERS_ERROR | " << error_msg << endl; exit(-1);}

#define RAND_SEED 27302730

#define TICKS_PER_CYCLE 500 // Access times in the trace are given in ticks.
 
#define CACHE_LINE_BYTES     64
#define CACHE_ADDRESS_ZEROS  6 

#define MAX_REG_RD   3 // Maximum number of registers read
#define MAX_REG_WR   1 // Maximum number of registers written
#define MAX_OPERANDS (MAX_REG_RD + MAX_REG_WR)

#define INO_WINDOW  400
#define MAX_PARENTS 10

#define OOO_HOPPING_WINDOW 10000000
#define OOO_SLIDING_WINDOW 800

#define VECTOR_WIDTH 1

template <class Duration>
using sys_time = chrono::time_point<chrono::system_clock, Duration>;
using sys_nanoseconds = sys_time<chrono::nanoseconds>;


#endif // CALIPERS_DEFS_H
