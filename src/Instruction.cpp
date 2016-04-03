#include "Instruction.hpp"
#include "LR35902.hpp"

#include <iostream>

Instruction::Instruction(const std::string& mnemonic, const std::string& alt_name, const std::string& flags, 
            uint8 opcode, uint8 bytes, uint8 cycles, bool verbose /* = false */) 
            : mnemonic(mnemonic), alt_name(alt_name), flags(flags), opcode(opcode), 
              bytes(bytes), addedBytes(0), addedCycles(0), cycles(cycles), verbose(verbose) { 
}

Instruction::~Instruction() {
    
}

    
void Instruction::execute(LR35902& cpu, Memory& memory) { 
    op(cpu, memory); 
    cpu.cycle_counter += cycles + addedCycles; 
    addedCycles = 0; 
    // std::cout << (int)cpu.registers.PC << " += " << (int)bytes << " + " << (int)addedBytes << std::endl; 
    cpu.registers.PC  += bytes + addedBytes; 
    addedBytes  = 0; 
}
