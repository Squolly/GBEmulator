#ifndef __INSTRUCTION_HPP__
#define __INSTRUCTION_HPP__

struct Instruction {
    const std::string name; 
    const std::string alt_name; 
    const int opcode; 
    const int bytes; 
    const int cycles; 
    
    virtual int op(Registers& registers, Memory& memory); 
};

#endif
