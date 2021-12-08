#include <iostream>
#include "MagicScrollBB.h"

void MagicScrollBB(){
    #ifdef NDEBUG
    std::cout << "MagicScrollBB/0.1: Hello World Release!" <<std::endl;
    #else
    std::cout << "MagicScrollBB/0.1: Hello World Debug!" <<std::endl;
    #endif
}

