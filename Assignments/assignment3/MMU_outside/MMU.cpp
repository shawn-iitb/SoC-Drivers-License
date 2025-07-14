#include "MMU.hpp"

#include <iostream>
#include <ostream>
#include <stdexcept>

MMU::MMU(Memory &memory, const Config &cfg): mem(memory), config(cfg) {
}

uint64_t MMU::translate(const uint64_t vaddr, const bool create_pte) const {
    if (vaddr >> config.addressWidth != 0) {
        throw std::out_of_range("Virtual address out of range");
    }

    uint64_t vaddr_copy = vaddr;

    const uint64_t offset = vaddr_copy & ((1 << config.pageWidth) - 1);
    vaddr_copy >>= config.pageWidth;

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

    const uint64_t paddr = mem.get_paddr(pageTableNumber, offset);

    if (config.debug) {
        std::cout << vaddr << " -> " << paddr << std::endl;
    }

    return paddr;
}

uint64_t MMU::loadVal(const uint64_t vaddr) const {
    const uint64_t paddr = translate(vaddr, false);

    return mem.memory_contents.at(paddr);
}

void MMU::storeVal(const uint64_t vaddr, const uint64_t val) const {
    const uint64_t paddr = translate(vaddr, true);

    mem.memory_contents[paddr] = val;
}

