#include "LR35902.hpp"

LR35902::LR35902() : running(true) {
    
}

LR35902::~LR35902() {

}

bool LR35902::retf(const uint8& flag) {
    if(flag) {
        ret();
        return true; 
    }
    
    return false; 
}

bool LR35902::retf_n(const uint8& flag) {
    if(!flag) {
        ret();
        return true; 
    }
    
    return false; 
}

void LR35902::ret() {
    // push address from stack 
    uint16 addr; 
    pop(addr); 
    registers.PC = addr; // Jump!
}

void LR35902::reti() {
    ret(); 
    ei(); 
}

bool LR35902::callf(const uint8& flag, const uint16& addr) {
    if(flag) {
        call(addr); 
        return true; 
    }
    return false; 
}

bool LR35902::callf_n(const uint8& flag, const uint16& addr) {
    if(!flag) {
        call(addr); 
        return true; 
    }
    return false; 
}

void LR35902::call(const uint16& addr) {
    push(registers.PC); 
    jp(addr); 
}

bool LR35902::jpf(const uint8& flag, const uint16& addr) {
    if(flag) {
        jp(addr); 
        return true; 
    }
    return false; 
}

bool LR35902::jpf_n(const uint8& flag, const uint16& addr) {
    if(!flag) {
        jp(addr); 
        return true; 
    }
    return false; 
}

void LR35902::jp(const uint16& addr) {
    registers.PC = addr; 
}
    
void LR35902::ei() {
    // TODO 
}
    
void LR35902::di() {
    // TODO 
}
    
void LR35902::push(const uint16& reg) {
    registers.SP += 2; 
    memory.write_16(registers.SP, reg); 
}

void LR35902::pop(uint16& reg) {
    reg = memory.read_16(registers.SP); 
    registers.SP -= 2; 
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
    if(registers.B == 0)  {                    // Z - result == 0? 
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

void LR35902::add_16_16(uint16& reg1, const uint16& reg2) {
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
    
    reg1 = r & 0xFFFF; 
    // registers.A = r & MASK_8; 
}

void LR35902::add_8_8(uint8& reg1, const uint8& reg2) {
    uint8 nibble_reg1 = reg1 & 0x0F; 
    uint8 nibble_reg2 = reg2 & 0x0F; 
    
    uint8 nibble_result = nibble_reg1 + nibble_reg2; 
    uint16 result = reg1 + reg2; 
    
    registers.clear_n(); 
    
    if(nibble_result > 0x0F) 
        registers.set_h(); 
    else 
        registers.clear_h(); 
    
    if(result > 255)
        registers.set_c(); 
    else
        registers.clear_c(); 
    
    if(result == 0) 
        registers.set_z(); 
    else
        registers.clear_z(); 
    
    reg1 = result & 0xFF; 
}

void LR35902::adc_8_8(uint8& reg1, const uint8& reg2) {
    uint8 carry = (registers.c() ? 1 : 0); 
    uint8 nibble_reg1 = reg1 & 0x0F; 
    uint8 nibble_reg2 = reg2 & 0x0F; 
    
    uint8 nibble_result = nibble_reg1 + nibble_reg2 + carry; 
    uint16 result = reg1 + reg2 + carry; 
    
    registers.clear_n(); 
    
    if(nibble_result > 0x0F) 
        registers.set_h(); 
    else 
        registers.clear_h(); 
    
    if(result > 255)
        registers.set_c(); 
    else
        registers.clear_c(); 
    
    if(result == 0) 
        registers.set_z(); 
    else
        registers.clear_z(); 
    
    reg1 = result & 0xFF; 
}

void LR35902::sbc_8_8(uint8& reg1, const uint8& reg2) {
    
}// TODO

void LR35902::sub_8(const uint8& reg) {
    
} // TODO

void LR35902::and_8(const uint8& reg) {
    registers.A = registers.A & reg; 
    if(registers.A == 0) 
        registers.set_z(); 
    else 
        registers.clear_z(); 
    registers.clear_n(); 
    registers.set_h(); 
    registers.clear_c(); 
}


void LR35902::xor_8(const uint8& reg) {
    registers.A = registers.A ^ reg; 
    if(registers.A == 0) 
        registers.set_z(); 
    else 
        registers.clear_z(); 
    registers.clear_n(); 
    registers.clear_h(); 
    registers.clear_c(); 
}


void LR35902::or_8(const uint8& reg) {
    registers.A = registers.A | reg; 
    if(registers.A == 0) 
        registers.set_z(); 
    else 
        registers.clear_z(); 
    registers.clear_n(); 
    registers.clear_h(); 
    registers.clear_c(); 
}


void LR35902::cp_8(const uint8& reg) {
    uint8 tmpA = registers.A; // store A 
    sub_8(reg); // basically sets flags
    registers.A = tmpA;       // restore A
}


uint16 LR35902::sign_ext(uint8 value) {
    return (0xF0 * ((value >> 7) & 0x1)) | value; // multiply sign of value (7. bit) with 0xF0 
}

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

