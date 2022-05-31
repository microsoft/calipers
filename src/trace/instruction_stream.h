#ifndef INSTRUCTION_STREAM_H
#define INSTRUCTION_STREAM_H

#include <string>
#include <fstream>

#include "calipers_types.h"

using namespace std;

/**
 * The base class for reading a stream of instructions from a trace file
 * Dervied classes define how the trace is parsed based on the ISA specifications.
 */
class InstructionStream
{
  protected:
    ifstream traceFile;
    bool traceBP; // Whether the trace provides branch prdecition outcomes
    bool traceICache; // Whether the trace provides I-Cache access cycles
    bool traceDCache; // Whether the trace provides D-Cache access cycles
    Instruction instr;

  public:
    InstructionStream(string trace_file_name, bool trace_bp,
                      bool trace_icache, bool trace_dcache);
    virtual Instruction* next() = 0;
};

#endif // INSTRUCTION_STREAM_H
