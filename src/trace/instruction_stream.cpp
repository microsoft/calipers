#include <iostream>

#include "calipers_defs.h"
#include "instruction_stream.h"

using namespace std;

InstructionStream::InstructionStream(string trace_file_name, bool trace_bp,
                                     bool trace_icache, bool trace_dcache) :
                                     traceBP(trace_bp),
                                     traceICache(trace_icache),
                                     traceDCache(trace_dcache)
{
    traceFile.open(trace_file_name);
    if (!traceFile.is_open())
    {
        CALIPERS_ERROR("Unable to open the trace file");
    }
}
