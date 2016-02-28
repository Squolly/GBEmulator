#include "LR35902.hpp"

LR35902::LR35902() : running(true) {
    
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

void LR35902::shift_left_c_reg_a() {
    uint8 zero = 0; 
    if (registers.A & BITMASK_7) { 
	zero = 1; 
	registers.set_c(); 
    }
    else
	registers.clear_c(); 
    registers.A = registers.A << 1;                        //  shift left
    registers.A = registers.A | zero; 
    registers.clear_z(); 
    registers.clear_n(); 
    registers.clear_h(); 
}

void LR35902::shift_left_reg_a() {
    uint8 zero = 0; 
    if(registers.c()) {
        zero = 1;
    }
    else {
        zero = 0; 
    }
    if (registers.A & BITMASK_7) { 
        registers.set_c(); 
    }
    else {
        registers.clear_c(); 
    }
    registers.A = registers.A << 1;                        //  shift left
    registers.A = registers.A | zero; 
    registers.clear_z(); 
    registers.clear_n(); 
    registers.clear_h(); 
}

void LR35902::shift_right_c_reg_a() {
    uint8 zero = 0;  
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

void LR35902::shift_right_reg_a() {
    uint8 zero = 0; 
    if(registers.c()) {
        zero = 0x80;
    }
    else {
        zero = 0; 
    }
    if (registers.A & BITMASK_0) { 
        registers.set_c(); 
    }
    else {
        registers.clear_c(); 
    }
    registers.A = registers.A >> 1;                        //  shift right
    registers.A = registers.A | zero; 
    registers.clear_z(); 
    registers.clear_n(); 
    registers.clear_h(); 
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

/*
N   C   Value of     H  Value of     Hex no   C flag after
        high nibble     low nibble   added    execution

0   0      0-9       0     0-9       00       0   DONE
0   0      0-8       0     A-F       06       0   DONE
0   0      0-9       1     0-3       06       0   DONE
0   0      A-F       0     0-9       60       1   DONE
0   0      9-F       0     A-F       66       1   DONE
0   0      A-F       1     0-3       66       1   DONE
0   1      0-2       0     0-9       60       1   DONE
0   1      0-2       0     A-F       66       1   DONE
0   1      0-3       1     0-3       66       1   DONE
1   0      0-9       0     0-9       00       0   DONE
1   0      0-8       1     6-F       FA       0   DONE
1   1      7-F       0     0-9       A0       1   DONE
1   1      6-F       1     6-F       9A       1   DONE
*/

#define LOW_NIBBLE(x) (x & 0xF)
#define HIGH_NIBBLE(x) ((x >> 4)&0xF)
void LR35902::dda() { // convert A from binary to BCD
    uint8 add = 0; 
    uint8 ln = LOW_NIBBLE(registers.A); 
    uint8 hn = HIGH_NIBBLE(registers.A); 
    uint8 H = registers.h(); 
    uint8 C = 0; 
    
    if(!registers.n()) {
        if(!registers.c()) {
            if(hn >= 0x0 && hn <= 0x9 && !H && ln >= 0x0 && ln <= 0x9) { add = 0x00; C = 0; }
            if(hn >= 0x0 && hn <= 0x8 && !H && ln >= 0xA && ln <= 0xF) { add = 0x06; C = 0; }
            if(hn >= 0x0 && hn <= 0x9 &&  H && ln >= 0x0 && ln <= 0x3) { add = 0x06; C = 0; }
            if(hn >= 0xA && hn <= 0xF && !H && ln >= 0x0 && ln <= 0x9) { add = 0x60; C = 1; }
            if(hn >= 0x9 && hn <= 0xF && !H && ln >= 0xA && ln <= 0xF) { add = 0x66; C = 1; }
            if(hn >= 0xA && hn <= 0xF &&  H && ln >= 0x0 && ln <= 0x3) { add = 0x66; C = 1; }
        }
        else {
            if(hn >= 0x0 && hn <= 0x2 && !H && ln >= 0x0 && ln <= 0x9) { add = 0x60; C = 1; }
            if(hn >= 0x0 && hn <= 0x2 && !H && ln >= 0xA && ln <= 0xF) { add = 0x66; C = 1; }
            if(hn >= 0x0 && hn <= 0x3 &&  H && ln >= 0x0 && ln <= 0x3) { add = 0x66; C = 1; }
        }
    }
    else {
        if(!registers.c()) {
            if(hn >= 0x0 && hn <= 0x9 && !H && ln >= 0x0 && ln <= 0x9) { add = 0x00; C = 0; }
            if(hn >= 0x0 && hn <= 0x8 &&  H && ln >= 0x6 && ln <= 0xF) { add = 0xFA; C = 0; }
        } 
        else {
            if(hn >= 0x7 && hn <= 0xF && !H && ln >= 0x0 && ln <= 0x9) { add = 0xA0; C = 1; }
            if(hn >= 0x6 && hn <= 0xF &&  H && ln >= 0x6 && ln <= 0xF) { add = 0x9A; C = 1; }
        }
    }
    
    // add value to registers.A 
    registers.A = registers.A + add; 
    if(C) 
        registers.set_c(); 
    else 
        registers.clear_c(); 
    registers.clear_h(); 
    if(!registers.A)
        registers.set_z(); 
    else
        registers.clear_z(); 
}

void LR35902::halt() {
    bhalt = true; 
}

