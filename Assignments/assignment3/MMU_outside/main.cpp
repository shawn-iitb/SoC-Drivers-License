#include <iostream>
#include "Config.h"
#include "Memory.hpp"
#include "MMU.hpp"

#define DEBUG true

int main() {
    const Config config(8, 4, 32, {2, 2}, DEBUG);

    Memory memory(config);

    const MMU mmu(memory, config);

    mmu.storeVal(0, 1);
    mmu.storeVal(0, 2);
    mmu.storeVal(1, 3);
    mmu.storeVal(2, 4);
    mmu.storeVal(3, 5);
    mmu.storeVal(4, 6);

    for (int i = 0; i < 5; i++) {
        std::cout << mmu.loadVal(i) << std::endl;
    }

    std::cout << std::endl;

    mmu.storeVal(35, 3);
    mmu.storeVal(37, 9);
    mmu.storeVal(32, 21);

    std::cout << mmu.loadVal(35) << std::endl;
    std::cout << mmu.loadVal(37) << std::endl;
    std::cout << mmu.loadVal(32) << std::endl;


    mmu.storeVal(28, 69);
    std::cout << mmu.loadVal(28) << std::endl;

    mmu.storeVal(69, 420);
    std::cout << mmu.loadVal(69) << std::endl;


    std::cout << std::endl;
    std::cout << std::endl;

    memory.display();

    return 0;
}
