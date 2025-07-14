#include "TLB.hpp"

#include <iostream>
#include <bits/ostream.tcc>


TLB::TLB(const Config &config): config(config) {
    lookup_no = 0;
}

void TLB::add(const uint64_t vpn, const uint64_t pfn) {
    if (TLB_content.size() >= config.maxTLBcapacity) {
        evict();
    }

    TLB_content[vpn] = pfn;
    TLB_lookups[vpn] = lookup_no;
    lookup_no++;
}

void TLB::evict() {
    std::pair<uint64_t, uint64_t> min = {-1, 0}; // -1 overflows
    for (const auto &[vpn, lkn] : TLB_lookups) {
        min = std::min(min, std::pair(lkn, vpn));
    }

    const uint64_t unlucky_vpn = min.second;

    TLB_content.erase(unlucky_vpn);
    TLB_lookups.erase(unlucky_vpn);
}

std::pair<bool, uint64_t> TLB::lookup(const uint64_t vpn) {
    if (TLB_content.find(vpn) == TLB_content.end()) {
        return {false, 0};
    }

    TLB_lookups[vpn] = lookup_no;
    lookup_no++;
    return {true, TLB_content[vpn]};
}

void TLB::display() {
    std::cout << "TLB display" << std::endl;
    for (const auto &[vpn, pfn] : TLB_content) {
        std::cout << vpn << " " << pfn << std::endl;
    }
    std::cout << std::endl;
}

