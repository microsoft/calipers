#ifndef STATISTICAL_BP_H
#define STATISTICAL_BP_H

#include <stdint.h>

#include "calipers_util.h"
#include "branch_predictor.h"

using namespace std;

/**
 * A statistical/stochastic branch predictor with fixed accuracy
 */
class StatisticalBp : public BranchPredictor
{
  private:
    float accuracy;

  public:
    StatisticalBp(string config)
    {
        vector<string> config_vec = split_string(config, ':');

        if (config_vec.size() != 2)
        {
            CALIPERS_ERROR("Invalid configuration for the statistical branch predictor");
        }

        accuracy = stof(config_vec[0]);
        predictionCycles = stoi(config_vec[1]);

    }

    bool mispredicted(uint64_t pc)
    {
        int r = rand() % 1000;
        return (r >= 10 * accuracy);
    }
};

#endif // STATISTICAL_BP_H
