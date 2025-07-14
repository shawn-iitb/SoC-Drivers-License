#include <iostream>
#include "Config.h"
#include "Memory.hpp"
#include "MMU.hpp"

#define DEBUG true

int main() {
    Config config(24, 12, 24, {12}, DEBUG);

    Memory memory(config);

    MMU mmu(memory, config);

    mmu.storeVal(0, 1);
    mmu.storeVal(0, 2);
    mmu.storeVal(1, 3);
    mmu.storeVal(2, 4);
    mmu.storeVal(3, 5);

    for (int i = 0; i < 4; i++) {
        std::cout << mmu.loadVal(i) << std::endl;
    }

    std::cout << std::endl;

    mmu.storeVal(9096, 3);
    mmu.storeVal(10000, 9);
    mmu.storeVal(11006, 21);

    std::cout << mmu.loadVal(9096) << std::endl;
    std::cout << mmu.loadVal(10000) << std::endl;
    std::cout << mmu.loadVal(11006) << std::endl;


    mmu.storeVal(4096, 69);
    std::cout << mmu.loadVal(4096) << std::endl;

    return 0;
}
