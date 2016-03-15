#include "LR35902.hpp"
#include "InstructionSet.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

struct InstructionDeleter {
  void operator() (const Instruction *instrPtr) const {
      if(instrPtr)
        delete instrPtr;
  }
};

LR35902::LR35902() : running(true), memory(MEMORY_SIZE) {
    instructions = std::vector<Instruction*>(0x100, static_cast<Instruction*>(0)); 
    instructions[0x00] = new         NOP_In();
    instructions[0x01] = new   LD_BC_d16_In();
    instructions[0x02] = new    LD_mBC_A_In();
    instructions[0x03] = new      INC_BC_In();
    instructions[0x04] = new       INC_B_In();
    instructions[0x05] = new       DEC_B_In();
    instructions[0x06] = new     LD_B_d8_In();
    instructions[0x07] = new        RLCA_In();
    instructions[0x08] = new   LD_a16_SP_In();
    instructions[0x09] = new   ADD_HL_BC_In();
    instructions[0x0A] = new    LD_A_mBC_In();
    instructions[0x0B] = new      DEC_BC_In();
    instructions[0x0C] = new       INC_C_In();
    instructions[0x0D] = new       DEC_C_In();
    instructions[0x0E] = new     LD_C_d8_In();
    instructions[0x0F] = new        RRCA_In();

    instructions[0x10] = new        STOP_In();
    instructions[0x11] = new   LD_DE_d16_In();
    instructions[0x12] = new    LD_mDE_A_In();
    instructions[0x13] = new      INC_DE_In();
    instructions[0x14] = new       INC_D_In();
    instructions[0x15] = new       DEC_D_In();
    instructions[0x16] = new     LD_D_d8_In();
    instructions[0x17] = new         RLA_In();
    instructions[0x18] = new       JR_r8_In();
    instructions[0x19] = new   ADD_HL_DE_In();
    instructions[0x1A] = new    LD_A_mDE_In();
    instructions[0x1B] = new      DEC_DE_In();
    instructions[0x1C] = new       INC_E_In();
    instructions[0x1D] = new       DEC_E_In();
    instructions[0x1E] = new     LD_E_d8_In();
    instructions[0x1F] = new         RRA_In();

    instructions[0x20] = new    JR_NZ_r8_In();
    instructions[0x21] = new   LD_HL_d16_In();
    instructions[0x22] = new   LD_mHLp_A_In();
    instructions[0x23] = new      INC_HL_In();
    instructions[0x24] = new       INC_H_In();
    instructions[0x25] = new       DEC_H_In();
    instructions[0x26] = new     LD_H_d8_In();
    instructions[0x27] = new         DAA_In();
    instructions[0x28] = new     JR_Z_r8_In();
    instructions[0x29] = new   ADD_HL_HL_In();
    instructions[0x2A] = new   LD_A_mHLp_In();
    instructions[0x2B] = new      DEC_HL_In();
    instructions[0x2C] = new       INC_L_In();
    instructions[0x2D] = new       DEC_L_In();
    instructions[0x2E] = new     LD_L_d8_In();
    instructions[0x2F] = new         CPL_In();

    instructions[0x30] = new    JR_NC_r8_In();
    instructions[0x31] = new   LD_SP_d16_In();
    instructions[0x32] = new   LD_mHLm_A_In();
    instructions[0x33] = new      INC_SP_In();
    instructions[0x34] = new     INC_mHL_In();
    instructions[0x35] = new     DEC_mHL_In();
    instructions[0x36] = new   LD_mHL_d8_In();
    instructions[0x37] = new         SCF_In();
    instructions[0x38] = new     JR_C_r8_In();
    instructions[0x39] = new   ADD_HL_SP_In();
    instructions[0x3A] = new   LD_A_mHLm_In();
    instructions[0x3B] = new      DEC_SP_In();
    instructions[0x3C] = new       INC_A_In();
    instructions[0x3D] = new       DEC_A_In();
    instructions[0x3E] = new     LD_A_d8_In();
    instructions[0x3F] = new         CCF_In();

    instructions[0x40] = new      LD_B_B_In();
    instructions[0x41] = new      LD_B_C_In();
    instructions[0x42] = new      LD_B_D_In();
    instructions[0x43] = new      LD_B_E_In();
    instructions[0x44] = new      LD_B_H_In();
    instructions[0x45] = new      LD_B_L_In();
    instructions[0x46] = new    LD_B_mHL_In();
    instructions[0x47] = new      LD_B_A_In();
    instructions[0x48] = new      LD_C_B_In();
    instructions[0x49] = new      LD_C_C_In();
    instructions[0x4A] = new      LD_C_D_In();
    instructions[0x4B] = new      LD_C_E_In();
    instructions[0x4C] = new      LD_C_H_In();
    instructions[0x4D] = new      LD_C_L_In();
    instructions[0x4E] = new    LD_C_mHL_In();
    instructions[0x4F] = new      LD_C_A_In();

    instructions[0x50] = new      LD_D_B_In();
    instructions[0x51] = new      LD_D_C_In();
    instructions[0x52] = new      LD_D_D_In();
    instructions[0x53] = new      LD_D_E_In();
    instructions[0x54] = new      LD_D_H_In();
    instructions[0x55] = new      LD_D_L_In();
    instructions[0x56] = new    LD_D_mHL_In();
    instructions[0x57] = new      LD_D_A_In();
    instructions[0x58] = new      LD_E_B_In();
    instructions[0x59] = new      LD_E_C_In();
    instructions[0x5A] = new      LD_E_D_In();
    instructions[0x5B] = new      LD_E_E_In();
    instructions[0x5C] = new      LD_E_H_In();
    instructions[0x5D] = new      LD_E_L_In();
    instructions[0x5E] = new    LD_E_mHL_In();
    instructions[0x5F] = new      LD_E_A_In();

    instructions[0x60] = new      LD_H_B_In();
    instructions[0x61] = new      LD_H_C_In();
    instructions[0x62] = new      LD_H_D_In();
    instructions[0x63] = new      LD_H_E_In();
    instructions[0x64] = new      LD_H_H_In();
    instructions[0x65] = new      LD_H_L_In();
    instructions[0x66] = new    LD_H_mHL_In();
    instructions[0x67] = new      LD_H_A_In();
    instructions[0x68] = new      LD_L_B_In();
    instructions[0x69] = new      LD_L_C_In();
    instructions[0x6A] = new      LD_L_D_In();
    instructions[0x6B] = new      LD_L_E_In();
    instructions[0x6C] = new      LD_L_H_In();
    instructions[0x6D] = new      LD_L_L_In();
    instructions[0x6E] = new    LD_L_mHL_In();
    instructions[0x6F] = new      LD_L_A_In();

    instructions[0x70] = new    LD_mHL_B_In(); 
    instructions[0x71] = new    LD_mHL_C_In(); 
    instructions[0x72] = new    LD_mHL_D_In(); 
    instructions[0x73] = new    LD_mHL_E_In(); 
    instructions[0x74] = new    LD_mHL_H_In(); 
    instructions[0x75] = new    LD_mHL_L_In(); 
    instructions[0x76] = new        HALT_In(); 
    instructions[0x77] = new    LD_mHL_A_In(); 
    instructions[0x78] = new      LD_A_B_In(); 
    instructions[0x79] = new      LD_A_C_In(); 
    instructions[0x7A] = new      LD_A_D_In(); 
    instructions[0x7B] = new      LD_A_E_In(); 
    instructions[0x7C] = new      LD_A_H_In(); 
    instructions[0x7D] = new      LD_A_L_In(); 
    instructions[0x7E] = new    LD_A_mHL_In(); 
    instructions[0x7F] = new      LD_A_A_In(); 

    instructions[0x80] = new     ADD_A_B_In();
    instructions[0x81] = new     ADD_A_C_In();
    instructions[0x82] = new     ADD_A_D_In();
    instructions[0x83] = new     ADD_A_E_In();
    instructions[0x84] = new     ADD_A_H_In();
    instructions[0x85] = new     ADD_A_L_In();
    instructions[0x86] = new   ADD_A_mHL_In();
    instructions[0x87] = new     ADD_A_A_In();
    instructions[0x88] = new     ADC_A_B_In();
    instructions[0x89] = new     ADC_A_C_In();
    instructions[0x8A] = new     ADC_A_D_In();
    instructions[0x8B] = new     ADC_A_E_In();
    instructions[0x8C] = new     ADC_A_H_In();
    instructions[0x8D] = new     ADC_A_L_In();
    instructions[0x8E] = new   ADC_A_mHL_In();
    instructions[0x8F] = new     ADC_A_A_In();

    instructions[0x90] = new       SUB_B_In();
    instructions[0x91] = new       SUB_C_In();
    instructions[0x92] = new       SUB_D_In();
    instructions[0x93] = new       SUB_E_In();
    instructions[0x94] = new       SUB_H_In();
    instructions[0x95] = new       SUB_L_In();
    instructions[0x96] = new     SUB_mHL_In();
    instructions[0x97] = new       SUB_A_In();
    instructions[0x98] = new       SBC_B_In();
    instructions[0x99] = new       SBC_C_In();
    instructions[0x9A] = new       SBC_D_In();
    instructions[0x9B] = new       SBC_E_In();
    instructions[0x9C] = new       SBC_H_In();
    instructions[0x9D] = new       SBC_L_In();
    instructions[0x9E] = new     SBC_mHL_In();
    instructions[0x9F] = new       SBC_A_In();

    instructions[0xA0] = new       AND_B_In();
    instructions[0xA1] = new       AND_C_In();
    instructions[0xA2] = new       AND_D_In();
    instructions[0xA3] = new       AND_E_In();
    instructions[0xA4] = new       AND_H_In();
    instructions[0xA5] = new       AND_L_In();
    instructions[0xA6] = new     AND_mHL_In();
    instructions[0xA7] = new       AND_A_In();
    instructions[0xA8] = new       XOR_B_In();
    instructions[0xA9] = new       XOR_C_In();
    instructions[0xAA] = new       XOR_D_In();
    instructions[0xAB] = new       XOR_E_In();
    instructions[0xAC] = new       XOR_H_In();
    instructions[0xAD] = new       XOR_L_In();
    instructions[0xAE] = new     XOR_mHL_In();
    instructions[0xAF] = new       XOR_A_In();
    
    instructions[0xB0] = new        OR_B_In();
    instructions[0xB1] = new        OR_C_In();
    instructions[0xB2] = new        OR_D_In();
    instructions[0xB3] = new        OR_E_In();
    instructions[0xB4] = new        OR_H_In();
    instructions[0xB5] = new        OR_L_In();
    instructions[0xB6] = new      OR_mHL_In();
    instructions[0xB7] = new        OR_A_In();
    instructions[0xB8] = new        CP_B_In();
    instructions[0xB9] = new        CP_C_In();
    instructions[0xBA] = new        CP_D_In();
    instructions[0xBB] = new        CP_E_In();
    instructions[0xBC] = new        CP_H_In();
    instructions[0xBD] = new        CP_L_In();
    instructions[0xBE] = new      CP_mHL_In();
    instructions[0xBF] = new        CP_A_In();

    instructions[0xC0] = new      RET_NZ_In();
    instructions[0xC1] = new      POP_BC_In();
    instructions[0xC2] = new   JP_NZ_a16_In();
    instructions[0xC3] = new      JP_a16_In();
    instructions[0xC4] = new CALL_NZ_a16_In();
    instructions[0xC5] = new     PUSH_BC_In();
    instructions[0xC6] = new    ADD_A_d8_In();
    instructions[0xC7] = new     RST_00H_In();
    instructions[0xC8] = new       RET_Z_In();
    instructions[0xC9] = new         RET_In();
    instructions[0xCA] = new    JP_Z_a16_In();
    instructions[0xCB] = new   PREFIX_CB_In();
    instructions[0xCC] = new  CALL_Z_a16_In();
    instructions[0xCD] = new    CALL_a16_In();
    instructions[0xCE] = new    ADC_A_d8_In();
    instructions[0xCF] = new     RST_08H_In();


    instructions[0xD0] = new      RET_NC_In();
    instructions[0xD1] = new      POP_DE_In();
    instructions[0xD2] = new   JP_NC_a16_In();
    instructions[0xD3] = 0;
    instructions[0xD4] = new CALL_NC_a16_In();
    instructions[0xD5] = new     PUSH_DE_In();
    instructions[0xD6] = new      SUB_d8_In();
    instructions[0xD7] = new     RST_10H_In();
    instructions[0xD8] = new       RET_C_In();
    instructions[0xD9] = new        RETI_In();
    instructions[0xDA] = new    JP_C_a16_In();
    instructions[0xDB] = 0;
    instructions[0xDC] = new  CALL_C_a16_In();
    instructions[0xDD] = 0;
    instructions[0xDE] = new    SBC_A_d8_In();
    instructions[0xDF] = new     RST_18H_In();


    instructions[0xE0] = new    LDH_a8_A_In();
    instructions[0xE1] = new      POP_HL_In();
    instructions[0xE2] = new     LD_mC_A_In();
    instructions[0xE3] = 0;
    instructions[0xE4] = 0;
    instructions[0xE5] = new     PUSH_HL_In();
    instructions[0xE6] = new      AND_d8_In();
    instructions[0xE7] = new     RST_20H_In();
    instructions[0xE8] = new   ADD_SP_r8_In();
    instructions[0xE9] = new      JP_mHL_In();
    instructions[0xEA] = new    LD_a16_A_In();
    instructions[0xEB] = 0;
    instructions[0xEC] = 0;
    instructions[0xED] = 0;
    instructions[0xEE] = new      XOR_d8_In();
    instructions[0xEF] = new     RST_28H_In();


    instructions[0xF0] = new    LDH_A_a8_In();
    instructions[0xF1] = new      POP_AF_In();
    instructions[0xF2] = new     LD_A_mC_In();
    instructions[0xF3] = new          DI_In();
    instructions[0xF4] = 0;
    instructions[0xF5] = new     PUSH_AF_In();
    instructions[0xF6] = new       OR_d8_In();
    instructions[0xF7] = new     RST_30H_In();
    instructions[0xF8] = new LD_HL_SP_r8_In();
    instructions[0xF9] = new    LD_SP_HL_In();
    instructions[0xFA] = new    LD_A_a16_In();
    instructions[0xFB] = new          EI_In();
    instructions[0xFC] = 0;
    instructions[0xFD] = 0;
    instructions[0xFE] = new       CP_d8_In();
    instructions[0xFF] = new     RST_38H_In();
}

LR35902::~LR35902() {
    std::for_each(instructions.begin(), instructions.end(), InstructionDeleter());
    instructions.clear();
}

bool LR35902::retf(uint8 flag) {
    if(flag) {
        ret();
        return true; 
    }
    
    return false; 
}

bool LR35902::retf_n(uint8 flag) {
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

bool LR35902::callf(uint8 flag, uint16 addr) {
    if(flag) {
        call(addr); 
        return true; 
    }
    return false; 
}

bool LR35902::callf_n(uint8 flag, uint16 addr) {
    if(!flag) {
        call(addr); 
        return true; 
    }
    return false; 
}

void LR35902::call(uint16 addr) {
    push(registers.PC); 
    jp(addr); 
}

bool LR35902::jpf(uint8 flag, uint16 addr) {
    if(flag) {
        jp(addr); 
        return true; 
    }
    return false; 
}

bool LR35902::jpf_n(uint8 flag, uint16 addr) {
    if(!flag) {
        jp(addr); 
        return true; 
    }
    return false; 
}

void LR35902::jp(uint16 addr) {
    registers.PC = addr; 
}
    
void LR35902::ei() {
    // TODO 
}
    
void LR35902::di() {
    // TODO 
}
    
void LR35902::push(uint16 reg) {
    registers.SP -= 2; 
    memory.write_16(registers.SP, reg); 
}

void LR35902::pop(uint16& reg) {
    reg = memory.read_16(registers.SP); 
    registers.SP += 2; 
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

void LR35902::add_16_16(uint16& reg1, uint16 reg2) {
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

void LR35902::add_8_8(uint8& reg1, uint8 reg2) {
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

void LR35902::adc_8_8(uint8& reg1, uint8 reg2) {
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

void LR35902::sbc_8_8(uint8& reg1, uint8 reg2) {
    uint8 carry = (registers.c() ? 1 : 0); 
    uint8 nibble_reg1 = reg1 & 0x0F; 
    uint8 nibble_reg2 = reg2 & 0x0F; 
    
    uint8 nibble_result = nibble_reg1 - nibble_reg2 - carry; 
    uint16 result = reg1 - reg2 - carry; 
    
    registers.set_n(); 
    
    if(nibble_result > 0x0F) // borrow from bit 4
        registers.clear_h(); 
    else 
        registers.set_h(); 
    
    if(result > 255) // borrow 
        registers.clear_c(); 
    else
        registers.set_c(); 
    
    if(result == 0) 
        registers.set_z(); 
    else
        registers.clear_z(); 
    
    reg1 = result & 0xFF; 
}

void LR35902::sub_8(uint8 reg) {
    uint8 nibble_reg1 = registers.A & 0x0F; 
    uint8 nibble_reg2 = reg & 0x0F; 
    
    uint8 nibble_result = nibble_reg1 - nibble_reg2; 
    uint16 result = registers.A - reg; 
    
    registers.set_n(); 
    
    if(nibble_result > 0x0F) // borrow from bit 4
        registers.clear_h(); 
    else 
        registers.set_h(); 
    
    if(result > 255) // borrow 
        registers.clear_c(); 
    else
        registers.set_c(); 
    
    if(result == 0) 
        registers.set_z(); 
    else
        registers.clear_z(); 
    
    registers.A = result & 0xFF; 
} 

void LR35902::and_8(uint8 reg) {
    registers.A = registers.A & reg; 
    if(registers.A == 0) 
        registers.set_z(); 
    else 
        registers.clear_z(); 
    registers.clear_n(); 
    registers.set_h(); 
    registers.clear_c(); 
}


void LR35902::xor_8(uint8 reg) {
    registers.A = registers.A ^ reg; 
    if(registers.A == 0) 
        registers.set_z(); 
    else 
        registers.clear_z(); 
    registers.clear_n(); 
    registers.clear_h(); 
    registers.clear_c(); 
}


void LR35902::or_8(uint8 reg) {
    registers.A = registers.A | reg; 
    if(registers.A == 0) 
        registers.set_z(); 
    else 
        registers.clear_z(); 
    registers.clear_n(); 
    registers.clear_h(); 
    registers.clear_c(); 
}


void LR35902::cp_8(uint8 reg) {
    uint8 tmpA = registers.A; // store A 
    sub_8(reg); // basically sets flags
    registers.A = tmpA;       // restore A
}


uint16 LR35902::sign_ext(uint8 value) {
    return (0xF0 * ((value >> 7) & 0x1)) | value; // multiply sign of value (7. bit) with 0xF0 
}

// rotate left, old bit 7 in carry
void LR35902::rlc(uint8& reg) {
    uint8 bit0 = ((reg & 0x80) >> 7); 
    reg = ((reg << 1) & 0xFF) | bit0; 
    
    // flags
    if(!reg) {
        registers.set_z();
    }
    else {
        registers.clear_z(); 
    }
    
    registers.clear_n(); 
    registers.clear_h(); 
    
    if(bit0) {
        registers.set_c(); 
    }
    else {
        registers.clear_c(); 
    }
}

// rotate right, old bit 0 in carry
void LR35902::rrc(uint8& reg) {
    uint8 bit7 = ((reg & 0x01) << 7); 
    reg = ((reg >> 1) & 0xFF) | bit7; 
    
    // flags
    if(!reg) {
        registers.set_z();
    }
    else {
        registers.clear_z(); 
    }
    
    registers.clear_n(); 
    registers.clear_h(); 
    
    if(bit7) {
        registers.set_c(); 
    }
    else {
        registers.clear_c(); 
    }
}

// rotate left through carry
void LR35902::rl(uint8& reg) {
    uint8 carry = (registers.c() ? 1 : 0); 
    uint16 result = reg << 1; 
    reg = (result & 0xFF) | carry; 
    
    // flags
    if(!reg) {
        registers.set_z();
    }
    else {
        registers.clear_z(); 
    }
    
    registers.clear_n(); 
    registers.clear_h(); 
    
    if(result & 0xFF00) {
        registers.set_c(); 
    }
    else {
        registers.clear_c(); 
    }
}

// rotate right through carry
void LR35902::rr(uint8& reg) {
    uint8 carry     = (registers.c() ? 0x80 : 0x00); 
    uint8 new_carry = reg & 0x01; 
    uint16 result   = reg >> 1; 
    reg = (result & 0xFF) | carry; 
    
    // flags
    if(!reg) {
        registers.set_z();
    }
    else {
        registers.clear_z(); 
    }
    
    registers.clear_n(); 
    registers.clear_h(); 
    
    if(new_carry) {
        registers.set_c(); 
    }
    else {
        registers.clear_c(); 
    }
}

void LR35902::sla(uint8& reg) {
    uint16 result = reg << 1; 
    reg = result & 0xFF; 
    
    if(!reg) {
        registers.set_z(); 
    }
    else {
        registers.clear_z(); 
    }
    
    registers.clear_n(); 
    registers.clear_h(); 
    
    if(result & 0xFF00) {
        registers.set_c(); 
    }
    else {
        registers.clear_c(); 
    }
}

void LR35902::sra(uint8& reg) {
    uint8 bit0 = reg & 0x01; 
    reg = (reg >> 1) & 0xFF; 
    
    // old MSB = new MSB (sign does not change) 
    reg = reg | ((reg & 0x40) << 1); 
    
    if(!reg) {
        registers.set_z(); 
    }
    else {
        registers.clear_z(); 
    }
    
    registers.clear_n(); 
    registers.clear_h(); 
    
    if(bit0) {
        registers.set_c(); 
    }
    else {
        registers.clear_c(); 
    }
}

// swap upper and lower nubbles of reg
void LR35902::swap(uint8& reg) {
    uint8 high = (reg & 0xF0) >> 4; 
    reg = ((reg << 4) | high) & 0xFF;
    
    if(!reg) {
        registers.set_z(); 
    }
    else {
        registers.clear_z(); 
    }
    
    registers.clear_n(); 
    registers.clear_h(); 
    registers.clear_c(); 
}

void LR35902::srl(uint8& reg) {
    uint8 bit0 = reg & 0x01; 
    reg = (reg >> 1) & 0xFF; 
    
    if(!reg) {
        registers.set_z(); 
    }
    else {
        registers.clear_z(); 
    }
    
    registers.clear_n(); 
    registers.clear_h(); 
    
    if(bit0) {
        registers.set_c(); 
    }
    else {
        registers.clear_c(); 
    }
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

// Z is 1 if bit b of reg is 0, else it is 0
void LR35902::bit(uint8 b, uint8 reg) {
    if((1 << b) & reg) { // if bit is set (0-7)
        registers.clear_z(); 
    }
    else {
        registers.set_z(); 
    }
    
    registers.clear_n(); 
    registers.set_h();
    // flag C unaffected
}

// reset bit b of reg (flags unaffected)
void LR35902::res(uint8 b, uint8& reg) {
    uint8 mask = (1 << b); 
    mask = ~mask; 
    reg = mask & reg; 
}

// set bit b of reg (flags uneffected)
void LR35902::set(uint8 b, uint8& reg) {
    uint8 bit_b = (1 << b); 
    reg = reg | bit_b; 
}

    

void LR35902::halt() {
    bhalt = true; 
}

void LR35902::init() {
    registers.PC = 0; 
}

void LR35902::disassemble() {
    registers.PC = 0x000; 
    
    while(registers.PC < 0x100) {
        if(registers.PC == 0x00A8) // skip Logo and other Data
            registers.PC = 0x00E0; 
        uint8 opcode = 0; 
        Instruction* inst = instructions[opcode = memory.read_8(registers.PC)];
        if(inst == NULL) {
            std::cout << "Invalid instruction: " << (int)opcode << std::endl;
            std::cout << "PC: " << registers.PC << std::endl; 
            break; 
        }
        else {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << registers.PC << " - "; 
            std::cout << std::setw(2) << (int)opcode << ": " << inst->alt_name << std::endl; 
            if(opcode == 0xCB)
                inst->addedBytes = 1; 
            else 
                inst->addedBytes = 0; 
            registers.PC += inst->bytes;
            registers.PC += inst->addedBytes;
        }
    }
}

void LR35902::single_step() {
    uint8 opcode; 
    Instruction* inst = instructions[opcode = memory.read_8(registers.PC)];
    if(inst == NULL) {
        std::cout << "Invalid instruction: " << (int)opcode << std::endl;
        std::cout << "PC: " << registers.PC << std::endl; 
    }
    else {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << registers.PC << " - "; 
        std::cout << std::setw(2) << (int)opcode << ": " << inst->alt_name << std::endl; 
 
        std::cout << "State before instruction: " << std::endl; 
        print_state(); 
        inst->execute(*this, memory); 
        // registers.PC += inst->bytes;
       //  registers.PC += inst->addedBytes;
        std::cout << "State after instruction: " << std::endl; 
        print_state(); 
    }
}

void LR35902::print_state() {
    // print registers
    std::cout << std::setfill(' '); 
    std::cout << std::setw(7) << "PC" << std::setw(7) << "AF" << std::setw(7) << "BC" << std::setw(7) << "DE" << std::setw(7) << "HL" << std::setw(7) << "SP" << std::endl; 
    std::cout << std::setw(7) << registers.PC << std::setw(7) << registers.AF << std::setw(7) << registers.BC << std::setw(7) << registers.DE << std::setw(7) << registers.HL << std::setw(7) << registers.SP << std::endl; 
}
    

