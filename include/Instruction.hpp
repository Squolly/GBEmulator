#ifndef __INSTRUCTION_HPP__
#define __INSTRUCTION_HPP__

#include <string>

#include "LR35902.hpp"
#include "Registers.hpp"
#include "Memory.hpp"

struct Instruction {
    const std::string mnemonic;  
    const std::string alt_name; 
    const std::string flags;    // affected flags
    const uint8 opcode;
    const uint8 bytes; 
    const uint8 cycles; 
    
    bool verbose; // verbose for debug
    
    Instruction(const std::string& mnemonic, const std::string& alt_name, const std::string& flags, 
		const uint8 opcode, const uint8 bytes, const uint8 cycles, bool verbose = false) : 
		mnemonic(mnemonic), alt_name(alt_name), flags(flags), opcode(opcode), cycles(cycles), verbose(verbose)
		{ }
	
    virtual void execute(LR35902& cpu, Memory& memory) { op(cpu, memory); cpu.cycle_counter += cycles; cpu.registers.PC += bytes; }
    virtual void op(LR35902& cpu, Memory& memory) = 0; 
};

#endif
