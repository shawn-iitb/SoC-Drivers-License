#pragma once
#include <stdint.h>
#include "Memory.hpp"
#include "Config.h"
#include <string>

class MMU {
    public:
        MMU(Memory& memory, const Config& cfg);
        void storeVal(uint64_t vaddr, uint64_t val) const; // we expose only these objects and methods to the user
        uint64_t loadVal(uint64_t vaddr) const;

    private:
        Memory& mem;
        const Config& config;
        uint64_t translate(uint64_t vaddr, bool create_pte) const;
};

