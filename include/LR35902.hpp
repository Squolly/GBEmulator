#ifndef __LR35902_HPP__
#define __LR35902_HPP__

#include "Memory.hpp"
#include "Registers.hpp"

struct LR35902 {
    Registers registers; 
    bool running; 
    bool bhalt; 
    
    uint32 cycle_counter; 
    
    LR35902(); 
    ~LR35902(); 
    
    void halt();
    
    // control 
    void retf(const uint8& flag);                        // TODO  // return if flag
    void retf_n(const uint8& flag);                      // TODO  // return if !flag
    void ret();                                          // TODO
    void reti();                                         // TODO
    void res(const uint16& addr);                        // TODO  // reset to address
                                                         
    void callf(const uint8& flag, const uint16& addr);   // TODO  // call address if flag set
    void callf_n(const uint8& flag, const uint16& addr); // TODO  // fall address if flag not set
    void call(const uint16& addr);                       // TODO  // call address
                                                        
    void jpf(const uint8& flag, const uint16& addr);     // TODO
    void jpf_n(const uint8& flag, const uint16& addr);   // TODO
    void jp(const uint16& addr);                         // TODO
    
    void ei();                                           // TODO 
    void di();                                           // TODO 
                                                        
    void push(const uint16& reg);                        // TODO  // push register on stack 
    void pop(uint16& reg);                               // TODO  // pop register from stack
    
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
    void add_8_8(uint8& reg1, const uint8& reg2); // TODO 
    void adc_8_8(uint8& reg1, const uint8& reg2); // TODO 
    void sbc_8_8(uint8& reg1, const uint8& reg2); // TODO
    
    void sub_8(const uint8& reg);  // TODO
    void and_8(const uint8& reg);  // TODO
    void xor_8(const uint8& reg);  // TODO
    void or_8(const uint8& reg);   // TODO
    void cp_8(const uint8& reg);   // TODO
    
    void dda(); // convert A from binary to BCD
    
}; 

#endif
