#pragma once
#include <stdexcept>
#include <vector>

struct Config {
    int addressWidth;
    int addressSize;

    int pageWidth;
    int pageSize;

    int physicalWidth;
    int physicalSize;

    int pageTableLevels;
    std::vector<int> bitsPerLevel;

    int maxTLBcapacity;

    bool debug;

    Config(const int addressWidth, const int pageWidth, const int physicalWidth, const std::vector<int> &bitsPerLevel,
           const int maxTLBcapacity, const bool debug = false): addressWidth(addressWidth), pageWidth(pageWidth),
                                                                physicalWidth(physicalWidth),
                                                                bitsPerLevel(bitsPerLevel),
                                                                maxTLBcapacity(maxTLBcapacity), debug(debug) {
        addressSize = 1 << addressWidth;
        pageSize = 1 << pageWidth;
        physicalSize = 1 << physicalWidth;

        pageTableLevels = bitsPerLevel.size();

        for (const int bits: bitsPerLevel) {
            if (bits > pageWidth) {
                throw std::invalid_argument("Invalid bits per level");
            }
        }
    }
};
