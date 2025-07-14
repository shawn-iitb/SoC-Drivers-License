#include <stdexcept>
#include "Memory.hpp"
#include <iostream>
#include <map>


Memory::Memory(const Config &config): config(config) {
    nextAvailableFrame = 1;
}

uint64_t Memory::get_paddr(const uint64_t pageTableNumber, const uint64_t pageOffset) const {
    return (pageTableNumber << config.pageWidth) | pageOffset;
}

uint64_t Memory::newPTE(const uint64_t pte_paddr) {
    memory_contents[pte_paddr] = nextAvailableFrame;
    nextAvailableFrame++;

    return memory_contents[pte_paddr];
}

void Memory::display() {
    std::map<uint64_t, std::map<uint64_t, uint64_t>> pages;

    for (const auto& [addr, val] : memory_contents) {
        const uint64_t page = addr >> config.pageWidth;
        const uint64_t offset = addr & ((1 << config.pageWidth) - 1);

        pages[page][offset] = val;
    }

    for (const auto& [pageNo, pageData] : pages) {
        std::cout << "PAGE " << pageNo << std::endl;

        for (const auto& [offset, val] : pageData) {
            printf("%-4lu: %lu\n", offset, val);
        }

        std::cout << std::endl;
    }
}