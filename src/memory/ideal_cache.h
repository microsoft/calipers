#ifndef IDEAL_CACHE_H
#define IDEAL_CACHE_H

#include <stdint.h>

#include "cache.h"

/**
 * An ideal cache with single-cycle loads/stores
 */
class IdealCache: public Cache
{
  public:
    uint32_t loadCycles(uint64_t base, uint32_t length)
    {
        return 1;
    }

    uint32_t storeCycles(uint64_t base, uint32_t length)
    {
        return 1;
    }
};

#endif // IDEAL_CACHE_H
