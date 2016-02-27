#include "LR35902.hpp"

LR35902::LR35902() {

}

LR35902::~LR35902() {

}

void LR35902::inc_8bit_reg(uint8& reg) {
    reg += 1;                          
    if(registers.B == 0) {                     // Z - result == 0?
	registers.set_z();
    }
    else {
	registers.clear_z(); 
    }
    registers.clear_n();                       // N - 0
    if(registers.B == 0x10) {                  // H - carry from bit 3 to 4 (15 to 16 or 0x0F to 0x10)
	registers.set_h();
    }
    else {
	registers.clear_h(); 
    }
	                                       // C - not affected
}

void LR35902::inc_16bit_reg(uint16& reg) {
    reg += 1;
					       // Z - not affected
					       // N - not affected
					       // H - not affected
	                                       // C - not affected
}

    
void LR35902::dec_8bit_reg(uint8& reg) {
    reg -= 1;                          
    if(registers.B == 0)  {                                 // Z - result == 0? 
	registers.set_z();
    }
    else {
	registers.clear_z(); 
    }
    registers.set_n();                         // N - 1 a substraction was done
    if(registers.B == 0x0F) {                  // H - carry from bit 3 to 4 (15 to 16 or 0x0F to 0x10)
	registers.set_h();
    }
    else {
	registers.clear_h(); 
    }
	                                       // C - not affected
}

void LR35902::dec_16bit_reg(uint16& reg) {
    reg -= 1;
					       // Z - not affected
					       // N - not affected
					       // H - not affected
	                                       // C - not affected
}

void LR35902::shift_left_reg_a() {
    uint8 zero = 0; 
    if (registers.A & BITMASK_7) { 
	zero = 1; 
	registers.set_c(); 
    }
    else
	registers.clear_c(); 
    registers.A = registers.A <<  1;                        //  shift left
    registers.A = registers.A | zero; 
    registers.clear_z(); 
    registers.clear_n(); 
    registers.clear_h(); 
}

void LR35902::shift_right_reg_a() {
    uint16 zero = 0;  
    if (registers.A & BITMASK_0) {
	zero = 0x80;                                               //  1000 0000
	registers.set_c(); 
    }
    else {
	registers.clear_c(); 
    }
    
    registers.A = registers.A >> 1; 
    registers.A = registers.A | zero; 
    
    registers.clear_n(); 
    registers.clear_h(); 
    registers.clear_z(); 
}


const uint16 BITMASK_11n = 0x0FFF; 
const uint32 MASK_8 = 0xFF; 

void LR35902::add_16_16(const uint16& reg1, const uint16& reg2) {
    uint32 r = reg1 + reg2; 
    if (r > 65535) {
	registers.set_c();
    }
    else {
	registers.clear_c(); 
    }
    registers.clear_n(); 
    
    //  check H-flag (carry from bit 11 to bit 12)
    uint32 carry_check = (reg1 & BITMASK_11n) + (reg2 & BITMASK_11n); 
    if (carry_check > 0x0FFF) {
	registers.set_h(); 
    }
    else {
	registers.clear_h(); 
    }
    
    registers.A = r & MASK_8; 
}



    
