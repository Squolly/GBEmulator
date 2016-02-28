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
    
    void inc_8bit_reg(uint8& reg); 
    void inc_16bit_reg(uint16& reg); 
    
    void dec_8bit_reg(uint8& reg); 
    void dec_16bit_reg(uint16& reg); 
    
    void shift_left_c_reg_a(); 
    void shift_left_reg_a(); 
    void shift_right_c_reg_a(); 
    void shift_right_reg_a();
    
    void add_16_16(const uint16& reg1, const uint16& reg2); 
    
    void dda(); // convert A from binary to BCD
    
    void halt(); 
}; 

#endif
