#pragma once
#include <vector>
#include <cstdint>
#include <unordered_map>
#include "Config.h"

class Memory {
    friend class MMU; // we want MMU to be able to access the private methods but give access to the user
    public:
        Memory(const Config &config);


        void display();
    private:
        const Config &config;
        const uint64_t PDBR = 0;

        uint64_t get_paddr(uint64_t pageTableNumber, uint64_t pageOffset) const;

        uint64_t newPTE(uint64_t pte_paddr);

        std::unordered_map<uint64_t, uint64_t> memory_contents; // stores the things you want to store

        uint64_t nextAvailableFrame; // Keeping this as page number (not address of page)
};
