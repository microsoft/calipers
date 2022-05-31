#ifndef BRANCH_PREDICTOR_H
#define BRANCH_PREDICTOR_H

#include <stdint.h>

/**
 * The base branch predictor class
 */
class BranchPredictor
{
public:
    uint32_t predictionCycles;

    virtual bool mispredicted(uint64_t pc) = 0;
};

#endif // BRANCH_PREDICTOR_H
