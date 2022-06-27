/**
 * Copyright (c) Microsoft Corporation.
 * 
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef O3_CORE_GRAPH_ADVANCED
#define O3_CORE_GRAPH_ADVANCED

#include "graph.h"
#include "calipers_defs.h"
#include "scoreboard.h"

/**
 * An out-of-order processor model based on gem5's DerivO3CPU
 * This is a space-efficient implementation that performs a
 * "sliding-window" analysis, i.e., graph construction and analysis
 * are done (simultaneosly) on a window of size OOO_SLIDIING_WINDOW
 * that slides from the beginning to the end of instructions in the
 * trace.
 */
class O3CoreGraphAdvanced : public Graph
{
  private:
    /*** Microarchitectural parameters ***/

    uint32_t instrBufferSize; // Bandwidth is in instructions per cycle
    uint32_t fetchBandwidth;
    uint32_t dispatchBandwidth;
    uint32_t issueBandwidth;
    uint32_t commitBandwidth;
    uint32_t decodeCycles;
    uint32_t dispatchCycles;
    uint32_t executeToCommitCycles;
    uint32_t predictionCycles;
    uint32_t mispredictionPenalty;
    uint32_t memIssueBandwidth;
    uint32_t memCommitBandwidth;
    int bpType;
    string bpConfig;
    int icacheType;
    string icacheConfig;
    int dcacheType;
    string dcacheConfig;
    Scoreboard scoreboard[VECTOR_WIDTH]; // Also performs bookkeeping


    /*** Bookkeeping ***/

    uint64_t currentIcacheLine;
    uint64_t lastMisprediction;
    uint64_t lastBranch;
    bool previousInstrMispredicted;
    bool previousWasBranch;
    uint64_t linearPC;
    uint64_t lastMemLdSt;
    uint32_t prevExecutionCycles;

    unordered_map<int, pair<uint64_t, uint32_t>> regLastWrittenBy;
    // Key: Register, Value: <Instruction number, Execution cycles>

    unordered_map<int, bool> regLastWrittenByLoad;
    // Key: Register, Value: Whether it was written by a load

    pair<uint64_t,                              // First: Load/store number 
         pair<uint64_t, uint32_t>>* ldStWindow; // Second: <Base, Length> of address
    bool* ldStWindowType; // Is load?
    uint32_t ldStWindowPointer;

    unordered_map<uint64_t, uint32_t> lsCycles;
    // Key: Instruction number % AnalysisWindow, Value: Load/store cycles (UINT32_MAX for invalid)

    unordered_map<uint64_t, uint32_t> executionCycles;
    // Key: Instruction number % AnalysisWindow, Value: Execution cycles (UINT32_MAX for invalid)


    /*** Graph-related data structures ***/

    unordered_map<Vertex, vector<OutgoingEdge>, VertexHash, VertexEqual> graphChildren;
    // graphChildren[v] = Vector of children of Vertex v

    unordered_map<Vertex, vector<IncomingEdge>, VertexHash, VertexEqual> graphParents;
    // graphParents[v] = Vector of parents of Vertex v

    ScheduleSet scheduleOrder[VECTOR_WIDTH];
    // The set(s) of <instruction number, critical path length> pairs sorted based on length

    uint64_t headInstr;
    // The next instruction to be brought into the analysis window

    uint64_t headScheduledInstr;
    // All intructions before headScheduledInstr have been scheduled.

    set<uint64_t> alreadyScheduled[VECTOR_WIDTH];
    // The set(s) of instructions (starting from headScheduledInstr) that have been scheduled

    uint64_t maxSchedInstrNum[VECTOR_WIDTH];
    // The instruction(s) with the greatest number that has been scheduled


    void initBookKeeping();
    void initScoreboard();
    void model(Instruction* instr);
    void modelPipeline(Vertex& fetch_vertex, Vertex& dispatch_vertex,
                       Vertex& execute_vertex, Vertex& mem_vertex,
                       Vertex& commit_vertex, Instruction* instr,
                       uint32_t execution_cycles);
    bool modelMemoryOrderConstraint(Instruction* instr, Vertex& mem_vertex);
    void trackDataDependencies(Instruction* instr,
                               Vertex& execute_vertex, Vertex& mem_vertex);
    pair<uint32_t, bool> modelResourceDependencies();
    void addEdge(Vertex& parent, OutgoingEdge& e);
    void calculateInstructionCriticalPath();
    void updateCriticalPath(uint32_t idx,
                            Vertex* parent1, OutgoingEdge* e1,
                            Vertex* parent2, OutgoingEdge* e2,
                            Vertex* parent3, OutgoingEdge* e3);

  public:
    O3CoreGraphAdvanced(string trace_file_name,
                        string result_file_name,
                        InstructionStream* instr_stream,
                        uint32_t instr_buffer_size, 
                        uint32_t instr_queue_size, 
                        uint32_t fetch_bandwidth,
                        uint32_t dispatch_bandwidth,
                        uint32_t issue_bandwidth,
                        uint32_t commit_bandwidth,
                        uint32_t decode_cycles,
                        uint32_t dispatch_cycles,
                        uint32_t execute_to_commit_cycles,
                        uint32_t prediction_cycles,
                        uint32_t misprediction_penalty,
                        uint32_t mem_issue_bandwidth,
                        uint32_t mem_commit_bandwidth,
                        uint32_t int_alu_count,
                        uint32_t int_mul_div_count,
                        uint32_t fp_alu_count,
                        uint32_t fp_mul_div_count,
                        uint32_t lsu_count,
                        uint32_t lq_qize,
                        uint32_t sq_size,
                        int bp_type,
                        string bp_config,
                        int icache_type,
                        string icache_config,
                        int dcache_type,
                        string dcache_config);
    ~O3CoreGraphAdvanced();
    void run();
};


#endif // O3_CORE_GRAPH_ADVANCED
