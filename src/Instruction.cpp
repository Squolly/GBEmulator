#include "Instruction.hpp"
#include "LR35902.hpp"

Instruction::Instruction(const std::string& mnemonic, const std::string& alt_name, const std::string& flags, 
            const uint8 opcode, const uint8 bytes, const uint8 cycles, bool verbose /* = false */) 
            : mnemonic(mnemonic), alt_name(alt_name), flags(flags), opcode(opcode), 
              bytes(bytes), cycles(cycles), verbose(verbose) { 
}

void Instruction::execute(LR35902& cpu, Memory& memory) { 
    op(cpu, memory); 
    cpu.cycle_counter += cycles + addedCycles; 
    addedCycles = 0; 
    cpu.registers.PC  += bytes + addedBytes; 
    addedBytes  = 0; 
}
