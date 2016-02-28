#include <iostream>
#include <sstream>

#include "LR35902.hpp"
#include "InstructionSet.hpp"

std::string show_bcd(uint8 v) {
    std::stringstream ss; 
    ss << (int)((v >> 4)&0xF) << (int)((v)&0xF); 
    return ss.str(); 
}

int main() {
    LR35902 cpu; 
    Registers registers; 
    registers.H = 1; 
    registers.L = 3; 
    std::cout << "H: " << (int)registers.H << ", L: " << (int)registers.L << ", HL: " << (int)registers.HL << std::endl; 
    
    std::cout << "DDA test: " << std::endl; 
    cpu.registers.A = 0xFF; 
    std::cout << "A: " << (int)(cpu.registers.A) << " <-> " << show_bcd(cpu.registers.A) << std::endl; 
    cpu.dda(); 
    std::cout << "A: " << (int)(cpu.registers.A) << " <-> " << show_bcd(cpu.registers.A) << std::endl; 
}