#include <stdexcept>
#include "Memory.hpp"

Memory::Memory(const Config & cf) {
    for (int i = 0; i < cf.pageTableLevels; i++) {
        pageTables.push_back(std::unordered_map<uint32_t, PageTableEntry> {});
    }

    nextAvailableFrame = 0;
}

PageTableEntry Memory::getPageTableEntry(const uint32_t level, const uint32_t index) const {
    return pageTables[level].at(index); // not using indexing because it will auto initialize if no entry is present
}

void Memory::setPageTableEntry(const uint32_t level, const uint32_t index, const PageTableEntry& entry) {
    pageTables[level][index] = entry;
}