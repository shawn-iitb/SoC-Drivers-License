#include "MMU.hpp"

#include <iostream>
#include <ostream>
#include <stdexcept>

MMU::MMU(Memory &memory, TLB &tlb, const Config &cfg): mem(memory), tlb(tlb), config(cfg) {
    misses = 0;
}

uint64_t MMU::translate(const uint64_t vaddr, const bool create_pte) {
    if (vaddr >> config.addressWidth != 0) {
        throw std::out_of_range("Virtual address out of range");
    }

    int pageNo;

    uint64_t vaddr_copy = vaddr;
    const uint64_t offset = vaddr_copy & ((1 << config.pageWidth) - 1);
    vaddr_copy >>= config.pageWidth;

    const uint64_t big_vpn = vaddr_copy;

    auto [hit, pfn] = tlb.lookup(big_vpn);
    if (hit) {
        pageNo = pfn;
    } else {
        misses++;

        std::vector<uint64_t> vpns(config.pageTableLevels);
        for (int i = config.pageTableLevels - 1; i >= 0; i--) {
            const uint64_t vpn = vaddr_copy & ((1 << config.bitsPerLevel[i]) - 1);
            vaddr_copy >>= config.bitsPerLevel[i];
            vpns[i] = vpn;
        }

        uint64_t pageTableNumber = mem.PDBR;
        for (int level = 0; level < config.pageTableLevels; level++) {
            uint64_t paddr = mem.get_paddr(pageTableNumber, vpns[level]);
            if (mem.memory_contents.find(paddr) == mem.memory_contents.end()) {
                if (create_pte) {
                    mem.newPTE(paddr);
                    level--;
                    continue;
                } else {
                    throw std::out_of_range("Address not found");
                }
            } else {
                pageTableNumber = mem.memory_contents[paddr];
            }
        }

        pageNo = pageTableNumber;

        tlb.add(big_vpn, pageNo);
    }

    const uint64_t paddr = mem.get_paddr(pageNo, offset);

    if (config.debug) {
        std::cout << vaddr << " -> " << paddr << std::endl;
    }

    return paddr;
}

uint64_t MMU::loadVal(const uint64_t vaddr) {
    const uint64_t paddr = translate(vaddr, false);

    return mem.memory_contents.at(paddr);
}

void MMU::storeVal(const uint64_t vaddr, const uint64_t val) {
    const uint64_t paddr = translate(vaddr, true);

    mem.memory_contents[paddr] = val;
}

