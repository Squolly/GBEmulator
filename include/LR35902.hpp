#ifndef __LR35902_HPP__
#define __LR35902_HPP__

#include "types.hpp"

#include "Memory.hpp"
#include "Registers.hpp"

class Instruction;  

struct LR35902 {
    Registers registers; 
    Memory    memory; 
    bool      running; 
    bool      bhalt; 
    std::vector<Instruction*> instructions; 
    
    uint32    cycle_counter; 
    
    LR35902(); 
    ~LR35902(); 
    
    void halt();
    
    // control 
    bool retf(const uint8& flag);                        // return if flag
    bool retf_n(const uint8& flag);                      // return if !flag
    void ret();                                          // return from subroutine 
    void reti();                                         // uses ret currently 
                                                         
    bool callf(const uint8& flag, const uint16& addr);   // call address if flag set
    bool callf_n(const uint8& flag, const uint16& addr); // call address if flag not set
    void call(const uint16& addr);                       // call address
                                                        
    bool jpf(const uint8& flag, const uint16& addr);     // jump if flag is set 
    bool jpf_n(const uint8& flag, const uint16& addr);   // jump if flag is not set
    void jp(const uint16& addr);                         // jump
    
    void ei();                                           // TODO 
    void di();                                           // TODO 

    void push(const uint16& reg);                        // push register on stack 
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
    
    void add_16_16(uint16& reg1, const uint16& reg2); 
    void add_8_8(uint8& reg1, const uint8& reg2);
    void adc_8_8(uint8& reg1, const uint8& reg2);
    void sbc_8_8(uint8& reg1, const uint8& reg2);
    
    void sub_8(const uint8& reg);
    void and_8(const uint8& reg);
    void xor_8(const uint8& reg);
    void or_8(const uint8& reg); 
    void cp_8(const uint8& reg);
    
    // ALU extended instructions
    void rlc(uint8& reg); 
    void rrc(uint8& reg);
    void rl(uint8& reg); 
    void rr(uint8& reg);
    void sla(uint8& reg); 
    void sra(uint8& reg); 
    void swap(uint8& reg); 
    void srl(uint8& reg); 
    
    void bit(uint8 b, const uint8& reg); 
    void res(uint8 b, uint8& reg); 
    void set(uint8 b, uint8& reg); 
    
    void dda(); // convert A from binary to BCD
    
    void disassemble(MemoryMappedModule* module, uint16 start_address, uint16 end_address); 
    
}; 

#endif
