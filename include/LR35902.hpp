#ifndef __LR35902_HPP__
#define __LR35902_HPP__

#include <iostream>

#include "types.hpp"

#include "Memory.hpp"
#include "Registers.hpp"

class Instruction;  

struct TraceEntry {
    TraceEntry(Registers registers_before, Instruction* instruction) : registers_before(registers_before), instruction(instruction) { }
    Registers registers_before; 
    Registers registers_after; 
    // Memory memory; 
    Instruction* instruction;
    
}; 

struct LR35902 {
    Registers registers; 
    Memory    memory; 
    bool      running; 
    bool      bhalt; 
    
    // Debug
    bool debug_mode; 
    bool debug_hold; 
    
    std::vector<Instruction*> instructions; 
    std::vector<TraceEntry> trace; 
    
    uint32    cycle_counter; 
    
    LR35902(); 
    ~LR35902(); 
    
    void halt();
    
    // control 
    bool retf(uint8 flag);                        // return if flag
    bool retf_n(uint8 flag);                      // return if !flag
    void ret();                                          // return from subroutine 
    void reti();                                         // uses ret currently 
                                                         
    bool callf(uint8 flag, uint16 addr, uint16 next_pc);   // call address if flag set
    bool callf_n(uint8 flag, uint16 addr, uint16 next_pc); // call address if flag not set
    void call(uint16 addr, uint16 next_pc);                       // call address
                                                        
    bool jpf(uint8 flag, uint16 addr);     // jump if flag is set 
    bool jpf_n(uint8 flag, uint16 addr);   // jump if flag is not set
    void jp(uint16 addr);                         // jump
    
    void ei();                                           // TODO 
    void di();                                           // TODO 

    void push(uint16 reg);                               // push register on stack 
    void pop(uint16& reg);                               // pop register from stack
    
    // ALU
    uint16 sign_ext(uint8 value); 
    
    void inc_8bit_reg(uint8& reg); 
    void inc_16bit_reg(uint16& reg); 
    
    void dec_8bit_reg(uint8& reg); 
    void dec_16bit_reg(uint16& reg); 
    
    void shift_left_c_reg_a(); 
    void shift_left_reg_a(); 
    void shift_right_c_reg_a(); 
    void shift_right_reg_a();
    
    void add_16_16(uint16& reg1, uint16 reg2); 
    void add_8_8(uint8& reg1,  uint8 reg2);
    void adc_8_8(uint8& reg1,  uint8 reg2);
    void sbc_8_8(uint8& reg1,  uint8 reg2);
    
    void sub_8(uint8 reg);
    void and_8(uint8 reg);
    void xor_8(uint8 reg);
    void or_8(uint8 reg); 
    void cp_8(uint8 reg);
    
    // ALU extended instructions
    void rlc(uint8& reg); 
    void rrc(uint8& reg);
    void rl(uint8& reg); 
    void rr(uint8& reg);
    void sla(uint8& reg); 
    void sra(uint8& reg); 
    void swap(uint8& reg); 
    void srl(uint8& reg); 
    
    void bit(uint8 b, uint8 reg); 
    void res(uint8 b, uint8& reg); 
    void set(uint8 b, uint8& reg); 
    
    void dda(); // convert A from binary to BCD
    
    void init(); 
    void disassemble(); 
    void single_step(bool verbose);
    void print_state(std::ostream& out = std::cout); 
    void print_state(Registers& registers, std::ostream& out = std::cout); 
    
}; 

#endif
