#include "InstructionSet.hpp"
#include "InstructionSet_PrefixCB.hpp"

#include "LR35902.hpp"
#include "Memory.hpp"

#include <iostream> 

// Constructors

 PREFIX_CB_In::PREFIX_CB_In()   : Instruction( "CB",    "PREFIX CB", "----", 0xCB, 1,  4, VERBOSE_FLAG) { 
     _cb_instructions = std::vector<Instruction*>(0x100, static_cast<Instruction*>(0)); 
     _cb_instructions[0x00] = new   CB_RLC_B_In();
     _cb_instructions[0x01] = new   CB_RLC_C_In();
     _cb_instructions[0x02] = new   CB_RLC_D_In();
     _cb_instructions[0x03] = new   CB_RLC_E_In();
     _cb_instructions[0x04] = new   CB_RLC_H_In();
     _cb_instructions[0x05] = new   CB_RLC_L_In();
     _cb_instructions[0x06] = new CB_RLC_mHL_In();
     _cb_instructions[0x07] = new   CB_RLC_A_In();
     _cb_instructions[0x08] = new   CB_RRC_B_In();
     _cb_instructions[0x09] = new   CB_RRC_C_In();
     _cb_instructions[0x0A] = new   CB_RRC_D_In();
     _cb_instructions[0x0B] = new   CB_RRC_E_In();
     _cb_instructions[0x0C] = new   CB_RRC_H_In();
     _cb_instructions[0x0D] = new   CB_RRC_L_In();
     _cb_instructions[0x0E] = new CB_RRC_mHL_In();
     _cb_instructions[0x0F] = new   CB_RRC_A_In();
     
     _cb_instructions[0x10] = new   CB_RL_B_In();
     _cb_instructions[0x11] = new   CB_RL_C_In();
     _cb_instructions[0x12] = new   CB_RL_D_In();
     _cb_instructions[0x13] = new   CB_RL_E_In();
     _cb_instructions[0x14] = new   CB_RL_H_In();
     _cb_instructions[0x15] = new   CB_RL_L_In();
     _cb_instructions[0x16] = new CB_RL_mHL_In();
     _cb_instructions[0x17] = new   CB_RL_A_In();
     _cb_instructions[0x18] = new   CB_RR_B_In();
     _cb_instructions[0x19] = new   CB_RR_C_In();
     _cb_instructions[0x1A] = new   CB_RR_D_In();
     _cb_instructions[0x1B] = new   CB_RR_E_In();
     _cb_instructions[0x1C] = new   CB_RR_H_In();
     _cb_instructions[0x1D] = new   CB_RR_L_In();
     _cb_instructions[0x1E] = new CB_RR_mHL_In();
     _cb_instructions[0x1F] = new   CB_RR_A_In();
     
     _cb_instructions[0x20] = new   CB_SLA_B_In();
     _cb_instructions[0x21] = new   CB_SLA_C_In();
     _cb_instructions[0x22] = new   CB_SLA_D_In();
     _cb_instructions[0x23] = new   CB_SLA_E_In();
     _cb_instructions[0x24] = new   CB_SLA_H_In();
     _cb_instructions[0x25] = new   CB_SLA_L_In();
     _cb_instructions[0x26] = new CB_SLA_mHL_In();
     _cb_instructions[0x27] = new   CB_SLA_A_In();
     _cb_instructions[0x28] = new   CB_SRA_B_In();
     _cb_instructions[0x29] = new   CB_SRA_C_In();
     _cb_instructions[0x2A] = new   CB_SRA_D_In();
     _cb_instructions[0x2B] = new   CB_SRA_E_In();
     _cb_instructions[0x2C] = new   CB_SRA_H_In();
     _cb_instructions[0x2D] = new   CB_SRA_L_In();
     _cb_instructions[0x2E] = new CB_SRA_mHL_In();
     _cb_instructions[0x2F] = new   CB_SRA_A_In();
     
     _cb_instructions[0x30] = new   CB_SWAP_B_In();
     _cb_instructions[0x31] = new   CB_SWAP_C_In();
     _cb_instructions[0x32] = new   CB_SWAP_D_In();
     _cb_instructions[0x33] = new   CB_SWAP_E_In();
     _cb_instructions[0x34] = new   CB_SWAP_H_In();
     _cb_instructions[0x35] = new   CB_SWAP_L_In();
     _cb_instructions[0x36] = new CB_SWAP_mHL_In();
     _cb_instructions[0x37] = new   CB_SWAP_A_In();
     _cb_instructions[0x38] = new    CB_SRL_B_In();
     _cb_instructions[0x39] = new    CB_SRL_C_In();
     _cb_instructions[0x3A] = new    CB_SRL_D_In();
     _cb_instructions[0x3B] = new    CB_SRL_E_In();
     _cb_instructions[0x3C] = new    CB_SRL_H_In();
     _cb_instructions[0x3D] = new    CB_SRL_L_In();
     _cb_instructions[0x3E] = new  CB_SRL_mHL_In();
     _cb_instructions[0x3F] = new    CB_SRL_A_In();
     
     _cb_instructions[0x40] = new   BIT_0_B_In();
     _cb_instructions[0x41] = new   BIT_0_C_In();
     _cb_instructions[0x42] = new   BIT_0_D_In();
     _cb_instructions[0x43] = new   BIT_0_E_In();
     _cb_instructions[0x44] = new   BIT_0_H_In();
     _cb_instructions[0x45] = new   BIT_0_L_In();
     _cb_instructions[0x46] = new BIT_0_mHL_In();
     _cb_instructions[0x47] = new   BIT_0_A_In();
     _cb_instructions[0x48] = new   BIT_1_B_In();
     _cb_instructions[0x49] = new   BIT_1_C_In();
     _cb_instructions[0x4A] = new   BIT_1_D_In();
     _cb_instructions[0x4B] = new   BIT_1_E_In();
     _cb_instructions[0x4C] = new   BIT_1_H_In();
     _cb_instructions[0x4D] = new   BIT_1_L_In();
     _cb_instructions[0x4E] = new BIT_1_mHL_In();
     _cb_instructions[0x4F] = new   BIT_1_A_In();
     
     _cb_instructions[0x50] = new   BIT_2_B_In();
     _cb_instructions[0x51] = new   BIT_2_C_In();
     _cb_instructions[0x52] = new   BIT_2_D_In();
     _cb_instructions[0x53] = new   BIT_2_E_In();
     _cb_instructions[0x54] = new   BIT_2_H_In();
     _cb_instructions[0x55] = new   BIT_2_L_In();
     _cb_instructions[0x56] = new BIT_2_mHL_In();
     _cb_instructions[0x57] = new   BIT_2_A_In();
     _cb_instructions[0x58] = new   BIT_3_B_In();
     _cb_instructions[0x59] = new   BIT_3_C_In();
     _cb_instructions[0x5A] = new   BIT_3_D_In();
     _cb_instructions[0x5B] = new   BIT_3_E_In();
     _cb_instructions[0x5C] = new   BIT_3_H_In();
     _cb_instructions[0x5D] = new   BIT_3_L_In();
     _cb_instructions[0x5E] = new BIT_3_mHL_In();
     _cb_instructions[0x5F] = new   BIT_3_A_In();
     
     _cb_instructions[0x60] = new   BIT_4_B_In();
     _cb_instructions[0x61] = new   BIT_4_C_In();
     _cb_instructions[0x62] = new   BIT_4_D_In();
     _cb_instructions[0x63] = new   BIT_4_E_In();
     _cb_instructions[0x64] = new   BIT_4_H_In();
     _cb_instructions[0x65] = new   BIT_4_L_In();
     _cb_instructions[0x66] = new BIT_4_mHL_In();
     _cb_instructions[0x67] = new   BIT_4_A_In();
     _cb_instructions[0x68] = new   BIT_5_B_In();
     _cb_instructions[0x69] = new   BIT_5_C_In();
     _cb_instructions[0x6A] = new   BIT_5_D_In();
     _cb_instructions[0x6B] = new   BIT_5_E_In();
     _cb_instructions[0x6C] = new   BIT_5_H_In();
     _cb_instructions[0x6D] = new   BIT_5_L_In();
     _cb_instructions[0x6E] = new BIT_5_mHL_In();
     _cb_instructions[0x6F] = new   BIT_5_A_In();
     
     _cb_instructions[0x70] = new   BIT_6_B_In();
     _cb_instructions[0x71] = new   BIT_6_C_In();
     _cb_instructions[0x72] = new   BIT_6_D_In();
     _cb_instructions[0x73] = new   BIT_6_E_In();
     _cb_instructions[0x74] = new   BIT_6_H_In();
     _cb_instructions[0x75] = new   BIT_6_L_In();
     _cb_instructions[0x76] = new BIT_6_mHL_In();
     _cb_instructions[0x77] = new   BIT_6_A_In();
     _cb_instructions[0x78] = new   BIT_7_B_In();
     _cb_instructions[0x79] = new   BIT_7_C_In();
     _cb_instructions[0x7A] = new   BIT_7_D_In();
     _cb_instructions[0x7B] = new   BIT_7_E_In();
     _cb_instructions[0x7C] = new   BIT_7_H_In();
     _cb_instructions[0x7D] = new   BIT_7_L_In();
     _cb_instructions[0x7E] = new BIT_7_mHL_In();
     _cb_instructions[0x7F] = new   BIT_7_A_In();
     
     _cb_instructions[0x80] = new   RES_0_B_In();
     _cb_instructions[0x81] = new   RES_0_C_In();
     _cb_instructions[0x82] = new   RES_0_D_In();
     _cb_instructions[0x83] = new   RES_0_E_In();
     _cb_instructions[0x84] = new   RES_0_H_In();
     _cb_instructions[0x85] = new   RES_0_L_In();
     _cb_instructions[0x86] = new RES_0_mHL_In();
     _cb_instructions[0x87] = new   RES_0_A_In();
     _cb_instructions[0x88] = new   RES_1_B_In();
     _cb_instructions[0x89] = new   RES_1_C_In();
     _cb_instructions[0x8A] = new   RES_1_D_In();
     _cb_instructions[0x8B] = new   RES_1_E_In();
     _cb_instructions[0x8C] = new   RES_1_H_In();
     _cb_instructions[0x8D] = new   RES_1_L_In();
     _cb_instructions[0x8E] = new RES_1_mHL_In();
     _cb_instructions[0x8F] = new   RES_1_A_In();
     
     _cb_instructions[0x90] = new   RES_2_B_In(); 
     _cb_instructions[0x91] = new   RES_2_C_In(); 
     _cb_instructions[0x92] = new   RES_2_D_In(); 
     _cb_instructions[0x93] = new   RES_2_E_In(); 
     _cb_instructions[0x94] = new   RES_2_H_In(); 
     _cb_instructions[0x95] = new   RES_2_L_In(); 
     _cb_instructions[0x96] = new RES_2_mHL_In(); 
     _cb_instructions[0x97] = new   RES_2_A_In(); 
     _cb_instructions[0x98] = new   RES_3_B_In(); 
     _cb_instructions[0x99] = new   RES_3_C_In(); 
     _cb_instructions[0x9A] = new   RES_3_D_In(); 
     _cb_instructions[0x9B] = new   RES_3_E_In(); 
     _cb_instructions[0x9C] = new   RES_3_H_In(); 
     _cb_instructions[0x9D] = new   RES_3_L_In(); 
     _cb_instructions[0x9E] = new RES_3_mHL_In(); 
     _cb_instructions[0x9F] = new   RES_3_A_In(); 
     
     _cb_instructions[0xA0] = new   RES_4_B_In();
     _cb_instructions[0xA1] = new   RES_4_C_In();
     _cb_instructions[0xA2] = new   RES_4_D_In();
     _cb_instructions[0xA3] = new   RES_4_E_In();
     _cb_instructions[0xA4] = new   RES_4_H_In();
     _cb_instructions[0xA5] = new   RES_4_L_In();
     _cb_instructions[0xA6] = new RES_4_mHL_In();
     _cb_instructions[0xA7] = new   RES_4_A_In();
     _cb_instructions[0xA8] = new   RES_5_B_In();
     _cb_instructions[0xA9] = new   RES_5_C_In();
     _cb_instructions[0xAA] = new   RES_5_D_In();
     _cb_instructions[0xAB] = new   RES_5_E_In();
     _cb_instructions[0xAC] = new   RES_5_H_In();
     _cb_instructions[0xAD] = new   RES_5_L_In();
     _cb_instructions[0xAE] = new RES_5_mHL_In();
     _cb_instructions[0xAF] = new   RES_5_A_In();
     
     _cb_instructions[0xB0] = new   RES_6_B_In();
     _cb_instructions[0xB1] = new   RES_6_C_In();
     _cb_instructions[0xB2] = new   RES_6_D_In();
     _cb_instructions[0xB3] = new   RES_6_E_In();
     _cb_instructions[0xB4] = new   RES_6_H_In();
     _cb_instructions[0xB5] = new   RES_6_L_In();
     _cb_instructions[0xB6] = new RES_6_mHL_In();
     _cb_instructions[0xB7] = new   RES_6_A_In();
     _cb_instructions[0xB8] = new   RES_7_B_In();
     _cb_instructions[0xB9] = new   RES_7_C_In();
     _cb_instructions[0xBA] = new   RES_7_D_In();
     _cb_instructions[0xBB] = new   RES_7_E_In();
     _cb_instructions[0xBC] = new   RES_7_H_In();
     _cb_instructions[0xBD] = new   RES_7_L_In();
     _cb_instructions[0xBE] = new RES_7_mHL_In();
     _cb_instructions[0xBF] = new   RES_7_A_In();
     
     _cb_instructions[0xC0] = new   SET_0_B_In();
     _cb_instructions[0xC1] = new   SET_0_C_In();
     _cb_instructions[0xC2] = new   SET_0_D_In();
     _cb_instructions[0xC3] = new   SET_0_E_In();
     _cb_instructions[0xC4] = new   SET_0_H_In();
     _cb_instructions[0xC5] = new   SET_0_L_In();
     _cb_instructions[0xC6] = new SET_0_mHL_In();
     _cb_instructions[0xC7] = new   SET_0_A_In();
     _cb_instructions[0xC8] = new   SET_1_B_In();
     _cb_instructions[0xC9] = new   SET_1_C_In();
     _cb_instructions[0xCA] = new   SET_1_D_In();
     _cb_instructions[0xCB] = new   SET_1_E_In();
     _cb_instructions[0xCC] = new   SET_1_H_In();
     _cb_instructions[0xCD] = new   SET_1_L_In();
     _cb_instructions[0xCE] = new SET_1_mHL_In();
     _cb_instructions[0xCF] = new   SET_1_A_In();
     
     _cb_instructions[0xD0] = new   SET_2_B_In();
     _cb_instructions[0xD1] = new   SET_2_C_In();
     _cb_instructions[0xD2] = new   SET_2_D_In();
     _cb_instructions[0xD3] = new   SET_2_E_In();
     _cb_instructions[0xD4] = new   SET_2_H_In();
     _cb_instructions[0xD5] = new   SET_2_L_In();
     _cb_instructions[0xD6] = new SET_2_mHL_In();
     _cb_instructions[0xD7] = new   SET_2_A_In();
     _cb_instructions[0xD8] = new   SET_3_B_In();
     _cb_instructions[0xD9] = new   SET_3_C_In();
     _cb_instructions[0xDA] = new   SET_3_D_In();
     _cb_instructions[0xDB] = new   SET_3_E_In();
     _cb_instructions[0xDC] = new   SET_3_H_In();
     _cb_instructions[0xDD] = new   SET_3_L_In();
     _cb_instructions[0xDE] = new SET_3_mHL_In();
     _cb_instructions[0xDF] = new   SET_3_A_In();
     
     _cb_instructions[0xE0] = new   SET_4_B_In();
     _cb_instructions[0xE1] = new   SET_4_C_In();
     _cb_instructions[0xE2] = new   SET_4_D_In();
     _cb_instructions[0xE3] = new   SET_4_E_In();
     _cb_instructions[0xE4] = new   SET_4_H_In();
     _cb_instructions[0xE5] = new   SET_4_L_In();
     _cb_instructions[0xE6] = new SET_4_mHL_In();
     _cb_instructions[0xE7] = new   SET_4_A_In();
     _cb_instructions[0xE8] = new   SET_5_B_In();
     _cb_instructions[0xE9] = new   SET_5_C_In();
     _cb_instructions[0xEA] = new   SET_5_D_In();
     _cb_instructions[0xEB] = new   SET_5_E_In();
     _cb_instructions[0xEC] = new   SET_5_H_In();
     _cb_instructions[0xED] = new   SET_5_L_In();
     _cb_instructions[0xEE] = new SET_5_mHL_In();
     _cb_instructions[0xEF] = new   SET_5_A_In();
     
     _cb_instructions[0xF0] = new   SET_6_B_In();
     _cb_instructions[0xF1] = new   SET_6_C_In();
     _cb_instructions[0xF2] = new   SET_6_D_In();
     _cb_instructions[0xF3] = new   SET_6_E_In();
     _cb_instructions[0xF4] = new   SET_6_H_In();
     _cb_instructions[0xF5] = new   SET_6_L_In();
     _cb_instructions[0xF6] = new SET_6_mHL_In();
     _cb_instructions[0xF7] = new   SET_6_A_In();
     _cb_instructions[0xF8] = new   SET_7_B_In();
     _cb_instructions[0xF9] = new   SET_7_C_In();
     _cb_instructions[0xFA] = new   SET_7_D_In();
     _cb_instructions[0xFB] = new   SET_7_E_In();
     _cb_instructions[0xFC] = new   SET_7_H_In();
     _cb_instructions[0xFD] = new   SET_7_L_In();
     _cb_instructions[0xFE] = new SET_7_mHL_In();
     _cb_instructions[0xFF] = new   SET_7_A_In();
}           // 0xCB

 PREFIX_CB_In::~PREFIX_CB_In() {
     for(int i=0; i<0x100; ++i) 
         delete _cb_instructions[i]; 
     _cb_instructions.clear(); 
 }
 
 void PREFIX_CB_In::execute(LR35902& cpu, Memory& memory) { 
    op(cpu, memory); 
    // cpu.registers.PC--; 
    cpu.cycle_counter += cycles + addedCycles; 
    addedCycles = 0; 
    // cpu.registers.PC  += bytes + addedBytes; 
    addedBytes  = 0; 
}

// =================================================================================================
// OpCodes 0x00 - 0x0F
// =================================================================================================

NOP_In::NOP_In()                      : Instruction( "NOP",        "NOP", "----", 0x00, 1,  4, VERBOSE_FLAG) { } // 0x00
LD_BC_d16_In::LD_BC_d16_In()          : Instruction(  "LD", "LD BC, d16", "----", 0x01, 3, 12, VERBOSE_FLAG) { } // 0x01
LD_mBC_A_In::LD_mBC_A_In()            : Instruction(  "LD", "LD (BC), A", "----", 0x02, 1,  8, VERBOSE_FLAG) { } // 0x02
INC_BC_In::INC_BC_In()                : Instruction( "INC",     "INC BC", "----", 0x03, 1,  8, VERBOSE_FLAG) { } // 0x03
INC_B_In::INC_B_In()                  : Instruction( "INC",      "INC B", "Z0H-", 0x04, 1,  4, VERBOSE_FLAG) { } // 0x04
DEC_B_In::DEC_B_In()                  : Instruction( "DEC",      "DEC B", "Z1H-", 0x05, 1,  4, VERBOSE_FLAG) { } // 0x05
LD_B_d8_In::LD_B_d8_In()              : Instruction(  "LD",   "LD B, d8", "----", 0x06, 2,  8, VERBOSE_FLAG) { } // 0x06
RLCA_In::RLCA_In()                    : Instruction("RLCA",       "RLCA", "000C", 0x07, 1,  4, VERBOSE_FLAG) { } // 0x07
LD_a16_SP_In::LD_a16_SP_In()          : Instruction(  "LD", "LD a16, SP", "----", 0x08, 3, 20, VERBOSE_FLAG) { } // 0x08
ADD_HL_BC_In::ADD_HL_BC_In()          : Instruction( "ADD", "ADD HL, BC", "-0HC", 0x09, 1,  8, VERBOSE_FLAG) { } // 0x09
LD_A_mBC_In::LD_A_mBC_In()            : Instruction(  "LD", "LD A, (BC)", "----", 0x0A, 1,  8, VERBOSE_FLAG) { } // 0x0A
DEC_BC_In::DEC_BC_In()                : Instruction( "DEC",     "DEC BC", "----", 0x0B, 1,  8, VERBOSE_FLAG) { } // 0x0B
INC_C_In::INC_C_In()                  : Instruction( "INC",      "INC C", "Z0H-", 0x0C, 1,  4, VERBOSE_FLAG) { } // 0x0C
DEC_C_In::DEC_C_In()                  : Instruction( "DEC",      "DEC C", "Z1H-", 0x0D, 1,  4, VERBOSE_FLAG) { } // 0x0D
LD_C_d8_In::LD_C_d8_In()              : Instruction(  "LD",   "LD C, d8", "----", 0x0E, 2,  8, VERBOSE_FLAG) { } // 0x0E
RRCA_In::RRCA_In()                    : Instruction("RRCA",       "RRCA", "000C", 0x0F, 1,  4, VERBOSE_FLAG) { } // 0x0F

// =================================================================================================
// OpCodes 0x10 - 0x1F
// =================================================================================================

STOP_In::STOP_In()                    : Instruction("STOP",     "STOP 0", "----", 0x10, 2,  4, VERBOSE_FLAG) { }  // 0x10
LD_DE_d16_In::LD_DE_d16_In()          : Instruction(  "LD", "LD DE, d16", "----", 0x11, 3, 12, VERBOSE_FLAG) { }  // 0x11
LD_mDE_A_In::LD_mDE_A_In()            : Instruction(  "LD", "LD (DE), A", "----", 0x12, 1,  8, VERBOSE_FLAG) { }  // 0x12
INC_DE_In::INC_DE_In()                : Instruction( "INC",     "INC DE", "----", 0x13, 1,  8, VERBOSE_FLAG) { }  // 0x13
INC_D_In::INC_D_In()                  : Instruction( "INC",      "INC D", "Z0H-", 0x14, 1,  4, VERBOSE_FLAG) { }  // 0x14
DEC_D_In::DEC_D_In()                  : Instruction( "DEC",      "DEC D", "Z1H-", 0x15, 1,  4, VERBOSE_FLAG) { }  // 0x15
LD_D_d8_In::LD_D_d8_In()              : Instruction(  "LD",   "LD D, d8", "----", 0x16, 2,  8, VERBOSE_FLAG) { }  // 0x16
RLA_In::RLA_In()                      : Instruction( "RLA",        "RLA", "000C", 0x17, 1,  4, VERBOSE_FLAG) { }  // 0x17
JR_r8_In::JR_r8_In()                  : Instruction(  "JR",      "JR r8", "----", 0x18, 2, 12, VERBOSE_FLAG) { }  // 0x18
ADD_HL_DE_In::ADD_HL_DE_In()          : Instruction( "ADD", "ADD HL, DE", "-0HC", 0x19, 1,  8, VERBOSE_FLAG) { }  // 0x19
LD_A_mDE_In::LD_A_mDE_In()            : Instruction(  "LD", "LD A, (DE)", "----", 0x1A, 1,  8, VERBOSE_FLAG) { }  // 0x1A
DEC_DE_In::DEC_DE_In()                : Instruction( "DEC",     "DEC DE", "----", 0x1B, 1,  8, VERBOSE_FLAG) { }  // 0x1B
INC_E_In::INC_E_In()                  : Instruction( "INC",      "INC E", "Z0H-", 0x1C, 1,  4, VERBOSE_FLAG) { }  // 0x1C
DEC_E_In::DEC_E_In()                  : Instruction( "DEC",      "DEC E", "Z1H-", 0x1D, 1,  4, VERBOSE_FLAG) { }  // 0x1D
LD_E_d8_In::LD_E_d8_In()              : Instruction(  "LD",   "LD E, d8", "----", 0x1E, 2,  8, VERBOSE_FLAG) { }  // 0x1E
RRA_In::RRA_In()                      : Instruction( "RRA",        "RRA", "000C", 0x1F, 1,  4, VERBOSE_FLAG) { }  // 0x1F

// =================================================================================================
// OpCodes 0x20 - 0x2F
// =================================================================================================

JR_NZ_r8_In::JR_NZ_r8_In()            : Instruction( "JR",   "JR NZ, r8", "----", 0x20, 2,  8 /* 12 */, VERBOSE_FLAG) { } // 0x20
LD_HL_d16_In::LD_HL_d16_In()          : Instruction( "LD",  "LD HL, d16", "----", 0x21, 3, 12, VERBOSE_FLAG) { }  // 0x21
LD_mHLp_A_In::LD_mHLp_A_In()          : Instruction( "LD", "LD (HL+), A", "----", 0x22, 1,  8, VERBOSE_FLAG) { }  // 0x22
INC_HL_In::INC_HL_In()                : Instruction( "INC",     "INC HL", "----", 0x23, 1,  8, VERBOSE_FLAG) { }  // 0x23
INC_H_In::INC_H_In()                  : Instruction( "INC",      "INC H", "Z0H-", 0x24, 1,  4, VERBOSE_FLAG) { }  // 0x24
DEC_H_In::DEC_H_In()                  : Instruction( "DEC",      "DEC H", "Z1H-", 0x25, 1,  4, VERBOSE_FLAG) { }  // 0x25
LD_H_d8_In::LD_H_d8_In()              : Instruction( "LD",    "LD H, d8", "----", 0x26, 2,  8, VERBOSE_FLAG) { }  // 0x26
DAA_In::DAA_In()                      : Instruction( "DAA",        "DAA", "Z-0C", 0x27, 1,  4, VERBOSE_FLAG) { }  // 0x27
JR_Z_r8_In::JR_Z_r8_In()              : Instruction(  "JR",         "JR", "----", 0x28, 2,  8 /* 12 */, VERBOSE_FLAG) { } // 0x28
ADD_HL_HL_In::ADD_HL_HL_In()          : Instruction( "ADD", "ADD HL, HL", "-0HC", 0x29, 1,  8, VERBOSE_FLAG) { } // 0x29
LD_A_mHLp_In::LD_A_mHLp_In()          : Instruction(  "LD","LD A, (HL+)", "----", 0x2A, 1,  8, VERBOSE_FLAG) { } // 0x2A
DEC_HL_In::DEC_HL_In()                : Instruction( "DEC",     "DEC HL", "----", 0x2B, 1,  8, VERBOSE_FLAG) { } // 0x2B
INC_L_In::INC_L_In()                  : Instruction( "INC",      "INC L", "Z0H-", 0x2C, 1,  4, VERBOSE_FLAG) { } // 0x2C
DEC_L_In::DEC_L_In()                  : Instruction( "DEC",      "DEC L", "Z1H-", 0x2D, 1,  4, VERBOSE_FLAG) { } // 0x2D
LD_L_d8_In::LD_L_d8_In()              : Instruction(  "LD",   "LD L, d8", "----", 0x2E, 2,  8, VERBOSE_FLAG) { } // 0x2E
CPL_In::CPL_In()                      : Instruction( "CPL",        "CPL", "-11-", 0x2F, 1,  4, VERBOSE_FLAG) { } // 0x2F

// =================================================================================================
// OpCodes 0x30 - 0x3F
// =================================================================================================

JR_NC_r8_In::JR_NC_r8_In()            : Instruction(  "JR",  "JR NC, r8", "----", 0x30, 2,  8 /* 12 */, VERBOSE_FLAG) { } // 0x30
LD_SP_d16_In::LD_SP_d16_In()          : Instruction(  "LD", "LD SP, d16", "----", 0x31, 3, 12, VERBOSE_FLAG) { }  // 0x31
LD_mHLm_A_In::LD_mHLm_A_In()          : Instruction(  "LD","LD (HL-), A", "----", 0x32, 1,  8, VERBOSE_FLAG) { }  // 0x32
INC_SP_In::INC_SP_In()                : Instruction( "INC",     "INC SP", "----", 0x33, 1,  8, VERBOSE_FLAG) { }  // 0x33
INC_mHL_In::INC_mHL_In()              : Instruction( "INC",   "INC (HL)", "Z0H-", 0x34, 1, 12, VERBOSE_FLAG) { }  // 0x34
DEC_mHL_In::DEC_mHL_In()              : Instruction( "DEC",   "DEC (HL)", "Z1H-", 0x35, 1, 12, VERBOSE_FLAG) { }  // 0x35
LD_mHL_d8_In::LD_mHL_d8_In()          : Instruction(  "LD","LD (HL), d8", "----", 0x36, 2, 12, VERBOSE_FLAG) { }  // 0x36
SCF_In::SCF_In()                      : Instruction( "SCF",        "SCF", "-001", 0x37, 1,  4, VERBOSE_FLAG) { }  // 0x37
JR_C_r8_In::JR_C_r8_In()              : Instruction(  "JR",         "JR", "----", 0x38, 2,  8 /* 12 */, VERBOSE_FLAG) { } // 0x38
ADD_HL_SP_In::ADD_HL_SP_In()          : Instruction( "ADD", "ADD HL, SP", "-0HC", 0x39, 1,  8, VERBOSE_FLAG) { }  // 0x39
LD_A_mHLm_In::LD_A_mHLm_In()          : Instruction(  "LD","LD A, (HL-)", "----", 0x3A, 1,  8, VERBOSE_FLAG) { } // 0x3A
DEC_SP_In::DEC_SP_In()                : Instruction( "DEC",     "DEC SP", "----", 0x3B, 1,  8, VERBOSE_FLAG) { } // 0x3B
INC_A_In::INC_A_In()                  : Instruction( "INC",      "INC A", "Z0H-", 0x3C, 1,  4, VERBOSE_FLAG) { } // 0x3C
DEC_A_In::DEC_A_In()                  : Instruction( "DEC",      "DEC A", "Z1H-", 0x3D, 1,  4, VERBOSE_FLAG) { } // 0x3D
LD_A_d8_In::LD_A_d8_In()              : Instruction(  "LD",   "LD A, d8", "----", 0x3E, 2,  8, VERBOSE_FLAG) { } // 0x3E
CCF_In::CCF_In()                      : Instruction( "CCF",        "CCF", "-00C", 0x3F, 1,  4, VERBOSE_FLAG) { } // 0x3F

// =================================================================================================
// OpCodes 0x40 - 0x4F
// =================================================================================================

LD_B_B_In::LD_B_B_In()            : Instruction( "LD",   "LD B, B", "----", 0x40, 1, 4, VERBOSE_FLAG) { }        // 0x40
LD_B_C_In::LD_B_C_In()            : Instruction( "LD",   "LD B, C", "----", 0x41, 1, 4, VERBOSE_FLAG) { }        // 0x41
LD_B_D_In::LD_B_D_In()            : Instruction( "LD",   "LD B, D", "----", 0x42, 1, 4, VERBOSE_FLAG) { }        // 0x42
LD_B_E_In::LD_B_E_In()            : Instruction( "LD",   "LD B, E", "----", 0x43, 1, 4, VERBOSE_FLAG) { }        // 0x43
LD_B_H_In::LD_B_H_In()            : Instruction( "LD",   "LD B, H", "----", 0x44, 1, 4, VERBOSE_FLAG) { }        // 0x44
LD_B_L_In::LD_B_L_In()            : Instruction( "LD",   "LD B, L", "----", 0x45, 1, 4, VERBOSE_FLAG) { }        // 0x45
LD_B_mHL_In::LD_B_mHL_In()        : Instruction( "LD","LD B, (HL)", "----", 0x46, 1, 8, VERBOSE_FLAG) { }        // 0x46
LD_B_A_In::LD_B_A_In()            : Instruction( "LD",   "LD B, A", "----", 0x47, 1, 4, VERBOSE_FLAG) { }        // 0x47
LD_C_B_In::LD_C_B_In()            : Instruction( "LD",   "LD C, B", "----", 0x48, 1, 4, VERBOSE_FLAG) { }        // 0x48
LD_C_C_In::LD_C_C_In()            : Instruction( "LD",   "LD C, C", "----", 0x49, 1, 4, VERBOSE_FLAG) { }        // 0x49
LD_C_D_In::LD_C_D_In()            : Instruction( "LD",   "LD C, D", "----", 0x4A, 1, 4, VERBOSE_FLAG) { }        // 0x4A
LD_C_E_In::LD_C_E_In()            : Instruction( "LD",   "LD C, E", "----", 0x4B, 1, 4, VERBOSE_FLAG) { }        // 0x4B
LD_C_H_In::LD_C_H_In()            : Instruction( "LD",   "LD C, H", "----", 0x4C, 1, 4, VERBOSE_FLAG) { }        // 0x4C
LD_C_L_In::LD_C_L_In()            : Instruction( "LD",   "LD C, L", "----", 0x4D, 1, 4, VERBOSE_FLAG) { }        // 0x4D
LD_C_mHL_In::LD_C_mHL_In()        : Instruction( "LD","LD C, (HL)", "----", 0x4E, 1, 8, VERBOSE_FLAG) { }        // 0x4E
LD_C_A_In::LD_C_A_In()            : Instruction( "LD",   "LD C, A", "----", 0x4F, 1, 4, VERBOSE_FLAG) { }        // 0x4F

// =================================================================================================
// OpCodes 0x50 - 0x5F
// =================================================================================================

LD_D_B_In::LD_D_B_In()            : Instruction( "LD",   "LD D, B", "----", 0x50, 1, 4, VERBOSE_FLAG) { }        // 0x50
LD_D_C_In::LD_D_C_In()            : Instruction( "LD",   "LD D, C", "----", 0x51, 1, 4, VERBOSE_FLAG) { }        // 0x51
LD_D_D_In::LD_D_D_In()            : Instruction( "LD",   "LD D, D", "----", 0x52, 1, 4, VERBOSE_FLAG) { }        // 0x52
LD_D_E_In::LD_D_E_In()            : Instruction( "LD",   "LD D, E", "----", 0x53, 1, 4, VERBOSE_FLAG) { }        // 0x53
LD_D_H_In::LD_D_H_In()            : Instruction( "LD",   "LD D, H", "----", 0x54, 1, 4, VERBOSE_FLAG) { }        // 0x54
LD_D_L_In::LD_D_L_In()            : Instruction( "LD",   "LD D, L", "----", 0x55, 1, 4, VERBOSE_FLAG) { }        // 0x55
LD_D_mHL_In::LD_D_mHL_In()        : Instruction( "LD","LD D, (HL)", "----", 0x56, 1, 8, VERBOSE_FLAG) { }        // 0x56
LD_D_A_In::LD_D_A_In()            : Instruction( "LD",   "LD D, A", "----", 0x57, 1, 4, VERBOSE_FLAG) { }        // 0x57
LD_E_B_In::LD_E_B_In()            : Instruction( "LD",   "LD E, B", "----", 0x58, 1, 4, VERBOSE_FLAG) { }        // 0x58
LD_E_C_In::LD_E_C_In()            : Instruction( "LD",   "LD E, C", "----", 0x59, 1, 4, VERBOSE_FLAG) { }        // 0x59
LD_E_D_In::LD_E_D_In()            : Instruction( "LD",   "LD E, D", "----", 0x5A, 1, 4, VERBOSE_FLAG) { }        // 0x5A
LD_E_E_In::LD_E_E_In()            : Instruction( "LD",   "LD E, E", "----", 0x5B, 1, 4, VERBOSE_FLAG) { }        // 0x5B
LD_E_H_In::LD_E_H_In()            : Instruction( "LD",   "LD E, H", "----", 0x5C, 1, 4, VERBOSE_FLAG) { }        // 0x5C
LD_E_L_In::LD_E_L_In()            : Instruction( "LD",   "LD E, L", "----", 0x5D, 1, 4, VERBOSE_FLAG) { }        // 0x5D
LD_E_mHL_In::LD_E_mHL_In()        : Instruction( "LD","LD E, (HL)", "----", 0x5E, 1, 8, VERBOSE_FLAG) { }        // 0x5E
LD_E_A_In::LD_E_A_In()            : Instruction( "LD",   "LD E, A", "----", 0x5F, 1, 4, VERBOSE_FLAG) { }        // 0x5F

// =================================================================================================
// OpCodes 0x60 - 0x6F
// =================================================================================================

LD_H_B_In::LD_H_B_In()            : Instruction( "LD",   "LD H, B", "----", 0x60, 1, 4, VERBOSE_FLAG) { }        // 0x60
LD_H_C_In::LD_H_C_In()            : Instruction( "LD",   "LD H, C", "----", 0x61, 1, 4, VERBOSE_FLAG) { }        // 0x61
LD_H_D_In::LD_H_D_In()            : Instruction( "LD",   "LD H, D", "----", 0x62, 1, 4, VERBOSE_FLAG) { }        // 0x62
LD_H_E_In::LD_H_E_In()            : Instruction( "LD",   "LD H, E", "----", 0x63, 1, 4, VERBOSE_FLAG) { }        // 0x63
LD_H_H_In::LD_H_H_In()            : Instruction( "LD",   "LD H, H", "----", 0x64, 1, 4, VERBOSE_FLAG) { }        // 0x64
LD_H_L_In::LD_H_L_In()            : Instruction( "LD",   "LD H, L", "----", 0x65, 1, 4, VERBOSE_FLAG) { }        // 0x65
LD_H_mHL_In::LD_H_mHL_In()        : Instruction( "LD","LD H, (HL)", "----", 0x66, 1, 8, VERBOSE_FLAG) { }        // 0x66
LD_H_A_In::LD_H_A_In()            : Instruction( "LD",   "LD H, A", "----", 0x67, 1, 4, VERBOSE_FLAG) { }        // 0x67
LD_L_B_In::LD_L_B_In()            : Instruction( "LD",   "LD L, B", "----", 0x68, 1, 4, VERBOSE_FLAG) { }        // 0x68
LD_L_C_In::LD_L_C_In()            : Instruction( "LD",   "LD L, C", "----", 0x69, 1, 4, VERBOSE_FLAG) { }        // 0x69
LD_L_D_In::LD_L_D_In()            : Instruction( "LD",   "LD L, D", "----", 0x6A, 1, 4, VERBOSE_FLAG) { }        // 0x6A
LD_L_E_In::LD_L_E_In()            : Instruction( "LD",   "LD L, E", "----", 0x6B, 1, 4, VERBOSE_FLAG) { }        // 0x6B
LD_L_H_In::LD_L_H_In()            : Instruction( "LD",   "LD L, H", "----", 0x6C, 1, 4, VERBOSE_FLAG) { }        // 0x6C
LD_L_L_In::LD_L_L_In()            : Instruction( "LD",   "LD L, L", "----", 0x6D, 1, 4, VERBOSE_FLAG) { }        // 0x6D
LD_L_mHL_In::LD_L_mHL_In()        : Instruction( "LD","LD L, (HL)", "----", 0x6E, 1, 8, VERBOSE_FLAG) { }        // 0x6E
LD_L_A_In::LD_L_A_In()            : Instruction( "LD",   "LD L, A", "----", 0x6F, 1, 4, VERBOSE_FLAG) { }        // 0x6F

// =================================================================================================
// OpCodes 0x70 - 0x7F
// =================================================================================================

LD_mHL_B_In::LD_mHL_B_In()        : Instruction( "LD",  "LD (HL), B", "----", 0x70, 1, 8, VERBOSE_FLAG) { }      // 0x70
LD_mHL_C_In::LD_mHL_C_In()        : Instruction( "LD",  "LD (HL), C", "----", 0x71, 1, 8, VERBOSE_FLAG) { }      // 0x71
LD_mHL_D_In::LD_mHL_D_In()        : Instruction( "LD",  "LD (HL), D", "----", 0x72, 1, 8, VERBOSE_FLAG) { }      // 0x72
LD_mHL_E_In::LD_mHL_E_In()        : Instruction( "LD",  "LD (HL), E", "----", 0x73, 1, 8, VERBOSE_FLAG) { }      // 0x73
LD_mHL_H_In::LD_mHL_H_In()        : Instruction( "LD",  "LD (HL), H", "----", 0x74, 1, 8, VERBOSE_FLAG) { }      // 0x74
LD_mHL_L_In::LD_mHL_L_In()        : Instruction( "LD",  "LD (HL), L", "----", 0x75, 1, 8, VERBOSE_FLAG) { }      // 0x75
HALT_In::HALT_In()                : Instruction( "LD",        "HALT", "----", 0x76, 1, 4, VERBOSE_FLAG) { }      // 0x76
LD_mHL_A_In::LD_mHL_A_In()        : Instruction( "LD",  "LD (HL), A", "----", 0x77, 1, 8, VERBOSE_FLAG) { }      // 0x77
LD_A_B_In::LD_A_B_In()            : Instruction( "LD",     "LD A, B", "----", 0x78, 1, 4, VERBOSE_FLAG) { }      // 0x78
LD_A_C_In::LD_A_C_In()            : Instruction( "LD",     "LD A, C", "----", 0x79, 1, 4, VERBOSE_FLAG) { }      // 0x79
LD_A_D_In::LD_A_D_In()            : Instruction( "LD",     "LD A, D", "----", 0x7A, 1, 4, VERBOSE_FLAG) { }      // 0x7A
LD_A_E_In::LD_A_E_In()            : Instruction( "LD",     "LD A, E", "----", 0x7B, 1, 4, VERBOSE_FLAG) { }      // 0x7B
LD_A_H_In::LD_A_H_In()            : Instruction( "LD",     "LD A, H", "----", 0x7C, 1, 4, VERBOSE_FLAG) { }      // 0x7C
LD_A_L_In::LD_A_L_In()            : Instruction( "LD",     "LD A, L", "----", 0x7D, 1, 4, VERBOSE_FLAG) { }      // 0x7D
LD_A_mHL_In::LD_A_mHL_In()        : Instruction( "LD",  "LD A, (HL)", "----", 0x7E, 1, 8, VERBOSE_FLAG) { }      // 0x7E
LD_A_A_In::LD_A_A_In()            : Instruction( "LD",     "LD A, A", "----", 0x7F, 1, 4, VERBOSE_FLAG) { }      // 0x7F

// =================================================================================================
// OpCodes 0x80 - 0x8F
// =================================================================================================

  ADD_A_B_In::ADD_A_B_In()            : Instruction( "ADD",   "ADD A, B", "Z0HC", 0x80, 1, 4, VERBOSE_FLAG) { }     // 0x80
  ADD_A_C_In::ADD_A_C_In()            : Instruction( "ADD",   "ADD A, C", "Z0HC", 0x81, 1, 4, VERBOSE_FLAG) { }     // 0x81
  ADD_A_D_In::ADD_A_D_In()            : Instruction( "ADD",   "ADD A, D", "Z0HC", 0x82, 1, 4, VERBOSE_FLAG) { }     // 0x82
  ADD_A_E_In::ADD_A_E_In()            : Instruction( "ADD",   "ADD A, E", "Z0HC", 0x83, 1, 4, VERBOSE_FLAG) { }     // 0x83
  ADD_A_H_In::ADD_A_H_In()            : Instruction( "ADD",   "ADD A, H", "Z0HC", 0x84, 1, 4, VERBOSE_FLAG) { }     // 0x84
  ADD_A_L_In::ADD_A_L_In()            : Instruction( "ADD",   "ADD A, L", "Z0HC", 0x85, 1, 4, VERBOSE_FLAG) { }     // 0x85
ADD_A_mHL_In::ADD_A_mHL_In()          : Instruction( "ADD","ADD A, (HL)", "Z0HC", 0x86, 1, 8, VERBOSE_FLAG) { }     // 0x86
  ADD_A_A_In::ADD_A_A_In()            : Instruction( "ADD",   "ADD A, A", "Z0HC", 0x87, 1, 4, VERBOSE_FLAG) { }     // 0x87
  ADC_A_B_In::ADC_A_B_In()            : Instruction( "ADC",   "ADC A, B", "Z0HC", 0x88, 1, 4, VERBOSE_FLAG) { }     // 0x88
  ADC_A_C_In::ADC_A_C_In()            : Instruction( "ADC",   "ADC A, C", "Z0HC", 0x89, 1, 4, VERBOSE_FLAG) { }     // 0x89
  ADC_A_D_In::ADC_A_D_In()            : Instruction( "ADC",   "ADC A, D", "Z0HC", 0x8A, 1, 4, VERBOSE_FLAG) { }     // 0x8A
  ADC_A_E_In::ADC_A_E_In()            : Instruction( "ADC",   "ADC A, E", "Z0HC", 0x8B, 1, 4, VERBOSE_FLAG) { }     // 0x8B
  ADC_A_H_In::ADC_A_H_In()            : Instruction( "ADC",   "ADC A, H", "Z0HC", 0x8C, 1, 4, VERBOSE_FLAG) { }     // 0x8C
  ADC_A_L_In::ADC_A_L_In()            : Instruction( "ADC",   "ADC A, L", "Z0HC", 0x8D, 1, 4, VERBOSE_FLAG) { }     // 0x8D
ADC_A_mHL_In::ADC_A_mHL_In()          : Instruction( "ADC","ADC A, (HL)", "Z0HC", 0x8E, 1, 8, VERBOSE_FLAG) { }     // 0x8E
  ADC_A_A_In::ADC_A_A_In()            : Instruction( "ADC",   "ADC A, A", "Z0HC", 0x8F, 1, 4, VERBOSE_FLAG) { }     // 0x8F
  
// =================================================================================================
// OpCodes 0x90 - 0x9F
// =================================================================================================

   SUB_B_In::SUB_B_In()    : Instruction( "SUB",   "SUB B", "Z1HC", 0x90, 1, 4, VERBOSE_FLAG) { }     // 0x90
   SUB_C_In::SUB_C_In()    : Instruction( "SUB",   "SUB C", "Z1HC", 0x91, 1, 4, VERBOSE_FLAG) { }     // 0x91
   SUB_D_In::SUB_D_In()    : Instruction( "SUB",   "SUB D", "Z1HC", 0x92, 1, 4, VERBOSE_FLAG) { }     // 0x92
   SUB_E_In::SUB_E_In()    : Instruction( "SUB",   "SUB E", "Z1HC", 0x93, 1, 4, VERBOSE_FLAG) { }     // 0x93
   SUB_H_In::SUB_H_In()    : Instruction( "SUB",   "SUB H", "Z1HC", 0x94, 1, 4, VERBOSE_FLAG) { }     // 0x94
   SUB_L_In::SUB_L_In()    : Instruction( "SUB",   "SUB L", "Z1HC", 0x95, 1, 4, VERBOSE_FLAG) { }     // 0x95
 SUB_mHL_In::SUB_mHL_In()  : Instruction( "SUB","SUB (HL)", "Z1HC", 0x96, 1, 8, VERBOSE_FLAG) { }     // 0x96
   SUB_A_In::SUB_A_In()    : Instruction( "SUB","SUB A, A", "Z1HC", 0x97, 1, 4, VERBOSE_FLAG) { }     // 0x97
   SBC_B_In::SBC_B_In()    : Instruction( "SBC",   "SBC B", "Z1HC", 0x98, 1, 4, VERBOSE_FLAG) { }     // 0x98
   SBC_C_In::SBC_C_In()    : Instruction( "SBC",   "SBC C", "Z1HC", 0x99, 1, 4, VERBOSE_FLAG) { }     // 0x99
   SBC_D_In::SBC_D_In()    : Instruction( "SBC",   "SBC D", "Z1HC", 0x9A, 1, 4, VERBOSE_FLAG) { }     // 0x9A
   SBC_E_In::SBC_E_In()    : Instruction( "SBC",   "SBC E", "Z1HC", 0x9B, 1, 4, VERBOSE_FLAG) { }     // 0x9B
   SBC_H_In::SBC_H_In()    : Instruction( "SBC",   "SBC H", "Z1HC", 0x9C, 1, 4, VERBOSE_FLAG) { }     // 0x9C
   SBC_L_In::SBC_L_In()    : Instruction( "SBC",   "SBC L", "Z1HC", 0x9D, 1, 4, VERBOSE_FLAG) { }     // 0x9D
 SBC_mHL_In::SBC_mHL_In()  : Instruction( "SBC","SBC (HL)", "Z1HC", 0x9E, 1, 8, VERBOSE_FLAG) { }     // 0x9E
   SBC_A_In::SBC_A_In()    : Instruction( "SBC",   "SBC A", "Z1HC", 0x9F, 1, 4, VERBOSE_FLAG) { }     // 0x9F

// =================================================================================================
// OpCodes 0xA0 - 0xAF
// =================================================================================================

   AND_B_In::AND_B_In()    : Instruction( "AND",   "AND B", "Z010", 0xA0, 1, 4, VERBOSE_FLAG) { }     // 0xA0
   AND_C_In::AND_C_In()    : Instruction( "AND",   "AND C", "Z010", 0xA1, 1, 4, VERBOSE_FLAG) { }     // 0xA1
   AND_D_In::AND_D_In()    : Instruction( "AND",   "AND D", "Z010", 0xA2, 1, 4, VERBOSE_FLAG) { }     // 0xA2
   AND_E_In::AND_E_In()    : Instruction( "AND",   "AND E", "Z010", 0xA3, 1, 4, VERBOSE_FLAG) { }     // 0xA3
   AND_H_In::AND_H_In()    : Instruction( "AND",   "AND H", "Z010", 0xA4, 1, 4, VERBOSE_FLAG) { }     // 0xA4
   AND_L_In::AND_L_In()    : Instruction( "AND",   "AND L", "Z010", 0xA5, 1, 4, VERBOSE_FLAG) { }     // 0xA5
 AND_mHL_In::AND_mHL_In()  : Instruction( "AND","AND (HL)", "Z010", 0xA6, 1, 8, VERBOSE_FLAG) { }     // 0xA6
   AND_A_In::AND_A_In()    : Instruction( "AND",   "AND A", "Z010", 0xA7, 1, 4, VERBOSE_FLAG) { }     // 0xA7
   XOR_B_In::XOR_B_In()    : Instruction( "XOR",   "XOR B", "Z000", 0xA8, 1, 4, VERBOSE_FLAG) { }     // 0xA8
   XOR_C_In::XOR_C_In()    : Instruction( "XOR",   "XOR C", "Z000", 0xA9, 1, 4, VERBOSE_FLAG) { }     // 0xA9
   XOR_D_In::XOR_D_In()    : Instruction( "XOR",   "XOR D", "Z000", 0xAA, 1, 4, VERBOSE_FLAG) { }     // 0xAA
   XOR_E_In::XOR_E_In()    : Instruction( "XOR",   "XOR E", "Z000", 0xAB, 1, 4, VERBOSE_FLAG) { }     // 0xAB
   XOR_H_In::XOR_H_In()    : Instruction( "XOR",   "XOR H", "Z000", 0xAC, 1, 4, VERBOSE_FLAG) { }     // 0xAC
   XOR_L_In::XOR_L_In()    : Instruction( "XOR",   "XOR L", "Z000", 0xAD, 1, 4, VERBOSE_FLAG) { }     // 0xAD
 XOR_mHL_In::XOR_mHL_In()  : Instruction( "XOR","XOR (HL)", "Z000", 0xAE, 1, 8, VERBOSE_FLAG) { }     // 0xAE
   XOR_A_In::XOR_A_In()    : Instruction( "XOR",   "XOR A", "Z000", 0xAF, 1, 4, VERBOSE_FLAG) { }     // 0xAF
   
// =================================================================================================
// OpCodes 0xB0 - 0xBF
// =================================================================================================

   OR_B_In::OR_B_In()    : Instruction( "OR",    "OR B", "Z000", 0xB0, 1, 4, VERBOSE_FLAG) { }     // 0xB0
   OR_C_In::OR_C_In()    : Instruction( "OR",    "OR C", "Z000", 0xB1, 1, 4, VERBOSE_FLAG) { }     // 0xB1
   OR_D_In::OR_D_In()    : Instruction( "OR",    "OR D", "Z000", 0xB2, 1, 4, VERBOSE_FLAG) { }     // 0xB2
   OR_E_In::OR_E_In()    : Instruction( "OR",    "OR E", "Z000", 0xB3, 1, 4, VERBOSE_FLAG) { }     // 0xB3
   OR_H_In::OR_H_In()    : Instruction( "OR",    "OR H", "Z000", 0xB4, 1, 4, VERBOSE_FLAG) { }     // 0xB4
   OR_L_In::OR_L_In()    : Instruction( "OR",    "OR L", "Z000", 0xB5, 1, 4, VERBOSE_FLAG) { }     // 0xB5
 OR_mHL_In::OR_mHL_In()  : Instruction( "OR", "OR (HL)", "Z000", 0xB6, 1, 8, VERBOSE_FLAG) { }     // 0xB6
   OR_A_In::OR_A_In()    : Instruction( "OR",   "OR  A", "Z000", 0xB7, 1, 4, VERBOSE_FLAG) { }     // 0xB7
   CP_B_In::CP_B_In()    : Instruction( "CP",    "CP B", "Z1HC", 0xB8, 1, 4, VERBOSE_FLAG) { }     // 0xB8
   CP_C_In::CP_C_In()    : Instruction( "CP",    "CP C", "Z1HC", 0xB9, 1, 4, VERBOSE_FLAG) { }     // 0xB9
   CP_D_In::CP_D_In()    : Instruction( "CP",    "CP D", "Z1HC", 0xBA, 1, 4, VERBOSE_FLAG) { }     // 0xBA
   CP_E_In::CP_E_In()    : Instruction( "CP",    "CP E", "Z1HC", 0xBB, 1, 4, VERBOSE_FLAG) { }     // 0xBB
   CP_H_In::CP_H_In()    : Instruction( "CP",    "CP H", "Z1HC", 0xBC, 1, 4, VERBOSE_FLAG) { }     // 0xBC
   CP_L_In::CP_L_In()    : Instruction( "CP",    "CP L", "Z1HC", 0xBD, 1, 4, VERBOSE_FLAG) { }     // 0xBD
 CP_mHL_In::CP_mHL_In()  : Instruction( "CP", "CP (HL)", "Z1HC", 0xBE, 1, 8, VERBOSE_FLAG) { }     // 0xBE
   CP_A_In::CP_A_In()    : Instruction( "CP",    "CP A", "Z1HC", 0xBF, 1, 4, VERBOSE_FLAG) { }     // 0xBF
   
// =================================================================================================
// OpCodes 0xC0 - 0xCF
// =================================================================================================

      RET_NZ_In::RET_NZ_In()      : Instruction( "RET",      "RET NZ", "----", 0xC0, 1,  8 /* 20 */, VERBOSE_FLAG) { }  // 0xC0
      POP_BC_In::POP_BC_In()      : Instruction( "POP",      "POP BC", "----", 0xC1, 1, 12, VERBOSE_FLAG) { }           // 0xC1
   JP_NZ_a16_In::JP_NZ_a16_In()   : Instruction(  "JP",  "JP NZ, a16", "----", 0xC2, 3, 12 /* 16 */, VERBOSE_FLAG) { }  // 0xC2
      JP_a16_In::JP_a16_In()      : Instruction(  "JP",      "JP a16", "----", 0xC3, 3, 16, VERBOSE_FLAG) { }           // 0xC3
 CALL_NZ_a16_In::CALL_NZ_a16_In() : Instruction("CALL","CALL NZ, a16", "----", 0xC4, 3, 12 /* 24 */, VERBOSE_FLAG) { }  // 0xC4
     PUSH_BC_In::PUSH_BC_In()     : Instruction("PUSH",     "PUSH BC", "----", 0xC5, 1, 16, VERBOSE_FLAG) { }           // 0xC5
    ADD_A_d8_In::ADD_A_d8_In()    : Instruction("ADD",    "ADD A, d8", "Z0HC", 0xC6, 2,  8, VERBOSE_FLAG) { }           // 0xC6
     RST_00H_In::RST_00H_In()     : Instruction("RST",      "RST 00H", "----", 0xC7, 1, 16, VERBOSE_FLAG) { }           // 0xC7
       RET_Z_In::RET_Z_In()       : Instruction("RET",        "RET Z", "----", 0xC8, 1, 8 /* 20 */, VERBOSE_FLAG) { }   // 0xC8
         RET_In::RET_In()         : Instruction("RET",          "RET", "----", 0xC9, 1, 16, VERBOSE_FLAG) { }           // 0xC9
    JP_Z_a16_In::JP_Z_a16_In()    : Instruction(  "JP",   "JP Z, a16", "----", 0xCA, 3, 12 /* 16 */, VERBOSE_FLAG) { }  // 0xCA

  CALL_Z_a16_In::CALL_Z_a16_In()  : Instruction("CALL", "CALL Z, a16", "----", 0xCC, 3, 12 /* 24 */, VERBOSE_FLAG) { }  // 0xCC
    CALL_a16_In::CALL_a16_In()    : Instruction("CALL",    "CALL a16", "----", 0xCD, 3, 24, VERBOSE_FLAG) { }           // 0xCD
    ADC_A_d8_In::ADC_A_d8_In()    : Instruction( "ADC",   "ADC A, d8", "Z0HC", 0xCE, 2,  8, VERBOSE_FLAG) { }           // 0xCE
     RST_08H_In::RST_08H_In()     : Instruction("RST",      "RST 08H", "----", 0xCF, 1, 16, VERBOSE_FLAG) { }           // 0xCF
     
// =================================================================================================
// OpCodes 0xD0 - 0xDF
// =================================================================================================

     RET_NC_In::RET_NC_In()      : Instruction( "RET",      "RET NC", "----", 0xD0, 1, 8 /* 20 */, VERBOSE_FLAG) { }    // 0xD0
     POP_DE_In::POP_DE_In()      : Instruction( "POP",      "POP DE", "----", 0xD1, 1, 12, VERBOSE_FLAG) { }            // 0xD1
  JP_NC_a16_In::JP_NC_a16_In()   : Instruction(  "JP",  "JP NC, a16", "----", 0xD2, 3, 12 /* 16 */, VERBOSE_FLAG) { }   // 0xD2
// 0xD3: no operation for this opcode in LR35902
CALL_NC_a16_In::CALL_NC_a16_In() : Instruction("CALL","CALL NC, a16", "----", 0xD4, 3, 12 /* 24 */, VERBOSE_FLAG) { }   // 0xD4
    PUSH_DE_In::PUSH_DE_In()     : Instruction("PUSH",     "PUSH DE", "----", 0xD5, 1, 16, VERBOSE_FLAG) { }            // 0xD5
     SUB_d8_In::SUB_d8_In()      : Instruction( "SUB",   "SUB A, d8", "Z1HC", 0xD6, 2,  8, VERBOSE_FLAG) { }            // 0xD6
    RST_10H_In::RST_10H_In()     : Instruction( "RST",     "RST 10H", "----", 0xD7, 1, 16, VERBOSE_FLAG) { }            // 0xD7
      RET_C_In::RET_C_In()       : Instruction( "RET",       "RET C", "----", 0xD8, 1, 8 /* 12 */, VERBOSE_FLAG) { }    // 0xD8
       RETI_In::RETI_In()        : Instruction("RETI",        "RETI", "----", 0xD9, 1, 16, VERBOSE_FLAG) { }            // 0xD9
   JP_C_a16_In::JP_C_a16_In()    : Instruction(  "JP",   "JP C, a16", "----", 0xDA, 3, 12 /* 16 */, VERBOSE_FLAG) { }   // 0xDA
// 0xDB: no operation for this opcode in LR35902
 CALL_C_a16_In::CALL_C_a16_In()  : Instruction("CALL", "CALL C, a16", "----", 0xDC, 3, 12 /* 24 */, VERBOSE_FLAG) { }   // 0xDC
// 0xDD: no operation for this opcode in LR35902
   SBC_A_d8_In::SBC_A_d8_In()    : Instruction( "SBC",   "SBC A, d8", "Z1HC", 0xDE, 2,  8, VERBOSE_FLAG) { }            // 0xDE
    RST_18H_In::RST_18H_In()     : Instruction( "RST",     "RST 18H", "----", 0xDF, 1, 16, VERBOSE_FLAG) { }            // 0xDF
    
// =================================================================================================
// OpCodes 0xE0 - 0xEF
// =================================================================================================

 LDH_a8_A_In::LDH_a8_A_In()    : Instruction( "LDH", "LDH (a8), A", "----", 0xE0, 2, 12, VERBOSE_FLAG) { }       // 0xE0
   POP_HL_In::POP_HL_In()      : Instruction( "POP",      "POP HL", "----", 0xE1, 1, 12, VERBOSE_FLAG) { }       // 0xE1
 LD_mC_A_In::LD_mC_A_In()      : Instruction(  "LD",   "LD (C), A", "----", 0xE2, 1,  8, VERBOSE_FLAG) { }       // 0xE2 (bugfix: was 2 bytes, now 1 byte [table says 2 though])
// 0xE3: no operation for this opcode in LR35902
// 0xE4: no operation for this opcode in LR35902
  PUSH_HL_In::PUSH_HL_In()     : Instruction("PUSH",     "PUSH HL", "----", 0xE5, 1, 16, VERBOSE_FLAG) { }       // 0xE5
   AND_d8_In::AND_d8_In()      : Instruction("AND",    "AND A, d8", "Z010", 0xE6, 2,  8, VERBOSE_FLAG) { }       // 0xE6
  RST_20H_In::RST_20H_In()     : Instruction("RST",      "RST 20H", "----", 0xE7, 1, 16, VERBOSE_FLAG) { }       // 0xE7
ADD_SP_r8_In::ADD_SP_r8_In() : Instruction("ADD",   "ADD SP, r8", "00HC",   0xE8, 2, 16, VERBOSE_FLAG) { }       // 0xE8
   JP_mHL_In::JP_mHL_In()      : Instruction( "JP",      "JP (HL)", "----", 0xE9, 1,  4, VERBOSE_FLAG) { }       // 0xE9
 LD_a16_A_In::LD_a16_A_In()    : Instruction( "LD",  "LD (a16), A", "----", 0xEA, 3, 16, VERBOSE_FLAG) { }       // 0xEA
// 0xEB: no operation for this opcode in LR35902
// 0xEC: no operation for this opcode in LR35902
// 0xED: no operation for this opcode in LR35902
   XOR_d8_In::XOR_d8_In()      : Instruction( "XOR",      "XOR d8", "Z000", 0xEE, 2,  8, VERBOSE_FLAG) { }       // 0xEE
  RST_28H_In::RST_28H_In()     : Instruction( "RST",     "RST 28H", "----", 0xEF, 1, 16, VERBOSE_FLAG) { }       // 0xEF
  
// =================================================================================================
// OpCodes 0xF0 - 0xFF
// =================================================================================================

 LDH_A_a8_In::LDH_A_a8_In(): Instruction( "LDH", "LDH A, (a8)", "----", 0xF0, 2, 12, VERBOSE_FLAG) { }    // 0xF0
   POP_AF_In::POP_AF_In()  : Instruction( "POP",      "POP AF", "----", 0xF1, 1, 12, VERBOSE_FLAG) { }    // 0xF1
  LD_A_mC_In::LD_A_mC_In() : Instruction(  "LD",  "LDH A, (C)", "----", 0xF2, 1,  8, VERBOSE_FLAG) { }    // 0xF2 (bugfix: was 2 bytes, now 1 byte [table says 2 though])
       DI_In::DI_In()      : Instruction(  "DI",          "DI", "----", 0xF3, 1,  4, VERBOSE_FLAG) { }    // 0xF3
// 0xF4: no operation for this opcode in LR35902
  PUSH_AF_In::PUSH_AF_In() : Instruction("PUSH",     "PUSH AF", "----", 0xF5, 1, 16, VERBOSE_FLAG) { }    // 0xF5
    OR_d8_In::OR_d8_In()   : Instruction(  "OR",    "OR A, d8", "Z000", 0xF6, 2,  8, VERBOSE_FLAG) { }    // 0xF6
  RST_30H_In::RST_30H_In() : Instruction( "RST",     "RST 30H", "----", 0xF7, 1, 16, VERBOSE_FLAG) { }    // 0xF7
LD_HL_SP_r8_In::LD_HL_SP_r8_In() : Instruction("LD","LD HL, SP+r8", "00HC", 0xF8, 2, 12, VERBOSE_FLAG) { }// 0xF8
 LD_SP_HL_In::LD_SP_HL_In(): Instruction(  "LD",   "LD SP, HL", "----", 0xF9, 1,  8, VERBOSE_FLAG) { }    // 0xF9
 LD_A_a16_In::LD_A_a16_In(): Instruction(  "LD",   "LD A, a16", "----", 0xFA, 1, 16, VERBOSE_FLAG) { }    // 0xFA
       EI_In::EI_In()      : Instruction(  "EI",          "EI", "----", 0xFB, 1,  4, VERBOSE_FLAG) { }    // 0xFB
// 0xFC: no operation for this opcode in LR35902
// 0xFD: no operation for this opcode in LR35902
    CP_d8_In::CP_d8_In()   : Instruction(  "CP",       "CP d8", "Z1HC", 0xFE, 2,  8, VERBOSE_FLAG) { }    // 0xFE
  RST_38H_In::RST_38H_In() : Instruction( "RST",     "RST 38H", "----", 0xFF, 1, 16, VERBOSE_FLAG) { }    // 0xFF
  
// Implementation of OpCode functionallity 

// =================================================================================================
// OpCodes 0x00 - 0x0F
// =================================================================================================

void       NOP_In::op(LR35902& cpu, Memory& memory) {  }                                                          // 0x00
void LD_BC_d16_In::op(LR35902& cpu, Memory& memory) { cpu.registers.BC = memory.read_16(cpu.registers.PC + 1); }  // 0x01
void  LD_mBC_A_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.BC, cpu.registers.A); }        // 0x02
void    INC_BC_In::op(LR35902& cpu, Memory& memory) { cpu.inc_16bit_reg(cpu.registers.BC); }                      // 0x03
void     INC_B_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.B); }                        // 0x04
void     DEC_B_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.B); }                        // 0x05
void   LD_B_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = memory.read_8(cpu.registers.PC + 1); }    // 0x06
void      RLCA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_left_c_reg_a(); }                                 // 0x07
void LD_a16_SP_In::op(LR35902& cpu, Memory& memory) { uint16 addr = memory.read_16(cpu.registers.PC + 1);         // 0x08
                                                      memory.write_16(addr, cpu.registers.SP); }                 
void ADD_HL_BC_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.HL, cpu.registers.BC); }        // 0x09
void  LD_A_mBC_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_8(cpu.registers.BC); }        // 0x0A
void    DEC_BC_In::op(LR35902& cpu, Memory& memory) { cpu.dec_16bit_reg(cpu.registers.BC);  }                     // 0x0B
void     INC_C_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.C);  }                       // 0x0C
void     DEC_C_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.C);  }                       // 0x0D
void   LD_C_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = memory.read_8(cpu.registers.PC + 1);  }   // 0x0E
void      RRCA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_right_c_reg_a();  }                               // 0x0F

// =================================================================================================
// OpCodes 0x10 - 0x1F
// =================================================================================================

void      STOP_In::op(LR35902& cpu, Memory& memory) { cpu.running = false; }                                      // 0x10                                                       // 0x10
void LD_DE_d16_In::op(LR35902& cpu, Memory& memory) { cpu.registers.DE = memory.read_16(cpu.registers.PC + 1); }  // 0x11
void  LD_mDE_A_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.DE, cpu.registers.A);}         // 0x12
void    INC_DE_In::op(LR35902& cpu, Memory& memory) { cpu.inc_16bit_reg(cpu.registers.DE); }                      // 0x13
void     INC_D_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.D); }                        // 0x14
void     DEC_D_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.D); }                        // 0x15
void   LD_D_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = memory.read_8(cpu.registers.PC + 1); }    // 0x16
void       RLA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_left_reg_a();  }                                  // 0x17
void     JR_r8_In::op(LR35902& cpu, Memory& memory) { uint8 r8 = memory.read_8(cpu.registers.PC + 1);             // 0x18
                                                      if(r8 <= 0x7F) cpu.registers.PC += r8; 
                                                      else cpu.registers.PC -= (((~r8) + 1) & 0x7F); }
void ADD_HL_DE_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.HL, cpu.registers.DE); }        // 0x19
void  LD_A_mDE_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_8(cpu.registers.DE); }        // 0x1A
void    DEC_DE_In::op(LR35902& cpu, Memory& memory) { cpu.dec_16bit_reg(cpu.registers.DE);  }                     // 0x1B
void     INC_E_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.E);  }                       // 0x1C
void     DEC_E_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.E);  }                       // 0x1D
void   LD_E_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = memory.read_8(cpu.registers.PC + 1);  }   // 0x1E
void       RRA_In::op(LR35902& cpu, Memory& memory) { cpu.shift_right_reg_a();  }                                 // 0x1F

// =================================================================================================
// OpCodes 0x20 - 0x2F
// =================================================================================================

void  JR_NZ_r8_In::op(LR35902& cpu, Memory& memory) { if(!cpu.registers.z()) { // 0x20
                                                          uint8 off = memory.read_8(cpu.registers.PC + 1); 
                                                          std::cout << "off: " << (int)off << std::endl; 
                                                          if(off < 0x7f) cpu.registers.PC = cpu.registers.PC + off; 
                                                          else cpu.registers.PC = cpu.registers.PC + (0xFF00 | off); 
                                                          addedCycles = 4; } } // bytes will be added after execution
void LD_HL_d16_In::op(LR35902& cpu, Memory& memory) { cpu.registers.HL = memory.read_16(cpu.registers.PC + 1); }  // 0x21
void LD_mHLp_A_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, cpu.registers.A);          // 0x22
                                                      cpu.inc_16bit_reg(cpu.registers.HL); } 
void    INC_HL_In::op(LR35902& cpu, Memory& memory) { cpu.inc_16bit_reg(cpu.registers.HL); }                      // 0x23
void     INC_H_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.H); }                        // 0x24
void     DEC_H_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.H); }                        // 0x25
void   LD_H_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = memory.read_8(cpu.registers.PC + 1); }    // 0x26
void       DAA_In::op(LR35902& cpu, Memory& memory) { cpu.dda(); }                                                // 0x27
void   JR_Z_r8_In::op(LR35902& cpu, Memory& memory) { if(cpu.registers.z()) {                                     // 0x28
                                                          uint8 off = memory.read_8(cpu.registers.PC + 1); 
                                                          if(off < 0x7f) cpu.registers.PC = cpu.registers.PC + off; 
                                                          else cpu.registers.PC = cpu.registers.PC - (((~off)+1)&0x7F); 
                                                          addedCycles = 4; } } // bytes will be added after execution
void ADD_HL_HL_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.HL, cpu.registers.HL); }        // 0x29
void LD_A_mHLp_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_8(cpu.registers.HL);          // 0x2A
                                                      cpu.inc_16bit_reg(cpu.registers.HL); }
void    DEC_HL_In::op(LR35902& cpu, Memory& memory) { cpu.dec_16bit_reg(cpu.registers.HL);  }                     // 0x2B
void     INC_L_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.L);  }                       // 0x2C
void     DEC_L_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.L);  }                       // 0x2D
void   LD_L_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = memory.read_8(cpu.registers.PC + 1);  }   // 0x2E
void       CPL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = (~cpu.registers.A)&0xFF; 
                                                      cpu.registers.set_n(); cpu.registers.set_h(); }             // 0x2F

// =================================================================================================
// OpCodes 0x30 - 0x3F
// =================================================================================================

  void  JR_NC_r8_In::op(LR35902& cpu, Memory& memory) { if(!cpu.registers.c()) {                                  // 0x30
                                                            uint8 off = memory.read_8(cpu.registers.PC + 1); 
                                                            if(off < 0x7f) cpu.registers.PC = cpu.registers.PC + off; 
                                                            else cpu.registers.PC = cpu.registers.PC - (((~off)+1)&0x7F); 
                                                            addedCycles = 4; } } // bytes will be added after execution
  void LD_SP_d16_In::op(LR35902& cpu, Memory& memory) { cpu.registers.SP = memory.read_16(cpu.registers.PC + 1); }// 0x31
  void LD_mHLm_A_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, cpu.registers.A);        // 0x32
                                                        cpu.dec_16bit_reg(cpu.registers.HL); } 
  void    INC_SP_In::op(LR35902& cpu, Memory& memory) { cpu.inc_16bit_reg(cpu.registers.SP); }                    // 0x33
  void   INC_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 value = memory.read_8(cpu.registers.HL);            // 0x34
                                                        cpu.inc_8bit_reg(value); 
                                                        memory.write_8(cpu.registers.HL, value); }
  void   DEC_mHL_In::op(LR35902& cpu, Memory& memory) { uint8 value = memory.read_8(cpu.registers.HL);            // 0x35
                                                        cpu.dec_8bit_reg(value); 
                                                        memory.write_8(cpu.registers.HL, value); }
  void LD_mHL_d8_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, memory.read_8(cpu.registers.PC + 1)); }  // 0x36
  void       SCF_In::op(LR35902& cpu, Memory& memory) { cpu.registers.clear_n(); cpu.registers.clear_h(); cpu.registers.set_c(); }  // 0x37
  void   JR_C_r8_In::op(LR35902& cpu, Memory& memory) { if(cpu.registers.c()) {                                    // 0x38
                                                            uint8 off = memory.read_8(cpu.registers.PC + 1); 
                                                            if(off < 0x7f) cpu.registers.PC = cpu.registers.PC + off; 
                                                            else cpu.registers.PC = cpu.registers.PC - (((~off)+1)&0x7F); 
                                                            addedCycles = 4; } } // bytes will be added after execution
  void ADD_HL_SP_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.HL, cpu.registers.SP); }       // 0x39
  void LD_A_mHLm_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_8(cpu.registers.HL);         // 0x3A
                                                        cpu.dec_16bit_reg(cpu.registers.HL); }
  void    DEC_SP_In::op(LR35902& cpu, Memory& memory) { cpu.dec_16bit_reg(cpu.registers.SP);  }                    // 0x3B
  void     INC_A_In::op(LR35902& cpu, Memory& memory) { cpu.inc_8bit_reg(cpu.registers.A);  }                      // 0x3C
  void     DEC_A_In::op(LR35902& cpu, Memory& memory) { cpu.dec_8bit_reg(cpu.registers.A);  }                      // 0x3D
  void   LD_A_d8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_8(cpu.registers.PC + 1);  }  // 0x3E 
  void       CCF_In::op(LR35902& cpu, Memory& memory) { cpu.registers.clear_n(); cpu.registers.clear_h();          // 0x3F complement carry
                                                        if(cpu.registers.c()) cpu.registers.clear_c(); 
                                                        else                  cpu.registers.set_c(); } 

// =================================================================================================
// OpCodes 0x40 - 0x4F
// =================================================================================================

void    LD_B_B_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = cpu.registers.B;  }                        // 0x40
void    LD_B_C_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = cpu.registers.C;  }                        // 0x41
void    LD_B_D_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = cpu.registers.D;  }                        // 0x42
void    LD_B_E_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = cpu.registers.E;  }                        // 0x43
void    LD_B_H_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = cpu.registers.H;  }                        // 0x44
void    LD_B_L_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = cpu.registers.L;  }                        // 0x45
void    LD_B_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = memory.read_8(cpu.registers.HL); }       // 0x46
void    LD_B_A_In::op(LR35902& cpu, Memory& memory) { cpu.registers.B = cpu.registers.A;  }                        // 0x47
void    LD_C_B_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = cpu.registers.B;  }                        // 0x48
void    LD_C_C_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = cpu.registers.C;  }                        // 0x49
void    LD_C_D_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = cpu.registers.D;  }                        // 0x4A
void    LD_C_E_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = cpu.registers.E;  }                        // 0x4B
void    LD_C_H_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = cpu.registers.H;  }                        // 0x4C
void    LD_C_L_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = cpu.registers.L;  }                        // 0x4D
void    LD_C_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = memory.read_8(cpu.registers.HL); }       // 0x4E
void    LD_C_A_In::op(LR35902& cpu, Memory& memory) { cpu.registers.C = cpu.registers.A;  }                        // 0x4F

// =================================================================================================          
// OpCodes 0x50 - 0x5F
// =================================================================================================

void    LD_D_B_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = cpu.registers.B;  }                        // 0x50
void    LD_D_C_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = cpu.registers.C;  }                        // 0x51
void    LD_D_D_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = cpu.registers.D;  }                        // 0x52
void    LD_D_E_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = cpu.registers.E;  }                        // 0x53
void    LD_D_H_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = cpu.registers.H;  }                        // 0x54
void    LD_D_L_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = cpu.registers.L;  }                        // 0x55
void  LD_D_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = memory.read_8(cpu.registers.HL); }         // 0x56
void    LD_D_A_In::op(LR35902& cpu, Memory& memory) { cpu.registers.D = cpu.registers.A;  }                        // 0x57
void    LD_E_B_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = cpu.registers.B;  }                        // 0x58
void    LD_E_C_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = cpu.registers.C;  }                        // 0x59
void    LD_E_D_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = cpu.registers.D;  }                        // 0x5A
void    LD_E_E_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = cpu.registers.E;  }                        // 0x5B
void    LD_E_H_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = cpu.registers.H;  }                        // 0x5C
void    LD_E_L_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = cpu.registers.L;  }                        // 0x5D
void  LD_E_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = memory.read_8(cpu.registers.HL); }         // 0x5E
void    LD_E_A_In::op(LR35902& cpu, Memory& memory) { cpu.registers.E = cpu.registers.A;  }                        // 0x5F

// =================================================================================================
// OpCodes 0x60 - 0x6F
// =================================================================================================

void    LD_H_B_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = cpu.registers.B;  }                        // 0x60
void    LD_H_C_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = cpu.registers.C;  }                        // 0x61
void    LD_H_D_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = cpu.registers.D;  }                        // 0x62
void    LD_H_E_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = cpu.registers.E;  }                        // 0x63
void    LD_H_H_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = cpu.registers.H;  }                        // 0x64
void    LD_H_L_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = cpu.registers.L;  }                        // 0x65
void  LD_H_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = memory.read_8(cpu.registers.HL); }         // 0x66
void    LD_H_A_In::op(LR35902& cpu, Memory& memory) { cpu.registers.H = cpu.registers.A;  }                        // 0x67
void    LD_L_B_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = cpu.registers.B;  }                        // 0x68
void    LD_L_C_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = cpu.registers.C;  }                        // 0x69
void    LD_L_D_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = cpu.registers.D;  }                        // 0x6A
void    LD_L_E_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = cpu.registers.E;  }                        // 0x6B
void    LD_L_H_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = cpu.registers.H;  }                        // 0x6C
void    LD_L_L_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = cpu.registers.L;  }                        // 0x6D
void  LD_L_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = memory.read_8(cpu.registers.HL); }         // 0x6E
void    LD_L_A_In::op(LR35902& cpu, Memory& memory) { cpu.registers.L = cpu.registers.A;  }                        // 0x6F

// =================================================================================================
// OpCodes 0x70 - 0x7F
// =================================================================================================

void  LD_mHL_B_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, cpu.registers.B);  }        // 0x70
void  LD_mHL_C_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, cpu.registers.C);  }        // 0x71
void  LD_mHL_D_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, cpu.registers.D);  }        // 0x72
void  LD_mHL_E_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, cpu.registers.E);  }        // 0x73
void  LD_mHL_H_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, cpu.registers.H);  }        // 0x74
void  LD_mHL_L_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, cpu.registers.L);  }        // 0x75
void      HALT_In::op(LR35902& cpu, Memory& memory) { cpu.halt(); }                                                // 0x76
void  LD_mHL_A_In::op(LR35902& cpu, Memory& memory) { memory.write_8(cpu.registers.HL, cpu.registers.A);  }                        // 0x77
void    LD_A_B_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = cpu.registers.B;  }                        // 0x78
void    LD_A_C_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = cpu.registers.C;  }                        // 0x79
void    LD_A_D_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = cpu.registers.D;  }                        // 0x7A
void    LD_A_E_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = cpu.registers.E;  }                        // 0x7B
void    LD_A_H_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = cpu.registers.H;  }                        // 0x7C
void    LD_A_L_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = cpu.registers.L;  }                        // 0x7D
void  LD_A_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_8(cpu.registers.HL); }         // 0x7E
void    LD_A_A_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = cpu.registers.A;  }                        // 0x7F

// =================================================================================================
// OpCodes 0x80 - 0x8F
// =================================================================================================

void   ADD_A_B_In::op(LR35902& cpu, Memory& memory) { cpu.add_8_8(cpu.registers.A, cpu.registers.B); }             // 0x80
void   ADD_A_C_In::op(LR35902& cpu, Memory& memory) { cpu.add_8_8(cpu.registers.A, cpu.registers.C); }             // 0x81
void   ADD_A_D_In::op(LR35902& cpu, Memory& memory) { cpu.add_8_8(cpu.registers.A, cpu.registers.D); }             // 0x82
void   ADD_A_E_In::op(LR35902& cpu, Memory& memory) { cpu.add_8_8(cpu.registers.A, cpu.registers.E); }             // 0x83
void   ADD_A_H_In::op(LR35902& cpu, Memory& memory) { cpu.add_8_8(cpu.registers.A, cpu.registers.H); }             // 0x84
void   ADD_A_L_In::op(LR35902& cpu, Memory& memory) { cpu.add_8_8(cpu.registers.A, cpu.registers.L); }             // 0x85
void ADD_A_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.add_8_8(cpu.registers.A, memory.read_8(cpu.registers.HL)); } // 0x86
void   ADD_A_A_In::op(LR35902& cpu, Memory& memory) { cpu.add_8_8(cpu.registers.A, cpu.registers.A); }             // 0x87
void   ADC_A_B_In::op(LR35902& cpu, Memory& memory) { cpu.adc_8_8(cpu.registers.A, cpu.registers.B); }             // 0x88
void   ADC_A_C_In::op(LR35902& cpu, Memory& memory) { cpu.adc_8_8(cpu.registers.A, cpu.registers.C); }             // 0x89
void   ADC_A_D_In::op(LR35902& cpu, Memory& memory) { cpu.adc_8_8(cpu.registers.A, cpu.registers.D); }             // 0x8A
void   ADC_A_E_In::op(LR35902& cpu, Memory& memory) { cpu.adc_8_8(cpu.registers.A, cpu.registers.E); }             // 0x8B
void   ADC_A_H_In::op(LR35902& cpu, Memory& memory) { cpu.adc_8_8(cpu.registers.A, cpu.registers.H); }             // 0x8C
void   ADC_A_L_In::op(LR35902& cpu, Memory& memory) { cpu.adc_8_8(cpu.registers.A, cpu.registers.L); }             // 0x8D
void ADC_A_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.adc_8_8(cpu.registers.A, memory.read_8(cpu.registers.HL));} // 0x8E
void   ADC_A_A_In::op(LR35902& cpu, Memory& memory) { cpu.adc_8_8(cpu.registers.A, cpu.registers.A); }             // 0x8F

// =================================================================================================
// OpCodes 0x90 - 0x9F
// =================================================================================================

void    SUB_B_In::op(LR35902& cpu, Memory& memory) { cpu.sub_8(cpu.registers.B); }                                 // 0x90
void    SUB_C_In::op(LR35902& cpu, Memory& memory) { cpu.sub_8(cpu.registers.C); }                                 // 0x91
void    SUB_D_In::op(LR35902& cpu, Memory& memory) { cpu.sub_8(cpu.registers.D); }                                 // 0x92
void    SUB_E_In::op(LR35902& cpu, Memory& memory) { cpu.sub_8(cpu.registers.E); }                                 // 0x93
void    SUB_H_In::op(LR35902& cpu, Memory& memory) { cpu.sub_8(cpu.registers.H); }                                 // 0x94
void    SUB_L_In::op(LR35902& cpu, Memory& memory) { cpu.sub_8(cpu.registers.L); }                                 // 0x95
void  SUB_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.sub_8(memory.read_8(cpu.registers.HL)); }                 // 0x96
void    SUB_A_In::op(LR35902& cpu, Memory& memory) { cpu.sub_8(cpu.registers.A); }                                 // 0x97
void    SBC_B_In::op(LR35902& cpu, Memory& memory) { cpu.sbc_8_8(cpu.registers.A, cpu.registers.B); }              // 0x98
void    SBC_C_In::op(LR35902& cpu, Memory& memory) { cpu.sbc_8_8(cpu.registers.A, cpu.registers.C); }              // 0x99
void    SBC_D_In::op(LR35902& cpu, Memory& memory) { cpu.sbc_8_8(cpu.registers.A, cpu.registers.D); }              // 0x9A
void    SBC_E_In::op(LR35902& cpu, Memory& memory) { cpu.sbc_8_8(cpu.registers.A, cpu.registers.E); }              // 0x9B
void    SBC_H_In::op(LR35902& cpu, Memory& memory) { cpu.sbc_8_8(cpu.registers.A, cpu.registers.H); }              // 0x9C
void    SBC_L_In::op(LR35902& cpu, Memory& memory) { cpu.sbc_8_8(cpu.registers.A, cpu.registers.L); }              // 0x9D
void  SBC_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.sbc_8_8(cpu.registers.A, memory.read_8(cpu.registers.HL));} // 0x9E
void    SBC_A_In::op(LR35902& cpu, Memory& memory) { cpu.sbc_8_8(cpu.registers.A, cpu.registers.A); }              // 0x9F

// =================================================================================================
// OpCodes 0xA0 - 0xAF
// =================================================================================================

void    AND_B_In::op(LR35902& cpu, Memory& memory) { cpu.and_8(cpu.registers.B); }                                 // 0xA0
void    AND_C_In::op(LR35902& cpu, Memory& memory) { cpu.and_8(cpu.registers.C); }                                 // 0xA1
void    AND_D_In::op(LR35902& cpu, Memory& memory) { cpu.and_8(cpu.registers.D); }                                 // 0xA2
void    AND_E_In::op(LR35902& cpu, Memory& memory) { cpu.and_8(cpu.registers.E); }                                 // 0xA3
void    AND_H_In::op(LR35902& cpu, Memory& memory) { cpu.and_8(cpu.registers.H); }                                 // 0xA4
void    AND_L_In::op(LR35902& cpu, Memory& memory) { cpu.and_8(cpu.registers.L); }                                 // 0xA5
void  AND_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.and_8(memory.read_8(cpu.registers.HL)); }                 // 0xA6
void    AND_A_In::op(LR35902& cpu, Memory& memory) { cpu.and_8(cpu.registers.A); }                                 // 0xA7
void    XOR_B_In::op(LR35902& cpu, Memory& memory) { cpu.xor_8(cpu.registers.B); }                                 // 0xA8
void    XOR_C_In::op(LR35902& cpu, Memory& memory) { cpu.xor_8(cpu.registers.C); }                                 // 0xA9
void    XOR_D_In::op(LR35902& cpu, Memory& memory) { cpu.xor_8(cpu.registers.D); }                                 // 0xAA
void    XOR_E_In::op(LR35902& cpu, Memory& memory) { cpu.xor_8(cpu.registers.E); }                                 // 0xAB
void    XOR_H_In::op(LR35902& cpu, Memory& memory) { cpu.xor_8(cpu.registers.H); }                                 // 0xAC
void    XOR_L_In::op(LR35902& cpu, Memory& memory) { cpu.xor_8(cpu.registers.L); }                                 // 0xAD
void  XOR_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.xor_8(memory.read_8(cpu.registers.HL));}                  // 0xAE
void    XOR_A_In::op(LR35902& cpu, Memory& memory) { cpu.xor_8(cpu.registers.A); }                                 // 0xAF

// =================================================================================================
// OpCodes 0xB0 - 0xBF
// =================================================================================================

void     OR_B_In::op(LR35902& cpu, Memory& memory) { cpu.or_8(cpu.registers.B); }                                  // 0xB0
void     OR_C_In::op(LR35902& cpu, Memory& memory) { cpu.or_8(cpu.registers.C); }                                  // 0xB1
void     OR_D_In::op(LR35902& cpu, Memory& memory) { cpu.or_8(cpu.registers.D); }                                  // 0xB2
void     OR_E_In::op(LR35902& cpu, Memory& memory) { cpu.or_8(cpu.registers.E); }                                  // 0xB3
void     OR_H_In::op(LR35902& cpu, Memory& memory) { cpu.or_8(cpu.registers.H); }                                  // 0xB4
void     OR_L_In::op(LR35902& cpu, Memory& memory) { cpu.or_8(cpu.registers.L); }                                  // 0xB5
void   OR_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.or_8(memory.read_8(cpu.registers.HL)); }                  // 0xB6
void     OR_A_In::op(LR35902& cpu, Memory& memory) { cpu.or_8(cpu.registers.A); }                                  // 0xB7
void     CP_B_In::op(LR35902& cpu, Memory& memory) { cpu.cp_8(cpu.registers.B); }                                  // 0xB8
void     CP_C_In::op(LR35902& cpu, Memory& memory) { cpu.cp_8(cpu.registers.C); }                                  // 0xB9
void     CP_D_In::op(LR35902& cpu, Memory& memory) { cpu.cp_8(cpu.registers.D); }                                  // 0xBA
void     CP_E_In::op(LR35902& cpu, Memory& memory) { cpu.cp_8(cpu.registers.E); }                                  // 0xBB
void     CP_H_In::op(LR35902& cpu, Memory& memory) { cpu.cp_8(cpu.registers.H); }                                  // 0xBC
void     CP_L_In::op(LR35902& cpu, Memory& memory) { cpu.cp_8(cpu.registers.L); }                                  // 0xBD
void   CP_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.cp_8(memory.read_8(cpu.registers.HL));}                   // 0xBE
void     CP_A_In::op(LR35902& cpu, Memory& memory) { cpu.cp_8(cpu.registers.A); }                                  // 0xBF

// =================================================================================================
// OpCodes 0xC0 - 0xCF
// =================================================================================================

void      RET_NZ_In::op(LR35902& cpu, Memory& memory) { if(cpu.retf_n(cpu.registers.z())) { cpu.registers.PC -= bytes; addedCycles = 12; } }      // 0xC0
void      POP_BC_In::op(LR35902& cpu, Memory& memory) { cpu.pop(cpu.registers.BC); }                               // 0xC1
void   JP_NZ_a16_In::op(LR35902& cpu, Memory& memory) { if(cpu.jpf_n(cpu.registers.z(), memory.read_16(cpu.registers.PC + 1))) addedCycles = 4; } // 0xC2
void      JP_a16_In::op(LR35902& cpu, Memory& memory) { cpu.jp(memory.read_16(cpu.registers.PC + 1)); }            // 0xC3
void CALL_NZ_a16_In::op(LR35902& cpu, Memory& memory) { if(cpu.callf_n(cpu.registers.z(), memory.read_16(cpu.registers.PC + 1), cpu.registers.PC + bytes)) { addedCycles = 12; cpu.registers.PC -= bytes; }  } // 0xC4
void     PUSH_BC_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.BC); }                              // 0xC5
void    ADD_A_d8_In::op(LR35902& cpu, Memory& memory) { cpu.add_8_8(cpu.registers.A, memory.read_8(cpu.registers.PC + 1)); } // 0xC6
void     RST_00H_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.PC); cpu.jp(0x0000);  }             // 0xC7
void       RET_Z_In::op(LR35902& cpu, Memory& memory) { if(cpu.retf(cpu.registers.z())) { cpu.registers.PC -= bytes; addedCycles = 12;}   }       // 0xC8
void         RET_In::op(LR35902& cpu, Memory& memory) { cpu.ret(); /* prevent PC increasing */ cpu.registers.PC -= bytes;  }                                              // 0xC9
void    JP_Z_a16_In::op(LR35902& cpu, Memory& memory) { if(cpu.jpf(cpu.registers.z(), memory.read_16(cpu.registers.PC + 1))) addedCycles = 4; }   // 0xCA
void   PREFIX_CB_In::op(LR35902& cpu, Memory& memory) { uint8 cb_op = memory.read_8(cpu.registers.PC + 1); _cb_instructions[cb_op]->execute(cpu, memory); addedBytes = 1; } // 0xCB
void  CALL_Z_a16_In::op(LR35902& cpu, Memory& memory) { if(cpu.callf(cpu.registers.z(), memory.read_16(cpu.registers.PC + 1), cpu.registers.PC + bytes)) { addedCycles = 12; cpu.registers.PC -= bytes; }  }// 0xCC
void    CALL_a16_In::op(LR35902& cpu, Memory& memory) { cpu.call(memory.read_16(cpu.registers.PC + 1), cpu.registers.PC + bytes); cpu.registers.PC -= bytes;  }         // 0xCD
void    ADC_A_d8_In::op(LR35902& cpu, Memory& memory) { cpu.adc_8_8(cpu.registers.A, memory.read_8(cpu.registers.PC + 1));} // 0xCE
void     RST_08H_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.PC); cpu.jp(0x0008);  }             // 0xCF

// =================================================================================================
// OpCodes 0xD0 - 0xDF
// =================================================================================================

void     RET_NC_In::op(LR35902& cpu, Memory& memory) { if(cpu.retf_n(cpu.registers.c())) { cpu.registers.PC -= bytes; addedCycles = 12;}  }       // 0xD0
void     POP_DE_In::op(LR35902& cpu, Memory& memory) { cpu.pop(cpu.registers.DE); }                                // 0xD1
void  JP_NC_a16_In::op(LR35902& cpu, Memory& memory) { if(cpu.jpf_n(cpu.registers.c(), memory.read_16(cpu.registers.PC + 1))) addedCycles = 4; } // 0xD2
// 0xD3: no operation for this opcode in LR35902
void CALL_NC_a16_In::op(LR35902& cpu, Memory& memory) { if(cpu.callf_n(cpu.registers.c(), memory.read_16(cpu.registers.PC + 1), cpu.registers.PC + bytes)) { addedCycles = 12; cpu.registers.PC -= bytes; }   } // 0xD4
void     PUSH_DE_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.DE); }                              // 0xD5
void      SUB_d8_In::op(LR35902& cpu, Memory& memory) { cpu.sub_8(memory.read_8(cpu.registers.PC + 1)); }          // 0xD6
void     RST_10H_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.PC); cpu.jp(0x0010);  }             // 0xD7
void       RET_C_In::op(LR35902& cpu, Memory& memory) { if(cpu.retf(cpu.registers.c())) { cpu.registers.PC -= bytes; addedCycles = 12; } }       // 0xD8
void        RETI_In::op(LR35902& cpu, Memory& memory) { cpu.reti(); cpu.registers.PC -= bytes;  }                                             // 0xD9
void    JP_C_a16_In::op(LR35902& cpu, Memory& memory) { if(cpu.jpf(cpu.registers.c(), memory.read_16(cpu.registers.PC + 1))) addedCycles = 4; } // 0xDA
// 0xDB: no operation for this opcode in LR35902
void  CALL_C_a16_In::op(LR35902& cpu, Memory& memory) { if(cpu.callf(cpu.registers.c(), memory.read_16(cpu.registers.PC + 1), cpu.registers.PC + bytes)) { addedCycles = 12; cpu.registers.PC -= bytes; }  } // 0xD4
// 0xDD: no operation for this opcode in LR35902
void    SBC_A_d8_In::op(LR35902& cpu, Memory& memory) { cpu.sbc_8_8(cpu.registers.A, memory.read_8(cpu.registers.PC + 1));} // 0xDE
void     RST_18H_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.PC); cpu.jp(0x0018);  }             // 0xDF

// =================================================================================================
// OpCodes 0xE0 - 0xEF
// =================================================================================================

void   LDH_a8_A_In::op(LR35902& cpu, Memory& memory) { memory.write_8((0xFF00 | memory.read_8(cpu.registers.PC + 1)), cpu.registers.A);  } // 0xE0
void     POP_HL_In::op(LR35902& cpu, Memory& memory) { cpu.pop(cpu.registers.HL); }                                // 0xE1
void    LD_mC_A_In::op(LR35902& cpu, Memory& memory) { memory.write_8((0xFF00 | cpu.registers.C), cpu.registers.A);  } // 0xE2
// 0xE3: no operation for this opcode in LR35902
// 0xE4: no operation for this opcode in LR35902
void    PUSH_HL_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.HL); }                               // 0xE5
void     AND_d8_In::op(LR35902& cpu, Memory& memory) { cpu.and_8(memory.read_8(cpu.registers.PC + 1)); }           // 0xE6
void    RST_20H_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.PC); cpu.jp(0x0020);  }              // 0xE7
void  ADD_SP_r8_In::op(LR35902& cpu, Memory& memory) { cpu.add_16_16(cpu.registers.SP,                             // 0xE8
                                                                     cpu.sign_ext(memory.read_8(cpu.registers.PC + 1))); 
                                                       cpu.registers.clear_z(); } // always cleared
void    JP_mHL_In::op(LR35902& cpu, Memory& memory) { cpu.jp(memory.read_16(cpu.registers.HL));  }                 // 0xE9
void  LD_a16_A_In::op(LR35902& cpu, Memory& memory) { memory.write_8(memory.read_16(cpu.registers.PC + 1), cpu.registers.A);  } // 0xEA
// 0xEB: no operation for this opcode in LR35902
// 0xEC: no operation for this opcode in LR35902
// 0xED: no operation for this opcode in LR35902
void    XOR_d8_In::op(LR35902& cpu, Memory& memory) { cpu.xor_8(memory.read_8(cpu.registers.PC + 1));}             // 0xEE
void   RST_28H_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.PC); cpu.jp(0x0028);  }               // 0xEF

// =================================================================================================
// OpCodes 0xF0 - 0xFF
// =================================================================================================

void    LDH_A_a8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_8(0xFF00 | memory.read_8(cpu.registers.PC + 1));  } // 0xF0
void      POP_AF_In::op(LR35902& cpu, Memory& memory) { cpu.pop(cpu.registers.AF); }                               // 0xF1
void     LD_A_mC_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_8(0xFF00 | cpu.registers.C);  } // 0xF2
void          DI_In::op(LR35902& cpu, Memory& memory) { cpu.di(); }                                                // 0xF3
// 0xF4: no operation for this opcode in LR35902
void     PUSH_AF_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.AF); }                              // 0xF5
void       OR_d8_In::op(LR35902& cpu, Memory& memory) { cpu.or_8(memory.read_8(cpu.registers.PC + 1)); }           // 0xF6
void     RST_30H_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.PC); cpu.jp(0x0030);  }             // 0xF7
void LD_HL_SP_r8_In::op(LR35902& cpu, Memory& memory) { cpu.registers.HL = cpu.registers.SP;                       // 0xF8
                                                        cpu.add_16_16(cpu.registers.HL, 
                                                        cpu.sign_ext(memory.read_8(cpu.registers.PC + 1))); 
                                                        cpu.registers.clear_z(); }
void    LD_SP_HL_In::op(LR35902& cpu, Memory& memory) { cpu.registers.SP = cpu.registers.HL;  }                    // 0xF9
void    LD_A_a16_In::op(LR35902& cpu, Memory& memory) { cpu.registers.A = memory.read_8(memory.read_16(cpu.registers.PC + 1)); } // 0xFA
void          EI_In::op(LR35902& cpu, Memory& memory) { cpu.ei(); }                                                // 0xFB
// 0xFC: no operation for this opcode in LR35902
// 0xFD: no operation for this opcode in LR35902
void       CP_d8_In::op(LR35902& cpu, Memory& memory) { cpu.cp_8(memory.read_8(cpu.registers.PC + 1));}            // 0xFE
void     RST_38H_In::op(LR35902& cpu, Memory& memory) { cpu.push(cpu.registers.PC); cpu.jp(0x0038);  }             // 0xFF
