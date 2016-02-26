#ifndef __INSTRUCTION_HPP__
#define __INSTRUCTION_HPP__

#include <string>

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
    
    virtual int op(Registers& registers, Memory& memory) = 0; 
};

#endif
