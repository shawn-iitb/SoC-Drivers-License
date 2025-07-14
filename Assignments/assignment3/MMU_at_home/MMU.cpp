#include "MMU.hpp"

#include <iostream>
#include <ostream>
#include <stdexcept>

MMU::MMU(Memory &memory, const Config &cfg): mem(memory), config(cfg) {
}

uint64_t MMU::translate(const uint64_t vaddr) const {
    if (vaddr >> config.addressWidth != 0) {
        throw std::out_of_range("Virtual address out of range");
    }

    if (config.pageTableLevels > 1) {
        throw std::out_of_range("lol i havent done this yet");
    }

    const uint64_t vpn = vaddr >> config.pageWidth;
    const uint64_t offset = vaddr & ((1 << config.pageWidth) - 1);
    uint64_t pfn;

    try {
        pfn = mem.getPageTableEntry(0, vpn).physicalFrame;
    } catch (const std::out_of_range &e) {
        const PageTableEntry new_pte {
            .physicalFrame = mem.nextAvailableFrame,
            .present = true
        };
        mem.setPageTableEntry(0, vpn, new_pte);
        mem.nextAvailableFrame++; // allowed in a const function since mem is just a reference... woahh

        pfn = new_pte.physicalFrame;
    }

    const uint64_t paddr = (pfn << config.pageWidth) | offset; // + also works but watever


    if (config.debug) {
        std::cout << vaddr << " -> " << paddr << std::endl;
    }

    return paddr;
}

uint64_t MMU::loadVal(const uint64_t vaddr) const {
    const uint64_t paddr = translate(vaddr);

    return mem.memory_contents.at(paddr);
}

void MMU::storeVal(const uint64_t vaddr, const uint64_t val) const {
    const uint64_t paddr = translate(vaddr);

    mem.memory_contents[paddr] = val;
}

