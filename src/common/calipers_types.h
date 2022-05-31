#ifndef CALIPERS_TYPES_H
#define CALIPERS_TYPES_H

#include "graph_util.h"


enum CacheType
{
    TraceC, // Provided by the trace
    IdealC,
    StatisticalC,
    RealC
};


enum BranchPredictorType
{
    TraceB, // Provided by the trace
    StatisticalB
};


// An ISA might not need all the execution types defined below
enum ExecutionType
{
    IntBase,
    IntMul,
    IntDiv,
    FpBase,
    FpMul,
    FpDiv,
    Load,
    Store,
    BranchCond,
    BranchUncond,
    Syscall,
    Atomic,
    Other
};


// Resource types that may cause structural hazards
enum Resource
{
    RscFetch,
    RscDispatch,
    RscIssue,
    RscMemIssue,
    RscCommit,
    RscMemCommit,
    RscIntAlu,
    RscIntMul,
    RscIntDiv,
    RscIntMulDiv,
    RscFpu,
    RscFpAlu,
    RscFpMul,
    RscFpDiv,
    RscFpMulDiv,
    RscLsu,
};


// Queue types that may cause structural hazards
enum QueueResource
{
    RscInstrQ,
    RscLQ,
    RscSQ,
};


typedef struct INSTRUCTION
{
    uint64_t pc;
    uint32_t bytes;
    uint32_t fetchCycles;
    uint32_t lsCycles;
    bool mispredicted;

    int executionType; // From the ExecutionType enum
    // If an instruction needs multiple execution
    // units, define executionType as an arrays

    uint32_t regReadCount;
    int regRead[MAX_REG_RD];

    uint32_t regWriteCount;
    int regWrite[MAX_REG_WR];

    uint32_t memLoadCount;
    uint64_t memLoadBase;
    uint32_t memLoadLength;

    uint32_t memStoreCount;
    uint64_t memStoreBase;
    uint32_t memStoreLength;
} Instruction;


// A container of different types of instructions
// (Used, e.g., for calculating the breakdown of critical path instructions)
typedef struct INSTRUCTION_TYPES
{
    Vector intInstructions;
    Vector fpInstructions;
    Vector loadInstructions;
    Vector storeInstructions;
    Vector branchInstructions;
    Vector otherInstructions;
} InstructionTypes;


// A container of different types of cycles
// (Used, e.g., for calculating the breakdown of critical path cycles)
typedef struct CYCLE_TYPES
{
    Vector goodFetchHitCycles;
    Vector goodFetchMissCycles;
    Vector badFetchHitCycles;
    Vector badFetchMissCycles;
    Vector decodeCycles;
    Vector dispatchCycles;
    Vector intCycles;
    Vector fpCycles;
    Vector lsCycles;
    Vector loadL1HitCycles;
    Vector loadL2HitCycles;
    Vector loadMissCycles;
    Vector storeL1HitCycles;
    Vector storeL2HitCycles;
    Vector storeMissCycles;
    Vector branchCycles;
    Vector syscallCycles;
    Vector atomicCycles;
    Vector otherCycles;
    Vector commitCycles;
} CycleTypes;



// Different vertex types for different stages of an instruction in the core pipeline
enum VertexType
{
    InstrFetch = 0,
    InstrDispatch = 1,
    InstrExecute = 2,
    MemExecute = 3,
    InstrCommit = 4,
    Last = 4
};

#endif // CALIPERS_TYPES_H
