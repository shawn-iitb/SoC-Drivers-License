#pragma once
#include <unordered_map>
#include "Config.h"

class TLB {
    friend class MMU;
    public:
        TLB(const Config &config);

        void display();
    private:
        const Config &config;

        std::unordered_map<uint64_t, uint64_t> TLB_content;
        uint64_t lookup_no;
        std::unordered_map<uint64_t, uint64_t> TLB_lookups;

        void add(uint64_t vpn, uint64_t pfn);
        void evict();
        std::pair<bool, uint64_t> lookup(uint64_t vpn);
};
