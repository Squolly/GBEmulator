#include <iostream>

#include "LR35902.hpp"

int main() {
    Registers registers; 
    registers.H = 1; 
    registers.L = 3; 
    std::cout << "H: " << (int)registers.H << ", L: " << (int)registers.L << ", HL: " << (int)registers.HL << std::endl; 

}