#include <iostream>
#include "Config.h"
#include "Memory.hpp"
#include "MMU.hpp"

#define DEBUG false

int main() {
    const Config config(8, 4, 32, {2, 2}, 2, DEBUG);

    Memory memory(config);
    TLB tlb(config);

    MMU mmu(memory, tlb, config);

    tlb.display();

    mmu.storeVal(0, 1);
    mmu.storeVal(0, 2);
    mmu.storeVal(1, 3);
    mmu.storeVal(2, 4);
    mmu.storeVal(3, 5);
    mmu.storeVal(4, 6);

    for (int i = 0; i < 5; i++) {
        std::cout << mmu.loadVal(i) << std::endl;
    }

    tlb.display();


    std::cout << std::endl;

    mmu.storeVal(35, 3);
    mmu.storeVal(37, 9);
    mmu.storeVal(32, 21);

    std::cout << mmu.loadVal(35) << std::endl;
    std::cout << mmu.loadVal(37) << std::endl;
    std::cout << mmu.loadVal(32) << std::endl;

    tlb.display();


    mmu.storeVal(28, 69);
    std::cout << mmu.loadVal(28) << std::endl;

    tlb.display();


    mmu.storeVal(69, 420);
    std::cout << mmu.loadVal(69) << std::endl;

    tlb.display();

    mmu.loadVal(28);
    mmu.loadVal(0);
    tlb.display();



    std::cout << std::endl;
    std::cout << std::endl;

    // memory.display();

    std::cout << std::endl;

    std::cout << mmu.misses << std::endl;

    return 0;
}
