#include "LR35902.hpp"
#include "InstructionSet.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>

LR35902::LR35902() : running(true), memory(MEMORY_SIZE), debug_mode(false), debug_hold(false), cycle_counter(0) {
    instructions = std::vector<std::unique_ptr<Instruction>>(0x100); 
    instructions[0x00] = std::unique_ptr<Instruction>(new         NOP_In());
    instructions[0x01] = std::unique_ptr<Instruction>(new   LD_BC_d16_In());
    instructions[0x02] = std::unique_ptr<Instruction>(new    LD_mBC_A_In());
    instructions[0x03] = std::unique_ptr<Instruction>(new      INC_BC_In());
    instructions[0x04] = std::unique_ptr<Instruction>(new       INC_B_In());
    instructions[0x05] = std::unique_ptr<Instruction>(new       DEC_B_In());
    instructions[0x06] = std::unique_ptr<Instruction>(new     LD_B_d8_In());
    instructions[0x07] = std::unique_ptr<Instruction>(new        RLCA_In());
    instructions[0x08] = std::unique_ptr<Instruction>(new   LD_a16_SP_In());
    instructions[0x09] = std::unique_ptr<Instruction>(new   ADD_HL_BC_In());
    instructions[0x0A] = std::unique_ptr<Instruction>(new    LD_A_mBC_In());
    instructions[0x0B] = std::unique_ptr<Instruction>(new      DEC_BC_In());
    instructions[0x0C] = std::unique_ptr<Instruction>(new       INC_C_In());
    instructions[0x0D] = std::unique_ptr<Instruction>(new       DEC_C_In());
    instructions[0x0E] = std::unique_ptr<Instruction>(new     LD_C_d8_In());
    instructions[0x0F] = std::unique_ptr<Instruction>(new        RRCA_In());

    instructions[0x10] = std::unique_ptr<Instruction>(new        STOP_In());
    instructions[0x11] = std::unique_ptr<Instruction>(new   LD_DE_d16_In());
    instructions[0x12] = std::unique_ptr<Instruction>(new    LD_mDE_A_In());
    instructions[0x13] = std::unique_ptr<Instruction>(new      INC_DE_In());
    instructions[0x14] = std::unique_ptr<Instruction>(new       INC_D_In());
    instructions[0x15] = std::unique_ptr<Instruction>(new       DEC_D_In());
    instructions[0x16] = std::unique_ptr<Instruction>(new     LD_D_d8_In());
    instructions[0x17] = std::unique_ptr<Instruction>(new         RLA_In());
    instructions[0x18] = std::unique_ptr<Instruction>(new       JR_r8_In());
    instructions[0x19] = std::unique_ptr<Instruction>(new   ADD_HL_DE_In());
    instructions[0x1A] = std::unique_ptr<Instruction>(new    LD_A_mDE_In());
    instructions[0x1B] = std::unique_ptr<Instruction>(new      DEC_DE_In());
    instructions[0x1C] = std::unique_ptr<Instruction>(new       INC_E_In());
    instructions[0x1D] = std::unique_ptr<Instruction>(new       DEC_E_In());
    instructions[0x1E] = std::unique_ptr<Instruction>(new     LD_E_d8_In());
    instructions[0x1F] = std::unique_ptr<Instruction>(new         RRA_In());

    instructions[0x20] = std::unique_ptr<Instruction>(new    JR_NZ_r8_In());
    instructions[0x21] = std::unique_ptr<Instruction>(new   LD_HL_d16_In());
    instructions[0x22] = std::unique_ptr<Instruction>(new   LD_mHLp_A_In());
    instructions[0x23] = std::unique_ptr<Instruction>(new      INC_HL_In());
    instructions[0x24] = std::unique_ptr<Instruction>(new       INC_H_In());
    instructions[0x25] = std::unique_ptr<Instruction>(new       DEC_H_In());
    instructions[0x26] = std::unique_ptr<Instruction>(new     LD_H_d8_In());
    instructions[0x27] = std::unique_ptr<Instruction>(new         DAA_In());
    instructions[0x28] = std::unique_ptr<Instruction>(new     JR_Z_r8_In());
    instructions[0x29] = std::unique_ptr<Instruction>(new   ADD_HL_HL_In());
    instructions[0x2A] = std::unique_ptr<Instruction>(new   LD_A_mHLp_In());
    instructions[0x2B] = std::unique_ptr<Instruction>(new      DEC_HL_In());
    instructions[0x2C] = std::unique_ptr<Instruction>(new       INC_L_In());
    instructions[0x2D] = std::unique_ptr<Instruction>(new       DEC_L_In());
    instructions[0x2E] = std::unique_ptr<Instruction>(new     LD_L_d8_In());
    instructions[0x2F] = std::unique_ptr<Instruction>(new         CPL_In());

    instructions[0x30] = std::unique_ptr<Instruction>(new    JR_NC_r8_In());
    instructions[0x31] = std::unique_ptr<Instruction>(new   LD_SP_d16_In());
    instructions[0x32] = std::unique_ptr<Instruction>(new   LD_mHLm_A_In());
    instructions[0x33] = std::unique_ptr<Instruction>(new      INC_SP_In());
    instructions[0x34] = std::unique_ptr<Instruction>(new     INC_mHL_In());
    instructions[0x35] = std::unique_ptr<Instruction>(new     DEC_mHL_In());
    instructions[0x36] = std::unique_ptr<Instruction>(new   LD_mHL_d8_In());
    instructions[0x37] = std::unique_ptr<Instruction>(new         SCF_In());
    instructions[0x38] = std::unique_ptr<Instruction>(new     JR_C_r8_In());
    instructions[0x39] = std::unique_ptr<Instruction>(new   ADD_HL_SP_In());
    instructions[0x3A] = std::unique_ptr<Instruction>(new   LD_A_mHLm_In());
    instructions[0x3B] = std::unique_ptr<Instruction>(new      DEC_SP_In());
    instructions[0x3C] = std::unique_ptr<Instruction>(new       INC_A_In());
    instructions[0x3D] = std::unique_ptr<Instruction>(new       DEC_A_In());
    instructions[0x3E] = std::unique_ptr<Instruction>(new     LD_A_d8_In());
    instructions[0x3F] = std::unique_ptr<Instruction>(new         CCF_In());

    instructions[0x40] = std::unique_ptr<Instruction>(new      LD_B_B_In());
    instructions[0x41] = std::unique_ptr<Instruction>(new      LD_B_C_In());
    instructions[0x42] = std::unique_ptr<Instruction>(new      LD_B_D_In());
    instructions[0x43] = std::unique_ptr<Instruction>(new      LD_B_E_In());
    instructions[0x44] = std::unique_ptr<Instruction>(new      LD_B_H_In());
    instructions[0x45] = std::unique_ptr<Instruction>(new      LD_B_L_In());
    instructions[0x46] = std::unique_ptr<Instruction>(new    LD_B_mHL_In());
    instructions[0x47] = std::unique_ptr<Instruction>(new      LD_B_A_In());
    instructions[0x48] = std::unique_ptr<Instruction>(new      LD_C_B_In());
    instructions[0x49] = std::unique_ptr<Instruction>(new      LD_C_C_In());
    instructions[0x4A] = std::unique_ptr<Instruction>(new      LD_C_D_In());
    instructions[0x4B] = std::unique_ptr<Instruction>(new      LD_C_E_In());
    instructions[0x4C] = std::unique_ptr<Instruction>(new      LD_C_H_In());
    instructions[0x4D] = std::unique_ptr<Instruction>(new      LD_C_L_In());
    instructions[0x4E] = std::unique_ptr<Instruction>(new    LD_C_mHL_In());
    instructions[0x4F] = std::unique_ptr<Instruction>(new      LD_C_A_In());

    instructions[0x50] = std::unique_ptr<Instruction>(new      LD_D_B_In());
    instructions[0x51] = std::unique_ptr<Instruction>(new      LD_D_C_In());
    instructions[0x52] = std::unique_ptr<Instruction>(new      LD_D_D_In());
    instructions[0x53] = std::unique_ptr<Instruction>(new      LD_D_E_In());
    instructions[0x54] = std::unique_ptr<Instruction>(new      LD_D_H_In());
    instructions[0x55] = std::unique_ptr<Instruction>(new      LD_D_L_In());
    instructions[0x56] = std::unique_ptr<Instruction>(new    LD_D_mHL_In());
    instructions[0x57] = std::unique_ptr<Instruction>(new      LD_D_A_In());
    instructions[0x58] = std::unique_ptr<Instruction>(new      LD_E_B_In());
    instructions[0x59] = std::unique_ptr<Instruction>(new      LD_E_C_In());
    instructions[0x5A] = std::unique_ptr<Instruction>(new      LD_E_D_In());
    instructions[0x5B] = std::unique_ptr<Instruction>(new      LD_E_E_In());
    instructions[0x5C] = std::unique_ptr<Instruction>(new      LD_E_H_In());
    instructions[0x5D] = std::unique_ptr<Instruction>(new      LD_E_L_In());
    instructions[0x5E] = std::unique_ptr<Instruction>(new    LD_E_mHL_In());
    instructions[0x5F] = std::unique_ptr<Instruction>(new      LD_E_A_In());

    instructions[0x60] = std::unique_ptr<Instruction>(new      LD_H_B_In());
    instructions[0x61] = std::unique_ptr<Instruction>(new      LD_H_C_In());
    instructions[0x62] = std::unique_ptr<Instruction>(new      LD_H_D_In());
    instructions[0x63] = std::unique_ptr<Instruction>(new      LD_H_E_In());
    instructions[0x64] = std::unique_ptr<Instruction>(new      LD_H_H_In());
    instructions[0x65] = std::unique_ptr<Instruction>(new      LD_H_L_In());
    instructions[0x66] = std::unique_ptr<Instruction>(new    LD_H_mHL_In());
    instructions[0x67] = std::unique_ptr<Instruction>(new      LD_H_A_In());
    instructions[0x68] = std::unique_ptr<Instruction>(new      LD_L_B_In());
    instructions[0x69] = std::unique_ptr<Instruction>(new      LD_L_C_In());
    instructions[0x6A] = std::unique_ptr<Instruction>(new      LD_L_D_In());
    instructions[0x6B] = std::unique_ptr<Instruction>(new      LD_L_E_In());
    instructions[0x6C] = std::unique_ptr<Instruction>(new      LD_L_H_In());
    instructions[0x6D] = std::unique_ptr<Instruction>(new      LD_L_L_In());
    instructions[0x6E] = std::unique_ptr<Instruction>(new    LD_L_mHL_In());
    instructions[0x6F] = std::unique_ptr<Instruction>(new      LD_L_A_In());

    instructions[0x70] = std::unique_ptr<Instruction>(new    LD_mHL_B_In()); 
    instructions[0x71] = std::unique_ptr<Instruction>(new    LD_mHL_C_In()); 
    instructions[0x72] = std::unique_ptr<Instruction>(new    LD_mHL_D_In()); 
    instructions[0x73] = std::unique_ptr<Instruction>(new    LD_mHL_E_In()); 
    instructions[0x74] = std::unique_ptr<Instruction>(new    LD_mHL_H_In()); 
    instructions[0x75] = std::unique_ptr<Instruction>(new    LD_mHL_L_In()); 
    instructions[0x76] = std::unique_ptr<Instruction>(new        HALT_In()); 
    instructions[0x77] = std::unique_ptr<Instruction>(new    LD_mHL_A_In()); 
    instructions[0x78] = std::unique_ptr<Instruction>(new      LD_A_B_In()); 
    instructions[0x79] = std::unique_ptr<Instruction>(new      LD_A_C_In()); 
    instructions[0x7A] = std::unique_ptr<Instruction>(new      LD_A_D_In()); 
    instructions[0x7B] = std::unique_ptr<Instruction>(new      LD_A_E_In()); 
    instructions[0x7C] = std::unique_ptr<Instruction>(new      LD_A_H_In()); 
    instructions[0x7D] = std::unique_ptr<Instruction>(new      LD_A_L_In()); 
    instructions[0x7E] = std::unique_ptr<Instruction>(new    LD_A_mHL_In()); 
    instructions[0x7F] = std::unique_ptr<Instruction>(new      LD_A_A_In()); 

    instructions[0x80] = std::unique_ptr<Instruction>(new     ADD_A_B_In());
    instructions[0x81] = std::unique_ptr<Instruction>(new     ADD_A_C_In());
    instructions[0x82] = std::unique_ptr<Instruction>(new     ADD_A_D_In());
    instructions[0x83] = std::unique_ptr<Instruction>(new     ADD_A_E_In());
    instructions[0x84] = std::unique_ptr<Instruction>(new     ADD_A_H_In());
    instructions[0x85] = std::unique_ptr<Instruction>(new     ADD_A_L_In());
    instructions[0x86] = std::unique_ptr<Instruction>(new   ADD_A_mHL_In());
    instructions[0x87] = std::unique_ptr<Instruction>(new     ADD_A_A_In());
    instructions[0x88] = std::unique_ptr<Instruction>(new     ADC_A_B_In());
    instructions[0x89] = std::unique_ptr<Instruction>(new     ADC_A_C_In());
    instructions[0x8A] = std::unique_ptr<Instruction>(new     ADC_A_D_In());
    instructions[0x8B] = std::unique_ptr<Instruction>(new     ADC_A_E_In());
    instructions[0x8C] = std::unique_ptr<Instruction>(new     ADC_A_H_In());
    instructions[0x8D] = std::unique_ptr<Instruction>(new     ADC_A_L_In());
    instructions[0x8E] = std::unique_ptr<Instruction>(new   ADC_A_mHL_In());
    instructions[0x8F] = std::unique_ptr<Instruction>(new     ADC_A_A_In());

    instructions[0x90] = std::unique_ptr<Instruction>(new       SUB_B_In());
    instructions[0x91] = std::unique_ptr<Instruction>(new       SUB_C_In());
    instructions[0x92] = std::unique_ptr<Instruction>(new       SUB_D_In());
    instructions[0x93] = std::unique_ptr<Instruction>(new       SUB_E_In());
    instructions[0x94] = std::unique_ptr<Instruction>(new       SUB_H_In());
    instructions[0x95] = std::unique_ptr<Instruction>(new       SUB_L_In());
    instructions[0x96] = std::unique_ptr<Instruction>(new     SUB_mHL_In());
    instructions[0x97] = std::unique_ptr<Instruction>(new       SUB_A_In());
    instructions[0x98] = std::unique_ptr<Instruction>(new       SBC_B_In());
    instructions[0x99] = std::unique_ptr<Instruction>(new       SBC_C_In());
    instructions[0x9A] = std::unique_ptr<Instruction>(new       SBC_D_In());
    instructions[0x9B] = std::unique_ptr<Instruction>(new       SBC_E_In());
    instructions[0x9C] = std::unique_ptr<Instruction>(new       SBC_H_In());
    instructions[0x9D] = std::unique_ptr<Instruction>(new       SBC_L_In());
    instructions[0x9E] = std::unique_ptr<Instruction>(new     SBC_mHL_In());
    instructions[0x9F] = std::unique_ptr<Instruction>(new       SBC_A_In());

    instructions[0xA0] = std::unique_ptr<Instruction>(new       AND_B_In());
    instructions[0xA1] = std::unique_ptr<Instruction>(new       AND_C_In());
    instructions[0xA2] = std::unique_ptr<Instruction>(new       AND_D_In());
    instructions[0xA3] = std::unique_ptr<Instruction>(new       AND_E_In());
    instructions[0xA4] = std::unique_ptr<Instruction>(new       AND_H_In());
    instructions[0xA5] = std::unique_ptr<Instruction>(new       AND_L_In());
    instructions[0xA6] = std::unique_ptr<Instruction>(new     AND_mHL_In());
    instructions[0xA7] = std::unique_ptr<Instruction>(new       AND_A_In());
    instructions[0xA8] = std::unique_ptr<Instruction>(new       XOR_B_In());
    instructions[0xA9] = std::unique_ptr<Instruction>(new       XOR_C_In());
    instructions[0xAA] = std::unique_ptr<Instruction>(new       XOR_D_In());
    instructions[0xAB] = std::unique_ptr<Instruction>(new       XOR_E_In());
    instructions[0xAC] = std::unique_ptr<Instruction>(new       XOR_H_In());
    instructions[0xAD] = std::unique_ptr<Instruction>(new       XOR_L_In());
    instructions[0xAE] = std::unique_ptr<Instruction>(new     XOR_mHL_In());
    instructions[0xAF] = std::unique_ptr<Instruction>(new       XOR_A_In());
    
    instructions[0xB0] = std::unique_ptr<Instruction>(new        OR_B_In());
    instructions[0xB1] = std::unique_ptr<Instruction>(new        OR_C_In());
    instructions[0xB2] = std::unique_ptr<Instruction>(new        OR_D_In());
    instructions[0xB3] = std::unique_ptr<Instruction>(new        OR_E_In());
    instructions[0xB4] = std::unique_ptr<Instruction>(new        OR_H_In());
    instructions[0xB5] = std::unique_ptr<Instruction>(new        OR_L_In());
    instructions[0xB6] = std::unique_ptr<Instruction>(new      OR_mHL_In());
    instructions[0xB7] = std::unique_ptr<Instruction>(new        OR_A_In());
    instructions[0xB8] = std::unique_ptr<Instruction>(new        CP_B_In());
    instructions[0xB9] = std::unique_ptr<Instruction>(new        CP_C_In());
    instructions[0xBA] = std::unique_ptr<Instruction>(new        CP_D_In());
    instructions[0xBB] = std::unique_ptr<Instruction>(new        CP_E_In());
    instructions[0xBC] = std::unique_ptr<Instruction>(new        CP_H_In());
    instructions[0xBD] = std::unique_ptr<Instruction>(new        CP_L_In());
    instructions[0xBE] = std::unique_ptr<Instruction>(new      CP_mHL_In());
    instructions[0xBF] = std::unique_ptr<Instruction>(new        CP_A_In());

    instructions[0xC0] = std::unique_ptr<Instruction>(new      RET_NZ_In());
    instructions[0xC1] = std::unique_ptr<Instruction>(new      POP_BC_In());
    instructions[0xC2] = std::unique_ptr<Instruction>(new   JP_NZ_a16_In());
    instructions[0xC3] = std::unique_ptr<Instruction>(new      JP_a16_In());
    instructions[0xC4] = std::unique_ptr<Instruction>(new CALL_NZ_a16_In());
    instructions[0xC5] = std::unique_ptr<Instruction>(new     PUSH_BC_In());
    instructions[0xC6] = std::unique_ptr<Instruction>(new    ADD_A_d8_In());
    instructions[0xC7] = std::unique_ptr<Instruction>(new     RST_00H_In());
    instructions[0xC8] = std::unique_ptr<Instruction>(new       RET_Z_In());
    instructions[0xC9] = std::unique_ptr<Instruction>(new         RET_In());
    instructions[0xCA] = std::unique_ptr<Instruction>(new    JP_Z_a16_In());
    instructions[0xCB] = std::unique_ptr<Instruction>(new   PREFIX_CB_In());
    instructions[0xCC] = std::unique_ptr<Instruction>(new  CALL_Z_a16_In());
    instructions[0xCD] = std::unique_ptr<Instruction>(new    CALL_a16_In());
    instructions[0xCE] = std::unique_ptr<Instruction>(new    ADC_A_d8_In());
    instructions[0xCF] = std::unique_ptr<Instruction>(new     RST_08H_In());


    instructions[0xD0] = std::unique_ptr<Instruction>(new      RET_NC_In());
    instructions[0xD1] = std::unique_ptr<Instruction>(new      POP_DE_In());
    instructions[0xD2] = std::unique_ptr<Instruction>(new   JP_NC_a16_In());
    // instructions[0xD3]; 
    instructions[0xD4] = std::unique_ptr<Instruction>(new CALL_NC_a16_In());
    instructions[0xD5] = std::unique_ptr<Instruction>(new     PUSH_DE_In());
    instructions[0xD6] = std::unique_ptr<Instruction>(new      SUB_d8_In());
    instructions[0xD7] = std::unique_ptr<Instruction>(new     RST_10H_In());
    instructions[0xD8] = std::unique_ptr<Instruction>(new       RET_C_In());
    instructions[0xD9] = std::unique_ptr<Instruction>(new        RETI_In());
    instructions[0xDA] = std::unique_ptr<Instruction>(new    JP_C_a16_In());
    // instructions[0xDB]; 
    instructions[0xDC] = std::unique_ptr<Instruction>(new  CALL_C_a16_In());
    // instructions[0xDD]; 
    instructions[0xDE] = std::unique_ptr<Instruction>(new    SBC_A_d8_In());
    instructions[0xDF] = std::unique_ptr<Instruction>(new     RST_18H_In());


    instructions[0xE0] = std::unique_ptr<Instruction>(new    LDH_a8_A_In());
    instructions[0xE1] = std::unique_ptr<Instruction>(new      POP_HL_In());
    instructions[0xE2] = std::unique_ptr<Instruction>(new     LD_mC_A_In());
    // instructions[0xE3];
    // instructions[0xE4];
    instructions[0xE5] = std::unique_ptr<Instruction>(new     PUSH_HL_In());
    instructions[0xE6] = std::unique_ptr<Instruction>(new      AND_d8_In());
    instructions[0xE7] = std::unique_ptr<Instruction>(new     RST_20H_In());
    instructions[0xE8] = std::unique_ptr<Instruction>(new   ADD_SP_r8_In());
    instructions[0xE9] = std::unique_ptr<Instruction>(new      JP_HL_In());
    instructions[0xEA] = std::unique_ptr<Instruction>(new    LD_a16_A_In());
    // instructions[0xEB];
    // instructions[0xEC];
    // instructions[0xED];
    instructions[0xEE] = std::unique_ptr<Instruction>(new      XOR_d8_In());
    instructions[0xEF] = std::unique_ptr<Instruction>(new     RST_28H_In());


    instructions[0xF0] = std::unique_ptr<Instruction>(new    LDH_A_a8_In());
    instructions[0xF1] = std::unique_ptr<Instruction>(new      POP_AF_In());
    instructions[0xF2] = std::unique_ptr<Instruction>(new     LD_A_mC_In());
    instructions[0xF3] = std::unique_ptr<Instruction>(new          DI_In());
    // instructions[0xF4]; 
    instructions[0xF5] = std::unique_ptr<Instruction>(new     PUSH_AF_In());
    instructions[0xF6] = std::unique_ptr<Instruction>(new       OR_d8_In());
    instructions[0xF7] = std::unique_ptr<Instruction>(new     RST_30H_In());
    instructions[0xF8] = std::unique_ptr<Instruction>(new LD_HL_SP_r8_In());
    instructions[0xF9] = std::unique_ptr<Instruction>(new    LD_SP_HL_In());
    instructions[0xFA] = std::unique_ptr<Instruction>(new    LD_A_a16_In());
    instructions[0xFB] = std::unique_ptr<Instruction>(new          EI_In());
    // instructions[0xFC]; 
    // instructions[0xFD]; 
    instructions[0xFE] = std::unique_ptr<Instruction>(new       CP_d8_In());
    instructions[0xFF] = std::unique_ptr<Instruction>(new     RST_38H_In());
}

LR35902::~LR35902() { }

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

bool LR35902::callf(uint8 flag, uint16 addr, uint16 next_pc) {
    if(flag) {
        call(addr, next_pc); 
        return true; 
    }
    return false; 
}

bool LR35902::callf_n(uint8 flag, uint16 addr, uint16 next_pc) {
    if(!flag) {
        call(addr, next_pc); 
        return true; 
    }
    return false; 
}

void LR35902::call(uint16 addr, uint16 next_pc) {
    push(next_pc); 
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
    if(reg == 0) {                     // Z - result == 0?
        registers.set_z();
    }
    else {
        registers.clear_z(); 
    }
    registers.clear_n();                // N - 0
    
    // bug fix: if lower nibble becomes 0 we had a carry over bit 3 to 4
    if((reg & 0x0F) == 0x00) {                  // H - carry from bit 3 to 4 (15 to 16 or 0x0F to 0x10)
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
    if(reg == 0)  {                    // Z - result == 0? 
        registers.set_z();
    }
    else {
        registers.clear_z(); 
    }
    registers.set_n();                 // N - 1 a substraction was done
    
    // fixed bug: half carry is set everytime lower nibble becomes F
    if((reg & 0x0F) == 0x0F) {         // H - carry from bit 3 to 4 (15 to 16 or 0x0F to 0x10)
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
    
    reg1 = result & 0xFF; 
    
    if(reg1 == 0) 
        registers.set_z(); 
    else
        registers.clear_z(); 
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
    
    reg1 = result & 0xFF; 
    
    if(reg1 == 0) 
        registers.set_z(); 
    else
        registers.clear_z(); 
}

void LR35902::sbc_8_8(uint8& reg1, uint8 reg2) {
    uint8 carry = (registers.c() ? 1 : 0); 
    uint8 nibble_reg1 = reg1 & 0x0F; 
    uint8 nibble_reg2 = reg2 & 0x0F; 
    
    uint8 nibble_result = nibble_reg1 - nibble_reg2 - carry; 
    uint16 result = reg1 - reg2 - carry; 
    
    registers.set_n(); 
    
    if(nibble_result > 0x0F) // borrow from bit 4
        registers.set_h(); 
    else 
        registers.clear_h(); 
    
    if(result > 255) // borrow 
        registers.set_c(); 
    else
        registers.clear_c(); 
    
    if(result == 0) 
        registers.set_z(); 
    else
        registers.clear_z(); 
    
    reg1 = result & 0xFF; 
}

void LR35902::sub_8(uint8 reg) {
    uint8 nibble_reg1 = registers.A & (uint8)0xF; 
    uint8 nibble_reg2 = reg & (uint8)0xF; 
    
    uint8 nibble_result = nibble_reg1 - nibble_reg2; 
    uint16 result = registers.A - reg; 
    registers.set_n(); 
    
    if(nibble_result > 0x0F) // borrow from bit 4
        registers.set_h(); 
    else 
        registers.clear_h(); 
    
    if(result > 255) // borrow (wrong description in documentation) 
        registers.set_c(); 
    else
        registers.clear_c(); 
    
    registers.A = result & 0xFF; 
    
    if(registers.A == 0) 
        registers.set_z(); 
    else
        registers.clear_z(); 
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
        Instruction* inst = instructions[opcode = memory.read_8(registers.PC)].get();
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

void LR35902::single_step(bool verbose) {
    static std::ofstream debug_out("debug.txt"); 
    
    uint8 opcode; 
    Instruction* inst = instructions[opcode = memory.read_8(registers.PC)].get();

    if(inst == NULL) {
        if(verbose) {
            std::cout << "Invalid instruction: " << (int)opcode << std::endl;
            std::cout << "PC: " << registers.PC << std::endl; 
        }
    }
    else {
        if(verbose) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << registers.PC << " - "; 
            std::cout << std::setw(2) << (int)opcode << ": " << inst->alt_name << std::endl; 
    
            std::cout << "State before instruction: " << std::endl; 
            print_state(); 
        }
        if(debug_mode) {
            if(!debug_hold) {
                TraceEntry te(registers, inst); 
                inst->execute(*this, memory); 
                te.registers_after = registers; 
                trace.push_back(te); 
                if(inst->alt_name == "RST 38H") 
                    debug_hold = true; 
            }
        }
        else {
            static bool once = false; 
            if(!once && registers.PC >= 0xFF);  
               //  once = true; 
            
            if(once) {
                std::cout << "cpu cycle counter: " << cycle_counter << std::endl; 
            debug_out << std::hex << std::setw(4) << std::setfill('0') << (int)opcode << std::endl; 
            debug_out << std::hex << std::setw(4) << std::setfill('0') << registers.PC << " " 
                      << std::hex << std::setw(4) << std::setfill('0') << registers.AF << " " 
                      << std::hex << std::setw(4) << std::setfill('0') << registers.BC << " "  
                      << std::hex << std::setw(4) << std::setfill('0') << registers.DE << " " 
                      << std::hex << std::setw(4) << std::setfill('0') << registers.HL << " " 
                      << std::hex << std::setw(4) << std::setfill('0') << registers.SP << std::endl; 
            }    
            // std::cout << "registers.PC + inst->bytes: " << registers.PC << " + " << (int)inst->bytes << ": " << registers.PC + inst->bytes << std::endl;  
            inst->execute(*this, memory); 
     
            if(once) {
            debug_out << std::hex << std::setw(4) << std::setfill('0') << registers.PC << " " 
                      << std::hex << std::setw(4) << std::setfill('0') << registers.AF << " " 
                      << std::hex << std::setw(4) << std::setfill('0') << registers.BC << " " 
                      << std::hex << std::setw(4) << std::setfill('0') << registers.DE << " " 
                      << std::hex << std::setw(4) << std::setfill('0') << registers.HL << " " 
                      << std::hex << std::setw(4) << std::setfill('0') << registers.SP << std::endl << std::endl; 
            }
        }
        // registers.PC += inst->bytes;
       //  registers.PC += inst->addedBytes;
        
        if(verbose) {
            std::cout << "State after instruction: " << std::endl; 
            print_state(); 
        }
    }
}

void LR35902::print_state(std::ostream& out/* = std::cout */) {
    // print registers
    out << std::setfill(' '); 
    out << std::setw(7) << "PC" << std::setw(7) << "AF" << std::setw(7) << "BC" << std::setw(7) << "DE" << std::setw(7) << "HL" << std::setw(7) << "SP" << std::endl; 
    out << std::setw(7) << registers.PC << std::setw(7) << registers.AF << std::setw(7) << registers.BC << std::setw(7) << registers.DE << std::setw(7) << registers.HL << std::setw(7) << registers.SP << std::endl; 
}

void LR35902::print_state(Registers& registers, std::ostream& out /* = std::cout*/) {
    // print registers
    out << std::setfill(' '); 
    out << std::setw(7) << "PC" << std::setw(7) << "AF" << std::setw(7) << "BC" << std::setw(7) << "DE" << std::setw(7) << "HL" << std::setw(7) << "SP" << std::endl; 
    out << std::setw(7) << registers.PC << std::setw(7) << registers.AF << std::setw(7) << registers.BC << std::setw(7) << registers.DE << std::setw(7) << registers.HL << std::setw(7) << registers.SP << std::endl; 
}
    

