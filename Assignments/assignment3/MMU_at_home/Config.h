#pragma once
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

    bool debug;

    Config(int addressWidth, int pageWidth, int physicalWidth, std::vector<int> bitsPerLevel,
           bool debug = false): addressWidth(addressWidth), pageWidth(pageWidth), physicalWidth(physicalWidth),
                                bitsPerLevel(bitsPerLevel), debug(debug) {
        addressSize = 1 << addressWidth;
        pageSize = 1 << pageWidth;
        physicalSize = 1 << physicalWidth;

        pageTableLevels = bitsPerLevel.size();
    }
};
