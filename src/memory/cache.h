#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>

/**
 * The base cache class
 */
class Cache
{
  public:
    virtual uint32_t loadCycles(uint64_t base, uint32_t length) = 0;
    virtual uint32_t storeCycles(uint64_t base, uint32_t length) = 0;
    virtual void printStats() {}
};

#endif // CACHE_H
