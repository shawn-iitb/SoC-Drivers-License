#pragma once
#include <stdint.h>
#include "Memory.hpp"
#include "TLB.hpp"
#include "Config.h"

class MMU {
    public:
        MMU(Memory& memory, TLB& tlb, const Config& cfg);
        void storeVal(uint64_t vaddr, uint64_t val); // we expose only these objects and methods to the user
        uint64_t loadVal(uint64_t vaddr);

        int misses;
    private:
        Memory& mem;
        TLB& tlb;
        const Config& config;

        uint64_t translate(uint64_t vaddr, bool create_pte);
};

