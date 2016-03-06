#ifndef __INSTRUCTION_HPP__
#define __INSTRUCTION_HPP__

#include <string>

#include "types.hpp"

class Memory; 
class LR35902; 

struct Instruction {
    const std::string mnemonic;  
    const std::string alt_name; 
    const std::string flags;    // affected flags
    const uint8 opcode;
    const uint8 bytes; 
    const uint8 cycles; 
    
    uint8 addedCycles; // some instructions may need more cycles in some cases
    uint8 addedBytes;  // some instructions may need more bytes (well... CB only uses more, namely 2) 
    
    bool verbose; // verbose for debug
    
    Instruction(const std::string& mnemonic, const std::string& alt_name, const std::string& flags, 
                const uint8 opcode, const uint8 bytes, const uint8 cycles, bool verbose = false);
    
    virtual void execute(LR35902& cpu, Memory& memory);
    virtual void op(LR35902& cpu, Memory& memory) = 0; 
};

#endif
